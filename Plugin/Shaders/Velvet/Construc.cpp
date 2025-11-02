// Yves  2005-11-24  \Master13.0\Plugin\Shaders\Velvet\Construc.cpp

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

CustomShader::CustomShader(HTreeObject *treeobject) : Shader(treeobject) {
    m_Sheen = HPercentProperty::New(theApp.m_SheenInfo);
    m_Edginess = HFloatProperty::New(theApp.m_EdginessInfo);
}

CustomShader::~CustomShader() {
    delete m_Sheen;
    delete m_Edginess;
}
