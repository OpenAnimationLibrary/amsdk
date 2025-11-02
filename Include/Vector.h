//BC  2/19/2004  \Bob110\Include\Vector.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "StdAfx.h"
#include "Exports.h"
#include "Permutation.h"
#include "Macros.h"
#ifndef _ALGORITHM_
#include <algorithm>
#endif
#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F
#endif

class Matrix34;
class Matrix33;
class Vector2;
class Quaternion;

//size 12
class MATRIXEXPORT Vector final {
public:
    float x{0.F};
    float y{0.F};
    float z{0.F};

    constexpr Vector() noexcept = default;
    constexpr explicit Vector(const int f) noexcept : x(static_cast<float>(f)), y(static_cast<float>(f)), z(static_cast<float>(f)) {}
    constexpr explicit Vector(const float f) noexcept : x(f), y(f), z(f) {}
    constexpr explicit Vector(const double f) noexcept : x(static_cast<float>(f)), y(static_cast<float>(f)), z(static_cast<float>(f)) {}
    constexpr Vector(const float xi, const float yi, const float zi) noexcept : x(xi), y(yi), z(zi) {}

#pragma warning(suppress : 26447)
    Vector(const Vector other, const Permutation perm) noexcept : x(other[perm[0]]), y(other[perm[1]]), z(other[perm[2]]) {}
    constexpr Vector(Vector2 other) noexcept;

    constexpr float const &operator [](const int index) const noexcept {
        ASSERT(index < 3);
        return (&x)[index];
    }

    constexpr float &operator [](const int index) noexcept {
        ASSERT(index < 3);
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

    constexpr void Set(const float xi, const float yi, const float zi) noexcept {
        x = xi;
        y = yi;
        z = zi;
    }

    constexpr void Set(const float fill) noexcept {
        x = y = z = fill;
    }

    constexpr void SetZero() noexcept {
        x = y = z = 0.F;
    }

    constexpr Vector &operator=(const float scale) noexcept {
        x = y = z = scale;
        return *this;
    }

    constexpr Vector &operator *=(const Vector other) noexcept {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    constexpr Vector &operator *=(const float scale) noexcept {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    constexpr Vector &operator /=(const Vector other) noexcept {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    constexpr Vector &operator /=(const float scale) noexcept {
        ASSERT(scale != 0.F);
        x /= scale;
        y /= scale;
        z /= scale;
        return *this;
    }

    constexpr Vector &operator +=(const Vector other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    constexpr Vector &operator +=(const float scale) noexcept {
        x += scale;
        y += scale;
        z += scale;
        return *this;
    }

    constexpr Vector &operator -=(const Vector other) noexcept {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    constexpr Vector &operator -=(const float scale) noexcept {
        x -= scale;
        y -= scale;
        z -= scale;
        return *this;
    }

    HASH_INLINE Vector &operator *=(const Matrix34 &m) noexcept;
    HASH_INLINE Vector &operator *=(const Matrix33 &m) noexcept;
    HASH_INLINE Vector &operator *=(const Quaternion &q) noexcept;

    Vector &operator ^=(const Vector a) noexcept {
        return (*this = Cross(a));
    }

    constexpr Vector &Negate() noexcept {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    //unary minus
    Vector operator -() const noexcept {
        return Vector(*this).Negate();
    }

    friend bool operator ==(const Vector &li, const Vector &re) noexcept {
        return floatEQ(li.x, re.x) && floatEQ(li.y, re.y) && floatEQ(li.z, re.z);
    }

    friend bool operator !=(const Vector &li, const Vector &re) noexcept {
        return !operator==(li, re);
    }

    friend bool operator <(const Vector &li, const Vector &re) noexcept {
        return li.Dot() < re.Dot();
    }

    constexpr friend Vector operator +(const Vector li, const Vector re) noexcept {
        return Vector(li.x+re.x,li.y+re.y,li.z+re.z);//li += re;
    }

    constexpr friend Vector operator -(const Vector li, const Vector re) noexcept {
        return Vector(li.x-re.x,li.y-re.y,li.z-re.z);//li -= re;
    }

    constexpr friend Vector operator *(const Vector li, const Vector re) noexcept {
        return Vector(li.x*re.x,li.y*re.y,li.z*re.z);//li *= re;
    }

    constexpr friend Vector operator /(const Vector li, const Vector re) noexcept {
        return Vector(li.x/re.x,li.y/re.y,li.z/re.z);//li /= re;
    }

    constexpr Vector operator +(float scale) const noexcept;
    constexpr Vector operator -(float scale) const noexcept;
    constexpr Vector operator /(float scale) const noexcept;
    [[nodiscard]] HASH_INLINE float Norm() const noexcept;
    [[nodiscard]] HASH_INLINE float InvNorm() const noexcept;
    [[nodiscard]] HASH_INLINE Vector Normalized() const noexcept;
    [[nodiscard]] HASH_INLINE Vector FixedNormalized() const noexcept;
    HASH_INLINE float NormalizeLength() noexcept;
    HASH_INLINE Vector &Normalize() noexcept;
    HASH_INLINE Vector &FixedNormalize() noexcept;
    [[nodiscard]] constexpr float Dot(Vector other) const noexcept;
    [[nodiscard]] HASH_INLINE float Dot() const noexcept;
    [[nodiscard]] constexpr Vector Absolute() const noexcept;
    [[nodiscard]] constexpr Vector Reciprocal() const noexcept;
    HASH_INLINE void CrossSelf(Vector other) noexcept;
    [[nodiscard]] HASH_INLINE Vector Cross(Vector other) const noexcept;

    [[nodiscard]] Vector Hundredized() const noexcept {
        return Vector(*this).Hundredize();
    }

    Vector &Hundredize() noexcept {
        if (const float length_local = Norm(); length_local != 0.F)
            *this *= UNIT / length_local;
        return *this;
    }

    constexpr float operator |(const Vector other) const noexcept {
        //same as Dot
        return Dot(other);
    }

    Vector operator ^(const Vector other) const noexcept {
        //same as Cross
        return Cross(other);
    }

    [[nodiscard]] int MaxDim() const noexcept {
        const float fx = hash_math::abs(x), fy = hash_math::abs(y), fz = hash_math::abs(z);
        return fx > fy ? fx > fz ? 0 : 2 : fy > fz ? 1 : 2;
    }

    [[nodiscard]] int MinDim() const noexcept {
        const float fx = hash_math::abs(x), fy = hash_math::abs(y), fz = hash_math::abs(z);
        return fx < fy ? fx < fz ? 0 : 2 : fy < fz ? 1 : 2;
    }

    void RoundVector(const double modulo = 0.0001) noexcept {
        Round(x, modulo);
        Round(y, modulo);
        Round(z, modulo);
    }

    [[nodiscard]] bool IsLess(const float minvalue) const noexcept {
        if (hash_math::abs(x) > minvalue)
            return false;
        if (hash_math::abs(y) > minvalue)
            return false;
        if (hash_math::abs(z) > minvalue)
            return false;
        return true;
    }

    //if maxdifference == 0.F , the values must match
    [[nodiscard]] bool IsEqual(const Vector other, const float maxdifference = FLT_EPSILON) const noexcept {
        if (maxdifference == 0.F) {
            if (floatNEQ(x, other.x))
                return false;
            if (floatNEQ(y, other.y))
                return false;
            if (floatNEQ(z, other.y))
                return false;
        } else {
            if (hash_math::abs(x - other.x) > maxdifference)
                return false;
            if (hash_math::abs(y - other.y) > maxdifference)
                return false;
            if (hash_math::abs(z - other.z) > maxdifference)
                return false;
        }
        return true;
    }

    [[nodiscard]] bool IsZero() const noexcept {
        return !IsNotZero();
    }

    [[nodiscard]] bool IsNotZero() const noexcept {
        if (x != 0.F)
            return true;
        if (y != 0.F)
            return true;
        if (z != 0.F)
            return true;
        return false;
    }

    void RoundToZero(const float min = 1e-10F) noexcept {
        //if values are smaller than min , set this values to 0
        if (hash_math::abs(x) < min)
            x = 0.F;
        if (hash_math::abs(y) < min)
            y = 0.F;
        if (hash_math::abs(z) < min)
            z = 0.F;
    }

    void FixZero() noexcept {
        //fix -0.0
        if (hash_math::abs(x) < 1e-10F)
            x = 0.F;
        if (hash_math::abs(y) < 1e-10F)
            y = 0.F;
        if (hash_math::abs(z) < 1e-10F)
            z = 0.F;
    }

    constexpr void FixNormalizedVector() noexcept {
        //fix when Normalize returns a Vector like this (0,1.000,1e-6)
        const Vector temp = Absolute();
        if (const bool x_one = (temp.x > .9999f && temp.y < 1e-3F && temp.z < 1e-3F); x_one) {
            Set(SIGN_FLOAT(x), 0.F, 0.F);
        } else {
            if (const bool y_one = (temp.y > .9999f && temp.x < 1e-3F && temp.z < 1e-3F); y_one) {
                Set(0.F, SIGN_FLOAT(y), 0.F);
            } else {
                if (const bool z_one = (temp.z > .9999f && temp.x < 1e-3F && temp.y < 1e-3F); z_one) {
                    Set(0.F, 0.F, SIGN_FLOAT(z));
                }
            }
        }
    }

    constexpr void Clamp(const float minvalue = 0.F, const float maxvalue = 1.F) noexcept {
        x = std::clamp(x, minvalue, maxvalue);
        y = std::clamp(y, minvalue, maxvalue);
        z = std::clamp(y, minvalue, maxvalue);
    }

    constexpr void PushMinMax(Vector &minv, Vector &maxv) const noexcept {
        if (x > maxv.x)
            maxv.x = x;
        if (x < minv.x)
            minv.x = x;
        if (y > maxv.y)
            maxv.y = y;
        if (y < minv.y)
            minv.y = y;
        if (z > maxv.z)
            maxv.z = z;
        if (z < minv.z)
            minv.z = z;
    }

#ifdef _DEBUG
    [[nodiscard]] bool IsValid() const noexcept {
        if (!IsFinite(x))
            return false;
        if (!IsFinite(y))
            return false;
        if (!IsFinite(z))
            return false;
        return true;
    }
#endif

    friend void swap(Vector &lhs, Vector &rhs) noexcept {
        const Vector tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }

    friend float Dot(const Vector lhs, const Vector rhs) noexcept {
        return lhs.Dot(rhs);
    }

    friend Vector Cross(const Vector lhs, const Vector rhs) noexcept {
        return lhs.Cross(rhs);
    }

    constexpr friend bool IsBackward(const Vector a, const Vector b, const Vector c) noexcept {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) < 0.F;
    }

    constexpr friend Vector Min(const Vector left, const Vector right) noexcept {
        return Vector(left.x < right.x ? left.x : right.x, left.y < right.y ? left.y : right.y, left.z < right.z ? left.z : right.z);
    }

    constexpr friend Vector Max(const Vector left, const Vector right) noexcept {
        return Vector(left.x > right.x ? left.x : right.x, left.y > right.y ? left.y : right.y, left.z > right.z ? left.z : right.z);
    }

    constexpr friend Vector operator *(Vector, float) noexcept;
    constexpr friend Vector operator *(float, Vector) noexcept;
    constexpr friend Vector operator *(Vector, double) noexcept;
    constexpr friend Vector operator *(double, Vector) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Vector &val) {
        os << val.x << " " << val.y << " " << val.z;
        return os;
    }
};

constexpr Vector operator *(Vector, float) noexcept;
constexpr Vector operator *(float, Vector) noexcept;

constexpr Vector operator *(const Vector rhs, const float lhs) noexcept {
    return Vector(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}

constexpr Vector operator *(const float lhs, const Vector rhs) noexcept {
    return Vector(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}

constexpr Vector operator *(Vector, double) noexcept;
constexpr Vector operator *(double, Vector) noexcept;

constexpr Vector operator *(const Vector rhs, const double lhs) noexcept {
    return Vector(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}

constexpr Vector operator *(const double lhs, const Vector rhs) noexcept {
    return Vector(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}

constexpr Vector Vector::operator -(const float scale) const noexcept {
    return Vector(x - scale, y - scale, z - scale);
}

constexpr Vector Vector::operator +(const float scale) const noexcept {
    return Vector(x + scale, y + scale, z + scale);
}

constexpr Vector Vector::operator /(const float scale) const noexcept {
    ASSERT(scale != 0.F);
    return Vector(x / scale, y / scale, z / scale);
}

constexpr Vector Vector::Reciprocal() const noexcept {
    return Vector(hash_math::rcp(x), hash_math::rcp(y), hash_math::rcp(z));
}

HASH_INLINE void Vector::CrossSelf(const Vector other) noexcept {
    *this = Cross(other);
}

constexpr Vector Vector::Absolute() const noexcept {
    return Vector(hash_math::abs(x), hash_math::abs(y), hash_math::abs(z));
}

HASH_INLINE Vector Vector::Cross(const Vector other) const noexcept {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

constexpr float Vector::Dot(const Vector other) const noexcept {
    return x * other.x + y * other.y + z * other.z;
}

HASH_INLINE float Vector::Dot() const noexcept {
    //Dot Self
    return x * x + y * y + z * z;
}

HASH_INLINE float Vector::Norm() const noexcept {
    return hash_math::sqrt(Dot());
}

HASH_INLINE float Vector::InvNorm() const noexcept {
    return hash_math::rcp(hash_math::sqrt(Dot()));
}

HASH_INLINE Vector Vector::Normalized() const noexcept {
    Vector ret_val(*this);
    return ret_val.Normalize();
}

HASH_INLINE Vector Vector::FixedNormalized() const noexcept {
    Vector ret_val(*this);
    return ret_val.FixedNormalize();
}

HASH_INLINE float Vector::NormalizeLength() noexcept {
    const float length_local = hash_math::sqrt(x * x + y * y + z * z);
    ASSERT(length_local >= 0.F);
    if (length_local < 1e-10F) {
        return 0.F;
    }
    *this /= length_local;
    return length_local;
}

HASH_INLINE Vector &Vector::Normalize() noexcept {
    const float square = hash_math::sqrt(x * x + y * y + z * z);
    if (square != 0.F && (square > 1.000001F || square < 0.99999F)) {
        *this /= square;
    }
    return *this;
}

HASH_INLINE Vector &Vector::FixedNormalize() noexcept {
    const float square = hash_math::sqrt(x * x + y * y + z * z);
    if (square != 0.F && (square > 1.000001F || square < 0.99999F)) {
        *this /= square;
        const float vsum = hash_math::abs(x + y + z);
        if (vsum > 1.F && vsum < 1.0001F)
            FixNormalizedVector();
    }
    return *this;
}

//free function

HASH_INLINE float DistancePointToPlane(const Vector point, const Vector p_onplane, const Vector normal) noexcept {
    const Vector delta = point - p_onplane;
    return Dot(delta, normal);
}

constexpr void PushMinMax(const Vector p, Vector &minv, Vector &maxv) noexcept {
    if (p.x > maxv.x)
        maxv.x = p.x;
    if (p.x < minv.x)
        minv.x = p.x;
    if (p.y > maxv.y)
        maxv.y = p.y;
    if (p.y < minv.y)
        minv.y = p.y;
    if (p.z > maxv.z)
        maxv.z = p.z;
    if (p.z < minv.z)
        minv.z = p.z;
}
