//BC  4/25/2003  \Bob105\Include\TimeRang.h
// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "HashTime.h"
#include <algorithm>
#include <vector>

#define NEVER   TimeRange(TimeRange::RangeType::RT_NEVER)// NOLINT(cppcoreguidelines-macro-usage)
#define FOREVER TimeRange(TimeRange::RangeType::RT_FOREVER)// NOLINT(cppcoreguidelines-macro-usage)

class TimeRange final {
public:
    enum struct RangeType {
        RT_NEVER, RT_FOREVER
    };

    Time m_start{MAX_TICKS};
    Time m_end{MIN_TICKS};

    TimeRange() noexcept = default;

    TimeRange(const int time) noexcept : m_start(time), m_end(time) {}

    TimeRange(const Time time) noexcept : m_start(time), m_end(time) {}

    TimeRange(const TimeRange &other) = default;

    TimeRange(const Time start, const Time end) noexcept : m_start(start), m_end(end) {}

    explicit TimeRange(const RangeType rt) noexcept {
        switch (rt) {
            case RangeType::RT_NEVER:
                SetNever();
                return;
            case RangeType::RT_FOREVER:
                SetForever();
                return;
        }
    }

    ~TimeRange() = default;

    TimeRange &operator=(const TimeRange &other) noexcept {
        if (this == &other)
            return *this;
        m_start = other.m_start;
        m_end = other.m_end;
        return *this;
    }

    TimeRange(TimeRange &&) = default;
    TimeRange &operator=(TimeRange &&) = default;

    void Set(const Time start, const Time end) noexcept {
        m_start = start;
        m_end = end;
    }

    void SetNever() noexcept {
        m_start = MAX_TICKS;
        m_end = MIN_TICKS;
    }

    void SetForever() noexcept {
        m_start = MIN_TICKS;
        m_end = MAX_TICKS;
    }

    [[nodiscard]] Time GetLength() const noexcept {
        return m_end - m_start;
    }

    [[nodiscard]] int GetLengthInFramesInt(const double fps) const noexcept {
        return m_end.GetFrameInt(fps) - m_start.GetFrameInt(fps);
    }

    [[nodiscard]] bool IsValid() const noexcept {
        return m_end >= m_start;
    }

    [[nodiscard]] bool IsIntersect(const TimeRange &range) const noexcept {
        return m_end > range.m_start && m_start < range.m_end;
    }

    [[nodiscard]] bool IsTimeInRange(const Time time) const noexcept {
        return time >= m_start && time <= m_end;
    }

    [[nodiscard]] bool IsTimeWithinRange(const Time time) const noexcept {
        return time > m_start && time < m_end;
    }

    [[nodiscard]] bool IsRangeInRange(const TimeRange &range) const noexcept {
        return range.m_start >= m_start && range.m_end <= m_end;
    }

    [[nodiscard]] bool IsActiveHere(const Time time) const noexcept {
        return time >= m_start && time < m_end;
    }

    void operator |=(const TimeRange &other) noexcept {
        //union
        m_start = MIN(m_start, other.m_start);
        m_end = MAX(m_end, other.m_end);
    }

    void operator |=(const Time time) noexcept {
        //union
        m_start = MIN(m_start, time);
        m_end = MAX(m_end, time);
    }

    void operator &=(const TimeRange &other) noexcept {
        //intersect
        m_start = MAX(m_start, other.m_start);
        m_end = MIN(m_end, other.m_end);
        if (m_start > m_end)
            SetNever();
    }

    void operator &=(const Time time) noexcept {
        //intersect
        if (IsTimeInRange(time)) {
            m_start = time;
            m_end = time;
        } else {
            SetNever();
        }
    }

    void operator +=(const Time time) noexcept {
        //slide
        m_start += time;
        if (m_end != MAXTIME)
            m_end += time;
    }

    TimeRange operator +(const Time time) const noexcept {
        TimeRange result(*this);

        result += time;
        return result;
    }

    void operator -=(const Time time) noexcept {
        //slide
        if (m_start != MINTIME)
            m_start -= time;
        m_end -= time;
    }

    TimeRange operator -(const Time time) const noexcept {
        TimeRange result(*this);

        result -= time;
        return result;
    }

    void operator *=(const float n) noexcept {
        //scale
        m_start *= n;
        m_end *= n;
    }

    TimeRange operator *(const float n) const noexcept //scale
    {
        TimeRange result(*this);

        result *= n;
        return result;
    }

    void Union(const Time time) noexcept {
        m_start = MIN(m_start, time);
        m_end = MAX(m_end, time);
    }

    [[nodiscard]] bool IsInstance() const noexcept {
        return m_start == m_end;
    }

    constexpr friend bool operator==(const TimeRange &lhs, const TimeRange &rhs) noexcept {
        return lhs.m_start == rhs.m_start && lhs.m_end == rhs.m_end;
    }

    constexpr friend bool operator!=(const TimeRange &lhs, const TimeRange &rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const TimeRange &val) {
        os << val.m_start << " " << val.m_end;
        return os;
    }
};

class TimeLineSelection final {
public:
    TimeRange m_timerange;
    std::vector<int> m_linearray;

    TimeLineSelection() noexcept = default;
    ~TimeLineSelection() = default;

    TimeLineSelection(const TimeLineSelection &other) noexcept {
        *this = other;
    }

    TimeLineSelection(const Time start, const Time end) noexcept {
        m_timerange.m_start = start;
        m_timerange.m_end = end;
    }

    explicit TimeLineSelection(TimeRange range) noexcept : m_timerange(std::move(range)) {}

    TimeLineSelection(TimeLineSelection &&other) noexcept {
        *this = other;
    }

    TimeLineSelection &operator=(TimeLineSelection &&other) noexcept {
        if (this == &other)
            return *this;
        *this = other;
        return *this;
    }

    void Clear() noexcept {
        m_timerange.SetNever();
        m_linearray.clear();
    }

    void operator +=(const TimeLineSelection &other) {
        //union
        m_timerange |= other.m_timerange;
        for (int i : other.m_linearray) {
            if (!IsInSelection(i))
                m_linearray.push_back(i);
        }
    }

    void operator +=(const int line) {
        if (line >= 0 && !IsInSelection(line))
            m_linearray.push_back(line);
    }

    TimeLineSelection &operator=(const TimeLineSelection &other) noexcept { // NOLINT(bugprone-exception-escape)
        if (this == &other)
            return *this;
        m_timerange = other.m_timerange;
        m_linearray.clear();
        for (int i : other.m_linearray) {
            m_linearray.push_back(i);
        }
        return *this;
    }

    [[nodiscard]] bool IsInSelection(const int line) const noexcept {
#ifdef _DEBUG
        bool test = std::ranges::any_of(m_linearray, [line](int i) { return i == line; });
#endif
        for (int i : m_linearray) {
            if (i == line) {
#ifdef _DEBUG
                ASSERT(test == true);
#endif
                return true;
            }
        }
#ifdef _DEBUG
        ASSERT(test == false);
#endif
        return false;
    }

    void SetLineRange(const int first, const int last) {
        m_linearray.clear();
        m_linearray.push_back(first);
        m_linearray.push_back(last);
    }
};

class TimeLineRect final {
public:
    TimeRange m_timerange;
    int m_top;
    int m_bottom;

    TimeLineRect() noexcept : m_timerange(0), m_top(hash_constants::big_int), m_bottom(-hash_constants::big_int) {}

    TimeLineRect(const Time start, const Time end, const int top = hash_constants::big_int, const int bottom = -hash_constants::big_int) noexcept : m_timerange(start, end), m_top(top), m_bottom(bottom) {}

    void Clear() noexcept {
        m_timerange.SetNever();
        m_top = hash_constants::big_int;
        m_bottom = -hash_constants::big_int;
    }

    void operator |=(const TimeLineRect &other) noexcept {
        //union
        m_timerange |= other.m_timerange;
        m_top = MIN(m_top, other.m_top);
        m_bottom = MAX(m_bottom, other.m_bottom);
    }

    void operator |=(const TimeLineSelection &other) noexcept {
        //union
        m_timerange |= other.m_timerange;
        for (const int i : other.m_linearray) {
            m_top = MIN(m_top, i);
            m_bottom = MAX(m_bottom, i);
        }
    }
};
