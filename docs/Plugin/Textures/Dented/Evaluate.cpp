// Dan  11/28/2001  \Dan90\Plugin\Textures\Dented\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Noise.h"

#define SMALL 0.0000001

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_size;
        case 1:
            return m_bump;
        case 2:
            return m_freq;
        case 3:
            return m_ampl;
        case 4:
            return m_octaves;
        case 5:
            return m_weight;
        case 6:
            return m_seed;
        default:
            return nullptr;
    }
}

static double octval(const double iX, const double iY, const double iZ, const int octaves, const float fmult, const float amult, const float power) {
    double value = 0.0;
    double amplitude = 0.5;

    double px = iX;
    double py = iY;
    double pz = iZ;

    for (int i = 0; i < octaves; ++i) {
        value += hash_math::abs(Noise3(px, py, pz)) * amplitude;
        px *= fmult;
        py *= fmult;
        pz *= fmult;
        amplitude *= amult;
    } /* for */

    return hash_math::pow(value, (double)power);
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    static int precalc = FALSE;

    const float xsize = m_size->GetX()->GetValue();
    const float ysize = m_size->GetY()->GetValue();
    const float zsize = m_size->GetZ()->GetValue();
    const float bumpsize = 5.0F - m_bump->GetValue()/*/10.F*/;

    const float seed = m_seed->GetValue();
    const float fmult = m_freq->GetValue()/*/100.F*/;
    const float amult = m_ampl->GetValue()/*/100.F*/;
    const float power = m_weight->GetValue()/*/100.F*/;
    const int octaves = m_octaves->GetValue();

    if (!precalc) {
        // this could be done in an "Init()" routine
        init_noiz_tbl();
        precalc = TRUE;
    }

    const double inx = evalp.x / xsize;
    const double iny = evalp.y / ysize;
    const double inz = evalp.z / zsize + seed;

    Vector norm = *texinfo->GetN();

    //	to_tspace(&norm,axes);

    const double val = octval(inx, iny, inz, octaves, fmult, amult, power);
    const double valX = octval(inx + SMALL, iny, inz, octaves, fmult, amult, power);
    const double valY = octval(inx, iny + SMALL, inz, octaves, fmult, amult, power);
    const double valZ = octval(inx, iny, inz + SMALL, octaves, fmult, amult, power);

    double dx = (valX - val) / SMALL;
    double dy = (valY - val) / SMALL;
    double dz = (valZ - val) / SMALL;

    const double dotprod = dx * norm.x + dy * norm.y + dz * norm.z;

    dx -= dotprod * norm.x;
    dy -= dotprod * norm.y;
    dz -= dotprod * norm.z;

    norm.x -= (float)(bumpsize * dx);
    norm.y -= (float)(bumpsize * dy);
    norm.z -= (float)(bumpsize * dz);

    //	to_gspace(&norm,axes);

    texinfo->GetN()->x = norm.x;
    texinfo->GetN()->y = norm.y;
    texinfo->GetN()->z = norm.z;

    texinfo->GetN()->Normalize();

    // Store SLOT 15 data
    texinfo->SetHeight((float)(val * 100.F));

    return TRUE;
}
