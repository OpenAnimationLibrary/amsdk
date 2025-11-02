// MirrorConstraint.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "MirrorConstraint.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMirrorConstraintApp

BEGIN_MESSAGE_MAP(CMirrorConstraintApp, CWinApp)
    //{{AFX_MSG_MirrorConstraint(CMirrorConstraintApp)
    // HINWEIS - Hier werden MirrorConstraintping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MirrorConstraint
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

CMirrorConstraintApp theApp;

BOOL CMirrorConstraintApp::OnModel(HModelCache *hmc) {
    para = new MC_PARAMETER;
    para->hmc = hmc;
    GetSettings();

//    para->search = "right";
//    para->replace = "left";

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }
    SaveSettings();

    CWaitCursor wait;
    if (Work()) {
        para->hmc->SetChanged(TRUE);
        para->hmc->RefreshInProjectBar(TRUE);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete para;
        return TRUE;
    }
    delete para;
    GetHProject()->UpdateAllViews(TRUE);
    return TRUE;
}

BOOL CMirrorConstraintApp::OnAction(HActionCache *hac) {
    para = new MC_PARAMETER;
    para->hmc = hac->GetDefaultModelCache();
    if (!para->hmc) {
        delete para;
        return TRUE;
    }
    GetSettings();
//        para->search = "left";
//        para->replace = "right";
//    para->search = "right";
//    para->replace = "left";

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }
    SaveSettings();

    CWaitCursor wait;
    if (WorkAction(hac)) {
        para->hmc->SetChanged(TRUE);
        para->hmc->RefreshInProjectBar(TRUE);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete para;
        return TRUE;
    }
    delete para;
    GetHProject()->UpdateAllViews(TRUE);
    return TRUE;
}

BOOL CMirrorConstraintApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMirrorConstraintApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

void CMirrorConstraintApp::GetSettings() const {
    para->search = GetRegistryString("MirrorConstraint HXT", "search", "right");
    para->replace = GetRegistryString("MirrorConstraint HXT", "replace", "left");
}

void CMirrorConstraintApp::SaveSettings() const {
    SetRegistryString("MirrorConstraint HXT", "search", para->search);
    SetRegistryString("MirrorConstraint HXT", "replace", para->replace);
}
