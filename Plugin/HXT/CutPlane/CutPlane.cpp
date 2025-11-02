// CutPlane.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "CutPlane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCutPlaneApp

BEGIN_MESSAGE_MAP(CCutPlaneApp, CWinApp)
        //{{AFX_MSG_MAP(CCutPlaneApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCutPlaneApp Konstruktion

CCutPlaneApp::CCutPlaneApp() {
    mdlg = nullptr;
}

CCutPlaneApp::~CCutPlaneApp() {
    if (plane.hg && hmc) {
        hmc->DeleteSpline(plane.sp1);
        hmc->DeleteSpline(plane.sp2);
        delete plane.hg;
        plane.hg = nullptr;
    }
    if (mdlg) {
        if (mdlg->m_hWnd) {
            mdlg->DestroyWindow();
        }
        hmc = nullptr;
        MDialog::Cleanup();
    }
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CCutPlaneApp-Objekt

CCutPlaneApp theApp;

void CCutPlaneApp::OnSelectionChanged(const bool check) const {
    if (mdlg)
        mdlg->EnableControls(check);
}

BOOL CCutPlaneApp::OnStart(HModelCache *_hmc) {

    if (mdlg) {
        return true;
    }

    plane.hg = nullptr;
    plane.max_value = 0.F;
    plane.addring = true;
    plane.break_splines = false;
    plane.cut_splines = false;
    plane.infinite = false;
    plane.offset = 0.F;
    hmc = _hmc;

#ifdef _DEBUG
    //	plane.cut_splines = true;
    //	plane.offset = 100.F;
    fsd.Open("e:\\cutp.txt", FileMode::HS_ASCII);
    fsd << hmc->GetName() << nl;
#endif

    UpdateSplineList();
#ifdef _DEBUG
    //	DebugOut();
#endif
    CWnd *hwnd = CWnd::FromHandle(GetMainApplicationWnd());
    mdlg = new MDialog();
    mdlg->Create(IDD_DIALOG1, CWnd::FromHandle(GetMainApplicationWnd()));
    mdlg->ShowWindow(SW_SHOWNORMAL);
    hwnd->SetFocus();
    AFX_MANAGE_STATE(AfxGetAppModuleState()) //crash in V16
    CreatePlane();

    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return true;
}

BOOL CCutPlaneApp::InitInstance() {
    return CPluginApp::InitInstance();
}

int CCutPlaneApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
