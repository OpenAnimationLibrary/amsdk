// Yves 10-12-2006  \Plugin\Shaders\PharrSkin\EvaluatePharrSkin.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "resource.h"

HProperty *CustomShader::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_ior;
        case 1:
            return m_thickness;
        default:
            return nullptr;
    }
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

void CustomShader::GetDiffuse(HShading *shading) {}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const Vector &N = *htexinfo->GetN();
    const Vector L = -*shading->GetL(); // NOTE: In shading model used by Matt Pharr,
    const Vector I = -htexinfo->GetD(); //       all vectors are pointing away from surface.
    Vector H = I + L;
    H.Normalize();
    const float l1 = shading->GetLDot();
    const float v = shading->GetEDot();
    const float h = H.Dot(N);
    const RGBFloat skincolor = shading->GetDCol();
    RGBFloat sheencolor = hattr->GetSpecularColorForRead()->GetNormalizedRGBFloat();

    const float thickness = m_thickness->GetValue() / 3.0f;
    const float ior = m_ior->GetValue();

    float kr, kt, kr2, kt2;
    const Vector T = Fresnel(I, N, v, ior, kr, kt);

    // Add glossy/diffuse reflection at edge.
    sheencolor *= lightcolor;
    sheencolor *= l1 * kr;
    if (h > 0.F)
        sheencolor *= hash_math::pow(h, 4.0f);
    else
        sheencolor *= 0.2f;
    sheencolor *= l1;
    shading->SetSCol(sheencolor);

    // Simulate subsurface scattering beneath the skin; three single scattering terms,
    // each progressively becoming more isotropic, is an ad-hoc approximation
    // to the distribution of multiply-scattered light.
    const Vector T2 = Fresnel(L, N, l1, ior, kr2, kt2);
    RGBFloat scatteringcolor = skincolor;
    scatteringcolor *= kt * kt2;
    scatteringcolor *= SingleScatter(T, T2, N, 0.8f, 0.8f, thickness) + SingleScatter(T, T2, N, 0.3f, 0.5f, thickness) + SingleScatter(T, T2, N, 0.F, 0.4f, thickness);
    shading->SetDCol(skincolor + scatteringcolor);
    return true;
}

Vector CustomShader::Fresnel(const Vector &V, const Vector &N, const float v, const float ior, float &kr, float &kt) {
    /* float angleout, iorm, iora, iorh;   // Compute Refraction direction as in Refracti.cpp
       Vector dout;
       float sino2, sini2m = v * v - 1.F;
       if ((sino2 = 1 + ior*ior * sini2m) > 0) {
          angleout = ior * v - sqrt( sino2 );
          dout = ior * V + angleout * N;
          dout.Normalize();
          iorm = N.Dot(dout);
          iorm = sqrt(1-v) / sqrt(1-iorm);
       }
    */
    // Compute Snell's law
    const float iior = -hash_math::rcp(ior);
    const float sini2 = 1.F - hash_math::sqr(v);
    float beta = v;
//    float ir = iior * iior - sini2;
    /*   if ( ir < 0.F ) { // Process "Total Internal Reflection" condition.
          Vector T( -V );
          kr = 1.F;
          kt = 0.F;
          return T;
       }
    */
    beta -= hash_math::sqrt(hash_math::sqr(ior) - sini2);
    Vector T(N);
    T *= beta;
    T -= V;
    T *= iior;
//    float iora = N.Dot(T);
//    iora = hash_math::sqrt(1 - v) / hash_math::sqrt(1 - iora);
    /*
       float c2 = 0.F;     // Compute refraction direction Heckbert way
       iior = -1.F / ior;
       float sini2h = 1.F - v * v;
       float coso2h = 1.F - ior*ior * sini2h;
       if ( coso2h >= 0.F )
          c2 = sqrt( coso2h );
       Vector Th = N;
       Th *= iior * v + c2;
       Th -= V * iior;
       iorh = N.Dot(Th);
       iorh = sqrt(1-v) / sqrt(1-iorh);
    */
    const float t = N.Dot(T);
    float rpar = ior * v;
    rpar = (rpar - t) / (rpar + t);
    float rper = ior * t;
    rper = (v - rper) / (v + rper);
    kr = (hash_math::sqr(rpar) + hash_math::sqr(rper)) * 0.5f;
    /*   if ( ir < 0.F ) { // Process "Total Internal Reflection" condition.
          kt = 0.F;
       else
    */
    kt = 1.F - kr;
    return T;
}

float CustomShader::SingleScatter(const Vector &wi, const Vector &wo, const Vector &n, const float assymetry, const float albedo, const float thickness) {
    const float win = hash_math::abs(wi.Dot(n));
    const float won = hash_math::abs(wo.Dot(n));
    return albedo * Phase(wo, wi, assymetry) / (win + won) * (1.F - exp(-(hash_math::rcp(win) + hash_math::rcp(won)) * thickness));
}

float CustomShader::Phase(const Vector &v1, const Vector &v2, const float assymetry) {
    // Compute the Henyey-Greenstein phase function.
    const float costheta = -v1.Dot(v2);
    return (1.F - hash_math::sqr(assymetry)) / hash_math::pow(1.F + hash_math::sqr(assymetry) - 2.F * assymetry * costheta, 1.5f);
}
