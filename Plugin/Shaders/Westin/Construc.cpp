// Yves  2005/11/24  \Master13.0\Plugin\Shaders\Westin\Construc.cpp

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
    m_IsPerpendicular = HBoolProperty::New(theApp.m_IsPerpendicularInfo);
    m_Alignment = HTypeProperty::New(theApp.m_AlignmentInfo);
    m_IsIsotropic = HBoolProperty::New(theApp.m_IsIsotropicInfo);
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
    SetRegistryValue("Westin SHD", "IsPerpendicular", m_IsPerpendicular->GetValue());
    SetRegistryValue("Westin SHD", "Alignment", (int)m_Alignment->GetValue());
    SetRegistryValue("Westin SHD", "IsIsotropic", m_IsIsotropic->GetValue());

    delete m_IsPerpendicular;
    delete m_Alignment;
    delete m_IsIsotropic;
    delete m_AxisBone;
}
