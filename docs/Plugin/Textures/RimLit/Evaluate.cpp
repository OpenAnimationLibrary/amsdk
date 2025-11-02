// RC  10/1/2001  \Randy90\Plugin\Textures\RimLit\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "TexApp.h"

extern CTextureApp theApp;

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_bcolor;
        case 1:
            return m_light;
        case 2:
            return m_fo;
        case 3:
            return m_mix;
        default:
            return nullptr;
    }
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    Vector Light(-m_light->GetX()->GetValue(), -m_light->GetY()->GetValue(), m_light->GetZ()->GetValue());

    Vector nn = *texinfo->GetN();
    Light.Normalize();
    nn.Normalize();
    float alpha = 1.F - Light.Dot(nn);

    alpha = alpha > 1.F ? 1.F : alpha;

    alpha = hash_math::pow(alpha, m_fo->GetValue());
    color = color * alpha + (1 - alpha) * origcolor;
    // mix it
    const float mix = m_mix->GetValue() / 100.F;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));
    texinfo->GetAttr()->GetDiffuseFallOff()->SetValue(1.F - alpha * mix);
    //texinfo.attr->SetAmbiance((alpha)*mix);

    return TRUE;
}
