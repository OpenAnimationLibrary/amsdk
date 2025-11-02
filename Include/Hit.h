//BC  5/3/2004  \Bob110\Include\Hit.h
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeMemberInit
#pragma once

#include "Allocate.h"
#include "Vector.h"
#include "DataType.h"

class RObject;
class BinNode;
class RayPatch;
class Follicle;
class HairCubic;

class Hit final {
public:
    Vector m_p;
    Vector m_truen;
    RObject *m_object{nullptr};
    BinNode *m_baseobject{nullptr};
    RayPatch *m_raypatch{nullptr};
    Follicle *m_follicle{nullptr};
    UINT m_patchid{0};
    float m_t{0.F};
    float m_u{0.F};
    float m_v{0.F};
    int m_offset{0};
    int m_polyid{-1};

// @formatter:off
    union {
        BITFIELDS16 m_Hit_bitfield{0}; //BITFIELDS8 doesn't save memory due padding
        struct {
            BITFIELDS16 m_isexitblobby : 1,
            m_is5point : 1,
            m_isblobby : 1,
            m_side : 1, //for triangle intersection
            m_isflipped : 1,
            m_ishit : 1,
            m_isadditivetransparency : 1,
            m_ismultiplyspecularbytransparency : 1,
            unused : 8;
        };
    };
// @formatter:on

#ifdef _MEMDEBUG
    void *operator new(size_t size, char *file, const int line) noexcept {
        return ALLOCEXT(size, file, line);
    }
    void *operator new[](size_t size, char *file, const int line) {
        return ALLOCEXT(size, file, line);
    }
#else
    void *operator new(const size_t size) noexcept {
        return AllocExt(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeExt(ptr);
    }

    Hit() noexcept = default;

    Hit(const Vector mp, RObject *mobject, const float mt, const float mu, const float mv, const int mpolyid, const int mside) noexcept : m_p(mp),
                                                                                                                                          m_object(mobject),
                                                                                                                                          m_t(mt),
                                                                                                                                          m_u(mu),
                                                                                                                                          m_v(mv),
                                                                                                                                          m_polyid(mpolyid) {
        m_side = (USHORT)mside;
    }

    Hit(const Hit &other) noexcept : m_p(other.m_p),
                            m_truen(other.m_truen),
                            m_object(other.m_object),
                            m_baseobject(other.m_baseobject),
                            m_raypatch(other.m_raypatch),
                            m_follicle(other.m_follicle),
                            m_patchid(other.m_patchid),
                            m_t(other.m_t),
                            m_u(other.m_u),
                            m_v(other.m_v),
                            m_offset(other.m_offset),
                            m_polyid(other.m_polyid),
                            m_Hit_bitfield(other.m_Hit_bitfield) {}

    ~Hit() = default;

    Hit &operator=(const Hit &) noexcept = default;
    Hit(Hit &&) = default;
    Hit &operator=(Hit &&) = default;

    void Empty() noexcept {
        m_polyid = -1;
        m_baseobject = nullptr;
        m_object = nullptr;
        m_follicle = nullptr;
        m_raypatch = nullptr;
        m_Hit_bitfield = 0;
        m_t = m_u = m_v = 0.F;
        m_offset = 0;
        m_patchid = 0;
        m_p.SetZero();
        m_truen.SetZero();
    }
};
