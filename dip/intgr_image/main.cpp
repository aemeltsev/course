#include <QCoreApplication>
#include <QImage>
#include "rgbpixel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage input_im("lena.png");
    input_im = input_im.convertToFormat(QImage::Format_RGB32);
    QImage output_im(input_im.size(), input_im.format());

    QRgb* out_line = nullptr;
    const QRgb* in_line = nullptr;

    std::size_t k_width = 3;
    std::size_t k_height = 3;
    /*
    std::size_t k_width = 7;
    std::size_t k_height = 7;
    */
    /*
    std::size_t k_width = 5;
    std::size_t k_height = 5;
    */

    std::size_t offset_x = static_cast<std::size_t>((k_width - 1) / 2);
    std::size_t offset_y = static_cast<std::size_t>((k_height - 1) / 2);

    for(auto y = 0; y < input_im.height(); ++y)
    {
        out_line = reinterpret_cast<QRgb*>(output_im.scanLine(y));

        for(auto x = 0; x < input_im.width(); ++x)
        {
            qreal pixel_R = 0;
            qreal pixel_G = 0;
            qreal pixel_B = 0;

            //Apply convolution to each channel
            for(auto j = 0; j < k_height; ++j)
            {
                if(y + j < offset_y || y + j - offset_y >= input_im.height())
                {
                    continue;
                }

                in_line = reinterpret_cast<const QRgb*>(input_im.constScanLine(y + j - offset_y));

                for(auto i = 0; i < k_width; ++i)
                {
                    if(x + i < offset_x || x + i - offset_x >= input_im.width())
                    {
                        continue;
                    }

                    auto k = kernel::edge[i + j * k_width];
                    auto pixel = in_line[x + i - offset_x];

                    pixel_R += k * qRed(pixel);
                    pixel_G += k * qGreen(pixel);
                    pixel_B += k * qBlue(pixel);
                }
            }

            quint8 r = qBound(0., pixel_R, 255.);
            quint8 g = qBound(0., pixel_G, 255.);
            quint8 b = qBound(0., pixel_B, 255.);
            out_line[x] = qRgb(r, g, b);
        }
    }
    output_im.save("out.png");

    return a.exec();
}
