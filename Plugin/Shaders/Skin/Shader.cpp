// Yves Poissant  2004/01/15  \My Plugin\Shaders\Skin\Shader.cpp
//

#include "StdAfx.h"
#include "Shader.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShaderApp

BEGIN_MESSAGE_MAP(CShaderApp, CWinApp)
    //{{AFX_MSG_MAP(CShaderApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardApp construction

CShaderApp::CShaderApp(): m_FalloffInfo{nullptr}, m_RoughnessInfo{nullptr}, m_ShiftStartInfo{nullptr}, m_ShiftEndInfo{nullptr}, m_SaturationInfo{nullptr}, m_HueShiftInfo{nullptr},
                          m_BloodColorInfo{nullptr}, m_HueStrengthInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString String;

    String.LoadString(IDS_FALLOFF);
    m_FalloffInfo = HPercentPropertyInfo::New(String, "SkinFallOff");
    m_FalloffInfo->SetDefaultValue(1.F);
    m_FalloffInfo->SetMinValue(0.1f);
    m_FalloffInfo->SetMaxValue(5.0f);

    String.LoadString(IDS_ROUGHNESS);
    m_RoughnessInfo = HPercentPropertyInfo::New(String, "SkinRoughness");
    m_RoughnessInfo->SetDefaultValue(0.3f);
    m_RoughnessInfo->SetMinValue(0.F);
    m_RoughnessInfo->SetMaxValue(1.F);

    String.LoadString(IDS_SHIFTSTART);
    m_ShiftStartInfo = HPercentPropertyInfo::New(String, "SkinShift1");
    m_ShiftStartInfo->SetDefaultValue(-0.05f);
    m_ShiftStartInfo->SetMinValue(-2.F);
    m_ShiftStartInfo->SetMaxValue(2.F);

    String.LoadString(IDS_SHIFTEND);
    m_ShiftEndInfo = HPercentPropertyInfo::New(String, "SkinShift2");
    m_ShiftEndInfo->SetDefaultValue(1.3f);
    m_ShiftEndInfo->SetMinValue(-2.F);
    m_ShiftEndInfo->SetMaxValue(2.F);

    String.LoadString(IDS_SATURATION);
    m_SaturationInfo = HPercentPropertyInfo::New(String, "SkinSaturation");
    m_SaturationInfo->SetDefaultValue(0.4f);
    m_SaturationInfo->SetMinValue(0.F);
    m_SaturationInfo->SetMaxValue(1.F);

    String.LoadString(IDS_HUESHIFT);
    m_HueShiftInfo = HPercentPropertyInfo::New(String, "SkinHueShift");
    m_HueShiftInfo->SetDefaultValue(-0.1f);
    m_HueShiftInfo->SetMinValue(-1.F);
    m_HueShiftInfo->SetMaxValue(1.F);

    String.LoadString(IDS_BLOOD);
    m_BloodColorInfo = HColorPropertyInfo::New(String, "BloodColor");
    m_BloodColorInfo->SetDefaultValue(ColorVector(1.F, 0.F, 0.F));

    String.LoadString(IDS_HUESTRENGTH);
    m_HueStrengthInfo = HPercentPropertyInfo::New(String, "SkinHueStrength");
    m_HueStrengthInfo->SetDefaultValue(0.3f);
    m_HueStrengthInfo->SetMinValue(0.F);
    m_HueStrengthInfo->SetMaxValue(1.F);

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_FalloffInfo;
    delete m_RoughnessInfo;
    delete m_ShiftStartInfo;
    delete m_ShiftEndInfo;
    delete m_SaturationInfo;
    delete m_HueShiftInfo;
    delete m_BloodColorInfo;
    delete m_HueStrengthInfo;
    return CPluginApp::ExitInstance();
}

CShaderApp &GetApp() {
    return theApp;
}
