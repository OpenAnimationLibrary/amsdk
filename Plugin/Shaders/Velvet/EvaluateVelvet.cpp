// Yves  2005-11-24  \Master13.0\Plugin\Shaders\Velvet\EvaluateVelvet.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_Sheen;
        case 1:
            return m_Edginess;
        default:
            return nullptr;
    }
}

const char *CustomShader::GetShaderDiffuseFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderSpecularFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {}

// Based on Stephen H. Westin SHW_Velvet Renderman shader
bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const float size = hattr->GetSpecExponent();
    if (size == 0.F)
        return FALSE;
    const RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    const RGBFloat Cl = lightcolor * shading->GetIntensity();
    //   size = sqrt ( 0.5f / size ); // This is to match Phong specular sizes
    const Vector V = -htexinfo->GetD();
    const Vector L = -*shading->GetL();
//    Vector &N = *htexinfo->GetN();
    const float v = shading->GetEDot();
    const float l = shading->GetLDot();
    const float r = L.Dot(V);

    float cosine = MAX(r, 0.F);
    float spec = hash_math::pow(cosine, size) * Ks; // Retroreflective lobe
    cosine = MAX(v, 0.F);
    const float sine = hash_math::sqrt(1.F - cosine * cosine);
    spec += hash_math::pow(sine, m_Edginess->GetValue()); // Horizon scattering

    const RGBFloat speccolor = Cs * Cl * (spec * l) * m_Sheen->GetValue();
    shading->SetSCol(speccolor);
    return true;
}
