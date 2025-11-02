// NAP  1/17/2002  \Noel90\Plugin\Textures\Eyeball\Evaluate.cpp

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
            return m_bcolor;
        case 1:
            return m_fcolor;
        case 2:
            return m_freq;
        case 3:
            return m_fref;
        case 4:
            return m_fo;
        case 5:
            return m_bref;
        case 6:
            return m_bo;
        case 7:
            return m_mix;
        case 8:
            return m_offset;
        case 9:
            return m_scale;
        case 10:
            return m_size;
        case 11:
            return m_sfreq;
        case 12:
            return m_soft;
        case 13:
            return m_useback;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CustomTexture::CalcSpots(Vector *) {
    return 0.F;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat origcolour(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    const RGBFloat iris(m_bcolor->GetNormalizedRGBFloat());
    const RGBFloat iris2(m_fcolor->GetNormalizedRGBFloat());

    constexpr float layer_opac = 1.F; //NAP layer_opac was uninited 1.F is a guess
    // params 
    const float pupilsize = m_size->GetValue();
    const float irissize = m_sfreq->GetValue();
    const float soft = m_soft->GetValue() / 100.F;
    float freq = m_freq->GetValue() / 2.F;

    // get distance from centre - z axis
    float x = evalp.x + m_offset->GetX()->GetValue();
    float y = evalp.y + m_offset->GetY()->GetValue();
    x *= x;
    y *= y;

    float pos;
    if (x + y != 0.F)
        pos = hash_math::sqrt(x + y);
    else
        pos = 0.F;
    texinfo->GetAttr()->GetSpecularSize()->SetValue(0.2F);
    const RGBFloat black(0.F);

    const RGBFloat white = origcolour;
    RGBFloat Ct;
    if (pos < pupilsize) // pupil
        Ct = black;
    else if (pos < pupilsize + soft) {
        //blend
        const float range = (pos - pupilsize) / soft;
        Ct = (1.F - range) * black + iris * range;
        texinfo->GetAttr()->GetSpecularIntensity()->SetValue(0.8F);
    } else if (pos < irissize) {
        // iris
        const float r = (pos - pupilsize) / (irissize - pupilsize);
        //PO*=r;
        float alpha = hash_math::atan(evalp.y / evalp.x) / hash_constants::pi_2;
        alpha *= 10.F;
        Vector pp(alpha, alpha, alpha);
        float turb = 0.F;
        const float f2 = freq;
        freq = 1.F;
        //for (i = 1;  i <= 4;  i += 1) {
        pp.z += 20.0F * f2;
        turb += hash_math::abs(snoise(pp * f2 + pp)) / freq;
        //freq *= 2;  f2 *= 2;
        //}
        turb *= r;
        const RGBFloat ir = iris2 * (1.F - std::clamp(turb * 0.5F, 0.F, 1.F));
        const RGBFloat Cr = (1.F - r) * iris + ir * iris2;
        Ct = (1.F - r) * ir + r * Cr;
        texinfo->GetAttr()->GetSpecularIntensity()->SetValue(0.1F);
    } else if (pos < irissize + soft) {
        // iris blend
        const float range = (pos - irissize) / soft;
        Ct = (1.F - range) * iris2 + white * range;
    } else {
        //white
        Ct = white;
        texinfo->GetAttr()->GetSpecularIntensity()->SetValue(0.4F);
    }
    float trans = m_fo->GetValue() / 100.F;
    const float st = trans;
    trans = m_bo->GetValue() / 100.F;
    const float bt = trans;
    const float br = m_bref->GetValue() / 100.F;
    const float sr = m_fref->GetValue() / 100.F;

    // set transparency and reflectivity.
    const float opac = layer_opac * st + (1.F - layer_opac) * bt;
    texinfo->GetAttr()->GetTransparency()->SetValue(opac);
    const float ref = layer_opac * sr + (1.F - layer_opac) * br;
    texinfo->GetAttr()->GetReflectivity()->SetValue(ref);
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(Ct);

    // mix the output
    const float mix = m_mix->GetValue() / 100.F;

    texinfo->GetAttr()->GetDiffuseColor()->SetValue(Ct * mix + origcolour * (1.F - mix));

    return true;
}
