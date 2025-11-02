// CloneWeight.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "CloneWeight.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloneWeightApp

BEGIN_MESSAGE_MAP(CCloneWeightApp, CWinApp)
        //{{AFX_MSG_MAP(CCloneWeightApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloneWeightApp Konstruktion

CCloneWeightApp::CCloneWeightApp() = default;

CCloneWeightApp::~CCloneWeightApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CCloneWeightApp-Objekt

CCloneWeightApp theApp;

BOOL CCloneWeightApp::OnModel(HModelCache *hmc) {
    para = new Parameter;
    para->hmc = hmc;
    para->max_dist = 0.01F;
    para->reassigncp = TRUE;

    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete para;
        return TRUE;
    }
    if (!para->hmc) {
        AfxMessageBox("Destination model needed",MB_ICONERROR);
        delete para;
        return TRUE;
    }
    para->hmc->Update();
    para->hmc->SaveAllToUndo();
    if (!Worker(hmc, para->hmc)) {
        AfxMessageBox("Error occured\nCheck the used models",MB_ICONERROR);
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    delete para;
    return TRUE;
}

BOOL CCloneWeightApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CCloneWeightApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
