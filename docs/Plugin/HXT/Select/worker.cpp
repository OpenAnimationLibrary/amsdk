#include "StdAfx.h"
#include "Select.h"

void CSelectApp::LoadSettings() const {
    para->number = GetRegistryValue("Select HXT", "cp_nr", 0);
    para->pid1 = GetRegistryValue("Select HXT", "pid1", 0);
    para->pid2 = GetRegistryValue("Select HXT", "pid2", 0);
    para->pid3 = GetRegistryValue("Select HXT", "pid3", 0);
    para->pid4 = GetRegistryValue("Select HXT", "pid4", 0);
    para->pid5 = GetRegistryValue("Select HXT", "pid5", 0);
    para->type = GetRegistryValue("Select HXT", "seltype", 0);
    para->view = GetRegistryValue("Select HXT", "view", 0);
    para->tolerance = GetRegistryValue("Select HXT", "tolerance", 0.9F);
    para->cp_mode = GetRegistryValue("Select HXT", "cp_mode", 0);
}

void CSelectApp::SaveSettings() const {
    SetRegistryValue("Select HXT", "cp_nr", (int)para->number);
    SetRegistryValue("Select HXT", "pid1", (int)para->pid1);
    SetRegistryValue("Select HXT", "pid2", (int)para->pid2);
    SetRegistryValue("Select HXT", "pid3", (int)para->pid3);
    SetRegistryValue("Select HXT", "pid4", (int)para->pid4);
    SetRegistryValue("Select HXT", "pid5", (int)para->pid5);
    SetRegistryValue("Select HXT", "seltype", para->type);
    SetRegistryValue("Select HXT", "view", para->view);
    SetRegistryValue("Select HXT", "tolerance", para->tolerance);
    SetRegistryValue("Select HXT", "cp_mode", para->cp_mode);
}

BOOL CSelectApp::Work(HModelCache *hmc) const {
    CString buf1, buf2, buf3, buf4, buf5;
    CString temp;
    HCP *hcp{}, *hcp_found{};
    HSpline *hsp{};
    HGroupCP *accumgroup{nullptr};
    int azpatch, patchfound;
    HPatch5 *hp5{};
    int i, j;
    PatchID pid;
    PatchID5 pid5;
    CArray<HCP *, HCP *> splinepoints;

    BOOL changed = FALSE;
    BOOL found = false;
    GetHProject()->DeselectAll();

    CWaitCursor wait;
    temp.Format("Nothing to do");
    hmc->FindPatches();
    int azep = azpatch = hmc->GetPatchCount();
    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        azep++;
    }
    auto *ep = new EPatch[azep + 1];
    for (i = 0; i < azpatch; ++i) {
        ep[i].Init(hmc->GetPatch(i), screen);
    }
    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        ep[i].Init(hp5, screen);
        i++;
    }
    azep = i;
    if (para->type != 0) {
        //Patchoperations
        switch (para->type) {
            case 1:
                //Patch id
                buf1.Format(" %u", para->pid1);
                buf2.Format(" %u", para->pid2);
                buf3.Format(" %u", para->pid3);
                buf4.Format(" %u", para->pid4);
                buf5.Format(" %u", para->pid5);
                patchfound = -1;
                if (para->pid5 != 0) {
                    temp = "patch" + buf1 + buf2 + buf3 + buf4 + buf5 + " not found";
                    //			    temp.Format("patch %s %s %s %s %s not found",buf1,buf2,buf3,buf4,buf5);
                    //5Point
                    pid5.m_id1 = para->pid1;
                    pid5.m_id2 = para->pid2;
                    pid5.m_id3 = para->pid3;
                    pid5.m_id4 = para->pid4;
                    pid5.m_id5 = para->pid5;
                    for (i = 0; i < azep; ++i) {
                        if (ep[i].numpoint == 5) {
                            if (ep[i].opatch5->GetPatchID() == pid5) {
                                patchfound = i;
                                break;
                            }
                        }
                    }
                } else {
                    temp = "patch" + buf1 + buf2 + buf3 + buf4 + " not found";
                    //			    temp.Format("patch %s %s %s %s not found",buf1,buf2,buf3,buf4);
                    pid.m_id1 = para->pid1;
                    pid.m_id2 = para->pid2;
                    pid.m_id3 = para->pid3;
                    pid.m_id4 = para->pid4;
                    for (i = 0; i < azep; ++i) {
                        if (ep[i].numpoint != 5) {
                            if (ep[i].opatch->GetPatchID() == pid) {
                                patchfound = i;
                                break;
                            }
                        }
                    }
                }
                if (patchfound != -1) {
                    found = true;
                    changed = true;
                    switch (ep[patchfound].numpoint) {
                        case 3:
                            ep[patchfound].opatch->GetCP1()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch->GetCP2()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch->GetCP3()->AddToGroup(&accumgroup);
                            break;
                        case 4:
                            ep[patchfound].opatch->GetCP1()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch->GetCP2()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch->GetCP3()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch->GetCP4()->AddToGroup(&accumgroup);
                            break;
                        case 5:
                            ep[patchfound].opatch5->GetCP1()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch5->GetCP2()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch5->GetCP3()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch5->GetCP4()->AddToGroup(&accumgroup);
                            ep[patchfound].opatch5->GetCP5()->AddToGroup(&accumgroup);
                            break;
                    }
                }
                break;
            case 2:
                //3Point
                for (i = 0; i < azep; ++i) {
                    if (ep[i].numpoint == 3) {
                        ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                        ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                        ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                        found = true;
                        changed = true;
                    }
                }
                break;
            case 3:
                //5Point
                for (i = 0; i < azep; ++i) {
                    if (ep[i].numpoint == 5) {
                        ep[i].opatch5->GetCP1()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP2()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP3()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP4()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP5()->AddToGroup(&accumgroup);
                        found = true;
                        changed = true;
                    }
                }
                break;
            case 4:
                //hook
                for (i = 0; i < azep; ++i) {
                    if (ep[i].ishooked) {
                        found = true;
                        changed = true;
                        switch (ep[i].numpoint) {
                            case 3:
                                ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                                break;
                            case 4:
                                ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP4()->AddToGroup(&accumgroup);
                                break;
                            case 5:
                                ep[i].opatch5->GetCP1()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP2()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP3()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP4()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP5()->AddToGroup(&accumgroup);
                                break;
                        }
                    }
                }
                break;
            case 5:
                //5point and hook
                for (i = 0; i < azep; ++i) {
                    if (ep[i].numpoint == 5) {
                        ep[i].opatch5->GetCP1()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP2()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP3()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP4()->AddToGroup(&accumgroup);
                        ep[i].opatch5->GetCP5()->AddToGroup(&accumgroup);
                        found = true;
                        changed = true;
                    }
                    if (ep[i].ishooked) {
                        found = true;
                        changed = true;
                        switch (ep[i].numpoint) {
                            case 3:
                                ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                                break;
                            case 4:
                                ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                                ep[i].opatch->GetCP4()->AddToGroup(&accumgroup);
                                break;
                            case 5:
                                ep[i].opatch5->GetCP1()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP2()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP3()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP4()->AddToGroup(&accumgroup);
                                ep[i].opatch5->GetCP5()->AddToGroup(&accumgroup);
                                break;
                        }
                    }
                }
                break;
            case 6:
                //unweighted
                for (hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
                    for (hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
                        HCP *headcp = hcp->GetHead();
                        if (!headcp->GetCPWeightHead()) {
                            hcp->AddToGroup(&accumgroup);
                            found = TRUE;
                            changed = TRUE;
                        }
                        if (hcp->IsLoop())
                            break;
                    }
                }
                break;
            case 7:
                //normal
                if (azep > 1) {
                    for (j = 0; j < azep; ++j) {
                        int pos_dir = 0;
                        int neg_dir = 0;
                        for (i = 0; i < azep; ++i) {
                            if (ep[j].IsNeighbor(&ep[i], false)) {
                                if (Dot(ep[j].ndir[0], ep[i].ndir[0]) < 0) {
                                    neg_dir++;
                                } else {
                                    pos_dir++;
                                }
                            }
                        }
                        if (neg_dir > pos_dir) {
                            found = true;
                            changed = true;
                            switch (ep[j].numpoint) {
                                case 3:
                                    ep[j].opatch->GetCP1()->AddToGroup(&accumgroup);
                                    ep[j].opatch->GetCP2()->AddToGroup(&accumgroup);
                                    ep[j].opatch->GetCP3()->AddToGroup(&accumgroup);
                                    break;
                                case 4:
                                    ep[j].opatch->GetCP1()->AddToGroup(&accumgroup);
                                    ep[j].opatch->GetCP2()->AddToGroup(&accumgroup);
                                    ep[j].opatch->GetCP3()->AddToGroup(&accumgroup);
                                    ep[j].opatch->GetCP4()->AddToGroup(&accumgroup);
                                    break;
                                case 5:
                                    ep[j].opatch5->GetCP1()->AddToGroup(&accumgroup);
                                    ep[j].opatch5->GetCP2()->AddToGroup(&accumgroup);
                                    ep[j].opatch5->GetCP3()->AddToGroup(&accumgroup);
                                    ep[j].opatch5->GetCP4()->AddToGroup(&accumgroup);
                                    ep[j].opatch5->GetCP5()->AddToGroup(&accumgroup);
                                    break;
                            }
                        }
                    }
                } else {
                    temp.Format("Only one patch in this model");
                }
                break;
            case 8:
                //view dependent
                for (j = 0; j < azep; ++j) {
                    BOOL found1 = false;
                    switch (para->view) {
                        case 0:
                            if (ep[j].ndir[0].z >= para->tolerance)
                                found1 = true;
                            break;
                        case 1:
                            if (ep[j].ndir[0].z <= para->tolerance * -1)
                                found1 = true;
                            break;
                        case 2:
                            if (ep[j].ndir[0].x <= para->tolerance * -1)
                                found1 = true;
                            break;
                        case 3:
                            if (ep[j].ndir[0].x >= para->tolerance)
                                found1 = true;
                            break;
                        case 4:
                            if (ep[j].ndir[0].y >= para->tolerance)
                                found1 = true;
                            break;
                        case 5:
                            if (ep[j].ndir[0].y <= para->tolerance * -1)
                                found1 = true;
                            break;
                    }
                    if (found1) {
                        found = true;
                        changed = true;
                        switch (ep[j].numpoint) {
                            case 3:
                                ep[j].opatch->GetCP1()->AddToGroup(&accumgroup);
                                ep[j].opatch->GetCP2()->AddToGroup(&accumgroup);
                                ep[j].opatch->GetCP3()->AddToGroup(&accumgroup);
                                break;
                            case 4:
                                ep[j].opatch->GetCP1()->AddToGroup(&accumgroup);
                                ep[j].opatch->GetCP2()->AddToGroup(&accumgroup);
                                ep[j].opatch->GetCP3()->AddToGroup(&accumgroup);
                                ep[j].opatch->GetCP4()->AddToGroup(&accumgroup);
                                break;
                            case 5:
                                ep[j].opatch5->GetCP1()->AddToGroup(&accumgroup);
                                ep[j].opatch5->GetCP2()->AddToGroup(&accumgroup);
                                ep[j].opatch5->GetCP3()->AddToGroup(&accumgroup);
                                ep[j].opatch5->GetCP4()->AddToGroup(&accumgroup);
                                ep[j].opatch5->GetCP5()->AddToGroup(&accumgroup);
                                break;
                        }
                    }
                }
                break;
        }
    } else {
        //cp
        buf1.Format("%u", para->number);
        temp = "cp " + buf1 + " not found";
        for (hsp = hmc->GetHeadSpline(); hsp && !found; hsp = hsp->GetNextSpline()) {
            for (hcp = hsp->GetHeadCP(); hcp && !found; hcp = hcp->GetNext()) {
                if (hcp->GetID() == para->number) {
                    found = TRUE;
                    hcp_found = hcp;
                    break;
                }
                if (hcp->IsLoop())
                    break;
            }
        }
        if (found) {
            switch (para->cp_mode) {
                case 0:
                    hcp_found->AddToGroup(&accumgroup);
                    changed = true;
                    break;
                case 1:
                    for (hcp = hcp_found->GetSpline()->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
                        hcp->AddToGroup(&accumgroup);
                        if (hcp->IsLoop())
                            break;
                    }
                    changed = true;
                    break;
                case 2:
                    for (hcp = hcp_found->GetSpline()->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
                        //						splinepoints.Add(hcp);
                        for (HCP *hcp1 = hcp->GetHead(); hcp1; hcp1 = hcp1->GetNextAttached()) {
                            splinepoints.Add(hcp1);
                        }
                        if (hcp->IsLoop())
                            break;
                    }
                    if (splinepoints.GetSize() > 1) {
                        for (i = 0; i < azep; ++i) {
                            int azconnect = 0;
                            for (j = 0; j < splinepoints.GetSize(); ++j) {
                                switch (ep[i].numpoint) {
                                    case 3:
                                        if (ep[i].opatch->GetCP1() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch->GetCP2() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch->GetCP3() == splinepoints[j])
                                            azconnect++;
                                        break;
                                    case 4:
                                        if (ep[i].opatch->GetCP1() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch->GetCP2() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch->GetCP3() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch->GetCP4() == splinepoints[j])
                                            azconnect++;
                                        break;
                                    case 5:
                                        if (ep[i].opatch5->GetCP1() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch5->GetCP2() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch5->GetCP3() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch5->GetCP4() == splinepoints[j])
                                            azconnect++;
                                        if (ep[i].opatch5->GetCP5() == splinepoints[j])
                                            azconnect++;
                                        break;
                                }
                            }
                            if (azconnect > 1) {
                                changed = true;
                                switch (ep[i].numpoint) {
                                    case 3:
                                        ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                                        ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                                        ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                                        break;
                                    case 4:
                                        ep[i].opatch->GetCP1()->AddToGroup(&accumgroup);
                                        ep[i].opatch->GetCP2()->AddToGroup(&accumgroup);
                                        ep[i].opatch->GetCP3()->AddToGroup(&accumgroup);
                                        ep[i].opatch->GetCP4()->AddToGroup(&accumgroup);
                                        break;
                                    case 5:
                                        ep[i].opatch5->GetCP1()->AddToGroup(&accumgroup);
                                        ep[i].opatch5->GetCP2()->AddToGroup(&accumgroup);
                                        ep[i].opatch5->GetCP3()->AddToGroup(&accumgroup);
                                        ep[i].opatch5->GetCP4()->AddToGroup(&accumgroup);
                                        ep[i].opatch5->GetCP5()->AddToGroup(&accumgroup);
                                        break;
                                }
                            }
                        }
                    }
                    splinepoints.RemoveAll();
                    break;
            }
        }
    }
    if (!found) {
        AfxMessageBox(temp, MB_OK);
    }
    SaveSettings();
    delete[] ep;
    delete para;
    if (changed) {
        hmc->AddToTemporaryGroup(accumgroup);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
    } else {
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
    }
    return TRUE;
}
