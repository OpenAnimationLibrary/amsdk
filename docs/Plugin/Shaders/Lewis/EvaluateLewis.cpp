// Yves  2005-12-04  \Master13.0\Plugin\Shaders\Lewis\EvaluateLewis.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(int i) {
    return nullptr;
}

Shader::ShaderType CustomShader::GetShaderType() {
    return ST_BRDF;
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

void CustomShader::GetDiffuse(HShading *shading) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const RGBFloat Cd = hattr->GetDiffuseColor()->GetNormalizedRGBFloat();
    const float diffuseintensity = 1.F - hattr->GetSpecularIntensity()->GetValue();
    shading->SetDCol(Cd * (shading->GetLDot() * diffuseintensity));
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
    RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const RGBFloat Cl = lightcolor * (shading->GetIntensity() * shading->GetLDot());
    const Vector V = htexinfo->GetD();
    const Vector &R = *shading->GetAway();
    const float u = -R.Dot(V);
    if (u < 0.F)
        return false;

    const float spec = hash_math::pow(u, size);

    if (m_IsFresnel->GetValue()) {
//        Vector &N = *htexinfo->GetN();
        const Vector &L = *shading->GetL();
        Vector H = V + L;
        H.Normalize();
        Fresnel(u, Cs);
    }
    shading->SetSCol(Cs * Cl * (spec * ((size + 2.F) / 2.F) * Ks));
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
    Cs += (RGBFloat(1.F, 1.F, 1.F) - Cs) * f;
}
*/
