// RC  10/1/2001  \Randy90\Plugin\Textures\Macro\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_useback;
        case 1:
            return m_bcolor;
        case 2:
            return m_fcolor;
        case 3:
            return m_fref;
        case 4:
            return m_fo;
        case 5:
            return m_bo;
        case 6:
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
    RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    const RGBFloat color2(m_fcolor->GetNormalizedRGBFloat());
    if (m_useback->GetValue()) {
        color = origcolor;
    }

    Vector nn = *texinfo->GetN();
    nn.Normalize();
    Vector dd = texinfo->GetD();
    dd.Normalize();

    float alpha = nn.Dot(dd);
    alpha = hash_math::abs(alpha);
    alpha = hash_math::pow(alpha, m_fref->GetValue());

    const float trans = m_bo->GetValue() / 100.F * alpha + m_fo->GetValue() / 100.F * (1.F - alpha);
    texinfo->GetAttr()->GetTransparency()->SetValue(trans);
    color = alpha * color + (1.F - alpha) * color2;

    const float mix = m_mix->GetValue() / 100.F;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));

    return TRUE;
}
