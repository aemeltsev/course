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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage input_im("lena.png");
    input_im = input_im.convertToFormat(QImage::Format_RGB32);
    QImage output_im(input_im.size(), input_im.format());

    for (auto y = 0; y < input_im.height(); ++y) {
        const QRgb *in_line = reinterpret_cast<const QRgb*>(input_im.constScanLine(y));
        const QRgb *in_line_prev = reinterpret_cast<const QRgb*>(input_im.constScanLine(y-1));
        QRgb *out_line = reinterpret_cast<QRgb*>(output_im.scanLine(y));

        for (auto x = 0; x < input_im.width(); ++x) {
            int diff_x = qGray(in_line[x]);
            int diff_y = diff_x;

            if(x>0) diff_x -= qGray(in_line[x-1]);
            if(y>0) diff_y -= qGray((in_line_prev[x]));

            int grad = static_cast<int>(gradient(diff_x, diff_y));
            quint8 c = qBound(0, grad, 255);
            out_line[x] = qRgba(c, c, c, qAlpha(in_line[x]));
        }
    }

    output_im.save("magnitude.png");

    return EXIT_SUCCESS;
}
