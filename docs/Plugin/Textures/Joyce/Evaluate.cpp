// KB  11/7/01  \Ken90\Plugin\Textures\Joyce\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "Matrix34.h"
#include "TexApp.h"

extern CTextureApp theApp;

template<typename T>
constexpr auto snoise(T x) { return 2.F*theApp.Noise(x)-1.F; }

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_papercolor;
        case 1:
            return m_pencilcolor;
        case 2:
            return m_washcolor;
        case 3:
            return m_dark1color;
        case 4:
            return m_dark2color;
        case 5:
            return m_pencilnoise;
        case 6:
            return m_pencilfreq;
        case 7:
            return m_pencilsize;
        case 8:
            return m_washnoise;
        case 9:
            return m_washfreq;
        case 10:
            return m_washsize;
        case 11:
            return m_dark1noise;
        case 12:
            return m_dark1freq;
        case 13:
            return m_dark1size;
        case 14:
            return m_dark2noise;
        case 15:
            return m_dark2freq;
        case 16:
            return m_dark2size;
        case 17:
            return m_mix;
        case 18:
            return m_freq;
        case 19:
            return m_light;
        case 20:
            return m_bitmap;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

float CTextureApp::fBm(const Vector P, const float freq) {
    Vector PP(P);
    float n = 0.F;
    float scale = 2.F;
    for (int i = 0; i < 5; ++i) {
        n += snoise(PP*freq) / scale;
        PP *= 2.F;
        scale *= 2.F;
    }
    return n;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    Vector Light(-m_light->GetX()->GetValue(), -m_light->GetY()->GetValue(), m_light->GetZ()->GetValue());

    RGBFloat pencil(m_pencilcolor->GetNormalizedRGBFloat());
    RGBFloat wash(m_washcolor->GetNormalizedRGBFloat());
    RGBFloat dark1(m_dark1color->GetNormalizedRGBFloat());
    RGBFloat dark2(m_dark2color->GetNormalizedRGBFloat());
    RGBFloat paper(m_papercolor->GetNormalizedRGBFloat());

    Vector normal = *texinfo->GetN();
    Vector I = texinfo->GetD();
    normal.Normalize();
    Light.Normalize();
    RGBFloat color(paper);
    // wash
    float wsize = m_washsize->GetValue() / 100.F;
    float w = hash_math::abs(Light.Dot(normal));
    w = smoothstep(wsize, 1, w);
    wash.m_red += theApp.fBm(evalp, m_washfreq->GetValue()) * (m_washnoise->GetValue() / 100.F);
    wash.m_green += theApp.fBm(evalp, m_washfreq->GetValue()) * (m_washnoise->GetValue() / 100.F);
    wash.m_blue += theApp.fBm(evalp, m_washfreq->GetValue()) * (m_washnoise->GetValue() / 100.F);
    if (w < 0)
        w = 0.F;
    if (w > 1)
        w = 1.F;

    color = w * color + (1.F - w) * wash;
    // dark1
    float d1size = m_dark1size->GetValue() / 100.F;
    float d1 = hash_math::abs(Light.Dot(normal));
    d1 = smoothstep(d1size, 1, d1);
    d1 = hash_math::pow(d1, .5F);
    dark1.m_red += theApp.fBm(evalp, m_dark1freq->GetValue()) * (m_dark1noise->GetValue() / 100.F);
    dark1.m_green += theApp.fBm(evalp, m_dark1freq->GetValue()) * (m_dark1noise->GetValue() / 100.F);
    dark1.m_blue += theApp.fBm(evalp, m_dark1freq->GetValue()) * (m_dark1noise->GetValue() / 100.F);
    if (d1 < 0)
        d1 = 0.F;
    if (d1 > 1)
        d1 = 1.F;
    color = d1 * color + (1 - d1) * dark1;

    // dark2
    float d2size = m_dark2size->GetValue() / 100.F;
    float d2 = hash_math::abs(Light.Dot(normal));
    d2 = smoothstep(d2size, 1, d2);
    d2 = hash_math::pow(d2, .5F);
    dark2.m_red += theApp.fBm(evalp, m_dark2freq->GetValue()) * (m_dark2noise->GetValue() / 100.F);
    dark2.m_green += theApp.fBm(evalp, m_dark2freq->GetValue()) * (m_dark2noise->GetValue() / 100.F);
    dark2.m_blue += theApp.fBm(evalp, m_dark2freq->GetValue()) * (m_dark2noise->GetValue() / 100.F);
    if (d2 < 0)
        d2 = 0.F;
    if (d2 > 1)
        d2 = 1.F;
    color = d2 * color + (1.F - d2) * dark2;

    // 
    // pencil
//    float psize = m_pencilsize->GetValue() / 100.F;
    float p = hash_math::abs(I.Dot(normal));
    pencil.m_red += theApp.fBm(evalp, m_pencilfreq->GetValue()) * (m_pencilnoise->GetValue() / 100.F);
    pencil.m_green += theApp.fBm(evalp, m_pencilfreq->GetValue()) * (m_pencilnoise->GetValue() / 100.F);
    pencil.m_blue += theApp.fBm(evalp, m_pencilfreq->GetValue()) * (m_pencilnoise->GetValue() / 100.F);
    p += theApp.fBm(evalp + 10.F, m_pencilfreq->GetValue()) * (m_pencilnoise->GetValue() / 100.F);

    float pamt = m_pencilsize->GetValue() / 100.F;

    p = pulse(0.F, pamt, .05F, p);

    if (p < 0)
        p = 0.F;
    if (p > 1)
        p = 1.F;

    color = (1 - p) * color + p * pencil;

    float pn;
    // mix in paper.
    if (m_bitmap == nullptr) {
        pn = smoothstep(0.F, 1.F, theApp.fBm(evalp, m_freq->GetValue()) * m_mix->GetValue() / 100.F);
    } else {
//        Vector2 re(1, 1);
        float opacity;
        Vector ep = evalp;
        ASSERT(texinfo->GetMatrix());
        Matrix34 m = *texinfo->GetMatrix();
        ep *= m;
        RGBFloat diffuse(0.F, 1.F, 1.F);
        float x = repeat(ep[0], m_freq->GetValue()/100.F);
        float y = repeat(ep[1], m_freq->GetValue()/100.F);
        if (m_bitmap->GetClip()) {
            x = x * m_bitmap->GetWidth();
            y = y * m_bitmap->GetHeight();

            if (!m_bitmap->ReadBitmap(x, y, &diffuse, &opacity, texinfo->GetPixelWidth()))
                return FALSE;
        }
        pn = diffuse.m_green * (m_mix->GetValue() / 100.F);
    }

    if (pn < 0.F)
        pn = 0.F;
    if (pn > 1.F)
        pn = 1.F;
    color = pn * paper + (1.F - pn) * color;

    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color);

    return TRUE;
}
