// Dan  11/26/2001  \Dan90\Plugin\Volume\Dust\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"

extern "C" __declspec(dllexport) Volumetric *CreateVolumetric(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomVolumetric(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return VOLUMETRICDLLVERSION;
}

CustomVolumetric::CustomVolumetric(HTreeObject *treeobject) : Volumetric(treeobject) {
    CString string;
    // New Infos here
    string.LoadString(IDS_SPEED);
    m_speedinfo = HFloatPropertyInfo::New(string, "Speed");
    m_speedinfo->SetDefaultValue(100.F);
    m_speedinfo->SetMinValue(-32000.0F);
    m_speedinfo->SetMaxValue(32000.0F);

    string.LoadString(IDS_SWIRL);
    m_swirlinfo = HFloatPropertyInfo::New(string, "Swirl");
    m_swirlinfo->SetDefaultValue(15.0F);
    m_swirlinfo->SetMinValue(-32000.0F);
    m_swirlinfo->SetMaxValue(32000.0F);

    string.LoadString(IDS_SCALE);
    m_scaleinfo = HFloatPropertyInfo::New(string, "Scale");
    m_scaleinfo->SetDefaultValue(50.0F);
    m_scaleinfo->SetMinValue(0.0001F);
    m_scaleinfo->SetMaxValue(32000.0F);

    m_speed = HFloatProperty::New(m_speedinfo);
    m_swirl = HFloatProperty::New(m_swirlinfo);
    m_scale = HFloatProperty::New(m_scaleinfo);
}

CustomVolumetric::~CustomVolumetric() {
    delete m_speed;
    delete m_swirl;
    delete m_scale;
    delete m_speedinfo;
    delete m_swirlinfo;
    delete m_scaleinfo;
}

void CustomVolumetric::Init(const Time time) {
    const float cycle = m_swirl->GetValue() / 60.0F;
    m_depth = m_speed->GetValue() * time.GetSeconds() / m_scale->GetValue();
    const float theta = cycle * time.GetSeconds() * hash_constants::pi_2;
    m_costheta = hash_math::cos(theta);
    m_sintheta = hash_math::sin(theta);
}
