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
    CString string;
    string.LoadString(IDS_GRADIENT);
    m_gradientinfo = HGradientPropertyInfo::New(string, "Gradient"); //LEAK
    m_gradient = HGradientProperty::New(m_gradientinfo);

}

CustomShader::~CustomShader() {
    delete m_gradient;
    delete m_gradientinfo;

}
