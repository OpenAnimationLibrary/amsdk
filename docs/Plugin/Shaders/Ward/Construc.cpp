// Yves Poissant  2004/03/21  \My Plugins\Shaders\WardAnisotropic\Construc.cpp

#include "StdAfx.h"
#include "StrClass.h"
#include "Custom.h"
#include "Shader.h"
#include "F_Protos.h"

extern CShaderApp theApp;

extern "C" __declspec(dllexport) Shader *CreateShader(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomShader(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return SHADERDLLVERSION;
}

CustomShader::CustomShader(HTreeObject *treeobject) : Shader(treeobject) {
    m_Material = HTypeProperty::New(theApp.m_MaterialInfo);
    m_RoughnessX = HPercentProperty::New(theApp.m_RoughnessXInfo);
    m_RoughnessY = HPercentProperty::New(theApp.m_RoughnessYInfo);
    m_Alignment = HTypeProperty::New(theApp.m_AlignmentInfo);
    m_IsIsotropic = HBoolProperty::New(theApp.m_IsIsotropicInfo);
    m_IsBRDF = HBoolProperty::New(theApp.m_IsBRDFInfo);
    m_AxisBone = HPointerProperty::New(theApp.m_AxisBoneInfo);
    m_ObjType = HOT_MODEL; // Or on a group is the same
    m_RefBone = nullptr;
    HModel *mdl = GetModel();
    HTreeObject *obj;
    if (!mdl) {
        if ((obj = GetOwner()) == nullptr)
            return; // This is a registration instance. Don't bother
        while ((obj = obj->GetParent()))
            if (obj->GetObjectType() == HOT_MATERIAL) {
                m_AxisBone->Show(FALSE); // Don't show if we are on a material attribute.
                m_ObjType = HOT_MATERIAL;
                return;
            }
        m_ObjType = -1; // This is the render instance
        return;
    }
    obj = (HTreeObject *)mdl;
    while ((obj = obj->GetParent()))
        if (obj->GetObjectType() == HOT_CHOR) {
            m_AxisBone->Show(FALSE); // Don't show if we are on a chor instance
            m_ObjType = HOT_CHOR;
            return;
        }
}

CustomShader::~CustomShader() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    SetRegistryValue("Ward SHD", "Material", (int)m_Material->GetValue());
    SetRegistryValue("Ward SHD", "RoughX", m_RoughnessX->GetValue());
    SetRegistryValue("Ward SHD", "RoughY", m_RoughnessY->GetValue());
    SetRegistryValue("Ward SHD", "Alignment", (int)m_Alignment->GetValue());
    SetRegistryValue("Ward SHD", "IsIsotropic", m_IsIsotropic->GetValue());
    SetRegistryValue("Ward SHD", "IsBRDF", m_IsBRDF->GetValue());

    delete m_Material;
    delete m_RoughnessX;
    delete m_RoughnessY;
    delete m_Alignment;
    delete m_IsIsotropic;
    delete m_IsBRDF;
    delete m_AxisBone;
}
