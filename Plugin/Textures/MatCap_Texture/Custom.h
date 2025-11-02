// Dan  11/26/2001  \Dan90\Plugin\Textures\Crumple\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    HClipProperty *m_clip;
    HFloatProperty *m_opacity;
    HBoolProperty *m_additiv;

//    HFloatProperty *m_intensity;
//    HPointerProperty *m_decal;

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
        return "Soulcage\\MatCap_texture";
    }

    // SERIALIZATION
    //    bool ParseArg(const char *label, const char *value) override;

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

//    HModel GetModel();
    static HObjectListNode *GetPointerList(HPointerPropertyBase *prop);
};
