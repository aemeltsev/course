#include <QCoreApplication>
#include <QVector>
#include <QtMath>
#include <QTime>
#include <QElapsedTimer>
#include <QDebug>
#include <QImage>
#include <QRandomGenerator>

#include "buffer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage input_im("lena.png");
    input_im = input_im.convertToFormat(QImage::Format_RGB32);
    QImage output_im(input_im.size(), input_im.format());

    // Here we configure the denoise parameters.
    int radius = 3;

    // Add noise to the image
    for (int i = 0; i < 100000; i++) {
        auto var = QRandomGenerator::global()->bounded(256);
        input_im.setPixel(var % input_im.width(),
                         var % input_im.height(),
                         qRgb(var % 256,
                              var % 256,
                              var % 256));
    }

    dip::Buffer image(input_im);
    dip::Buffer buffer;

    QElapsedTimer timer;
    timer.start();

    for (auto y = 0; y < input_im.height(); ++y) {
        QRgb *oLine = reinterpret_cast<QRgb*>(output_im.scanLine(y));
        int yp = qMax(y - radius, 0); // the position of the center pixel in the window along the y-axis
        int kh = qMin(y + radius, input_im.height() - 1) - yp + 1;

        for (auto x = 0; x < input_im.width(); ++x) {
            int xp = qMax(x - radius, 0); // the position of the center pixel in the window along the x-axis
            int kw = qMin(x + radius, input_im.width() - 1) - xp + 1;

            // Adjust the buffer to the number of pixels from the window.
            buffer.resize(kw, kh);

            // Copy all pixels in scan window to the buffer.
            for(auto j=0; j<kh; ++j){
                QVector<const quint8*> pixel = image.constPixel(xp, yp + j);
                buffer.copy(j, pixel);
            }

            // Sort the buffer.
            buffer.sort();

            // Select the pixel in the middle of the buffer.
            QVector<quint8> pixel = buffer[buffer.size()/2];

            oLine[x] = qRgb(pixel[0], pixel[1], pixel[2]);
        }
    }

    qDebug() << timer.elapsed();
    output_im.save("median.png");

    return EXIT_SUCCESS;
}
