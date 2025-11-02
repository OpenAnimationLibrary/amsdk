// Dan  11/26/2001  \Dan90\Plugin\Textures\Brick\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HFloatProperty *m_bwidth;
    HFloatProperty *m_bheight;
    HFloatProperty *m_bdepth;
    HFloatProperty *m_noise;
    HFloatProperty *m_freq;
    HFloatProperty *m_bump;
    HFloatProperty *m_bref;
    HFloatProperty *m_bo;
    HFloatProperty *m_fref;
    HFloatProperty *m_fo;
    HFloatProperty *m_amplitude;
    HFloatProperty *m_msize;
    HFloatProperty *m_fuzz;
    HFloatProperty *m_mix;
    HTranslateProperty *m_offset;
    HScaleProperty *m_scale;
    HColorProperty *m_bcolor;
    HColorProperty *m_fcolor;
    HBoolProperty *m_useback;

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
        return "ToonNation\\Brick";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS
    float calcBrickVal(const Vector *v) const;

};
