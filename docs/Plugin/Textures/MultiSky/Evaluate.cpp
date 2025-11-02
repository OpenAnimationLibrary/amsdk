// RC  10/1/2001  \Randy90\Plugin\Textures\MultiSky\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "TexApp.h"

extern CTextureApp theApp;

template<typename T>
constexpr auto snoise(T x) {
    return 2.F * theApp.Noise(x) - 1.F;
}

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_height;
        case 1:
            return m_cover;
        case 2:
            return m_octaves;
        case 3:
            return m_haze;
        case 4:
            return m_sintensity;
        case 5:
            return m_si;
        case 6:
            return m_trans;
        case 7:
            return m_type;
        case 8:
            return m_sun;
        case 9:
            return m_offset;
        case 10:
            return m_scale;
        case 11:
            return m_hcolor;
        case 12:
            return m_scolor;
        case 13:
            return m_c1color;
        case 14:
            return m_c2color;
        case 15:
            return m_bcolor;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CustomTexture::calcSky(Vector P, const int octaves, const float cover) const {
    float mag = 0.F;
    const int type = m_type->GetValue();
    const int octaves_int = octaves + 1;
    Vector pp(P);
    float scale = 1.F;
    switch (type) {
        case 0:
            for (int i = 1; i < octaves_int; ++i) {
                P *= 2.F;
                mag += theApp.Noise(P) * scale;
                scale /= 2.F;
            }
            break;
        case 1:
            for (int i = 1; i < octaves_int; ++i) {
                mag += theApp.Noise(P) * scale;
                P *= 4.0F;
                scale /= 4.0F;
            }

            break;
        case 2:
            for (int i = 1; i < octaves_int; ++i) {
                mag += snoise(P) * scale;
                P *= 2.F;
                scale /= 2.F;
            }
            mag = hash_math::abs(mag);
            break;
        case 3:
            for (int i = 1; i < octaves_int; ++i) {
                P *= 2.F;
                mag += theApp.Noise(P) * scale;
                scale /= 2.F;
            }

            break;
        case 4:
            pp.x += snoise(P / 2.F);
            pp.y += snoise(-P / 2.F);
            pp.z += snoise(P / 2.F);
            for (int i = 1; i < octaves_int; ++i) {
                mag += theApp.Noise(pp) * scale;
                pp *= 2.F;
                scale /= 2.F;
            }
            mag = hash_math::abs(mag);
            break;
        case 5:
            for (int i = 1; i < octaves_int; ++i) {
                mag += hash_math::abs(snoise(P)) * scale;
                P *= 2.F;
                scale /= 2.F;
            }

            break;
        default:
            break;
    }
    if (cover != 0.F) {
        mag = mag * mag * mag * cover;
    }

    return mag;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    RGBFloat sky = m_bcolor->GetNormalizedRGBFloat();
    RGBFloat haze = m_hcolor->GetNormalizedRGBFloat();
    RGBFloat cloud = m_c1color->GetNormalizedRGBFloat();
    RGBFloat cloud2 = m_c2color->GetNormalizedRGBFloat();
    RGBFloat sun = m_scolor->GetNormalizedRGBFloat();

    Vector neweval(evalp);
    // position and scale
    neweval.x += m_offset->GetX()->GetValue();
    neweval.y += m_offset->GetY()->GetValue();
    neweval.z += m_offset->GetZ()->GetValue();

    neweval.x /= m_scale->GetX()->GetValue();
    neweval.y /= m_scale->GetY()->GetValue();
    neweval.z /= m_scale->GetZ()->GetValue();

    // calc cloud value
    Vector P(neweval);
    float coverage = m_cover->GetValue() / 100.F;
    int octaves = m_octaves->GetValue();
    float cval = calcSky(P, octaves, coverage);
    Vector V(0.F, 0.F, -1.F);
    //Vector N(0,-1,0);
    Vector N = *texinfo->GetN();
    V = V - V.Dot(N) * N;
    Vector U = V.Cross(N);
    V = U.Cross(N);
    U.Normalize();
    V.Normalize();
    float soft = m_height->GetValue() / 100.F;
    U *= soft;
    V *= soft;
    // calc near values for bumping....
    P = neweval;
    P += U;
    float du = calcSky(P, octaves, coverage);

    P = neweval;
    P += V;
    float dv = calcSky(P, octaves, coverage);

    du = du - cval;
    dv = dv - cval;
    N += du * U;
    N += dv * V;
    N.Normalize();
    Vector ldir(-m_sun->GetX()->GetValue(), -m_sun->GetY()->GetValue(), m_sun->GetZ()->GetValue());
    ldir.Normalize();

    float shadeval;
    if (m_type->GetValue() != 3) {
        shadeval = N.Dot(ldir);
    } else {
        Vector Vlocal = texinfo->GetD();
        float sigma = m_sintensity->GetValue() / 100.F;
        sigma *= sigma;
        float A = 1 - 0.5F * sigma / (sigma + 0.33F);
        float B = 0.45F * sigma / (sigma + 0.09F);
        float tr = hash_math::cos(Vlocal.Dot(N));
        Vector VpN = Vlocal - N * Vlocal.Dot(N);
        float cti = N.Dot(ldir);
        Vector tmp = ldir - N * cti;
        tmp.Normalize();
        const float cpd = VpN.Dot(tmp);
        const float ti = acos(cti);
        const float alpha = MAX(ti, tr);
        const float beta = MIN(ti, tr);
        shadeval = cti * (A + B * MAX(0.F, cpd) * hash_math::sin(alpha) * hash_math::tan(beta));
    }

    cloud = shadeval * cloud2 + (1.F - shadeval) * cloud;
    cloud *= sun;
    cval = cval > 1.F ? 1.F : cval;
    // change between blue and cloud
    sky = cval * cloud + (1.F - cval) * sky;

    // do haze
    const float ha = m_haze->GetValue();
    RGBFloat outcol;
    if (evalp.y > ha) {
        outcol = sky;
    } else {
        float h = evalp.y / ha;
        outcol = sky * h + (1.F - h) * haze;
    }

    // transparency 
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(outcol);
    // self illuminating.
    if (m_si->GetValue())
        texinfo->GetAttr()->GetAmbiance()->SetValue(1.F);
    float trans = m_trans->GetValue();
    trans = (1.F - cval) * trans;
    texinfo->GetAttr()->GetTransparency()->SetValue(trans);

    return TRUE;
}
