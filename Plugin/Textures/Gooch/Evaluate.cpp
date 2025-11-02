// RC  10/1/2001  \Randy90\Plugin\Textures\Gooch\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

template<typename T>
constexpr auto snoise(T x) { return 2.F*theApp.Noise(x)-1.F; }

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_amplitude;
        case 1:
            return m_useback;
        case 2:
            return m_bcolor;
        case 3:
            return m_fcolor;
        case 4:
            return m_noise;
        case 5:
            return m_freq;
        case 6:
            return m_mix;
        case 7:
            return m_scalex;
        case 8:
            return m_scaley;
        case 9:
            return m_light;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat color1(m_fcolor->GetNormalizedRGBFloat());
    RGBFloat color(m_bcolor->GetNormalizedRGBFloat());

    const RGBFloat kblue(m_scalex->GetValue() / 100.F, 0.F, 0.F);
    const RGBFloat kyellow(0, m_scaley->GetValue() / 100.F, m_scaley->GetValue() / 100.F);
    Vector l(-m_light->GetX()->GetValue(), -m_light->GetY()->GetValue(), m_light->GetZ()->GetValue());
    const RGBFloat kcool = kblue + m_mix->GetValue() / 100.F * color;
    const RGBFloat kwarm = kyellow + m_amplitude->GetValue() / 100.F * color1;
    float alpha = hash_math::atan(evalp.z / evalp.x) / hash_constants::pi_2;
    alpha *= 10.F;
    Vector pp(alpha);
    float turb = 0.F;
    const float f2 = m_freq->GetValue();
    const float freq = m_noise->GetValue();
    pp.z += 20.F * f2;
    turb += hash_math::abs(snoise(pp * f2 + pp));
    l.Normalize();
    const Vector N = *texinfo->GetN();

    float t = l.Dot(N);
    if (freq > 0)
        t *= turb * freq;
    color = (1.F + t) / 2.F * kcool + (1.F - (1.F + t) / 2.F) * kwarm;

    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color);

    return TRUE;
}
