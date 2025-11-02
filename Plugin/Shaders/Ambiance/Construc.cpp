// KB  8/28/2003  \Ken110\Plugin\Shaders\Ambiance\Construc.cpp

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
    m_ambiancecolor = HColorProperty::New(theApp.m_ambiancecolorinfo);
}

CustomShader::~CustomShader() {
    delete m_ambiancecolor;
}
