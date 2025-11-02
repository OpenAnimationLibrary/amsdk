// KB  9/26/01  \Ken90\Plugin\Turb\FractalSum\TurbApp.cpp
//

#include "StdAfx.h"
#include "TurbApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurbApp

BEGIN_MESSAGE_MAP(CTurbApp, CWinApp)
        //{{AFX_MSG_MAP(CTurbApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurbApp construction

BOOL CTurbApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    string.LoadString(IDS_OCTAVES);
    m_octavesinfo = HIntPropertyInfo::New(string, "Octaves");
    m_octavesinfo->SetDefaultValue(1);
    m_octavesinfo->SetMinValue(0);
    m_octavesinfo->SetMaxValue(5);
    // Ensure the material preview window will update when this value is changed
    m_octavesinfo->SetDrawWhen(HIntPropertyInfo::DRAWIFMATERIALS);
    return CPluginApp::InitInstance();
}

int CTurbApp::ExitInstance() {
    // Delete Infos Here
    delete m_octavesinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTurbApp object

CTurbApp theApp;
