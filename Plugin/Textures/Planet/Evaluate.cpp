// RC  10/1/2001  \Randy90\Plugin\Textures\Planet\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Noise.h"

#define SMALL 0.0000001

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_featuresize;
        case 1:
            return m_polardist;
        case 2:
            return m_water;
        case 3:
            return m_bump;
        case 4:
            return m_ice;
        case 5:
            return m_freq;
        case 6:
            return m_ampl;
        case 7:
            return m_octaves;
        case 8:
            return m_noisemult;
        case 9:
            return m_seed;
        case 10:
            return m_offset;
        case 11:
            return m_mottlesize;
        case 12:
            return m_mottlemag;
        case 13:
            return m_depthnoise;
        case 14:
            return m_maxdepth;
        case 15:
            return m_snow;
        default:
            return nullptr;
    }
}

struct rgbcol {
    float red;
    float green;
    float blue;
};

constexpr int NUMCOLS = 12;
constexpr rgbcol color_spline[NUMCOLS] = {
    {0.529F, 0.412F, 0.2745F}, {0.529F, 0.412F, 0.2745F}, {0.529F, 0.412F, 0.2745F}, {0.255F, 0.341F, 0.050F}, {0.256F, 0.341F, 0.141F}, {0.235F, 0.392F, 0.235F}, {0.490F, 0.494F, 0.1176F},
    {0.655F, 0.529F, 0.392F}, {0.769F, 0.616F, 0.314F}, {0.976F, 0.820F, 0.471F}, {1.F, 1.F, 1.F}, {1.F, 1.F, 1.F}
};

namespace {
    Vector get_color(double val) {
        if (val > 1.0)
            val = 1.0;
        if (val < 0.0)
            val = 0.0;

        const auto range = (float)(val * (NUMCOLS - 1));
        const int a = fast_floor(range);
        const int b = a + 1;
        const float diff = range - a;

        Vector out;
        out.x = color_spline[a].red * (1.F - diff) + color_spline[b].red * diff;
        out.y = color_spline[a].green * (1.F - diff) + color_spline[b].green * diff;
        out.z = color_spline[a].blue * (1.F - diff) + color_spline[b].blue * diff;

        return out;
    }

    double octval(const double iX, const double iY, const double iZ, const int octaves, const double fmult, const double amult) {
        double value = 0.0;
        //    double frequency = 1.0;
        double amplitude = 0.5;

        double px = iX;
        double py = iY;
        double pz = iZ;

        /* inner loop of spectral construction */
        for (int i = 0; i < octaves; ++i) {
            value += Noise3(px, py, pz) * amplitude;
            px *= fmult;
            py *= fmult;
            pz *= fmult;
            amplitude *= amult;
        } /* for */

        return value;
    }
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    static int precalc = FALSE;

    const double size = m_featuresize->GetValue();
    const double polar_dist = m_polardist->GetValue();
    double sea_level = m_water->GetValue() / 50 - 1.0; // Convert 0..100 to -1..1
    const double bumpsize = m_bump->GetValue() / 200.0F;
    const double ice_caps = 1.0 - m_ice->GetValue() / 100.F;

    const double seed = m_seed->GetValue();
    const double fmult = m_freq->GetValue() / 100.F;
    const double amult = m_ampl->GetValue() / 100.F;
    const int octaves = (int)m_octaves->GetValue();
    const double offset = m_offset->GetValue() / 100.F - 0.5;
    const double noise_amplitude = m_noisemult->GetValue() / 100.F;

    const double mottle_scale = 1. / (m_mottlesize->GetValue() / 100.0);
    const double mottle_mag = m_mottlemag->GetValue() / 100.F;

    const double depth_scale = m_depthnoise->GetValue() / 30.0F;
    const double depth_max = m_maxdepth->GetValue() / 100.F;
    const double nonlinear = m_snow->GetValue() / 20.0F;

    constexpr double water_scale = 0.5;
    constexpr double lat_scale = 0.95;
    constexpr double purt_scale = 1;
    constexpr double mottle_limit = 0.8;
    //    const double map_exp = 0;

    int useIce = TRUE;
    if (ice_caps >= 1.0)
        useIce = FALSE;

    if (!precalc) {
        // this could be done in an "Init()" routine
        init_noiz_tbl();
        precalc = TRUE;
    }

    const double inx = evalp.x / size;
    const double iny = evalp.y / size;
    const double inz = evalp.z / size + seed;

    //	to_tspace(&norm,axes);

    const double val = octval(inx, iny, inz, octaves, fmult, amult);

    double chaos = noise_amplitude * (val + offset);

    if (chaos > sea_level) {
        constexpr double mtn_scale = 1.0;
        chaos *= mtn_scale;
        sea_level *= mtn_scale;
    } else
        chaos *= water_scale;

    double latitude = hash_math::abs(evalp.y / polar_dist);

    latitude += sea_level;
    latitude += (chaos - sea_level) * (nonlinear * (1 - latitude) + purt_scale) / (1 - sea_level);

    //    if (map_exp > 0)
    //        latitude = lat_scale * pow(latitude, map_exp);
    //    else
    latitude *= lat_scale;

    Vector Ct;
    if (chaos > sea_level) {
        texinfo->GetAttr()->GetSpecularIntensity()->SetValue(0.F);

        Ct = get_color(latitude);

        if (latitude < mottle_limit * ice_caps) {
            constexpr double mottle_dim = 0.25;
            const double purt = octval(inx * mottle_scale, iny * mottle_scale, inz * mottle_scale, 6, fmult, mottle_dim);
            Ct.x += (float)(mottle_mag * purt * 0.5F);
            Ct.y += (float)(mottle_mag * purt * 0.175F);
            Ct.z += (float)(mottle_mag * purt * 0.5F);
        }

        if (bumpsize > 0) {
            Vector norm = *texinfo->GetN();

            const double valX = octval(inx + SMALL, iny, inz, octaves, fmult, amult);
            const double valY = octval(inx, iny + SMALL, inz, octaves, fmult, amult);
            const double valZ = octval(inx, iny, inz + SMALL, octaves, fmult, amult);

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

            texinfo->GetN()->x = norm.x;
            texinfo->GetN()->y = norm.y;
            texinfo->GetN()->z = norm.z;
            texinfo->GetN()->Normalize();
        }
    } else {
        Ct.x = 0.12F;
        Ct.y = 0.3F;
        Ct.z = 0.6F;
        chaos -= sea_level;
        chaos *= depth_scale;
        chaos = MAX(chaos, -depth_max);

        Ct.x *= (float)(1.F + chaos);
        Ct.y *= (float)(1.F + chaos);
        Ct.z *= (float)(1.F + chaos);
    }

    if (useIce && latitude > ice_caps) {
        Ct.x = 1.F;
        Ct.y = 1.F;
        Ct.z = 1.F;
        texinfo->GetAttr()->GetSpecularIntensity()->SetValue(0.F);
    }

    if (Ct.x < 0.05F)
        Ct.x = 0.05F;
    if (Ct.y < 0.05F)
        Ct.y = 0.05F;
    if (Ct.z < 0.05F)
        Ct.z = 0.05F;

    // Store height data
    if (latitude > 1.0)
        latitude = 1.0;
    if (latitude < 0.0)
        latitude = 0.0;
    texinfo->SetHeight((float)(latitude * 100.F));

    RGBFloat ct;
    ct.m_red = Ct.x;
    ct.m_green = Ct.y;
    ct.m_blue = Ct.z;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(ct);

    return TRUE;
}
