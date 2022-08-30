#ifndef RGBPIXEL_H
#define RGBPIXEL_H
#include <QtGlobal>
#include <QColor>
#include <cmath>

namespace dip
{

template<typename T>
class PixRGB
{
    T m_r;
    T m_g;
    T m_b;

public:
    explicit PixRGB()
        :m_r(0)
        ,m_g(0)
        ,m_b(0)
    {}

    PixRGB(const T r, const T g, const T b)
        :m_r(r)
        ,m_g(g)
        ,m_b(b)
    {}

    PixRGB(QRgb pixel)
        :m_r(qRed(pixel))
        ,m_g(qGreen(pixel))
        ,m_b(qBlue(pixel))
    {}

    PixRGB(const PixRGB<T>& pix)
    {
        if(this != &pix)
        {
            this->m_r = pix.m_r;
            this->m_g = pix.m_g;
            this->m_b = pix.m_b;
        }
    }

    operator PixRGB<qreal>() const
    {
        return PixRGB<qreal>(static_cast<qreal>(m_r),
                             static_cast<qreal>(m_g),
                             static_cast<qreal>(m_b));
    }

    PixRGB<T>& operator=(const PixRGB<T>& pix)
    {
        if(this != &pix)
        {
            this->m_r = pix.m_r;
            this->m_g = pix.m_g;
            this->m_b = pix.m_b;
        }
        return *this;
    }

    PixRGB<T> operator+(const PixRGB<T>& other) const
    {
        return PixRGB<T>(this->m_r + other.m_r,
                         this->m_g + other.m_g,
                         this->m_b + other.m_b);
    }

    PixRGB<T> operator+(const PixRGB<T>& other)
    {
        return PixRGB<T>(this->m_r + other.m_r,
                         this->m_g + other.m_g,
                         this->m_b + other.m_b);
    }


    PixRGB<T> operator-(const PixRGB<T>& other) const
    {
        return PixRGB<T>(this->m_r - other.m_r,
                         this->m_g - other.m_g,
                         this->m_b - other.m_b);
    }

    PixRGB<T> operator-(const PixRGB<T>& other)
    {
        return PixRGB<T>(this->m_r - other.m_r,
                         this->m_g - other.m_g,
                         this->m_b - other.m_b);
    }

    PixRGB<T> operator*(const PixRGB<T>& other) const
    {
        return PixRGB<T>(this->m_r * other.m_r,
                         this->m_g * other.m_g,
                         this->m_b * other.m_b);
    }

    PixRGB<T> operator*(const PixRGB<T>& other)
    {
        return PixRGB<T>(this->m_r * other.m_r,
                         this->m_g * other.m_g,
                         this->m_b * other.m_b);
    }

    PixRGB<T> operator/(const PixRGB<T>& other) const
    {
        return PixRGB<T>(this->m_r / other.m_r,
                         this->m_g / other.m_g,
                         this->m_b / other.m_b);
    }

    PixRGB<T> operator/(const PixRGB<T>& other)
    {
        return PixRGB<T>(this->m_r / other.m_r,
                         this->m_g / other.m_g,
                         this->m_b / other.m_b);
    }

    PixRGB<T>& operator+=(const PixRGB<T>& other)
    {
        this->m_r += other.m_r;
        this->m_g += other.m_g;
        this->m_b += other.m_b;

        return *this;
    }

    PixRGB<T>& operator-=(const PixRGB<T>& other)
    {
        this->m_r -= other.m_r;
        this->m_g -= other.m_g;
        this->m_b -= other.m_b;

        return *this;
    }

    PixRGB<T>& operator*=(const PixRGB<T>& other)
    {
        this->m_r *= other.m_r;
        this->m_g *= other.m_g;
        this->m_b *= other.m_b;

        return *this;
    }

    PixRGB<T>& operator/=(const PixRGB<T>& other)
    {
        this->m_r /= other.m_r;
        this->m_g /= other.m_g;
        this->m_b /= other.m_b;

        return *this;
    }

    PixRGB<T> operator+(const QRgb& px)
    {
        return PixRGB<T>(this->m_r + static_cast<T>(qRed(px)),
                         this->m_g + static_cast<T>(qGreen(px)),
                         this->m_b + static_cast<T>(qBlue(px)));
    }

    PixRGB<T> operator-(const QRgb& px)
    {
        return PixRGB<T>(this->m_r - static_cast<T>(qRed(px)),
                         this->m_g - static_cast<T>(qGreen(px)),
                         this->m_b - static_cast<T>(qBlue(px)));
    }

    PixRGB<T> operator*(const QRgb& px)
    {
        return PixRGB<T>(this->m_r + static_cast<T>(qRed(px)),
                         this->m_g + static_cast<T>(qGreen(px)),
                         this->m_b + static_cast<T>(qBlue(px)));
    }

    PixRGB<T> operator/(const QRgb& px)
    {
        return PixRGB<T>(this->m_r + static_cast<T>(qRed(px)),
                         this->m_g + static_cast<T>(qGreen(px)),
                         this->m_b + static_cast<T>(qBlue(px)));
    }

    PixRGB<T>& operator+=(const QRgb& px)
    {
        this->m_r += static_cast<T>(qRed(px));
        this->m_g += static_cast<T>(qGreen(px));
        this->m_b += static_cast<T>(qBlue(px));

        return *this;
    }

    PixRGB<T>& operator-=(const QRgb& px)
    {
        this->m_r -= static_cast<T>(qRed(px));
        this->m_g -= static_cast<T>(qGreen(px));
        this->m_b -= static_cast<T>(qBlue(px));

        return *this;
    }

    PixRGB<T>& operator*=(const QRgb& px)
    {
        this->m_r *= static_cast<T>(qRed(px));
        this->m_g *= static_cast<T>(qGreen(px));
        this->m_b *= static_cast<T>(qBlue(px));

        return *this;
    }

    PixRGB<T>& operator/=(const QRgb& px)
    {
        this->m_r /= static_cast<T>(qRed(px));
        this->m_g /= static_cast<T>(qGreen(px));
        this->m_b /= static_cast<T>(qBlue(px));

        return *this;
    }

    bool operator ==(const PixRGB<T>& other) const
    {
        return this->m_r == other.m_r
            && this->m_g == other.m_g
            && this->m_b == other.m_b;
    }

    bool operator !=(const PixRGB<T>& other) const
    {
        return !(*this == other);
    }

    T pRed() const {return m_r;}
    T pGreen() const {return m_g;}
    T pBlue() const {return m_b;}

    void setRed(const T r) {m_r = r;}
    void setGreen(const T g) {m_g = g;}
    void setBlue(const T b) {m_b = b;}

    T luminance() const {return static_cast<T>((m_r + m_g + m_b) / 3);}
};

template<typename T> inline
PixRGB<qreal> operator*(const PixRGB<T>& lhs, qreal rhs)
{
    return PixRGB<qreal>(rhs * lhs.pRed(),
                         rhs * lhs.pGreen(),
                         rhs * lhs.pBlue());
}

template<typename T> inline
PixRGB<qreal> operator*(qreal lhs, const PixRGB<T>& rhs)
{
    return PixRGB<qreal>(lhs * rhs.pRed(),
                         lhs * rhs.pGreen(),
                         lhs * rhs.pBlue());
}

template<typename T> inline
PixRGB<T> integral_sum(const PixRGB<T>* other,
                       int line_width,
                       int x, int y, int kw, int kh)
{
    const PixRGB<T> *p0 = other + x + y * line_width;
    const PixRGB<T> *p1 = p0 + kw;
    const PixRGB<T> *p2 = p0 + kh * line_width;
    const PixRGB<T> *p3 = p2 + kw;

    return (*p0) + (*p3) - (*p1) - (*p2);
}

template<typename T>
PixRGB<T> pow(const QRgb& other, quint32 n)
{
    auto r = qRed(other);
    auto g = qGreen(other);
    auto b = qBlue(other);

    return PixRGB<T>(static_cast<T>(std::pow(r, n)),
                     static_cast<T>(std::pow(g, n)),
                     static_cast<T>(std::pow(b, n)));
}

template<typename T>
PixRGB<T> pow(const PixRGB<T>& other, quint32 n)
{
    auto r = other.pRed();
    auto g = other.pGreen();
    auto b = other.pBlue();

    return PixRGB<T>(std::pow(r, n),
                     std::pow(g, n),
                     std::pow(b, n));
}

template<typename T>
PixRGB<T> sqrt(const PixRGB<T>& other)
{
    return PixRGB<T>(std::sqrt(other.pRed()),
                     std::sqrt(other.pGreen()),
                     std::sqrt(other.pBlue()));
}

template<typename T>
PixRGB<T> bound(T min, const PixRGB<T>& other, T max)
{
    return PixRGB<T>(qBound(min, other.pRed(), max),
                        qBound(min, other.pGreen(), max),
                        qBound(min, other.pBlue(), max));
}

template<typename T, typename Y>
PixRGB<T> mult(Y n, const PixRGB<T>& other)
{
    return PixRGB<T>(n * other.pRed(),
                     n * other.pGreen(),
                     n * other.pBlue());
}

template<typename T>
PixRGB<T> exp(const PixRGB<T>& other)
{
    return PixRGB<T>(std::exp(other.pRed()),
                     std::exp(other.pGreen()),
                     std::exp(other.pBlue()));
}

} //namespace dip
#endif // RGBPIXEL_H
