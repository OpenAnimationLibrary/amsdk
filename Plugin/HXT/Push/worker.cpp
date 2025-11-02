#include "StdAfx.h"
#include "Push.h"
#include <Matrix34.h>
#include <SDK/HAction.h>
#include <SDK/HChor.h>
#include <SDK/HPatch.h>
#include <SDK/HRelatio.h>

void MoveCP(HCP *cp, const Vector &normal, const float pushSize, HCPInstance *cpinstance, const Time time) {
    HCP *headcp = cp->GetHead();
    const Vector orgPos = *headcp->GetWorldPosition();
    if (cpinstance) {
        const Vector newPos = orgPos + normal * pushSize;
        const Vector diffPos = newPos - orgPos;
        cpinstance->GetPosition()->StoreValue(time, diffPos, FALSE); //Pose, Action
    } else {
        Vector newPos = orgPos + normal * pushSize;
        headcp->SetPosition(&newPos);
    }
}

void MoveCPAction(HCP *cp, const Vector &normal, const float pushSize, HCPInstance *cpinstance, const Time time) {
    if (cpinstance) {
        HCP *headcp = cp->GetHead();
        const Vector orgPos = *headcp->GetWorldPosition();
        const Vector newPos = orgPos + normal * pushSize;
        const Vector diffPos = newPos - orgPos;
        cpinstance->GetPosition()->StoreValue(time, diffPos, FALSE); //Pose, Action
    }
}

Vector GetNormalfromPoint(HCP *cp, HPatch *hp, const Matrix34 &matrix) {
    const Vector position = *cp->GetPosition();
    const Vector worldposition = *cp->GetScreenPosition();
    Vector normal;

    const UINT id = cp->GetID();
    Vector pospatch = hp->GetPointOnPatch(0, 0);
    if (pospatch == position) {
        hp->GetPointNormalOnPatch(0, 0, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(0, 0, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    pospatch = hp->GetPointOnPatch(1, 0);
    if (pospatch == position) {
        hp->GetPointNormalOnPatch(1, 0, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(1, 0, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    pospatch = hp->GetPointOnPatch(0, 1);
    if (pospatch == position) {
        hp->GetPointNormalOnPatch(0, 1, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(0, 1, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    pospatch = hp->GetPointOnPatch(1, 1);
    if (pospatch == position) {
        hp->GetPointNormalOnPatch(1, 1, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(1, 1, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    const String error = "Normal not calculated for CP " + (String)id;
    AfxMessageBox(error.Get(), MB_OK);
    return normal;
}

Vector GetNormalfromPointInstance(HCP *cp, HPatch *hp, const Matrix34 &matrix) {
    const Vector position = *cp->GetPosition();
    const Vector worldposition = *cp->GetScreenPosition();
    const Vector actionposition = *cp->GetWorldPosition();
    Vector normal;

    const UINT id = cp->GetID();

    Vector pospatch = hp->GetPointOnPatch(0, 0);
    if (pospatch == position || pospatch == actionposition) {
        hp->GetPointNormalOnPatch(0, 0, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(0, 0, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    pospatch = hp->GetPointOnPatch(1, 0);
    if (pospatch == position || pospatch == actionposition) {
        hp->GetPointNormalOnPatch(1, 0, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(1, 0, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    pospatch = hp->GetPointOnPatch(0, 1);
    if (pospatch == position || pospatch == actionposition) {
        hp->GetPointNormalOnPatch(0, 1, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(0, 1, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    pospatch = hp->GetPointOnPatch(1, 1);
    if (pospatch == position || pospatch == actionposition) {
        hp->GetPointNormalOnPatch(1, 1, normal);
        return normal;
    }
    if (pospatch == worldposition) {
        hp->GetPointNormalOnPatch(1, 1, normal);
        normal *= matrix;
        normal.Normalize();
        return normal;
    }

    const String error = "Normal not calculated for CP " + (String)id;
    AfxMessageBox(error.Get(), MB_OK);
    return normal;
}

void CPushApp::CalculateAllNormals() {

    AllCPs.InitHashTable(997);


    Matrix34 matrix;
    matrix.SetIdentity();
    HBone *hb = para->hmc->GetCurrentBone();
    if (hb) {
        matrix = hb->GetScreenToModelMatrix();
    }

    for (UINT i = 0; i < para->hmc->GetPatchCount(); ++i) {
        HPatch *hp = para->hmc->GetPatch(i);
        HCP *p1 = hp->GetCP1();
        HCP *p2 = hp->GetCP2();
        HCP *p3 = hp->GetCP3();
        HCP *p4 = hp->GetCP4();
        Vector n1 = GetNormalfromPoint(p1, hp, matrix);
        Vector n2 = GetNormalfromPoint(p2, hp, matrix);
        Vector n3 = GetNormalfromPoint(p3, hp, matrix);
        AllCPs.SetAt(p1, n1);
        AllCPs.SetAt(p2, n2);
        AllCPs.SetAt(p3, n3);
        if (p1 != p4) {
            Vector n4 = GetNormalfromPoint(p4, hp, matrix);
            AllCPs.SetAt(p4, n4);
            if (p4 != p4->GetHead()) {
                p4 = p4->GetHead();
                n4 = GetNormalfromPoint(p4, hp, matrix);
                AllCPs.SetAt(p4, n4);
            }
        }
        if (p1 != p1->GetHead()) {
            p1 = p1->GetHead();
            n1 = GetNormalfromPoint(p1, hp, matrix);
            AllCPs.SetAt(p1, n1);
        }
        if (p2 != p2->GetHead()) {
            p2 = p2->GetHead();
            n2 = GetNormalfromPoint(p2, hp, matrix);
            AllCPs.SetAt(p2, n2);
        }
        if (p3 != p3->GetHead()) {
            p3 = p3->GetHead();
            n3 = GetNormalfromPoint(p3, hp, matrix);
            AllCPs.SetAt(p3, n3);
        }
    }
}

void CPushApp::CalculateAllNormalsInstance() {
    AllCPs.InitHashTable(997);


    Matrix34 matrix;
    matrix.SetIdentity();
    HBone *hb = para->hmc->GetCurrentBone();
    if (hb)
        matrix = hb->GetScreenToModelMatrix();

    for (UINT i = 0; i < para->hmc->GetPatchCount(); ++i) {
        HPatch *hp = para->hmc->GetPatch(i);
        HCP *p1 = hp->GetCP1();
        HCP *p2 = hp->GetCP2();
        HCP *p3 = hp->GetCP3();
        HCP *p4 = hp->GetCP4();
        Vector n1 = GetNormalfromPointInstance(p1, hp, matrix);
        Vector n2 = GetNormalfromPointInstance(p2, hp, matrix);
        Vector n3 = GetNormalfromPointInstance(p3, hp, matrix);
        AllCPs.SetAt(p1, n1);
        AllCPs.SetAt(p2, n2);
        AllCPs.SetAt(p3, n3);
        if (p1 != p4) {
            Vector n4 = GetNormalfromPointInstance(p4, hp, matrix);
            AllCPs.SetAt(p4, n4);
            if (p4 != p4->GetHead()) {
                p4 = p4->GetHead();
                n4 = GetNormalfromPointInstance(p4, hp, matrix);
                AllCPs.SetAt(p4, n4);
            }
        }
        if (p1 != p1->GetHead()) {
            p1 = p1->GetHead();
            n1 = GetNormalfromPointInstance(p1, hp, matrix);
            AllCPs.SetAt(p1, n1);
        }
        if (p2 != p2->GetHead()) {
            p2 = p2->GetHead();
            n2 = GetNormalfromPointInstance(p2, hp, matrix);
            AllCPs.SetAt(p2, n2);
        }
        if (p3 != p3->GetHead()) {
            p3 = p3->GetHead();
            n3 = GetNormalfromPointInstance(p3, hp, matrix);
            AllCPs.SetAt(p3, n3);
        }
    }
}

BOOL CPushApp::WorkInstance(HActionCache *hactioncache, HChor *hchor, const BOOL isaction) {
    Vector vec;
    HCP *cp;
    float mul;
    const float fps = GetHProject()->GetFPS();
    Time time;
    HCPInstance *cpinstance;

    if (isaction) {
        HActionCache *hac = hactioncache;
        HModel *hm = hac->EditWithModelCache(para->hmc);
        HChor *hc = hm->GetChor();
        const Time currenttime = hac->GetChor()->GetTime();
        time.SetFrame(para->frame[0], fps);
        if (time != currenttime) {
            hc->CreateFrame(currenttime);
        }
        hc->CreateFrame(time);
        hc->SetTime(currenttime);
        CalculateAllNormalsInstance();
        mul = para->distance[0];
        for (int i = 0; i < groupcps.GetSize(); ++i) {
            cp = groupcps[i];
            if (AllCPs.Lookup(cp, vec)) {
                cpinstance = cp->GetCPInstance();
                if (!cpinstance) {
                    cpinstance = cp->CreateCPInstance();
                }
                if (currenttime != Time()) {
                    MoveCPAction(cp, vec, 0, cpinstance, currenttime);
                }
                MoveCPAction(cp, vec, mul, cpinstance, time);
            }
        }
        hac->EndEditWithModelCache(hm);
        hac->OnModified();
    } else {
        HChor *hc = hchor;
        const Time currenttime = hc->GetTime();
        time.SetFrame(para->frame[0], fps);
        if (time != currenttime) {
            hc->CreateFrame(currenttime);
        }
        hc->CreateFrame(time);
        hc->SetTime(currenttime);
        CalculateAllNormalsInstance();
        mul = para->distance[0];
        for (int i = 0; i < groupcps.GetSize(); ++i) {
            cp = groupcps[i];
            if (AllCPs.Lookup(cp, vec)) {
                cpinstance = cp->GetCPInstance();
                if (!cpinstance) {
                    cpinstance = cp->CreateCPInstance();
                }
                if (currenttime != Time()) {
                    MoveCPAction(cp, vec, 0, cpinstance, currenttime);
                }
                MoveCPAction(cp, vec, mul, cpinstance, time);
            }
        }
        hc->OnModified();
        hc->SetTime(currenttime);
    }

    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return TRUE;
}

BOOL CPushApp::Work() {
    Vector vec;
    HCP *cp;
    float mul;
    const float fps = GetHProject()->GetFPS();
    Time time;
    HCPInstance *cpinstance;
    const String actionname = para->hmc->GetMatchName() + "_Push";
    CalculateAllNormals();
    switch (para->makekeys) {
        case 0:
        {
            mul = para->distance[0];
            for (int i = 0; i < groupcps.GetSize(); ++i) {
                cp = groupcps[i];
                if (AllCPs.Lookup(cp, vec)) {
                    MoveCP(cp, vec, mul, nullptr, Time());
                }
            }
            para->hmc->SetChanged(true);
        }
        break;
        case 1:
        {
            HPercentProperty *driving = HPercentProperty::New();
            HUserCategoryProperty *usercategory = para->hmc->CreateUserCategoryProperty();
            usercategory->AddUserProperty(driving, actionname.Get(), TRUE);
            auto *info = (HPercentPropertyInfo *)driving->GetPropertyInfo();
            if (para->pose0)
                info->SetMinValue(-1.F);
            else
                info->SetMinValue(0.F);
            info->SetDefaultValue(0.F);
            HRelationContainer *rcc = para->hmc->CreateRelationContainer();
            HRelation *relation = rcc->CreateRelation(driving);
            HModel *hm = relation->StartEdit();
            HUserCategoryProperty *usercategoryinstance = hm->GetUserCategoryProperty();
            auto *drivinginstance = (HPercentProperty *)usercategoryinstance->GetPropertyAt(driving->GetIndex());
            time.SetFrame(0, fps);
            if (para->pose0) {
                //Pose -100 -> 100
                drivinginstance->StoreValue(time, -1.F);
                drivinginstance->Interpolate(time);
                mul = para->distance[0];
                for (int i = 0; i < groupcps.GetSize(); ++i) {
                    cp = groupcps[i];
                    if (AllCPs.Lookup(cp, vec)) {
                        cpinstance = cp->GetCPInstance();
                        if (!cpinstance) {
                            cpinstance = cp->CreateCPInstance();
                        }
                        MoveCP(cp, vec, mul, cpinstance, time);
                    }
                }
                drivinginstance->StoreValue(time, 0.F);
                drivinginstance->Interpolate(time);
                mul = para->distance[1];
                for (int i = 0; i < groupcps.GetSize(); ++i) {
                    cp = groupcps[i];
                    if (AllCPs.Lookup(cp, vec)) {
                        cpinstance = cp->GetCPInstance();
                        if (!cpinstance) {
                            cpinstance = cp->CreateCPInstance();
                        }
                        MoveCP(cp, vec, mul, cpinstance, time);
                    }
                }
                drivinginstance->StoreValue(time, 1.F);
                drivinginstance->Interpolate(time);
                mul = para->distance[2];
                for (int i = 0; i < groupcps.GetSize(); ++i) {
                    cp = groupcps[i];
                    if (AllCPs.Lookup(cp, vec)) {
                        cpinstance = cp->GetCPInstance();
                        if (!cpinstance) {
                            cpinstance = cp->CreateCPInstance();
                        }
                        MoveCP(cp, vec, mul, cpinstance, time);
                    }
                }
            } else {
                //Pose 0 -> 100
                drivinginstance->StoreValue(time, 0.F);
                drivinginstance->Interpolate(time);
                mul = para->distance[0];
                for (int i = 0; i < groupcps.GetSize(); ++i) {
                    cp = groupcps[i];
                    if (AllCPs.Lookup(cp, vec)) {
                        cpinstance = cp->GetCPInstance();
                        if (!cpinstance) {
                            cpinstance = cp->CreateCPInstance();
                        }
                        MoveCP(cp, vec, mul, cpinstance, time);
                    }
                }
                drivinginstance->StoreValue(time, 1.F);
                drivinginstance->Interpolate(time);
                mul = para->distance[1];
                for (int i = 0; i < groupcps.GetSize(); ++i) {
                    cp = groupcps[i];
                    if (AllCPs.Lookup(cp, vec)) {
                        cpinstance = cp->GetCPInstance();
                        if (!cpinstance) {
                            cpinstance = cp->CreateCPInstance();
                        }
                        MoveCP(cp, vec, mul, cpinstance, time);
                    }
                }
            }
            drivinginstance->SetValue(0.F);
            relation->EndEdit(hm);
        }
        break;
        case 2:
        {
            HActionCache *hac = HActionCache::New(actionname.Get(), TRUE, TRUE);
            HModel *hm = hac->EditWithModelCache(para->hmc);
            hac->SetDefaultModelCache(para->hmc);
            HChor *hc = hm->GetChor();
            for (int j = 0; j < 10; ++j) {
                if (!para->keyframe[j])
                    continue;
                time.SetFrame(para->frame[j], fps);
                hc->CreateFrame(time);
                mul = para->distance[j];
                for (int i = 0; i < groupcps.GetSize(); ++i) {
                    cp = groupcps[i];
                    if (AllCPs.Lookup(cp, vec)) {
                        cpinstance = cp->GetCPInstance();
                        if (!cpinstance) {
                            cpinstance = cp->CreateCPInstance();
                        }
                        MoveCP(cp, vec, mul, cpinstance, time);
                    }
                }
            }
            hac->EndEditWithModelCache(hm);
            hac->ExpandInProjectBar(true);
        }
        break;
    }

    AllCPs.RemoveAll();
    return TRUE;
}
