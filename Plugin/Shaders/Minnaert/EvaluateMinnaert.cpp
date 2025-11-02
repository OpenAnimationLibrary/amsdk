// Yves  2006-01-16  \Master13.00\Plugin\Shaders\Minnaert\EvaluateMinnaert.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_roughness;
    return nullptr;
}

const char *CustomShader::GetShaderDiffuseFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

const char *CustomShader::GetShaderSpecularFilters() {
    return nullptr;
}

void CustomShader::GetDiffuse(HShading *shading) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const RGBFloat Cd = hattr->GetDiffuseColor()->GetNormalizedRGBFloat();
    const float e = hash_math::pow(shading->GetEDot() * shading->GetLDot(), m_roughness->GetValue() - 1.F);
    shading->SetDCol(Cd * e);
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}
