// MH  9/20/2002  \Mart100\Plugin\Shaders\Glossy\EvaluateGlossy.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_sharpness;
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

float smoothstep(const float a, const float b, const float x) {
    if (x < a)
        return 0.F;
    if (x >= b)
        return 1.F;
    const float x1 = (x - a) / (b - a);
    return hash_math::sqr(x1) * (3.F - 2.F * x1);
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
    const Vector &N = *htexinfo->GetN();
    const Vector &L = *shading->GetL();
    const Vector V = htexinfo->GetD();
    Vector H = L + V;
    H.Normalize();
    const float u = hash_math::abs(H.Dot(N));

    float spec = hash_math::pow(u, size);
    const float sharp = 1.F - m_sharpness->GetValue();
    spec = smoothstep(0.72f - sharp, 0.72f + sharp, spec); // How will this work with HDR save?

    Fresnel(u, Cs); // Glossy specularity is due to transparent layer so must reflect light
    const RGBFloat speccolor = Cs * Cl * (spec * Ks);
    shading->SetSCol(speccolor);
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
    // u is the cosine between normal and H vector or between reflected ray and light.
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
