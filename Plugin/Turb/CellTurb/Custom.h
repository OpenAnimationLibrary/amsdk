// RC  6/4/2002  \Randy95\Plugin\Turb\CellTurb\Custom.h
#pragma once

#include "StdAfx.h" 

#include "Turbulen.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTurbulence final : public Turbulence {
public:
    HTypeProperty *m_celltype;
    HFloatProperty *m_threshold;
    HIntProperty *m_oct;
    HFloatProperty *m_density;
    HBoolProperty *m_euclid;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomTurbulence(HTreeObject *treeobject);
    ~CustomTurbulence() override;

    CustomTurbulence(const CustomTurbulence&) = delete;
    CustomTurbulence &operator= (const CustomTurbulence&) = delete; 
    CustomTurbulence(CustomTurbulence &&) = delete; 
    CustomTurbulence &operator=(CustomTurbulence &&) = delete; 

    bool ParseArg(const char *label, const char *value) override;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_TURBULENCE;
    }

    UINT GetNameID() noexcept override {
        return IDS_TURBULENCENAME;
    }

    const char *GetClassName() override {
        return "Toonnation\\CellTurb";
    }

    // EVALUATION
    float Voronoi2(const Vector *p, int style) const;
    float Evaluate(const Vector &evalp) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM FUNCTIONS
//    void Shift(const Vector &p, Vector &v);
};
