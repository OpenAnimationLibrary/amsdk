// Dan  11/26/2001  \Dan90\Plugin\Textures\MultiSky\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HFloatProperty *m_height;
    HFloatProperty *m_cover;
    HIntProperty *m_octaves;
    HFloatProperty *m_haze;
    HFloatProperty *m_sintensity;
    HBoolProperty *m_si;
    HFloatProperty *m_trans;
    HTypeProperty *m_type;
    HVectorProperty *m_sun;
    HTranslateProperty *m_offset;
    HScaleProperty *m_scale;
    HColorProperty *m_hcolor;
    HColorProperty *m_scolor;
    HColorProperty *m_c1color;
    HColorProperty *m_c2color;
    HColorProperty *m_bcolor;

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
        return "ToonNation\\MultiSky";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS

    [[nodiscard]] float calcSky(Vector P, int octaves, float cover) const;

};
