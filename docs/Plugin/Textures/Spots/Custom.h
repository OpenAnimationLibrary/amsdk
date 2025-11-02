// Dan  11/26/2001  \Dan90\Plugin\Textures\Spots\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HBoolProperty *m_useback;
    HColorProperty *m_bcolor;
    HColorProperty *m_fcolor;
    HFloatProperty *m_fref;
    HFloatProperty *m_fo;
    HFloatProperty *m_bref;
    HFloatProperty *m_bo;
    HFloatProperty *m_noise;
    HFloatProperty *m_freq;
    HFloatProperty *m_bump;
    HFloatProperty *m_mix;
    HTranslateProperty *m_offset;
    HScaleProperty *m_scale;
    HFloatProperty *m_size;
    HFloatProperty *m_sfreq;
    HFloatProperty *m_soft;

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
        return "ToonNation\\Spots";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS
    float CalcSpots(const Vector *P) const;
};
