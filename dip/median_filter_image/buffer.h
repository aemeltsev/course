#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <cstring>
#include <QImage>

namespace dip {

class Buffer
{
    std::vector<quint8> m_r;
    std::vector<quint8> m_g;
    std::vector<quint8> m_b;
    int m_width;
    int m_size;

public:
    Buffer()
        :m_width(0)
        ,m_size(0)
    {}

    Buffer(const QImage& image)
    {
        m_width = image.width();
        m_size = m_width * image.height();
        m_r.resize(m_size);
        m_g.resize(m_size);
        m_b.resize(m_size);

        const QRgb* bits = reinterpret_cast<const QRgb*>(image.constBits());

        for(auto i=0; i<m_size; ++i)
        {
            auto pixel = bits[i];
            m_r[i] = qRed(pixel);
            m_g[i] = qGreen(pixel);
            m_b[i] = qBlue(pixel);
        }
    }

    void sort()
    {
        std::sort(m_r.begin(), m_r.end());
        std::sort(m_g.begin(), m_g.end());
        std::sort(m_b.begin(), m_b.end());
    }

    void resize(int width, int height)
    {
        m_width = width;
        m_size = m_width * height;
        m_r.resize(m_size);
        m_g.resize(m_size);
        m_b.resize(m_size);
    }

    void copy(int line, const QVector<const quint8*>& pixel)
    {
        std::memcpy(m_r.data() + line * m_width, pixel[0], m_width * sizeof(quint8));
        std::memcpy(m_g.data() + line * m_width, pixel[1], m_width * sizeof(quint8));
        std::memcpy(m_b.data() + line * m_width, pixel[2], m_width * sizeof(quint8));
    }

    QVector<const quint8*> constPixel(int x, int y) const
    {
        QVector<const quint8*> lines(3);
        lines[0] = m_r.data() + x + y * m_width;
        lines[1] = m_g.data() + x + y * m_width;
        lines[2] = m_b.data() + x + y * m_width;

        return lines;
    }

    QVector<quint8> operator[](int i)
    {
        QVector<quint8> pixel(3);
        pixel[0] = m_r[i];
        pixel[1] = m_g[i];
        pixel[2] = m_b[i];

        return pixel;
    }

    std::size_t size(){ return m_size; }
};
} // namespace dip
#endif // BUFFER_H
