// \Plugin\Shaders\Brushed\EvaluateBrushed.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"
#include "Matrix34.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_grain;
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
    size = hash_math::sqrt(0.5f / size); // This is to match Phong specular sizes
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    if (Ks == 0.F)
        return false;
    const RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat() * Ks;
    const RGBFloat Cl = lightcolor * shading->GetIntensity();
//    Vector &N = *htexinfo->GetN();
    const Vector &L = *shading->GetL();
    const Vector I = htexinfo->GetD();
    Vector ng = m_grain->GetValue();
    TransformVectorNoTranslate(*htexinfo->GetMatrix(), ng);
    ng.Normalize();
    const float cos_eye = -ng.Dot(I);
    const float sin_eye = hash_math::sqrt(1.F - cos_eye * cos_eye);
    const float cos_light = ng.Dot(L);
    const float sin_light = hash_math::sqrt(1.F - cos_light * cos_light);
    float aniso = MAX(cos_light * cos_eye + sin_light * sin_eye, 0.F);
    aniso = hash_math::pow(aniso, hash_math::rcp(size));
    const float shad = MAX(shading->GetEDot(), 0.F) * MAX(shading->GetLDot(), 0.F);
    const RGBFloat speccolor = Cs * Cl * aniso * shad;
    shading->SetSCol(speccolor);
    return true;
}
