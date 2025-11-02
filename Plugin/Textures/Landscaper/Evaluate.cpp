// KB  10/23/01  \Ken90\Plugin\Textures\Landscaper\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

template <typename T>
constexpr auto snoise(T x) { return 2.F * theApp.Noise(x) - 1.F; }

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_fcolor1;
        case 1:
            return m_fcolor2;
        case 2:
            return m_fcolor3;
        case 3:
            return m_foct;
        case 4:
            return m_ffreq;
        case 5:
            return m_fnt;
        case 6:
            return m_scolor1;
        case 7:
            return m_scolor2;
        case 8:
            return m_scolor3;
        case 9:
            return m_soct;
        case 10:
            return m_sfreq;
        case 11:
            return m_sbump;
        case 12:
            return m_snt;
        case 13:
            return m_falloff;
        case 14:
            return m_offset;
        case 15:
            return m_scale;
        case 16:
            return m_height;
        case 17:
            return m_aslope;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CustomTexture::calcNoise(const Vector P, const int ntype, const float octaves, const float freq) {
    if (ntype == 0) {
        return 1.F;
    }
    int i;
    float sum = 0.F;
    if (ntype == 1) {
        // fractal
        float a = 1.F;
        Vector pp = P * freq;
        for (i = 0; i < octaves; ++i) {
            sum += theApp.Noise(pp) * a;
            a *= 0.5F;
            pp *= 2.F;
        }
    } else if (ntype == 2) {
        // strata - based on y
        const float a = P.y * freq + snoise(P / octaves);
        const Vector pp(a, a, a);
        sum = snoise(pp);
    } else if (ntype == 3 || ntype == 7) {
        // fbm
        Vector pp = P * freq;
        float a = 1.F;
        for (i = 0; i < octaves; ++i) {
            sum += a * theApp.Noise(pp);
            a *= 0.5F;
            pp *= 2.0;
        }
        sum = 2.F * sum - 1.F;
    } else if (ntype == 4 || ntype == 6) // turbulence
    {
        Vector pp = P * freq;
        for (i = 0; i < octaves; ++i) {
            sum += snoise(pp);
            //a*=0.7f;
            pp *= 1.40F;
        }
    } else if (ntype == 5) // simplenoise -stretched x
    {
        Vector pp = P * freq;
        pp.x /= 5.0F;
        for (i = 0; i < octaves; ++i) {
            sum += snoise(pp);
            pp *= 1.5F;
        }
    } else if (ntype == 8) {
        const Vector pp = P * freq;
        constexpr Vector nf(1.F, 1.F, 1.F);
        constexpr Vector nf2(0.F, 1.F, 2.F);

        const float dir = snoise(nf);
        const float dir2 = snoise(nf2);

        Vector wav(dir, 0.F, dir2);
        float Km = 1.0F;

        //P.Normalize();
        for (int i1 = 0; i1 < octaves; ++i1) {
            Vector ii((float)i1);
            sum += Km * hash_math::cos(pp.Dot(wav));
            wav.x += snoise(ii);
            wav.z += snoise(-ii);

            Km *= 0.707F;
        }
    }
    if (sum < -1.F)
        sum = -1.F;
    else if (sum > 1.F)
        sum = 1.F;
    return sum;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    RGBFloat flat1(m_fcolor1->GetNormalizedRGBFloat());
    RGBFloat flat2(m_fcolor2->GetNormalizedRGBFloat());
    RGBFloat flat3(m_fcolor3->GetNormalizedRGBFloat());

    RGBFloat slope1(m_scolor1->GetNormalizedRGBFloat());
    RGBFloat slope2(m_scolor2->GetNormalizedRGBFloat());
    RGBFloat slope3(m_scolor3->GetNormalizedRGBFloat());

    float falloff = m_falloff->GetValue();
    Vector neweval = evalp;
    // position and scale
    neweval.x += m_offset->GetX()->GetValue();
    neweval.y += m_offset->GetY()->GetValue();
    neweval.z += m_offset->GetZ()->GetValue();

    neweval.x /= m_scale->GetX()->GetValue();
    neweval.y /= m_scale->GetY()->GetValue();
    neweval.z /= m_scale->GetZ()->GetValue();

    Vector up(0.F, 1.F, 0.F);
    Vector nn = *texinfo->GetN();
    nn.Normalize();
    float mix = hash_math::abs(up.Dot(nn));

    float fn = calcNoise(neweval, m_fnt->GetValue(), m_foct->GetValue(), m_ffreq->GetValue());
    float sn = calcNoise(neweval, m_snt->GetValue(), m_soct->GetValue(), m_sfreq->GetValue());
    float xx = fn;
    // flat value
    RGBFloat out1, out2;
    if (fn < -0.5F) {
        fn = hash_math::abs(fn) * 2.F - 1.F;
        out1 = fn * flat1 + (1.F - fn) * flat2;
    } else if (fn < 0.5F) {
        fn = 0.5F + fn;
        out1 = fn * flat3 + (1.F - fn) * flat2;
    } else {
        fn = hash_math::abs(fn) * 2.F - 1.F;

        out1 = fn * flat1 + (1.F - fn) * flat3;
    }

    // slope value
    if (sn < -0.5F) {
        sn = hash_math::abs(sn) * 2.F - 1.F;
        out2 = sn * slope1 + (1.F - sn) * slope2;
    } else if (sn < 0.5F) {
        sn = 0.5F + sn;
        out2 = sn * slope3 + (1.F - sn) * slope2;
    } else {
        sn = sn * 2.F - 1.F;
        out2 = sn * slope1 + (1.F - sn) * slope3;
    }
    mix = hash_math::pow(mix, falloff);
    RGBFloat outcol = mix * out1 + (1 - mix) * out2;

    // also fade with height.
    float alt = m_height->GetValue();

    if (alt > 0.F && evalp.y > 0.F) {
        if (m_aslope->GetValue() > 0) {
            out1 = out2; // set high values to be slope instead of flat
        }
        if (evalp.y > alt) {
            outcol = out1; // flat colour
        } else {
            alt = evalp.y / alt;
            outcol = alt * out1 + (1.F - alt) * outcol;
        }
    }
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(outcol);
    // bump if type > 5
    if (m_fnt->GetValue() > 5) {
        Vector ca = neweval;
        Vector V(0.F, 1.F, 0.F);
        Vector N = *texinfo->GetN();
        V = V - V.Dot(N) * N;
        Vector U = V.Cross(N);
        V = U.Cross(N);
        U.Normalize();
        V.Normalize();
        U *= .4f;
        V *= .4f;
        ca += U;
        float dx = calcNoise(ca, m_snt->GetValue(), m_soct->GetValue(), m_sfreq->GetValue());
        ca -= U;
        ca += V;
        float dy = calcNoise(ca, m_snt->GetValue(), m_soct->GetValue(), m_sfreq->GetValue());
        dx = xx - dx;
        dy = xx - dy;
        U = U * (dx * 0.2F);
        V = V * (dy * 0.2F);
        *texinfo->GetN() += U;
        *texinfo->GetN() += V;
        texinfo->GetN()->Normalize();
    }
    return TRUE;
}
