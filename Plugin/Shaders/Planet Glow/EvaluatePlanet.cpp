// Yves  2005-11-22  \Master13.0\Plugin\Shaders\PlanetGlow\EvaluatePlanet.cpp

#include "StdAfx.h"
#include "Shader.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_Falloff;
        case 1:
            return m_Glow;
        case 2:
            return m_Fade;
        case 3:
            return m_Xparency;
        case 4:
            return m_LoColor;
        case 5:
            return m_HiColor;
        default:
            return nullptr;
    }
}

const char *CustomShader::GetShaderDiffuseFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

const char *CustomShader::GetShaderSpecularFilters() {
    return nullptr;
}

void CustomShader::GetDiffuse(HShading *shading) {
    HAttrProperty *hattr = shading->GetTexInfo()->GetAttr();
    const float opacity = 1.F - hattr->GetTransparency()->GetValue();
    if (opacity == 0.F)
        return;
    RGBFloat Cd = hattr->GetDiffuseColor()->GetNormalizedRGBFloat();
    const float DiffuseFalloff = hattr->GetDiffuseFallOff()->GetValue();
    float shade = shading->GetLDot();
    float density = shading->GetEDot();
    float span = hash_math::sqrt(1.F - hash_math::sqr(density));
    if (DiffuseFalloff != 1.F) {
        if (DiffuseFalloff)
            shade = MIN(1.F, shade / DiffuseFalloff);
        else
            shade = 0.F;
    }
    const float falloff = m_Falloff->GetValue(); // Fraction of planet size vs atmosphere size
    if (const float factor = hash_math::sqrt(1.F - hash_math::sqr(falloff)); span > falloff) {
        // Do the silhouette atmospheric layer
        density /= factor; // Normalize so density is 1 at falloff distance
        density = hash_math::pow(density, m_Fade->GetValue()); // Compensate for dust and mist near the planet surface
        Cd = MixColor(m_HiColor->GetNormalizedRGBFloat(), m_LoColor->GetNormalizedRGBFloat(), density);
        density *= m_Glow->GetValue();
    } else {
        // Do the transparent atmospheric cover over the planet
        span /= falloff; // Normalize span projection on planet surface
        density -= hash_math::sqrt(1.F - hash_math::sqr(span)) * falloff; // Subtract projected planet view cosine from density
        density /= 2.F * factor; // Normalize for only one side of density
        density *= m_Xparency->GetValue();
    }
    density /= opacity;
    shading->SetDCol(Cd * shade * density);
    //	shading->SetDCol( Cd * (float) shade );
    //	transparency = 1.0 - opacity * shade;
    //	hattr->GetTransparency()->SetValue( (float)transparency );
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}

RGBFloat CustomShader::MixColor(const RGBFloat &c1, const RGBFloat &c2, const double mix) {
    return (c2 - c1) * (float)mix + c1;
}
