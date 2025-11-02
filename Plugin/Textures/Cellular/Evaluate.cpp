// RC  6/6/2002  \Randy95\Plugin\Textures\Cellular\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "TexApp.h"

extern CTextureApp theApp;

template<typename T>
constexpr auto snoise(T x) { return 2.F*theApp.Noise(x)-1.F; }

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_amplitude;
        case 1:
            return m_fref;
        case 2:
            return m_fo;
        case 3:
            return m_bref;
        case 4:
            return m_bo;
        case 5:
            return m_noise;
        case 6:
            return m_freq;
        case 7:
            return m_bump;
        case 8:
            return m_mix;
        case 9:
            return m_offset;
        case 10:
            return m_scale;
        case 11:
            return m_useback;
        case 12:
            return m_bcolor;
        case 13:
            return m_fcolor;
        default:
            return nullptr;
    }
}

float CustomTexture::Voronoi(const Vector *p, float *b) {
    const int x = fast_floor(p->x);
    const int y = fast_floor(p->y);
    const int z = fast_floor(p->z);
    const float fx = p->x - x;
    const float fy = p->y - y;
    const float fz = p->z - z;
    float nd;
    float d = LocalVoronoi(x, y, z, p);

    float ld = d;
    if (d > fx && (nd = LocalVoronoi(x - 1, y, z, p)) < d) {
        ld = d;
        d = nd;
    }
    if (d > fy && (nd = LocalVoronoi(x, y - 1, z, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fz && (nd = LocalVoronoi(x, y, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && (nd = LocalVoronoi(x + 1, y, z, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fy && (nd = LocalVoronoi(x, y + 1, z, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fz && (nd = LocalVoronoi(x, y, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && d > 1.F - fy && (nd = LocalVoronoi(x + 1, y + 1, z, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fy && d > fx && (nd = LocalVoronoi(x - 1, y - 1, z, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && d > 1.F - fz && (nd = LocalVoronoi(x + 1, y, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fx && d > fz && (nd = LocalVoronoi(x - 1, y, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fz && d > 1.F - fy && (nd = LocalVoronoi(x, y + 1, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fz && d > fy && (nd = LocalVoronoi(x, y - 1, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fx && d > fy && d > fz && (nd = LocalVoronoi(x - 1, y - 1, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && d > 1.F - fy && d > 1.F - fz && (nd = LocalVoronoi(x + 1, y + 1, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fx && d > 1.F - fy && d > 1.F - fz && (nd = LocalVoronoi(x - 1, y + 1, z + 1, p)) < d) {
        ld = d;
        d = nd;
    } else {
        if (d > fx && d > 1.F - fy && d > fz && (nd = LocalVoronoi(x - 1, y + 1, z - 1, p)) < d) {
            ld = d;
            d = nd;
        }
    }
    if (d > 1.F - fx && d > fy && d > fz && (nd = LocalVoronoi(x + 1, y - 1, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }
    if (d > 1.F - fx && d > fy && d > 1.F - fz && (nd = LocalVoronoi(x + 1, y - 1, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fx && d > 1.F - fy && (nd = LocalVoronoi(x - 1, y + 1, z, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && d > fy && (nd = LocalVoronoi(x + 1, y - 1, z, p)) < d) {
        ld = d;
        d = nd;
    }
    if (d > 1.F - fy && d > fz && (nd = LocalVoronoi(x, y + 1, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && d > fz && (nd = LocalVoronoi(x + 1, y, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > 1.F - fx && d > 1.F - fy && d > fz && (nd = LocalVoronoi(x + 1, y + 1, z - 1, p)) < d) {
        ld = d;
        d = nd;
    }
    if (d > fx && d > 1.F - fz && (nd = LocalVoronoi(x - 1, y, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }

    if (d > fy && d > 1.F - fz && (nd = LocalVoronoi(x, y - 1, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }
    if (d > fx && d > fy && d > 1.F - fz && (nd = LocalVoronoi(x - 1, y - 1, z + 1, p)) < d) {
        ld = d;
        d = nd;
    }
    *b = ld;

    return d;
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat color1(m_fcolor->GetNormalizedRGBFloat());
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    RGBFloat color = m_bcolor->GetNormalizedRGBFloat();

    float bu = m_bump->GetValue();
    Vector calc;
    float bumps;
    const float noifreq = m_freq->GetValue() / 10.F;
    const float noiscale = m_noise->GetValue() / 100.F;
    Vector np;
    np.x = evalp.x;
    np.y = evalp.y;
    np.z = evalp.z;
    calc.x = (evalp.x + m_offset->GetX()->GetValue()) / m_scale->GetX()->GetValue();
    calc.y = (evalp.y + m_offset->GetY()->GetValue()) / m_scale->GetY()->GetValue();
    calc.z = (evalp.z + m_offset->GetZ()->GetValue()) / m_scale->GetZ()->GetValue();

    if (noiscale > 0.F) {
        const float noi = snoise(np * noifreq);
        calc.x = calc.x + noi * noiscale;
        calc.y = calc.y + noi * noiscale;
        calc.z = calc.z + noi * noiscale;
    }

    float x = Voronoi(&calc, &bumps);
    x = smoothstep(0.F, 1.F, x);
    // bump if bump value greater than zero....
    if (x > 1.F)
        x = 1.F;
    if (x < 0.F)
        x = 0.F;
    if (bu > 0.F) {
        Vector V(0, 1, 0);
        const Vector N = *texinfo->GetN();
        V = V - V.Dot(N) * N;
        Vector U = V.Cross(N);
        V = U.Cross(N);
        U.Normalize();
        V.Normalize();
        V *= 0.2F;
        U *= 0.2F;
        bu /= 5.F;
        calc += U;
        float dx = Voronoi(&calc, &bumps);
        calc -= U;
        calc += V;
        float dy = Voronoi(&calc, &bumps);
        dx = dx - x;
        dy = dy - x;

        U = U * (dx * x * bu);
        V = V * (dy * x * bu);
        *texinfo->GetN() += U;
        *texinfo->GetN() += V;
        texinfo->GetN()->Normalize();
    }

    const float mix = m_mix->GetValue() / 100.F;
    const float fr = m_fref->GetValue() / 100.F;
    const float br = m_bref->GetValue() / 100.F;
    const float opac1(m_bo->GetValue() / 100.F);
    const float opac2(m_fo->GetValue() / 100.F);

    // mix
    const float origref = texinfo->GetAttr()->GetReflectivity()->GetValue();
    const float origopac = texinfo->GetAttr()->GetTransparency()->GetValue();

    color = color1 * x + color * (1.F - x);
    const float opac = opac2 * x + opac1 * (1.F - x);
    const float ref = fr * x + br * (1.F - x);
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));
    texinfo->GetAttr()->GetTransparency()->SetValue(opac * mix + origopac * (1.F - mix));
    texinfo->GetAttr()->GetReflectivity()->SetValue(ref * mix + origref * (1.F - mix));

    return TRUE;
}
