// Yves 10/12/2006  \Plugin\Shaders\PharrSkin\Construc.cpp

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
    m_ior = HFloatProperty::New(theApp.m_iorinfo);
    m_thickness = HFloatProperty::New(theApp.m_thicknessinfo);
}

CustomShader::~CustomShader() {
    delete m_ior;
    delete m_thickness;
}
