// RMWeight.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "RMWeight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRMWeightApp

BEGIN_MESSAGE_MAP(CRMWeightApp, CWinApp)
        //{{AFX_MSG_RMWeight(CRMWeightApp)
        // HINWEIS - Hier werden RMWeightping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_RMWeight
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMWeightApp Konstruktion

CRMWeightApp::CRMWeightApp() = default;

CRMWeightApp::~CRMWeightApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CRMWeightApp-Objekt

CRMWeightApp theApp;

int CRMWeightApp::CheckWeight(HCP *cp) {
    HSegmentCache *hsc1;
    HSegmentCache *hsc = cp->GetSegmentCache();
    if (!hsc)
        return 0; //cp not assigned, cannot have cpweights
    int az_removes = 0;
#ifdef _DEBUG
    fs << nl;
    fs << "CP ID " << cp->GetID() << nl;
    fs << hsc->GetName() << nl;
#endif
    CArray<HCPWeight *, HCPWeight *> toremove;

    for (HCPWeight *cpweight = cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
        hsc1 = cpweight->GetSegmentCache();
#ifdef _DEBUG
        fs << hsc1->GetName();
#endif
        if (hsc == hsc1 || 0 == cpweight->GetWeight()) {
#ifdef _DEBUG
            fs << " deleted";
#endif
            toremove.Add(cpweight);
            az_removes++;
        }
#ifdef _DEBUG
        fs << nl;
#endif
    }
    for (int i = 0; i < toremove.GetSize(); ++i) {
        cp->RemoveCPWeight(toremove[i]);
    }
    return az_removes;
}

BOOL CRMWeightApp::OnModel(HModelCache *hmc) {
    int az_error = 0;
#ifdef _DEBUG
    fs.Open("E://weight.txt", FileMode::HS_ASCII);
#endif
    for (HSpline *spline = hmc->GetHeadSpline(); spline; spline = spline->GetNextSpline()) {
        for (HCP *cp = spline->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (cp == cp->GetHead())
                az_error += CheckWeight(cp);
            if (cp->IsLoop())
                break;
        }
    }
#ifdef _DEBUG
    fs.Close();
#endif

    if (az_error > 0) {
        hmc->SetChanged(true);
        CString temp;
        temp.Format("%d weight errors corrected.", az_error);
        AfxMessageBox(temp,MB_OK);
    }

    return true;
}

BOOL CRMWeightApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CRMWeightApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
