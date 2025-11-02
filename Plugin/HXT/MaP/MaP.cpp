// MaP.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "MaP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaPApp

BEGIN_MESSAGE_MAP(CMaPApp, CWinApp)
        //{{AFX_MSG_MAP(CMaPApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaPApp Konstruktion

CMaPApp::CMaPApp() = default;

CMaPApp::~CMaPApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMaPApp-Objekt

CMaPApp theApp;

String RemoveNumber(const String &name) {
    String test = name.GetWithoutDigits();
    return test;
}

void CMaPApp::RemoveEmptyGroups(CArray<HGroup *, HGroup *> &grouplist) {
    for (int i = 0; i < grouplist.GetSize(); ++i) {
        const HGroupCP *hgcp = grouplist[i]->GetGroupCP();
        if (hgcp == nullptr)
            delete grouplist[i];
    }
}

BOOL CMaPApp::FindMatch(HGroup *fgroup, CArray<HGroup *, HGroup *> &grouplist) {

    int i;
    CArray<HGroup *, HGroup *> worklist;
    CArray<HCP *, HCP *> cplist;
    HGroupCP *hgcp;
    Vector pivot, min, max;

    max.Set(-hash_constants::max_float);
    min.Set(hash_constants::max_float);
    pivot.Set(0.F);
    const String temp = fgroup->GetName();
    for (i = 0; i < grouplist.GetSize(); ++i) {
        String temp1 = grouplist[i]->GetName();
        String temp2 = RemoveNumber(temp1);
        if (temp2 == temp && temp1 != temp) {
            worklist.Add(grouplist[i]);
        }
    }
    if (worklist.GetSize() == 0)
        return false;
    for (i = 0; i < worklist.GetSize(); ++i) {
        for (hgcp = worklist[i]->GetGroupCP(); hgcp; hgcp = hgcp->GetNext()) {
            HCP *cp = hgcp->GetCP();
            fgroup->AddCP(cp);
            cplist.Add(cp);
        }
        for (int j = 0; j < cplist.GetSize(); ++j) {
            worklist[i]->RemoveCP(cplist[j]);
        }
        cplist.RemoveAll();
    }
    for (i = 0; i < worklist.GetSize(); ++i) {
        delete worklist[i];
    }
    worklist.RemoveAll();
    for (hgcp = fgroup->GetGroupCP(); hgcp; hgcp = hgcp->GetNext()) {
        const Vector test = *hgcp->GetCP()->GetModelPosition();
        test.PushMinMax(min, max);
    }

    pivot = 0.5 * (max + min);
    int k = 0;
    HProperty *property_org = fgroup->GetPropertyAt(k);
    while (property_org) {
        String propertyname = property_org->GetFullName();
        if (propertyname.Find(".Pivot") > -1) {
            auto *hvp = (HVectorProperty *)property_org;
            hvp->StoreValue(Time(), pivot);
            break;
        }
        k++;
        property_org = fgroup->GetPropertyAt(k);
    }

    return true;
}

void CMaPApp::GetGroupList(HModelCache *hmc, CArray<HGroup *, HGroup *> &grouplist) {
    grouplist.RemoveAll();
    HGroupContainer *hgc = hmc->GetChildGroupContainer();
    for (HGroup *hg = hgc->GetChildGroup(); hg; hg = (HGroup *)hg->GetSiblingSame()) {
        grouplist.Add(hg);
    }
}

BOOL CMaPApp::OnModel(HModelCache *hmc) {
    if (!hmc->GetChildGroupContainer())
        return true;
    CArray<HGroup *, HGroup *> grouplist;
    bool match;

    bool ischanged = false;
    do {
        GetGroupList(hmc, grouplist);
        match = false;
        for (int i = 0; i < grouplist.GetSize(); ++i) {
            if (FindMatch(grouplist[i], grouplist)) {
                match = true;
                ischanged = true;
                break;
            }
        }
    } while (match);
    //Check for groups , they don't have cp's and remove them
    RemoveEmptyGroups(grouplist);
    grouplist.RemoveAll();
    if (ischanged) {
        hmc->SetChanged(true);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        return true;
    }
    return true;

}

BOOL CMaPApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMaPApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
