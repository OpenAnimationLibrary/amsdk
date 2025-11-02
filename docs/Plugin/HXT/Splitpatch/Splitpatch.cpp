// Splitpatch.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Splitpatch.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitpatchApp

BEGIN_MESSAGE_MAP(CSplitpatchApp, CWinApp)
        //{{AFX_MSG_MAP(CSplitpatchApp)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitpatchApp Konstruktion
CSplitpatchApp::CSplitpatchApp() = default;

CSplitpatchApp::~CSplitpatchApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CSplitpatchApp-Objekt

CSplitpatchApp theApp;

BOOL CSplitpatchApp::OnGroup(HModelCache *hmc, HGroup *hg) {

    para = new Parameter;
    para->insert = GetRegistryValue("SplitPatch HXT", "insert", false);
    para->connect = GetRegistryValue("SplitPatch HXT", "connect", false);

    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }
    SetRegistryValue("SplitPatch HXT", "insert", para->insert);
    SetRegistryValue("SplitPatch HXT", "connect", para->connect);
    return Work(hmc, hg);
}

BOOL CSplitpatchApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CSplitpatchApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
