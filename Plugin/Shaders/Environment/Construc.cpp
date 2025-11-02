// Yves  2006-05-15  \Master13.0\Plugin\Shaders\Environment\Construc.cpp

#include "StdAfx.h"
#include "Shader.h"
#include "Custom.h"

extern CShaderApp theApp;

extern "C" __declspec(dllexport) Shader *CreateShader(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomShader(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return SHADERDLLVERSION;
}

CustomShader::CustomShader(HTreeObject *treeobject) : Shader2(treeobject) {
    m_Clip = HClipProperty::New(theApp.m_ClipInfo);
    m_Mapping = HTypeProperty::New(theApp.m_MappingInfo);
    m_Exposure = HFloatProperty::New(theApp.m_ExposureInfo);
    m_AxisBone = HPointerProperty::New(theApp.m_AxisBoneInfo);
    m_ObjType = HOT_MODEL; // Or on a group is the same
    m_RefBone = nullptr;
    m_Chor = nullptr;
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
            m_Chor = (HChor *)obj;
            return;
        }
}

CustomShader::~CustomShader() {
    delete m_Clip;
    delete m_Mapping;
    delete m_Exposure;
    delete m_AxisBone;
}
