// Yves  2005-11-24  \Master13.0\Plugin\Shaders\Velvet\Shader.cpp
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

CShaderApp::CShaderApp(): m_SheenInfo{nullptr}, m_EdginessInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString String;

    String.LoadString(IDS_SHEEN);
    m_SheenInfo = HPercentPropertyInfo::New(String, "Sheen");
    m_SheenInfo->SetDefaultValue(0.25f);
    m_SheenInfo->SetMinValue(0.F);
    m_SheenInfo->SetMaxValue(1.F);

    String.LoadString(IDS_EDGINESS);
    m_EdginessInfo = HFloatPropertyInfo::New(String, "Edginess");
    m_EdginessInfo->SetDefaultValue(10.F);
    m_EdginessInfo->SetMinValue(0.1f);
    m_EdginessInfo->SetMaxValue(100.F);

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_SheenInfo;
    delete m_EdginessInfo;
    return CPluginApp::ExitInstance();
}
