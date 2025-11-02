// Yves  2005/11/24  \Master13.0\Plugin\Shaders\Westin\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class HBoneContainer;

class CustomShader final : public Shader {
public:
    HBoolProperty *m_IsPerpendicular;
    HTypeProperty *m_Alignment;
    HBoolProperty *m_IsIsotropic;
    HPointerProperty *m_AxisBone;

    int m_ObjType;
    HBone *m_RefBone;
    CustomShader *m_Original{};

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
        return "Hash\\Westin";
    }

    void Copy(const DLLPlugin &other) override;

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time) override;
    HObjectListNode *GetPointerList(HPointerPropertyBase *prop) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
    RGBFloat GetBRDF(HShading *shading, HTexInfo *htexinfo, float size) const;
    Vector GetSurfaceTangent(HShading *shading, HTexInfo *htexinfo, const Vector &N, BOOL &failed) const;
//    RGBFloat WardIsotropic(float h, float v, float l, float r, RGBFloat C);
//    RGBFloat WardAnisotropic(float h, float v, float l, float w, float rt, float rp, RGBFloat C);
    static void RecurseBoneList(HObjectListNode **previous, HBone *parentbone);
    static HBone *MatchChorBone(HBone *ModelBone, HBoneContainer *ChorBoneContainer);
};
