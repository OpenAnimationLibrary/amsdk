// Dan  11/26/2001  \Dan90\Plugin\Shaders\Phong\Construc.cpp

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
    CString string;
    string.LoadString(IDS_SHARPNESS);
    m_sharpnessinfo = HPercentPropertyInfo::New(string, "Sharpness");
    m_sharpnessinfo->SetDefaultValue(.95f);
    m_sharpness = HPercentProperty::New(m_sharpnessinfo);

}

CustomShader::~CustomShader() {
    delete m_sharpness;
    delete m_sharpnessinfo;
}
