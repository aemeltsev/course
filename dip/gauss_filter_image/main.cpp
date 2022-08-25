#include <QCoreApplication>
#include <QVector>
#include <QtMath>
#include <QTime>
#include <QElapsedTimer>
#include <QDebug>
#include <QImage>
#include <QRandomGenerator>

#include "rgbpixel.h"

inline QVector<qreal> gaussKernel(int radius, qreal sigma, int *kl)
{
    int kw = 2 * radius + 1;
    QVector<qreal> kernel(kw * kw);
    qreal sum = 0;

    // Create convolution matrix according to the formula:
    for (int j = 0; j < kw; j++)
    {
        for (int i = 0; i < kw; i++)
        {
            int x = i - radius;
            int y = j - radius;
            qreal sigma2 = -2 * sigma * sigma;
            qreal weight = qExp((x * x + y * y) / sigma2);
            kernel[i + j * kw] = weight;
            sum += weight;
        }
    }

    // Normalize weights.
    for (int i = 0; i < kernel.size(); i++)
        kernel[i] /= sum;

    *kl = kw;

    return kernel;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage inImage("lena.png");
    inImage = inImage.convertToFormat(QImage::Format_RGB32);
    QImage outImage(inImage.size(), inImage.format());

    // Here we configure the denoise parameters.
    int radius = 3;
    qreal sigma = 1000;

    // Create gaussian denoise kernel.
    int kw;
    QVector<qreal> kernel = gaussKernel(radius, sigma, &kw);

    // Add noise to the image
    QRandomGenerator *rg = QRandomGenerator::global();
    for (int i = 0; i < 5000; i++) {
        inImage.setPixel(rg->bounded(QTime::currentTime().msec()) % inImage.width(),
                         rg->bounded(QTime::currentTime().msec()) % inImage.height(),
                         qRgb(rg->bounded(QTime::currentTime().msec()) % 256,
                              rg->bounded(QTime::currentTime().msec()) % 256,
                              rg->bounded(QTime::currentTime().msec()) % 256));
    }

    QElapsedTimer timer;
    timer.start();

    for (int y = 0; y < inImage.height(); y++) {
        const QRgb *iLine = (const QRgb *) inImage.constScanLine(y);
        QRgb *oLine = (QRgb *) outImage.scanLine(y);

        for (int x = 0; x < inImage.width(); x++) {
            dip::PixRGB<qreal> sum;
            qreal sumW = 0;

            // Apply kernel.
            for (int j = 0, pos = 0; j < kw; j++) {
                const QRgb *line = (const QRgb *) inImage.constScanLine(y + j - radius);

                if (y + j < radius
                    || y + j >= radius + inImage.height())
                    continue;

                for (int i = 0; i < kw; i++, pos++) {
                    if (x + i < radius
                        || x + i >= radius + inImage.width())
                        continue;

                    dip::PixRGB<quint32> pixel(line[x + i - radius]);
                    qreal weight = kernel[pos];
                    sum += weight * pixel;
                    sumW += weight;
                }
            }

            // We normallize the kernel because the size of the kernel is not
            // fixed.
            sum /= sumW;

            oLine[x] = qRgba(static_cast<int>(sum.pRed()),
                             static_cast<int>(sum.pGreen()),
                             static_cast<int>(sum.pBlue()),
                             qAlpha(iLine[x]));
        }
    }

    qDebug() << timer.elapsed();
    outImage.save("gauss.png");

    return EXIT_SUCCESS;
}
