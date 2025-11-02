// Dan  11/26/2001  \Dan90\Plugin\Volume\Mist\Construc.cpp

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

    string.LoadString(IDS_SWIRL);
    m_valinfo = HFloatPropertyInfo::New(string, "Swirl");
    m_valinfo->SetDefaultValue(1.F);
    m_valinfo->SetMinValue(-32000.0F);
    m_valinfo->SetMaxValue(32000.0F);
    m_val = HFloatProperty::New(m_valinfo);

    string.LoadString(IDS_SPEED);
    m_heightinfo = HFloatPropertyInfo::New(string, "Height");
    m_heightinfo->SetDefaultValue(15.0F);
    m_heightinfo->SetMinValue(-32000.0F);
    m_heightinfo->SetMaxValue(32000.0F);
    m_height = HFloatProperty::New(m_heightinfo);

    string.LoadString(IDS_SCALE);
    m_scaleinfo = HFloatPropertyInfo::New(string, "Scale");
    m_scaleinfo->SetDefaultValue(50.0F);
    m_scaleinfo->SetMinValue(0.0001F);
    m_scaleinfo->SetMaxValue(32000.0F);
    m_scale = HFloatProperty::New(m_scaleinfo);
}

CustomVolumetric::~CustomVolumetric() {
    delete m_val;
    delete m_height;
    delete m_scale;
    delete m_valinfo;
    delete m_heightinfo;
    delete m_scaleinfo;
}

void CustomVolumetric::Init(Time time) {
    m_oval = m_val->GetValue();
}
