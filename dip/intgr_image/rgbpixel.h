#ifndef RGBPIXEL_H
#define RGBPIXEL_H
#include <QtGlobal>
#include <QColor>

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

    PixRGB(const PixRGB<T>& pix)
    {
        if(this != &pix)
        {
            this->m_r = pix.m_r;
            this->m_g = pix.m_g;
            this->m_b = pix.m_b;
        }
    }

    PixRGB<T> operator+(const PixRGB<T>& other)
    {
        return static_cast<PixRGB<T>>(this->m_r + other.m_r,
                                      this->m_g + other.m_g,
                                      this->m_b + other.m_b);
    }

    PixRGB<T> operator-(const PixRGB<T>& other)
    {
        return static_cast<PixRGB<T>>(this->m_r - other.m_r,
                                      this->m_g - other.m_g,
                                      this->m_b - other.m_b);
    }

    PixRGB<T> operator*(const PixRGB<T>& other)
    {
        return static_cast<PixRGB<T>>(static_cast<T>(this->m_r * other.m_r),
                                      static_cast<T>(this->m_g * other.m_g),
                                      static_cast<T>(this->m_b * other.m_b));
    }

    PixRGB<T> operator/(const PixRGB<T>& other)
    {
        return static_cast<PixRGB<T>>(static_cast<T>(this->m_r / other.m_r),
                                      static_cast<T>(this->m_g / other.m_g),
                                      static_cast<T>(this->m_b / other.m_b));
    }

    PixRGB<T>& operator+=(const PixRGB<T>& other)
    {
        this += other;
        return *this;
    }

    PixRGB<T>& operator-=(const PixRGB<T>& other)
    {
        this -= other;
        return *this;
    }

    PixRGB<T>& operator*=(const PixRGB<T>& other)
    {
        this *= other;
        return *this;
    }

    PixRGB<T>& operator/=(const PixRGB<T>& other)
    {
        this /= other;
        return *this;
    }

    PixRGB<T> operator+(const QRgb& px)
    {
        return static_cast<PixRGB<T>>(this->m_r + static_cast<T>(qRed(px)),
                                      this->m_g + static_cast<T>(qGreen(px)),
                                      this->m_b + static_cast<T>(qBlue(px)));
    }

    PixRGB<T> operator-(const QRgb& px)
    {
        return static_cast<PixRGB<T>>(this->m_r - static_cast<T>(qRed(px)),
                                      this->m_g - static_cast<T>(qGreen(px)),
                                      this->m_b - static_cast<T>(qBlue(px)));
    }

    PixRGB<T> operator*(const QRgb& px)
    {
        return static_cast<PixRGB<T>>(this->m_r + static_cast<T>(qRed(px)),
                                      this->m_g + static_cast<T>(qGreen(px)),
                                      this->m_b + static_cast<T>(qBlue(px)));
    }

    PixRGB<T> operator/(const QRgb& px)
    {
        return static_cast<PixRGB<T>>(this->m_r + static_cast<T>(qRed(px)),
                                      this->m_g + static_cast<T>(qGreen(px)),
                                      this->m_b + static_cast<T>(qBlue(px)));
    }

    PixRGB<T>& operator+=(const QRgb& px)
    {
        this += px;
        return *this;
    }

    PixRGB<T>& operator-=(const QRgb& px)
    {
        this -= px;
        return *this;
    }

    PixRGB<T>& operator*=(const QRgb& px)
    {
        this *= px;
        return *this;
    }

    PixRGB<T>& operator/=(const QRgb& px)
    {
        this /= px;
        return *this;
    }

    bool operator ==(const PixRGB& other) const
    {
        return this->m_r == other.m_r
            && this->m_g == other.m_g
            && this->m_b == other.m_b;
    }

    bool operator !=(const PixRGB& other) const
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

} //namespace dip
#endif // RGBPIXEL_H
