// Dan  11/26/2001  \Dan90\Plugin\Textures\BBall\Custom.h

#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    //   enum values { NUMCHANNELINFOS };
    //   ChannelInfo chaninfo[NUMCHANNELINFOS];
    //   static Vector             pip[10];
    //   int                       numpips;

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
        return "Hash\\Basketball";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;

    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override {
        return TRUE;
    }

    HProperty *GetPropertyAt(int i) override;

    // CUSTOM TEXTURE FUNCTIONS
    //   void                      ReadPips();
};
