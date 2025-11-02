// Dan  11/26/2001  \Dan90\Plugin\Textures\Joyce\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HColorProperty *m_papercolor;
    HColorProperty *m_pencilcolor;
    HColorProperty *m_washcolor;
    HColorProperty *m_dark1color;
    HColorProperty *m_dark2color;
    HFloatProperty *m_pencilnoise;
    HFloatProperty *m_pencilfreq;
    HFloatProperty *m_pencilsize;
    HFloatProperty *m_washnoise;
    HFloatProperty *m_washfreq;
    HFloatProperty *m_washsize;
    HFloatProperty *m_dark1noise;
    HFloatProperty *m_dark1freq;
    HFloatProperty *m_dark1size;
    HFloatProperty *m_dark2noise;
    HFloatProperty *m_dark2freq;
    HFloatProperty *m_dark2size;
    HFloatProperty *m_mix;
    HFloatProperty *m_freq;
    HVectorProperty *m_light;
    HClipProperty *m_bitmap;

    String m_filename;
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
        return "ToonNation\\Joyce";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

};
