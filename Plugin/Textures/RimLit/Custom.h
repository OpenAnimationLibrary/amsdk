// Dan  11/26/2001  \Dan90\Plugin\Textures\RimLit\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HColorProperty *m_bcolor;
    HVectorProperty *m_light;
    HFloatProperty *m_fo;
    HFloatProperty *m_mix;

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
        return "ToonNation\\RimLit";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;
};
