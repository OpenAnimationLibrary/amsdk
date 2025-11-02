//RC  8/3/2004  \Sony115\Include\PatchID.h
#pragma once

#include "StrClass.h"

class PatchID {
public:
    UINT m_id1{0};
    UINT m_id2{0};
    UINT m_id3{0};
    UINT m_id4{0};

    PatchID() noexcept = default;
    PatchID(const UINT id1, const UINT id2, const UINT id3, const UINT id4) noexcept : m_id1(id1), m_id2(id2), m_id3(id3), m_id4(id4) {}

    void Offset(const int offset) noexcept {
        m_id1 += offset;
        m_id2 += offset;
        m_id3 += offset;
        m_id4 += offset;
    }

    explicit operator String() const;
};

HASH_INLINE bool operator==(const PatchID &lhs, const PatchID &rhs) noexcept {
    return lhs.m_id1 == rhs.m_id1 && lhs.m_id2 == rhs.m_id2 && lhs.m_id3 == rhs.m_id3 && lhs.m_id4 == rhs.m_id4;
}

HASH_INLINE bool operator!=(const PatchID &lhs, const PatchID &rhs) noexcept {
    return lhs.m_id1 != rhs.m_id1 || lhs.m_id2 != rhs.m_id2 || lhs.m_id3 != rhs.m_id3 || lhs.m_id4 != rhs.m_id4;
}

class PatchID5 final : public PatchID {
public:
    UINT m_id5{0};

    PatchID5() noexcept = default;
    PatchID5(const UINT id1, const UINT id2, const UINT id3, const UINT id4, const UINT id5) noexcept : PatchID(id1, id2, id3, id4), m_id5(id5) {}

    PatchID5 &operator=(const PatchID &other) noexcept {
        m_id1 = other.m_id1;
        m_id2 = other.m_id2;
        m_id3 = other.m_id3;
        m_id4 = other.m_id4;
        return *this;
    }

    explicit operator String() const;
};

HASH_INLINE bool operator==(const PatchID5 &lhs, const PatchID5 &rhs) noexcept {
    return lhs.m_id1 == rhs.m_id1 && lhs.m_id2 == rhs.m_id2 && lhs.m_id3 == rhs.m_id3 && lhs.m_id4 == rhs.m_id4 && lhs.m_id5 == rhs.m_id5;
}

HASH_INLINE bool operator!=(const PatchID5 &lhs, const PatchID5 &rhs) noexcept {
    return lhs.m_id1 != rhs.m_id1 || lhs.m_id2 != rhs.m_id2 || lhs.m_id3 != rhs.m_id3 || lhs.m_id4 != rhs.m_id4 || lhs.m_id5 != rhs.m_id5;
}
