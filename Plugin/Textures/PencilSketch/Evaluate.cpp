// RC  10/1/2001  \Randy90\Plugin\Textures\PencilSketch\Evaluate.cpp

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
            return m_bo;
        case 6:
            return m_mix;
        case 7:
            return m_fuzz;
        case 8:
            return m_xs;
        case 9:
            return m_ys;
        case 10:
            return m_pencil;
        case 11:
            return m_light;
        case 12:
            return m_rough;
        case 13:
            return m_chatter;
        default:
            return nullptr;
    }
}

void CTextureApp::InitNoiseTable() {
    srand(17); // NOLINT(cert-msc51-cpp)
    for (int i = MAXX; i-- > 0;) {
        for (int j = MAXY; j-- > 0;) {
            for (int k = MAXZ; k-- > 0;) {
                m_noiz_tbl[i][j][k] = rand() % 1000; // NOLINT(concurrency-mt-unsafe)
            }
        }
    }
}

float CTextureApp::Noise(const Vector p) const {
    Vector p_n(p);
    p_n += 15000.0F;
    int ix = fast_ftol_unsigned(p_n.x) % MAXX;
    if (ix < 0)
        ix += MAXX;
    int iy = fast_ftol_unsigned(p_n.y) % MAXY;
    if (iy < 0)
        iy += MAXY;
    int iz = fast_ftol_unsigned(p_n.z) % MAXZ;
    if (iz < 0)
        iz += MAXZ;

    const float ox = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.x - fast_ftol_unsigned(p_n.x)))) * .5F;
    const float oy = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.y - fast_ftol_unsigned(p_n.y)))) * .5F;
    const float oz = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.z - fast_ftol_unsigned(p_n.z)))) * .5F;

    const int ixp = ix + 1 >= MAXX ? 0 : ix + 1;
    const int iyp = iy + 1 >= MAXY ? 0 : iy + 1;
    const int izp = iz + 1 >= MAXZ ? 0 : iz + 1;

    const float A = m_noiz_tbl[ix][iy][iz];
    const float B = m_noiz_tbl[ixp][iy][iz];
    const float C = m_noiz_tbl[ixp][iyp][iz];
    const float D = m_noiz_tbl[ixp][iyp][izp];
    const float E = m_noiz_tbl[ixp][iy][izp];
    const float F = m_noiz_tbl[ix][iy][izp];
    const float G = m_noiz_tbl[ix][iyp][izp];
    const float H = m_noiz_tbl[ix][iyp][iz];
    float t1 = (1.F - ox) * A + ox * B;
    float t2 = (1.F - ox) * H + ox * C;
    const float t3 = (1.F - ox) * F + ox * E;
    const float t4 = (1.F - ox) * G + ox * D;
    t1 = (1.F - oy) * t1 + oy * t2;
    t2 = (1.F - oy) * t3 + oy * t4;
    t1 = (1.F - oz) * t1 + oz * t2;

    t2 = t1 * .001F;
    if (t2 > 0.F)
        return t2;
    return 0.F;
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    const RGBFloat origcolor(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat());
    const RGBFloat color2(m_fcolor->GetNormalizedRGBFloat());
    RGBFloat color(m_bcolor->GetNormalizedRGBFloat());
    if (m_useback->GetValue()) {
        color = origcolor;
    }

    Vector nn = *texinfo->GetN();
    Vector dd(-m_light->GetX()->GetValue(), -m_light->GetY()->GetValue(), m_light->GetZ()->GetValue());
    nn.Normalize();
    dd.Normalize();
    Vector P = evalp;
    P.x *= m_xs->GetValue();
    P.y *= m_ys->GetValue();
    P.z *= m_xs->GetValue();
    const float chatter = snoise(P + texinfo->GetTime().GetFrame(30.)) * m_chatter->GetValue() / 100.F;
    float noise = snoise(P);
    float alpha = nn.Dot(dd);
    const float rough = m_rough->GetValue() / 100.F;
    const float mix = m_mix->GetValue() / 100.F;

    alpha = (1.F + alpha) / 2.F;
    noise += chatter;

    alpha += noise * rough;
    // alpha = hash_math::abs(alpha);

    alpha = hash_math::pow(alpha, m_fref->GetValue());

    alpha = pulse(0.F, m_pencil->GetValue() / 100.F, m_fuzz->GetValue() / 100.F, alpha);

    color = alpha * color + (1.F - alpha) * color2;
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color * mix + origcolor * (1.F - mix));

    return TRUE;
}
