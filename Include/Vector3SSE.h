// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeMemberInit
#pragma once

#include "Vector.h"

#if defined(__AVX2__)
#include <intrin.h>
const __m128 zero_m128 = _mm_set_ps(1.F, 0.F, 0.F, 0.F); //_mm_setzero_ps();
#else
#define vec_splat(x, e) _mm_shuffle_ps(x, x, _MM_SHUFFLE(e, e, e, e))

static HASH_INLINE __m128 dot3(const __m128 vec0, const __m128 vec1) noexcept {
    const __m128 result = _mm_mul_ps(vec0, vec1);
    return _mm_add_ps(vec_splat(result, 0), _mm_add_ps(vec_splat(result, 1), vec_splat(result, 2)));
}
#endif
#ifndef __SMMINTRIN_H
#include <smmintrin.h>
#endif

/*
! don't use !
    precision only 11 bit
    [[nodiscard]] float InvNorm() const {
        return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x7F))); //SSE4
        return _mm_cvtss_f32(_mm_rsqrt_ss(dot3(mmvalue, mmvalue)));
    }

//too big error -> differences between the versions
static HASH_INLINE __m128 newtonrapson_rsqrt4(const __m128 v) {
    const __m128 approx = _mm_rsqrt_ps(v);
    const __m128 muls = _mm_mul_ps(_mm_mul_ps(v, approx), approx);
    return _mm_mul_ps(_mm_mul_ps(_mm_set_ps(.5F, .5F, .5F, .5F), approx), _mm_sub_ps(_mm_set_ps(3.F, 3.F, 3.F, 3.F), muls));
}
//relative error bigger than above
HASH_INLINE __m128 newtonrapson_rsqrt(const __m128& a) {
    const __m128 r = _mm_rsqrt_ps(a);
    return _mm_add_ps(_mm_mul_ps(_mm_set_ps1(1.5F), r), _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(a, _mm_set_ps1(-0.5F)), r), _mm_mul_ps(r, r)));
}
*/

class alignas(16) Vector3SSE final {
public:
    //Member variables
    union {
        __m128 mmvalue{0.F, 0.F, 0.F, 1.F};  // NOLINT(clang-diagnostic-missing-braces)

        struct {
            float x, y, z;
            int dummy;
        };
    };

    //constructors
    constexpr Vector3SSE() noexcept = default;

    constexpr explicit Vector3SSE(const __m128 m) noexcept : mmvalue(m) {}
    explicit Vector3SSE(const Vector other) noexcept : mmvalue(_mm_set_ps(1.F, other.z, other.y, other.x)) {}
    explicit Vector3SSE(const float fill) noexcept : mmvalue(_mm_set_ps(1.F, fill, fill, fill)) {}
    Vector3SSE(const float xi, const float yi, const float zi) noexcept : mmvalue(_mm_set_ps(1.F, zi, yi, xi)) {}

    void Set(const float s_x, const float s_y, const float s_z) noexcept {
        mmvalue = _mm_set_ps(1.F, s_z, s_y, s_x);
    }

    void Set(const float fill) noexcept {
        mmvalue = _mm_set1_ps(fill);
    }

    Vector3SSE &operator=(const Vector other) noexcept {
        mmvalue = _mm_set_ps(1.F, other.z, other.y, other.x);
        return *this;
    }

    [[nodiscard]] constexpr Vector ToVector() const noexcept {
        return Vector(x, y, z);
    }

    explicit constexpr operator const __m128 &() const noexcept {
        return mmvalue;
    }

    explicit constexpr operator __m128 &() noexcept {
        return mmvalue;
    }

    static Vector3SSE load(const void *const a) noexcept {
        return Vector3SSE(_mm_and_ps(_mm_load_ps((float *)a), _mm_castsi128_ps(_mm_set_epi32(0, -1, -1, -1))));
    }

    static Vector3SSE loadu(const void *const a) noexcept {
        return Vector3SSE(_mm_and_ps(_mm_loadu_ps((float *)a), _mm_castsi128_ps(_mm_set_epi32(0, -1, -1, -1))));
    }

    static void storeu(void *ptr, const Vector3SSE &v) noexcept {
        _mm_storeu_ps((float *)ptr, v.mmvalue);
    }

    constexpr float const &operator [](const int index) const noexcept {
        return (&x)[index];
    }

    constexpr float &operator [](const int index) noexcept {
        return (&x)[index];
    }

    friend bool operator ==(const Vector3SSE &li, const Vector3SSE &re) noexcept {
        return _mm_movemask_ps(_mm_cmpeq_ps(li.mmvalue, re.mmvalue)) == 0xf;
    }

    friend bool operator !=(const Vector3SSE &li, const Vector3SSE &re) noexcept {
        return _mm_movemask_ps(_mm_cmpneq_ps(li.mmvalue, re.mmvalue)) != 0;
    }

    friend bool operator <(const Vector3SSE &li, const Vector3SSE &re) noexcept {
        return li.Dot() < re.Dot();
    }

    //arithmetic operators with Vector3SSE
    friend Vector3SSE operator +(Vector3SSE li, const Vector3SSE &re) noexcept {
        return li += re;
    }

    friend Vector3SSE operator -(Vector3SSE li, const Vector3SSE &re) noexcept {
        return li -= re;
    }

    friend Vector3SSE operator *(Vector3SSE li, const Vector3SSE &re) noexcept {
        return li *= re;
    }


    friend Vector3SSE operator /(Vector3SSE li, const Vector3SSE &re) noexcept {
        return li /= re;
    }

    Vector3SSE &operator +=(const Vector3SSE other) noexcept {
        mmvalue = _mm_add_ps(mmvalue, other.mmvalue);
        return *this;
    }

    Vector3SSE &operator +=(const Vector other) noexcept {
        const Vector3SSE local(other);
        mmvalue = _mm_add_ps(mmvalue, local.mmvalue);
        return *this;
    }

    Vector3SSE &operator -=(const Vector3SSE other) noexcept {
        mmvalue = _mm_sub_ps(mmvalue, other.mmvalue);
        return *this;
    }

    Vector3SSE &operator -=(const Vector other) noexcept {
        const Vector3SSE local(other);
        mmvalue = _mm_sub_ps(mmvalue, local.mmvalue);
        return *this;
    }

    Vector3SSE &operator *=(const Vector3SSE other) noexcept {
        mmvalue = _mm_mul_ps(mmvalue, other.mmvalue);
        return *this;
    }

    Vector3SSE &operator *=(const Vector other) noexcept {
        const Vector3SSE local(other);
        mmvalue = _mm_mul_ps(mmvalue, local.mmvalue);
        return *this;
    }

    Vector3SSE &operator /=(const Vector3SSE other) noexcept {
        mmvalue = _mm_div_ps(mmvalue, other.mmvalue);
        return *this;
    }

    Vector3SSE &operator /=(const Vector other) noexcept {
        const Vector3SSE local(other);
        mmvalue = _mm_div_ps(mmvalue, local.mmvalue);
        return *this;
    }

    //arithmetic operators with float
    Vector3SSE operator +(const float other) const noexcept {
        return Vector3SSE(_mm_add_ps(mmvalue, _mm_set1_ps(other)));
    }

    Vector3SSE operator -(const float other) const noexcept {
        return Vector3SSE(_mm_sub_ps(mmvalue, _mm_set1_ps(other)));
    }

    Vector3SSE operator *(const float other) const noexcept {
        return Vector3SSE(_mm_mul_ps(mmvalue, _mm_set1_ps(other)));
    }

    Vector3SSE operator /(const float other) const noexcept {
        if (other != 0.F)
            return Vector3SSE(_mm_div_ps(mmvalue, _mm_set1_ps(other)));
        return Vector3SSE(_mm_set_ps1(0.F));
    }

    //op= operators with float
    Vector3SSE &operator +=(const float other) noexcept {
        mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(other));
        return *this;
    }

    Vector3SSE &operator -=(const float other) noexcept {
        mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(other));
        return *this;
    }

    Vector3SSE &operator *=(const float other) noexcept {
        mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(other));
        return *this;
    }

    Vector3SSE &operator /=(const float other) noexcept {
        if (other != 0.F)
            mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(other));
        return *this;
    }

    //cross product NO constexpr
    [[nodiscard]] Vector3SSE Cross(const Vector3SSE other) const noexcept {
        return Vector3SSE(_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(other.mmvalue, other.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
                                     _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(other.mmvalue, other.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))));
    }

    void CrossSelf(const Vector3SSE other) noexcept {
        mmvalue = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(other.mmvalue, other.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
                             _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(other.mmvalue, other.mmvalue, _MM_SHUFFLE(3, 0, 2, 1))));
    }

    void CrossSelf(const Vector other) noexcept {
        const Vector3SSE local(other);
        mmvalue = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(local.mmvalue, local.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
                             _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(local.mmvalue, local.mmvalue, _MM_SHUFFLE(3, 0, 2, 1))));
    }

    Vector3SSE operator ^(const Vector3SSE a) const noexcept {
        return Cross(a);
    } //same as Cross

/*
    [[nodiscard]] Vector3SSE Negate() const noexcept {
        constexpr __m128 signs = {-0.F, -0.F, -0.F, -0.F};
        return Vector3SSE(_mm_xor_ps(mmvalue, signs));
    }

    Vector3SSE operator -() const noexcept {
//        constexpr __m128 signs = {-0.F, -0.F, -0.F, -0.F};
        return Vector3SSE(_mm_xor_ps(mmvalue, _mm_set1_ps(-0.0F)));
    } //unary minus
*/

#if defined(__AVX2__)
    [[nodiscard]] float Dot(const Vector3SSE other) const noexcept {
        return _mm_cvtss_f32(_mm_dp_ps(mmvalue, other.mmvalue, 0x7F));
    }

    [[nodiscard]] float Dot() const noexcept {
        return _mm_cvtss_f32(_mm_dp_ps(mmvalue, mmvalue, 0x7F));
    }

    [[nodiscard]] float Norm() const noexcept {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x7F)));
    }

    [[nodiscard]] bool IsZeroVector() noexcept {
#ifdef __clang__
        mmvalue[3] = 1.F;
#else
        mmvalue.m128_f32[3] = 1.F;
#endif
        return _mm_movemask_ps(_mm_cmpeq_ps(mmvalue, zero_m128)) == 0xf;
    }
#else
    [[nodiscard]] float Dot(const Vector3SSE other) const noexcept {
        return _mm_cvtss_f32(dot3(mmvalue, other.mmvalue));
    }

    [[nodiscard]] float Dot() const noexcept {
        return _mm_cvtss_f32(dot3(mmvalue, mmvalue));
    }

    [[nodiscard]] float Norm() const noexcept {
        return _mm_cvtss_f32(_mm_sqrt_ss(dot3(mmvalue, mmvalue)));
    }
#endif

    void FixNormalizedVector() noexcept {
        //fix when Normalize returns a Vector like this (0,1.000,1e-6)
        const Vector3SSE temp = Absolute();
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

    Vector3SSE &FixedNormalize() noexcept {
        const float square = hash_math::sqrt(x * x + y * y + z * z);
        if (square != 0.F && (square > 1.000001F || square < 0.99999F)) {
            *this /= square;
            const float vsum = hash_math::abs(x + y + z);
            if (vsum > 1.F && vsum < 1.0001F)
                FixNormalizedVector();
        }
        return *this;
    }

    Vector FixedNormalizeToVector() noexcept {
        const float square = hash_math::sqrt(x * x + y * y + z * z);
        if (square != 0.F && (square > 1.000001F || square < 0.99999F)) {
            *this /= square;
            const float vsum = hash_math::abs(x + y + z);
            if (vsum > 1.F && vsum < 1.0001F)
                FixNormalizedVector();
        }
        return Vector(x,y,z);
    }

    Vector3SSE &Normalize() noexcept {
        const float square = Dot();
        return square != 0.F ? *this /= hash_math::sqrt(square) : *this;
    }

    float NormalizeLength() noexcept {
        const float length_local = Norm();
        if (length_local < 1e-10F) {
            return 0.F;
        }
        *this /= length_local;
        return length_local;
    }

    friend void swap(Vector3SSE &a, Vector3SSE &b) noexcept {
        const Vector3SSE tmp(a);
        a = b;
        b = tmp;
    }

    friend float Dot(const Vector3SSE a, const Vector3SSE b) noexcept {
        return a.Dot(b);
    }

    friend Vector3SSE Cross(const Vector3SSE a, const Vector3SSE b) noexcept {
        return a.Cross(b);
    }

    [[nodiscard]] Vector3SSE Absolute() const noexcept {
        const __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
        return Vector3SSE(_mm_and_ps(mmvalue, mask));
    }

    [[nodiscard]] bool IsLess(const float minvalue) const noexcept {
        const __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
        const auto a = Vector3SSE(_mm_and_ps(mmvalue, mask));
        if (a.x > minvalue)
            return false;
        if (a.y > minvalue)
            return false;
        if (a.z > minvalue)
            return false;
        return true;
    }

    void PushMinMax(Vector3SSE &minv, Vector3SSE &maxv) const noexcept {
        minv.mmvalue = _mm_min_ps(mmvalue, minv.mmvalue);
        maxv.mmvalue = _mm_max_ps(mmvalue, maxv.mmvalue);
    }

    constexpr friend Vector3SSE Min(const Vector3SSE left, const Vector3SSE right) noexcept {
        return Vector3SSE(_mm_min_ps(left.mmvalue, right.mmvalue));
    }

    constexpr friend Vector3SSE Max(const Vector3SSE left, const Vector3SSE right) noexcept {
        return Vector3SSE(_mm_max_ps(left.mmvalue, right.mmvalue));
    }

#ifdef _DEBUG
    [[nodiscard]] bool IsValid() const {
        // NOLINT(modernize-use-nodiscard)
        if (!IsFinite(x))
            return false;
        if (!IsFinite(y))
            return false;
        if (!IsFinite(z))
            return false;
        return true;
    }
#endif
    friend std::ostream &operator<<(std::ostream &os, const Vector3SSE &val) {
        os << val.x << " " << val.y << " " << val.z;
        return os;
    }

};

HASH_INLINE Vector3SSE operator +(const float a, const Vector3SSE b) noexcept {
    return b + a;
}

HASH_INLINE Vector3SSE operator -(const float a, const Vector3SSE b) noexcept {
    return Vector3SSE(_mm_set1_ps(a)) - b;
}

HASH_INLINE Vector3SSE operator *(const float a, const Vector3SSE b) noexcept {
    return b * a;
}

HASH_INLINE Vector3SSE operator /(const float a, const Vector3SSE b) noexcept {
    return Vector3SSE(_mm_set1_ps(a)) / b;
}

HASH_INLINE void PushMinMax(const Vector p, Vector3SSE &minv, Vector3SSE &maxv) noexcept {
    minv.mmvalue = _mm_min_ps(Vector3SSE(p).mmvalue, minv.mmvalue);
    maxv.mmvalue = _mm_max_ps(Vector3SSE(p).mmvalue, maxv.mmvalue);
}
