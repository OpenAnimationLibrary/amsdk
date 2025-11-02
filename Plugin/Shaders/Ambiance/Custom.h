// KB  8/28/2003  \Ken110\Plugin\Shaders\Ambiance\Custom.h
#pragma once

#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomShader final : public Shader2 {
public:
    HColorProperty *m_ambiancecolor;

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
        return "Hash\\Ambiance";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    const char *GetShaderAmbianceFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
    void GetAmbiance(HShading *shading) override;
};
