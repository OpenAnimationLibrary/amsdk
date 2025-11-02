// Dan  11/26/2001  \Dan90\Plugin\Shaders\Phong\Construc.cpp

#include "StdAfx.h"
#include "Shader.h"
#include "Custom.h"
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
    m_IsFresnel = HBoolProperty::New(theApp.m_IsFresnelInfo);
}

CustomShader::~CustomShader() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    SetRegistryValue("Phong SHD", "IsFresnel", m_IsFresnel->GetValue());
    delete m_IsFresnel;
}
