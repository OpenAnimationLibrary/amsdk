// Smooth.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Smooth.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmoothApp

BEGIN_MESSAGE_MAP(CSmoothApp, CWinApp)
    //{{AFX_MSG_MAP(CSmoothApp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmoothApp Konstruktion

CSmoothApp::CSmoothApp() = default;

CSmoothApp::~CSmoothApp() = default;
/////////////////////////////////////////////////////////////////////////////
// Das einzige CSmoothApp-Objekt

CSmoothApp theApp;

BOOL CSmoothApp::OnGroup(HModelCache *hmc, HGroup *hg) {

    Init(hmc, hg);
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }

    if (!Work(hmc, hg)) {
        delete para;
        return TRUE;
    }

    delete para;
    //   GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews();
    RefreshAllTrees();
    return TRUE;
}

BOOL CSmoothApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CSmoothApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
