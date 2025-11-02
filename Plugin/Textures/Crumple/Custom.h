// Dan  11/26/2001  \Dan90\Plugin\Textures\Crumple\Custom.h
#pragma once

#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    //   enum values             { XSIZE,YSIZE,ZSIZE,BUMP,		// Page 1
    //                             FREQ,AMPL,OCTAVES,WEIGHT,SEED,  // Page 2
    //                             NUMCHANNELINFOS };
    HScaleProperty *m_size;
    HFloatProperty *m_bump;
    HFloatProperty *m_freq;
    HFloatProperty *m_ampl;
    HIntProperty *m_octaves;
    HFloatProperty *m_weight;
    HFloatProperty *m_seed;

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
        return "Alibi\\Crumple";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;

    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override {
        return TRUE;
    }

    HProperty *GetPropertyAt(int i) override;
};
