//RC  4/24/2002  \HRandy95\Include\Vector4.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "Vector.h"
#include "Exports.h"
#include "Permutation.h"

class Matrix44;

//size 16
class MATRIXEXPORT Vector4 final {
public:
    float x{0.F};
    float y{0.F};
    float z{0.F};
    float w{0.F};

    constexpr Vector4() noexcept = default;
    constexpr Vector4(const float xi, const float yi, const float zi, const float wi) noexcept : x(xi), y(yi), z(zi), w(wi) {}
    constexpr Vector4(const int fill) noexcept : x(static_cast<float>(fill)), y(static_cast<float>(fill)), z(static_cast<float>(fill)), w(static_cast<float>(fill)) {}
    constexpr explicit Vector4(const float fill) noexcept : x(fill), y(fill), z(fill), w(fill) {}
    constexpr explicit Vector4(const double fill) noexcept : x(static_cast<float>(fill)), y(static_cast<float>(fill)), z(static_cast<float>(fill)), w(static_cast<float>(fill)) {}

    Vector4(const Vector4 &other, const Permutation &perm) noexcept : x(other[perm[0]]), y(other[perm[1]]), z(other[perm[2]]), w(other[perm[3]]) { }

    constexpr explicit Vector4(const Vector &other3) noexcept : x(other3.x), y(other3.y), z(other3.z), w(1.F) {}

    constexpr float const &operator [](const int index) const noexcept {
        ASSERT(index < 4);
        return (&x)[index];
    }

    constexpr float &operator [](const int index) noexcept {
        ASSERT(index < 4);
        return (&x)[index];
    }

    [[nodiscard]] constexpr float GetX() const noexcept {
        return x;
    }

    [[nodiscard]] constexpr float GetY() const noexcept {
        return y;
    }

    [[nodiscard]] constexpr float GetZ() const noexcept {
        return z;
    }

    [[nodiscard]] constexpr float GetW() const noexcept {
        return w;
    }

    constexpr void Set(const float s_x, const float s_y, const float s_z, const float s_w) noexcept {
        x = s_x;
        y = s_y;
        z = s_z;
        w = s_w;
    }

    constexpr void Set(const float fill) noexcept {
        x = y = z = w = fill;
    }

    Vector4 &operator -=(const Vector4 other) noexcept {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vector4 &operator +=(const Vector4 other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    HASH_INLINE Vector4 &operator /=(float scale) noexcept;
    HASH_INLINE Vector4 &operator *=(float scale) noexcept;

    bool operator==(const Vector4 other) const noexcept {
        return floatEQ(x, other.x) && floatEQ(y, other.y) && floatEQ(z, other.z) && floatEQ(w, other.w);
    }

    bool operator!=(const Vector4 other) const noexcept {
        return !operator==(other);
    }

    constexpr Vector4 operator +(const Vector4 other) const noexcept {
        return Vector4(x + other.x, y + other.y, x + other.x, w + other.w);
    }

    constexpr Vector4 operator -(const Vector4 other) const noexcept {
        return Vector4(x - other.x, y - other.y, x - other.x, w - other.w);
    }

//    HASH_INLINE float operator |(Vector4 other) const noexcept; //Dot Product
//    HASH_INLINE float operator |(Vector other) const noexcept; //Dot Product
    [[nodiscard]] HASH_INLINE float Dot(Vector4 other) const noexcept; //Dot Product
    [[nodiscard]] HASH_INLINE float Dot(Vector other) const noexcept; //Dot Product
    [[nodiscard]] HASH_INLINE float Dot() const noexcept;
    [[nodiscard]] HASH_INLINE Vector4 operator /(Vector4 other) const noexcept;
    [[nodiscard]] HASH_INLINE Vector4 operator /(float scale) const noexcept;
    [[nodiscard]] HASH_INLINE Vector4 operator *(Vector4 other) const noexcept; //Member by member multiply
    [[nodiscard]] HASH_INLINE Vector4 operator *(float scale) const noexcept;

    friend void swap(Vector4 &lhs, Vector4 &rhs) noexcept {
        const Vector4 temp(lhs);
        lhs = rhs;
        rhs = temp;
    }

    [[nodiscard]] bool IsZero() const noexcept {
        if (hash_math::abs(x) > FLT_EPSILON)
            return false;
        if (hash_math::abs(y) > FLT_EPSILON)
            return false;
        if (hash_math::abs(z) > FLT_EPSILON)
            return false;
        if (hash_math::abs(w) > FLT_EPSILON)
            return false;
        return true;
    }

#ifdef _DEBUG
    [[nodiscard]] bool IsValid() const {
        if (!IsFinite(x))
            return false;
        if (!IsFinite(y))
            return false;
        if (!IsFinite(z))
            return false;
        if (!IsFinite(w))
            return false;
        return true;
    }
#endif

    friend Vector4 operator *(const float scale, const Vector4 other) noexcept {
        return other * scale;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector4 &vec) {
        os << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
        return os;
    }
};

HASH_INLINE Vector4 &Vector4::operator /=(const float scale) noexcept {
    ASSERT(scale != 0.F);
    x /= scale;
    y /= scale;
    z /= scale;
    w /= scale;
    return *this;
}

HASH_INLINE Vector4 &Vector4::operator *=(const float scale) noexcept {
    x *= scale;
    y *= scale;
    z *= scale;
    w *= scale;
    return *this;
}

HASH_INLINE float Vector4::Dot(const Vector4 other) const noexcept {
//Dot Product
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

HASH_INLINE float Vector4::Dot(const Vector other) const noexcept {
    //Dot Product
    return x * other.x + y * other.y + z * other.z + w;
}

HASH_INLINE float Vector4::Dot() const noexcept {
    //Dot Self
    return x * x + y * y + z * z + w * w;
}

HASH_INLINE Vector4 Vector4::operator *(const Vector4 other) const noexcept {
    //Member by member multiply
    return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

HASH_INLINE Vector4 Vector4::operator /(const Vector4 other) const noexcept {
    return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

HASH_INLINE Vector4 Vector4::operator *(const float scale) const noexcept {
    return Vector4(x * scale, y * scale, z * scale, w * scale);
}

HASH_INLINE Vector4 Vector4::operator /(const float scale) const noexcept {
    ASSERT(scale != 0.F);
    if (scale != 0.F)
        return Vector4(x / scale, y / scale, z / scale, w / scale);
    return Vector4();
}
