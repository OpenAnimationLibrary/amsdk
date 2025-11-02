// Transfer_AW.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Transfer_AW.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransfer_AWApp

BEGIN_MESSAGE_MAP(CTransfer_AWApp, CWinApp)
    //{{AFX_MSG_MAP(CTransfer_AWApp)
    // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransfer_AWApp Konstruktion

CTransfer_AWApp::CTransfer_AWApp() = default;

CTransfer_AWApp::~CTransfer_AWApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CTransfer_AWApp-Objekt

CTransfer_AWApp theApp;

void GetBoneBranch(HBoneCache *hbc, CArrayEx<HBoneCache *, HBoneCache *> &bonearray) {
    for (; hbc; hbc = hbc->GetSiblingBoneCache()) {
        bonearray.Add(hbc);
        if (hbc->GetChildBoneCache())
            GetBoneBranch(hbc->GetChildBoneCache(), bonearray);
    }
}

BOOL CTransfer_AWApp::OnStart(HModelCache *hmc) {
    HGroupContainer *hgc;
    HBoneCacheContainer *hbcc;
    HBoneCache *hbc;
    HSegmentCache *hsc;
    HSegmentCache *hsc1;
    HCPWeight *cpweight;
    HGroupCP *hgcp;
//    int i, j;
    float sum_weight;
    MB_WEIGHT tempweight;
    HCP *hcp;
    CCW_CP t_cp;
    TAW_GROUP_PAIR t_group_pair;
    TAW_BONELIST _tempbone;
    CArrayEx<HBoneCache *, HBoneCache *> bonetemp;
    TAW_LORES _lcp;
    TAW_HIRES _hcp;
    t_group_pair.lores.hg = nullptr;
    t_group_pair.hires.hg = nullptr;
    bool first_error;
    CString temp;

    para = new W_PARA;
    GetSettings();
    //#ifndef	_DEBUG
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        Cleanup();
        return true;
    }
    //#else
#ifdef _DEBUG
    fsd.Open("e:\\AM_Debug\\Transfer_AW.txt", FileMode::HS_ASCII);
    fsd << hmc->GetName() << nl;
#endif
    group_pair.SetSize(0, 10);
    bone_list.SetSize(0, 32);
    cp_list.SetSize(0, 128);
    flex_list.SetSize(0, 32);
    para->p_bar = GetProgressBar();

    CWaitCursor wait;
    if (para->p_bar) {
        para->p_bar->Initialize();
        para->p_bar->SetMessage1("Transfer_AW");
        para->p_bar->SetMessage2("Retrieve data");
        para->p_bar->SetProgress(0);
    }
    if ((hgc = hmc->GetChildGroupContainer())) {
        TAW_NOFLEX tflex;
        String groupname1;
        String groupname;
        for (HGroup *hg = hgc->GetChildGroup(); hg; hg = (HGroup *)hg->GetSibling()) {
            groupname = hg->GetName();
            if (groupname.Left(3) == "lo-") {
                t_group_pair.lores.hg = hg;
                for (HGroup *hg1 = hgc->GetChildGroup(); hg1; hg1 = (HGroup *)hg1->GetSibling()) {
                    groupname1 = hg1->GetName();
                    if (groupname1.Left(3) == "hi-") {
                        if (groupname.Right(groupname.GetLength() - 3) == groupname1.Right(groupname1.GetLength() - 3)) {
                            t_group_pair.hires.hg = hg1;
                            break;
                        }
                    }
                }
                if (t_group_pair.lores.hg && t_group_pair.hires.hg) {
                    group_pair.Add(t_group_pair);
                    t_group_pair.lores.hg = nullptr;
                    t_group_pair.hires.hg = nullptr;
                }
            }
            if (groupname.Find("no-flex") != -1) {
                tflex.hg = hg;
                flex_list.Add(tflex);
            }
        }
    } else {
        Cleanup();
        AfxMessageBox("No groups in this model",MB_OK | MB_ICONSTOP);
        return true;
    }

    if (group_pair.GetSize() < 1) {
        Cleanup();
        AfxMessageBox("No matching groups found",MB_OK | MB_ICONSTOP);
        return true;
    }

    if (para->p_bar) {
        para->p_bar->SetProgress(20);
    }

    if (flex_list.GetSize() != 0)
        para->has_noflex = true;

    hbcc = hmc->GetChildBoneCacheContainer();
    hbc = hbcc->GetChildBoneCache();

    bonetemp.SetSize(0, 32);
    GetBoneBranch(hbc, bonetemp);
    if (bonetemp.GetSize() == 0) {
        Cleanup();
        AfxMessageBox("No bones found",MB_OK | MB_ICONSTOP);
        return true;
    }

    for (int i = 0; i < bonetemp.GetSize(); ++i) {
        if (bonetemp[i]->GetObjectType() == HOT_NULLOBJECT)
            continue;
        _tempbone.hsc = (HSegmentCache *)bonetemp[i];
        _tempbone.start = bonetemp[i]->GetPivot()->GetValue();
        _tempbone.end = bonetemp[i]->GetEnd()->GetValue();
        Vector *bounds = _tempbone.hsc->GetBounds();
        bounds = _tempbone.hsc->GetBounds();
        _tempbone.bbox.bmin.Set(hash_constants::max_float);
        _tempbone.bbox.bmax.Set(-hash_constants::max_float);
        for (int j = 0; j < 8; ++j) {
            bounds[j].PushMinMax(_tempbone.bbox.bmin, _tempbone.bbox.bmax);
        }
        bone_list.Add(_tempbone);
    }
    bonetemp.RemoveAll();

    if (para->p_bar) {
        para->p_bar->SetProgress(40);
    }

    for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
            if (hcp == hcp->GetHead()) {
                if (!para->proceed_nohidden || (para->proceed_nohidden && !hcp->IsHide())) {
                    t_cp.cp = hcp;
                    t_cp.pos = *hcp->GetWorldPosition();
                    t_cp.id = hcp->GetID();
                    t_cp.bone_nr = -1;
                    hsc = hcp->GetSegmentCache();
                    if (hsc) {
                        for (int i = 0; i < bone_list.GetSize(); ++i) {
                            if (hsc == bone_list[i].hsc) {
                                t_cp.bone_nr = i;
                                break;
                            }
                        }
                    }
                }
                cp_list.Add(t_cp);
            }
            if (hcp->IsLoop())
                break;
        }
    }

    if (para->p_bar) {
        para->p_bar->SetProgress(60);
    }

    for (int i = 0; i < group_pair.GetSize(); ++i) {
        //lores group
        first_error = false;
        hgcp = group_pair[i].lores.hg->GetGroupCP();
        while (hgcp) {
            hcp = hgcp->GetCP();
            _lcp.refer = -1;
            for (int j = 0; j < cp_list.GetSize(); ++j) {
                if (hcp == cp_list[j].cp) {
                    _lcp.refer = j;
                    break;
                }
            }
            if (_lcp.refer != -1) {
                if (cp_list[_lcp.refer].bone_nr != -1) {
                    if ((cpweight = hcp->GetCPWeightHead())) {
                        sum_weight = 0;
                        tempweight.hsc = hcp->GetSegmentCache();
                        tempweight.weight = 1.F;
                        _lcp.weightlist.Add(tempweight);
                        _lcp.has_weight = true;
                        for (cpweight = hcp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
                            hsc1 = cpweight->GetSegmentCache();
                            tempweight.hsc = hsc1;
                            tempweight.weight = cpweight->GetWeight();
                            _lcp.weightlist.Add(tempweight);
                            sum_weight += tempweight.weight;
                        }
                        _lcp.weightlist[0].weight = 1.F - sum_weight;
                    } else {
                        _lcp.has_weight = false;
                    }
                    group_pair[i].lores.cplist.Add(_lcp);
                    _lcp.weightlist.RemoveAll();
                } else {
                    if (!first_error) {
                        temp.Format("Possible problem with Group\n\"%s\"\nsome CP's are not assigned to a bone", group_pair[i].lores.hg->GetName());
                        AfxMessageBox(temp,MB_ICONEXCLAMATION);
                        first_error = true;
                    }
                }
            }
            hgcp = hgcp->GetNext();
        }
        //hires group
        hgcp = group_pair[i].hires.hg->GetGroupCP();
        _hcp.az_dist_hires = 0;
        _hcp.az_dist_lores = 0;
        _hcp.isassigned = false;
        _hcp.isnoflex = false;
        _hcp.has_weight = false;
        while (hgcp) {
            hcp = hgcp->GetCP();
            _hcp.refer = -1;
            for (int j = 0; j < cp_list.GetSize(); ++j) {
                if (hcp == cp_list[j].cp) {
                    _hcp.refer = j;
                    break;
                }
            }
            if (_hcp.refer != -1) {
                group_pair[i].hires.cplist.Add(_hcp);
            }
            hgcp = hgcp->GetNext();
        }
    }

    if (para->p_bar) {
        para->p_bar->SetProgress(100);
    }
    if (para->has_noflex) {
        int h;
        TAW_REF tref;
        for (int i = 0; i < flex_list.GetSize(); ++i) {
            hgcp = flex_list[i].hg->GetGroupCP();
            while (hgcp) {
                hcp = hgcp->GetCP();
                for (int j = 0; j < group_pair.GetSize(); ++j) {
                    for (h = 0; h < group_pair[j].hires.cplist.GetSize(); ++h) {
                        if (hcp == cp_list[group_pair[j].hires.cplist[h].refer].cp) {
                            group_pair[j].hires.cplist[h].isnoflex = true;
                            tref.group_nr = j;
                            tref.cp_nr = h;
                            flex_list[i].ref.Add(tref);
                            flex_list[i].refer.Add(group_pair[j].hires.cplist[h].refer);
                            break;
                        }
                    }
                }
                hgcp = hgcp->GetNext();
            }
        }
    }

    Work(hmc);

#ifdef _DEBUG
    for (int i = 0; i < group_pair.GetSize(); ++i) {
        fsd << nl << group_pair[i].lores.hg->GetName() << "  ";
        fsd << group_pair[i].hires.hg->GetName() << nl;
        fsd << nl << "LoRes" << nl;
        for (int j = 0; j < group_pair[i].lores.cplist.GetSize(); ++j) {
            fsd << "CP #" << cp_list[group_pair[i].lores.cplist[j].refer].id << " assigned to " << bone_list[cp_list[group_pair[i].lores.cplist[j].refer].bone_nr].hsc->GetName() << nl;
            if (group_pair[i].lores.cplist[j].has_weight) {
                fsd << "Weights" << nl;
                for (int h = 0; h < group_pair[i].lores.cplist[j].weightlist.GetSize(); ++h) {
                    fsd << group_pair[i].lores.cplist[j].weightlist[h].hsc->GetName() << " " << group_pair[i].lores.cplist[j].weightlist[h].weight << nl;
                }
            } else {
                fsd << "Not weightet" << nl;
            }
        }
        fsd << nl << "HiRes" << nl;
        for (int j = 0; j < group_pair[i].hires.cplist.GetSize(); ++j) {
            fsd << "CP #" << cp_list[group_pair[i].hires.cplist[j].refer].id;
            if (group_pair[i].hires.cplist[j].isassigned) {
                fsd << " assigned to " << bone_list[cp_list[group_pair[i].hires.cplist[j].refer].bone_nr].hsc->GetName() << nl;
            } else {
                fsd << " not assigned" << nl;
            }
            if ((cpweight = cp_list[group_pair[i].hires.cplist[j].refer].cp->GetCPWeightHead())) {
                sum_weight = 0;
                hsc = cp_list[group_pair[i].hires.cplist[j].refer].cp->GetSegmentCache();
                for (cpweight = cp_list[group_pair[i].hires.cplist[j].refer].cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
                    fsd << cpweight->GetSegmentCache()->GetName() << " " << cpweight->GetWeight() << nl;
                    sum_weight += cpweight->GetWeight();
                }
                fsd << hsc->GetName() << " " << 1.F - sum_weight << nl;
            } else {
                fsd << "No weights" << nl;
            }
        }
    }
    fsd << nl;
    fsd.Close();
#endif

    SaveSettings();
    Cleanup();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return true;
}

void CTransfer_AWApp::Cleanup() {
    group_pair.RemoveAll();
    flex_list.RemoveAll();
    bone_list.RemoveAll();
    cp_list.RemoveAll();
    if (para->p_bar) {
        para->p_bar->Uninitialize();
        para->p_bar = nullptr;
    }
    delete para;
}

BOOL CTransfer_AWApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CTransfer_AWApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

void CTransfer_AWApp::GetSettings() const {
    para->pass1_cp = GetRegistryValue("Transfer_AW HXT", "pass1_cp", 4);
    para->pass2_cp = GetRegistryValue("Transfer_AW HXT", "pass2_cp", 4);
    para->smooth = GetRegistryValue("Transfer_AW HXT", "smooth", 1.F);
    para->az_smoothpass = GetRegistryValue("Transfer_AW HXT", "smooth_pass", 1);
    para->alternate_hiresdist = GetRegistryValue("Transfer_AW HXT", "alternate_dist", false);
    para->proceed_nohidden = GetRegistryValue("Transfer_AW HXT", "nohidden", false);
    para->has_noflex = false;
    para->p_bar = nullptr;
}

void CTransfer_AWApp::SaveSettings() const {
    SetRegistryValue("Transfer_AW HXT", "pass1_cp", para->pass1_cp);
    SetRegistryValue("Transfer_AW HXT", "pass2_cp", para->pass2_cp);
    SetRegistryValue("Transfer_AW HXT", "smooth", para->smooth);
    SetRegistryValue("Transfer_AW HXT", "smooth_pass", para->az_smoothpass);
    SetRegistryValue("Transfer_AW HXT", "alternate_dist", para->alternate_hiresdist);
    SetRegistryValue("Transfer_AW HXT", "nohidden", para->proceed_nohidden);
}
