// KB  6/14/01  \Ken90\Plugin\Volume\Dust\VolumeApp.cpp
//

#include "StdAfx.h"
#include "VolumeApp.h"
#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeApp

BEGIN_MESSAGE_MAP(CVolumeApp, CWinApp)
    //{{AFX_MSG_MAP(CVolumeApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeApp construction

CVolumeApp::CVolumeApp() = default;

BOOL CVolumeApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CVolumeApp::ExitInstance() {
    // Delete Infos Here

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVolumeApp object

CVolumeApp theApp;

CVolumeApp &GetApp() {
    return theApp;
}
