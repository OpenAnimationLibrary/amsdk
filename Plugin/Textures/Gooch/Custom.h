// Dan  11/26/2001  \Dan90\Plugin\Textures\Gooch\Custom.h
#pragma once

#include "Texture.h"
#include "SDK/HPropert.h"
#include "resource.h"

class CustomTexture final : public Texture {
public:
    HFloatProperty *m_amplitude;
    HBoolProperty *m_useback;
    HColorProperty *m_bcolor;
    HColorProperty *m_fcolor;
    HFloatProperty *m_noise;
    HFloatProperty *m_freq;
    HFloatProperty *m_mix;
    HFloatProperty *m_scalex;
    HFloatProperty *m_scaley;
    HVectorProperty *m_light;

//HFloatProperty *m_bump;

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
        return "ToonNation\\Gooch";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS   
};
