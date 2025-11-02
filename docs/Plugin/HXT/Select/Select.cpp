// Select.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Select.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectApp

BEGIN_MESSAGE_MAP(CSelectApp, CWinApp)
        //{{AFX_MSG_MAP(CSelectApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectApp Konstruktion
CSelectApp::CSelectApp() = default;

CSelectApp::~CSelectApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CSelectApp-Objekt

CSelectApp theApp;

BOOL CSelectApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CSelectApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CSelectApp::OnWork(HModelCache *hmc) {

    CWnd *cwnd = CWnd::FromHandle(GetMainApplicationWnd());
    cwnd->UpdateWindow();

    CWaitCursor wait;
    if (hmc->GetPatchCount() == 0) {
        hmc->FindPatches();
        if (hmc->GetPatchCount() == 0) {
            AfxMessageBox("No patches found in this model", MB_OK | MB_ICONINFORMATION);
            return TRUE;
        }
    }

    HBone *hb = hmc->GetCurrentBone();
    screen = hb->GetScreenToModelMatrix();

    para = new Parameter;
    LoadSettings();
    /*
       para->number = 0;
       para->pid1 = 0;
       para->pid2 = 0;
       para->pid3 = 0;
       para->pid4 = 0;
       para->pid5 = 0;
       para->type = 0;
       para->view = 0;
       para->tolerance = 0.9f;
       para->cp_mode = 0;
    */
    CPDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return TRUE;
    }

    return Work(hmc);
}
