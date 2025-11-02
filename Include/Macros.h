//BC  2/4/2004  \Bob110\Include\Macros.h
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

#include "StdAfx.h"
/* unused
HASH_INLINE bool CompareZero(float f) noexcept {
    const int fi = *reinterpret_cast<int *>(&f);
    return (fi & 0x7fffffff) <= 4u;
}
*/

HASH_INLINE bool is_prime(const UINT x) noexcept {
    for (UINT i = 3; true; i += 2) {
        const UINT q = x / i;
        if (q < i)
            return true;
        if (x == q * i)
            return false;
    }
}

HASH_INLINE UINT Next_Prime(UINT x) noexcept {
    if (x <= 2)
        return 2;
    if (!(x & 1U))
        ++x;
    for (; !is_prime(x); x += 2) {}
    return x;
}

template <typename T>
int SIGN(const T a) noexcept {
    return a < 0 ? -1 : 1;
}

constexpr int SIGN(const float a) noexcept {
    return a < 0.F ? -1 : 1;
}

constexpr int SIGN(const double a) noexcept {
    return a < 0. ? -1 : 1;
}

constexpr float SIGN_FLOAT(const float a) noexcept {
    return a < 0.F ? -1.F : 1.F;
}

constexpr double SIGN_DOUBLE(const double a) noexcept {
    return a < 0. ? -1. : 1.;
}

HASH_INLINE void Round(float &in, const double multiple) noexcept {
    const auto f_multiple = (float)multiple;
    const float epsilon = std::numeric_limits<float>::epsilon() * f_multiple;
    const float incr = signbit(in) ? -epsilon : epsilon;
    in = roundf((in + incr) / f_multiple) * f_multiple;
}

HASH_INLINE void Round(double &in, const double multiple) noexcept {
    const double epsilon = std::numeric_limits<double>::epsilon() * multiple;
    const double incr = signbit(in) ? -epsilon : epsilon;
    in = round((in + incr) / multiple) * multiple;
}

HASH_INLINE float RoundValue(const float number, const float modulo) noexcept {
    float rvalue(number);
    Round(rvalue, modulo);
    return rvalue;
}

#ifdef MAX
#undef MAX
#endif
template <typename T>
constexpr T MAX(const T a, const T b) noexcept {
    return a > b ? a : b;
}
#ifdef MIN
#undef MIN
#endif
template <typename T>
constexpr T MIN(const T a, const T b) noexcept {
    return a < b ? a : b;
}

template <typename T1>
long RoundValue(const T1 number) {
    return lrint(number);
}

template <typename T1>
int64_t RoundValueLL(const T1 number) noexcept {
    return llrint(number);
}

// Swaps the two values.
template <typename T1>
void SWAP(T1 &a, T1 &b) noexcept {
    const T1 tmp = a;
    a = b;
    b = tmp;
}

template <typename T1>
unsigned int fast_log2floor(const T1 d) {
    return static_cast<unsigned int>(hash_math::log(d) / 0.69314718f);
}

template <typename T1>
float fast_log2trunc(const T1 d) {
    float ret = static_cast<float>(d);
    const auto pret = reinterpret_cast<int *>(&ret);
    *pret = *pret & 0xFF800000;
    return ret;
}

/*
template<typename T>
T lerp(T t, T a, T b) {
    ASSERT(false && "check for std::lerp");
    return a + t * (b - a);
}
*/

HASH_INLINE UINT fast_round_to_UINT(const float d) noexcept {
    return (UINT)lroundf(d);
}

template <typename T1, typename T2>
float safe_pow(const T1 a, const T2 b) {
    const float result = hash_math::pow(a, b);
    if (IsFinite(result))
        return result;
    return 0.F;
}

template <class T>
void hash_combine(size_t &seed1, const T v) noexcept {
    std::hash<T> hasher;
    seed1 ^= hasher(v) + 0x9e3779b9 + (seed1 << 6) + (seed1 >> 2);
}

template <typename T>
constexpr auto ISODD(T x) {
    return x & 0x01;
} //shag and plugin

template <typename T>
constexpr auto FLOOR_INT(T a) {
    return a > 0 ? static_cast<int>(a) : -static_cast<int>(-a);
} // some plugins;

template <typename T>
constexpr auto ROUNDOFF(T A) {
    return static_cast<int>(A < 0 ? A - .5 : A + .5);
} // some plugins;

template <typename T>
constexpr auto ROWBYTES(T A) {
    return (A + 15) >> 4 << 1;
} //bitmap

//#define ROWWORDS(A)            (((A)+15) >> 4) //unused
//#define PADWIDTH(x)            ((((x) * 8 + 31) & (~31)) / 8) //unused
//#define CEILING_INT(a)         ((a) == (int)(a) ? (a) : (a) > 0 ? 1 + (int)(a) : -(1 + (int)(-(a)))) //unused
//#define INVERSE(A)             { (A).x = -(A).x; (A).y = -(A).y; (A).z = -(A).z; }//unused
//#define NULLDELETE(a)          { delete (a); (a) = nullptr; } //unused
//#define FI(f)                  (*((int *)&(f)))//unused
//#define IsFloatZero(f)         ((FI(f) << 1) == 0)//unused
//#define FLOATSIGNBITSET(f)     ((*(const unsigned long *)&(f)) >> 31)        //unused
//#define FLOATSIGNBITNOTSET(f)  ((~(*(const unsigned long *)&(f))) >> 31)     //unused
//#define FLOATNOTZERO(f)        ((*(const unsigned long *)&(f)) & ~(1 << 31)) //unused

//#define STRINGIFY_APPEND(a, b) "" a # b
//#define STRINGIFY(x)           STRINGIFY_APPEND("", x)

#ifdef _DOCUMENT
#define DOC(A)                 _T(A)
#define MENU_DOC(A, B)         static MenuDoc f_ ## A(A, DOC(B))
//#define DOC_LEVEL(A, L)        static DocLevel f_ ## A_level(A, L)
#else
#define DOC(A)                 ""
#define MENU_DOC(A, B)
//#define DOC_LEVEL(A, L)
#endif

class MenuDoc;
void AddMenuDoc(MenuDoc *menudoc);

class MenuDoc final {
public:
    UINT m_id;
    char *m_documentation;

    MenuDoc(const UINT menuid, char *documentation) : m_id{menuid},
                                                      m_documentation{documentation} {
        AddMenuDoc(this);
    }
};

void *GetMenuDocMap();

class DocLevel;
void AddDocLevel(DocLevel *doclevel);

class DocLevel final {
public:
    UINT m_id;
    int m_level;

    DocLevel(const UINT id, const int level) : m_id(id),
                                               m_level(level) {
        AddDocLevel(this);
    }
};

void *GetDocLevelMap();

#if defined(_DEBUG)
#define ODS(s) OutputDebugStringA(s)
HASH_INLINE void ODSF(const char *format, ...) {
    constexpr int TraceBufferSize = 2048;
    char szBuf[TraceBufferSize];
    va_list argptr;
    va_start(argptr, format);
    vsprintf_s(szBuf, TraceBufferSize, format, argptr); // NOLINT(cert-err33-c)
    va_end(argptr);
    ::OutputDebugString(szBuf);
}
#else
HASH_INLINE void ODSF(const char *, ...) noexcept {}
#define ODS(s)
#endif

HASH_INLINE void ODSF_Rel(const char *format, ...) {
    constexpr int TraceBufferSize = 2048;
    char szBuf[TraceBufferSize];
    va_list argptr;
    va_start(argptr, format);
    vsprintf_s(szBuf, TraceBufferSize, format, argptr); // NOLINT(cert-err33-c)
    va_end(argptr);
    ::OutputDebugString(szBuf);
}

template <class F>
class final_act {
public:
    explicit final_act(F f) noexcept : f_(std::move(f)) {}

    final_act(final_act &&other) noexcept : f_(std::move(other.f_)), invoke_(other.invoke_) {
        other.invoke_ = false;
    }

    final_act(const final_act &) = delete;
    final_act &operator=(const final_act &) = delete;
    final_act &operator=(final_act &&) = delete;

    ~final_act() noexcept {
        if (invoke_)
            f_();
    }

private:
    F f_;
    bool invoke_{true};
};
