//BC  3/20/2003  \Bob105\Include\HashTime.h
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

#include "Macros.h"
#include "Exports.h"
#ifndef _IOSTREAM_
#include <iostream>
#endif

#define MAX_TICKS   _I64_MAX
#define MIN_TICKS   _I64_MIN

constexpr int64_t MAX_SECONDS = MAX_TICKS / 13500; //Time::TICKSPERSECOND;

//#define MINTIME     Time( Time::TimeType::TT_MIN )
//#define MAXTIME     Time( Time::TimeType::TT_MAX )
//#define MINTIMESTEP Time( Time::TimeType::TT_MINSTEP )

//const int64_t TICKSPERSECOND = 135000;

class String;

class FILEIOEXPORT Time final {
    int64_t m_ticks{0};

public:
    enum { TICKSPERSECOND = 135000 }; //no const int !

    enum struct TimeType : uint8_t {
        TT_MINSTEP,
        TT_MAX,
        TT_TAGGED,
        TT_MIN
    };

    Time() noexcept = default;

    explicit Time(const int64_t ticks) noexcept : m_ticks(ticks) {}

    explicit Time(const int seconds) noexcept {
        if (seconds == 0)
            m_ticks = 0;
        else
            m_ticks = RoundValueLL(seconds * (int)TICKSPERSECOND);
    }

    explicit Time(const float seconds) noexcept {
        if (seconds == 0.F)
            m_ticks = 0;
        else
            m_ticks = RoundValueLL(seconds * (float)TICKSPERSECOND);
    }

    explicit Time(const double seconds) noexcept {
        if (seconds == 0.)
            m_ticks = 0;
        else
            m_ticks = RoundValueLL(seconds * (double)TICKSPERSECOND);
    }

    explicit Time(const TimeType rt) noexcept {
        switch (rt) {
        case TimeType::TT_MINSTEP:
            SetMinStep();
            break;
        case TimeType::TT_MAX:
            SetMax();
            break;
        case TimeType::TT_TAGGED:
            SetTagged();
            break;
        case TimeType::TT_MIN:
            SetMin();
            break;
        }
    }

    Time(const double frame, const double fps) noexcept {
        SetSeconds(frame / fps);
    }

    Time &operator=(const int64_t ticks) noexcept {
        m_ticks = ticks;
        return *this;
    }

    Time &operator=(const int seconds) noexcept {
        m_ticks = RoundValueLL(seconds * (int)TICKSPERSECOND);
        return *this;
    }

    Time &operator=(const float seconds) noexcept {
        m_ticks = RoundValueLL(seconds * (float)TICKSPERSECOND);
        return *this;
    }

    Time &operator=(const double seconds) noexcept {
        m_ticks = RoundValueLL(seconds * (double)TICKSPERSECOND);
        return *this;
    }

    Time &operator=(const Time &other) noexcept = default;
    ~Time() = default;

    Time(const Time &) noexcept = default;
    Time(Time &&) noexcept = default;
    Time &operator=(Time &&) noexcept = default;

    Time operator +(const Time other) const noexcept {
        Time result(*this);
        result.m_ticks += other.m_ticks;
        return result;
    }

    Time operator -(const Time other) const noexcept {
        Time result(*this);
        result.m_ticks -= other.m_ticks;
        return result;
    }

    Time operator *(const Time other) const noexcept {
        //        const double c = static_cast<double>(GetSeconds()) * static_cast<double>(other.GetSeconds()); //this used to multiply ticks, but that very quickly overflowed the int, (when squaring time)
        //        return Time(c);
        const int64_t res = m_ticks * other.m_ticks;
        return Time(res);
    }

    Time operator *(const double n) const noexcept {
        Time result(*this);
        result.m_ticks = RoundValueLL(result.m_ticks * n);
        return result;
    }

    float operator /(const Time other) const noexcept {
        if (other.m_ticks)
            return static_cast<float>(m_ticks) / static_cast<float>(other.m_ticks);
        return 0.F;
    }

    Time operator /(const double n) const noexcept {
        if (n < 1e-30)
            return Time();
        Time result(*this);
        result.m_ticks = RoundValueLL(result.m_ticks / n);
        return result;
    }

    Time operator %(const Time other) const noexcept {
        Time result(*this);
        if (other.m_ticks)
            result.m_ticks %= other.m_ticks;
        return result;
    }

    void operator +=(const Time other) noexcept {
        m_ticks += other.m_ticks;
    }

    void operator -=(const Time other) noexcept {
        m_ticks -= other.m_ticks;
    }

    void operator *=(const Time other) noexcept {
        m_ticks *= other.m_ticks;
    }

    void operator *=(const double n) noexcept {
        m_ticks = RoundValueLL(m_ticks * n);
    }

    void operator /=(const Time other) noexcept {
        m_ticks /= other.m_ticks;
    }

    void operator /=(const double n) noexcept {
        ASSERT(n != 0.);
        m_ticks = RoundValueLL(m_ticks / n);
    }

    Time operator -() const noexcept {
        Time result(*this);
        result.m_ticks = -result.m_ticks;
        return result;
    }

    void Invert() noexcept {
        m_ticks = -m_ticks;
    }

    [[nodiscard]] float GetSeconds() const noexcept {
        if (IsZero())
            return 0.F;
        return static_cast<float>((double)m_ticks / (double)TICKSPERSECOND);
    }

    [[nodiscard]] double GetSecondsDouble() const noexcept {
        if (IsZero())
            return 0.;
        return ((double)m_ticks / (double)TICKSPERSECOND);
    }

    void SetSeconds(const double seconds) noexcept {
        m_ticks = RoundValueLL(seconds * (float)TICKSPERSECOND);
    }

    [[nodiscard]] int64_t GetTicks() const noexcept {
        return m_ticks;
    }

    [[nodiscard]] float GetTicksAsFloat() const noexcept {
        return static_cast<float>(m_ticks);
    }

    void SetTicks(const int64_t ticks) noexcept {
        m_ticks = ticks;
    }

    void AddTicks(const int64_t ticks) noexcept {
        m_ticks += ticks;
    }

    [[nodiscard]] bool IsZero() const noexcept {
        return m_ticks == 0LL;
    }

    [[nodiscard]] float GetFrame(const double fps) const noexcept {
        return static_cast<float>(GetSecondsDouble() * fps);
    }

    [[nodiscard]] int GetFrameInt(const double fps) const noexcept {
        return fast_ftol_signed(GetSecondsDouble() * fps + 0.5);
    }

    void SetFrame(const double frame, const double fps) noexcept {
        SetSeconds(frame / fps);
    }

    void StepFrame(const double fps) noexcept {
        m_ticks += RoundValueLL(1.0 / fps * (double)TICKSPERSECOND);
    }

    void StepFrameBack(const double fps) noexcept {
        m_ticks -= RoundValueLL(1.0 / fps * (double)TICKSPERSECOND);
    }

    void StepFrames(const double frames, const double fps) noexcept {
        m_ticks += RoundValueLL(1.0 / fps * (double)TICKSPERSECOND * frames);
    }

    void StepFramesBack(const double frames, const double fps) noexcept {
        m_ticks -= RoundValueLL(1.0 / fps * (double)TICKSPERSECOND * frames);
    }

    void SnapToFrame(const double fps) noexcept {
        const int64_t oneframe = RoundValueLL(1.0 / fps * (double)TICKSPERSECOND);
        m_ticks += (int64_t)(SIGN(m_ticks) * 0.5 * oneframe);
        m_ticks -= m_ticks % oneframe;
    }

    void FloorToFrame(const double fps) noexcept {
        const int64_t oneframe = RoundValueLL(1.0 / fps * (double)TICKSPERSECOND);
        m_ticks -= m_ticks % oneframe;
    }

    void CeilToFrame(const double fps) noexcept {
        const int64_t oneframe = RoundValueLL(1.0 / fps * (double)TICKSPERSECOND);
        if (const int64_t modulus = m_ticks % oneframe; modulus)
            m_ticks += oneframe - modulus;
    }

    [[nodiscard]] bool IsOnFrame(const double fps) const noexcept {
        const int64_t oneframe = RoundValueLL(1.0 / fps * (double)TICKSPERSECOND);
        if (const int64_t modulus = m_ticks % oneframe; modulus) {
            return false;
        }
        return true;
    }

    void MoveToFrame(const double fps, const Time direction) noexcept {
        direction.m_ticks > 0 ? CeilToFrame(fps) : FloorToFrame(fps);
    }

    [[nodiscard]] float GetCell(const double fps) const noexcept {
        return GetFrame(fps) + 1.F;
    }

    void SetCell(const double cell, const double fps) noexcept {
        SetFrame(cell - 1.0, fps);
    }

    [[nodiscard]] String ToString(double fps, TimeUnit timeunits, bool treatasdelta = false) const;

    friend Time operator *(double n, Time right) noexcept;

    void SetTagged(const bool state = true) noexcept {
        SetTicks(state ? -1LL : 0LL);
    }

    [[nodiscard]] bool IsTagged() const noexcept {
        return m_ticks == -1LL;
    }

    void SetMax() noexcept {
        SetTicks(MAX_TICKS);
    }

    void SetMin() noexcept {
        SetTicks(MIN_TICKS);
    }

    void SetMinStep() noexcept {
        SetTicks(1);
    }

    [[nodiscard]] bool IsMax() const noexcept {
        return (m_ticks == MAX_TICKS);
    }

    [[nodiscard]] bool IsMin() const noexcept {
        return (m_ticks == MIN_TICKS);
    }

    [[nodiscard]] bool IsMinStep() const noexcept {
        return (m_ticks == -1LL);
    }

    [[nodiscard]] Time GetAbsoluteValue() const noexcept {
        Time rvalue;
        if (m_ticks < 0) {
            rvalue.m_ticks = -m_ticks;
        } else {
            rvalue.m_ticks = m_ticks;
        }
        return rvalue;
    }

    constexpr friend bool operator==(const Time &lhs, const Time &rhs) noexcept {
        return lhs.m_ticks == rhs.m_ticks;
    }

    constexpr friend bool operator!=(const Time &lhs, const Time &rhs) noexcept {
        return lhs.m_ticks != rhs.m_ticks;
    }

    constexpr friend bool operator <(const Time &lhs, const Time &rhs) noexcept {
        return lhs.m_ticks < rhs.m_ticks;
    }

    constexpr friend bool operator >(const Time &lhs, const Time &rhs) noexcept {
        return lhs.m_ticks > rhs.m_ticks;
    }

    constexpr friend bool operator <=(const Time &lhs, const Time &rhs) noexcept {
        return !operator>(lhs, rhs);
    }

    constexpr friend bool operator >=(const Time &lhs, const Time &rhs) noexcept {
        return !operator<(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Time &val) {
        os << val.m_ticks << " " << val.GetSeconds();
        return os;
    }
};

HASH_INLINE Time operator *(const double n, const Time right) noexcept {
    Time result(right);
    result *= n;
    return result;
}

HASH_INLINE Time abs(const Time time) noexcept {
    Time result(time);
    result.SetTicks(hash_math::abs(result.GetTicks()));
    return result;
}

//const Time MINTIME(Time::TimeType::TT_MIN);
//const Time MAXTIME(Time::TimeType::TT_MAX);
//const Time MINTIMESTEP(Time::TimeType::TT_MINSTEP);
inline extern __declspec(selectany) const Time MINTIME(Time::TimeType::TT_MIN);
inline extern __declspec(selectany) const Time MAXTIME(Time::TimeType::TT_MAX);
inline extern __declspec(selectany) const Time MINTIMESTEP(Time::TimeType::TT_MINSTEP);
//const int64_t MAX_SECONDS = MAX_TICKS / TICKSPERSECOND;
