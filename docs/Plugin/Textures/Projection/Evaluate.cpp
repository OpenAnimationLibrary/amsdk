// MH  22 Apr 2002

#include "StdAfx.h"
#include "Custom.h"
#include "Matrix34.h"
#include "TexApp.h"

HProperty *CustomTexture::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_clip;
        case 1:
            return m_type;
        case 2:
            return m_kind;
        case 3:
            return m_value;
        case 4:
            return m_size;
        default:
            return nullptr;
    }
}

bool CustomTexture::EvaluateTransparency(const Vector &evalp, HTexInfo *texinfo) {
    return TRUE;
}

//static int breakx = 1137, breaky = 200;

bool CustomTexture::Evaluate(const Vector &evalp, HTexInfo *texinfo) {
    if (m_clip->GetClip() == nullptr)
        return FALSE;

    float mapx = 0.F, mapy = 0.F, opacity;
    const Vector2 size = m_size->GetValue();
    //    Vector2 repeat = m_clip->GetRepeat()->GetValue();

    const Vector n = evalp.Normalized();

    if (m_type->GetValue() == CTextureApp::SPHERICAL) {
        mapy = hash_math::cos(n.y) / hash_constants::pi;
        mapy = mapy - fast_ftol_signed(mapy);
    }
    if (m_type->GetValue() == CTextureApp::SPHERICAL || m_type->GetValue() == CTextureApp::CYLINDRICAL) {
        mapx = (hash_math::atan2(-n.x, n.z) + hash_constants::pi) / (2.F * hash_constants::pi);
        mapx = 1.F - (mapx - fast_ftol_signed(mapx));
    }
    if (m_type->GetValue() == CTextureApp::PLANAR || m_type->GetValue() == CTextureApp::CYLINDRICAL) {
        if (evalp.y > size.y / 2.F || evalp.y < -size.y / 2.F)
            return FALSE;
        mapy = evalp.y / size.y + 0.5F;
        mapy = MIN(1.F, MAX(0.F, mapy));
        mapy = 1.F - (mapy - fast_ftol_signed(mapy));
    }
    if (m_type->GetValue() == CTextureApp::PLANAR) {
        if (evalp.x > size.x / 2.F || evalp.x <= -size.x / 2.F)
            return FALSE;
        mapx = evalp.x / size.x + 0.5F;
        mapx = MIN(1.F, MAX(0.F, mapx));
        mapx = mapx - fast_ftol_signed(mapx);
    }
    const auto right = (float)m_clip->GetWidth();
    const auto bottom = (float)m_clip->GetHeight();
    if (mapx == 1.F)
        mapx = 0.F;
    if (mapy == 1.F)
        mapy = 0.F;
    const float x = mapx * right;
    const float y = mapy * bottom;

    RGBFloat color;
    BOOL hit = FALSE;
    if (m_kind->GetValue() != CTextureApp::BUMPMAP)
        hit = m_clip->ReadBitmap(x, y, &color, &opacity, texinfo->GetPixelWidth());

    float percent = m_value->GetValue() / 100.F;
    HAttrProperty *hattr = texinfo->GetAttr();

    switch (m_kind->GetValue()) {
        case CTextureApp::OPAQUEMAP:
            percent *= opacity;
            hattr->GetDiffuseColor()->SetValue(MAX(1.F - percent, 0.F) * hattr->GetDiffuseColor()->GetNormalizedRGBFloat() + color * percent);
            break;
        case CTextureApp::TRANSPARENCYMAP:
            hattr->GetTransparency()->SetValue(MIN((1.F - MAKELUMINANCE(color.m_red, color.m_green, color.m_blue)) * percent * opacity, 1.F));
            break;
        case CTextureApp::BUMPMAP:
        {
            Vector2 delta;
            Vector tilt;
            if (!m_clip->ReadBumpmap(x, y, delta, texinfo->GetPixelWidth()))
                break;
            if (delta.x == 0.F && delta.y == 0.F)
                break;
            delta *= percent;
            if (delta.x > 1.F)
                delta.x = 1.F;
            if (delta.y > 1.F)
                delta.y = 1.F;
            const float yangle = delta.x * -90.F / hash_constants::radians, xangle = delta.y * -90.F / hash_constants::radians;
            const float cy = hash_math::cos(yangle), sy = hash_math::sin(yangle), cx = hash_math::cos(xangle), sx = hash_math::sin(xangle);
            tilt.Set(sy * cx, -sx, cy * cx); // THESE ARE THE Z COLUMN FROM YXRotateRadians(), MUCH FASTER THAN BUILDING IT THEN TRANSFORMING 0,0,1
            Vector *N = texinfo->GetN();
            const Matrix34 materialtomap = VectorsToStandard(*N, Vector(0.F, 1.F, 0.F));
            *N = tilt * materialtomap.Transpose();
            break;
        }
        case CTextureApp::SPECULARSIZEMAP:
            hattr->GetSpecularSize()->SetValue((1.F - opacity) * hattr->GetSpecularSize()->GetValue() + MAKELUMINANCE(color.m_red, color.m_green, color.m_blue) * opacity * percent);
            break;
        case CTextureApp::SPECULARINTENSITYMAP:
            hattr->GetSpecularIntensity()->SetValue((1.F - opacity) * hattr->GetSpecularIntensity()->GetValue() + MAKELUMINANCE(color.m_red, color.m_green, color.m_blue) * opacity * percent);
            break;
        case CTextureApp::DIFFUSEMAP:
        {
            percent *= opacity;
            float mapintensity = MAKELUMINANCE(color.m_red, color.m_green, color.m_blue);
            mapintensity *= percent;
            mapintensity += 1.F - percent;
            if (mapintensity < 0.F)
                mapintensity = 0.F;
            hattr->GetDiffuseColor()->SetValue(mapintensity * hattr->GetDiffuseColor()->GetNormalizedRGBFloat());
            break;
        }
        case CTextureApp::MIRRORMAP:
            hattr->GetReflectivity()->SetValue((1.F - opacity) * hattr->GetReflectivity()->GetValue() + MAKELUMINANCE(color.m_red, color.m_green, color.m_blue) * opacity * percent);
            break;
        case CTextureApp::AMBIANCEMAP:
            hattr->GetAmbiance()->SetValue((1.F - opacity) * hattr->GetAmbiance()->GetValue() + MAKELUMINANCE(color.m_red, color.m_green, color.m_blue) * opacity * percent);
            break;
        case CTextureApp::COOKIECUTMAP:
            if (!hit) {
                opacity = 0;
                percent = 0;
            } else
                percent *= opacity;
            hattr->GetDiffuseColor()->SetValue(MAX(1.F - percent, 0.F) * hattr->GetDiffuseColor()->GetNormalizedRGBFloat() + color * percent);
            if (opacity < 1.F)
                hattr->GetTransparency()->SetValue(1.F - opacity);
            break;
        case CTextureApp::NORMALMAP:
        {
            Vector tilt;
            tilt.x = color.m_red * 2.F - 1.F;
            tilt.y = color.m_green * 2.F - 1.F;
            tilt.z = hash_math::sqrt(hash_math::abs(1.F - tilt.x * tilt.x - tilt.y * tilt.y));
            TransformVectorNoTranslate(*texinfo->GetMatrix(), tilt);
            Vector *N = texinfo->GetN();
            const Matrix34 materialtomap = VectorsToStandard(*N, Vector(0.F, 1.F, 0.F));
            *N = tilt * materialtomap.Transpose();
            break;
        }
    }

    return TRUE;
}
