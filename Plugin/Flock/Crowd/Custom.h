// KB  6/13/2003  \Ken105\Plugin\Flock\Crowd\Custom.h
#pragma once

#include "FlockDLL.h"
#include "resource.h"
#include "SDK/HPropert.h"
//#include <afxwin.h>

class CustomFlock final : public Flock {
public:
    HFloatProperty *m_mindistance;
    HFloatProperty *m_xzscaleoffset;
    HFloatProperty *m_yscaleoffset;
    HFloatProperty *m_rolloffset;
    HBoolProperty *m_proportional;

//    float m_lasttimeframe{};

    // CONSTRUCTION/DESTRUCTION
    explicit CustomFlock(HTreeObject *treeobject);
    ~CustomFlock() override;

    CustomFlock(const CustomFlock &) = delete;
    CustomFlock &operator=(const CustomFlock &) = delete;
    CustomFlock(CustomFlock &&) = delete;
    CustomFlock &operator=(CustomFlock &&) = delete;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_FLOCK;
    }

    UINT GetNameID() noexcept override {
        return IDS_FLOCKNAME;
    }

    const char *GetClassName() override {
        return "Hash\\Crowd";
    }

    // EVALUATION
    HProperty *GetPropertyAt(int i) override;
    void InitParticlePos(int id, TSQ &tsq, Time &actionoffset) override;
    void UpdateParticlePos(int id, TSQ &tsq, Vector &d, float frametime) override;
};
