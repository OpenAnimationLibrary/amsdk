// Dan  11/26/2001  \Dan90\Plugin\Textures\Weave\Custom.h
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
    HFloatProperty *m_amplitude;
    HFloatProperty *m_noise;
    HFloatProperty *m_freq;
    HFloatProperty *m_bump;
    HFloatProperty *m_fuzz;
    HFloatProperty *m_mix;
    HVector2Property *m_scale;
    HTypeProperty *m_map;

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
        return "ToonNation\\Weave2";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;
    static void CalcUV(Vector e, float *u, float *v, int type);
};
