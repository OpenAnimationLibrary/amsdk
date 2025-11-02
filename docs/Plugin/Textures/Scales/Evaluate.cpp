// KB  1/18/01  \Ken90\Plugin\Textures\Scales\Evaluate.cpp

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
            return m_edge;
        case 3:
            return m_valley;
        case 4:
            return m_rounding;
        case 5:
            return m_seed;
        case 6:
            return m_slope1;
        case 7:
            return m_slope2;
        default:
            return nullptr;
    }
}

float smoothbump(const float t, const float sb, const float st) {
    const float P4 = -6.F * t * t + 6.F * t;
    const float R1 = 3.F * t * t - 4.F * t + 1.F;
    const float R4 = 3.F * t * t - 2.F * t;

    return P4 + sb * R1 + st * R4;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const double xsize = m_size->GetX()->GetValue();
    const double ysize = m_size->GetY()->GetValue();
    const double zsize = m_size->GetZ()->GetValue();
    const double bumpsize = (m_bump->GetValue() - 50.0F) / 25.0F;

    double edge = m_edge->GetValue() / 100.F;
    double width = m_valley->GetValue() / 100.F;
    const double rounding = m_rounding->GetValue() / 100.F;
    const double seed = m_seed->GetValue();

    const float sb = (m_slope1->GetValue() - 50.0F) / 15.0F;
    const float st = (m_slope2->GetValue() - 50.0F) / 15.0F;

    // Other parameters
    //    double edist;

    Vector in, pos1, pos2;
    double dist1, dist2, rad;

    in.x = (float)(evalp.x / xsize);
    in.y = (float)(evalp.y / ysize);
    in.z = (float)(evalp.z / zsize + seed);

    Voronoi3(&in, // input position
             &pos1, &pos2, // output positions
             &dist1, &dist2); // output distances

    if (rounding == 1.0) {
        rad = dist2 - dist1;
    } else {
        rad = hash_math::pow(dist2, rounding) - pow(dist1, rounding);
    }

    const Vector pos1_to_pos2 = pos2 - pos1;
    const double p1p2_distance = pos1_to_pos2.Norm();

    edge = edge * p1p2_distance;
    width = width * p1p2_distance;
    /*
        if (rad <= width) {
            // MORTAR
            edist = 0;
        } else {
            // INSIDE
            edist = 1;
        }
    */
    if (rad > width && rad < width + edge) {
        // We're in the edge zone

        const auto t = (float)((rad - width) / edge);

        //        edist = t;

        Vector norm = *texinfo->GetN();
        //	to_tspace(&norm,axes);
        Vector diff = pos2 - pos1;
        /*
                diff.x = pos2.x - pos1.x;
                diff.y = pos2.y - pos1.y;
                diff.z = pos2.z - pos1.z;
                */
        // Subtract the normal components
        const float dotprod = diff.x * norm.x + diff.y * norm.y + diff.z * norm.z;

        diff.z -= dotprod * norm.x;
        diff.y -= dotprod * norm.y;
        diff.x -= dotprod * norm.z;

        // re-normalize in order to achieve a
        // standard looking slope
        diff.Normalize();

        const float mult = (float)bumpsize * smoothbump(t, sb, st);

        norm.x += mult * diff.x;
        norm.y += mult * diff.y;
        norm.z += mult * diff.z;

        texinfo->GetN()->x = norm.x;
        texinfo->GetN()->y = norm.y;
        texinfo->GetN()->z = norm.z;
        texinfo->GetN()->Normalize();

        //		to_gspace(&norm,axes);
    }

    // Store height data
    //    if (edist < 0.0)
    //        edist = 0.0;
    texinfo->SetHeight((float)(rad * 100.F));

    return TRUE;
}
