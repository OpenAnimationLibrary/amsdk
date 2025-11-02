// Yves  2004/11/19  \Plugin\Turb\Extended GridTurb\Custom.h
#pragma once

#include "StdAfx.h"

#include "SDK/HPropert.h"
#include "Turbulen.h"
#include "resource.h"

enum {
    GRID_CUBICAL,
    GRID_SPHERICAL,
    GRID_CYLINDRICAL
};

class CustomTurbulence final : public Turbulence {
public:
    HTypeProperty *m_GridType;

    HBoolCategoryProperty *m_UseX;
    HFloatProperty *m_XSize;
    HFloatProperty *m_XRatio;
    HPercentProperty *m_XBlur;

    HBoolCategoryProperty *m_UseY;
    HFloatProperty *m_YSize;
    HFloatProperty *m_YRatio;
    HPercentProperty *m_YBlur;

    HBoolCategoryProperty *m_UseZ;
    HFloatProperty *m_ZSize;
    HFloatProperty *m_ZRatio;
    HPercentProperty *m_ZBlur;

    HBoolCategoryProperty *m_UseAzimuth;
    HFloatProperty *m_AzimuthSize;
    HFloatProperty *m_AzimuthRatio;
    HPercentProperty *m_AzimuthBlur;
    HFloatProperty *m_AzimuthStripe;

    HBoolCategoryProperty *m_UseElevation;
    HFloatProperty *m_ElevationSize;
    HFloatProperty *m_ElevationRatio;
    HPercentProperty *m_ElevationBlur;
    HFloatProperty *m_ElevationStripe;

    HBoolCategoryProperty *m_UseRadial;
    HFloatProperty *m_RadialSize;
    HFloatProperty *m_RadialRatio;
    HPercentProperty *m_RadialBlur;

    CustomTurbulence *m_CopyOf;
    BOOL m_UIDirty;
    BOOL m_TypeDirty;
    BOOL m_UseXDirty;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomTurbulence(HTreeObject *treeobject);
    ~CustomTurbulence() override;

    CustomTurbulence(const CustomTurbulence &) = delete;
    CustomTurbulence &operator=(const CustomTurbulence &) = delete;
    CustomTurbulence(CustomTurbulence &&) = delete;
    CustomTurbulence &operator=(CustomTurbulence &&) = delete;

    void Copy(const DLLPlugin &other) override {
        m_CopyOf = (CustomTurbulence *)&other;
    }

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_TURBULENCE;
    }

    UINT GetNameID() noexcept override {
        return IDS_TURBULENCENAME;
    }

    const char *GetClassName() override {
        return "Hash\\Extended GridTurb";
    }

    // EVALUATION
    float Evaluate(const Vector &evalp) override;
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time = Time()) override;

    void UpdateUI();
    BOOL IsUpdatePtr(int at, HProperty *dueto) const;

    // CUSTOM FUNCTIONS
    static void MapCylinder(Vector e, float &u, float &v);
    static void MapSphere(Vector e, float &u, float &v, float &w);

    //	HELPER FUNCTIONS
};

inline float h_floor(const float x) {
    const auto y = (float)(int)x;
    return y - (float)(x < 0.F && x != y);
}

inline float h_ceil(const float x) {
    const auto y = (float)(int)x;
    return y + (float)(x > 0.F && x != y);
}

inline float m_mod(float a, const float b) {
    const auto n = (float)(int)(a / b);
    a -= n * b;
    return a < 0 ? a + b : a;
}

inline float SmoothStep(const float a, const float b, const float x) {
    if (x < a)
        return 0.F;
    if (x >= b)
        return 1.F;
    const float x1 = (x - a) / (b - a);
    return hash_math::sqr(x1) * (3.F - 2.F * x1);
}

inline float SmoothPulse(const float a, const float b, float fuzz, float x) {
    x += a * 0.5F;
    fuzz *= 0.5F;
    return SmoothStep(a - fuzz, a + fuzz, x) - SmoothStep(b - fuzz, b + fuzz, x);
}

inline float Repeat(const float x, const float freq) {
    return m_mod(x * freq, 1.F);
}

inline float WhichTile(const float x, const float freq) {
    return h_floor(x * freq);
}

inline float Step(const float a, const float x) {
    return x >= a;
}

inline float Pulse(const float a, const float b, const float x) {
    return Step(a, x) - Step(b, x);
}

inline float Clamp(const float a, const float b, const float x) {
    return x < a ? a : x > b ? b : x;
}
