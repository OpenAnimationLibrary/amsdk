// RC  10/1/2001  \Randy90\Plugin\Textures\XRay\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_useback;
        case 1:
            return m_bcolor;
        case 2:
            return m_bo;
        case 3:
            return m_mix;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    const RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    Vector nn = *texinfo->GetN();
    Vector dd = texinfo->GetD();
    nn.Normalize();
    dd.Normalize();
    float alpha = nn.Dot(dd);
    alpha = hash_math::abs(alpha);
    alpha = hash_math::pow(alpha, m_bo->GetValue());

    texinfo->GetAttr()->GetTransparency()->SetValue(alpha);
    const float mix = m_mix->GetValue() / 100.F;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));

    return TRUE;
}
