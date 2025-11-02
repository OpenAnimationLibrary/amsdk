#include "StdAfx.h"
#include "CloneWeight.h"

float Distance(const Vector v) {
    return v.Norm();
}

float Distance(const Vector v1, const Vector v2) {
    return Distance(v2 - v1);
}

bool NeedAttached(HSegmentCache *hsc, const HCP *cp) {
    HGroupCP *hgcp_org = hsc->GetGroupCP();
    if (!hgcp_org)
        return TRUE; //segment has no cp's
    for (HGroupCP *hgroup = hgcp_org; hgroup; hgroup = hgroup->GetNext()) {
        if (cp == hgroup->GetCP())
            return FALSE;
    }
    return TRUE;
}

void GetBoneBranch(HBoneCache *hbc, CArrayEx<HBoneCache *, HBoneCache *> &bonearray) {
    for (; hbc; hbc = hbc->GetSiblingBoneCache()) {
        bonearray.Add(hbc);
        if (hbc->GetChildBoneCache())
            GetBoneBranch(hbc->GetChildBoneCache(), bonearray);
    }
}

HBoneCache *FindMatchingBone(CArrayEx<HBoneCache *, HBoneCache *> &bonearray, HBoneCache *bonetofind) {
    for (int i = 0; i < bonearray.GetSize(); ++i) {
        if (bonearray[i]->GetMatchName() == bonetofind->GetMatchName())
            return bonearray[i];
    }
    return nullptr;
}

HSegmentCache *FindMatchingSegment(CArrayEx<HBoneCache *, HBoneCache *> &bonearray, HSegmentCache *bonetofind) {
    for (int i = 0; i < bonearray.GetSize(); ++i) {
        if (bonearray[i]->GetMatchName() == bonetofind->GetMatchName())
            return (HSegmentCache *)bonearray[i];
    }
    return nullptr;
}

BOOL CCloneWeightApp::CheckPosition(const Vector pos_tocheck, const Vector pos) const {
    if (pos_tocheck == pos)
        return TRUE;
    const float distance = hash_math::abs(Distance(pos_tocheck, pos));
    if (distance <= para->max_dist)
        return TRUE;
    return FALSE;
}

void CCloneWeightApp::FillCPList(HModelCache *hmc_org, HModelCache *hmc) {
    CCW_CP tempcp;
    for (HSpline *hsp = hmc_org->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (HCP *cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (!cp->IsHook() && cp == cp->GetHead()) {
                tempcp.cp = cp;
                tempcp.pos = *cp->GetHead()->GetModelPosition();
                cp_org.Add(tempcp);
            }
            if (cp->IsLoop())
                break;
        }
    }
    for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (HCP *cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (!cp->IsHook() && cp == cp->GetHead()) {
                tempcp.cp = cp;
                tempcp.pos = *cp->GetHead()->GetModelPosition();
                cp_dest.Add(tempcp);
            }
            if (cp->IsLoop())
                break;
        }
    }
}

void CCloneWeightApp::RemoveOldWeight(HCP *cp) {
    CArray<HCPWeight *, HCPWeight *> weightlist;
    for (HCPWeight *cpweight = cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
        weightlist.Add(cpweight);
    }
    if (weightlist.GetSize() == 0)
        return;
    for (int i = 0; i < weightlist.GetSize(); ++i) {
        cp->RemoveCPWeight(weightlist[i]);
    }
    weightlist.RemoveAll();
}

BOOL CCloneWeightApp::Worker(HModelCache *hmc_org, HModelCache *hmc) {
    CArrayEx<HBoneCache *, HBoneCache *> bc_org;
    CArrayEx<HBoneCache *, HBoneCache *> bc;
    HBoneCache *hbc_master, *hbc_org;
    if (hmc_org->GetChildBoneCacheContainer())
        hbc_org = hmc_org->GetChildBoneCacheContainer()->GetChildBoneCache();
    else
        return FALSE;

    GetBoneBranch(hbc_org, bc_org);
    if (hmc->GetChildBoneCacheContainer())
        hbc_master = hmc->GetChildBoneCacheContainer()->GetChildBoneCache();
    else
        return FALSE;

    cp_org.RemoveAll();
    cp_dest.RemoveAll();

    GetBoneBranch(hbc_master, bc);
    FillCPList(hmc_org, hmc);

    BOOL changed = FALSE, has_weights = FALSE;
    for (int i = 0; i < cp_org.GetSize(); ++i) {
        HSegmentCache *hsc_org = cp_org[i].cp->GetSegmentCache();
        if (!hsc_org)
            continue;
        if (para->reassigncp) {
            //assign cp's to bones
            for (int j = 0; j < cp_dest.GetSize(); ++j) {
                if (CheckPosition(cp_org[i].pos, cp_dest[j].pos)) {
                    HSegmentCache *hsc_start = cp_dest[j].cp->GetSegmentCache();
                    if (!hsc_start || hsc_org->GetMatchName() != hsc_start->GetMatchName()) {
                        HSegmentCache *dest_segment = FindMatchingSegment(bc, hsc_org);
                        if (dest_segment) {
                            dest_segment->AquireCP(cp_dest[j].cp);
                            changed = TRUE;
                        }
                    }
                }
            }
        }
        HCPWeight *cpweight = cp_org[i].cp->GetCPWeightHead();
        if (cpweight) {
            has_weights = TRUE;
            for (int j = 0; j < cp_dest.GetSize(); ++j) {
                if (CheckPosition(cp_org[i].pos, cp_dest[j].pos)) {
                    RemoveOldWeight(cp_dest[j].cp);
                    for (cpweight = cp_org[i].cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
                        HSegmentCache *hsc = cpweight->GetSegmentCache();
                        if (hsc) {
                            HSegmentCache *dest_segment = FindMatchingSegment(bc, hsc);
                            if (dest_segment) {
                                HCPWeight *cpweight_dest = cp_dest[j].cp->AddCPWeight();
                                if (cpweight_dest) {
                                    changed = TRUE;
                                    cpweight_dest->SetSegmentCache(dest_segment);
                                    cpweight_dest->SetWeight(cpweight->GetWeight());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (!has_weights) {
        const String msg = "Source \"" + hmc_org->GetMatchName() + "\" has no weighted cp's";
        AfxMessageBox(msg.Get(),MB_ICONWARNING);
    } else {
        if (!changed) {
            const String msg = "Target \"" + hmc->GetMatchName() + "\" doesn't match source \"" + hmc_org->GetMatchName() + "\"";
            AfxMessageBox(msg.Get(),MB_ICONWARNING);
        } else {
            hmc->SetChanged(TRUE);
        }
    }
#ifdef _DEBUG
    DebugWeights(hmc_org);
    DebugWeights(hmc);
#endif
    return TRUE;
}

#ifdef _DEBUG
void CCloneWeightApp::DebugWeights(HModelCache *hmc,const bool end) {
    FileStream fs1;
    const String modelname = hmc->GetMatchName();
    String filename;
    if (end)
        filename = "E://am_debug//end_weights_" + modelname + ".txt";
    else
        filename = "E://am_debug//start_weights_" + modelname + ".txt";

    /*
       filename = logname_ext.GetPathOnly()+"\\mbw_after_"+logname_ext.GetNameOnlyWithoutSuffix()+".txt";
    */
    FillCPSList(hmc);
    FillWeightList(hmc, true);
    fs1.Open(filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
    for (int i = 0; i < cpw_list.GetSize(); ++i) {
        fs1 << "CPID " << cpw_list[i].cp->GetID() << nl;
        if (cpw_list[i].cp->GetSegmentCache()) {
            fs1 << "  Assigned to \"" << cpw_list[i].cp->GetSegmentCache()->GetName() << "\"" << nl;
        } else {
            fs1 << "  Not assigned" << nl;
        }
        fs1 << "  Attached cp ";
        for (HCP *cp = cpw_list[i].cp->GetHead(); cp; cp = cp->GetNextAttached()) {
            fs1 << cp->GetID() << ";";
        }
        fs1 << nl;
        if (cpw_list[i].haveweight) {
            fs1 << "  CP is weightet" << nl;
            for (int j = 0; j < cpw_list[i].weightlist.GetSize(); ++j) {
                fs1 << "    Bone \"";
                if (cpw_list[i].weightlist[j].hsc)
                    fs1 << cpw_list[i].weightlist[j].hsc->GetName();
                fs1 << "\" " << cpw_list[i].weightlist[j].weight * 100.F << nl;
            }
        } else {
            fs1 << "  CP is unweightet" << nl;
        }
        fs1 << nl;
    }
    fs1.Close();
}

void CCloneWeightApp::FillCPSList(HModelCache *hmc) {
    _CPS tempcp;
    cps_list.RemoveAll();
    for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (HCP *cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (!cp->IsHook()) {
                //new
                tempcp.cp = cp;
                tempcp.pos = *cp->GetHead()->GetModelPosition();
                tempcp.isassigned = FALSE;
                tempcp.weightsource = FALSE;
                cps_list.Add(tempcp);
            }
            if (cp->IsLoop())
                break;
        }
    }
}

void CCloneWeightApp::FillWeightList(HModelCache *hmc, bool afterweighting) {
    CArrayEx<_WEIGHT, _WEIGHT> weightlist;
    HCPWeight *cpweight;

    cpw_list.RemoveAll();
    for (int i = 0; i < cps_list.GetSize(); ++i) {
        _CPW tempcpw;
        if (!cps_list[i].weightsource && !afterweighting)
            continue;
        weightlist.RemoveAll();
        HSegmentCache *hsc = cps_list[i].cp->GetSegmentCache();
        tempcpw.cp = cps_list[i].cp;
        tempcpw.pos = cps_list[i].pos;
        tempcpw.haveweight = FALSE;
        if (hsc) {
            if (tempcpw.cp == tempcpw.cp->GetHead()) {
                _WEIGHT tempweight;
                if ((cpweight = tempcpw.cp->GetCPWeightHead())) {
                    tempcpw.haveweight = TRUE;
                    tempweight.hsc = hsc;
                    tempweight.weight = 1.F;
                    tempcpw.weightlist.Add(tempweight);
                    for (cpweight = tempcpw.cp->GetCPWeightHead(); cpweight; cpweight = cpweight->GetNext()) {
                        hsc = cpweight->GetSegmentCache();
                        tempweight.hsc = hsc;
                        tempweight.weight = cpweight->GetWeight();
                        tempcpw.weightlist.Add(tempweight);
                    }
                    for (int j = 1; j < tempcpw.weightlist.GetSize(); ++j) {
                        tempcpw.weightlist[0].weight -= tempcpw.weightlist[j].weight;
                    }
                    cpw_list.Add(tempcpw);
                    tempcpw.weightlist.RemoveAll();
                } else {
                    tempcpw.haveweight = FALSE;
                    tempweight.hsc = tempcpw.cp->GetSegmentCache();
                    tempweight.weight = 1.F;
                    tempcpw.weightlist.Add(tempweight);
                    cpw_list.Add(tempcpw);
                    tempcpw.weightlist.RemoveAll();
                }
            }
        }
    }
}
#endif
