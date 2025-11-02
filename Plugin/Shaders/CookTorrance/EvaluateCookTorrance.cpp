// MH  9/20/2002  \Mart100\Plugin\Shaders\Phong\EvaluateCookTorrance.cpp

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
    float size = hattr->GetSpecExponent();
    if (size == 0.F)
        return false;
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    if (Ks == 0.F)
        return false;
    size = 2.F / size; // This is to match Phong specular sizes
    const RGBFloat Cl = lightcolor * shading->GetIntensity() * shading->GetLDot();
    shading->SetSCol(GetBRDF(shading, htexinfo, hattr, size) * Cl * Ks);
    return true;
}

RGBFloat CustomShader::GetBRDF(HShading *shading, HTexInfo *htexinfo, HAttrProperty *hattr, float size) {
    RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const Vector V = -htexinfo->GetD();
    const Vector L = -*shading->GetL();
    const Vector N = *htexinfo->GetN();
    Vector H = V + L;
    H.Normalize();
    float h = H.Dot(N);
    const float u = H.Dot(V);
    const float v = shading->GetEDot();
    const float l = shading->GetLDot();
    float Gg = 2.F * h / u;
    if (v < l)
        Gg *= v;
    else
        Gg *= l;
    if (Gg > 1.F)
        Gg = 1.F;
    h *= h;
    size *= size;
    const float Dd = exp((h - 1.F) / (size * h)) / (4.0f * size * h * h);
    Fresnel(h, Cs);
    return Cs * (Dd * Gg / (v * l));
}

void CustomShader::Fresnel(const float u, RGBFloat &Cs) {
    Cs.SetRed(FresnelComponent(u, Cs.Red()));
    Cs.SetGreen(FresnelComponent(u, Cs.Green()));
    Cs.SetBlue(FresnelComponent(u, Cs.Blue()));
}

float CustomShader::FresnelComponent(const float u, const float c) {
    float n = hash_math::sqrt(c);
    n = (1.F + n) / (1.F - n);
    const float g = hash_math::sqrt(n * n + u * u - 1.F);
    float t = u * (g + u) - 1.F;
    float f = t * t;
    t = u * (g - u) + 1.F;
    f /= t * t;
    f += 1.F;
    t = g - u;
    f *= t * t;
    t = g + u;
    f /= 2.F * t * t;
    return f;
}
