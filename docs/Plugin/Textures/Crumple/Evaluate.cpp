// KB  1/2/01  \Ken90\Plugin\Textures\Crumple\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Basis.h"

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

static Vector normdiff(const Vector &in, const Vector &norm, const float weight) {
    Vector in2;

    in2.x = in.x + 22.22F;
    in2.y = in.y + 33.33F;
    in2.z = in.z + 44.66F;

    Vector close1a, close2a;
    Vector close1b, close2b;
    double dist1a, dist2a;
    double dist1b, dist2b;

    ///////////////////////////////////////////////////
    // Calculate vectors to the closest points.
    // Specifically, we want close1a and close1b

    Voronoi3(&in, // input position
             &close1a, // output position 1
             &close2a, // output position 2
             &dist1a, // output distance 1
             &dist2a); // output distance 2

    Voronoi3(&in2, // input position
             &close1b, // output position 1
             &close2b, // output position 2
             &dist1b, // output distance 1
             &dist2b); // output distance 2

    ////////////////////////////////////////////////////
    // Now remove elements of the close1a and close1b
    // vectors that are NOT orthogonal to the surface
    // vector.

    // Calculate the pseudo dot-product. It's
    // actually the dot product * magnitude that we
    // calculate here.	
    close1a -= Dot(close1a, norm) * norm;
    close1b -= Dot(close1b, norm) * norm;

    // Return a weighted portion of either A or B
    const Vector retval = weight * close1a - (1 - weight) * close1b;

    return retval;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const Vector size(m_size->GetX()->GetValue(), m_size->GetY()->GetValue(), m_size->GetZ()->GetValue());
    float bumpsize = 5.0F - m_bump->GetValue() / 10.F;
    const float seed = m_seed->GetValue();
    const float fmult = m_freq->GetValue() / 100.F;
    const float amult = m_ampl->GetValue() / 100.F;
    const float weight = m_weight->GetValue() / 100.F;
    const int octaves = m_octaves->GetValue();

    Vector in = evalp / size;
    in.z += seed;

    Vector norm = *texinfo->GetN();

    for (int loop = 0; loop < octaves; loop++) {
        const Vector diff = normdiff(in, norm, weight);
        norm += diff * bumpsize;
        in *= fmult;
        bumpsize *= amult;
    }
    *texinfo->GetN() = norm;
    texinfo->GetN()->Normalize();

    //	texinfo.height = (float)(val * 100);

    return TRUE;
}
