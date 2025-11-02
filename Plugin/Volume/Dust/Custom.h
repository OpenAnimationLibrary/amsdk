// Dan  11/26/2001  \Dan90\Plugin\Volume\Dust\Custom.h
#pragma once

#include "Volume.h"
#include "SDK/HPropert.h"
#include "resource.h"

class CustomVolumetric final : public Volumetric {
public:
    HFloatPropertyInfo *m_speedinfo{nullptr};
    HFloatPropertyInfo *m_swirlinfo{nullptr};
    HFloatPropertyInfo *m_scaleinfo{nullptr};

    HFloatProperty *m_speed{nullptr};
    HFloatProperty *m_swirl{nullptr};
    HFloatProperty *m_scale{nullptr};
    float m_costheta{-1.F};//triggers an ASSERT if Init is not called before use
    float m_sintheta{0.F};
    float m_depth{0.F};

    // CONSTRUCTION/DESTRUCTION
    explicit CustomVolumetric(HTreeObject *treeobject);
    ~CustomVolumetric() override;

    CustomVolumetric(const CustomVolumetric &) = delete;
    CustomVolumetric &operator=(const CustomVolumetric &) = delete;
    CustomVolumetric(CustomVolumetric &&) = delete;
    CustomVolumetric &operator=(CustomVolumetric &&) = delete;

    void Init(Time time) override;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_VOLUMETRIC;
    }

    UINT GetNameID() noexcept override {
        return IDS_VOLUMETRICNAME;
    }

    const char *GetClassName() override {
        return "Hash\\Dust";
    }

    // RENDERING
    float GetOpacity(float falloff) override;
    HProperty *GetPropertyAt(int i) override;
};
