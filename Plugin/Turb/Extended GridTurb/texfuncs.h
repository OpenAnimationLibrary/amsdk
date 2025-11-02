#pragma once
#include "HashMath.h"
/*
#define pulse(a,b,fuzz,x) (smoothstep((a)-(fuzz),(a),(x)) -  smoothstep((b)-(fuzz),(b),(x)))
#define repeat(x,freq)    (mod((x) * (freq), 1.F))
#define udn(x,lo,hi) (smoothstep(.25F, .75F, Noise(x)) * ((hi) - (lo)) + (lo))
#define whichtile(x,freq) (floor((x) * (freq)))
#define odd(x)            (mod((x), 2) == 1)
#define even(x)           (mod((x), 2) == 0)
*/

inline float h_mod(float a, const float b) {
    const int n = (int)(a / b);
    a -= n * b;
    if (a < 0)
        a += b;
    return a;
}

inline float smoothstep(const float a, const float b, float x) {
    if (x < a)
        return 0.F;
    if (x >= b)
        return 1.F;
    x = (x - a) / (b - a); // normalize to [0:1]
    return x * x * (3.F - 2.F * x);
}

template<typename T>
constexpr auto odd(T x) {
    return h_mod(x, 2.F) == 1;
}

template<typename T>
constexpr auto even(T x) {
    return h_mod(x, 2.F) == 0;
}

template<typename T1, typename T2, typename T3, typename T4>
constexpr auto pulse(T1 a, T2 b, T3 fuzz, T4 x) {
    return smoothstep(a - fuzz, a, x) - smoothstep(b - fuzz, b, x);
}

template<typename T1, typename T2>
constexpr auto repeat(T1 x, T2 freq) {
    return h_mod(x * freq, 1.F);
}

template<typename T1, typename T2, typename T3>
constexpr auto udn(T1 x, T2 lo, T3 hi) {
    return smoothstep(.25F, .75F, Noise(x)) * (hi - lo) + lo;
}

template<typename T1, typename T2>
constexpr auto whichtile(T1 x, T2 freq) {
    return hash_math::floor(x * freq);
}

template<typename T1, typename T2>
constexpr auto step(T1 x, T2 y) {
    return y < x ? 0.F : 1.F;
}

inline float distance(float a[3], float b[3]) {
    float c[3];
    c[0] = a[0] - b[0];
    c[1] = a[1] - b[1];
    c[2] = a[2] - b[2];

    return hash_math::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
}

inline int H_Hash(const int k, const int l, const int m) {
    return (k * k * 1312717 + l * l * 976901 + m * m * 897687 + 36 * k + 22 * l + 37 * m + 82168) % 23840231;
}

static float Uniform(const int x, const int y, const int z) {
    return static_cast<float>(H_Hash(x, y, z) & 0xffff) / 0xffff;
}

static int Poisson(const float lambda, const int n, float x) {
    float p = hash_math::exp(-lambda);
    int i;
    for (i = 0; i < n; ++i) {
        x -= p;
        if (x < 0)
            return i;
        p = p * lambda / (i + 1);
    }
    return i;
}

inline float LocalVoronoi(const int x, const int y, const int z, const Vector *p) {
    float closest = 1.F;
    //
    // m = number of points in this cell
    //
    const int m = Poisson(4, 7, Uniform(x, y, z));
    float cc = 0.F;
    for (int i = 0; i < m; ++i) {
        const float px = x + Uniform(x, y, 2 * i + 1);
        const float py = y + Uniform(x, y, 2 * i + 2);
        const float pz = z + Uniform(x, y, 2 * i + 3);
        const float d2 = (px - p->x) * (px - p->x) + (py - p->y) * (py - p->y) + (pz - p->z) * (pz - p->z);
        if (d2 < closest) {
            closest = d2;
            cc = px;
        }
    }
    if (cc < 0.F)
        cc = 1.F - hash_math::abs(cc);
    if (closest > 0.F)
        return cc;
    return 0.F;
}
