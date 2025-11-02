// RC  10/1/2001  \Randy90\Plugin\Textures\WaterColour\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "TexApp.h"

extern CTextureApp theApp;

template <typename T>
constexpr auto snoise(T x) { return 2.F * theApp.Noise(x) - 1.F; }

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
        case 7:
            return m_fuzz;
        case 8:
            return m_xs;
        case 9:
            return m_ys;
        case 10:
            return m_pencil;
        case 11:
            return m_light;
        case 12:
            return m_rough;
        case 13:
            return m_var;
        case 14:
            return m_vscale;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    const RGBFloat color2(m_fcolor->GetNormalizedRGBFloat());
    RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    if (m_useback->GetValue()) {
        color = origcolor;
    }

    Vector nn = *texinfo->GetN();
    Vector dd(-m_light->GetX()->GetValue(), -m_light->GetY()->GetValue(), m_light->GetZ()->GetValue());
    nn.Normalize();
    dd.Normalize();
    Vector P = evalp;
    P.x *= m_xs->GetValue();
    P.y *= m_ys->GetValue();
    P.z *= m_xs->GetValue();

    const float noise = theApp.Noise(P);
    float alpha = nn.Dot(dd);
    float rough = m_rough->GetValue() / 100.F;
    const float mix = m_mix->GetValue() / 100.F;
    const float variation = m_mix->GetValue() / 100.F;
    const float vscale = m_vscale->GetValue();
    const RGBFloat white(1.F, 1.F, 1.F);

    alpha = (1.F + alpha) / 2.F;
    if (vscale != 0.F)
        alpha += snoise(P / vscale) * variation;
    else
        alpha += snoise(P) * variation;
    alpha = hash_math::pow(alpha, m_fref->GetValue());

    if (alpha > m_pencil->GetValue() / 100.F) {
      //do nothing  
    } else if (alpha > m_pencil->GetValue() / 100.F - .1F) {
        const float m = (alpha - m_pencil->GetValue() / 100.F) / 0.1F;
        color = m * color2 + (1.F - m) * color;
    } else if (alpha > m_fuzz->GetValue() / 100.F)
        color = color2;
    else if (alpha > m_fuzz->GetValue() / 100.F - .1F) {
        float m = (alpha - m_fuzz->GetValue() / 100.F) / 0.1F;
        m = m / 3.F;
        color = m * white + (1.F - m) * color2;
    } else
        color = white;
    rough *= noise * noise;
    //   color = (alpha * color) + ((1-alpha) * color2);
    color = (1.F - rough) * color + rough * white;
    //   texinfo.attr->SetDiffuseColor(color * mix + origcolor * (1.F-mix));
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));

    return TRUE;
}
