// Dan  11/26/2001  \Dan90\Plugin\Shaders\Phong\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomShader final : public Shader {
public:
    // CONSTRUCTION/DESTRUCTION
    explicit CustomShader(HTreeObject *treeobject);
    ~CustomShader() override;

    CustomShader(const CustomShader &) = delete;
    CustomShader &operator=(const CustomShader &) = delete;
    CustomShader(CustomShader &&) = delete;
    CustomShader &operator=(CustomShader &&) = delete;

    HPercentPropertyInfo *m_sharpnessinfo;
    HPercentProperty *m_sharpness;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_ICON1;
    }

    UINT GetNameID() noexcept override {
        return IDS_SHADERNAME;
    }

    const char *GetClassName() override {
        return "ToonNation\\Glossy";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;

    // OPERATION
    static void Fresnel(float u, RGBFloat &Cs);
};
