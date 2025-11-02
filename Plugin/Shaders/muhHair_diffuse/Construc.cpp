// 

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
    m_diffStrength = HPercentProperty::New(theApp.m_diffStrengthInfo);
    m_diffBlend = HPercentProperty::New(theApp.m_diffBlendInfo);
}

CustomShader::~CustomShader() {
    delete m_diffStrength;
    delete m_diffBlend;
}
