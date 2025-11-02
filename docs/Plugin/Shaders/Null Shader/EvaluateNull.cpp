// Yves  2005-11-22  \Master13.0\Plugin\Shaders\Null\EvaluateNull.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(int i) {
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
    shading->SetDCol(RGBFloat(0.F, 0.F, 0.F));
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    shading->SetSCol(RGBFloat(0.F, 0.F, 0.F));
    return true;
}
