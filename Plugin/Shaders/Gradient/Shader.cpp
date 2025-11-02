// KB  2/4/2003  \Ken105\Plugin\Shaders\Gradient\Shader.cpp
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

CShaderApp::CShaderApp(): m_gradientinfo{nullptr} {}

CShaderApp::~CShaderApp() = default;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    string.LoadString(IDS_GRADIENT);
    m_gradientinfo = HGradientPropertyInfo::New(string, "Gradient"); //LEAK

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_gradientinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

CShaderApp &GetApp() {
    return theApp;
}
