// RC  10/1/2001  \Randy90\Plugin\Textures\Brick\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "TexApp.h"

extern CTextureApp theApp;

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_bwidth;
        case 1:
            return m_bheight;
        case 2:
            return m_bdepth;
        case 3:
            return m_noise;
        case 4:
            return m_freq;
        case 5:
            return m_bump;
        case 6:
            return m_bref;
        case 7:
            return m_bo;
        case 8:
            return m_fref;
        case 9:
            return m_fo;
        case 10:
            return m_amplitude;
        case 11:
            return m_msize;
        case 12:
            return m_fuzz;
        case 13:
            return m_mix;
        case 14:
            return m_offset;
        case 15:
            return m_scale;
        case 16:
            return m_useback;
        case 17:
            return m_bcolor;
        case 18:
            return m_fcolor;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CustomTexture::calcBrickVal(const Vector *v) const {
    const float bwidth = m_bwidth->GetValue();
    const float bheight = m_bheight->GetValue();
    const float bdepth = m_bdepth->GetValue();
    const float mwidth = m_msize->GetValue();
    const float fuzz = m_fuzz->GetValue();
    float ss = v->x / bwidth;
    float tt = v->y / bheight;
    float uu = v->z / bdepth;
    if (hash_math::fmod(tt * 0.5F, 1.F) > 0.5F) {
        ss += 0.5F;
    }

    const float tbrick = hash_math::floor(tt);
    const float sbrick = hash_math::floor(ss);
    const float ubrick = hash_math::floor(uu);

    ss -= sbrick;
    tt -= tbrick;
    uu -= ubrick;

    const float bmw = bwidth + mwidth;
    const float bmh = bheight + mwidth;
    const float bmd = bdepth + mwidth;

    const float mwf = mwidth * 0.5F / bmw;
    const float mhf = mwidth * 0.5F / bmh;
    const float mdf = mwidth * 0.5F / bmd;

    const float w = pulse(fuzz + mwf, 1.F - mwf, fuzz / 2.F, ss);
    const float h = pulse(fuzz + mhf, 1.F - mhf, fuzz, tt);
    const float d = pulse(fuzz + mdf, 1.F - mdf, fuzz, uu);

    const float m = w * h * d;
    return m;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat color1(m_fcolor->GetNormalizedRGBFloat());
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    RGBFloat color = m_bcolor->GetNormalizedRGBFloat();
    if (m_useback->GetValue()) {
        color = origcolor;
    }

    Vector e(evalp);
    e.x += m_offset->GetX()->GetValue();
    e.y += m_offset->GetY()->GetValue();
    e.z += m_offset->GetZ()->GetValue();
    
    if (const float noi = m_noise->GetValue() / 10.F; noi > 0.F) {
        if (const Vector e_n = e * m_freq->GetValue(); e_n.IsNotZero())
            e += theApp.Noise(e_n / 10.F) * noi;
        else
            e += theApp.Noise(e_n) * noi;
    }

    e.x /= m_scale->GetX()->GetValue();
    e.y /= m_scale->GetY()->GetValue();
    e.z /= m_scale->GetZ()->GetValue();

    const float mix = m_mix->GetValue() / 100.F;
    Vector ca(e);
    const float x = calcBrickVal(&ca);

    color = color * x + color1 * (1.F - x);
    if (float bu = m_bump->GetValue(); bu > 0.F) {
        ca = e;
        Vector V(0.F, 1.F, 0.F);
        const Vector N = *texinfo->GetN();
        V = V - V.Dot(N) * N;
        Vector U = V.Cross(N);
        V = U.Cross(N);
        U.Normalize();
        V.Normalize();
        U *= .3F;
        V *= .3F;
        bu /= 10.F;
        ca += U;
        float dx = calcBrickVal(&ca);
        ca.x = e.x;
        ca.y = e.y;
        ca.z = e.z;
        ca += V;

        float dy = calcBrickVal(&ca);
        dx = hash_math::abs(x - dx);
        dy = hash_math::abs(x - dy);
        U = U * (dx * x * bu);
        V = V * (dy * x * bu);
        *texinfo->GetN() += U;
        *texinfo->GetN() += V;
        texinfo->GetN()->Normalize();
    }
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));

    return TRUE;
}
