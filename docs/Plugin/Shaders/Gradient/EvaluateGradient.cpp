// KB  11/15/2002  \Ken100\Plugin\Shaders\Gradient\EvaluateGradient.cpp

#include "StdAfx.h"
#include "resource.h"
#include "Custom.h"
#if defined(_DEBUG) || defined(DEBUG)
#include "F_Protos.h"
#endif

HProperty *CustomShader::GetPropertyAt(const int i) {
    if (i == 0)
        return m_gradient;
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
#if defined(_DEBUG) || defined(DEBUG)
    ASSERT(false);
    if (GetRegistryString("General", "GradTest", "ON") == "ON") {
        shading->SetDCol(RGBFloat(shading->GetHitP().z));
    } else {
#else
   {
#endif
        RGBFloat dcolor = shading->GetDCol();
        const RGBFloat color = m_gradient->GetColor(dcolor, shading->GetLDot());
        shading->SetDCol(color);
    }
}

// Does nothing.  The GetShaderSpecularFilters() should prevent this from being called.
bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}
