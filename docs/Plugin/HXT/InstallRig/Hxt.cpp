// KB  11/17/05  Plugin\HXT\InstallRig\Hxt.cpp
//

#include "StdAfx.h"
#include "Hxt.h"
//#include "MirrorBonesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHxtApp

BEGIN_MESSAGE_MAP(CHxtApp, CWinApp)
    //{{AFX_MSG_MAP(CWizardApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHxtApp construction

CHxtApp::CHxtApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CWizardApp object

CHxtApp theApp;

BOOL CHxtApp::OnInstallRig(HTreeObject *htreeobject) {
    /*MirrorBonesDialog dlg;

    int command = dlg.DoModal();

    if (command==IDCANCEL)
        return TRUE;

    if (dlg.m_adjustright)
        m_adjustright = true;
    else
        m_adjustright = false;
    
    if (dlg.m_assignvertices)
        m_assignvertices = true;
    else
        m_assignvertices = false;

    if (dlg.m_createbones)
        m_createbones = true;
    else
        m_createbones = false;

    m_tolerance = dlg.m_tolerance;
   */
    if (!Evaluate(htreeobject))
        return TRUE;

    return TRUE;
}

BOOL CHxtApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CHxtApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
