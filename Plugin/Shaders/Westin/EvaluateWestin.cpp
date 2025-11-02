// Yves  2005/11/24  \Master13.0\Plugin\Shaders\Westin\EvaluateWestin.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"
#include "Matrix34.h"
#include "SDK/HModel.h"

const char *CustomShader::GetShaderDiffuseFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderSpecularFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const float size = hattr->GetSpecExponent();
    if (size == 0.F)
        return false;
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    if (Ks == 0.F)
        return false;
    const RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();
    const RGBFloat Cl = lightcolor * shading->GetIntensity() * shading->GetLDot();
    shading->SetSCol(GetBRDF(shading, htexinfo, size) * Cs * Cl * Ks);
    return true;
}

// Based on Steffen H Westin Brushed Metal Renderman shader
RGBFloat CustomShader::GetBRDF(HShading *shading, HTexInfo *htexinfo, const float size) const {
    const Vector &N = *htexinfo->GetN();
    const Vector &L = *shading->GetL();
    const Vector V = htexinfo->GetD();
    BOOL doisotropic;
    Vector T = GetSurfaceTangent(shading, htexinfo, N, doisotropic);
    if (m_IsPerpendicular->GetValue())
        T = T.Cross(N);
    const float v = shading->GetEDot();
    const float l = shading->GetLDot();
    float aniso;
    if (doisotropic || m_IsIsotropic->GetValue())
        aniso = MAX(l * v, 0.F);
    else {
        const float cosI = -T.Dot(V);
        const float sinI = hash_math::sqrt(1.F - hash_math::sqr(cosI));
        const float cosL = T.Dot(L);
        const float sinL = hash_math::sqrt(1.F - hash_math::sqr(cosL));
        aniso = MAX(cosL * cosI + sinL * sinI, 0.F);
    }
    aniso = hash_math::pow(aniso, size);
    const float shad = MAX(v, 0.F) * MAX(l, 0.F);
    const float spec = aniso * shad;
    return spec;
}

Vector CustomShader::GetSurfaceTangent(HShading *shading, HTexInfo *htexinfo, const Vector &N, BOOL &failed) const {
    Vector Dir(0.F, 0.1f, 0.F);
    Vector Base;
    Matrix34 view;
    if (m_RefBone) {
        Base = m_RefBone->GetPivot();
        Dir = m_RefBone->GetEnd();
        view = m_RefBone->GetModelToScreenMatrix();
    } else {
        if (auto *bone = (HBone *)m_AxisBone->GetValue()) {
            Base = bone->GetPivot();
            Dir = bone->GetEnd();
        }
        view = *htexinfo->GetMatrix();
    }
    Base = Base * view;
    Dir = Dir * view - Base;
    Dir.Normalize();
    float l;
    failed = FALSE;
    Vector T;
    switch (m_Alignment->GetValue()) {
        case 0: // Tangent Vector
        {
            T = Dir - N * N.Dot(Dir);
            if ((l = T.Norm()) == 0.F)
                failed = TRUE;
            else
                T /= l;
        }
        break;

        case 1: // Up Vector
        {
            T = N ^ Dir;
            if ((l = T.Norm()) == 0.F)
                failed = TRUE;
            else
                T /= l;
        }
        break;

        case 2: // Axis Vector
        {
            Vector P = shading->GetHitP() - Base;
            if ((l = P.Norm()) == 0.F) // Hit point share position with pivot
                failed = TRUE; // Nothing we can do. Just shade isotropicly
            else {
                P /= l;
                Vector G = P - Dir * P.Dot(Dir);
                if ((l = G.Norm()) == 0.F) // Hit point is colinear with bone pivot and direction
                    failed = TRUE; // Nothing we can do. Just shade isotropicly
                else {
                    G /= l;
                    T = N ^ G;
                    if ((l = T.Norm()) < 0.05f) {
                        // Dir is coplanar with Normal plane
                        T = N ^ Dir;
                        T.Normalize();
                    } else
                        T /= l;
                }
            }
        }
        break;
        default:
            break;
    }
    return T;
}
