// Dan  11/26/2001  \Dan90\Plugin\Volume\Mist\Custom.h
#pragma once

#include "Volume.h"
#include "SDK/HPropert.h"
#include "resource.h"

class CustomVolumetric final : public Volumetric {
public:
    HFloatPropertyInfo *m_valinfo{nullptr};
    HFloatPropertyInfo *m_heightinfo{nullptr};
    HFloatPropertyInfo *m_scaleinfo{nullptr};

    HFloatProperty *m_val{nullptr};
    HFloatProperty *m_height{nullptr};
    HFloatProperty *m_scale{nullptr};
    float m_oval{0.F};

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
        return "Mist";
    }

    // RENDERING
    float GetOpacity(float falloff) override;
    HProperty *GetPropertyAt(int i) override;
};
