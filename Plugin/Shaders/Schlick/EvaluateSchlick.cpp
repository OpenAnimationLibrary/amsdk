// Yves  2005-11-24  \Master13.0\Plugin\Shaders\Schlick\EvaluateSchlick.cpp

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

    const float u = -H.Dot(N);
    if (u < 0.F)
        return false;
    const float spec = u / (size - size * u + u);

    if (m_IsFresnel->GetValue())
        Fresnel(u, Cs);
    shading->SetSCol(Cs * Cl * (spec * Ks));
    return true;
}

constexpr float ComputeFresnelTerm(const float inputvalue) {
    float f = 1.F - inputvalue;
    const float ff = hash_math::sqr(f);
    f *= hash_math::sqr(ff);
    return f;
}

void CustomShader::Fresnel(const float u, RGBFloat &Cs) {
    Cs += (RGBFloat(1.F) - Cs) * ComputeFresnelTerm(u);
}

/*
void CustomShader::Fresnel(const float u, RGBFloat &Cs) {
    // Schlick approximation of the Fresnel calculation
    // u is the cosine between normal and H vector or between reflected ray and eye.
    // u = 0 at grazing incident angle and = 1 at normal incident angle
    float f = 1.F - u;
    const float ff = f * f;
    f *= ff * ff;
    // f = 1 at grazing incident angle and = 0 at normal incident angle.
    // The Fresnel term is going to multiply the light color.
    // At grazing incidence light color is totally reflected back.
    Cs += (RGBFloat(1.F) - Cs) * f;
}
*/
