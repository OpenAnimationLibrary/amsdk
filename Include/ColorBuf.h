//Dan  7/22/2004  \DanLP115\Include\ColorBuf.h
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeMemberInit
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

#include "RGBFloat.h"

#ifndef MAXCOLOR
#define MAXCOLOR 255
#endif

class RGBFloat;
class RGBAFloat;

class ColorBuf final {
public:
    union {
        UINT color;
        struct {
            UBYTE red, green, blue, alpha;
        };

    };

    ColorBuf() noexcept : color(4278190080) {}//alpha = MAXCOLOR

    explicit ColorBuf(const unsigned int col) noexcept : color(col) {}
    explicit ColorBuf(const int col) noexcept : color(col) {
        alpha = MAXCOLOR;
    }

    ColorBuf(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue) noexcept {
        red = pred;
        green = pgreen;
        blue = pblue;
        alpha = MAXCOLOR;
    }

    ColorBuf(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue, const UBYTE palpha) noexcept {
        red = pred;
        green = pgreen;
        blue = pblue;
        alpha = palpha;
    }

    // ReSharper disable once CppNonExplicitConvertingConstructor
    ColorBuf(const COLORREF &c) noexcept {
        red = GetRValue(c);
        green = GetGValue(c);
        blue = GetBValue(c);
        alpha = MAXCOLOR;
    }

    explicit ColorBuf(const RGBAFloat &s_color) noexcept;

    ~ColorBuf() = default;

    ColorBuf &operator=(const ColorBuf &other) noexcept {
        if (this == &other)
            return *this;
        color = other.color;
        return *this;
    }

    ColorBuf(const ColorBuf &) = default;
    ColorBuf(ColorBuf &&) = default;
    ColorBuf &operator=(ColorBuf &&) = default;

    void operator +=(const ColorBuf &) noexcept;
    void operator -=(const ColorBuf &) noexcept ;
    void operator *=(float) noexcept ;
    ColorBuf operator +(const ColorBuf &other) const noexcept ;

    // ReSharper disable once CppNonExplicitConversionOperator
    constexpr operator COLORREF() const noexcept {
        return RGB(red, green, blue);
    }

    [[nodiscard]] RGBFloat GetFactoredRGBFloat() const noexcept;
    [[nodiscard]] RGBFloat GetNormalizedRGBFloat() const noexcept;
    [[nodiscard]] RGBAFloat GetNormalizedRGBAFloat() const noexcept;

    [[nodiscard]] UBYTE Red() const noexcept {
        return red;
    }

    [[nodiscard]] UBYTE Green() const noexcept {
        return green;
    }

    [[nodiscard]] UBYTE Blue() const noexcept {
        return blue;
    }

    [[nodiscard]] UBYTE Alpha() const noexcept {
        return alpha;
    }

    [[nodiscard]] UINT Color() const noexcept {
        return color;
    }

    void Set(const UBYTE pred, const UBYTE pgreen, const UBYTE pblue, const UBYTE palpha) noexcept {
        red = pred;
        green = pgreen;
        blue = pblue;
        alpha = palpha;
    }

    void SetRed(const UBYTE pred) noexcept {
        red = pred;
    }

    void SetGreen(const UBYTE pgreen) noexcept {
        green = pgreen;
    }

    void SetBlue(const UBYTE pblue) noexcept {
        blue = pblue;
    }

    void SetAlpha(const UBYTE palpha) noexcept {
        alpha = palpha;
    }

    void SetColor(const UINT pcolor) noexcept {
        color = pcolor;
        alpha = MAXCOLOR;
    }

    void GammaCorrect(float power) noexcept;

    [[nodiscard]] HASH_INLINE RGBFloat Get() const noexcept;
    [[nodiscard]] float GetOpacity() const noexcept;
    void Set(RGBFloat s_color) noexcept ;
    void SetOpacity(float opacity) noexcept;

    constexpr friend bool operator==(const ColorBuf &lhs, const ColorBuf &rhs) noexcept {
        return lhs.color == rhs.color;
    }

    constexpr friend bool operator!=(const ColorBuf &lhs, const ColorBuf &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const ColorBuf &val) {
        os << val.blue << " " << val.green << " " << val.red << " " << val.alpha;
        return os;
    }

};

HASH_INLINE void ColorBuf::Set(const RGBFloat s_color) noexcept {
    red = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Red() * MAXCOLOR + .5F)));
    green = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Green() * MAXCOLOR + .5F)));
    blue = (UBYTE)(MIN(255, fast_ftol_unsigned(s_color.Blue() * MAXCOLOR + .5F)));
}

HASH_INLINE float ColorBuf::GetOpacity() const noexcept {
    return (float)alpha / MAXCOLOR;
}

HASH_INLINE void ColorBuf::SetOpacity(const float opacity) noexcept {
    alpha = (UBYTE)(fast_ftol_unsigned(opacity * MAXCOLOR + .5F));
}

HASH_INLINE void ColorBuf::operator +=(const ColorBuf &other) noexcept {
    if (int tempred; (tempred = red + other.red) > MAXCOLOR) {
        red = MAXCOLOR;
    } else {
        red = (UBYTE)tempred;
    }
    if (int tempgreen; (tempgreen = green + other.green) > MAXCOLOR) {
        green = MAXCOLOR;
    } else {
        green = (UBYTE)tempgreen;
    }
    if (int tempblue; (tempblue = blue + other.blue) > MAXCOLOR) {
        blue = MAXCOLOR;
    } else {
        blue = (UBYTE)tempblue;
    }
    if (int tempalpha; (tempalpha = alpha + other.alpha) > MAXCOLOR) {
        alpha = MAXCOLOR;
    } else {
        alpha = (UBYTE)tempalpha;
    }
}

HASH_INLINE ColorBuf ColorBuf::operator +(const ColorBuf &other) const noexcept {
    ColorBuf temp(*this);
    temp.red += other.red;
    temp.green += other.green;
    temp.blue += other.blue;
    temp.alpha += other.alpha;
    return temp;
}

HASH_INLINE void ColorBuf::operator -=(const ColorBuf &other) noexcept {
    red -= other.red;
    green -= other.green;
    blue -= other.blue;
    alpha -= other.alpha;
}

HASH_INLINE void ColorBuf::operator *=(const float factor) noexcept {
    red = (UBYTE)(lround(factor * red + .5F));
    green = (UBYTE)(lround(factor * green + .5F));
    blue = (UBYTE)(lround(factor * blue + .5F));
    alpha = (UBYTE)(lround(factor * alpha + .5F));
/*
    red = static_cast<UBYTE>(factor * red + .5F);
    green = static_cast<UBYTE>(factor * green + .5F);
    blue = static_cast<UBYTE>(factor * blue + .5F);
    alpha = static_cast<UBYTE>(factor * alpha + .5F);
    */
}

HASH_INLINE void GammaCorrectColBuf(UBYTE *color, const float power) noexcept {
    if (!color || power == 1.F)
        return;
    *color = (UBYTE)(fast_round(MIN(255.F, MAXCOLOR * hash_math::pow((float)*color / MAXCOLOR, hash_math::rcp(power)))));
}

HASH_INLINE void ColorBuf::GammaCorrect(const float power) noexcept {
    if (power == 1.F)
        return;
    GammaCorrectColBuf(&red, power);
    GammaCorrectColBuf(&green, power);
    GammaCorrectColBuf(&blue, power);
}

template<typename T1, typename T2, typename T3>
constexpr auto MAKELUMINANCE(T1 red, T2 green, T3 blue) {
    return (0.299F * (red) + 0.587F * (green) + 0.114F * (blue));
}

