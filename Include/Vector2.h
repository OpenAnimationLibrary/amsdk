//RC  4/24/2002  \HRandy95\Include\Vector2.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "Vector.h"
#ifndef _ALGORITHM_
#include <algorithm>
#endif

class Matrix33;

//size 8
class Vector2 final {
public:
    float x{0.F};
    float y{0.F};

    constexpr Vector2() noexcept = default;
    constexpr Vector2(const float f) noexcept : x(f), y(f) {}
    constexpr explicit Vector2(const int f) noexcept : x(static_cast<float>(f)), y(static_cast<float>(f)) {}
    constexpr explicit Vector2(const double f) noexcept : x(static_cast<float>(f)), y(static_cast<float>(f)) {}
    constexpr Vector2(const float xi, const float yi) noexcept : x(xi), y(yi) {}
    constexpr Vector2(const LONG xi, const LONG yi) noexcept : x(static_cast<float>(xi)), y(static_cast<float>(yi)) {}
    constexpr Vector2(const int xi, const int yi) noexcept : x(static_cast<float>(xi)), y(static_cast<float>(yi)) {}

    constexpr float const &operator [](const int index) const noexcept {
        ASSERT(index < 2);
        return (&x)[index];
    }

    constexpr float &operator [](const int index) noexcept {
        ASSERT(index < 2);
        return (&x)[index];
    }

    constexpr Vector2 &operator=(const float scale) noexcept {
        x = y = scale;
        return *this;
    }

    [[nodiscard]] constexpr float GetX() const noexcept {
        return x;
    }

    [[nodiscard]] constexpr float GetY() const noexcept {
        return y;
    }

    constexpr void SetZero() noexcept {
        x = y = 0.F;
    }

    constexpr void Set(const float px, const float py) noexcept {
        x = px;
        y = py;
    }

    constexpr void Set(const int px, const int py) noexcept {
        x = static_cast<float>(px);
        y = static_cast<float>(py);
    }

    constexpr void Set(const float init) noexcept {
        x = y = init;
    }

    constexpr Vector2 &operator +=(const Vector2 other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vector2 &operator -=(const Vector2 other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr Vector2 &operator *=(const Vector2 other) noexcept {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    constexpr Vector2 &operator -=(const float scale) noexcept {
        x -= scale;
        y -= scale;
        return *this;
    }

    constexpr Vector2 &operator *=(const float scale) noexcept {
        x *= scale;
        y *= scale;
        return *this;
    }

    constexpr Vector2 &operator /=(const float scale) noexcept {
        ASSERT(scale != 0.F);
        x /= scale;
        y /= scale;
        return *this;
    }

    constexpr Vector2 &operator /=(const Vector2 other) noexcept {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    constexpr Vector2 &Negate() noexcept {
        x = -x;
        y = -y;
        return *this;
    }

    //unary minus
    constexpr Vector2 operator -() const noexcept {
        return Vector2(*this).Negate();
    }

    [[nodiscard]] bool IsZero() const noexcept {
        if (hash_math::abs(x) > FLT_EPSILON)
            return false;
        if (hash_math::abs(y) > FLT_EPSILON)
            return false;
        return true;
    }

    [[nodiscard]] constexpr float Sum() const noexcept {
        return x + y;
    }

    constexpr void Clamp(const float minvalue = 0.F, const float maxvalue = 1.F) noexcept {
        x = std::clamp(x, minvalue, maxvalue);
        y = std::clamp(y, minvalue, maxvalue);
    }

    bool operator==(const Vector2 other) const noexcept {
        return floatEQ(x, other.x) && floatEQ(y, other.y);
    }

    bool operator!=(const Vector2 other) const noexcept {
        return !operator==(other);
    }

    [[nodiscard]] constexpr float Square() const noexcept;
    [[nodiscard]] HASH_INLINE float Norm() const noexcept;
    constexpr Vector2 &Normalize() noexcept;
    HASH_INLINE float NormalizeLength() noexcept;
    [[nodiscard]] constexpr Vector2 Normalized() const noexcept;
    [[nodiscard]] constexpr Vector2 Absolute() const noexcept;
    [[nodiscard]] constexpr Vector2 Reciprocal() const noexcept;
    [[nodiscard]] constexpr Vector2 Orthogonal() const noexcept;
    [[nodiscard]] constexpr float Dot(Vector2) const noexcept;
    constexpr Vector2 operator +(Vector2) const noexcept;

    friend void swap(Vector2 &lhs, Vector2 &rhs) noexcept {
        const Vector2 tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }

#ifdef _DEBUG
    [[nodiscard]] bool IsValid() const {
        if (!IsFinite(x))
            return false;
        if (!IsFinite(y))
            return false;
        return true;
    }
#endif

//    friend Vector2 operator -(const Vector2 &);
    constexpr friend Vector2 operator -(Vector2, Vector2) noexcept;
    constexpr friend Vector2 operator *(Vector2, float) noexcept;
    constexpr friend Vector2 operator *(float, Vector2) noexcept;
    constexpr friend Vector2 operator /(Vector2, float) noexcept;

    constexpr friend Vector2 operator *(Vector2, Vector2) noexcept;//MEMBERWISE MULTIPLY
    constexpr friend float operator |(Vector2, Vector2) noexcept;  //DOT PRODUCT
    constexpr friend float operator ^(Vector2, Vector2) noexcept;  //CROSS PRODUCT

    constexpr friend float Dot(const Vector2 lhs, const Vector2 rhs) noexcept {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    constexpr friend Vector2 ToVector2(const Vector other) noexcept {
        return Vector2(other.x, other.y);
    }

    friend void RotateVector2(Vector2 &source, const float anglerad) noexcept {
        const float ca = hash_math::cos(anglerad), sa = hash_math::sin(anglerad);
        source.Set(ca * source.x - sa * source.y, sa * source.x + ca * source.y);
    }

    constexpr friend float CrossZ(const Vector2 lhs, const Vector2 rhs) noexcept {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec) {
        os << vec.x << " " << vec.y;
        return os;
    }
    };

    //Vector2 operator -(const Vector2 &);
constexpr Vector2 operator -(Vector2, Vector2) noexcept;
constexpr Vector2 operator *(Vector2, float) noexcept;
constexpr Vector2 operator *(float, Vector2) noexcept;
constexpr Vector2 operator /(Vector2, float) noexcept;

constexpr Vector2 operator *(Vector2, Vector2) noexcept;//MEMBERWISE MULTIPLY
constexpr float operator |(Vector2, Vector2) noexcept;  //DOT PRODUCT
constexpr float operator ^(Vector2, Vector2) noexcept;  //Cross PRODUCT

constexpr Vector2 operator /(const Vector2 other, const float scale) noexcept {
    ASSERT(scale != 0.F);
    return Vector2(other.x / scale, other.y / scale);
}

constexpr Vector2 Vector2::operator +(const Vector2 other) const noexcept {
    return Vector2(x + other.x, y + other.y);
}

constexpr Vector2 operator -(const Vector2 lhs, const Vector2 rhs) noexcept {
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

constexpr Vector2 operator *(const Vector2 other, const float s) noexcept {
    return Vector2(other.x * s, other.y * s);
}

constexpr Vector2 operator *(const float s, const Vector2 other) noexcept {
    return Vector2(other.x * s, other.y * s);
}

constexpr Vector2 operator *(const Vector2 lhs, const Vector2 rhs) noexcept {
    return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

constexpr float operator |(const Vector2 lhs, const Vector2 rhs) noexcept {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

constexpr float operator ^(const Vector2 lhs, const Vector2 rhs) noexcept {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

constexpr float Vector2::Dot(const Vector2 other) const noexcept {
    return x * other.x + y * other.y;
}

constexpr float Vector2::Square() const noexcept {
    return x * x + y * y;
}

HASH_INLINE float Vector2::Norm() const noexcept {
    return hash_math::sqrt(Square());
}

HASH_INLINE float Vector2::NormalizeLength() noexcept {
    const float length_local = Norm();
    if (length_local == 0.F)
        return 0.F;
    *this *= (1.F / length_local);
    return length_local;
}

constexpr Vector2 Vector2::Normalized() const noexcept {
    return Vector2(*this).Normalize();
}

constexpr Vector2 &Vector2::Normalize() noexcept {
    const float square = Square();
    return square != 0.F ? *this *= 1.F / hash_math::sqrt(square) : *this;
}

constexpr Vector2 Vector2::Absolute() const noexcept {
    return Vector2(hash_math::abs(x), hash_math::abs(y));
}

constexpr Vector2 Vector2::Reciprocal() const noexcept {
    return Vector2(hash_math::rcp(x), hash_math::rcp(y));
}

constexpr Vector2 Vector2::Orthogonal() const noexcept {
    return Vector2(y, -x);
}

constexpr Vector::Vector(const Vector2 other) noexcept : x(other.x), y(other.y), z(1.F) { }
