// Dan  4/15/2002  \Dan95\Plugin\Shaders\Anisotropic\Construc.cpp

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
    string.LoadString(IDS_ROUGHNESSX);
    m_roughnessxinfo = HPercentPropertyInfo::New(string, "Roughness X");
    m_roughnessxinfo->SetDefaultValue(GetRegistryValue("Anisotropic SHD", "RoughX", 0.15f));
    m_roughnessxinfo->SetMinValue(0.F);
    m_roughnessxinfo->SetMaxValue(100.F);
    m_roughnessx = HPercentProperty::New(m_roughnessxinfo);

    string.LoadString(IDS_ROUGHNESSY);
    m_roughnessyinfo = HPercentPropertyInfo::New(string, "Roughness Y");
    m_roughnessyinfo->SetDefaultValue(GetRegistryValue("Anisotropic SHD", "RoughX", 0.5f));
    m_roughnessyinfo->SetMinValue(0.F);
    m_roughnessyinfo->SetMaxValue(100.F);
    m_roughnessy = HPercentProperty::New(m_roughnessyinfo);

    string.LoadString(IDS_GRAIN);
    m_graininfo = HVectorPropertyInfo::New(string, "Grain");
    m_graininfo->GetX()->SetDefaultValue(GetRegistryValue("Anisotropic SHD", "GrainX", 1.F));
    m_graininfo->GetX()->SetMinValue(0.F);
    m_graininfo->GetX()->SetMaxValue(100.F);
    m_graininfo->GetX()->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
    m_graininfo->GetY()->SetDefaultValue(GetRegistryValue("Anisotropic SHD", "GrainY", 0.F));
    m_graininfo->GetY()->SetMinValue(0.F);
    m_graininfo->GetY()->SetMaxValue(100.F);
    m_graininfo->GetX()->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
    m_graininfo->GetZ()->SetDefaultValue(GetRegistryValue("Anisotropic SHD", "GrainZ", 0.F));
    m_graininfo->GetZ()->SetMinValue(0.F);
    m_graininfo->GetZ()->SetMaxValue(100.F);
    m_graininfo->GetX()->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
    m_grain = HVectorProperty::New(m_graininfo);

    m_normgrain = m_grain->GetValue();
    m_normgrain.Normalize();
}

CustomShader::~CustomShader() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    SetRegistryValue("Anisotropic SHD", "GrainX", m_grain->GetX()->GetValue());
    SetRegistryValue("Anisotropic SHD", "GrainY", m_grain->GetY()->GetValue());
    SetRegistryValue("Anisotropic SHD", "GrainZ", m_grain->GetZ()->GetValue());
    SetRegistryValue("Anisotropic SHD", "RoughX", m_roughnessx->GetValue());
    SetRegistryValue("Anisotropic SHD", "RoughY", m_roughnessy->GetValue());

    delete m_roughnessx;
    delete m_roughnessy;
    delete m_grain;

    delete m_roughnessxinfo;
    delete m_roughnessyinfo;
    delete m_graininfo;
}
