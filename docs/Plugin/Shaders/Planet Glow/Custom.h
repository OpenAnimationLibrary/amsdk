// Yves  2005-11-22  \master13.0\Plugin\Shaders\PlanetGlow\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"

class CustomShader final : public Shader {
public:
    HPercentProperty *m_Falloff;
    HPercentProperty *m_Glow;
    HPercentProperty *m_Fade;
    HPercentProperty *m_Xparency;
    HColorProperty *m_LoColor;
    HColorProperty *m_HiColor;

    // CUSTOMIZED
    static RGBFloat MixColor(const RGBFloat &c1, const RGBFloat &c2, double mix);

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
        return "Hash\\Planet Glow";
    }

    // SERIALIZATION
    bool ParseArg(const char *label, const char *value) override;

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    HProperty *GetPropertyAt(int i) override;

    // RENDERING
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
};
