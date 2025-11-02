// GrowSelection.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "GrowSelection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrowSelectionApp

BEGIN_MESSAGE_MAP(CGrowSelectionApp, CWinApp)
        //{{AFX_MSG_MAP(CGrowSelectionApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrowSelectionApp Konstruktion
CGrowSelectionApp::CGrowSelectionApp() = default;

CGrowSelectionApp::~CGrowSelectionApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CGrowSelectionApp-Objekt

CGrowSelectionApp theApp;

BOOL CGrowSelectionApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CGrowSelectionApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CGrowSelectionApp::OnWork(HGroup *hg) {

    CWaitCursor wait;
    auto *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
    if (!hmc)
        return true;
    hmc->FindPatches();
    if (hmc->GetPatchCount() == 0) {
        AfxMessageBox("No patches found in this model",MB_OK | MB_ICONINFORMATION);
        return true;
    }
    HBone *hb = hmc->GetCurrentBone();
    screen = hb->GetScreenToModelMatrix();
    return Work(hg, hmc);
}
