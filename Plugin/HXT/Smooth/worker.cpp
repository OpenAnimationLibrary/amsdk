#include "StdAfx.h"
#include "Smooth.h"

Vector midPoint(const Vector A, const Vector B) {
    Vector m = A + B;
    m *= 0.5F;
    return m;
}

Vector newPos(HCP *cp1, HCP *cp2) {

    const Vector p1 = *cp1->GetHead()->GetModelPosition();
    const Vector p2 = cp1->GetModelInTangent();
    const Vector p3 = cp2->GetModelOutTangent();
    const Vector p4 = *cp2->GetHead()->GetModelPosition();
    const Vector l2 = midPoint(p1, p2);
    const Vector h = midPoint(p2, p3);
    const Vector r3 = midPoint(p3, p4);
    const Vector l3 = midPoint(l2, h);
    const Vector r2 = midPoint(h, r3);
    const Vector c = midPoint(l3, r2);
    return c;
}

int CSmoothApp::GetSplineaz(HModelCache *hmc, HGroup *hg, const int az) {

    auto **hsp = new HSpline *[az * 2];
    int azspline = 0;
    for (HGroupCP *groupcp = hg->GetGroupCP(); groupcp; groupcp = groupcp->GetNext()) {
        HSpline *temp_hsp = groupcp->GetCP()->GetSpline();
        if (azspline == 0) {
            hsp[0] = temp_hsp;
            azspline++;
        } else {
            bool found = false;
            for (int i = 0; i < azspline; ++i) {
                if (hsp[i] == temp_hsp) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                hsp[azspline] = temp_hsp;
                azspline++;
            }
        }
    }

    delete [] hsp;
    return azspline;
}

int CSmoothApp::GetCPaz(HSpline *hsp) {
    int azcp = 0;

    for (HCP *hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext(), azcp++) {
        if (hcp->IsLoop())
            break;
    }
    return azcp;
}

BOOL CSmoothApp::Init(HModelCache *hmc, HGroup *hg) {
    int azgroupcp = 0;

    for (HGroupCP *groupcp = hg->GetGroupCP(); groupcp; groupcp = groupcp->GetNext()) {
        azgroupcp++;
    }

    para = new PARAMETER;

    para->azspline = GetSplineaz(hmc, hg, azgroupcp);
    para->lock_x = false;
    para->lock_y = false;
    para->lock_z = false;
    para->recurse = 1;
    para->complet = false;
    para->half = false;
    para->allsplines = 0;
    para->min_cp = 4;

    if (para->azspline == 1 && azgroupcp < 4) {
        para->complet = true;
    }
    return TRUE;
}

BOOL CSmoothApp::Work(HModelCache *hmc, HGroup *hg) const {
    int i, j;
    HGroupCP *accumgroup = nullptr;

    CWaitCursor wait;

    if (para->azspline == 1 && para->complet) {
        //1 Spline komplett
        para->spline = new SPLINE[1];
        para->spline[0].hsp = hg->GetGroupCP()->GetCP()->GetSpline();
        para->spline[0].azcp = GetCPaz(para->spline[0].hsp);
        para->spline[0].pos_org = new Vector [para->spline[0].azcp + 1];
        para->spline[0].pos_new = new Vector [para->spline[0].azcp + 1];
        para->spline[0].pos_changed = new bool [para->spline[0].azcp + 1];
        para->spline[0].azcp = 0;
        for (HCP *hcp = para->spline[0].hsp->GetHeadCP(); hcp; hcp = hcp->GetNext(), para->spline[0].azcp++) {
            para->spline[0].hcp.Add(hcp);
            if (hcp->IsLoop())
                break;
        }
    } else {
        if (!GetSplines(hmc, hg))
            return FALSE;
    }

    for (j = 0; j < para->azspline; ++j) {
        for (i = 0; i < para->spline[j].azcp; ++i) {
            para->spline[j].pos_org[i] = *para->spline[j].hcp[i]->GetModelPosition();
            para->spline[j].pos_changed[i] = false;
        }
    }
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }
    GetHProject()->DeselectAll();

    for (i = 0; i < para->recurse; ++i) {
        for (j = 0; j < para->azspline; ++j) {
            SmoothSpline(hmc, j);
        }
        CheckConnect(hmc);
        for (j = 0; j < para->azspline; ++j) {
            SetSpline(hmc, j);
        }
        accumgroup = nullptr;
        for (j = 0; j < para->azspline; ++j) {
            for (int k = 0; k < para->spline[j].azcp; ++k) {
                para->spline[j].hcp[k]->AddToGroup(&accumgroup);
            }
        }

        hmc->AddToTemporaryGroup(accumgroup);
        hmc->Update();
        GetHProject()->UpdateAllViews(TRUE);
        for (j = 0; j < para->azspline; ++j) {
            ChangeSplinePos(hmc, j);
        }
    }

    for (j = 0; j < para->azspline; ++j) {
        //         delete [] para->spline[j].hcp;
        delete [] para->spline[j].pos_org;
        delete [] para->spline[j].pos_new;
        delete [] para->spline[j].pos_changed;
    }
    delete [] para->spline;
    return TRUE;
}

int CSmoothApp::ReorderCP(CSPLINE *sortspline, const int splinenr, int azspline) const {
    int i;

    CArray<HCP *, HCP *> ord_cp;
    int j = 0;
    for (HCP *akt_cp = sortspline[splinenr].hsp->GetHeadCP(); akt_cp; akt_cp = akt_cp->GetNext()) {
        for (i = 0; i < sortspline[splinenr].azcp; ++i) {
            if (akt_cp == sortspline[splinenr].hcp[i]) {
                ord_cp.Add(akt_cp);
                j++;
            }
        }
        if (akt_cp->IsLoop())
            break;
    }

    int start = 0;
    int newazcp = 0;
    while (newazcp < 4 && start < sortspline[splinenr].azcp - 3) {
        newazcp = 1;
        for (i = start; i < sortspline[splinenr].azcp - 1; i++, newazcp++) {
            if (ord_cp[i]->GetNext() != ord_cp[i + 1])
                break;
        }
        start++;
    }

    if (newazcp < 4) {
        if (para->allsplines == 1) {
            i = 0;
            for (HCP *hcp = sortspline[splinenr].hsp->GetHeadCP(); hcp; hcp = hcp->GetNext(), ++i) {
                sortspline[splinenr].hcp.Add(hcp);
                if (hcp->IsLoop())
                    break;
            }
            sortspline[splinenr].azcp = i;
            sortspline[splinenr].use = true;
        } else {
            sortspline[splinenr].azcp = 0;
            sortspline[splinenr].use = false;
        }
        return azspline;
    }

    if (newazcp > sortspline[splinenr].azcp)
        newazcp = sortspline[splinenr].azcp;
    sortspline[splinenr].use = true;
    start--;
    if (sortspline[splinenr].azcp - newazcp >= 4 && azspline < para->azspline * 2) {
        //2.Spline !
        sortspline[azspline].hsp = sortspline[splinenr].hsp;
        j = 0;
        for (i = start + newazcp; i < sortspline[splinenr].azcp; i++, ++j) {
            sortspline[azspline].hcp.Add(sortspline[splinenr].hcp[i]);
        }
        sortspline[azspline].azcp = j;
        azspline++;
    }

    j = 0;
    for (i = 0; i < newazcp; i++, ++j) {
        sortspline[splinenr].hcp[j] = ord_cp[i + start];
    }
    sortspline[splinenr].azcp = newazcp;

    return azspline;
}

BOOL CSmoothApp::GetSplines(HModelCache *hmc, HGroup *hg) const {

    HGroupCP *groupcp;
    HSpline *temp_hsp;
    int i;
    bool found;
    CString temp;

    if (para->azspline == 1)
        para->azspline = 2;
    auto *sortspline = new CSPLINE[para->azspline * 2LL];
    int azspline = 0;
    if (para->allsplines == 1 && para->complet) {
        HCP *hcp;
        //alle komplett
        for (groupcp = hg->GetGroupCP(); groupcp; groupcp = groupcp->GetNext()) {
            temp_hsp = groupcp->GetCP()->GetSpline();
            if (azspline == 0) {
                sortspline[0].hsp = temp_hsp;
                i = 0;
                for (hcp = temp_hsp->GetHeadCP(); hcp; hcp = hcp->GetNext(), ++i) {
                    sortspline[0].hcp.Add(hcp);
                    if (hcp->IsLoop())
                        break;
                }
                sortspline[0].azcp = i;
                sortspline[0].use = i > 4;
                azspline++;
            } else {
                found = false;
                for (i = 0; i < azspline; ++i) {
                    if (sortspline[i].hsp == temp_hsp)
                        found = true;
                }
                if (!found) {
                    sortspline[azspline].hsp = temp_hsp;
                    i = 0;
                    for (hcp = temp_hsp->GetHeadCP(); hcp; hcp = hcp->GetNext(), ++i) {
                        sortspline[azspline].hcp.Add(hcp);
                        if (hcp->IsLoop())
                            break;
                    }
                    sortspline[azspline].azcp = i;
                    sortspline[azspline].use = i > 4;
                    azspline++;
                }
            }
        }
    } else {
        for (groupcp = hg->GetGroupCP(); groupcp; groupcp = groupcp->GetNext()) {
            temp_hsp = groupcp->GetCP()->GetSpline();
            if (azspline == 0) {
                sortspline[0].hsp = temp_hsp;
                sortspline[0].azcp = 0;
                sortspline[0].hcp.Add(groupcp->GetCP());
                sortspline[0].azcp ++;
                azspline++;
            } else {
                found = false;
                for (i = 0; i < azspline; ++i) {
                    if (sortspline[i].hsp == temp_hsp) {
                        found = true;
                        sortspline[i].hcp.Add(groupcp->GetCP());
                        sortspline[i].azcp ++;
                        break;
                    }
                }
                if (!found) {
                    sortspline[azspline].hsp = temp_hsp;
                    sortspline[azspline].azcp = 0;
                    sortspline[azspline].hcp.Add(groupcp->GetCP());
                    sortspline[azspline].azcp ++;
                    azspline++;
                }
            }
        }
        for (i = 0; i < azspline; ++i) {
            azspline = ReorderCP(sortspline, i, azspline);
        }
    }
    found = false;
    for (i = 0; i < azspline; ++i) {
        if (sortspline[i].azcp != 0)
            found = true;
    }
    if (!found) {
        temp.Format("No Splines with 4 successively selectetd CP's\nAbort");
        AfxMessageBox(temp,MB_OK | MB_ICONSTOP);
        delete [] sortspline;
        return false;
    }

    if (para->allsplines == 0) {
        //nur Spline mit den meisten CP'S
        int highestcp = 0;
        for (i = 1; i < azspline; ++i) {
            if (sortspline[highestcp].azcp < sortspline[i].azcp)
                highestcp = i;
        }
        para->spline = new SPLINE[1];
        para->azspline = 1;
        para->spline[0].hsp = sortspline[highestcp].hsp;
        para->spline[0].pos_org = new Vector [sortspline[highestcp].azcp + 1];
        para->spline[0].pos_new = new Vector [sortspline[highestcp].azcp + 1];
        para->spline[0].pos_changed = new bool [sortspline[highestcp].azcp + 1];
        for (i = 0; i < sortspline[highestcp].azcp; ++i) {
            para->spline[0].hcp.Add(sortspline[highestcp].hcp[i]);
        }
        para->spline[0].azcp = sortspline[highestcp].azcp;
    } else {
        int k;
        if (para->allsplines == 2) {
            //nur Splines mit xx CP's
            int j = 0;
            for (i = 0; i < azspline; ++i) {
                if (sortspline[i].azcp >= para->min_cp)
                    j++;
            }
            if (j == 0) {
                temp.Format("No Splines with %d successively selectetd CP's\nAbort", para->min_cp);
                AfxMessageBox(temp,MB_OK | MB_ICONSTOP);
                delete [] sortspline;
                return false;
            }
            para->spline = new SPLINE[j + 1];
            para->azspline = j;
            j = 0;
            for (i = 0; i < azspline; ++i) {
                if (sortspline[i].azcp >= para->min_cp) {
                    para->spline[j].hsp = sortspline[i].hsp;
                    para->spline[j].pos_org = new Vector [sortspline[i].azcp + 1];
                    para->spline[j].pos_new = new Vector [sortspline[i].azcp + 1];
                    para->spline[j].pos_changed = new bool [sortspline[i].azcp + 1];
                    for (k = 0; k < sortspline[i].azcp; ++k) {
                        para->spline[j].hcp.Add(sortspline[i].hcp[k]);
                    }
                    para->spline[j].azcp = sortspline[i].azcp;
                    j++;
                }
            }
        } else {
            //alle gefundenen
            para->spline = new SPLINE[azspline + 1];
            para->azspline = azspline;
            for (i = 0; i < azspline; ++i) {
                para->spline[i].hsp = sortspline[i].hsp;
                para->spline[i].pos_org = new Vector [sortspline[i].azcp + 1];
                para->spline[i].pos_new = new Vector [sortspline[i].azcp + 1];
                para->spline[i].pos_changed = new bool [sortspline[i].azcp + 1];
                for (k = 0; k < sortspline[i].azcp; ++k) {
                    para->spline[i].hcp.Add(sortspline[i].hcp[k]);
                }
                para->spline[i].azcp = sortspline[i].azcp;
            }
        }
    }

    delete [] sortspline;
    return true;
}

BOOL CSmoothApp::CheckConnect(HModelCache *hmc) const {
    int i, j;

    if (para->azspline == 1) {
        for (i = 1; i < para->spline[0].azcp - 1; ++i) {
            para->spline[0].pos_org[i] = para->spline[0].pos_new[i];
        }
        return TRUE;
    }

    for (j = 0; j < para->azspline - 1; ++j) {
        for (i = j + 1; i < para->azspline; ++i) {
            for (int h = 1; h < para->spline[j].azcp - 1; ++h) {
                if (!para->spline[j].pos_changed[h]) {
                    for (int k = 1; k < para->spline[i].azcp - 1; ++k) {
                        if (!para->spline[i].pos_changed[k]) {
                            if (para->spline[j].pos_org[h] == para->spline[i].pos_org[k]) {
                                const Vector temp = (para->spline[j].pos_new[h] + para->spline[i].pos_new[k]) / 2.F;
                                para->spline[j].pos_org[h] = temp;
                                para->spline[i].pos_org[k] = temp;
                                para->spline[j].pos_changed[h] = true;
                                para->spline[i].pos_changed[k] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    for (j = 0; j < para->azspline; ++j) {
        for (i = 1; i < para->spline[j].azcp - 1; ++i) {
            if (!para->spline[j].pos_changed[i])
                para->spline[j].pos_org[i] = para->spline[j].pos_new[i];
        }
    }
    return TRUE;
}

BOOL CSmoothApp::SetSpline(HModelCache *hmc, const int nr) const {
    for (int i = 1; i < para->spline[nr].azcp - 1; ++i) {
        para->spline[nr].hcp[i]->SetPosition(&para->spline[nr].pos_new[i]);
    }
    return TRUE;
}

BOOL CSmoothApp::ChangeSplinePos(HModelCache *hmc, const int nr) const {
    for (int i = 1; i < para->spline[nr].azcp - 1; ++i) {
        para->spline[nr].pos_org[i] = para->spline[nr].pos_new[i];
    }
    return TRUE;
}

BOOL CSmoothApp::SmoothSpline(HModelCache *hmc, const int nr) const {
    Vector P0, P1;
    HCP *hcp;
    int i;

    auto *v_s1 = new Vector[para->spline[nr].azcp + 1];
    auto *v_s2 = new Vector[para->spline[nr].azcp + 1];
    CArray<HCP *, HCP *> hcp_sp1;
    CArray<HCP *, HCP *> hcp_sp2;

    //1. Spline 1 - 3 - 5 etc
    P0 = para->spline[nr].pos_org[1];
    P1 = para->spline[nr].pos_org[3];
    HSpline *hsp1 = hmc->StartSpline(&P0, &P1);
    HCP *cp1 = hsp1->GetHeadCP()->GetNext();
    for (i = 5; i < para->spline[nr].azcp; i += 2) {
        P0 = para->spline[nr].pos_org[i];
        cp1 = hmc->AddCP(cp1, &P0);
    }
    //Spline1 Mittelpunkte erzeugen
    int azcp1 = 0;
    for (hcp = hsp1->GetHeadCP(); hcp; hcp = hcp->GetNext(), azcp1++) {
        hcp_sp1.Add(hcp);
    }
    for (i = 0; i < azcp1 - 1; ++i) {
        P0 = newPos(hcp_sp1[i], hcp_sp1[i + 1]);
        // ReSharper disable once CppAssignedValueIsNeverUsed
        cp1 = hmc->AddCP(hcp_sp1[i], &P0);
    }

    //2. Spline 0 - 2 - 4 etc
    P0 = para->spline[nr].pos_org[0];
    P1 = para->spline[nr].pos_org[2];
    HSpline *hsp2 = hmc->StartSpline(&P0, &P1);
    cp1 = hsp2->GetHeadCP()->GetNext();
    for (i = 4; i < para->spline[nr].azcp; i += 2) {
        P0 = para->spline[nr].pos_org[i];
        cp1 = hmc->AddCP(cp1, &P0);
    }
    //Spline2 Mittelpunkte erzeugen
    int azcp2 = 0;
    for (hcp = hsp2->GetHeadCP(); hcp; hcp = hcp->GetNext(), azcp2++) {
        hcp_sp2.Add(hcp);
    }
    for (i = 0; i < azcp2 - 1; ++i) {
        P0 = newPos(hcp_sp2[i], hcp_sp2[i + 1]);
        // ReSharper disable once CppAssignedValueIsNeverUsed
        cp1 = hmc->AddCP(hcp_sp2[i], &P0);
    }

    //Positionen Spline1
    i = 0;
    for (cp1 = hsp1->GetHeadCP(); cp1; cp1 = cp1->GetNext(), ++i) {
        v_s1[i] = *cp1->GetModelPosition();
    }
    //Positionen Spline2
    i = 0;
    for (cp1 = hsp2->GetHeadCP(); cp1; cp1 = cp1->GetNext(), ++i) {
        v_s2[i] = *cp1->GetModelPosition();
    }
    //Positionen verechnen fuer Mittelspline
    for (i = 1; i < para->spline[nr].azcp - 1; ++i) {
        if (para->half) {
            para->spline[nr].pos_new[i] = ((v_s1[i - 1] + v_s2[i]) / 2.F + para->spline[nr].pos_org[i]) / 2.F; //50 Prozent
        } else {
            para->spline[nr].pos_new[i] = (v_s1[i - 1] + v_s2[i]) / 2.F;
        }
    }

    if (para->lock_x || para->lock_y || para->lock_z) {
        for (i = 1; i < para->spline[nr].azcp - 1; ++i) {
            if (para->lock_x)
                para->spline[nr].pos_new[i].x = para->spline[nr].pos_org[i].x;
            if (para->lock_y)
                para->spline[nr].pos_new[i].y = para->spline[nr].pos_org[i].y;
            if (para->lock_z)
                para->spline[nr].pos_new[i].z = para->spline[nr].pos_org[i].z;
        }
    }
    // Hilfsspline loeschen
    hmc->DeleteSpline(hsp1);
    hmc->DeleteSpline(hsp2);

    delete [] v_s1;
    delete [] v_s2;
    return TRUE;
}
