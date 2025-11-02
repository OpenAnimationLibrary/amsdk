// Dan  3/24/2003  \DanLP105\Plugin\HXT\3DS\Hxt.cpp
//

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
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_isbuildattrarray = TRUE;
    m_iemp.m_isbuildbonelist = FALSE;
    m_attrextlist.SetSize(0, 10);
    m_hashtable.InitHashTable(67);
    m_masterscale = 1.F / 2.54F;
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
