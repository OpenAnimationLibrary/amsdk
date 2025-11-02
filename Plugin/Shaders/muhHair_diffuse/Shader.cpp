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

CShaderApp::CShaderApp(): m_diffStrengthInfo{nullptr}, m_diffBlendInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    string.LoadString(IDS_DIFFSTR);
    m_diffStrengthInfo = HPercentPropertyInfo::New(string, "DiffuseStrength");
    m_diffStrengthInfo->SetDefaultValue(GetRegistryValue("MUHHAIR_DIFF SHD", "DiffuseStrength", 1.F));
    m_diffStrengthInfo->SetMinValue(0.F);
    m_diffStrengthInfo->SetMaxValue(1.F);

    string.LoadString(IDS_DIFFBLEND);
    m_diffBlendInfo = HPercentPropertyInfo::New(string, "DiffuseBlend");
    m_diffBlendInfo->SetDefaultValue(GetRegistryValue("MUHHAIR_DIFF SHD", "DiffuseBlend", 0.1f));
    m_diffBlendInfo->SetMinValue(0.F);
    m_diffBlendInfo->SetMaxValue(1.F);

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_diffStrengthInfo;
    delete m_diffBlendInfo;

    return CPluginApp::ExitInstance();
}
