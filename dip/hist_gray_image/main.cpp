#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QImage>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QString filename = "data.txt";
    QFile file(filename);

    QHash<int, int> H;
    for(auto i=0; i<256; ++i) { H.insert(i, 0); }

    QImage input_im("lena.png");
    input_im = input_im.convertToFormat(QImage::Format_RGB32);
    QImage output_im(input_im.size(), input_im.format());

    QRgb* out_line = nullptr;
    const QRgb* in_line = nullptr;

    for(auto y = 0; y < input_im.height(); ++y)
    {
        const QRgb *in_line = reinterpret_cast<const QRgb*>(input_im.constScanLine(y));
        QRgb *out_line = reinterpret_cast<QRgb*>(output_im.scanLine(y));

        for(auto x = 0; x < input_im.width(); ++x)
        {
            auto gray = qGray(in_line[x]);
            out_line[x] = qRgb(gray, gray, gray);
            H[gray] += 1;
        }
    }

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QHashIterator<int, int> i(H);
    while (i.hasNext()) {
        i.next();
        out << i.key() << ": " << i.value() << Qt::endl;
    }

    output_im.save("out.png");
    file.close();

    return EXIT_SUCCESS;
}
