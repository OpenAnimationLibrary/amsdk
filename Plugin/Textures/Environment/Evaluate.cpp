// MH  12/12/2002  \Mart100\Plugin\Textures\Environment\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Matrix34.h"
#include "TexApp.h"

extern CTextureApp theApp;

//static Vector xaxis(-1.F, 0.F, 0.F), yaxis(0.F, 1.F, 0.F), translate(0.F, 0.F, 0.F);

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_clip;
        case 1:
            return m_opacity;
        case 2:
            return m_isadditive;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return true;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    ASSERT(texinfo->GetMatrix());

    if (m_clip->GetClip() == nullptr)
        return false;

    float opacity;
    RGBFloat diffuse;

    const Vector n = *texinfo->GetN();
    const Vector d = texinfo->GetD();
    Vector l(n);
    l *= 2.F * -n.Dot(d);
    l += d;
    l *= texinfo->GetMatrix()->Transpose();
    l.Normalize();

    float mapy = hash_math::acos(l.y) / hash_constants::pi;
    mapy = mapy - fast_ftol_signed(mapy);

    float mapx = (hash_math::atan2(-l.x, l.z) + hash_constants::pi) / hash_constants::pi_2;
    mapx = mapx - fast_ftol_signed(mapx);

    const float x = mapx * m_clip->GetWidth();
    const float y = mapy * m_clip->GetHeight();

    if (!m_clip->ReadBitmap(x, y, &diffuse, &opacity, texinfo->GetPixelWidth()))
        return false;
    if (opacity != 0.F) {
        opacity *= m_opacity->GetValue() / 100.F;
        if (m_isadditive->GetValue())
            texinfo->GetAttr()->GetDiffuseColor()->SetValue(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat() + diffuse * opacity);
        else
            texinfo->GetAttr()->GetDiffuseColor()->SetValue(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat() * (1.F - opacity) + diffuse * opacity);
    }
    return true;
}
