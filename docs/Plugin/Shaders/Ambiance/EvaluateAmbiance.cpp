// KB  8/28/2003  \Ken110\Plugin\Shaders\Ambiance\EvaluateAmbiance.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_ambiancecolor;
    return nullptr;
}

const char *CustomShader::GetShaderDiffuseFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderSpecularFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderAmbianceFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return FALSE;
}

void CustomShader::GetAmbiance(HShading *shading) {
    shading->SetACol(m_ambiancecolor->GetNormalizedRGBFloat());
}
