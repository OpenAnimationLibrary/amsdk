// Dan  3/24/2003  \DanLP105\Plugin\Shaders\Lambert\Shader.cpp
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

CShaderApp::CShaderApp(): m_roughnessinfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    string.LoadString(IDS_ROUGHNESS);
    m_roughnessinfo = HPercentPropertyInfo::New(string, "MiRoughness");
    m_roughnessinfo->SetDefaultValue(GetRegistryValue("Minnaert SHD", "Roughness", 0.5f));

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_roughnessinfo;

    return CPluginApp::ExitInstance();
}
