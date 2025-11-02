//BC  11/4/2004  \BobL115\Include\HashArra.h
// ReSharper disable CppClangTidyBugproneSizeofExpression
#pragma once

#include "Allocate.h"

template <class TYPE>
void ConstructTheElements(TYPE *pElements, int nCount) noexcept {
    ASSERT(nCount == 0 || AfxIsValidAddress(pElements, nCount * sizeof(TYPE)));

    memset((void *)pElements, 0, nCount * sizeof(TYPE));
    for (; nCount--; ++pElements) {
        ::new((void *)pElements) TYPE;
    }
}

template <class TYPE>
void DestructTheElements(TYPE *pElements, int count) noexcept {
    for (; count--; ++pElements) {
        pElements->~TYPE();
    }
}

template <class TYPE>
class ResourcePointerHandler final {
    TYPE **m_source;
    TYPE *m_orgdata;

public:
    explicit ResourcePointerHandler(TYPE **pointer) : m_source(pointer),
                                                      m_orgdata(*pointer) {}

    void ReleaseReplaced() {
        if (m_source && (*m_source == m_orgdata)) {
            *m_source = nullptr;
            FreeExt(m_orgdata);
            m_orgdata = nullptr;
        }
    }
};

template <class TYPE, class ARG_TYPE = const TYPE &>
class HashArray final {
    //protected:
    TYPE *m_data{nullptr};
    int m_size{0};
    int m_maxsize{0};
    int m_growby{6};

public:
    HashArray() noexcept = default;

    ~HashArray() {
        if (m_data) {
            DestructTheElements(m_data, m_size);
            FreeExt(m_data);
            m_data = nullptr;
        }
    }

    HashArray(HashArray &&) noexcept = default; //only needed for flare,beam glow presets, no code generated
    HashArray(const HashArray &) = delete;
    HashArray &operator=(const HashArray &) = delete;
    HashArray &operator=(HashArray &&) = delete;

    [[nodiscard]] int GetSize() const noexcept {
        return m_size;
    }

    [[nodiscard]] bool IsEmpty() const noexcept {
        return m_size == 0;
    }

    [[nodiscard]] int GetUpperBound() const {
        return m_size - 1;
    }

    void SetSize(int newsize, int growby = -1) noexcept;

    void FreeExtra() noexcept;

    void RemoveAll() noexcept {
        SetSize(0, -1);
    }

    [[nodiscard]] TYPE GetAt(int index) const noexcept {
        return m_data[index];
    }

    TYPE &ElementAt(int index) noexcept {
        return m_data[index];
    }

    void SetAt(int index, ARG_TYPE newElement) noexcept {
        m_data[index] = newElement;
    }

    void InsertAt(int nIndex, ARG_TYPE newElement, int nCount = 1);
    void RemoveAt(int index, int count = 1) noexcept;

    TYPE operator [](int index) const noexcept {
        return m_data[index];
    }

    TYPE &operator [](int index) noexcept {
        return m_data[index];
    }

    TYPE *GetArray() noexcept {
        return (TYPE *)m_data;
    }

    void SetAtGrow(int index, ARG_TYPE newElement) noexcept;
    int Add(ARG_TYPE newElement) noexcept;
    int Find(ARG_TYPE newElement);
    void Push(ARG_TYPE newElement) noexcept;
    TYPE Pop() noexcept;
    [[nodiscard]] TYPE GetPushed() const noexcept;

    void SetGranularity(const int granularity) noexcept {
        m_growby = granularity;
    }

    ResourcePointerHandler<TYPE> GetResourcePointerHandler() {
        return ResourcePointerHandler<TYPE>(&m_data);
    }
};

template <class TYPE, class ARG_TYPE>
int HashArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement) noexcept {
    const int index = m_size;
    SetAtGrow(index, newElement);
    return index;
}

template <class TYPE, class ARG_TYPE>
int HashArray<TYPE, ARG_TYPE>::Find(ARG_TYPE newElement) {
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i] == newElement)
            return i;
    }
    return -1;
}

template <class TYPE, class ARG_TYPE>
void HashArray<TYPE, ARG_TYPE>::SetSize(int newsize, int growby) noexcept {
    if (growby != -1)
        m_growby = growby;
    if (newsize == 0) {
        if (m_data) {
            DestructTheElements(m_data, m_size);
            FreeExt(m_data);
            m_data = nullptr;
        }
        m_size = m_maxsize = 0;
    } else if (!m_data) {
        growby = m_growby;
        if (growby == 0) {
            growby = m_size / 8;
            growby = (growby < 4) ? 4 : ((growby > 1024) ? 1024 : growby);
        }
        int newmax = newsize;
        if (newsize < m_maxsize + growby) {
            newmax = m_maxsize + growby;
        }
        m_data = (TYPE *)AllocExt(newmax * sizeof(TYPE));
        ConstructTheElements(m_data, newsize);
        m_size = newsize;
        m_maxsize = newmax;
        /*
                m_data = (TYPE *)AllocExt(newsize * sizeof(TYPE));
                HashConstructElements(m_data, newsize);
                m_size = m_maxsize = newsize;
        */
    } else if (newsize <= m_maxsize) {
        if (newsize > m_size) {
            ConstructTheElements(&m_data[m_size], newsize - m_size);
        } else if (m_size > newsize) {
            DestructTheElements(&m_data[newsize], m_size - newsize);
        }
        m_size = newsize;
    } else {
        growby = m_growby;
        if (growby == 0) {
            growby = m_size / 8;
            growby = (growby < 4) ? 4 : ((growby > 1024) ? 1024 : growby);
        }
        int newmax = newsize;
        if (newsize < m_maxsize + growby) {
            newmax = m_maxsize + growby;
        }

        TYPE *newdata = (TYPE *)AllocExt(newmax * sizeof(TYPE));
        memcpy((void *)newdata, (void *)m_data, m_size * sizeof(TYPE)); // NOLINT(bugprone-undefined-memory-manipulation)
        ConstructTheElements(&newdata[m_size], newsize - m_size);
        FreeExt(m_data);
        m_data = newdata;
        m_size = newsize;
        m_maxsize = newmax;
    }
}

template <class TYPE, class ARG_TYPE>
void HashArray<TYPE, ARG_TYPE>::FreeExtra() noexcept {
    if (m_size != m_maxsize) {
        TYPE *newdata = nullptr;
        if (m_size != 0) {
            newdata = (TYPE *)AllocExt(m_size * sizeof(TYPE));
            memcpy(newdata, m_data, m_size * sizeof(TYPE));
        }

        FreeExt(m_data);
        m_data = newdata;
        m_maxsize = m_size;
    }
}

template <class TYPE, class ARG_TYPE>
void HashArray<TYPE, ARG_TYPE>::SetAtGrow(int index, ARG_TYPE newElement) noexcept {
    if (index >= m_size)
        SetSize(index + 1);
    if (m_data)
        m_data[index] = newElement;
}

template <class TYPE, class ARG_TYPE>
void HashArray<TYPE, ARG_TYPE>::InsertAt(int nIndex, ARG_TYPE newElement, int nCount/*=1*/) {
    ASSERT(nIndex >= 0); //will expand to meet need
    ASSERT(nCount > 0); //zero or negative size not allowed
    if (nIndex >= m_size) {
        //adding after the end of the array
        SetSize(nIndex + nCount); //grow so nIndex is valid
    } else {
        //inserting in the middle of the array
        int nOldSize = m_size;
        SetSize(m_size + nCount); //grow it to new size
        //destroy intial data before copying over it
        DestructTheElements<TYPE>(&m_data[nOldSize], nCount);
        //shift old data up to fill gap
        memmove(&m_data[nIndex + nCount], &m_data[nIndex], (static_cast<unsigned long long>(nOldSize) - nIndex) * sizeof(TYPE));

        //re-init slots we copied from
        ConstructTheElements<TYPE>(&m_data[nIndex], nCount);
    }

    //insert new value in the gap
    ASSERT(nIndex + nCount <= m_size);
    while (nCount--) {
        m_data[nIndex++] = newElement;
    }
}

template <class TYPE, class ARG_TYPE>
void HashArray<TYPE, ARG_TYPE>::RemoveAt(int index, const int count) noexcept {
    ASSERT(m_size <= m_maxsize);
    //just remove a range
    const int movecount = m_size - (index + count);

    DestructTheElements<TYPE>(&m_data[index], count);
    if (movecount)
        memmove(&m_data[index], &m_data[index + count], movecount * sizeof(TYPE));
    m_size -= count;
}

template <class TYPE, class ARG_TYPE>
void HashArray<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement) noexcept {
    SetAtGrow(m_size, newElement);
}

template <class TYPE, class ARG_TYPE>
TYPE HashArray<TYPE, ARG_TYPE>::Pop() noexcept {
    ASSERT(m_size >= 1);
    TYPE rvalue = m_data[m_size - 1];
    DestructTheElements<TYPE>(&m_data[m_size - 1], 1);
    --m_size;
    return rvalue;
}

template <class TYPE, class ARG_TYPE>
TYPE HashArray<TYPE, ARG_TYPE>::GetPushed() const noexcept {
    return m_data[m_size - 1];
}
