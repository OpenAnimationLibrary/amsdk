// Simple_Scatter.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Simple_Scatter.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimple_ScatterApp

BEGIN_MESSAGE_MAP(CSimple_ScatterApp, CWinApp)
        //{{AFX_MSG_MAP(CSimple_ScatterApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimple_ScatterApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CSimple_ScatterApp-Objekt

CSimple_ScatterApp theApp;

bool CSimple_ScatterApp::OnChorGroup(HGroup *hgroup) {

    para = new PARAMETER;
    para->isgroup = true;
    para->hgroup = hgroup;
    para->hm_target = (HModel *)hgroup->GetParentOfType(HOT_MODEL);
    para->hmc_target = (HModelCache *)para->hm_target->GetCache();
    GetSettings();

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    if (para->rotate_min.x > para->rotate_max.x) {
        const float temp = para->rotate_max.x;
        para->rotate_max.x = para->rotate_min.x;
        para->rotate_min.x = temp;
    }
    if (para->rotate_min.y > para->rotate_max.y) {
        const float temp = para->rotate_max.y;
        para->rotate_max.y = para->rotate_min.y;
        para->rotate_min.y = temp;
    }
    if (para->rotate_min.z > para->rotate_max.z) {
        const float temp = para->rotate_max.z;
        para->rotate_max.z = para->rotate_min.z;
        para->rotate_min.z = temp;
    }
    if (para->scale_min.x > para->scale_max.x) {
        const float temp = para->scale_max.x;
        para->scale_max.x = para->scale_min.x;
        para->scale_min.x = temp;
    }
    if (para->scale_min.y > para->scale_max.y) {
        const float temp = para->scale_max.y;
        para->scale_max.y = para->scale_min.y;
        para->scale_min.y = temp;
    }
    if (para->scale_min.z > para->scale_max.z) {
        const float temp = para->scale_max.z;
        para->scale_max.z = para->scale_min.z;
        para->scale_min.z = temp;
    }
    if (para->uscale_min > para->uscale_max) {
        const float temp = para->uscale_max;
        para->uscale_max = para->uscale_min;
        para->uscale_min = temp;
    }

    SaveSettings();

    if (ImportandSimulate()) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    delete para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}

bool CSimple_ScatterApp::OnChorModel(HModel *hmodel) {

    para = new PARAMETER;
    para->isgroup = false;
    para->hm_target = hmodel;
    para->hmc_target = (HModelCache *)hmodel->GetCache();
    GetSettings();

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }

    if (para->rotate_min.x > para->rotate_max.x) {
        const float temp = para->rotate_max.x;
        para->rotate_max.x = para->rotate_min.x;
        para->rotate_min.x = temp;
    }
    if (para->rotate_min.y > para->rotate_max.y) {
        const float temp = para->rotate_max.y;
        para->rotate_max.y = para->rotate_min.y;
        para->rotate_min.y = temp;
    }
    if (para->rotate_min.z > para->rotate_max.z) {
        const float temp = para->rotate_max.z;
        para->rotate_max.z = para->rotate_min.z;
        para->rotate_min.z = temp;
    }
    if (para->scale_min.x > para->scale_max.x) {
        const float temp = para->scale_max.x;
        para->scale_max.x = para->scale_min.x;
        para->scale_min.x = temp;
    }
    if (para->scale_min.y > para->scale_max.y) {
        const float temp = para->scale_max.y;
        para->scale_max.y = para->scale_min.y;
        para->scale_min.y = temp;
    }
    if (para->scale_min.z > para->scale_max.z) {
        const float temp = para->scale_max.z;
        para->scale_max.z = para->scale_min.z;
        para->scale_min.z = temp;
    }
    if (para->uscale_min > para->uscale_max) {
        const float temp = para->uscale_max;
        para->uscale_max = para->uscale_min;
        para->uscale_min = temp;
    }
    SaveSettings();
    if (ImportandSimulate()) {
        delete para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    delete para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}

BOOL CSimple_ScatterApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CSimple_ScatterApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
