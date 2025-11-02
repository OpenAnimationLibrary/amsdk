// 

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"
#include "Matrix34.h"
#include "SDK/HThreadInfo.h"
//#include <iostream>

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_diffBlend;
        case 1:
            return m_diffStrength;
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
    if (shading->GetHit()) {
        HTexInfo *htexinfo = shading->GetTexInfo();
        HAttrProperty *hattr = htexinfo->GetAttr();
        const HColorProperty *diffuseColor = hattr->GetDiffuseColor();
        RGBFloat dcol = diffuseColor->GetNormalizedRGBFloat();
//        const float diff_blend = m_diffBlend->GetValue();
        const float diff_strenth = m_diffStrength->GetValue();

        // Calculate the real Normal   
        const float value = 2.F * shading->GetHit()->GetU() - 1.F;
        const float cosTheta = value;

        Vector T = shading->GetHairTangent();
        T.Normalize();

        Vector V = shading->GetHairCenter().Normalized();
        V.Negate();

        Vector L = *shading->GetL();
        L.Negate();
        L.Normalize();

        Vector CPrime = V - T.Dot(V) * T;
        CPrime.Normalize();
        Vector B = CPrime.Cross(T);
        B.Negate();
        B.Normalize();
        const float sinTheta = hash_math::sqrt(1.F - cosTheta * cosTheta);
        Vector N = B * cosTheta + CPrime * sinTheta;
        N.Normalize();

        // Store N for the specular shader
        *htexinfo->GetN() = N;

//        const Vector rootN = shading->GetHairRootNormal();

        // also bend the normal used for our diffuse calcs
//        Vector diffN = N * (1.F - diff_blend) + rootN * diff_blend;

        const float diffuse_dot = N.Dot(L) / 2.F + 0.5f;

        // diffuse
        dcol *= diffuse_dot * diff_strenth;
        shading->SetDCol(dcol);
    }
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}
