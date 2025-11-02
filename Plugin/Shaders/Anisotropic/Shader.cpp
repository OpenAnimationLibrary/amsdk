// Dan  3/24/2003  \DanLP105\Plugin\Shaders\Anisotropic\Shader.cpp
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

CShaderApp::CShaderApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName); //debug versions read and write from Master section
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
