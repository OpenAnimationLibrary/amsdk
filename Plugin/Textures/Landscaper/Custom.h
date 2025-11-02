// Dan  11/26/2001  \Dan90\Plugin\Textures\Landscaper\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HColorProperty *m_fcolor1;
    HColorProperty *m_fcolor2;
    HColorProperty *m_fcolor3;
    HFloatProperty *m_foct;
    HFloatProperty *m_ffreq;
    HTypeProperty *m_fnt;
    HColorProperty *m_scolor1;
    HColorProperty *m_scolor2;
    HColorProperty *m_scolor3;
    HFloatProperty *m_soct;
    HFloatProperty *m_sfreq;
    HFloatProperty *m_sbump;
    HTypeProperty *m_snt;
    HFloatProperty *m_falloff;
    HTranslateProperty *m_offset;
    HScaleProperty *m_scale;
    HFloatProperty *m_height;
    HTypeProperty *m_aslope;

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
        return "ToonNation\\Landscaper";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS
    [[nodiscard]] static float calcNoise(Vector P, int ntype, float octaves, float freq);
};
