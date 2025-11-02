// Dan  11/26/2001  \Dan90\Plugin\Textures\Projection\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"
constexpr int MAXX = 50;
constexpr int MAXY = 50;
constexpr int MAXZ = 10;

class CustomTexture final : public Texture {
public:
    HClipProperty *m_clip;
    HTypeProperty *m_type;
    HTypeProperty *m_kind;
    HFloatProperty *m_value;
    HVector2Property *m_size;

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
        return "Hash\\Projection Map";
    }

    // SERIALIZATION
    bool ParseArg(const char *label, const char *value) override;

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS
    //    BOOL GetTextureP(Vector2 &mapp, const Vector &p, Vector &d);
    //    Vector GetNormalP(Vector2 &mapn, const Vector &p, Vector *n);
    //    Vector GetPu(Vector2 &mapp, const Vector &p, Vector *n);
    //    Vector GetPv(Vector2 &mapp, const Vector &p, Vector *n);
    //    Vector2 GetTexelScale(Vector2 &mapp, const Vector &p, Vector *n);
    //    float GetTexelCmRatio(Vector2 &mapp, const Vector &p, Vector *n);
};
