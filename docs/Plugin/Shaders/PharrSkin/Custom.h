// Yves 10-12-2006  \Plugin\Shaders\PharrSkin\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class CustomShader final : public Shader {
public:
    HFloatProperty *m_ior;
    HFloatProperty *m_thickness;

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
        return "Hash\\PharrSkin";
    }

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;

    static Vector Fresnel(const Vector &V, const Vector &N, float v, float ior, float &kr, float &kt);
    [[nodiscard]] static float SingleScatter(const Vector &wi, const Vector &wo, const Vector &n, float assymetry, float albedo, float thickness);
    [[nodiscard]] static float Phase(const Vector &v1, const Vector &v2, float assymetry);
};
