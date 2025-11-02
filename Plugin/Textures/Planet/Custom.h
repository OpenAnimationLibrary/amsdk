// Dan  11/26/2001  \Dan90\Plugin\Textures\Planet\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HFloatProperty *m_featuresize;
    HFloatProperty *m_polardist;
    HFloatProperty *m_water;
    HFloatProperty *m_bump;
    HFloatProperty *m_ice;
    HFloatProperty *m_freq;
    HFloatProperty *m_ampl;
    HFloatProperty *m_octaves;
    HFloatProperty *m_noisemult;
    HFloatProperty *m_seed;
    HFloatProperty *m_offset;
    HFloatProperty *m_mottlesize;
    HFloatProperty *m_mottlemag;
    HFloatProperty *m_depthnoise;
    HFloatProperty *m_maxdepth;
    HFloatProperty *m_snow;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomTexture(HTreeObject *treeobject);
    ~CustomTexture() override;

    CustomTexture(const CustomTexture &) = delete;
    CustomTexture &operator=(const CustomTexture &) = delete;
    CustomTexture(CustomTexture &&) = delete;
    CustomTexture &operator=(CustomTexture &&) = delete;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_TEXTURE;
    }

    UINT GetNameID() noexcept override {
        return IDS_TEXTURENAME;
    }

    const char *GetClassName() override {
        return "Alibi\\Planet";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;

    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override {
        return TRUE;
    }

    HProperty *GetPropertyAt(int i) override;
};
