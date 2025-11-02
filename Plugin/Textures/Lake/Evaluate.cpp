// RC  10/1/2001  \Randy90\Plugin\Textures\Lake\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

template<typename T>
constexpr auto snoise(T x) { return 2.F*theApp.Noise(x)-1.F; }

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_useback;
        case 1:
            return m_bcolor;
        case 2:
            return m_fcolor;
        case 3:
            return m_bref;
        case 4:
            return m_bo;
        case 5:
            return m_fref;
        case 6:
            return m_fo;
        case 7:
            return m_noise;
        case 8:
            return m_bump;
        case 9:
            return m_amplitude;
        case 10:
            return m_mix;
        case 11:
            return m_offset;
        case 12:
            return m_scale;
        case 13:
            return m_wo;
        case 14:
            return m_wamp;
        case 15:
            return m_wlac;
        case 16:
            return m_wgain;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CustomTexture::fracSum(const Vector P, const float octaves) const {
    const float windfreq = m_wlac->GetValue() / 100.F;
    const float windamp = m_wgain->GetValue() / 100.F;
    const float minwind = m_wamp->GetValue() / 100.F;
    const float Km = octaves;

    Vector PP = windfreq * P;
    const float offset = Km * (snoise(PP) + 0.5F * snoise(2.F * PP));

    float turb = 0.F;
    float a = 1.F;
    PP *= 8.0F;
    const int oct = m_wo->GetValue();
    for (int i = 0; i < oct; ++i) {
        turb += hash_math::abs(a * snoise(PP));
        PP *= 2.F;
        a /= 2.F;
    }
    const float wind = minwind + windamp * turb;
    const float sum = wind * offset;
    return sum;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat color1(m_fcolor->GetNormalizedRGBFloat());
//    RGBFloat origcolor = texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat();
    const RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    const float opac = m_bo->GetValue() / 100.F;
    const float opac1 = m_fo->GetValue() / 100.F;
    const float ref = m_bref->GetValue() / 100.F;
    const float ref1 = m_fref->GetValue() / 100.F;

    const float noise = m_amplitude->GetValue();
    Vector e;
    e.x = evalp.x / m_scale->GetX()->GetValue() + m_offset->GetX()->GetValue();
    e.y = evalp.y / m_scale->GetY()->GetValue() + m_offset->GetY()->GetValue();
    e.z = evalp.z / m_scale->GetZ()->GetValue() + m_offset->GetZ()->GetValue();

    float bu = m_bump->GetValue();
    Vector ca;
    ca.x = e.x;
    ca.y = e.y;
    ca.z = e.z;
    const float x = fracSum(ca, noise);
    //
    Vector V(0.F, 1.F, 0.F);
    const Vector N = *texinfo->GetN();
    V = V - V.Dot(N) * N;
    Vector U = V.Cross(N);
    V = U.Cross(N);
    U.Normalize();
    V.Normalize();
    U *= 0.44F;
    V *= 0.44F;
    bu *= 0.1F;
    ca += U;
    float dx = fracSum(ca, noise);
    ca.x = e.x;
    ca.y = e.y;
    ca.z = e.z;
    ca += V;
    float dy = fracSum(ca, noise);
    //
    if (bu < 0.F) {
        bu = hash_math::abs(bu);
        dx = x - dx;
        dy = x - dy;
    } else {
        dx = x - dx;
        dy = x - dy;
    }
    U = U * (dx * x * bu);
    V = V * (dy * x * bu);
    *texinfo->GetN() += U;
    *texinfo->GetN() += V;
    texinfo->GetN()->Normalize();
    const Vector d = texinfo->GetD();
    const Vector nn = *texinfo->GetN();
    const float mix = hash_math::abs(nn.Dot(d));
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + color1 * (1.F - mix));
    texinfo->GetAttr()->GetReflectivity()->SetValue(ref * mix + ref1 * (1.F - mix));

    texinfo->GetAttr()->GetTransparency()->SetValue(opac * mix + opac1 * (1.F - mix));

    return TRUE;
}
