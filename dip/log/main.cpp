#include <QtGlobal>
#include <QCoreApplication>
#include <QtMath>
#include <QImage>

enum class GradientOperators
{
    GradientXDirection,
    GradientYDirection,
    GradientMagnitude,
    GradientDirection
};

inline qreal gradient(int diff_x, int diff_y, GradientOperators g_op = GradientOperators::GradientMagnitude)
{
    switch (g_op)
    {
    case GradientOperators::GradientXDirection:
        return qAbs(diff_x);

    case GradientOperators::GradientYDirection:
        return qAbs(diff_y);

    case GradientOperators::GradientMagnitude:
        return qAbs(diff_x) + qAbs(diff_y);

    case GradientOperators::GradientDirection:
        if(qAbs(diff_x) == 0 || qAbs(diff_y) == 0){
            return 255;
        }
        else{
            return qAtan(qAbs(diff_y)/qAbs(diff_x));
        }
    default:
        break;
    }

    return 0;
}

inline QVector<qreal> dip_log(int r,
                              qreal sigma,
                              qreal scale_xy,
                              qreal scale_w,
                              bool axys_x=false,
                              int* kern_len=nullptr)
{
    int kern_size = 2 * r + 1;
    QVector<qreal> result(kern_size * kern_size);

    for(auto j=0; j<kern_size; ++j)
    {
        for(auto i=0; i<kern_size; ++i)
        {
            qreal x = scale_xy * (i - r);
            qreal y = scale_xy * (j - r);

            qreal k = - scale_w * (axys_x ? y : x) / (qPow(sigma, 3) * qSqrt(2 * M_PI));
            qreal sigma2 = -2 * sigma * sigma;
            qreal weight = k * qExp((x * x + y * y) / sigma2);
            result[i + j * kern_size] = weight;
        }
    }
    *kern_len = kern_size;
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage input_im("lena.png");
    input_im = input_im.convertToFormat(QImage::Format_RGB32);
    QImage output_im(input_im.size(), input_im.format());

    int radius = 1;
    qreal sigma = 1;
    qreal scale_xy = 1;
    qreal scale_w = 1;

    int kern_len;
    QVector<qreal> kern_x = dip_log(radius, sigma, scale_xy, scale_w, false, &kern_len);
    QVector<qreal> kern_y = dip_log(radius, sigma, scale_xy, scale_w, true, &kern_len);

    for (auto y = 0; y < input_im.height(); ++y) {
        const QRgb *in_line = reinterpret_cast<const QRgb*>(input_im.constScanLine(y));
        QRgb *out_line = reinterpret_cast<QRgb*>(output_im.scanLine(y));

        for (auto x = 0; x < input_im.width(); ++x) {
            qreal sum_x = 0;
            qreal sum_y = 0;

            // Apply kernel
            for(int j=0, pos=0; j<kern_len; ++j)
            {
                const QRgb *line = reinterpret_cast<const QRgb*>(input_im.constScanLine(y + j * radius));

                if(y + j < radius || y + j >= radius + input_im.height()) continue;

                for(auto i=0; i<kern_len; ++i, ++pos)
                {
                    if(x + i < radius || x + i >= radius + input_im.width()) continue;

                    quint8 pixel = qGray(line[x + i - radius]);
                    sum_x += kern_x[pos] * pixel;
                    sum_y += kern_y[pos] * pixel;
                }
            }

            int grad = gradient(sum_x, sum_y);
            quint8 c = qBound(0, grad, 255);
            out_line[x] = qRgba(c, c, c, qAlpha(in_line[x]));
        }
    }

    output_im.save("log_edge.png");

    return EXIT_SUCCESS;
}
