// NAP  12/13/2004  \Noel120\Include\RGBFloat.h
// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "Allocate.h"
#include "Macros.h"
#ifndef _ALGORITHM_
#include <algorithm>
#endif
#ifndef _IOSTREAM_
#include <iostream>
#endif

class RGBHalf;
class RGBByte;
class ColorBuf;
class ColorProperty;

// RGBFloat always initialised with 0,0,0
// RGBAFloat always initialised with 0,0,0,1

//******************************************************************************
//** RGBFloat
//******************************************************************************
//size 12
class RGBFloat final {
public:
    float m_blue{0.F};
    float m_green{0.F};
    float m_red{0.F};

    RGBFloat() noexcept = default;

    constexpr RGBFloat(const float red, const float green, const float blue) noexcept : m_blue(blue), m_green(green), m_red(red) {}
    constexpr RGBFloat(const float value) noexcept : m_blue(value), m_green(value), m_red(value) {}
    explicit RGBFloat(const double scale) noexcept : m_blue((float)scale), m_green((float)scale), m_red((float)scale) {}
    explicit RGBFloat(const COLORREF c) noexcept {
        m_red = GetRValue(c);
        m_green = GetGValue(c);
        m_blue = GetBValue(c);
    }

    ~RGBFloat() = default;
    RGBFloat(const RGBFloat &) noexcept = default;
    RGBFloat &operator=(const RGBFloat &) noexcept = default;
    RGBFloat(RGBFloat &&) noexcept = default;
    RGBFloat &operator=(RGBFloat &&) noexcept = default;

    HASH_INLINE explicit RGBFloat(const RGBHalf &other) noexcept;
    HASH_INLINE explicit RGBFloat(const ColorBuf &other) noexcept;
    HASH_INLINE explicit RGBFloat(const RGBByte &other);

#ifdef _MEMDEBUG
    void *operator new(const size_t size, char *file, const int line) noexcept {
        return ALLOCBITMAP(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocBitmap(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeBitmap(ptr);
    }

    RGBFloat &operator=(const float scale) noexcept {
        m_red = m_green = m_blue = scale;
        return *this;
    }

    RGBFloat &operator=(const ColorBuf &other) noexcept;
    RGBFloat &operator=(const RGBHalf &other) noexcept;
    RGBFloat &operator=(const ColorProperty &other) noexcept;

    RGBFloat &operator +=(const RGBFloat &other) noexcept {
        m_red += other.m_red;
        m_green += other.m_green;
        m_blue += other.m_blue;
        return *this;
    }

    RGBFloat &operator +=(const RGBHalf &other) noexcept;
    RGBFloat &operator *=(const RGBHalf &other) noexcept;
    RGBFloat &operator +=(const RGBByte &other);

    RGBFloat &operator +=(const float value) noexcept {
        m_red += value;
        m_green += value;
        m_blue += value;
        return *this;
    }

    RGBFloat &operator -=(const RGBFloat &other) noexcept {
        m_red -= other.m_red;
        m_green -= other.m_green;
        m_blue -= other.m_blue;
        return *this;
    }

    RGBFloat &operator *=(const RGBFloat &other) noexcept {
        m_red *= other.m_red;
        m_green *= other.m_green;
        m_blue *= other.m_blue;
        return *this;
    }

    RGBFloat &operator *=(const float scale) noexcept {
        m_red *= scale;
        m_green *= scale;
        m_blue *= scale;
        return *this;
    }

    RGBFloat &operator /=(const RGBFloat &other) noexcept {
        ASSERT(other.m_red != 0.F);
        ASSERT(other.m_green != 0.F);
        ASSERT(other.m_blue != 0.F);
        m_red /= other.m_red;
        m_green /= other.m_green;
        m_blue /= other.m_blue;
        return *this;
    }

    RGBFloat &operator /=(const float scale) noexcept {
        return scale != 0.F ? *this *= hash_math::rcp(scale) : *this;
    }

    // Some new operators for Subsurface Scattering calculations.
    //   RGBFloat & operator += ( const float scale ) { m_red += scale; m_green += scale; m_blue += scale; return *this; }
    RGBFloat &Negate() noexcept {
        m_red = -m_red;
        m_green = -m_green;
        m_blue = -m_blue;
        return *this;
    }

    RGBFloat &Reciprocal() noexcept {
        m_red = hash_math::rcp(m_red);
        m_green = hash_math::rcp(m_green);
        m_blue = hash_math::rcp(m_blue);
        return *this;
    }

    RGBFloat &Square() noexcept {
        m_red *= m_red;
        m_green *= m_green;
        m_blue *= m_blue;
        return *this;
    }

    RGBFloat &Sqrt() noexcept {
        m_red = hash_math::sqrt(m_red);
        m_green = hash_math::sqrt(m_green);
        m_blue = hash_math::sqrt(m_blue);
        return *this;
    }

    RGBFloat &Exp() noexcept {
        m_red = hash_math::exp(m_red);
        m_green = hash_math::exp(m_green);
        m_blue = hash_math::exp(m_blue);
        return *this;
    }

    [[nodiscard]] float Red() const noexcept {
        return m_red;
    }

    [[nodiscard]] float Green() const noexcept {
        return m_green;
    }

    [[nodiscard]] float Blue() const noexcept {
        return m_blue;
    }

    void SetRed(const float red) noexcept {
        m_red = red;
    }

    void SetGreen(const float green) noexcept {
        m_green = green;
    }

    void SetBlue(const float blue) noexcept {
        m_blue = blue;
    }

    void Set(const float red, const float green, const float blue) noexcept {
        m_red = red;
        m_green = green;
        m_blue = blue;
    }

    void Set(const float init) noexcept {
        m_red = m_green = m_blue = init;
    }

    void SetZero() noexcept {
        m_red = m_green = m_blue = 0.F;
    }

    /*
        bool operator==(const RGBFloat &a) const noexcept {
            return (m_red == a.m_red) && (m_green == a.m_green) && (m_blue == a.m_blue);
        }
    
        bool operator!=(const RGBFloat &a) const noexcept {
            return !(*this == a);
        }
    */
    RGBFloat operator +(const RGBFloat &other) const noexcept {
        return RGBFloat(*this) += other;
    }

    RGBFloat operator -(const RGBFloat &other) const noexcept {
        return RGBFloat(*this) -= other;
    }

    RGBFloat operator *(const RGBFloat &other) const noexcept {
        return RGBFloat(*this) *= other;
    }

    RGBFloat operator *(const float scale) const noexcept {
        return RGBFloat(*this) *= scale;
    }

    RGBFloat operator /(const float scale) const noexcept {
        return RGBFloat(*this) /= scale;
    }

    RGBFloat operator /(const RGBFloat &other) const noexcept {
        return RGBFloat(*this) /= other;
    }

    float operator[](const int i) const noexcept {
        ASSERT(i < 3);
        return (&m_blue)[i];
    }

    [[nodiscard]] COLORREF GetCOLORREF() const noexcept {
        return RGB(fast_round(MAX<float>(0.F, MIN<float>(255.F, m_red))), fast_round(MAX<float>(0.F, MIN<float>(255.F, m_green))), fast_round(MAX<float>(0.F, MIN<float>(255.F, m_blue))));
    }

    [[nodiscard]] float GetLuminance() const noexcept {
        if (IsZero())
            return 0.F;
        return 0.299F * m_red + 0.587F * m_green + 0.114F * m_blue;
    }

    friend RGBFloat operator *(const float scale, const RGBFloat &other) noexcept {
        return other * scale;
    }

    void MinMax(const float minvalue, const float maxvalue) {
        m_red = std::clamp(m_red, minvalue, maxvalue);
        m_green = std::clamp(m_green, minvalue, maxvalue);
        m_blue = std::clamp(m_blue, minvalue, maxvalue);
    }

    [[nodiscard]] RGBFloat GammaCorrect(const float power) const noexcept {
        if (power == 1.F)
            return *this;
        const float rcp_power = hash_math::rcp(power);
        return RGBFloat(hash_math::pow(m_red, rcp_power), hash_math::pow(m_green, rcp_power), hash_math::pow(m_blue, rcp_power));
    }

    void Clamp(const float value = 1.F) noexcept {
        if (m_red > value)
            m_red = value;
        if (m_green > value)
            m_green = value;
        if (m_blue > value)
            m_blue = value;
    }

    void ClampBounds(const float minvalue = 0.F, const float maxvalue = 1.F) {
        m_red = std::clamp(m_red, minvalue, maxvalue);
        m_green = std::clamp(m_green, minvalue, maxvalue);
        m_blue = std::clamp(m_blue, minvalue, maxvalue);
    }

    /*
       bool CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
          if ( m_red < lobound || m_red > hibound )
             return true;
          if ( m_green < lobound || m_green > hibound )
             return true;
          if ( m_blue < lobound || m_blue > hibound )
             return true;
          return false;
       };
    */
    [[nodiscard]] bool IsAnyGreater(const float mincolor) const noexcept {
        if (m_red > mincolor)
            return true;
        if (m_green > mincolor)
            return true;
        if (m_blue > mincolor)
            return true;
        return false;
    }

    [[nodiscard]] bool IsZero() const noexcept {
        if (hash_math::abs(m_red) > FLT_EPSILON)
            return false;
        if (hash_math::abs(m_green) > FLT_EPSILON)
            return false;
        if (hash_math::abs(m_blue) > FLT_EPSILON)
            return false;
        return true;
    }

    [[nodiscard]] bool CheckIsValid() const noexcept {
        ASSERT(IsFinite(m_red));
        ASSERT(IsFinite(m_green));
        ASSERT(IsFinite(m_blue));
        if (!IsFinite(m_red))
            return false;
        if (!IsFinite(m_green))
            return false;
        if (!IsFinite(m_blue))
            return false;
        return true;
    }

    friend bool operator==(const RGBFloat &lhs, const RGBFloat &rhs) noexcept {
        return floatEQ(lhs.m_red, rhs.m_red) && floatEQ(lhs.m_green, rhs.m_green) && floatEQ(lhs.m_blue, rhs.m_blue);
    }

    friend bool operator!=(const RGBFloat &lhs, const RGBFloat &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const RGBFloat &val) {
        os << val.m_blue << " " << val.m_green << " " << val.m_red;
        return os;
    }
};

HASH_INLINE RGBFloat GetSpectrumColor(const float x) noexcept {
    const float theta = (1.66F * hash_constants::pi) * x;
    return RGBFloat((2.F + hash_math::cos(theta)) / 3.F, (1.F + hash_math::cos(theta - (2.F * hash_constants::pi / 3.F))) / 2.F, (2.F + hash_math::cos(theta - (4.F * hash_constants::pi / 3.F))) / 3.F);
}

//*****************************************************************************
//** RGBAFloat
//*****************************************************************************
class RGBAHalf;
class RGBAByte;

class RGBAFloat final {
public:
    RGBFloat m_color;
    float m_alpha{1.F};

    RGBAFloat() noexcept = default;
    constexpr RGBAFloat(const float red, const float green, const float blue, const float alpha) noexcept : m_color(red, green, blue), m_alpha(alpha) {}
    constexpr RGBAFloat(const float scale) noexcept : m_color(scale), m_alpha(scale) {}
    explicit RGBAFloat(const double scale) noexcept : m_color(scale), m_alpha((float)scale) {}
    explicit RGBAFloat(const COLORREF c) noexcept : m_color(c) {}

    ~RGBAFloat() = default;
    RGBAFloat(const RGBAFloat &) = default;
    RGBAFloat &operator=(const RGBAFloat &) noexcept = default;
    RGBAFloat(RGBAFloat &&) = default;
    RGBAFloat &operator=(RGBAFloat &&) = default;

    RGBAFloat(const RGBAHalf &other) noexcept;
    RGBAFloat(const RGBAByte &other) noexcept;
    RGBAFloat(const ColorBuf &other) noexcept;
    RGBAFloat(const RGBHalf &other) noexcept;

#ifdef _MEMDEBUG
    void *operator new(const size_t size, char *file, const int line) noexcept {
        return ALLOCBITMAP(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocBitmap(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeBitmap(ptr);
    }

    RGBAFloat &operator +=(const RGBAFloat &other) noexcept {
        m_color += other.Color();
        m_alpha += other.m_alpha;
        return *this;
    }

    RGBAFloat &operator -=(const RGBAFloat &other) noexcept {
        m_color -= other.Color();
        m_alpha -= other.m_alpha;
        return *this;
    }

    RGBAFloat &operator *=(const RGBAFloat &other) noexcept {
        m_color *= other.Color();
        m_alpha *= other.m_alpha;
        return *this;
    }

    RGBAFloat &operator *=(const float scale) noexcept {
        m_color *= scale;
        m_alpha *= scale;
        return *this;
    }

    RGBAFloat &operator /=(const RGBAFloat &other) noexcept {
        m_color /= other.Color();
        m_alpha /= other.m_alpha;
        return *this;
    }

    RGBAFloat &operator /=(const float scale) noexcept {
        return scale ? *this *= hash_math::rcp(scale) : *this;
    }

    // Some new operators for Subsurface Scattering calculations.
    RGBAFloat &operator=(const float scale) noexcept {
        m_color = scale;
        m_alpha = scale;
        return *this;
    }

    //   RGBAFloat & operator += ( const float scale ) { m_color += scale; m_alpha += scale; return *this; }
    RGBAFloat &Negate() noexcept {
        m_color.Negate();
        m_alpha = -m_alpha;
        return *this;
    }

    RGBAFloat &Reciprocal() noexcept {
        m_color.Reciprocal();
        m_alpha = hash_math::rcp(m_alpha);
        return *this;
    }

    RGBAFloat &Square() noexcept {
        m_color.Square();
        m_alpha *= m_alpha;
        return *this;
    }

    RGBAFloat &Sqrt() noexcept {
        m_color.Sqrt();
        m_alpha = hash_math::sqrt(m_alpha);
        return *this;
    }

    RGBAFloat &Exp() noexcept {
        m_color.Exp();
        m_alpha = hash_math::exp(m_alpha);
        return *this;
    }

    [[nodiscard]] RGBFloat Color() const noexcept {
        return m_color;
    }

    [[nodiscard]] float Red() const noexcept {
        return m_color.Red();
    }

    [[nodiscard]] float Green() const noexcept {
        return m_color.Green();
    }

    [[nodiscard]] float Blue() const noexcept {
        return m_color.Blue();
    }

    [[nodiscard]] float Alpha() const noexcept {
        return m_alpha;
    }

    void SetRed(const float red) noexcept {
        m_color.SetRed(red);
    }

    void SetGreen(const float green) noexcept {
        m_color.SetGreen(green);
    }

    void SetBlue(const float blue) noexcept {
        m_color.SetBlue(blue);
    }

    void SetAlpha(const float alpha) noexcept {
        m_alpha = alpha;
    }

    void SetColor(const RGBHalf &other) noexcept;

    void Set(const float red, const float green, const float blue, const float alpha) noexcept {
        m_color.Set(red, green, blue);
        m_alpha = alpha;
    }

    void Set(const float init) noexcept {
        m_color.Set(init);
        m_alpha = init;
    }

    //void SetZero() {
    //    m_color.SetZero();
    //    m_alpha = 1.F;
    //}

    void SetNoAlpha(const RGBFloat &color) noexcept {
        m_color = color;
    }

    /*
        bool operator==(const RGBAFloat &a) const noexcept {
            return (m_color == a.Color()) && (m_alpha == a.Alpha());
        }
    
        bool operator!=(const RGBAFloat &a) const noexcept {
            return !(*this == a);
        }
    */
    RGBAFloat operator +(const RGBAFloat &other) const noexcept {
        return RGBAFloat(*this) += other;
    }

    RGBAFloat operator -(const RGBAFloat &other) const noexcept {
        return RGBAFloat(*this) -= other;
    }

    RGBAFloat operator *(const RGBAFloat &other) const noexcept {
        return RGBAFloat(*this) *= other;
    }

    RGBAFloat operator *(const float scale) const noexcept {
        return RGBAFloat(*this) *= scale;
    }

    RGBAFloat operator /(const float scale) const noexcept {
        return RGBAFloat(*this) /= scale;
    }

    RGBAFloat operator /(const RGBAFloat &other) const noexcept {
        return RGBAFloat(*this) /= other;
    }

    float operator[](const int i) const noexcept {
        ASSERT(i < 4);
        return (&m_color.m_blue)[i];
    }

    friend RGBAFloat operator *(const float scale, const RGBAFloat &other) noexcept {
        return other * scale;
    }

    void Clamp(const float value = 1.F) noexcept {
        if (m_alpha > value)
            m_alpha = value;
        m_color.Clamp();
    }

    friend bool operator==(const RGBAFloat &lhs, const RGBAFloat &rhs) noexcept {
        return lhs.m_color == rhs.m_color && floatEQ(lhs.m_alpha, rhs.m_alpha);
    }

    friend bool operator!=(const RGBAFloat &lhs, const RGBAFloat &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const RGBAFloat &val) {
        os << val.m_color << " " << val.m_alpha;
        return os;
    }

    /*
       bool CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
          return m_color.CheckOffBound( lobound, hibound );
       };
       */
};

//*****************************************************************************
//** YAFloat
//*****************************************************************************
class YAHalf;
class YAByte;

class YAFloat final {
public:
    float m_luminance{0.F};
    float m_alpha{1.F};

    YAFloat() noexcept = default;
    YAFloat(const float luminance) noexcept : m_luminance(luminance) {}

    YAFloat(const float luminance, const float alpha) noexcept : m_luminance(luminance), m_alpha(alpha) {}

    YAFloat(const YAFloat &other) noexcept {
        *this = other;
    }

    YAFloat(const YAHalf &other) noexcept;
    YAFloat(const YAByte &other) noexcept;

    // Compute the CIE Rec.709 luminance
    YAFloat(const RGBAFloat &other) noexcept {
        m_luminance = other.Red() * 0.2125F + other.Green() * 0.7154F + other.Blue() * 0.0721F;
        m_alpha = other.Alpha();
    }

    YAFloat(const RGBAHalf &other) noexcept;
    YAFloat(const RGBAByte &other) noexcept;
    YAFloat(const ColorBuf &other) noexcept;
    YAFloat(const RGBHalf &other) noexcept;
    YAFloat(const RGBByte &other) noexcept;

#ifdef _MEMDEBUG
    void *operator new(const size_t size, char *file, const int line) noexcept {
        return ALLOCBITMAP(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocBitmap(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeBitmap(ptr);
    }

    YAFloat &operator=(const YAFloat &other) noexcept = default;

    ~YAFloat() = default;
    YAFloat(YAFloat &&) = default;
    YAFloat &operator=(YAFloat &&) = delete;

    YAFloat &operator +=(const YAFloat &other) noexcept {
        m_luminance += other.m_luminance;
        m_alpha += other.m_alpha;
        return *this;
    }

    YAFloat &operator -=(const YAFloat &other) noexcept {
        m_luminance -= other.m_luminance;
        m_alpha -= other.m_alpha;
        return *this;
    }

    YAFloat &operator *=(const YAFloat &other) noexcept {
        m_luminance *= other.m_luminance;
        m_alpha *= other.m_alpha;
        return *this;
    }

    YAFloat &operator *=(const float scale) noexcept {
        m_luminance *= scale;
        m_alpha *= scale;
        return *this;
    }

    YAFloat &operator /=(const YAFloat &other) noexcept {
        m_luminance /= other.m_luminance;
        m_alpha /= other.m_alpha;
        return *this;
    }

    YAFloat &operator /=(const float scale) noexcept {
        return scale ? *this *= hash_math::rcp(scale) : *this;
    }

    [[nodiscard]] float Luminance() const noexcept {
        return m_luminance;
    }

    [[nodiscard]] float Alpha() const noexcept {
        return m_alpha;
    }

    void SetLuminance(const float luminance) noexcept {
        m_luminance = luminance;
    }

    void SetAlpha(const float alpha) noexcept {
        m_alpha = alpha;
    }

    void Set(const float luminance, const float alpha) noexcept {
        m_luminance = luminance;
        m_alpha = alpha;
    }

    void Set(const float luminance) noexcept {
        m_luminance = luminance;
        m_alpha = 1.F;
    }

    // Compute the CIE Rec.709 luminance
    void Set(const float red, const float green, const float blue, const float alpha = 1.F) noexcept {
        m_luminance = red * 0.2125F + green * 0.7154F + blue * 0.0721F;
        m_alpha = alpha;
    }

    void SetNoAlpha(const float luminance) noexcept {
        m_luminance = luminance;
    }

    /*
        bool operator==(const YAFloat &a) const noexcept {
            return (m_luminance == a.m_luminance) && (m_alpha == a.m_alpha);
        }
    
        bool operator!=(const YAFloat &a) const noexcept {
            return !(*this == a);
        }
    */
    YAFloat operator +(const YAFloat &other) const noexcept {
        return YAFloat(*this) += other;
    }

    YAFloat operator -(const YAFloat &other) const noexcept {
        return YAFloat(*this) -= other;
    }

    YAFloat operator *(const YAFloat &other) const noexcept {
        return YAFloat(*this) *= other;
    }

    YAFloat operator *(const float scale) const noexcept {
        return YAFloat(*this) *= scale;
    }

    YAFloat operator /(const float scale) const noexcept {
        return YAFloat(*this) /= scale;
    }

    YAFloat operator /(const YAFloat &other) const noexcept {
        return YAFloat(*this) /= other;
    }

    float operator[](const int i) const noexcept {
        ASSERT(i < 2);
        return (&m_luminance)[i];
    }

    friend YAFloat operator *(const float scale, const YAFloat &other) noexcept {
        return other * scale;
    }

    friend bool operator==(const YAFloat &lhs, const YAFloat &rhs) noexcept {
        return floatEQ(lhs.m_luminance, rhs.m_luminance) && floatEQ(lhs.m_alpha, rhs.m_alpha);
    }

    friend bool operator!=(const YAFloat &lhs, const YAFloat &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const YAFloat &val) {
        os << val.m_luminance << " " << val.m_alpha;
        return os;
    }

    /*
       bool CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
          if ( m_luminance < lobound || m_luminance > hibound )
             return true;
          return false;
       };
       */
};
