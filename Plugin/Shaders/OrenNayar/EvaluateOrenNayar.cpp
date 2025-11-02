// KB  2/19/2004  \Master110\Plugin\Shaders\OrenNayar\EvaluateOrenNayar.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"
#include "SDK/HModel.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_roughness;
        case 1:
            return m_brightness;
        default:
            return nullptr;
    }
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
    const Vector &L = *shading->GetL();
    const Vector V = htexinfo->GetD();
    float ldot = shading->GetLDot();
    if (ldot > 1.F) {
        ldot = 1.F;
    }
    if (ldot < -1.F) {
        ldot = -1.F;
    }
    float edot = shading->GetEDot();
    if (edot > 1.F) {
        edot = 1.F;
    }
    if (edot < -1.F) {
        edot = -1.F;
    }

    float roughsquare = m_roughness->GetValue();
    roughsquare *= roughsquare;

    const Vector phieye = N ^ V;
    const Vector philight = N ^ L;
    const float A = 1.F - .5f * roughsquare / (roughsquare + .33f);
    const float B = .45f * roughsquare / (roughsquare + .09f);
    const float thetaeye = hash_math::cos(edot);
    const float thetalight = hash_math::cos(ldot);
    const float alpha = MAX(thetaeye, thetalight);
    const float beta = MIN(thetaeye, thetalight);

    float lambert;
    const float temp = phieye.Dot(philight);
    if (temp > 0.F)
        lambert = m_brightness->GetValue() * ldot * (A + B * temp * hash_math::sin(alpha) * hash_math::tan(beta));
    else
        lambert = m_brightness->GetValue() * ldot * A;

    shading->SetDCol(shading->GetDCol() * lambert);
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}
