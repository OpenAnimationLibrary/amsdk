//KB  8/28/2003  \Ken110\Include\RObject.h
#pragma once

#include "Allocate.h"
#include "Hit.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "RType.h"

class Hit;
class ThreadInfo;
class Ray;

class RObject {
public:
    UCHAR m_nodetype{0};
#ifdef _MEMDEBUG
    void *operator new(size_t size, char *file, const int line) noexcept {
        return ALLOCATT(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocAtt(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeAtt(ptr);
    }

    RObject() noexcept = default;
    explicit RObject(const UCHAR nodetype) noexcept : m_nodetype(nodetype) {}

    virtual ~RObject() = default;

    RObject(const RObject &) = delete;
    RObject &operator=(const RObject &) noexcept = default;
    RObject(RObject &&) = delete;
    RObject &operator=(RObject &&) = delete;

    virtual bool IsPatch() {
        return false;
    }

    virtual bool Intersect(const Ray &, Vector &, Vector &) {
        return false;
    }

    virtual void Intersect(Ray &, ThreadInfo *) {}
    virtual void Normal(Hit &, Vector &, Vector &) {}
    virtual void Collision(ThreadInfo *, Vector &, Vector &) {}
    virtual UCHAR GetRType() noexcept = 0;
};
