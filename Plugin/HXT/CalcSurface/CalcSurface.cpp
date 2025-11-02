// CalcSurface.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "CalcSurface.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcSurfaceApp

BEGIN_MESSAGE_MAP(CCalcSurfaceApp, CWinApp)
        //{{AFX_MSG_MAP(CCalcSurfaceApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcSurfaceApp Konstruktion
/////////////////////////////////////////////////////////////////////////////
// Das einzige CCalcSurfaceApp-Objekt

CCalcSurfaceApp theApp;

BOOL CCalcSurfaceApp::OnChor(HChor *hchor) {

    CWaitCursor wait;
    para = new Parameter;
    para->detail.SetSize(0, 100);
    const Time start_time = hchor->GetTime();
    CalculateChor(hchor);
    hchor->SetTime(start_time);
    GetProperty(hchor);
    PDialog pdlg(para);
    if (pdlg.DoModal() == IDOK) {
        if (para->fVSampleArea != para->fVSampleArea_org)
            para->fPSampleArea->StoreValue(Time(), para->fVSampleArea / 100.F, true);
        if (para->iVPhotonCast != para->iVPhotonCast_org)
            para->iPPhotonCast->StoreValue(Time(), para->iVPhotonCast, true);
        if (para->iVPhotonSample != para->iVPhotonSample_org)
            para->iPPhotonSample->StoreValue(Time(), para->iVPhotonSample, true);
        RefreshAllTrees();
        GetHProject()->UpdateAllViews(TRUE);
        para->detail.RemoveAll();
        delete para;
        return true;
    }
    GetHProject()->UpdateAllViews(TRUE);
    para->detail.RemoveAll();
    delete para;
    return true;
}

BOOL CCalcSurfaceApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CCalcSurfaceApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
