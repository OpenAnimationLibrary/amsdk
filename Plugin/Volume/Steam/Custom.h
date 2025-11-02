// Dan  11/26/2001  \Dan90\Plugin\Volume\Steam\Custom.h
#pragma once

#include "Volume.h"
#include "resource.h"
#include "SDK/HPropert.h"
#include "SDK/HVolFX.h"

class CustomVolumetric final : public Volumetric {
public:
    HFloatPropertyInfo *m_speedinfo{nullptr};
    HFloatPropertyInfo *m_swirlinfo{nullptr};
    HFloatPropertyInfo *m_scaleinfo{nullptr};

    HFloatProperty *m_speed{nullptr};
    HFloatProperty *m_swirl{nullptr};
    HFloatProperty *m_scale{nullptr};

    HVolFX *m_volfx{nullptr};
    float m_seconds{0.F};
    float m_scaledspeed{0.F};

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
        return "Hash\\Smoke";
    }

    // SERIALIZATION
    bool OnNotifyEndProjectLoad(float productversion) override;

    // RENDERING
    float GetOpacity(float falloff) override;
    HProperty *GetPropertyAt(int i) override;
};
