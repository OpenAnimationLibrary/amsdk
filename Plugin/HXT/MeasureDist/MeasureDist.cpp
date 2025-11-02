// MeasureDist.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "MeasureDist.h"
#include "SDK/HProject.h"
#include "SDK/HPatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeasureDistApp

BEGIN_MESSAGE_MAP(CMeasureDistApp, CWinApp)
        //{{AFX_MSG_MAP(CMeasureDistApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureDistApp Konstruktion
CMeasureDistApp::CMeasureDistApp() = default;

CMeasureDistApp::~CMeasureDistApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMeasureDistApp-Objekt

CMeasureDistApp theApp;

BOOL CMeasureDistApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMeasureDistApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

float Distance(const Vector v) {
    return v.Norm();
}

float Distance(const Vector v1, const Vector v2) {
    return Distance(v2 - v1);
}

BOOL CMeasureDistApp::OnCP(HCP *cp) const {
    if (!cp->IsCache())
        cp = (HCP *)cp->GetCache();
    HSpline *hsp = cp->GetSpline();
    HCP *last = nullptr;
    for (HCP *cp1 = hsp->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
        last = cp1;
        if (cp1->IsLoop())
            break;
    }
    const float length = hsp->GetHeadCP()->GetDistance(last);
    const String slength = UnitToString(length, GetMeasurementUnits());
    CString msg;
    msg.Format("Length %s", slength.Get());
    AfxMessageBox(msg, MB_OK | MB_ICONINFORMATION);
    return TRUE;
}

BOOL CMeasureDistApp::OnGroup(HGroup *hg) const {
    HCP *hcp1 = hg->GetGroupCP()->GetCP();
    const HSpline *hsp = hcp1->GetSpline();
    HCP *hcp2 = nullptr;
    for (HGroupCP *groupcp = hg->GetGroupCP(); groupcp; groupcp = groupcp->GetNext()) {
        if (HCP *t_cp = groupcp->GetCP(); t_cp != hcp1) {
            if (t_cp->GetSpline() == hsp) {
                hcp2 = t_cp;
            }
        }
    }

    if (hcp1 == nullptr || hcp2 == nullptr || hcp1->GetSpline() != hcp2->GetSpline()) {
        AfxMessageBox("Select at minimum 2 CP's on the same spline", MB_OK | MB_ICONERROR);
        GetHProject()->UpdateAllViews(true);
        return TRUE;
    }
    const Vector pos1 = *hcp1->GetHead()->GetModelPosition();
    const Vector pos2 = *hcp2->GetHead()->GetModelPosition();
    const double distance = Distance(pos1, pos2);
    const float length = hcp2->GetDistance(hcp1);
    const int unit = GetMeasurementUnits();
    const String slength = UnitToString(length, unit);
    const String sdistance = UnitToString((float)distance, unit);
    CString temp;
    temp.Format("Distance between CP #%i and CP #%i\nDirect distance is %s\nSpline distance is %s", hcp1->GetID(), hcp2->GetID(), sdistance.Get(), slength.Get());
    AfxMessageBox(temp, MB_OK | MB_ICONINFORMATION);

    return TRUE;
}
