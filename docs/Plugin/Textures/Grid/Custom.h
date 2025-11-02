// Dan  11/26/2001  \Dan90\Plugin\Textures\Grid\Custom.h

#pragma once
#include "Texture.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTexture final : public Texture {
public:
    //   enum values             {	LRED, LGREEN, LBLUE,
    //								TRANSP,
    //								OX, OY, OZ,
    //								WX, WY, WZ,
    //								IX, IY, IZ,
    //								G_TYPE,
    //								NUMCHANNELINFOS };
    HColorProperty *m_lcolor;
    HFloatProperty *m_transp;
    HTypeProperty *m_gtype;
    HVectorProperty *m_origin;
    HVectorProperty *m_width;
    HVectorProperty *m_interval;

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
        return "Wata\\Grid";
    }

    // EVALUATION
    bool Evaluate(const Vector &evalp, HTexInfo *texinfo) override;
    bool EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) override;
    HProperty *GetPropertyAt(int i) override;

    static int EvalElement(float w, float o, float i, float evalp, float *np);
    BOOL SetLineColor(HTexInfo *texinfo) const;
    BOOL EvaluatePlane(const Vector &evalp, HTexInfo *texinfo) const;
    BOOL EvaluateLine(const Vector &evalp, HTexInfo *texinfo) const;
    BOOL EvaluateCube(const Vector &evalp, HTexInfo *texinfo) const;
    BOOL EvaluateDot(const Vector &evalp, HTexInfo *texinfo) const;

    // CUSTOM TEXTURE FUNCTIONS
//    BOOL SetLineParam(CDialog *dialog, int rsrcid, int chid);
//    BOOL SetFltParam(CDialog *dialog, int rsrcid, int chid);
//    BOOL SetGridType(CDialog *dialog, int id);
};
