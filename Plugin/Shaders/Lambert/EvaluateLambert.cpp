// KB  2/6/01  \Ken90\Plugin\Shaders\Lambert\EvaluateLambert.cpp

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
    HAttrProperty *hattr = htexinfo->GetAttr();
    RGBFloat dcol = shading->GetDCol();
    const float diffusefalloff = hattr->GetDiffuseFallOff()->GetValue();
    if (diffusefalloff != 1.F) {
        if (diffusefalloff) {
            float temp;
            if ((temp = shading->GetLDot() * 1.F / diffusefalloff) > 1.F)
                temp = 1.F;
            dcol *= temp;
        }
    } else
        dcol *= shading->GetLDot();
    shading->SetDCol(dcol);
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}
