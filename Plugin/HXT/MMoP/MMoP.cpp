// MMoP.cpp : Definiert die Initialisierungsroutinen für die DLL.
//

#include "StdAfx.h"
#include "MMoP.h"
#include "PDialog.h"
#include<vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMMoPApp

BEGIN_MESSAGE_MAP(CMMoPApp, CWinApp)
END_MESSAGE_MAP()

CMMoPApp::CMMoPApp() = default;

CMMoPApp::~CMMoPApp() = default;

CMMoPApp theApp;

BOOL CMMoPApp::OnPath(HPathModel *hpm) {

    para = new PParameter;
    GetSettings();
    HModelCache *hmc = hpm->GetPathModelCache();
    HSpline *hsp = hmc->GetHeadSpline();
    para->hm_target = nullptr;
    para->chor = hpm->GetChor();
    para->spline_length = hsp->GetLength();

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        para->hproject->UpdateAllViews(true);
        delete para;
        return true;
    }
#ifdef _DEBUG
    fsd.Open("e:\\AM_Debug\\MMoP.txt", FileMode::HS_ASCII);
#endif
    Work(hsp);

    SaveSettings();
#ifdef _DEBUG
    fsd.Close();
#endif
    para->hproject->UpdateAllViews(true);
    RefreshAllTrees();
    delete para;
    return true;
}

struct SplineCont {
    HSpline *hsp = nullptr;
    int az = 1;
};

bool SortAz(const SplineCont &x, const SplineCont &y) {
    return x.az > y.az;
}

BOOL CMMoPApp::OnGroup(HGroup *hg) {

    HGroupCP *hgcp = hg->GetGroupCP();
    if (!hgcp) {
        AfxMessageBox("Check the group.",MB_OK | MB_ICONSTOP);
        GetHProject()->UpdateAllViews(true);
        return true;
    }

    std::vector<SplineCont> splines;

    for (HGroupCP *hgroup = hgcp; hgroup; hgroup = hgroup->GetNext()) {
        SplineCont tempspline;
        HCP *cp = hgroup->GetCP();
        HSpline *hsp = cp->GetSpline();
        tempspline.hsp = hsp;
        BOOL notfound = TRUE;
        for (auto &spline: splines) {
            if (spline.hsp == tempspline.hsp) {
                spline.az++;
                notfound = FALSE;
            }
        }
        if (notfound) {
            splines.push_back(tempspline);
        }
    }
    if (splines.empty()) {
        AfxMessageBox("GroupCP's not assigned to any spline. Make a bugreport",MB_OK | MB_ICONSTOP);
        GetHProject()->UpdateAllViews(true);
        return true;
    }
    std::ranges::sort(splines, SortAz);
    HSpline *hsp = splines[0].hsp;

    para = new PParameter;
    GetSettings();
    //    HSpline *hsp = hgcp->GetCP()->GetSpline();
    para->hm_target = (HModel *)hg->GetParentOfType(HOT_MODEL);
    para->chor = para->hm_target->GetChor();
    para->spline_length = hsp->GetLength();

    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        para->hproject->UpdateAllViews(true);
        delete para;
        return true;
    }
#ifdef _DEBUG
    fsd.Open("e:\\AM_Debug\\MMoP.txt", FileMode::HS_ASCII);
#endif
    Work(hsp);

    SaveSettings();
#ifdef _DEBUG
    fsd.Close();
#endif
    para->chor->OnModified();
    para->hproject->UpdateAllViews(true);
    RefreshAllTrees();
    delete para;
    return true;
}

void CMMoPApp::GetSettings() {
    para->azprop = 0;
    para->azaction = 0;
    para->hproject = GetHProject();
    para->hmc = nullptr;
    para->action_random = false;
    para->distance = GetRegistryValue("MMoP HXT", "distance", 50.F);
    para->offset.x = GetRegistryValue("MMoP HXT", "ofs_x", 0.F);
    para->offset.y = GetRegistryValue("MMoP HXT", "ofs_y", 0.F);
    para->offset.z = GetRegistryValue("MMoP HXT", "ofs_z", 0.F);
    para->store_rotate = GetRegistryValue("MMoP HXT", "store_rotate", TRUE);
    para->random = GetRegistryValue("MMoP HXT", "randomize", 0);
    para->align = GetRegistryValue("MMoP HXT", "align", FALSE);
    para->use_offset = GetRegistryValue("MMoP HXT", "use_offset", FALSE);
    para->max_az = GetRegistryValue("MMoP HXT", "max_az", 50);
    para->allow_overlap = GetRegistryValue("MMoP HXT", "overlap", FALSE);
    for (int i = 0; i < 21; ++i) {
        para->props[i] = nullptr;
        para->hac[i] = nullptr;
    }
    rndnumber = 0;
    rndnumber1 = 0;
}

void CMMoPApp::SaveSettings() const {
    SetRegistryValue("MMoP HXT", "distance", para->distance);
    SetRegistryValue("MMoP HXT", "ofs_x", para->offset.x);
    SetRegistryValue("MMoP HXT", "ofs_y", para->offset.y);
    SetRegistryValue("MMoP HXT", "ofs_z", para->offset.z);
    SetRegistryValue("MMoP HXT", "store_rotate", para->store_rotate);
    SetRegistryValue("MMoP HXT", "randomize", para->random);
    SetRegistryValue("MMoP HXT", "align", para->align);
    SetRegistryValue("MMoP HXT", "max_az", para->max_az);
    SetRegistryValue("MMoP HXT", "use_offset", para->use_offset);
    SetRegistryValue("MMoP HXT", "overlap", para->allow_overlap);
}

BOOL CMMoPApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMMoPApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
