// Yves Poissant  2004/03/21  \My Plugins\Shaders\Ward\EvaluateWard.cpp

#include "StdAfx.h"
#include "Shader.h"
#include "Custom.h"
#include "resource.h"
#include "Matrix34.h"
#include "SDK/HModel.h"

Shader::ShaderType CustomShader::GetShaderType() {
    if (m_IsBRDF->GetValue())
        return ST_BRDF;
    return ST_NORMAL;
}

const char *CustomShader::GetShaderDiffuseFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderSpecularFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const RGBFloat Cd = hattr->GetDiffuseColor()->GetNormalizedRGBFloat();
    float kd = 1.F - hattr->GetSpecularIntensity()->GetValue();
    if (kd < 0.F)
        kd = 0.F;
    shading->SetDCol(Cd * (shading->GetLDot() * kd));
}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const float Ks = hattr->GetSpecularIntensity()->GetValue();
    if (Ks == 0.F)
        return false;
    const RGBFloat Cs = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat() * Ks;
    const RGBFloat Cl = lightcolor * shading->GetIntensity() * shading->GetLDot();
    shading->SetSCol(GetBRDF(shading, htexinfo, hattr) * Cs * Cl);
    return true;
}

RGBFloat CustomShader::GetBRDF(HShading *shading, HTexInfo *htexinfo, HAttrProperty *hattr) const {
    const Vector V = -htexinfo->GetD();
    const Vector L = -*shading->GetL();
    const Vector N = *htexinfo->GetN();
    BOOL doisotropic;
    const Vector T = GetSurfaceTangent(shading, htexinfo, N, doisotropic);
    Vector H = V + L;
    H.Normalize();
    const float h = H.Dot(N);
    //    float u = H.Dot(V);
    const float v = shading->GetEDot();
    const float l = shading->GetLDot();
    // To get P, the projection of H on the plane perpendicular to N,
    // project H on N and subtract the result from H
    Vector P = H - N * h;
    P.Normalize();
    if (doisotropic || m_IsIsotropic->GetValue()) {
        float r = (m_RoughnessX->GetValue() + m_RoughnessY->GetValue()) * 0.5f;
        if (m_Material->GetValue() == NPRESETS - 1) {
            const float size = hattr->GetSpecExponent();
            r *= hash_math::sqrt(2.F / size); // This is to match Phong specular sizes
        }
        return WardIsotropic(h, v, l, r);
    }
    const float w = hash_math::abs(T.Dot(P));
    float size = 1.F;
    if (m_Material->GetValue() == NPRESETS - 1) {
        size = hattr->GetSpecExponent();
        size = hash_math::sqrt(2.F / size); // This is to match Phong specular sizes
    }
    return WardAnisotropic(h, v, l, w, size * m_RoughnessX->GetValue(), size * m_RoughnessY->GetValue());
}

Vector CustomShader::GetSurfaceTangent(HShading *shading, HTexInfo *htexinfo, const Vector &N, BOOL &failed) const {
    Vector Dir(0.F, 0.1f, 0.F);
    Vector Base(0.F, 0.F, 0.F);
    Matrix34 view;
    if (m_RefBone) {
        //        Matrix34 BoneMatrix;
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
            T = Dir - N * N.Dot(Dir);
            if ((l = T.Norm()) == 0.F)
                failed = TRUE;
            else
                T /= l;
            break;

        case 1: // Up Vector
            T = N ^ Dir;
            if ((l = T.Norm()) == 0.F)
                failed = TRUE;
            else
                T /= l;
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
        default:;
    }
    return T;
}

RGBFloat CustomShader::WardIsotropic(const float h, const float v, const float l, const float r) const {
    const float hh = hash_math::sqr(h);
    const float rr = hash_math::sqr(r);
    const float e = hash_math::exp((hh - 1.F) / (hh * rr));
    if (m_IsBRDF->GetValue())
        return e / (hash_math::sqrt(v * l) * 4.F * rr);
    return e;
}

RGBFloat CustomShader::WardAnisotropic(const float h, const float v, const float l, const float w, const float rt, const float rp) const {
    const float hh = hash_math::sqr(h);
    const float ww = hash_math::sqr(w);
    const float e = hash_math::exp((hh - 1.F) / hh * (ww / hash_math::sqr(rt) + (1.F - ww) / hash_math::sqr(rp)));
    if (m_IsBRDF->GetValue())
        return e / (hash_math::sqrt(v * l) * 4.F * rt * rp);
    return e;
}
