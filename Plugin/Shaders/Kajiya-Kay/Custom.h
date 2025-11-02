// 
#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

#define TABLE_SIZE	0x3FF

class CustomShader final : public Shader {
public:
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
        return "Hash\\Kajiya-Kay";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;

    ShaderType GetShaderType() override {
        return ST_HAIR;
    }
};
