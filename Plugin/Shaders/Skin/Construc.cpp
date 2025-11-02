// Yves Poissant  11/26/2001  \Dan90\Plugin\Shaders\Lambert\Construc.cpp

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
    m_Falloff = HPercentProperty::New(theApp.m_FalloffInfo);
    m_Roughness = HPercentProperty::New(theApp.m_RoughnessInfo);
    m_ShiftStart = HPercentProperty::New(theApp.m_ShiftStartInfo);
    m_ShiftEnd = HPercentProperty::New(theApp.m_ShiftEndInfo);
    m_Saturation = HPercentProperty::New(theApp.m_SaturationInfo);
    m_HueShift = HPercentProperty::New(theApp.m_HueShiftInfo);
    m_BloodColor = HColorProperty::New(theApp.m_BloodColorInfo);
    m_HueStrength = HPercentProperty::New(theApp.m_HueStrengthInfo);
}

CustomShader::~CustomShader() {
    delete m_Falloff;
    delete m_Roughness;
    delete m_ShiftStart;
    delete m_ShiftEnd;
    delete m_Saturation;
    delete m_HueShift;
    delete m_BloodColor;
    delete m_HueStrength;
}
