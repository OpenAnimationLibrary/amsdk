// ReSharper disable CppUnusedIncludeDirective
#pragma once

#include "StdAfx.h"
#include "FileCons.h"

#ifndef __AFX_H__
#include <afx.h>
#endif

#ifndef _CSTDINT_
#include <cstdint>
#endif

#ifndef _LIMITS_
#include <limits>
#endif

#ifndef _NUMBERS_
#include <numbers>
#endif

#pragma warning(push)
#pragma warning(disable: 4056)
namespace hash_constants {
    //integer constants
    constexpr int big_int = 2147483647;
    constexpr uint32_t max_uint = std::numeric_limits<uint32_t>::max();//0xffffffffui32;
    constexpr uint64_t max_ulonglong = std::numeric_limits<uint64_t>::max();//0xffffffffffffffffui64; 

    //float constants
    constexpr float big_float = 1e8F;
    constexpr float minus_big_float = -1e8F;
    constexpr float smalltan = 1.0e-6F;
    constexpr float max_float = std::numeric_limits<float>::max();//3.402823466e+38F;
    constexpr float pi =  std::numbers::pi_v<float>;//3.141592653589793F; // pi
    constexpr float pi_2 =  std::numbers::pi_v<float> * 2.F; // pi multiplicate 2
    constexpr float pi_div2 = std::numbers::pi_v<float> / 2.F; // pi divided 2
    constexpr float pi_div8 = std::numbers::pi_v<float> / 8.F; // pi divided 8
    constexpr float sqrt2 = std::numbers::sqrt2_v<float>;//1.4142135623731F; // square root of two
    constexpr float sqrt3 = std::numbers::sqrt3_v<float>;//1.73205076F; // square root of three
    constexpr float reci_sqrt3 = std::numbers::inv_sqrt3_v<float>;//0.57735027F; // reciproke square root of three
    constexpr float e2 = std::numbers::e_v<float> *-2.F;//2.7182818F * -2.F; // -2e
    constexpr float gravity = 980.665F; // 980.665 CM/SEC/SEC
    constexpr float radians = 57.29578F;
    constexpr float inverse_radians = 1.F/57.29578F;
    constexpr float small_float = 0.001F;

    //double constants
    constexpr double big_int_double = 2147483647.;
    constexpr double double_sqrt2 = 1.41421356237309504880; // square root of two
    constexpr double double_pi = 3.14159265358979323846; // pi
}

#if defined(__AVX2__)
#include <intrin.h>
#endif

template <typename T1>
bool IsFinite(T1 d) noexcept {
    return isfinite(d);
}

HASH_INLINE bool IsFinite(const float d) noexcept {
    return isfinite(d);
}

namespace hash_math {
    template <typename T>
    T abs(T a) noexcept {
        return a < 0 ? -a : a;
    }

    template <typename T>
    T sqr(const T x) noexcept {
        return x * x;
    }

    constexpr float sqr(const float x) noexcept {
        return x * x;
    }

    constexpr int sqrt(const int x) noexcept {
        return x > 0 ? (int)::sqrt((double)x) : 0;
    }

#ifdef _DEBUG
    HASH_INLINE float rcp(const float x) noexcept {
        ASSERT(IsFinite(x));
#else
    constexpr float rcp(const float x) noexcept {
#endif
        return x != 0.F ? 1.F / x : 0.F;
    }

    HASH_INLINE float sqrt(const float x) noexcept {
        ASSERT(IsFinite(x));
        return x > 0.F ? ::sqrtf(x) : 0.F;
    }

    HASH_INLINE float abs(const float x) noexcept {
        return fabsf(x);
    }

    HASH_INLINE float acos(const float x) noexcept {
        ASSERT(IsFinite(x));
        ASSERT(x <= 1.F && x >= -1.F);
        return acosf(x);
    }

    HASH_INLINE float asin(const float x) noexcept {
        ASSERT(IsFinite(x));
        ASSERT(x <= 1.F && x >= -1.F);
        return asinf(x);
    }

    HASH_INLINE float atan(const float x) noexcept {
        return atanf(x);
    }

    HASH_INLINE float atan2(const float y, const float x) noexcept {
        return atan2f(y, x);
    }

    HASH_INLINE float cos(const float x) noexcept {
        return cosf(x);
    }

    HASH_INLINE float cosh(const float x) noexcept {
        return coshf(x);
    }

    HASH_INLINE float exp(const float x) noexcept {
        return expf(x);
    }

    HASH_INLINE float fmod(const float x, const float y) noexcept {
        return fmodf(x, y);
    }

    HASH_INLINE float log(const float x) noexcept {
        return logf(x);
    }

    HASH_INLINE float log10(const float x) noexcept {
        return log10f(x);
    }

    HASH_INLINE float pow(const float x, const float y) noexcept {
        return powf(x, y);
    }

    HASH_INLINE float sin(const float x) noexcept {
        return sinf(x);
    }

    HASH_INLINE float sinh(const float x) noexcept {
        return sinhf(x);
    }

    HASH_INLINE float tan(const float x) noexcept {
        return tanf(x);
    }

    HASH_INLINE float tanh(const float x) noexcept {
        return tanhf(x);
    }

    HASH_INLINE float floor(const float x) noexcept {
        return floorf(x);
    }

    HASH_INLINE float ceil(const float x) noexcept {
        return ceilf(x);
    }

    HASH_INLINE float frac(const float x) noexcept {
        return x - floor(x);
    }

    // version for double
    HASH_INLINE double abs(const double x) noexcept {
        return fabs(x);
    }

    HASH_INLINE double acos(const double x) noexcept {
        return ::acos(x);
    }

    HASH_INLINE double asin(const double x) noexcept {
        return ::asin(x);
    }

    HASH_INLINE double atan(const double x) noexcept {
        return ::atan(x);
    }

    HASH_INLINE double atan2(const double y, const double x) noexcept {
        return ::atan2(y, x);
    }

    HASH_INLINE double cos(const double x) noexcept {
        return ::cos(x);
    }

    HASH_INLINE double cosh(const double x) noexcept {
        return ::cosh(x);
    }

    HASH_INLINE double exp(const double x) noexcept {
        return ::exp(x);
    }

    HASH_INLINE double fmod(const double x, const double y) noexcept {
        return ::fmod(x, y);
    }

    HASH_INLINE double log(const double x) noexcept {
        return ::log(x);
    }

    HASH_INLINE double log10(const double x) noexcept {
        return ::log10(x);
    }

    HASH_INLINE double pow(const double x, const double y) noexcept {
        return ::pow(x, y);
    }

#ifdef _DEBUG
    HASH_INLINE double rcp(const double x) noexcept {
        ASSERT(IsFinite(x));
#else
    constexpr double rcp(const double x) noexcept {
#endif
        return x != 0. ? 1. / x : 0.;
    }

    HASH_INLINE double sin(const double x) noexcept {
        return ::sin(x);
    }

    HASH_INLINE double sinh(const double x) noexcept {
        return ::sinh(x);
    }

    constexpr double sqr(const double x) noexcept {
        return x * x;
    }

    HASH_INLINE double sqrt(const double x) noexcept {
        ASSERT(IsFinite(x));
        return x > 0.F ? ::sqrt(x) : 0.F;
    }

    HASH_INLINE double tan(const double x) noexcept {
        return ::tan(x);
    }

    HASH_INLINE double tanh(const double x) noexcept {
        return ::tanh(x);
    }

    HASH_INLINE double floor(const double x) noexcept {
        return ::floor(x);
    }

    HASH_INLINE double ceil(const double x) noexcept {
        return ::ceil(x);
    }
}

//replacement for float ==
HASH_INLINE bool floatEQ(const float f1, const float f2) noexcept {
#ifdef _DEBUG
    const __m128 compare1 = _mm_cmpeq_ss(_mm_set_ss(f1), _mm_set_ss(f2));
    const bool t1 = (bool)_mm_movemask_ps(compare1);
    const bool t2 = f1 == f2;
    ASSERT(t1==t2);
#endif
    const __m128 compare = _mm_cmpeq_ss(_mm_set_ss(f1), _mm_set_ss(f2));
    return (bool)_mm_movemask_ps(compare);
}

//replacement for float !=
HASH_INLINE bool floatNEQ(const float f1, const float f2) noexcept {
#ifdef _DEBUG
    const __m128 compare1 = _mm_cmpneq_ss(_mm_set_ss(f1), _mm_set_ss(f2));
    const bool t1 = (bool)_mm_movemask_ps(compare1);
    const bool t2 = f1 != f2;
    ASSERT(t1==t2);
#endif
    const __m128 compare = _mm_cmpneq_ss(_mm_set_ss(f1), _mm_set_ss(f2));
    return (bool)_mm_movemask_ps(compare);
}

//replacement for double ==
HASH_INLINE bool doubleEQ(const double f1, const double f2) noexcept {
#ifdef _DEBUG
    const __m128d compare1 = _mm_cmpeq_sd(_mm_set_sd(f1), _mm_set_sd(f2));
    const bool t1 = (bool)_mm_movemask_pd(compare1);
    const bool t2 = f1 == f2;
    ASSERT(t1==t2);
#endif
    const __m128d compare = _mm_cmpeq_sd(_mm_set_sd(f1), _mm_set_sd(f2));
    return (bool)_mm_movemask_pd(compare);
}

//replacement for float !=
HASH_INLINE bool doubleNEQ(const double f1, const double f2) noexcept {
#ifdef _DEBUG
    const __m128d compare1 = _mm_cmpneq_sd(_mm_set_sd(f1), _mm_set_sd(f2));
    const bool t1 = (bool)_mm_movemask_pd(compare1);
    const bool t2 = f1 != f2;
    ASSERT(t1==t2);
#endif
    const __m128d compare = _mm_cmpneq_sd(_mm_set_sd(f1), _mm_set_sd(f2));
    return (bool)_mm_movemask_pd(compare);
}

constexpr float fast_ftol_signedf(const float d) noexcept {
    return static_cast<float>(static_cast<int>(d));
}

HASH_INLINE float fast_ftol_unsignedf(const float d) noexcept {
    return fabsf(truncf(d));
}

template <typename T1>
int fast_ftol_signed(T1 d) noexcept {
    return static_cast<int>(d);
}

HASH_INLINE int fast_ftol_signed(const float d) noexcept {
    return _mm_cvtt_ss2si(_mm_set_ss(d));
}

HASH_INLINE int fast_ftol_signed(const double d) noexcept {
    return _mm_cvttsd_si32(_mm_set_sd(d));
}

template <typename T1>
int fast_ftol_unsigned(T1 d) noexcept {
    return abs(static_cast<int>((float)d));
}

HASH_INLINE int fast_ftol_unsigned(const float d) noexcept {
    return hash_math::abs(_mm_cvtt_ss2si(_mm_set_ss(d)));
}

HASH_INLINE int fast_ftol_unsigned(const double d) noexcept {
    return hash_math::abs(_mm_cvttsd_si32(_mm_set_sd(d)));
}

template <typename T1>
int64_t fast_ftol_unsigned_longlong(const T1 d) noexcept {
    //for time::ticks
    return hash_math::abs(static_cast<int64_t>(d));
}

// faster than normal ::floor/::floorf
//rounding down to int (example 2.9 -> 2)
template <typename T1>
int fast_floor(T1 d) noexcept {
    return static_cast<int>(hash_math::floor(d));
}

#if defined(__AVX2__)
HASH_INLINE int fast_floor(const float d) noexcept {
    return _mm_cvtt_ss2si(_mm_round_ps(_mm_load_ss(&d), (_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC)));
}

HASH_INLINE int fast_floor(const double d) noexcept {
    return _mm_cvttsd_si32(_mm_round_pd(_mm_load_sd(&d), (_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC)));
}
#endif


//rounding to the nearest int (example 2.9 -> 3)
template <typename T1>
int fast_round(T1 d) noexcept {
    if (d < 0) {
        return static_cast<int>(d - 0.5);
    }
    return static_cast<int>(d + 0.5); // NOLINT(bugprone-incorrect-roundings)
}

#if defined(__AVX2__)
HASH_INLINE int fast_round(const float d) noexcept {
    return _mm_cvtt_ss2si(_mm_round_ps(_mm_load_ss(&d), (_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC)));
}

HASH_INLINE int fast_round(const double d) noexcept {
    return _mm_cvttsd_si32(_mm_round_pd(_mm_load_sd(&d), (_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC)));
}
#endif

#pragma warning(pop)
