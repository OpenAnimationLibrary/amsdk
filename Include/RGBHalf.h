// KB  12/2/2004  \Include\RGBHalf.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppClangTidyClangDiagnosticFloatEqual
#pragma once

#include "Allocate.h"
#include "Macros.h"
#include "3rdParty/OpenEXR3/Imath/half.h"

class ColorBuf;
class RGBFloat;
class RGBAFloat;

class RGBHalf final {
public:
    half m_blue{0};
    half m_green{0};
    half m_red{0};

    RGBHalf() noexcept = default;

    //Copy Constructors
    RGBHalf(const float color) noexcept : m_blue(color), m_green(color), m_red(color) {}
    RGBHalf(const float r, const float g, const float b) noexcept : m_blue(b), m_green(g), m_red(r) {}
    RGBHalf(const RGBFloat &other) noexcept; //don't make it explicit , other wise RGBHalf + and += RGBFloat fails

//    explicit RGBHalf(const double color) : m_blue((float)color), m_green((float)color), m_red((float)color) {}
//    explicit RGBHalf(const half color) : m_blue(color), m_green(color), m_red(color) {}

    ~RGBHalf() = default;
    RGBHalf(const RGBHalf &) = default;
    RGBHalf &operator=(const RGBHalf &) noexcept = default;
    RGBHalf(RGBHalf &&) = default;
    RGBHalf &operator=(RGBHalf &&) noexcept = default;
    RGBHalf &operator=(const RGBFloat &other) noexcept;

#ifdef  _MEMDEBUG
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

    RGBHalf &operator +=(const RGBHalf &other) noexcept;
    RGBHalf &operator -=(const RGBHalf &other) noexcept;
    HASH_INLINE RGBHalf &operator *=(const RGBHalf &other) noexcept;
    HASH_INLINE RGBHalf &operator *=(float scale) noexcept;
    HASH_INLINE RGBHalf &operator /=(float scale) noexcept;

    RGBHalf &operator +=(const RGBFloat &other) noexcept;
    RGBHalf &operator *=(const RGBFloat &other) noexcept;

    RGBHalf operator *(const RGBHalf &other) const noexcept{
        return RGBHalf(*this) *= other;
    }

    RGBHalf operator *(const float s) const noexcept {
        return RGBHalf(*this) *= s;
    }

    RGBHalf operator /(const float s) const noexcept {
        return RGBHalf(*this) /= s;
    }

    RGBHalf operator +(const RGBHalf &other) noexcept;

    half operator [](const int i) const noexcept {
        return (&m_red)[i];
    }

    half &operator [](const int i) noexcept {
        return (&m_red)[i];
    }

/*
    HASH_INLINE bool operator==(const RGBHalf &other) const noexcept;

    bool operator!=(const RGBHalf &other) const noexcept {
        return !(*this == other);
    }
*/
    [[nodiscard]] half Red() const noexcept {
        return m_red;
    }

    [[nodiscard]] half Green() const noexcept {
        return m_green;
    }

    [[nodiscard]] half Blue() const noexcept {
        return m_blue;
    }

    [[nodiscard]] float GetRedAsFloat() const noexcept {
        return m_red;
    }

    [[nodiscard]] float GetGreenAsFloat() const noexcept {
        return m_green;
    }

    [[nodiscard]] float GetBlueAsFloat() const noexcept {
        return m_blue;
    }

    [[nodiscard]] RGBFloat GetAsFloat() const noexcept;

    void Set(const half value) noexcept {
        m_red = m_green = m_blue = value;
    }

    void Set(const half red, const half green, const half blue) noexcept {
        m_red = red;
        m_green = green;
        m_blue = blue;
    }

    void Set(const float red, const float green, const float blue) noexcept {
        m_red = red;
        m_green = green;
        m_blue = blue;
    }

    void SetRed(const half red) noexcept {
        m_red = red;
    }

    void SetGreen(const half green) noexcept {
        m_green = green;
    }

    void SetBlue(const half blue) noexcept {
        m_blue = blue;
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

    void Max(const float max) noexcept {
        //Ken, NAP: not sure if this is correct half, float etc
        SetRed(MIN(max, GetRedAsFloat()));
        SetGreen(MIN(max, GetGreenAsFloat()));
        SetBlue(MIN(max, GetBlueAsFloat()));
    }

    [[nodiscard]] float GetLuminance() const noexcept {
        return 0.299F * m_red + 0.587F * m_green + 0.114F * m_blue;
    }

    [[nodiscard]] RGBHalf GammaCorrect(const float power) const noexcept {
        if (power == 1.F)
            return *this;
        RGBHalf rvalue; //NAP Bitmap speed
        rvalue.Set(hash_math::pow(m_red, hash_math::rcp(power)), hash_math::pow(m_green, hash_math::rcp(power)), hash_math::pow(m_blue, hash_math::rcp(power)));
        return rvalue;
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
};

HASH_INLINE RGBHalf &RGBHalf::operator +=(const RGBHalf &other) noexcept {
    m_red += other.Red();
    m_green += other.Green();
    m_blue += other.Blue();
    return *this;
}

HASH_INLINE RGBHalf &RGBHalf::operator -=(const RGBHalf &other) noexcept {
    m_red -= other.Red();
    m_green -= other.Green();
    m_blue -= other.Blue();
    return *this;
}

HASH_INLINE RGBHalf &RGBHalf::operator *=(const RGBHalf &other) noexcept {
    m_red *= other.Red();
    m_green *= other.Green();
    m_blue *= other.Blue();
    return *this;
}

HASH_INLINE RGBHalf &RGBHalf::operator *=(const float scale) noexcept {
    m_red *= scale;
    m_green *= scale;
    m_blue *= scale;
    return *this;
}

HASH_INLINE RGBHalf &RGBHalf::operator /=(const float scale) noexcept {
    ASSERT(scale != 0.F);
    m_red /= scale;
    m_green /= scale;
    m_blue /= scale;
    return *this;
}

HASH_INLINE RGBHalf RGBHalf::operator +(const RGBHalf &other) noexcept {
    m_red += other.Red();
    m_green += other.Green();
    m_blue += other.Blue();
    return RGBHalf(*this);
}

HASH_INLINE bool operator==(const RGBHalf &lhs, const RGBHalf &rhs) noexcept {
    return rhs.m_red == lhs.m_red && rhs.m_green == lhs.m_green && rhs.m_blue == lhs.m_blue;
}

HASH_INLINE bool operator!=(const RGBHalf &lhs, const RGBHalf &rhs) noexcept {
    return !operator==(lhs, rhs);
}

//**********************************************************
//**********************************************************
//**********************************************************
//**********************************************************
class RGBAHalf {
public:
    RGBHalf m_color;
    half m_alpha{1.F};

    RGBAHalf() noexcept = default;

    RGBAHalf(const float r, const float g, const float b, const float a) noexcept : m_color(r, g, b), m_alpha(a) {}
    RGBAHalf(const RGBFloat &other, float alpha) noexcept;
    RGBAHalf(const float value) noexcept : m_color(value) {}

//    explicit RGBAHalf(const half value) : m_color(value), m_alpha(value) {}
    explicit RGBAHalf(const RGBHalf other) noexcept : m_color(other) {}
//    explicit RGBAHalf(const double value) : m_color(value) {}
    explicit RGBAHalf(const ColorBuf &other) noexcept;
    explicit RGBAHalf(const RGBAFloat &other) noexcept;

    ~RGBAHalf() = default;
    RGBAHalf(const RGBAHalf &) = default;
    RGBAHalf &operator=(const RGBAHalf &) noexcept = default;
    RGBAHalf(RGBAHalf &&) = default;
    RGBAHalf &operator=(RGBAHalf &&) noexcept = default;

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

    HASH_INLINE RGBAHalf &operator=(const RGBAFloat &other) noexcept;

    RGBAHalf &operator +=(const RGBAHalf &other) noexcept;
    RGBAHalf &operator -=(const RGBAHalf &other) noexcept;
    HASH_INLINE RGBAHalf &operator *=(float scale) noexcept;
    HASH_INLINE RGBAHalf &operator /=(float scale) noexcept;

    RGBAHalf operator *(const float s) const noexcept {
        return RGBAHalf(*this) *= s;
    }

    RGBAHalf operator /(const float s) const noexcept {
        return RGBAHalf(*this) /= s;
    }

    RGBAHalf operator +(const RGBAHalf &other) noexcept;
    RGBAHalf operator -(const RGBAHalf &other) noexcept;

/*
    HASH_INLINE bool operator==(const RGBAHalf &other) const noexcept;

    bool operator!=(const RGBAHalf &other) const noexcept {
        return !(*this == other);
    }
*/

    half operator [](const int i) const noexcept {
        return ((half *)&m_color)[i];
    }

    half &operator [](const int i) noexcept {
        return ((half *)&m_color)[i];
    }

    [[nodiscard]] RGBHalf Color() const noexcept {
        return m_color;
    }

    [[nodiscard]] half Red() const noexcept {
        return m_color.Red();
    }

    [[nodiscard]] half Green() const noexcept {
        return m_color.Green();
    }

    [[nodiscard]] half Blue() const noexcept {
        return m_color.Blue();
    }

    [[nodiscard]] half Alpha() const noexcept {
        return m_alpha;
    }

    [[nodiscard]] float GetAlphaAsFloat() const noexcept {
        return m_alpha;
    }

    void SetRed(const half red) noexcept {
        m_color.SetRed(red);
    }

    void SetGreen(const half green) noexcept {
        m_color.SetGreen(green);
    }

    void SetBlue(const half blue) noexcept {
        m_color.SetBlue(blue);
    }

    void SetColor(const RGBHalf &color) noexcept {
        m_color = color;
    }

    void SetAlpha(const half alpha) noexcept {
        m_alpha = alpha;
    }

    void SetAlpha(const float alpha) noexcept {
        m_alpha = alpha;
    }

    void Set(const half red, const half green, const half blue, const half alpha) noexcept {
        m_color.Set(red, green, blue);
        m_alpha = alpha;
    }

    void Max(const float max)  noexcept{
        m_color.Max(max);
        SetAlpha(MIN(max, (float)Alpha()));
    }

    [[nodiscard]] RGBAFloat GetAsFloat() const noexcept;
    [[nodiscard]] RGBFloat GetColorAsFloat() const noexcept;

    /*
       bool CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
          return m_color.CheckOffBound( lobound, hibound );
       };
       */
};

HASH_INLINE RGBAHalf &RGBAHalf::operator +=(const RGBAHalf &other) noexcept {
    m_color += other.Color();
    m_alpha += other.Alpha();
    return *this;
}

HASH_INLINE RGBAHalf &RGBAHalf::operator -=(const RGBAHalf &other) noexcept {
    m_color -= other.Color();
    m_alpha -= other.Alpha();
    return *this;
}

HASH_INLINE RGBAHalf &RGBAHalf::operator *=(const float scale) noexcept {
    m_color *= scale;
    m_alpha *= scale;
    return *this;
}

HASH_INLINE RGBAHalf &RGBAHalf::operator /=(const float scale) noexcept {
    ASSERT(scale != 0.F);
    m_color /= scale;
    m_alpha /= scale;
    return *this;
}

HASH_INLINE RGBAHalf RGBAHalf::operator +(const RGBAHalf &other) noexcept {
    m_color += other.Color();
    m_alpha += other.Alpha();
    return RGBAHalf(*this);
}

HASH_INLINE RGBAHalf RGBAHalf::operator -(const RGBAHalf &other) noexcept {
    m_color -= other.Color();
    m_alpha -= other.Alpha();
    return RGBAHalf(*this);
}

HASH_INLINE bool operator==(const RGBAHalf &lhs, const RGBAHalf &rhs) noexcept {
    return lhs.m_color == rhs.m_color && lhs.m_alpha == rhs.m_alpha;
}

HASH_INLINE bool operator!=(const RGBAHalf &lhs, const RGBAHalf &rhs) noexcept {
    return !operator==(lhs, rhs);
}

//**********************************************************
//**********************************************************
//**********************************************************
//**********************************************************
class YAFloat;
class YAByte;

class YAHalf final {
public:
    half m_luminance{0};
    half m_alpha{1};

    YAHalf() noexcept = default;

    YAHalf(const half other) noexcept : m_luminance(other) {}
    YAHalf(const YAFloat &other) noexcept;
    YAHalf(const YAByte &other) noexcept;
    YAHalf(const float l, const float a) noexcept : m_luminance(l), m_alpha(a) {}
    YAHalf(const float f) noexcept : m_luminance(f) {}

    ~YAHalf() = default;
    YAHalf(const YAHalf &) = default;
    YAHalf &operator=(const YAHalf &) noexcept = default;
    YAHalf(YAHalf &&) = default;
    YAHalf &operator=(YAHalf &&) = default;

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

    YAHalf &operator=(const YAFloat &other) noexcept;
    YAHalf &operator=(const YAByte &other) noexcept;
    YAHalf &operator=(const RGBFloat &other) noexcept;
    YAHalf &operator=(const RGBAFloat &other) noexcept;
    YAHalf &operator=(const ColorBuf &other) noexcept;

    YAHalf &operator +=(const YAHalf &other) noexcept;
    YAHalf &operator -=(const YAHalf &other) noexcept;
    HASH_INLINE YAHalf &operator *=(float scale) noexcept;
    YAHalf &operator /=(float scale) noexcept;

    YAHalf operator *(const float s) const noexcept {
        return YAHalf(*this) *= s;
    }

    YAHalf operator +(const YAHalf &other) noexcept;

    HASH_INLINE bool operator==(const YAHalf &other) const noexcept;

    bool operator!=(const YAHalf &other) const noexcept {
        return !(*this == other);
    }

    half operator [](const int i) const noexcept {
        return ((half *)&m_luminance)[i];
    }

    half &operator [](const int i) noexcept {
        return (&m_luminance)[i];
    }

    [[nodiscard]] half Luminance() const noexcept {
        return m_luminance;
    }

    [[nodiscard]] half Alpha() const noexcept {
        return m_alpha;
    }

    void SetLuminance(const half luminance) noexcept {
        m_luminance = luminance;
    }

    void SetAlpha(const half alpha) noexcept {
        m_alpha = alpha;
    }

    void Set(const half luminance, const half alpha) noexcept {
        m_luminance = luminance;
        m_alpha = alpha;
    }

    /*
       bool CheckOffBound( float lobound, float hibound ) { // YP : For HDR testing and debugging purpose
          if ( m_luminance < lobound || m_luminance > hibound )
             return true;
          return false;
       };
       */
};

HASH_INLINE YAHalf &YAHalf::operator +=(const YAHalf &other) noexcept {
    m_luminance += other.m_luminance;
    m_alpha += other.m_alpha;
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator -=(const YAHalf &other) noexcept {
    m_luminance -= other.m_luminance;
    m_alpha -= other.m_alpha;
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator *=(const float scale) noexcept {
    m_luminance *= scale;
    m_alpha *= scale;
    return *this;
}

HASH_INLINE YAHalf &YAHalf::operator /=(const float scale) noexcept {
    ASSERT(scale != 0.F);
    m_luminance /= scale;
    m_alpha /= scale;
    return *this;
}

HASH_INLINE YAHalf YAHalf::operator +(const YAHalf &other) noexcept {
    m_luminance += other.m_luminance;
    m_alpha += other.m_alpha;
    return YAHalf(*this);
}

HASH_INLINE bool YAHalf::operator==(const YAHalf &other) const noexcept {
    return m_luminance == other.m_luminance && m_alpha == other.m_alpha;
}
