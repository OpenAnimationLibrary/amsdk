// Yves  2006-01-16  \Master13.0\Plugin\Shaders\Minnaert\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomShader final : public Shader {
public:
    HPercentProperty *m_roughness;

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
        return "Hash\\Minnaert";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
};
