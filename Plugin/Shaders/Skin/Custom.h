// Yves Poissant  2004-01-15  \My Plugins\Shaders\Skin\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomShader final : public Shader {
public:
    HPercentProperty *m_Falloff;
    HPercentProperty *m_Roughness;
    HPercentProperty *m_ShiftStart;
    HPercentProperty *m_ShiftEnd;
    HPercentProperty *m_Saturation;
    HPercentProperty *m_HueShift;
    HColorProperty *m_BloodColor;
    HPercentProperty *m_HueStrength;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomShader(HTreeObject *treeobject);
    ~CustomShader() override;

    CustomShader(const CustomShader &) = delete;
    CustomShader &operator=(const CustomShader &) = delete;
    CustomShader(CustomShader &&) = delete;
    CustomShader &operator=(CustomShader &&) = delete;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_ICON1;
    }

    UINT GetNameID() noexcept override {
        return IDS_SHADERNAME;
    }

    const char *GetClassName() override {
        return "Hash\\Skin";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;

    float OrenNayar(HShading *shading) const;
    static RGBFloat ToHSV(const RGBFloat *RGBColor);
    static RGBFloat ToRGB(const RGBFloat *HSVColor);
};
