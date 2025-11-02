// KB  2/4/2003  \Ken105\Plugin\Shaders\Anisotropic\EvaluateAnisotropic.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"
#include "Matrix34.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_roughnessx;
        case 1:
            return m_roughnessy;
        case 2:
            return m_grain;
        default:
            return nullptr;
    }
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
    //   Vector m_grain(1.F,0.F,0.F);
    //   float m_roughnessx = .15f;
    //   float m_roughnessy = .5f;
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    HColorProperty *specularcolor = hattr->GetSpecularColorForRead();
    const float intensity = shading->GetIntensity();

    if (hattr->GetSpecularIntensity()->GetValue() > 0.005f) {
        m_normgrain = m_grain->GetValue();
        TransformVectorNoTranslate(*htexinfo->GetMatrix(), m_normgrain);
        m_normgrain.Normalize();

        const Vector X = m_normgrain / m_roughnessx->GetValue();
        Vector Y = *htexinfo->GetN() ^ m_normgrain;
        Y /= m_roughnessy->GetValue();
        Vector H = *shading->GetL();
        H += htexinfo->GetD();
        H.Negate();
        H.Normalize();

        float rho = shading->GetLDot() * exp(-2.F * (hash_math::sqr(X.Dot(H)) + hash_math::sqr(Y.Dot(H))) / (1.F + H.Dot(*htexinfo->GetN()))) / hash_math::sqrt(shading->GetLDot() * shading->GetEDot())
        / (4.0f * m_roughnessx->GetValue() * m_roughnessy->GetValue());

        rho *= hattr->GetSpecularIntensity()->GetValue();

        RGBFloat speccolor = rho;
        if (specularcolor->GetRed()->GetValue() == 1.F && specularcolor->GetGreen()->GetValue() == 1.F && specularcolor->GetBlue()->GetValue() == 1.F)
            speccolor *= lightcolor * intensity;
        else
            speccolor *= specularcolor->GetNormalizedRGBFloat() * intensity;

        shading->SetSCol(speccolor);
        return TRUE;
    }
    return FALSE;
}
