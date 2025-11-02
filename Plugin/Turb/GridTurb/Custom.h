// Dan  11/26/2001  \Dan90\Plugin\Turb\GridTurb\Custom.h
#pragma once

#include "StdAfx.h"
#include "SDK/HPropert.h"
#include "Turbulen.h"
#include "resource.h"

class CustomTurbulence final : public Turbulence {
public:
    HTypeProperty *m_celltype;
    HIntProperty *m_octaves;
    HIntProperty *m_gridsize;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomTurbulence(HTreeObject *treeobject);
    ~CustomTurbulence() override;

    CustomTurbulence(const CustomTurbulence &) = delete;
    CustomTurbulence &operator=(const CustomTurbulence &) = delete;
    CustomTurbulence(CustomTurbulence &&) = delete;
    CustomTurbulence &operator=(CustomTurbulence &&) = delete;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_TURBULENCE;
    }

    UINT GetNameID() noexcept override {
        return IDS_TURBULENCENAME;
    }

    const char *GetClassName() override {
        return "Toonnation\\GridTurb";
    }

    // EVALUATION
    float Evaluate(const Vector &evalp) override;
    HProperty *GetPropertyAt(int i) override;
    float Voronoi2(const Vector *p, int style) const;
    static void CalcUV(const Vector &e, float *u, float *v, int type);
    [[nodiscard]] static float EvaluateHex(const Vector &P, float radius, float scale, float sfuzz);

    // CUSTOM FUNCTIONS
//    void Shift(const Vector &p, Vector &v);
};
