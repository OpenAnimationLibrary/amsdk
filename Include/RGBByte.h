// NAP  12/20/2004  \Noel120\Include\RGBByte.h
// ReSharper disable CppFunctionIsNotImplemented
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "Allocate.h"
#include "DataType.h"
#include "Macros.h"
#ifndef _IOSTREAM_
#include <iostream>
#endif

class RGBAFloat;
class RGBFloat;
#ifndef MAXCOLOR
#define MAXCOLOR 255
#endif
template<typename T>
constexpr auto FLOATTOBYTE(T flt) { return (UBYTE)MAX(0, MIN(MAXCOLOR, fast_round(flt * MAXCOLOR))); }

//******************************************************************************
//** RGBByte
//******************************************************************************
class RGBByte final {
public:
    UBYTE m_blue{0};
    UBYTE m_green{0};
    UBYTE m_red{0};

    RGBByte() noexcept = default;
    RGBByte(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue) noexcept: m_blue(pblue), m_green(pgreen), m_red(pred) {}

    RGBByte(const COLORREF c) noexcept {
        m_blue = GetBValue(c);
        m_green = GetGValue(c);
        m_red = GetRValue(c);
    }

    RGBByte(const RGBFloat &color);

    ~RGBByte() = default;
    RGBByte(const RGBByte &) = default;
    RGBByte &operator=(const RGBByte &) noexcept = default;
    RGBByte(RGBByte &&) = default;
    RGBByte &operator=(RGBByte &&) = default;

#ifdef _MEMDEBUG
    void             *operator new(const size_t size, char *file, const int line) {
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

    RGBByte &operator +=(const RGBByte &) noexcept;
    RGBByte &operator -=(const RGBByte &) noexcept;
    HASH_INLINE RGBByte &operator *=(float) noexcept;
    RGBByte operator +(const RGBByte &other) noexcept;

    // ReSharper disable once CppNonExplicitConversionOperator
    constexpr operator COLORREF() const noexcept {
        return RGB(m_red, m_green, m_blue);
    }

    RGBByte &operator /=(const float scale) noexcept {
        return *this *= hash_math::rcp(scale);
    }

    [[nodiscard]] RGBFloat GetFactoredRGBFloat() const;
    [[nodiscard]] RGBFloat GetNormalizedRGBFloat() const;

    [[nodiscard]] UBYTE Red() const noexcept {
        return m_red;
    }

    [[nodiscard]] UBYTE Green() const noexcept {
        return m_green;
    }

    [[nodiscard]] UBYTE Blue() const noexcept {
        return m_blue;
    }

    void Set(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue) noexcept {
        m_red = pred;
        m_green = pgreen;
        m_blue = pblue;
    }

    void Set(const UBYTE value) noexcept {
        m_red = m_green = m_blue = value;
    }

    void SetRed(const UBYTE red) noexcept {
        m_red = red;
    }

    void SetGreen(const UBYTE green) noexcept {
        m_green = green;
    }

    void SetBlue(const UBYTE blue) noexcept {
        m_blue = blue;
    }

    [[nodiscard]] RGBByte GammaCorrect(float power) const noexcept;

    [[nodiscard]] RGBFloat Get() const;
    void Set(const RGBFloat &);

    [[nodiscard]] float GetLuminance() const noexcept {
        return 0.299F * m_red + 0.587F * m_green + 0.114F * m_blue;
    }

    constexpr friend bool operator==(const RGBByte &lhs, const RGBByte &rhs) noexcept {
        return lhs.m_red == rhs.m_red && lhs.m_green == rhs.m_green && lhs.m_blue == rhs.m_blue;
    }

    constexpr friend bool operator!=(const RGBByte &lhs, const RGBByte &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const RGBByte &val) {
        os << val.m_blue << " " << val.m_green << " " << val.m_red;
        return os;
    }

    //   bool CheckOffBound( float lobound, float hibound ) { return false; }; // YP : For HDR testing and debugging purpose
};

HASH_INLINE RGBByte &RGBByte::operator +=(const RGBByte &other) noexcept {
    if (int tempred; (tempred = m_red + other.m_red) > MAXCOLOR)
        m_red = MAXCOLOR;
    else
        m_red = (UBYTE)tempred;
    if (int tempgreen; (tempgreen = m_green + other.m_green) > MAXCOLOR)
        m_green = MAXCOLOR;
    else
        m_green = (UBYTE)tempgreen;
    if (int tempblue; (tempblue = m_blue + other.m_blue) > MAXCOLOR)
        m_blue = MAXCOLOR;
    else
        m_blue = (UBYTE)tempblue;
    return *this;
}

HASH_INLINE RGBByte RGBByte::operator +(const RGBByte &other) noexcept {
    m_red += other.m_red;
    m_green += other.m_green;
    m_blue += other.m_blue;
    return *this;
}

HASH_INLINE RGBByte &RGBByte::operator -=(const RGBByte &other) noexcept{
    m_red -= other.m_red;
    m_green -= other.m_green;
    m_blue -= other.m_blue;
    return *this;
}

HASH_INLINE RGBByte &RGBByte::operator *=(const float factor) noexcept {
    m_red = (UBYTE)lround(m_red * factor);//(m_red * factor + .5F);
    m_green = (UBYTE)lround(m_green * factor);//(m_green * factor + .5F);
    m_blue = (UBYTE)lround(m_blue * factor);//(m_blue * factor + .5F);
    return *this;
}

HASH_INLINE void GammaCorrect(UBYTE *color, const float power) noexcept {
    if (power == 1.F)
        return;
    *color = (UBYTE)fast_round(MIN<float>(255.F, MAXCOLOR * hash_math::pow((float)*color / MAXCOLOR, hash_math::rcp(power))));
}

HASH_INLINE RGBByte RGBByte::GammaCorrect(const float power) const noexcept {
    if (power == 1.F)
        return *this;
    return RGBByte(
        (UBYTE)fast_round(MIN(255.F, MAXCOLOR * hash_math::pow((float)m_red / MAXCOLOR, hash_math::rcp(power)))),
        (UBYTE)fast_round(MIN(255.F, MAXCOLOR * hash_math::pow((float)m_green / MAXCOLOR, hash_math::rcp(power)))),
        (UBYTE)fast_round(MIN(255.F, MAXCOLOR * hash_math::pow((float)m_blue / MAXCOLOR, hash_math::rcp(power)))));
}

//******************************************************************************
//** RGBAByte
//******************************************************************************
class RGBAByte final {
public:
    RGBByte m_color;
    UBYTE m_alpha{MAXCOLOR};

    RGBAByte() noexcept = default;
    RGBAByte(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue) noexcept : m_color(pred, pgreen, pblue) {}
    RGBAByte(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue, const UBYTE palpha) noexcept : m_color(pred, pgreen, pblue), m_alpha(palpha) {}
    RGBAByte(const COLORREF c) noexcept : m_color(c) {}
    RGBAByte(const RGBAFloat &color);

    ~RGBAByte() = default;
    RGBAByte(const RGBAByte &) = default;
    RGBAByte &operator=(const RGBAByte &) noexcept = default;
    RGBAByte(RGBAByte &&) = default;
    RGBAByte &operator=(RGBAByte &&) = default;

#ifdef _MEMDEBUG
    void             *operator new(const size_t size, char *file, const int line) {
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

    RGBAByte &operator +=(const RGBAByte &) noexcept;
    RGBAByte &operator -=(const RGBAByte &) noexcept;
    HASH_INLINE RGBAByte &operator *=(float) noexcept;
    RGBAByte operator +(const RGBAByte &other) noexcept;

    // ReSharper disable once CppNonExplicitConversionOperator
    constexpr operator COLORREF() const noexcept {
        return RGB(m_color.m_red, m_color.m_green, m_color.m_blue);
    }

    RGBAByte &operator /=(const float scale) noexcept {
        return *this *= hash_math::rcp(scale);
    }

    [[nodiscard]] RGBFloat GetFactoredRGBFloat() const;
    [[nodiscard]] RGBFloat GetNormalizedRGBFloat() const;
    [[nodiscard]] RGBAFloat GetFactoredRGBAFloat() const;
    [[nodiscard]] RGBAFloat GetNormalizedRGBAFloat() const;

    [[nodiscard]] UBYTE Red() const noexcept {
        return m_color.m_red;
    }

    [[nodiscard]] UBYTE Green() const noexcept {
        return m_color.m_green;
    }

    [[nodiscard]] UBYTE Blue() const noexcept {
        return m_color.m_blue;
    }

    [[nodiscard]] UBYTE Alpha() const noexcept {
        return m_alpha;
    }

    void Set(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue, const UBYTE alpha) noexcept {
        m_color.Set(pred, pgreen, pblue);
        m_alpha = alpha;
    }

    void SetRed(const UBYTE red) noexcept {
        m_color.SetRed(red);
    }

    void SetGreen(const UBYTE green) noexcept {
        m_color.SetGreen(green);
    }

    void SetBlue(const UBYTE blue) noexcept {
        m_color.SetBlue(blue);
    }

    void SetAlpha(const UBYTE alpha) noexcept {
        m_alpha = alpha;
    }

    [[nodiscard]] RGBAByte GammaCorrect(const float power) const noexcept {
        RGBAByte value;
        value.m_color = m_color.GammaCorrect(power);
        value.m_alpha = m_alpha;
        return value;
    }

    [[nodiscard]] HASH_INLINE RGBFloat GetRGBFloat() const noexcept;
    [[nodiscard]] HASH_INLINE RGBAFloat GetRGBAFloat() const noexcept;
    [[nodiscard]] float GetOpacity() const noexcept;
    HASH_INLINE void Set(const RGBFloat &) noexcept;
    HASH_INLINE void Set(const RGBAFloat &) noexcept;
    void SetOpacity(float opacity) noexcept;

    [[nodiscard]] float GetLuminance() const noexcept {
        return m_color.GetLuminance();
    }

    constexpr friend bool operator==(const RGBAByte &lhs, const RGBAByte &rhs) noexcept {
        return lhs.m_color == rhs.m_color && lhs.m_alpha == rhs.m_alpha;
    }

    constexpr friend bool operator!=(const RGBAByte &lhs, const RGBAByte &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const RGBAByte &val) {
        os << val.m_color << " " << val.m_alpha;
        return os;
    }

    //   bool CheckOffBound( float lobound, float hibound ) { return false; }; // YP : For HDR testing and debugging purpose
};

HASH_INLINE float RGBAByte::GetOpacity() const noexcept {
    return (float)m_alpha / MAXCOLOR;
}

HASH_INLINE void RGBAByte::SetOpacity(const float opacity) noexcept {
    m_alpha = FLOATTOBYTE(opacity);
}

HASH_INLINE RGBAByte &RGBAByte::operator +=(const RGBAByte &other) noexcept {
    m_color.operator+=(other.m_color);

    if (int tempalpha; (tempalpha = m_alpha + other.m_alpha) > MAXCOLOR)
        m_alpha = MAXCOLOR;
    else
        m_alpha = (UBYTE)tempalpha;
    return *this;
}

HASH_INLINE RGBAByte RGBAByte::operator +(const RGBAByte &other) noexcept {
    m_color += other.m_color;
    m_alpha += other.m_alpha;
    return RGBAByte(*this);
}

HASH_INLINE RGBAByte &RGBAByte::operator -=(const RGBAByte &other) noexcept {
    m_color -= other.m_color;
    m_alpha -= other.m_alpha;
    return *this;
}

HASH_INLINE RGBAByte &RGBAByte::operator *=(const float factor) noexcept {
    m_color *= factor;
    m_alpha = (UBYTE)lround(m_alpha * factor);//(m_alpha * factor + .5F);
    return *this;
}

//******************************************************************************
//** YAByte
//******************************************************************************
class YAFloat;

class YAByte final {
public:
    UBYTE m_luminance{0};
    UBYTE m_alpha{MAXCOLOR};

    YAByte() noexcept = default;
    YAByte(const UBYTE luminance) noexcept : m_luminance(luminance) {}
    YAByte(const UBYTE luminance, const UBYTE alpha) noexcept : m_luminance(luminance), m_alpha(alpha) {}

    ~YAByte() = default;
    YAByte(const YAByte &) = default;
    YAByte &operator=(const YAByte &) noexcept = default;
    YAByte(YAByte &&) = default;
    YAByte &operator=(YAByte &&) = default;

    YAByte(const float luminance) noexcept {
        m_luminance = (UBYTE)(luminance * 255.F);
        m_alpha = MAXCOLOR;
    }

    YAByte(const float luminance, const float alpha) noexcept {
        m_luminance = (UBYTE)(luminance * 255.F);
        m_alpha = (UBYTE)(alpha * 255.F);
    }

    // compute CIE Rec.709 luminance
    YAByte(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue) noexcept {
        m_luminance = (UBYTE)(pred * 0.2125F + pgreen * 0.7154F + pblue * 0.0721F);
        m_alpha = MAXCOLOR;
    }

    YAByte(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue, const UBYTE palpha) noexcept {
        m_luminance = (UBYTE)(pred * 0.2125F + pgreen * 0.7154F + pblue * 0.0721F);
        m_alpha = palpha;
    }

    YAByte(const YAFloat &color);

#ifdef _MEMDEBUG
    void             *operator new(const size_t size, char *file, const int line) {
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

    YAByte &operator +=(const YAByte &) noexcept;
    YAByte &operator -=(const YAByte &) noexcept;
    HASH_INLINE YAByte &operator *=(float) noexcept;
    YAByte operator +(const YAByte &other) noexcept;

    // ReSharper disable once CppNonExplicitConversionOperator
    constexpr operator UBYTE() const noexcept {
        return m_luminance;
    }

    YAByte &operator /=(const float scale) noexcept {
        return *this *= hash_math::rcp(scale);
    }

    [[nodiscard]] float GetFactoredFloat() const noexcept {
        return m_luminance;
    }

    [[nodiscard]] float GetNormalizedFloat() const noexcept {
        return (float)m_luminance / MAXCOLOR;
    }

    [[nodiscard]] YAFloat GetFactoredRGBAFloat() const;
    [[nodiscard]] YAFloat GetNormalizedRGBAFloat() const;

    [[nodiscard]] UBYTE Luminance() const noexcept {
        return m_luminance;
    }

    [[nodiscard]] UBYTE Alpha() const noexcept {
        return m_alpha;
    }

    void Set(const UBYTE luminance, const UBYTE alpha) noexcept {
        m_luminance = luminance;
        m_alpha = alpha;
    }

    void SetLuminance(const UBYTE luminance) noexcept {
        m_luminance = luminance;
    }

    void SetLuminance(const float luminance) noexcept {
        m_luminance = (UBYTE)(luminance * MAXCOLOR);
    }

    void SetAlpha(const UBYTE alpha) noexcept {
        m_alpha = alpha;
    }

    [[nodiscard]] YAByte GammaCorrect(const float power) const noexcept {
        if (power == 1.F)
            return *this;
        YAByte value;
        value.m_luminance = (UBYTE)fast_round(MIN(255.F, MAXCOLOR * hash_math::pow((float)m_luminance / MAXCOLOR, hash_math::rcp(power))));
        value.m_alpha = m_alpha;
        return value;
    }

    [[nodiscard]] float GetFloat() const noexcept {
        return (float)m_luminance / MAXCOLOR;
    }

    [[nodiscard]] YAFloat GetYAFloat() const;

    [[nodiscard]] float GetOpacity() const noexcept {
        return (float)m_alpha / MAXCOLOR;
    }

    void SetOpacity(const float value) noexcept {
        m_alpha = FLOATTOBYTE(value);
    }

    [[nodiscard]] float GetLuminance() const noexcept {
        return (float)m_luminance / MAXCOLOR;
    }

    constexpr friend bool operator==(const YAByte &lhs, const YAByte &rhs) noexcept {
        return lhs.m_luminance == rhs.m_luminance && lhs.m_alpha == rhs.m_alpha;
    }

    constexpr friend bool operator!=(const YAByte &lhs, const YAByte &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const YAByte &val) {
        os << val.m_luminance << " " << val.m_alpha;
        return os;
    }

    //   bool CheckOffBound( float lobound, float hibound ) { return false; }; // YP : For HDR testing and debugging purpose
};

HASH_INLINE YAByte &YAByte::operator +=(const YAByte &other) noexcept {
    int temp;
    if ((temp = m_luminance + other.m_luminance) > MAXCOLOR)
        m_luminance = MAXCOLOR;
    else
        m_luminance = (UBYTE)temp;
    if ((temp = m_alpha + other.m_alpha) > MAXCOLOR)
        m_alpha = MAXCOLOR;
    else
        m_alpha = (UBYTE)temp;
    return *this;
}

HASH_INLINE YAByte YAByte::operator +(const YAByte &other) noexcept {
    m_luminance += other.m_luminance;
    m_alpha += other.m_alpha;
    return YAByte(*this);
}

HASH_INLINE YAByte &YAByte::operator -=(const YAByte &other) noexcept {
    m_luminance -= other.m_luminance;
    m_alpha -= other.m_alpha;
    return *this;
}

HASH_INLINE YAByte &YAByte::operator *=(const float factor) noexcept {
    m_luminance = (UBYTE)lround(m_luminance * factor);//(m_luminance * factor + .5F);
    m_alpha = (UBYTE)lround(m_alpha * factor);//(m_alpha * factor + .5F);
    return *this;
}
