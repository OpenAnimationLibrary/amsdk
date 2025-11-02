// Yves  2004/10/27  Plugin\Turb\Musgrave\Custom.h
#pragma once

#include "Turbulen.h"
#include "resource.h"
#include "SDK/HPropert.h"
#include "FracNoise.h"
#include "Transfer.h"
#include "Sampler.h"

class CustomTurbulence final : public Turbulence {
public:
    FractalNoise m_FractalNoiser;
    Transferer m_Transferer;
    Sampler m_Sampler;
    float d_Min{0.F};
    float d_Max{0.F};

    // CONSTRUCTION/DESTRUCTION
    explicit CustomTurbulence(HTreeObject *treeobject);
    ~CustomTurbulence() override;

    CustomTurbulence(const CustomTurbulence &) = delete;
    CustomTurbulence &operator=(const CustomTurbulence &) = delete;
    CustomTurbulence(CustomTurbulence &&) = delete;
    CustomTurbulence &operator=(CustomTurbulence &&) = delete;

    void Copy(const DLLPlugin &other) override {
        const auto &Turb = (CustomTurbulence &)other;
        m_FractalNoiser.Copy(Turb.m_FractalNoiser);
    }

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_TURBULENCE;
    }

    UINT GetNameID() noexcept override {
        return IDS_TURBULENCENAME;
    }

    const char *GetClassName() override {
        return "Hash\\Musgrave";
    }

    bool ParseArg(const char *label, const char *value) override;

    // EVALUATION
    float Evaluate(const Vector &evalp) override;
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time = Time()) override;

    // CUSTOM FUNCTIONS
    //    void Shift(const Vector &p, Vector &v);
    //    float Cutoff(float lo, float hi, float val, BOOL smooth);
    void SaveHisto(float val);
    void ResetDebug();
};
