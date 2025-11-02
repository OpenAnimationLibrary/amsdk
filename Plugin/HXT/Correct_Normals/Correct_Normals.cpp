// Correct_Normals.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Correct_Normals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCorrect_NormalsApp

BEGIN_MESSAGE_MAP(CCorrect_NormalsApp, CWinApp)
    //{{AFX_MSG_MAP(CCorrect_NormalsApp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCorrect_NormalsApp Konstruktion
CCorrect_NormalsApp::CCorrect_NormalsApp() = default;

CCorrect_NormalsApp::~CCorrect_NormalsApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CCorrect_NormalsApp-Objekt

CCorrect_NormalsApp theApp;

bool CheckPatch(PatchList *plist, const int patchnumber) {
    int neg_dir;

    int pos_dir = neg_dir = 0;
    for (int i = 0; i < plist->neighborlist[patchnumber].azneighbor; ++i) {
        if (Dot(plist->patchlist[patchnumber].ndir[0], plist->patchlist[plist->neighborlist[patchnumber].neighbor[i]].ndir[0]) < 0) {
            neg_dir++;
        } else {
            pos_dir++;
        }
    }

    if (neg_dir > pos_dir) {
        if (plist->patchlist[patchnumber].opatch) {
            plist->patchlist[patchnumber].opatch->ReverseNormal();
            plist->patchlist[patchnumber].ndir[0].Negate();
        }
        if (plist->patchlist[patchnumber].opatch5) {
            plist->patchlist[patchnumber].opatch5->ReverseNormal();
            plist->patchlist[patchnumber].ndir[0].Negate();
        }
        return true;
    }
    return false;
}

BOOL CCorrect_NormalsApp::ReverseNormals(HModelCache *hmc) {
    EPatch ep_temp;
    HPatch5 *hp5;
    int azpatches, i;
    HGroupCP *accumgroup = nullptr;
//    HPatch *hp;
//    HCP *cp;
//    Vector testscreen;

    hmc->OpenView(0); //Frontview needed
    CWaitCursor wait;
    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("Correct Normals");
        p_bar->SetMessage2("Find patches");
        p_bar->SetProgress(0);
    }

    hmc->FindPatches();
    if ((azpatches = hmc->GetPatchCount()) == 0) {
        AfxMessageBox("No patches found in this model", MB_OK | MB_ICONSTOP);
        if (p_bar)
            p_bar->Uninitialize();
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        return true;
    }

    int azpatches5 = 0;
    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        azpatches5++;
    }

    auto *plist = new PatchList;
    double counter = 100. / azpatches + azpatches5;
    double akt_count;
    if (p_bar) {
        p_bar->SetMessage2("Init patchlist");
    }

    for (i = 0; i < azpatches; ++i) {
        if (p_bar) {
            akt_count = counter * i;
            p_bar->SetProgress((int)akt_count);
        }
        ep_temp.Init(hmc->GetPatch(i));
        plist->patchlist.Add(ep_temp);
    }

    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        if (p_bar) {
            akt_count = counter * i;
            p_bar->SetProgress((int)akt_count);
        }
        ep_temp.Init(hp5);
        plist->patchlist.Add(ep_temp);
        i++;
    }

    plist->Sort(p_bar);
    plist->GetNeighbors(p_bar, false);

    bool changed = false;
    counter = 100. / (plist->patchlist.GetSize() - 1);
    if (p_bar) {
        p_bar->SetMessage2("Check patch");
    }
    for (i = 0; i < plist->patchlist.GetSize(); ++i) {
        if (p_bar) {
            akt_count = counter * i;
            p_bar->SetProgress((int)akt_count);
        }
        if (CheckPatch(plist, i)) {
            changed = true;
            switch (plist->patchlist[i].numpoint) {
                case 3:
                    plist->patchlist[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                    break;
                case 4:
                    plist->patchlist[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch->GetCP4()->AddToGroup(&accumgroup);
                    break;
                case 5:
                    plist->patchlist[i].opatch5->GetCP1()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch5->GetCP2()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch5->GetCP3()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch5->GetCP4()->AddToGroup(&accumgroup);
                    plist->patchlist[i].opatch5->GetCP5()->AddToGroup(&accumgroup);
                    break;
            }
        }
    }
    delete plist;

    if (p_bar)
        p_bar->Uninitialize();
    if (changed) {
        hmc->AddToTemporaryGroup(accumgroup);
        hmc->SetChanged(true);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        return TRUE;
    }
    AfxMessageBox("Nothing to do", MB_OK | MB_ICONINFORMATION);
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

BOOL CCorrect_NormalsApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CCorrect_NormalsApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
