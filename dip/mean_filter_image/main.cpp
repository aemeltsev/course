#include <QCoreApplication>
#include <QVector>
#include <QtMath>
#include <QTime>
#include <QElapsedTimer>
#include <QDebug>
#include <QImage>
#include <QRandomGenerator>

#include "rgbpixel.h"

void integralImage(const QImage& image,
                   QVector<dip::PixRGB<quint8>>& planes,
                   QVector<dip::PixRGB<quint32>>& integral,
                   QVector<dip::PixRGB<quint64>>& integral2)
{
    auto oWidth = image.width() + 1;
    auto oHeight = image.height() + 1;
    planes.resize(image.width() * image.height());
    integral.resize(oWidth * oHeight);
    integral2.resize(oWidth * oHeight);

    for(int y = 1; y < oHeight; ++y)
    {
        const QRgb *line = reinterpret_cast<const QRgb*>(image.constScanLine(y - 1));
        dip::PixRGB<quint8>* planesLine = planes.data() + (y - 1) * image.width();

        dip::PixRGB<quint32> sum;
        dip::PixRGB<quint64> sum2;

        for(int x = 1; x < oWidth; ++x)
        {
            QRgb pixel = line[x - 1];

            sum += pixel;
            sum2 = sum2 + dip::pow<quint64>(pixel, 2);

            int offset = x + y * oWidth;

            int offsetPrevious = offset - oWidth;

            planesLine[x - 1] = pixel;

            integral[offset] = sum + integral[offsetPrevious];
            integral2[offset] = sum2 + integral2[offsetPrevious];
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage input_im("lena.png");
    input_im = input_im.convertToFormat(QImage::Format_RGB32);
    QImage output_im(input_im.size(), input_im.format());

    // Here we configure the denoise parameters.
    int radius = 2;
    int mu = 0;
    qreal sigma = 1;

    // Add noise to the image
    for (int i = 0; i < 25000; i++) {
        auto var = QRandomGenerator::global()->bounded(QTime::currentTime().msec());
        input_im.setPixel(var % input_im.width(),
                         var % input_im.height(),
                         qRgb(var % 256,
                              var % 256,
                              var % 256));
    }

    int oWidth = input_im.width() + 1;
    QVector<dip::PixRGB<quint8>> planes;
    QVector<dip::PixRGB<quint32>> integral;
    QVector<dip::PixRGB<quint64>> integral2;
    integralImage(input_im, planes, integral, integral2);

    QElapsedTimer timer;
    timer.start();

    for (int y = 0, pos = 0; y < input_im.height(); ++y) {
        const QRgb *iLine = reinterpret_cast<const QRgb*>(input_im.constScanLine(y));
        QRgb *oLine = reinterpret_cast<QRgb*>(output_im.scanLine(y));
        int yp = qMax(y - radius, 0);
        int kh = qMin(y + radius, input_im.height() - 1) - yp + 1;

        for (int x = 0; x < input_im.width(); ++x, ++pos) {
            int xp = qMax(x - radius, 0);
            int kw = qMin(x + radius, input_im.width() - 1) - xp + 1;

            dip::PixRGB<quint32> sum = dip::integral_sum(integral.constData(), oWidth,
                                                         xp, yp, kw, kh);
            dip::PixRGB<quint64> sum2 = dip::integral_sum(integral2.constData(), oWidth,
                                                          xp, yp, kw, kh);
            qreal ks = kw * kh;

            // Calculate mean and standard deviation.
            dip::PixRGB<qreal> mean = sum / ks;
            dip::PixRGB<qreal> dev = dip::sqrt(ks * sum2 - dip::pow<quint32>(sum, 2)) / ks;

            mean = bound(0., mean + mu, 255.);
            dev = bound(0., mult(sigma, dev), 127.);

            dip::PixRGB<qreal> sumP;
            dip::PixRGB<qreal> sumW;

            for (int j = 0; j < kh; j++) {
                const dip::PixRGB<quint8> *line = planes.constData()
                                                  + (yp + j) * input_im.width();

                for (int i = 0; i < kw; i++) {
                    // Calculate weighted avverage.
                    dip::PixRGB<quint8> pixel = line[xp + i];
                    dip::PixRGB<qreal> d = mean - pixel;
                    dip::PixRGB<qreal> h = mult(-2., dev * dev);
                    dip::PixRGB<qreal> weight = exp(d * d / h);
                    sumP += weight * pixel;
                    sumW += weight;
                }
            }

            // Normalize result.
            sumP /= sumW;
            oLine[x] = qRgba(sumP.pRed(), sumP.pGreen(), sumP.pBlue(), qAlpha(iLine[x]));

        }
    }

    qDebug() << timer.elapsed();
    output_im.save("gauss.png");

    return EXIT_SUCCESS;
}
