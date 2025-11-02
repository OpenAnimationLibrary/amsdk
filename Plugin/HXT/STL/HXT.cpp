#include "StdAfx.h"
#include "Hxt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHxtApp

BEGIN_MESSAGE_MAP(CHxtApp, CWinApp)
    //{{AFX_MSG_MAP(CHxtApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHxtApp construction

CHxtApp::CHxtApp() {
    m_iemp.m_isbuildmaparray = FALSE;
    m_iemp.m_isbuildattrarray = FALSE;
    m_iemp.m_isbuildbonelist = FALSE;
    m_hprogressbar = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHxtApp object

CHxtApp theApp;

BOOL CHxtApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CHxtApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
