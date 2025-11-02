// Yves Poissant 09-2003 \Extended Noise\TurbApp.cpp
//

#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurbApp

BEGIN_MESSAGE_MAP(CTurbApp, CWinApp)
    //{{AFX_MSG_MAP(CTurbApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CTurbApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
#ifndef _DEBUG
    free((void *)m_pszProfileName);
#endif
    m_pszProfileName = _tcsdup("AM Plugins");

    m_NoiserUI.InitProperties();
    m_TransfererUI.InitProperties();
    m_SamplerUI.InitProperties();

    return CPluginApp::InitInstance();
}

int CTurbApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CTurbApp construction

/////////////////////////////////////////////////////////////////////////////
// The one and only CTurbApp object

CTurbApp theApp;

CTurbApp &GetApp() {
    return theApp;
}
