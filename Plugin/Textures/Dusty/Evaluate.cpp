// RC  10/1/2001  \Randy90\Plugin\Textures\Dusty\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_bcolor;
        case 1:
            return m_bo;
        case 2:
            return m_noise;
        case 3:
            return m_freq;
        case 4:
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

    Vector nn = *texinfo->GetN();
    if (const float noi = m_noise->GetValue() / 10.F; noi > 0.F) {
        const Vector n_n = evalp * m_freq->GetValue();
        if (n_n.IsNotZero())
            nn += theApp.Noise(n_n / 10.F) * noi;
        else
            nn += theApp.Noise(n_n) * noi;
    }

    nn.Normalize();
    float alpha = nn.y;

    alpha = alpha < 0.F ? 0.F : alpha;
    alpha = hash_math::pow(alpha, m_bo->GetValue());
    color = color * alpha + (1.F - alpha) * origcolor;
    // mix it
    const float mix = m_mix->GetValue() / 100.F;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));

    return TRUE;
}
