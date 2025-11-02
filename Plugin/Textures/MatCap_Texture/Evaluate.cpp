// KB  1/2/01  \Ken90\Plugin\Textures\Crumple\Evaluate.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_clip;
        case 1:
            return m_opacity;
        case 2:
            return m_additiv;
        default:
            return nullptr;
    }
}

HObjectListNode *CustomTexture::GetPointerList(HPointerPropertyBase *) {
    return nullptr;
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {

    if (m_clip->GetClip() == nullptr)
        return FALSE;


    const Vector n = *texinfo->GetN();
//    const float xcolor = ((n.Normalize().x / 2.F) * 0.95f) + 0.5F;
//    const float ycolor = (((n.Normalize().y / 2.F) * -1.0f) * 0.95f) + 0.5F;

    Vector n1 = n.Normalized();
    n1 *= 0.5F;
    const float xcolor = n1.x * 0.95F + 0.5F;
    const float ycolor = -n1.y * 0.95F + 0.5F;

    const float mapx = xcolor * m_clip->GetWidth();
    const float mapy = ycolor * m_clip->GetHeight();

    //m_clip->ReadBitmap(mapx, mapy, &diffuse, &opacity, 1);

    float opacity;
    RGBFloat diffuse;
    if (!m_clip->ReadBitmap(mapx, mapy, &diffuse, &opacity, texinfo->GetPixelWidth()))
        return FALSE;
    if (opacity != 0.F) {
        opacity *= m_opacity->GetValue() / 100.F;
        if (m_additiv->GetValue())
            texinfo->GetAttr()->GetDiffuseColor()->SetValue(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat() + diffuse * opacity);
        else
            texinfo->GetAttr()->GetDiffuseColor()->SetValue(texinfo->GetAttr()->GetDiffuseColor()->GetNormalizedRGBFloat() * (1.F - opacity) + diffuse * opacity);
    }
    return TRUE;
}
