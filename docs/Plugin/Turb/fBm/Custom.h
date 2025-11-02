// Dan  11/26/2001  \Dan90\Plugin\Turb\fBm\Custom.h
#pragma once

#include "StdAfx.h"
#include "Turbulen.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomTurbulence final : public Turbulence {
public:
    HIntProperty *m_octaves;

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
        return "Hash\\fBm";
    }

    // EVALUATION
    float Evaluate(const Vector &evalp) override;
    HProperty *GetPropertyAt(int i) override;

    // CUSTOM FUNCTIONS
//    void Shift(const Vector &p, Vector &v);
};
