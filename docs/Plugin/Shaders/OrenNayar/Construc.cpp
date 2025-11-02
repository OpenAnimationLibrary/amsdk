// WEP 8/30/2002  \will100\Plugin\Shaders\OrenNayar\Construc.cpp

#include "StdAfx.h"
#include "StrClass.h"
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
    m_roughness = HPercentProperty::New(theApp.m_roughnessinfo);
    m_brightness = HPercentProperty::New(theApp.m_brightnessinfo);
}

CustomShader::~CustomShader() {
    delete m_roughness;
    delete m_brightness;
}
