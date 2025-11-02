// MH  8/28/2008 Created.

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
    return nullptr;
}

void CustomShader::GetDiffuse(HShading *shading) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    const Vector &N = *htexinfo->GetN();
    RGBFloat Cs(1.F, 1.F, 1.F);
    constexpr Vector vertical(0.F, 1.F, 0.F);
    White((1.F + vertical.Dot(N)) / 2.F, Cs);
    shading->SetDCol(Cs);
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return TRUE;
}

void CustomShader::White(const float u, RGBFloat &Cs) {
    // u is the cosine between normal and the ground
    Cs = RGBFloat(1.F) * u;
}
