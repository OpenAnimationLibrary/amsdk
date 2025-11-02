// Yves  2006-05-15  \Master13.0\Plugin\Shaders\Environment\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"
#include "SDK/HChor.h"

class HBoneContainer;

class CustomShader final : public Shader2 {
public:
    enum { LatitudeLongitude, LightProbe, MirroredSphere, CubeMapCross };

    HClipProperty *m_Clip;
    HTypeProperty *m_Mapping;
    HFloatProperty *m_Exposure;
    CustomShader *m_Original{};
    int m_ObjType;
    HBone *m_RefBone;
    HPointerProperty *m_AxisBone;
    HChor *m_Chor;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomShader(HTreeObject *treeobject);
    ~CustomShader() override;

    CustomShader(const CustomShader &) = delete;
    CustomShader &operator=(const CustomShader &) = delete;
    CustomShader(CustomShader &&) = delete;
    CustomShader &operator=(CustomShader &&) = delete;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_ICON1;
    }

    UINT GetNameID() noexcept override {
        return IDS_SHADERNAME;
    }

    const char *GetClassName() override {
        return "Hash\\Environment";
    }

    void Copy(const DLLPlugin &other) override;

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    const char *GetShaderAmbianceFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time) override;
    HObjectListNode *GetPointerList(HPointerPropertyBase *prop) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
    void GetAmbiance(HShading *shading) override;

    // OPERATION
    int m_Width{};
    int m_Height{};
    int m_MapType{};
    void SampleLightProbe(const Vector &n, float &u, float &v) const;
    void SampleLatitudeLongitude(Vector &n, float &u, float &v) const;
    void SampleMirroredSphere(const Vector &n, float &u, float &v) const;
    void SampleCubeMapCross(const Vector &n, float &u, float &v) const;
    RGBFloat GetIBLEnvironment(Vector &r) const;
    static void RecurseBoneList(HObjectListNode **previous, HBone *parentbone);
    static HBone *MatchChorBone(HBone *ModelBone, HBoneContainer *ChorBoneContainer);
};
