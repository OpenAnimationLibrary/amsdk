// KB  2/4/2003  \Ken105\Plugin\Shaders\BlinnPhong\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(int i) {
    return nullptr;
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

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const float size = hattr->GetSpecExponent();
    if (size == 0.F)
        return false;
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    if (Ks == 0.F)
        return false;
    RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const RGBFloat Cl = lightcolor * (shading->GetIntensity() * shading->GetLDot());
    const Vector &N = *htexinfo->GetN();
    const Vector &L = *shading->GetL();
    const Vector V = htexinfo->GetD();
    Vector H = V + L;
    H.Normalize();
    const float u = hash_math::abs(H.Dot(N));
    const float spec = hash_math::pow(u, size);
    if (m_IsFresnel->GetValue())
        Fresnel(u, Cs);
    shading->SetSCol(Cs * Cl * (spec * Ks));
    return true;
}

constexpr float ComputeFresnelTerm(const float inputvalue) {
    float f = 1.F - inputvalue;
    const float ff = f * f;
    f *= ff * ff;
    return f;
}

void CustomShader::Fresnel(const float u, RGBFloat &Cs) {
    Cs += (RGBFloat(1.F) - Cs) * ComputeFresnelTerm(u);
}
