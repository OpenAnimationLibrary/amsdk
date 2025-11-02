// MC.cpp : Defines the initialization routines for the DLL.
//

#include "StdAfx.h"
#include "MotionCaptureApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCApp

BEGIN_MESSAGE_MAP(CMCApp, CWinApp)
        //{{AFX_MSG_MAP(CMCApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCApp construction


/////////////////////////////////////////////////////////////////////////////
// The one and only CMCApp object

CMCApp theApp;

BOOL CMCApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");
    return CPluginApp::InitInstance();
}

int CMCApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
