// Yves  12/08/2005  \Dan90\Plugin\Shaders\Blinn\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomShader final : public Shader {
public:
    HTypeProperty *m_Attenuation;

    float m_2m2;
    float m_savedsize;

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
        return "Hash\\Blinn";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
    // OPERATION
    RGBFloat GetBRDF(HShading *shading, HTexInfo *htexinfo, HAttrProperty *hattr, float size);
    static void Fresnel(float u, RGBFloat &Cs);
//    void SchlickFesnel(float u, RGBFloat &Cs);
//    float FresnelComponent(float u, float c);
};
