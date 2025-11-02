// Dan  11/26/2001  \Dan90\Plugin\Textures\InkStroke\Custom.h
#pragma once

#include "Texture.h"
#include "SDK/HPropert.h"
#include "resource.h"

class CustomTexture final : public Texture {
public:
    HBoolProperty *m_useback;
    HColorProperty *m_bcolor;
    HColorProperty *m_fcolor;
    HFloatProperty *m_fref;
    HFloatProperty *m_fo;
    HFloatProperty *m_bo;
    HFloatProperty *m_mix;
    HFloatProperty *m_fuzz;
    HFloatProperty *m_xs;
    HFloatProperty *m_ys;
    HFloatProperty *m_pencil;
    HVectorProperty *m_light;
    HFloatProperty *m_rough;
    HFloatProperty *m_tx;
    HFloatProperty *m_ty;
    HClipProperty *m_bitmap;

    String filename;
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
        return "ToonNation\\InkStroke";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

};
