// Yves  2006-01-16  \Master13.0\Plugin\Shaders\Blinn\EvaluateBlinn.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_Attenuation;
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
    const RGBFloat Cl = lightcolor * shading->GetIntensity() * shading->GetLDot();
    shading->SetSCol(GetBRDF(shading, htexinfo, hattr, size) * Cl * Ks);
    return true;
}

RGBFloat CustomShader::GetBRDF(HShading *shading, HTexInfo *htexinfo, HAttrProperty *hattr, const float size) {
    RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const Vector V = -htexinfo->GetD();
    const Vector L = -*shading->GetL();
    const Vector N = *htexinfo->GetN();
    Vector H = V + L;
    H.Normalize();
    const float h = H.Dot(N);
    const float u = H.Dot(V);
    const float v = shading->GetEDot();
    const float l = shading->GetLDot();
    const float Dd = safe_pow(h, size); // Blinn uses his H vector for the distribution
    float Gg;
    if (m_Attenuation->GetValue() == 0) {
        // Default is TorranceSparrow Geometric Attenuation
        Gg = 2.F * h / u;
        if (v < l)
            Gg *= v;
        else
            Gg *= l;
        if (Gg > 1.F)
            Gg = 1.F;
    } else {
        // Alternative is Sancer Attenuation
        if (m_savedsize != size) {
            m_2m2 = -2.F * safe_pow(2.F, -1.F + 2.F / size) * (1.F - safe_pow(2.F, -2.F / size)) / hash_math::log(safe_pow(2.F, -4.0f / size));
            m_savedsize = size;
        }
        const float l2 = l * l;
        const float v2 = v * v;
        const float c1 = l2 / (m_2m2 * (1.F - l2));
        const float c2 = v2 / (m_2m2 * (1.F - v2));
        const float ci = safe_pow(0.05f / c1, 0.63f) - 0.14f; // An quicker approximation for the 2 lines above.
        const float cr = safe_pow(0.05f / c2, 0.63f) - 0.14f;
        Gg = hash_math::rcp(1.F + ci + cr);
    }
    Fresnel(h, Cs);
    return Cs * (Dd * Gg / v);
}

/* org
void CustomShader::Fresnel(const float u, RGBFloat &Cs) {
    float f = 1.F - u;
    const float ff = f * f;
    f *= ff * ff;
    Cs += (RGBFloat(1.F, 1.F, 1.F) - Cs) * f;
}
*/

constexpr float ComputeFresnelTerm(const float inputvalue) {
    float f = 1.F - inputvalue;
    const float ff = f * f;
    f *= ff * ff;
    return f;
}

void CustomShader::Fresnel(const float u, RGBFloat &Cs) {
    Cs += (RGBFloat(1.F) - Cs) * ComputeFresnelTerm(u);
}
