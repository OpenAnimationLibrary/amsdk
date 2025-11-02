// RC  10/1/2001  \Randy90\Plugin\Textures\Spots\Evaluate.cpp

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
            return m_noise;
        case 8:
            return m_freq;
        case 9:
            return m_bump;
        case 10:
            return m_mix;
        case 11:
            return m_offset;
        case 12:
            return m_scale;
        case 13:
            return m_size;
        case 14:
            return m_sfreq;
        case 15:
            return m_soft;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CustomTexture::CalcSpots(const Vector *P) const {
    const float size = m_size->GetValue() / 100.F;
    const float scaler = m_sfreq->GetValue() / 100.F;
    const float xoff = m_offset->GetX()->GetValue();
    const float yoff = m_offset->GetY()->GetValue();
    const float zoff = m_offset->GetZ()->GetValue();
    const float xscale = m_scale->GetX()->GetValue();
    const float yscale = m_scale->GetY()->GetValue();
    const float zscale = m_scale->GetZ()->GetValue();

    const float fuzz = m_soft->GetValue() / 100.F;
    float center[3];

    float p[3];
    const float noifreq = m_freq->GetValue() / 10.F;
    const float noiscale = m_noise->GetValue() / 10.F;
    //float bombscale = chaninfo[DISPLACE].GetValue()/10.F;

    float ss, tt;
    Vector np;
    np.x = (P->x + xoff) * xscale;
    np.y = (P->y + yoff) * yscale;
    np.z = (P->z + zoff) * zscale;
    // if noise then perturb pattern
    if (noiscale > 0.F) {
        const float noi = theApp.Noise(np * noifreq);
        ss = np.x + noi * noiscale;
        tt = np.y + noi * noiscale;
    } else {
        ss = np.x;
        tt = np.y;
    }
    // if bomb then perturb tiles....
    //if (bombscale > 0.0){
    //		col = whichtile(ss, scaler);
    //		row = whichtile(tt, scaler);
    //		Vector bomb(col,row,1);
    //		bnoi = (ANoise(bomb  + 0.5))*2-1;
    //	}
    //	else {
    //		bnoi = 0;
    //	}
    p[0] = repeat(ss + xoff, scaler); // + (bnoi*bombscale);
    p[1] = repeat(tt + yoff, scaler); // + (bnoi*bombscale);
    p[2] = repeat(P->z + zoff, scaler);

    center[0] = 0.5F;
    center[1] = 0.5F;
    center[2] = 0.5F;

    /* location of center of disk */
    const float radius = size; /* radius of disk */
    const float d = distance(center, p);
    const float layer_opac = 1.F - smoothstep(radius - fuzz, radius, d);

    return layer_opac;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat origcolour = texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat();
    RGBFloat BackC = m_bcolor->GetNormalizedRGBFloat();
    const RGBFloat SpotC = m_fcolor->GetNormalizedRGBFloat();
    if (m_useback->GetValue()) {
        BackC = origcolour;
    }

    float bu = m_bump->GetValue() * 10.F;
    Vector ca;
    ca.x = evalp.x;
    ca.y = evalp.y;
    ca.z = evalp.z;
    const float x = CalcSpots(&ca);
    // bump if bump value greater than zero....
    if (bu > 0.F) {
        Vector V(0.F, 1.F, 0.F);
        const Vector N = *texinfo->GetN();
        V = V - V.Dot(N) * N;
        Vector U = V.Cross(N);
        V = U.Cross(N);
        U.Normalize();
        V.Normalize();
        U *= .4F;
        V *= .4F;
        bu /= 100.F;
        ca += U;
        float dx = CalcSpots(&ca);
        ca.x = evalp.x;
        ca.y = evalp.y;
        ca.z = evalp.z;
        ca += V;
        float dy = CalcSpots(&ca);
        dx = x - dx;
        dy = x - dy;
        U = U * (dx * x * bu);
        V = V * (dy * x * bu);
        *texinfo->GetN() += U;
        *texinfo->GetN() += V;
        texinfo->GetN()->Normalize();
    }
    const float layer_opac = x;
    float trans = m_fo->GetValue() / 100.F;
    const float st = trans;
    trans = m_bo->GetValue() / 100.F;
    const float bt = trans;
    const float br = m_bref->GetValue() / 100.F;
    const float sr = m_fref->GetValue() / 100.F;

    const RGBFloat final = SpotC * layer_opac + (1.F - layer_opac) * BackC;

    // set transparency and reflectivity.
    const float opac = layer_opac * st + (1.F - layer_opac) * bt;
    texinfo->GetAttr()->GetTransparency()->SetValue(opac);
    const float ref = layer_opac * sr + (1.F - layer_opac) * br;
    texinfo->GetAttr()->GetReflectivity()->SetValue(ref);
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(final);

    // mix the output
    const float mix = m_mix->GetValue() / 100.F;

    texinfo->GetAttr()->GetDiffuseColor()->SetValue(final * mix + origcolour * (1.F - mix));

    return TRUE;
}
