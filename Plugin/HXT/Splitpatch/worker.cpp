#include "StdAfx.h"
#include "Splitpatch.h"

Vector midPoint(const Vector A, const Vector B) {
    Vector m = A + B;
    m *= 0.5F;
    return m;
}

Vector deCasteljau(const Vector p1, const Vector p2, const Vector p3, const Vector p4) {
    const Vector l2 = midPoint(p1, p2);
    const Vector h = midPoint(p2, p3);
    const Vector r3 = midPoint(p3, p4);
    const Vector l3 = midPoint(l2, h);
    const Vector r2 = midPoint(h, r3);
    const Vector c = midPoint(l3, r2);
    return c;
}

Vector splineMid(HCP *cp1, HCP *cp2) {
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

HCP *findsecondcp(HCP *cp1, const HCP *cp2) {
    HSpline *hsp = cp1->GetSpline();
    for (HCP *temp = hsp->GetHeadCP(); temp; temp = temp->GetNext()) {
        for (HCP *temp1 = temp->GetHead(); temp1; temp1 = temp1->GetNextAttached()) {
            if (temp1 == cp2)
                return temp;
        }
        if (temp->IsLoop())
            return nullptr;
    }
    return nullptr;
}

BOOL CheckInsert(const PointSP *point, const Vector pos, const int azpoint) {
    if (azpoint == 0)
        return true;
    for (int i = 0; i < azpoint; ++i) {
        if (point[i].pos == pos)
            return false;
    }
    return true;
}

HCP *InsertingCP(HModelCache *hmc, const bool isflip, Vector position, HCP *cp1, HCP *cp2) {
    HSpline *hsp;
    HCP *addedcp;
    if (isflip) {
        if (cp1->IsLoop()) {
            hsp = cp1->GetSpline();
            addedcp = hsp->CreateCPBefore(cp2, position);
        } else {
            addedcp = hmc->InsertCP(&cp1, cp2, &position);
        }
    } else {
        if (cp2->IsLoop()) {
            hsp = cp2->GetSpline();
            addedcp = hsp->CreateCPBefore(cp1, position);
        } else {
            addedcp = hmc->InsertCP(&cp2, cp1, &position);
        }
    }
    return addedcp;
}

void AddToSplines(CArrayEx<nSpline, nSpline> &nspline, const Vector p1, const Vector p2, const Vector p3) {
    nSpline tspline;
    for (int i = 0; i < nspline.GetSize(); ++i) {
        if (nspline[i].pos[0] == p1) {
            nspline[i].pos.InsertAt(0, p2);
            nspline[i].pos.InsertAt(0, p3);
            return;
        }
        if (nspline[i].pos[0] == p3) {
            nspline[i].pos.InsertAt(0, p2);
            nspline[i].pos.InsertAt(0, p1);
            return;
        }
        if (nspline[i].pos[nspline[i].pos.GetSize() - 1] == p1) {
            nspline[i].pos.Add(p2);
            nspline[i].pos.Add(p3);
            return;
        }
        if (nspline[i].pos[nspline[i].pos.GetSize() - 1] == p3) {
            nspline[i].pos.Add(p2);
            nspline[i].pos.Add(p1);
            return;
        }
    }
    tspline.pos.Add(p1);
    tspline.pos.Add(p2);
    tspline.pos.Add(p3);
    nspline.Add(tspline);
}

void AddToSplines(CArrayEx<nSpline, nSpline> &nspline, const Vector p1, const Vector p2) {
    nSpline tspline;
    for (int i = 0; i < nspline.GetSize(); ++i) {
        if (nspline[i].pos[0] == p1) {
            nspline[i].pos.InsertAt(0, p2);
            return;
        }
        if (nspline[i].pos[nspline[i].pos.GetSize() - 1] == p1) {
            nspline[i].pos.Add(p2);
            return;
        }
    }
    tspline.pos.Add(p1);
    tspline.pos.Add(p2);
    nspline.Add(tspline);
}

BOOL CSplitpatchApp::Work(HModelCache *hmc, HGroup *hg) const {
    int azpatches4, azpatches5, aktpatch, azpoint;
    HPatch **sel_patch4{};
    HPatch5 *hp5{}, **sel_patch5{};
    HCP *cp1_0{}, *cp2_0{}, *cp3_0{}, *cp4_0{};
    HCP *cp1_1{}, *cp2_1{}, *cp3_1{}, *cp4_1{};
    Vector mp_spline1, mp_spline2, mp_spline3, mp_spline4, mp_temp, mp_patch;
    Vector cp1_pos, cp2_pos, cp3_pos, cp4_pos;
    //	int i,j;
    HGroupCP *sel{nullptr};
    CString errormsg, temp;
    int id1, id2, id3, id4;
    BOOL ishook;
    CArrayEx<nSpline, nSpline> nspline;
    int azpatches = azpatches5 = azpatches4 = azpoint = 0;
    BOOL model_changed = false;

    hmc->FindPatches();
    azpatches = hmc->GetPatchCount();
    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        if (hg->IsPatchInGroup(hp5)) {
            azpoint += 9;
            azpatches5++;
        }
    }

    if (azpatches > 0) {
        for (aktpatch = 0; aktpatch < azpatches; aktpatch++) {
            if (hg->IsPatchInGroup(hmc->GetPatch(aktpatch))) {
                azpatches4++;
                if (hmc->GetPatch(aktpatch)->GetNumPoints() == 3)
                    azpoint += 7;
                if (hmc->GetPatch(aktpatch)->GetNumPoints() == 4)
                    azpoint += 8;
            }
        }
    }

    if (azpoint == 0) {
        delete para;
        return true;
    }

    if (azpatches4 > 0)
        sel_patch4 = new HPatch *[azpatches4 + 1];
    if (azpatches5 > 0)
        sel_patch5 = new HPatch5 *[azpatches5 + 1];
    auto *point = new PointSP[azpoint * 2LL];
    azpoint = 0;

    if (azpatches5 > 0) {
        azpatches5 = 0;
        for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
            if (hg->IsPatchInGroup(hp5)) {
                sel_patch5[azpatches5] = hp5;
                azpatches5++;
            }
        }
    }

    if (azpatches4 > 0) {
        azpatches4 = 0;
        for (aktpatch = 0; aktpatch < azpatches; aktpatch++) {
            if (hg->IsPatchInGroup(hmc->GetPatch(aktpatch))) {
                sel_patch4[azpatches4] = hmc->GetPatch(aktpatch);
                azpatches4++;
            }
        }
    }
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }
    GetHProject()->DeselectAll();

    if (azpatches5 > 0) {
        Vector mp_spline5;
        for (int i = 0; i < azpatches5; ++i) {
            //5 Point Patches
            ishook = false;
            cp1_0 = sel_patch5[i]->GetCP1();
            if (cp1_0->IsHook())
                ishook = true;
            cp2_0 = sel_patch5[i]->GetCP2();
            if (cp2_0->IsHook())
                ishook = true;
            cp3_0 = sel_patch5[i]->GetCP3();
            if (cp3_0->IsHook())
                ishook = true;
            cp4_0 = sel_patch5[i]->GetCP4();
            if (cp4_0->IsHook())
                ishook = true;
            HCP *cp5_0 = sel_patch5[i]->GetCP5();
            if (cp5_0->IsHook())
                ishook = true;
            cp1_1 = findsecondcp(cp1_0, cp2_0);
            cp2_1 = findsecondcp(cp2_0, cp3_0);
            cp3_1 = findsecondcp(cp3_0, cp4_0);
            cp4_1 = findsecondcp(cp4_0, cp5_0);
            HCP *cp5_1 = findsecondcp(cp5_0, cp1_0);
            if (cp1_1 && cp2_1 && cp3_1 && cp4_1 && cp5_1 && !ishook) {
                cp1_pos = *cp1_0->GetHead()->GetModelPosition();
                cp2_pos = *cp2_0->GetHead()->GetModelPosition();
                cp3_pos = *cp3_0->GetHead()->GetModelPosition();
                cp4_pos = *cp4_0->GetHead()->GetModelPosition();
                Vector cp5_pos = *cp5_0->GetHead()->GetModelPosition();
                if (sel_patch5[i]->IsFlipV1()) {
                    mp_spline1 = splineMid(cp1_0, cp1_1);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline1, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, true, mp_spline1, cp1_0, cp1_1);
                            point[azpoint].pos = mp_spline1;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                } else {
                    mp_spline1 = splineMid(cp1_1, cp1_0);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline1, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, false, mp_spline1, cp1_0, cp1_1);
                            point[azpoint].pos = mp_spline1;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                }
                if (sel_patch5[i]->IsFlipV2()) {
                    mp_spline2 = splineMid(cp2_0, cp2_1);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline2, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, true, mp_spline2, cp2_0, cp2_1);
                            point[azpoint].pos = mp_spline2;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                } else {
                    mp_spline2 = splineMid(cp2_1, cp2_0);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline2, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, false, mp_spline2, cp2_0, cp2_1);
                            point[azpoint].pos = mp_spline2;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                }
                if (sel_patch5[i]->IsFlipV3()) {
                    mp_spline3 = splineMid(cp3_0, cp3_1);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline3, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, true, mp_spline3, cp3_0, cp3_1);
                            point[azpoint].pos = mp_spline3;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                } else {
                    mp_spline3 = splineMid(cp3_1, cp3_0);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline3, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, false, mp_spline3, cp3_0, cp3_1);
                            point[azpoint].pos = mp_spline3;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                }
                if (sel_patch5[i]->IsFlipV4()) {
                    mp_spline4 = splineMid(cp4_0, cp4_1);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline4, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, true, mp_spline4, cp4_0, cp4_1);
                            point[azpoint].pos = mp_spline4;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                } else {
                    mp_spline4 = splineMid(cp4_1, cp4_0);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline4, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, false, mp_spline4, cp4_0, cp4_1);
                            point[azpoint].pos = mp_spline4;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                }
                if (sel_patch5[i]->IsFlipV5()) {
                    mp_spline5 = splineMid(cp5_0, cp5_1);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline5, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, true, mp_spline5, cp5_0, cp5_1);
                            point[azpoint].pos = mp_spline5;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                } else {
                    mp_spline5 = splineMid(cp5_1, cp5_0);
                    if (para->insert) {
                        if (CheckInsert(point, mp_spline5, azpoint)) {
                            point[azpoint].cp = InsertingCP(hmc, false, mp_spline5, cp5_0, cp5_1);
                            point[azpoint].pos = mp_spline5;
                            point[azpoint].attached = para->connect == 0;
                            azpoint++;
                        }
                    }
                }
                mp_temp = (mp_spline1 - cp1_pos + (mp_spline4 - cp5_pos)) * 0.5F;
                mp_temp += (mp_spline2 - cp2_pos + (mp_spline5 - cp1_pos)) * 0.5F;
                mp_temp += (mp_spline3 - cp3_pos + (mp_spline1 - cp2_pos)) * 0.5F;
                mp_temp += (mp_spline4 - cp4_pos + (mp_spline2 - cp3_pos)) * 0.5F;
                mp_temp += (mp_spline5 - cp5_pos + (mp_spline3 - cp4_pos)) * 0.5F;
                mp_temp /= 5;
                mp_patch = (mp_spline1 + mp_spline2 + mp_spline3 + mp_spline4 + mp_spline5) / 5;
                mp_patch += mp_temp;
                AddToSplines(nspline, mp_spline1, mp_patch, mp_spline3);
                AddToSplines(nspline, mp_spline2, mp_patch, mp_spline4);
                AddToSplines(nspline, mp_spline5, mp_patch);
                model_changed = true;
            } else {
                id1 = cp1_0->GetID();
                id2 = cp2_0->GetID();
                id3 = cp3_0->GetID();
                id4 = cp4_0->GetID();
                int id5 = cp5_0->GetID();
                PatchID5 pid5 = sel_patch5[i]->GetPatchID();
                errormsg.Format("Problem\nPatchID %u %u %u %u %u\nPatch not changed\n", pid5.m_id1, pid5.m_id2, pid5.m_id3, pid5.m_id4, pid5.m_id5);
                if (ishook) {
                    if (cp1_0->IsHook()) {
                        temp.Format("cp %d is hook\n", id1);
                        errormsg += temp;
                    }
                    if (cp2_0->IsHook()) {
                        temp.Format("cp %d is hook\n", id2);
                        errormsg += temp;
                    }
                    if (cp3_0->IsHook()) {
                        temp.Format("cp %d is hook\n", id3);
                        errormsg += temp;
                    }
                    if (cp4_0->IsHook()) {
                        temp.Format("cp %d is hook\n", id4);
                        errormsg += temp;
                    }
                    if (cp5_0->IsHook()) {
                        temp.Format("cp %d is hook\n", id5);
                        errormsg += temp;
                    }
                } else {
                    if (cp1_1 == nullptr) {
                        errormsg += "cp1_1 not found\ncp1_0 ID ";
                        temp.Format("%d\n", id1);
                        errormsg += temp;
                    }
                    if (cp2_1 == nullptr) {
                        errormsg += "cp2_1 not found\ncp2_0 ID ";
                        temp.Format("%d\n", id2);
                        errormsg += temp;
                    }
                    if (cp3_1 == nullptr) {
                        errormsg += "cp3_1 not found\ncp3_0 ID ";
                        temp.Format("%d\n", id3);
                        errormsg += temp;
                    }
                    if (cp4_1 == nullptr) {
                        errormsg += "cp4_1 not found\ncp4_0 ID ";
                        temp.Format("%d\n", id4);
                        errormsg += temp;
                    }
                    if (cp5_1 == nullptr) {
                        errormsg += "cp5_1 not found\ncp5_0 ID ";
                        temp.Format("%d\n", id5);
                        errormsg += temp;
                    }
                }
                AfxMessageBox(errormsg, MB_OK & MB_ICONINFORMATION);
            }
        }
    }
    if (azpatches > 0) {
        PatchID pid;
        for (int i = 0; i < azpatches4; ++i) {
            //3 Point Patches
            if (sel_patch4[i]->GetNumPoints() == 3) {
                ishook = false;
                cp1_0 = sel_patch4[i]->GetCP1();
                if (cp1_0->IsHook())
                    ishook = true;
                cp2_0 = sel_patch4[i]->GetCP2();
                if (cp2_0->IsHook())
                    ishook = true;
                cp3_0 = sel_patch4[i]->GetCP3();
                if (cp3_0->IsHook())
                    ishook = true;
                cp1_1 = findsecondcp(cp1_0, cp2_0);
                cp2_1 = findsecondcp(cp2_0, cp3_0);
                cp3_1 = findsecondcp(cp3_0, cp1_0);
                if (cp1_1 && cp2_1 && cp3_1 && !ishook) {
                    cp1_pos = *cp1_0->GetHead()->GetModelPosition();
                    cp2_pos = *cp2_0->GetHead()->GetModelPosition();
                    cp3_pos = *cp3_0->GetHead()->GetModelPosition();
                    if (sel_patch4[i]->IsFlipV1()) {
                        mp_spline1 = splineMid(cp1_0, cp1_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline1, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline1, cp1_0, cp1_1);
                                point[azpoint].pos = mp_spline1;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline1 = splineMid(cp1_1, cp1_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline1, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline1, cp1_0, cp1_1);
                                point[azpoint].pos = mp_spline1;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    if (sel_patch4[i]->IsFlipV2()) {
                        mp_spline2 = splineMid(cp2_0, cp2_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline2, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline2, cp2_0, cp2_1);
                                point[azpoint].pos = mp_spline2;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline2 = splineMid(cp2_1, cp2_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline2, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline2, cp2_0, cp2_1);
                                point[azpoint].pos = mp_spline2;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    if (sel_patch4[i]->IsFlipV3()) {
                        mp_spline3 = splineMid(cp3_0, cp3_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline3, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline3, cp3_0, cp3_1);
                                point[azpoint].pos = mp_spline3;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline3 = splineMid(cp3_1, cp3_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline3, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline3, cp3_0, cp3_1);
                                point[azpoint].pos = mp_spline3;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    mp_patch = (mp_spline1 + mp_spline2 + mp_spline3) / 3;
                    AddToSplines(nspline, mp_spline1, mp_patch, mp_spline3);
                    AddToSplines(nspline, mp_spline2, mp_patch);
                    model_changed = true;
                } else {
                    id1 = cp1_0->GetID();
                    id2 = cp2_0->GetID();
                    id3 = cp3_0->GetID();
                    pid = sel_patch4[i]->GetPatchID();
                    errormsg.Format("Problem\nPatchID %u %u %u %u\nPatch not changed\n", pid.m_id1, pid.m_id2, pid.m_id3, pid.m_id4);
                    if (ishook) {
                        if (cp1_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id1);
                            errormsg += temp;
                        }
                        if (cp2_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id2);
                            errormsg += temp;
                        }
                        if (cp3_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id3);
                            errormsg += temp;
                        }
                    } else {
                        if (cp1_1 == nullptr) {
                            errormsg += "cp1_1 not found\ncp1_0 ID ";
                            temp.Format("%d\n", id1);
                            errormsg += temp;
                        }
                        if (cp2_1 == nullptr) {
                            errormsg += "cp2_1 not found\ncp2_0 ID ";
                            temp.Format("%d\n", id2);
                            errormsg += temp;
                        }
                        if (cp3_1 == nullptr) {
                            errormsg += "cp3_1 not found\ncp3_0 ID ";
                            temp.Format("%d\n", id3);
                            errormsg += temp;
                        }
                    }
                    AfxMessageBox(errormsg, MB_OK & MB_ICONINFORMATION);
                }
            }

            //4 Point Patches
            if (sel_patch4[i]->GetNumPoints() == 4) {
                ishook = false;
                cp1_0 = sel_patch4[i]->GetCP1();
                if (cp1_0->IsHook())
                    ishook = true;
                cp2_0 = sel_patch4[i]->GetCP2();
                if (cp2_0->IsHook())
                    ishook = true;
                cp3_0 = sel_patch4[i]->GetCP3();
                if (cp3_0->IsHook())
                    ishook = true;
                cp4_0 = sel_patch4[i]->GetCP4();
                if (cp4_0->IsHook())
                    ishook = true;
                cp1_1 = findsecondcp(cp1_0, cp2_0);
                cp2_1 = findsecondcp(cp2_0, cp3_0);
                cp3_1 = findsecondcp(cp3_0, cp4_0);
                cp4_1 = findsecondcp(cp4_0, cp1_0);
                if (cp1_1 && cp2_1 && cp3_1 && cp4_1 && !ishook) {
                    cp1_pos = *cp1_0->GetHead()->GetModelPosition();
                    cp2_pos = *cp2_0->GetHead()->GetModelPosition();
                    cp3_pos = *cp3_0->GetHead()->GetModelPosition();
                    cp4_pos = *cp4_0->GetHead()->GetModelPosition();
                    if (sel_patch4[i]->IsFlipV1()) {
                        mp_spline1 = splineMid(cp1_0, cp1_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline1, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline1, cp1_0, cp1_1);
                                point[azpoint].pos = mp_spline1;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline1 = splineMid(cp1_1, cp1_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline1, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline1, cp1_0, cp1_1);
                                point[azpoint].pos = mp_spline1;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    if (sel_patch4[i]->IsFlipV2()) {
                        mp_spline2 = splineMid(cp2_0, cp2_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline2, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline2, cp2_0, cp2_1);
                                point[azpoint].pos = mp_spline2;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline2 = splineMid(cp2_1, cp2_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline2, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline2, cp2_0, cp2_1);
                                point[azpoint].pos = mp_spline2;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    if (sel_patch4[i]->IsFlipV3()) {
                        mp_spline3 = splineMid(cp3_0, cp3_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline3, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline3, cp3_0, cp3_1);
                                point[azpoint].pos = mp_spline3;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline3 = splineMid(cp3_1, cp3_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline3, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline3, cp3_0, cp3_1);
                                point[azpoint].pos = mp_spline3;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    if (sel_patch4[i]->IsFlipV4()) {
                        mp_spline4 = splineMid(cp4_0, cp4_1);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline4, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, true, mp_spline4, cp4_0, cp4_1);
                                point[azpoint].pos = mp_spline4;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    } else {
                        mp_spline4 = splineMid(cp4_1, cp4_0);
                        if (para->insert) {
                            if (CheckInsert(point, mp_spline4, azpoint)) {
                                point[azpoint].cp = InsertingCP(hmc, false, mp_spline4, cp4_0, cp4_1);
                                point[azpoint].pos = mp_spline4;
                                point[azpoint].attached = para->connect == 0;
                                azpoint++;
                            }
                        }
                    }
                    mp_temp = (mp_spline1 - cp1_pos + (mp_spline3 - cp4_pos)) * 0.5F;
                    mp_temp += (mp_spline1 - cp2_pos + (mp_spline3 - cp3_pos)) * 0.5F;
                    mp_temp += (mp_spline2 - cp2_pos + (mp_spline4 - cp1_pos)) * 0.5F;
                    mp_temp += (mp_spline2 - cp3_pos + (mp_spline4 - cp4_pos)) * 0.5F;
                    mp_temp /= 4;
                    mp_patch = (mp_spline1 + mp_spline2 + mp_spline3 + mp_spline4) / 4;
                    mp_patch += mp_temp;
                    AddToSplines(nspline, mp_spline1, mp_patch, mp_spline3);
                    AddToSplines(nspline, mp_spline2, mp_patch, mp_spline4);
                    model_changed = true;
                } else {
                    id1 = cp1_0->GetID();
                    id2 = cp2_0->GetID();
                    id3 = cp3_0->GetID();
                    id4 = cp4_0->GetID();
                    pid = sel_patch4[i]->GetPatchID();
                    errormsg.Format("Problem\nPatchID %u %u %u %u\nPatch not changed\n", pid.m_id1, pid.m_id2, pid.m_id3, pid.m_id4);
                    if (ishook) {
                        if (cp1_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id1);
                            errormsg += temp;
                        }
                        if (cp2_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id2);
                            errormsg += temp;
                        }
                        if (cp3_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id3);
                            errormsg += temp;
                        }
                        if (cp4_0->IsHook()) {
                            temp.Format("cp %d is hook\n", id4);
                            errormsg += temp;
                        }
                    } else {
                        if (cp1_1 == nullptr) {
                            errormsg += "cp1_1 not found\ncp1_0 ID ";
                            temp.Format("%d\n", id1);
                            errormsg += temp;
                        }
                        if (cp2_1 == nullptr) {
                            errormsg += "cp2_1 not found\ncp2_0 ID ";
                            temp.Format("%d\n", id2);
                            errormsg += temp;
                        }
                        if (cp3_1 == nullptr) {
                            errormsg += "cp3_1 not found\ncp3_0 ID ";
                            temp.Format("%d\n", id3);
                            errormsg += temp;
                        }
                        if (cp4_1 == nullptr) {
                            errormsg += "cp4_1 not found\ncp4_0 ID ";
                            temp.Format("%d\n", id4);
                            errormsg += temp;
                        }
                    }
                    AfxMessageBox(errormsg, MB_OK & MB_ICONINFORMATION);
                }
            }
        }
    }

    if (model_changed) {
        HSpline *hsp1;
        for (int i = 0; i < nspline.GetSize(); ++i) {
            hsp1 = hmc->CreateSpline();
            for (int j = 0; j < nspline[i].pos.GetSize(); ++j) {
                point[azpoint].cp = hsp1->CreateCPAtTail(nspline[i].pos[j]);
                point[azpoint].pos = nspline[i].pos[j];
                point[azpoint].attached = false;
                azpoint++;
            }
        }
        //connect CP's
        for (int i = 0; i < azpoint - 1; ++i) {
            for (int j = i + 1; j < azpoint; ++j) {
                if (point[i].cp && point[j].cp && point[i].pos == point[j].pos && !point[i].attached && !point[j].attached) {
                    // attach the points
                    hmc->AttachCPs(point[i].cp, point[j].cp);
                    point[i].attached = true;
                }
            }
        }
        for (hsp1 = hmc->GetHeadSpline(); hsp1; hsp1 = hsp1->GetNextSpline()) {
            for (cp1_0 = hsp1->GetHeadCP(); cp1_0; cp1_0 = cp1_0->GetNext()) {
                cp1_0->AddToGroup(&sel);
                if (cp1_0->IsLoop())
                    break;
            }
        }
        hmc->AddToTemporaryGroup(sel);
        hmc->Update();
        GetHProject()->DeselectAll();
    }

    delete[] point;
    if (azpatches4 > 0)
        delete sel_patch4;
    if (azpatches5 > 0)
        delete sel_patch5;
    for (int i = 0; i < nspline.GetSize(); ++i) {
        nspline[i].pos.RemoveAll();
    }
    nspline.RemoveAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    delete para;
    return TRUE;
}
