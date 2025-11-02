// \Plugin\Shaders\Brushed\Construc.cpp

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
    CString string;

    string.LoadString(IDS_GRAIN);
    m_graininfo = HVectorPropertyInfo::New(string, "Grain");
    m_graininfo->GetX()->SetDefaultValue(GetRegistryValue("Brushed SHD", "GrainX", 1.F));
    m_graininfo->GetX()->SetMinValue(0.F);
    m_graininfo->GetX()->SetMaxValue(100.F);
    m_graininfo->GetX()->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
    m_graininfo->GetY()->SetDefaultValue(GetRegistryValue("Brushed SHD", "GrainY", 0.F));
    m_graininfo->GetY()->SetMinValue(0.F);
    m_graininfo->GetY()->SetMaxValue(100.F);
    m_graininfo->GetX()->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
    m_graininfo->GetZ()->SetDefaultValue(GetRegistryValue("Brushed SHD", "GrainZ", 0.F));
    m_graininfo->GetZ()->SetMinValue(0.F);
    m_graininfo->GetZ()->SetMaxValue(100.F);
    m_graininfo->GetX()->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
    m_grain = HVectorProperty::New(m_graininfo);

    m_normgrain = m_grain->GetValue();
    m_normgrain.Normalize();
}

CustomShader::~CustomShader() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    SetRegistryValue("Brushed SHD", "GrainX", m_grain->GetX()->GetValue());
    SetRegistryValue("Brushed SHD", "GrainY", m_grain->GetY()->GetValue());
    SetRegistryValue("Brushed SHD", "GrainZ", m_grain->GetZ()->GetValue());

    delete m_grain;

    delete m_graininfo;
}
