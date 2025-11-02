// Yves  2005/10/19  \Master13.0\Pugin\Shaders\WardAnisotropic\Custom.h

#pragma once
#include <afxwin.h>
#include "ShadeDll.h"
#include "resource.h"
#include "SDK/HPropert.h"

class HBoneContainer;

class CustomShader final : public Shader {
public:
    HTypeProperty *m_Material;
    HPercentProperty *m_RoughnessX;
    HPercentProperty *m_RoughnessY;
    HTypeProperty *m_Alignment;
    HBoolProperty *m_IsIsotropic;
    HBoolProperty *m_IsBRDF;
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
        return "Hash\\Ward";
    }

    void Copy(const DLLPlugin &other) override;

    // EVALUATION
    const char *GetShaderDiffuseFilters() override;
    const char *GetShaderSpecularFilters() override;
    ShaderType GetShaderType() override;
    // RENDERING
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time) override;
    HObjectListNode *GetPointerList(HPointerPropertyBase *prop) override;
    bool GetSpecular(HShading *shading, const RGBFloat &lightcolor) override;
    void GetDiffuse(HShading *shading) override;
    RGBFloat GetBRDF(HShading *shading, HTexInfo *htexinfo, HAttrProperty *hattr) const;
    Vector GetSurfaceTangent(HShading *shading, HTexInfo *htexinfo, const Vector &N, BOOL &failed) const;
    [[nodiscard]] RGBFloat WardIsotropic(float h, float v, float l, float r) const;
    [[nodiscard]] RGBFloat WardAnisotropic(float h, float v, float l, float w, float rt, float rp) const;
    static void RecurseBoneList(HObjectListNode **previous, HBone *parentbone);
    static HBone *MatchChorBone(HBone *ModelBone, HBoneContainer *ChorBoneContainer);
};
