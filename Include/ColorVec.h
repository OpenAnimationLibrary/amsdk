//NAP  12/20/2004  \Noel120\Include\ColorVec.h
// ReSharper disable CppClangTidyCppcoreguidelinesPreferMemberInitializer
#pragma once

#ifndef _ALGORITHM_
#include <algorithm>
#endif

class HalfColorBuf;
class ColorBuf;

//******************************************************************************
//** ColorVector
//******************************************************************************
class ColorVector final {
public:
    float m_red{0.F};
    float m_green{0.F};
    float m_blue{0.F};

    ColorVector() noexcept = default;
    ~ColorVector() = default;

    ColorVector(const float red, const float green, const float blue) : m_red(red), m_green(green), m_blue(blue) { }

    explicit ColorVector(const float scale) {
        m_red = m_green = m_blue = scale;
    }

    explicit ColorVector(const COLORREF c) {
        m_red = GetRValue(c);
        m_green = GetGValue(c);
        m_blue = GetBValue(c);
    }

    ColorVector(const ColorVector &other) {
        *this = other;
    }

    explicit ColorVector(const HalfColorBuf &other);

    ColorVector &operator=(const float scale) noexcept {
        m_red = m_green = m_blue = scale;
        return *this;
    }

    ColorVector &operator=(const ColorVector &other) noexcept = default;
    ColorVector(ColorVector &&) = default;
    ColorVector &operator=(ColorVector &&) = default;

    ColorVector &operator +=(const ColorVector &other) noexcept {
        m_red += other.m_red;
        m_green += other.m_green;
        m_blue += other.m_blue;
        return *this;
    }

    ColorVector &operator -=(const ColorVector &other) noexcept {
        m_red -= other.m_red;
        m_green -= other.m_green;
        m_blue -= other.m_blue;
        return *this;
    }

    ColorVector &operator *=(const ColorVector &other) noexcept {
        m_red *= other.m_red;
        m_green *= other.m_green;
        m_blue *= other.m_blue;
        return *this;
    }

    ColorVector &operator *=(const float scale) noexcept {
        m_red *= scale;
        m_green *= scale;
        m_blue *= scale;
        return *this;
    }

    ColorVector &operator /=(const ColorVector &other) noexcept {
        m_red /= other.m_red;
        m_green /= other.m_green;
        m_blue /= other.m_blue;
        return *this;
    }

    ColorVector &operator /=(const float scale) noexcept {
        return *this *= hash_math::rcp(scale);
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

/*
    bool operator==(const ColorVector &a) const noexcept {
        return (m_red == a.m_red) && (m_green == a.m_green) && (m_blue == a.m_blue);
    }

    bool operator!=(const ColorVector &a) const noexcept {
        return !(*this == a);
    }
*/
    ColorVector operator +(const ColorVector &a) const {
        return ColorVector(*this) += a;
    }

    ColorVector operator -(const ColorVector &a) const {
        return ColorVector(*this) -= a;
    }

    ColorVector operator *(const ColorVector &a) const {
        return ColorVector(*this) *= a;
    }

    ColorVector operator *(const float s) const {
        return ColorVector(*this) *= s;
    }

    ColorVector operator /(const float s) const {
        return ColorVector(*this) /= s;
    }

    ColorVector operator /(const ColorVector &a) const {
        return ColorVector(*this) /= a;
    }

    float operator [](const int i) const {
        return (&m_red)[i];
    }

    [[nodiscard]] COLORREF GetCOLORREF() const {
        return RGB(fast_round(m_red), fast_round(m_green), fast_round(m_blue));
    }

    [[nodiscard]] float GetLuminance() const noexcept {
        return 0.3f * m_red + 0.59f * m_green + 0.11f * m_blue;
    }

    friend ColorVector operator *(const float s, const ColorVector &a) {
        return a * s;
    }

    void ClampBounds(const float minvalue = 0.F, const float maxvalue = 1.F) {
        m_red = std::clamp(m_red, minvalue, maxvalue);
        m_green = std::clamp(m_green, minvalue, maxvalue);
        m_blue = std::clamp(m_blue, minvalue, maxvalue);
    }
};

HASH_INLINE bool operator==(const ColorVector &lhs, const ColorVector &rhs) noexcept {
    return lhs.m_red == rhs.m_red && lhs.m_green == rhs.m_green && lhs.m_blue == rhs.m_blue;
}

HASH_INLINE bool operator!=(const ColorVector &lhs, const ColorVector &rhs) {
    return !operator==(lhs, rhs);
}

HASH_INLINE ColorVector GetSpectrumColorVector(const float x) {
    const float theta = (1.66f * hash_constants::pi) * x;
    return ColorVector((2.F + hash_math::cos(theta)) / 3.F, (1.F + hash_math::cos(theta - (2.F * hash_constants::pi / 3.F))) / 2.F, (2.F + hash_math::cos(theta - (4.f * hash_constants::pi / 3.F))) / 3.F);
}

//*****************************************************************************
//** ColorVectorAlpha
//*****************************************************************************
class HalfColorBufAlpha;

class ColorVectorAlpha final {
public:
    ColorVector m_color;
    float m_alpha{1.F};

    ColorVectorAlpha() noexcept = default;
    ~ColorVectorAlpha() = default;

    ColorVectorAlpha(const float red, const float green, const float blue, const float alpha) : m_color(red, green, blue), m_alpha(alpha) {}

    explicit ColorVectorAlpha(const float scale) : m_color(scale), m_alpha(scale) {}

    explicit ColorVectorAlpha(const COLORREF c) : m_color(c) {}

    ColorVectorAlpha(const ColorVectorAlpha &other) {
        *this = other;
    }

    explicit ColorVectorAlpha(const HalfColorBufAlpha &other);
    explicit ColorVectorAlpha(const ColorBuf &other);

    ColorVectorAlpha(ColorVectorAlpha &&) = default;

    ColorVectorAlpha &operator=(const ColorVectorAlpha &other) noexcept {
        if (this == &other)
            return *this;
        m_color = other.Color();
        m_alpha = other.Alpha();
        return *this;
    }

    ColorVectorAlpha &operator=(ColorVectorAlpha &&) = delete;

    ColorVectorAlpha &operator +=(const ColorVectorAlpha &other) noexcept {
        m_color += other.Color();
        m_alpha += other.m_alpha;
        return *this;
    }

    ColorVectorAlpha &operator -=(const ColorVectorAlpha &other) noexcept {
        m_color -= other.Color();
        m_alpha -= other.m_alpha;
        return *this;
    }

    ColorVectorAlpha &operator *=(const ColorVectorAlpha &other) noexcept {
        m_color *= other.Color();
        m_alpha *= other.m_alpha;
        return *this;
    }

    ColorVectorAlpha &operator *=(const float scale) noexcept {
        m_color *= scale;
        m_alpha *= scale;
        return *this;
    }

    ColorVectorAlpha &operator /=(const ColorVectorAlpha &other) noexcept {
        m_color /= other.Color();
        m_alpha /= other.m_alpha;
        return *this;
    }

    ColorVectorAlpha &operator /=(const float scale) noexcept {
        return *this *= hash_math::rcp(scale);
    }

    [[nodiscard]] ColorVector Color() const noexcept {
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

    void Set(const float red, const float green, const float blue, const float alpha) noexcept {
        m_color.Set(red, green, blue);
        m_alpha = alpha;
    }

    void Set(const float init) noexcept {
        m_color.Set(init);
        m_alpha = init;
    }

/*
    bool operator==(const ColorVectorAlpha &a) const noexcept {
        return (m_color == a.Color()) && (m_alpha == a.Alpha());
    }

    bool operator!=(const ColorVectorAlpha &a) const noexcept {
        return !(*this == a);
    }
*/
    ColorVectorAlpha operator +(const ColorVectorAlpha &a) const {
        return ColorVectorAlpha(*this) += a;
    }

    ColorVectorAlpha operator -(const ColorVectorAlpha &a) const {
        return ColorVectorAlpha(*this) -= a;
    }

    ColorVectorAlpha operator *(const ColorVectorAlpha &a) const {
        return ColorVectorAlpha(*this) *= a;
    }

    ColorVectorAlpha operator *(const float s) const {
        return ColorVectorAlpha(*this) *= s;
    }

    ColorVectorAlpha operator /(const float s) const {
        return ColorVectorAlpha(*this) /= s;
    }

    ColorVectorAlpha operator /(const ColorVectorAlpha &a) const {
        return ColorVectorAlpha(*this) /= a;
    }

    float operator [](const int i) const noexcept {
        return (&m_color.m_red)[i];
    }

    friend ColorVectorAlpha operator *(const float s, const ColorVectorAlpha &a) {
        return a * s;
    }
};

HASH_INLINE bool operator==(const ColorVectorAlpha &lhs, const ColorVectorAlpha &rhs) noexcept {
    return lhs.m_color == rhs.m_color && lhs.m_alpha == rhs.m_alpha;
}

HASH_INLINE bool operator!=(const ColorVectorAlpha &lhs, const ColorVectorAlpha &rhs) noexcept {
    return !operator==(lhs, rhs);
}

//*****************************************************************************
//** Colors
//*****************************************************************************
/*
class ColorVectors final {
public:
    ColorVector m_ambient, m_diffuse, m_specular, m_reflection, m_shadow;
};
*/
