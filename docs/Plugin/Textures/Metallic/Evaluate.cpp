// RC  10/1/2001  \Randy90\Plugin\Textures\Metallic\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "texfuncs.h"
#include "Matrix34.h"
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
            return m_tx;
        case 14:
            return m_ty;
        case 15:
            return m_da;
        case 16:
            return m_df;
        case 17:
            return m_dt;
        case 18:
            return m_bitmap;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    // chnaged divisions to multiplication
    RGBFloat origcolor = texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat();
    RGBFloat color = m_bcolor->GetNormalizedRGBFloat();
    RGBFloat color2 = m_fcolor->GetNormalizedRGBFloat();
    if (m_useback->GetValue()) {
        color = origcolor;
    }

    Vector P = evalp;
    P.x *= m_xs->GetValue();
    P.y *= m_ys->GetValue();
    P.z *= m_xs->GetValue();
    float dink = m_da->GetValue();
    float dinkf = m_df->GetValue() * 0.01F;
    float dinkt = m_dt->GetValue() * 0.01F;
    //   float dinkf=m_df->GetValue()/100.F;
    //   float dinkt=m_dt->GetValue()/100.F;

    float ssize = m_fo->GetValue() * 0.01F;
    float sintensity = m_fref->GetValue() * 0.01F;
    //   float ssize=m_fo->GetValue()/100.F;
    //   float sintensity=m_fref->GetValue()/100.F;

    //    float rough = m_rough->GetValue() * 0.01f;
    //   float rough = m_rough->GetValue()/100.F;
    //   float mix = m_mix->GetValue()/100.F;

    // get value from texture.
    Vector2 re(m_tx->GetValue(), m_ty->GetValue());
    RGBFloat diffuse;

    float specnoise = 0.F;
    float scale = 1.F;
    for (int i = 0; i < 4; ++i) {
        specnoise += snoise(P) / scale;
        scale *= 0.5F;
        P *= 0.5F;
    }
    float outspec = specnoise + ssize;
    outspec = hash_math::abs(outspec);
    if (outspec > 1.F)
        outspec = 1.F;
    if (m_pencil->GetValue() > 0.F) {
        Vector NN = *texinfo->GetN();
        Vector up(0.F, 1.F, 0.F);
        Vector left = NN.Cross(up);
        up = left.Cross(NN);
        NN += up * (specnoise * m_pencil->GetValue() * 0.001F);
        //		NN+=up*(specnoise*m_pencil->GetValue()/1000.0f);
        NN.Normalize();
        *texinfo->GetN() = NN;
    }
    float opacity;
    if (m_bitmap->GetClip() && m_fuzz->GetValue() > 0.F) {
        ASSERT(texinfo->GetMatrix());
        //        Matrix34 inversematrix = texinfo->GetMatrix()->Transpose(); // may need true inverse for scale
        Vector n = *texinfo->GetN();
        //n *= inversematrix;

        float mapy = hash_math::cos(n.y) / hash_constants::pi;
        mapy = mapy - fast_ftol_signed(mapy);

        float mapx = (hash_math::atan2(-n.x, n.z) + hash_constants::pi) / (2.F * hash_constants::pi);
        mapx = mapx - fast_ftol_signed(mapx);

        m_bitmap->GetRepeat()->SetValue(re);
        float x = mapx * (m_bitmap->GetWidth() - 1);
        float y = mapy * (m_bitmap->GetHeight() - 1);

        if (!m_bitmap->ReadBitmap(x, y, &diffuse, &opacity, texinfo->GetPixelWidth()))
            return FALSE;

        //		float mix= (m_fuzz->GetValue()/100.F);
        float mix = m_fuzz->GetValue() * 0.01F;
        color = mix * diffuse + (1.F - mix) * color;
    }

    // do dink
    if (dink != 0.F) {
        Vector V(0.F, 1.F, 0.F);
        Vector N = *texinfo->GetN();
        V = V - V.Dot(N) * N;
        Vector U = V.Cross(N);
        V = U.Cross(N);
        U.Normalize();
        V.Normalize();
        V *= 0.1F;
        U *= 0.1F;
        float d = getDink(evalp, dinkf, dinkt);
        float dx = getDink(evalp + U, dinkf, dinkt);
        float dy = getDink(evalp + V, dinkf, dinkt);
        dx = dx - d;
        dy = dy - d;
        U = U * (dx * d * dink);
        V = V * (dy * d * dink);
        *texinfo->GetN() += U;
        *texinfo->GetN() += V;
        texinfo->GetN()->Normalize();
    }
    texinfo->GetAttr()->GetDiffuseColor()->SetValue(color);
    texinfo->GetAttr()->GetSpecularColor()->SetValue(color2);
    texinfo->GetAttr()->GetSpecularSize()->SetValue(outspec);
    texinfo->GetAttr()->GetSpecularIntensity()->SetValue(sintensity);
    texinfo->GetAttr()->GetReflectivity()->SetValue(m_rough->GetValue() * 0.01F);
    texinfo->GetAttr()->GetDiffuseFallOff()->SetValue(m_bo->GetValue() * 0.01F);
    //   texinfo->GetAttr()->GetReflectivity()->SetValue(m_rough->GetValue()/100.F);
    //   texinfo->GetAttr()->GetDiffuseFallOff()->SetValue(m_bo->GetValue()/100.F);
    // loverly....

    return TRUE;
}

float CustomTexture::getDink(const Vector P, const float from, const float to) {
    float s = 0.F;
    float gain = 1.F;
    Vector PP = P / 2.F;
    for (int i = 0; i < 4; ++i) {
        s += theApp.Noise(PP) * gain;
        PP *= 2.F;
        gain *= 0.5F;
    }
    return smoothstep(from, to, s);
}
