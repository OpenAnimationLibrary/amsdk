// E_Rebuild.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "E_Rebuild.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CE_RebuildApp

BEGIN_MESSAGE_MAP(CE_RebuildApp, CWinApp)
        //{{AFX_MSG_MAP(CE_RebuildApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CE_RebuildApp Konstruktion

CE_RebuildApp::CE_RebuildApp() = default;

CE_RebuildApp::~CE_RebuildApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CE_RebuildApp-Objekt

CE_RebuildApp theApp;

BOOL CE_RebuildApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CE_RebuildApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CE_RebuildApp::OnModelCache(HModelCache *hmc) {

    int azpatches;
    HGroupContainer *hgc;

    CWnd *cwnd = CWnd::FromHandle(GetMainApplicationWnd());
    cwnd->UpdateWindow();

    hmc->FindPatches();
    if ((azpatches = hmc->GetPatchCount()) == 0)
        return TRUE;
    if (hmc->GetViewMode() != 0) {
        hmc->OpenView(0);
        GetHProject()->UpdateAllViews(TRUE);
    }
    para = new PParameter;
    LoadSettings();
#ifdef _DEBUG
    para->maxPatches = 10;
    para->groupstrict = TRUE;
    para->scale = .9f;
    para->check_minextrude = FALSE;
    para->minextrude = 1.F;
    para->reverseextrude = FALSE;
    para->near_average = 0.01F; //0.005 Kugelproblem
    para->minscale = 0.1F;
    para->maxscale = 0.9F;
    para->randomscale = FALSE;
    para->hasExplodegroups = FALSE;
#endif
    azpatches = 0;
    if ((hgc = hmc->GetChildGroupContainer())) {
        for (HGroup *hg = hgc->GetChildGroup(); hg; hg = (HGroup *)hg->GetSibling()) {
            String groupname = hg->GetName();
            if (groupname.Find("Exp_") != -1) {
                para->hasExplodegroups = TRUE;
                azpatches++;
            }
        }
    }

    if (azpatches < 2) {
        para->hasExplodegroups = FALSE;
    } else {
        para->hasExplodegroups = TRUE;
    }

    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
#ifndef _DEBUG 
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
#endif
        delete para;
        return TRUE;
    }
#ifndef _DEBUG 
    GetHProject()->UpdateAllViews(TRUE);
#endif
    if (para->hasExplodegroups) {
        if (RebuildModelGroups(hmc)) {
#ifndef _DEBUG 
            GetHProject()->UpdateAllViews(TRUE);
            RefreshAllTrees();
#endif
            SaveSettings();
            delete para;
            return TRUE;
        }
        delete para;
        return TRUE;
    }
    if (RebuildModelVariabel(hmc)) {
#ifndef _DEBUG 
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
#endif
        SaveSettings();
        delete para;
        return TRUE;
    }
    delete para;
    return TRUE;
}

void CE_RebuildApp::SaveSettings() const {
    SetRegistryValue("E_Rebuild HXT", "maxPatch", para->maxPatches);
    SetRegistryValue("E_Rebuild HXT", "groupstrict", para->groupstrict);
    SetRegistryValue("E_Rebuild HXT", "scale", para->scale);
    SetRegistryValue("E_Rebuild HXT", "checkminextrude", para->check_minextrude);
    SetRegistryValue("E_Rebuild HXT", "minextrude", para->minextrude);
    SetRegistryValue("E_Rebuild HXT", "reverseextrude", para->reverseextrude);
    SetRegistryValue("E_Rebuild HXT", "nearaverage", para->near_average); //0.005 Kugelproblem
    SetRegistryValue("E_Rebuild HXT", "minscale", para->minscale);
    SetRegistryValue("E_Rebuild HXT", "maxscale", para->maxscale);
    SetRegistryValue("E_Rebuild HXT", "randomscale", para->randomscale);
    SetRegistryValue("E_Rebuild HXT", "hasexpgroups", para->hasExplodegroups);
}

void CE_RebuildApp::LoadSettings() const {
    para->maxPatches = GetRegistryValue("E_Rebuild HXT", "maxPatch", 10);
    para->groupstrict = GetRegistryValue("E_Rebuild HXT", "groupstrict", TRUE);
    para->scale = GetRegistryValue("E_Rebuild HXT", "scale", .9f);
    para->check_minextrude = GetRegistryValue("E_Rebuild HXT", "checkminextrude", FALSE);
    para->minextrude = GetRegistryValue("E_Rebuild HXT", "minextrude", 1.F);
    para->reverseextrude = GetRegistryValue("E_Rebuild HXT", "reverseextrude", FALSE);
    para->near_average = GetRegistryValue("E_Rebuild HXT", "nearaverage", 0.01F); //0.005 Kugelproblem
    para->minscale = GetRegistryValue("E_Rebuild HXT", "minscale", 0.1F);
    para->maxscale = GetRegistryValue("E_Rebuild HXT", "maxscale", 0.9F);
    para->randomscale = GetRegistryValue("E_Rebuild HXT", "randomscale", FALSE);
    para->hasExplodegroups = GetRegistryValue("E_Rebuild HXT", "hasexpgroups", FALSE);
}
