// Yves  2006-05-15  \Master13.0\Plugin\Shaders\Environment\Evaluate.cpp

#include "StdAfx.h"
#include "Matrix34.h"
#include "Custom.h"
#include "resource.h"
#include "SDK/HModel.h"
//#include "RType.h"

const char *CustomShader::GetShaderDiffuseFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderSpecularFilters() {
    return nullptr;
}

const char *CustomShader::GetShaderAmbianceFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_MENUFILTER);
    return filter;
}

void CustomShader::GetDiffuse(HShading *shading) {}

bool CustomShader::GetSpecular(HShading *shading, const RGBFloat &lightcolor) {
    return false;
}

void CustomShader::GetAmbiance(HShading *shading) {
    if (m_Clip->GetClip() == nullptr)
        return;

    HTexInfo *htexinfo = shading->GetTexInfo();
    HAttrProperty *hattr = htexinfo->GetAttr();
    const RGBFloat Ca = hattr->GetDiffuseColor()->GetNormalizedRGBFloat();
//    float size = hattr->GetSpecExponent();
    const Vector &N = *htexinfo->GetN();
    Vector R = shading->GetHitP().Normalized();
    R -= N * (2.F * N.Dot(R)); // R is in Screen space now
    Matrix34 toworld;

//    Matrix34 view;
    if (m_RefBone) {
        toworld = m_RefBone->GetModelToScreenMatrix();
        toworld *= *htexinfo->GetInverseMatrix();
    } else {
        auto *bone = (HBone *)m_AxisBone->GetValue();
        if (!bone) {
            if (HModel *ChorModel = GetModel())
                bone = (HBone *)ChorModel;
        }
        if (bone) {
            toworld = bone->GetModelToScreenMatrix();
            toworld *= *htexinfo->GetInverseMatrix();
        } else
            toworld = *htexinfo->GetInverseMatrix();
    }
    TransformVectorNoTranslate(toworld, R);

    m_Width = m_Clip->GetWidth();
    m_Height = m_Clip->GetHeight();
    RGBFloat hdri = GetIBLEnvironment(R);
    hdri *= hash_math::pow(2.F, m_Exposure->GetValue()) * Ca;
    shading->SetACol(hdri);
}

void CustomShader::SampleLatitudeLongitude(Vector &n, float &u, float &v) const {
    u = (hash_math::atan2(-n.x, n.z) + hash_constants::pi) / (2.F * hash_constants::pi);
    u = (1.F - (u - fast_ftol_signed(u))) * m_Width;
    if (n.y < -1)
        n.y = -1.F;
    if (n.y > 1)
        n.y = 1.F;
    v = hash_math::cos(n.y) / hash_constants::pi;
    v = (v - fast_ftol_signed(v)) * m_Height;
}

// FROM Debevec:
// If we consider the images to be normalized to have coordinates
// u=[-1,1], v=[-1,1], we have theta=atan2(v,u), phi=pi*sqrt(u*u+v*v).
// The unit vector pointing in the corresponding direction is obtained
// by rotating (0,0,-1) by phi degrees around the y (up) axis and then
// theta degrees around the -z (forward) axis. If for a direction vector
// in the world (Dx, Dy, Dz), the corresponding (u,v) coordinate in the
// light probe image is (Dx*r,Dy*r) where r=(1/pi)*acos(Dz)/sqrt(Dx^2 + Dy^2).

void CustomShader::SampleLightProbe(const Vector &n, float &u, float &v) const {
    const float r = 0.159154943f * hash_math::cos(n.z) / hash_math::sqrt(n.x * n.x + n.y * n.y);
    u = (n.x * r + 0.5f) * m_Width;
    v = (-n.y * r + 0.5f) * m_Height;
}

void CustomShader::SampleMirroredSphere(const Vector &n, float &u, float &v) const {
    const float r = hash_math::sin(hash_math::cos(n.z) / 2.F) / (2.F * hash_math::sqrt(n.x * n.x + n.y * n.y));
    u = (n.x * r + 0.5f) * m_Width;
    v = (-n.y * r + 0.5f) * m_Height;
}

void CustomShader::SampleCubeMapCross(const Vector &n, float &u, float &v) const {
    if (n.z < 0.F && n.z <= -hash_math::abs(n.x) && n.z <= -hash_math::abs(n.y)) {
        u = 1.5f - 0.5f * n.x / n.z;
        v = 1.5f + 0.5f * n.y / n.z;
    } else if (n.z >= 0.F && n.z >= hash_math::abs(n.x) && n.z >= hash_math::abs(n.y)) {
        u = 1.5f + 0.5f * n.x / n.z;
        v = 3.5f + 0.5f * n.y / n.z;
    } else if (n.y < 0.F && n.y <= -hash_math::abs(n.x) && n.y <= -hash_math::abs(n.z)) {
        u = 1.5f - 0.5f * n.x / n.y;
        v = 2.5f - 0.5f * n.z / n.y;
    } else if (n.y >= 0.F && n.y >= hash_math::abs(n.x) && n.y >= hash_math::abs(n.z)) {
        u = 1.5f + 0.5f * n.x / n.y;
        v = 0.5f - 0.5f * n.z / n.y;
    } else if (n.x < 0.F && n.x <= -hash_math::abs(n.y) && n.x <= -hash_math::abs(n.z)) {
        u = 0.5f + 0.5f * n.z / n.x;
        v = 1.5f + 0.5f * n.y / n.x;
    } else if (n.x >= 0.F && n.x >= hash_math::abs(n.y) && n.x >= hash_math::abs(n.z)) {
        u = 2.5f + 0.5f * n.z / n.x;
        v = 1.5f - 0.5f * n.y / n.x;
    }
    u = u * m_Width / 3.0f;
    v = v * m_Height / 4.0f;
}

RGBFloat CustomShader::GetIBLEnvironment(Vector &r) const {
    RGBFloat sampledenergy;
    float opacity, u = 0.F, v = 0.F;
    switch (m_Mapping->GetValue()) {
        case LatitudeLongitude:
            SampleLatitudeLongitude(r, u, v);
            break;
        case LightProbe:
            SampleLightProbe(r, u, v);
            break;
        case MirroredSphere:
            SampleMirroredSphere(r, u, v);
            break;
        case CubeMapCross:
            SampleCubeMapCross(r, u, v);
            break;
        default: 
            break;
    }
    m_Clip->ReadBitmap(u, v, &sampledenergy, &opacity, 1.F);
    return sampledenergy * opacity;
}
