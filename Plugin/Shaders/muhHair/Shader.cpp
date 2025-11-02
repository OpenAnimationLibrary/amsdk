// 
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

CShaderApp::CShaderApp(): m_primWidthInfo{nullptr}, m_scndryWidthInfo{nullptr}, m_transWidthInfo{nullptr}, m_primDevInfo{nullptr}, m_scndryDevInfo{nullptr}, m_transDevInfo{nullptr},
                          m_primStrengthInfo{nullptr}, m_scndryStrengthInfo{nullptr}, m_transStrengthInfo{nullptr}, m_fresInfo{nullptr}, m_directionAttenInfo{nullptr}, m_specBlendInfo{nullptr},
                          m_iorInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    string.LoadString(IDS_PRIMARYWIDTH);
    m_primWidthInfo = HPercentPropertyInfo::New(string, "PrimaryWidth");
    m_primWidthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "PrimaryWidth", 0.5f));
    m_primWidthInfo->SetMinValue(0.F);
    m_primWidthInfo->SetMaxValue(1.F);

    string.LoadString(IDS_SECONDARYWIDTH);
    m_scndryWidthInfo = HPercentPropertyInfo::New(string, "SecondaryWidth");
    m_scndryWidthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "SecondaryWidth", 0.5f));
    m_scndryWidthInfo->SetMinValue(0.F);
    m_scndryWidthInfo->SetMaxValue(1.F);

    string.LoadString(IDS_TRANSLUCENTWIDTH);
    m_transWidthInfo = HPercentPropertyInfo::New(string, "TranslucentWidth");
    m_transWidthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "TranslucentWidth", 0.5f));
    m_transWidthInfo->SetMinValue(0.F);
    m_transWidthInfo->SetMaxValue(1.F);

    string.LoadString(IDS_PRIMARYDEV);
    m_primDevInfo = HPercentPropertyInfo::New(string, "PrimaryDeviation");
    m_primDevInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "PrimaryDeviation", 0.1f));
    m_primDevInfo->SetMinValue(-1.F);
    m_primDevInfo->SetMaxValue(1.F);

    string.LoadString(IDS_SECONDARYDEV);
    m_scndryDevInfo = HPercentPropertyInfo::New(string, "SecondaryDeviation");
    m_scndryDevInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "SecondaryDeviation", -0.15f));
    m_scndryDevInfo->SetMinValue(-1.F);
    m_scndryDevInfo->SetMaxValue(1.F);

    string.LoadString(IDS_TRANSLUCENTDEV);
    m_transDevInfo = HPercentPropertyInfo::New(string, "TranslucentDeviation");
    m_transDevInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "TranslucentDeviation", -0.1f));
    m_transDevInfo->SetMinValue(-1.F);
    m_transDevInfo->SetMaxValue(1.F);

    string.LoadString(IDS_PRIMARYSTR);
    m_primStrengthInfo = HPercentPropertyInfo::New(string, "PrimaryStrength");
    m_primStrengthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "PrimaryStrength", 1.F));
    m_primStrengthInfo->SetMinValue(0.F);
    m_primStrengthInfo->SetMaxValue(10.F);

    string.LoadString(IDS_SECONDARYSTR);
    m_scndryStrengthInfo = HPercentPropertyInfo::New(string, "SecondaryStrength");
    m_scndryStrengthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "SecondaryStrength", 1.F));
    m_scndryStrengthInfo->SetMinValue(0.F);
    m_scndryStrengthInfo->SetMaxValue(10.F);

    string.LoadString(IDS_TRANSLUCENTSTR);
    m_transStrengthInfo = HPercentPropertyInfo::New(string, "TranslucentStrength");
    m_transStrengthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "TranslucentStrength", 1.F));
    m_transStrengthInfo->SetMinValue(0.F);
    m_transStrengthInfo->SetMaxValue(10.F);

    string.LoadString(IDS_FRESAMT);
    m_fresInfo = HPercentPropertyInfo::New(string, "FresnelAmount");
    m_fresInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "FresnelAmount", 0.2f));
    m_fresInfo->SetMinValue(0.F);
    m_fresInfo->SetMaxValue(1.F);

    string.LoadString(IDS_IOR);
    m_iorInfo = HFloatPropertyInfo::New(string, "HairIndexofRefraction");
    m_iorInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "IOR", 1.5f));
    m_iorInfo->SetMinValue(1.F);
    m_iorInfo->SetMaxValue(2.F);

    string.LoadString(IDS_DIRATTEN);
    m_directionAttenInfo = HPercentPropertyInfo::New(string, "DirectionAttenuation");
    m_directionAttenInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "DirectionAttenuation", 0.5f));
    m_directionAttenInfo->SetMinValue(0.F);
    m_directionAttenInfo->SetMaxValue(1.F);

    string.LoadString(IDS_SPECBLEND);
    m_specBlendInfo = HPercentPropertyInfo::New(string, "SpecularBlend");
    m_specBlendInfo->SetDefaultValue(GetRegistryValue("MUHHAIR SHD", "SpecularBlend", 0.1f));
    m_specBlendInfo->SetMinValue(0.F);
    m_specBlendInfo->SetMaxValue(1.F);

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_primWidthInfo;
    delete m_scndryWidthInfo;
    delete m_transWidthInfo;

    delete m_primDevInfo;
    delete m_scndryDevInfo;
    delete m_transDevInfo;

    delete m_primStrengthInfo;
    delete m_scndryStrengthInfo;
    delete m_transStrengthInfo;

    delete m_fresInfo;
    delete m_iorInfo;

    delete m_directionAttenInfo;

    delete m_specBlendInfo;

    return CPluginApp::ExitInstance();
}
