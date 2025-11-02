// KB  9/23/02  \Ken95\Plugin\Textures\Weave\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "TexApp.h"

extern CTextureApp theApp;

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
            return m_bref;
        case 6:
            return m_bo;
        case 7:
            return m_amplitude;
        case 8:
            return m_noise;
        case 9:
            return m_freq;
        case 10:
            return m_bump;
        case 11:
            return m_fuzz;
        case 12:
            return m_mix;
        case 13:
            return m_scale;
        case 14:
            return m_map;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat color1(m_fcolor->GetNormalizedRGBFloat());
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    if (m_useback->GetValue()) {
        color = origcolor;
    }
    const float noise = theApp.Noise(evalp * (m_freq->GetValue() / 10.F)) * (m_noise->GetValue() / 10.F);
    float s, t;
    if (m_map->GetValue() == 4) {
        // revert to older Weave code
        s = evalp.x + noise;
        t = evalp.y + noise;
    } else {
        const Vector P = evalp + (2.F * noise - 1.F);
        CalcUV(P, &s, &t, m_map->GetValue());
    }
    float xfreq = m_scale->GetX()->GetValue();
    float yfreq = m_scale->GetY()->GetValue();
    if (m_map->GetValue() == 4) {
        // revert to older Weave code
        xfreq /= 10.F;
        yfreq /= 10.F;
    }

    const float ss = repeat(s, xfreq);
    const float tt = repeat(t, yfreq);
    const float col = whichtile(s, xfreq);
    const float row = whichtile(t, yfreq);
    const float fuzz = m_fuzz->GetValue() / 100.F / 2.F;
    const float size = 0.5F - m_amplitude->GetValue() / 100.F / 2.F;
    RGBFloat outcol;
    Vector outopac;
    float outref;
    const float fr = m_fref->GetValue() / 100.F;
    const float br = m_bref->GetValue() / 100.F;
    const Vector fo(m_fo->GetValue() / 100.F);
    const Vector bo(m_bo->GetValue() / 100.F);
    const Vector origo(texinfo->GetAttr()->GetTransparency()->GetValue());
    const float origr = texinfo->GetAttr()->GetReflectivity()->GetValue();

    float layer_opac;
    if ((even(row) && odd(col)) || (even(col) && odd(row))) {
        /* vertical bar */

        layer_opac = pulse(fuzz + size, 1.F - size, fuzz, ss);
        if (m_map->GetValue() != 4)
            layer_opac *= hash_math::sin(hash_constants::pi * ss);
        outcol = color * layer_opac + origcolor * (1.F - layer_opac);
        outopac = bo * layer_opac + origo * (1.F - layer_opac);
        outref = br * layer_opac + origr * (1.F - layer_opac);

        /* horizontal bar */

        layer_opac = pulse(fuzz + size, 1.F - size, fuzz, tt);
        if (m_map->GetValue() != 4)
            layer_opac *= hash_math::sin(hash_constants::pi * tt);
        outcol = color1 * layer_opac + outcol * (1.F - layer_opac);
        outopac = fo * layer_opac + outopac * (1.F - layer_opac);
        outref = fr * layer_opac + outref * (1.F - layer_opac);
    } else {
        /* horizontal bar */

        layer_opac = pulse(fuzz + size, 1.F - size, fuzz, tt);
        if (m_map->GetValue() != 4)
            layer_opac *= hash_math::sin(hash_constants::pi * tt);

        outcol = color1 * layer_opac + origcolor * (1.F - layer_opac);
        outopac = fo * layer_opac + origo * (1.F - layer_opac);
        outref = fr * layer_opac + origr * (1.F - layer_opac);

        /* vertical bar */

        layer_opac = pulse(fuzz + size, 1.F - size, fuzz, ss);
        if (m_map->GetValue() != 4)
            layer_opac *= hash_math::sin(hash_constants::pi * ss);

        outcol = color * layer_opac + outcol * (1.F - layer_opac);
        outopac = bo * layer_opac + outopac * (1.F - layer_opac);
        outref = br * layer_opac + outref * (1.F - layer_opac);
    }

    // mix with previous
    const float mix = m_mix->GetValue() / 100.F;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(outcol * mix + origcolor * (1.F - mix));
    const Vector temp = outopac * mix + origo * (1.F - mix);
    texinfo->GetAttr()->GetTransparency()->SetValue(temp.x);
    texinfo->GetAttr()->GetReflectivity()->SetValue(outref * mix + origr * (1.F - mix));

    //    noise *= m_bump->GetValue() / 100.F;

    return TRUE;
}

void CustomTexture::CalcUV(const Vector e, float *u, float *v, const int type) {
    float ele = 0.F, az = 0.F;
    Vector temp(e);
    temp.Normalize();

    switch (type) {
        case 0:
            az = (-hash_math::atan2(temp.z, temp.x) + hash_constants::pi) / (2.F * hash_constants::pi);
            ele = 0.5F - hash_math::cos(temp.y) / hash_constants::pi;
            break;
        case 1:
            az = (-hash_math::atan2(temp.z, temp.y) + hash_constants::pi) / (2.F * hash_constants::pi);
            ele = temp.x;
            break;
        case 2:
            az = (-hash_math::atan2(temp.z, temp.x) + hash_constants::pi) / (2.F * hash_constants::pi);
            ele = temp.y;
            break;
        case 3:
            az = (-hash_math::atan2(temp.x, temp.y) + hash_constants::pi) / (2.F * hash_constants::pi);
            ele = temp.z;
            break;
    }

    *u = az;
    *v = ele;
}
