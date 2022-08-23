#include <QCoreApplication>
#include <QImage>
#include <QVector>
#include "rgbpixel.h"

void integralImage(const QImage& image, QVector<dip::PixRGB<quint32>>& integral)
{
    auto oWidth = image.width() + 1;
    auto oHeight = image.height() + 1;
    integral.resize(oWidth * oHeight);

    for(int y = 1; y < oHeight; ++y)
    {
        const QRgb *line = reinterpret_cast<const QRgb*>(image.constScanLine(y - 1));
        dip::PixRGB<quint32> sum;

        for(int x = 1; x < oWidth; ++x)
        {
            QRgb cur_pixel = line[x - 1];

            sum += cur_pixel;

            int offset = x + y * oWidth;

            int offsetPrevious = offset - oWidth;

            integral[offset] = sum + integral[offsetPrevious];
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

    std::size_t k_width = input_im.width() + 1;
    QVector<dip::PixRGB<quint32>> integral;
    integralImage(input_im, integral);

    int radius = 10;

    for(int y = 0; y < input_im.height(); ++y)
    {
        const QRgb *in_line = reinterpret_cast<const QRgb*>(input_im.constScanLine(y));
        QRgb *out_line = reinterpret_cast<QRgb*>(output_im.scanLine(y));
        auto yp = qMax(y - radius, 0);
        auto kh = qMin(y + radius, input_im.height() - 1) - yp + 1;

        for(int x = 0; x < input_im.width(); ++x)
        {
            auto xp = qMax(x - radius, 0);
            auto kw = qMin(x + radius, input_im.width() - 1) - xp + 1;

            dip::PixRGB<quint32> *p0 = integral.data() + xp + yp * k_width;
            dip::PixRGB<quint32> *p1 = p0 + kw;
            dip::PixRGB<quint32> *p2 = p0 + kh * k_width;
            dip::PixRGB<quint32> *p3 = p2 + kw;

            quint32 sumR = p0->pRed() - p1->pRed() - p2->pRed() + p3->pRed();
            quint32 sumG = p0->pGreen() - p1->pGreen() - p2->pGreen() + p3->pGreen();
            quint32 sumB = p0->pBlue() - p1->pBlue() - p2->pBlue() + p3->pBlue();

            qreal ks = kw * kh;

            quint8 r = qRound(sumR / ks);
            quint8 g = qRound(sumG / ks);
            quint8 b = qRound(sumB / ks);

            out_line[x] = qRgba(r, g, b, qAlpha(in_line[x]));
        }
    }
    output_im.save("out.png");

    return EXIT_SUCCESS;
}
