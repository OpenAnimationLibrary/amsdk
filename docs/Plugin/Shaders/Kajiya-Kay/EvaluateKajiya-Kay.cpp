// 

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"
#include "Matrix34.h"
#include <iostream>
#include <exception>

HProperty *CustomShader::GetPropertyAt(int i) {
    return nullptr;
    /*
    switch (i) {
       case 0:
          return m_myfirstproperty;
       default:
          return nullptr;
    }
    */
}

const char *CustomShader::GetShaderDiffuseFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

const char *CustomShader::GetShaderSpecularFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {
    if (shading->GetHit()) {
        HTexInfo *htexinfo = shading->GetTexInfo();
        HAttrProperty *hattr = htexinfo->GetAttr();
        const HColorProperty *diffuseColor = hattr->GetDiffuseColor();
        RGBFloat dcol = diffuseColor->GetNormalizedRGBFloat();

        // Get the hair tangent vector
        const Vector T = shading->GetHairTangent();

        // Get the light vector and make sure it's pointing the correct way (away)
        Vector L = *shading->GetL();
        L.Normalize();
        L.Negate();

        float dotTL = L.Dot(T);

        if (dotTL < 0.F)
            dotTL = 0.F;

        // Sin(T,L)
        dcol *= hash_math::sqrt(1.F - dotTL * dotTL);
        shading->SetDCol(dcol);
    }
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const HColorProperty *specularcolor = hattr->GetSpecularColorForRead();

    if (hattr->GetSpecularIntensity()->GetValue() > 0.005f) {
        // Get the viewing vector and point it the proper way
        Vector V = htexinfo->GetD();
        V.Negate();
        V.Normalize();

        // Get the hair tangent vector
        Vector T = shading->GetHairTangent();
        T.Normalize();

        // Get the light vector and point it in the proper direction
        Vector L = *shading->GetL();
        L.Normalize();
        L.Negate();

        const float dotTL = T.Dot(L);
        const float dotTV = T.Dot(V);
        const float sinTL = hash_math::sqrt(1 - dotTL * dotTL);
        const float sinTV = hash_math::sqrt(1 - dotTV * dotTV);

        const float value = dotTL * dotTV + sinTL * sinTV;

        if (value < 0.F)
            return false;

        // Now calculate the normal phong specular shading
        const float f = hattr->GetSpecularIntensity()->GetValue() * hash_math::pow(value, hattr->GetSpecExponent());
        RGBFloat speccolor = f;

        speccolor *= specularcolor->GetNormalizedRGBFloat() * lightcolor * shading->GetIntensity();

        shading->SetSCol(speccolor);
        return true;
    }
    return false;
}
