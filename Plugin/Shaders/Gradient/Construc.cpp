// KB  11/15/2002  \Ken100\Plugin\Shaders\Gradient\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "Shader.h"

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
    m_gradient = HGradientProperty::New(theApp.m_gradientinfo);
}

CustomShader::~CustomShader() {
    delete m_gradient;
}
