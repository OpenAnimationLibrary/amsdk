// Yves  2005-11-23  \Ken100\Plugin\Shaders\Gradient\EvaluateGradientLight.cpp

#include "StdAfx.h"
#include "Custom.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_gradient;
    return nullptr;
}

const char *CustomShader::GetShaderDiffuseFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

const char *CustomShader::GetShaderSpecularFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const RGBFloat Cd = hattr->GetDiffuseColor()->GetNormalizedRGBFloat();
    RGBFloat white(1.F);
    const RGBFloat color = m_gradient->GetColor(white, shading->GetLDot());
    shading->SetDCol(Cd * color * shading->GetLDot() * shading->GetIntensity());
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const float size = hattr->GetSpecExponent();
    if (size == 0.F)
        return false;
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    if (Ks == 0.F)
        return false;
    const RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const RGBFloat Cl = lightcolor * (shading->GetIntensity() * shading->GetLDot());

    const Vector &L = *shading->GetL();
    const Vector &N = *htexinfo->GetN();
    const Vector V = htexinfo->GetD();
    Vector H = V + L;
    H.Normalize();
    const float u = hash_math::abs(H.Dot(N));
    const float spec = hash_math::pow(u, size);
    RGBFloat white(1.F, 1.F, 1.F);
    RGBFloat color = m_gradient->GetColor(white, spec); // u
    color *= Cs * Cl * (spec * Ks);
    shading->SetSCol(color);
    return true;
}
