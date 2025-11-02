// MH 8/28/2008 Created.

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
    m_IsWhite = HBoolProperty::New(theApp.m_IsWhiteInfo);
}

CustomShader::~CustomShader() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    SetRegistryValue("White SHD", "IsWhite", m_IsWhite->GetValue());
    delete m_IsWhite;
}
