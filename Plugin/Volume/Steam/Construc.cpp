// Dan  11/26/2001  \Dan90\Plugin\Volume\Steam\Construc.cpp

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
    m_volfx = (HVolFX *)treeobject;
    if (m_volfx && m_volfx->IsCache()) {
        //Steam is typicaly a cylinder pointing up
        reinterpret_cast<HVolFXCache *>(m_volfx)->GetType()->SetValue(HVolFXCache::CYLINDER);
        constexpr RotateEuler re(-90.F, 0.F, 0.F);
        m_volfx->GetTransform()->GetRotate()->SetValue(Quaternion(re));
    }

    CString string;

    string.LoadString(IDS_SPEED);
    m_speedinfo = HFloatPropertyInfo::New(string, "Speed");
    m_speedinfo->SetDefaultValue(100.F);
    m_speedinfo->SetMinValue(-32000.0F);
    m_speedinfo->SetMaxValue(32000.0F);
    m_speed = HFloatProperty::New(m_speedinfo);

    string.LoadString(IDS_SWIRL);
    m_swirlinfo = HFloatPropertyInfo::New(string, "Swirl");
    m_swirlinfo->SetFactorValue(60.0F); //init used to devide 15 by 60 
    m_swirlinfo->SetDefaultValue(0.25F); //was 15 so 15/60=.25 //user sees the same but 8.5 loads wrong see onNotifyEndProjectLoad
    m_swirlinfo->SetMinValue(-32000.0F);
    m_swirlinfo->SetMaxValue(32000.0F);
    m_swirl = HFloatProperty::New(m_swirlinfo);

    string.LoadString(IDS_SCALE);
    m_scaleinfo = HFloatPropertyInfo::New(string, "Scale");
    m_scaleinfo->SetDefaultValue(50.0F);
    m_scaleinfo->SetMinValue(0.0001F);
    m_scaleinfo->SetMaxValue(32000.0F);
    m_scaleinfo->SetFlags(HFloatPropertyInfo::FF_PERCENTAGE);
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
    m_seconds = time.GetSeconds();
    //COMEBACK
    m_scaledspeed = m_speed->GetValue() * m_seconds / m_scale->GetValue();
}

bool CustomVolumetric::OnNotifyEndProjectLoad(const float productversion) {
    if (productversion < 9.0)
        m_swirl->StoreValue(Time(), m_swirl->GetValue() * 60.0F); //should do each key
    return TRUE;
}
