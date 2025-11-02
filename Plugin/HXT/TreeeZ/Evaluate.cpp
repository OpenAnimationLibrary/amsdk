// KB  6/4/01  \Ken90\Plugin\HXT\Duplicator\Evaluate.cpp
// Z 04-03-18 ZPiDER/Marcel Bricman/kci:dnd

#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
//#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HChor.h"
#include "SDK/HProject.h"
#include "SDK/HDecal.h"

//-------------------------------------------------------------------------- H E L P E R S

// returns the group named like <name>
HGroup *FindGroup(HModelCache *hmc, const String &name) {
    try {
        if (hmc->GetChildGroupContainer())
            return (HGroup *)hmc->GetChildGroupContainer()->FindChildByName(name.Get_const_char());
        return nullptr;
    }
    catch (...) { }
    return nullptr;
}

void setCPdecoration(HCP *cp, const float value) {
    cp->SetInAlpha(1.F + value);
}

float getCPdecoration(HCP *cp) {
    return cp->GetInAlpha() - 1.F;
}

void transformGroup(HGroupCP *gcp, const float s, const Vector r, const Vector t, const float along) {
    while (gcp) {
        HCP *cp = gcp->GetCP();
        Vector cppos = *cp->GetPosition();
        cppos *= ScaleV(Vector(s));
        cppos *= Rotate2V(Vector(0.F, 1.F, 0.F), r);
        cppos *= TranslateV(t);
        cp->SetPosition(&cppos);

        // decorate cps with level info
        setCPdecoration(cp, along);

        gcp = gcp->GetNext();
    }
}

HGroup *getGroup(HModelCache *hmc, const String &name) {
    HGroup *group = FindGroup(hmc, name);
    if (group == nullptr)
        group = hmc->CreateGroup(name);
    return group;
}

void addGroupCPsToGroup(HGroupCP *from, HGroup *to) {
    while (from && to) {
        HCP *cp = from->GetCP();
        to->AddCP(cp);
        from = from->GetNext();
    }
}

//-------------------------------------------------------------------------- C L U S T E R I N G
// clustered tracking

struct PointTreeZ {
    int id{};
    HCP *cp{};
    Vector pos{};
    int depth{};
    int parent{};
    int child1{};
    int child2{};
    BOOL done{};
};

typedef CMap<int, int, PointTreeZ, PointTreeZ> PointMap;
typedef CMap<int, int, HCP *, HCP *> CPMap;

int maxid = 0;
#ifdef _DEBUG
BOOL debug = FALSE;
BOOL debugfine = FALSE;
#endif
HChor *chor = nullptr;

// collects all leaves descending of p into pointMap
void collect(const int start, PointMap &pointMap, PointMap &output) {
#ifdef _DEBUG
    if (debugfine == TRUE) {
        const String s = "collecting " + String(start);
        AfxMessageBox(TEXT(s.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
    }
#endif
    const PointTreeZ *p = &pointMap[start];
    if (p != nullptr && p->id != 0) {
        if (p->cp != nullptr) {
            output.SetAt(p->id, *p);
        } else {
            collect(p->child1, pointMap, output);
            collect(p->child2, pointMap, output);
        }
    }
}

// clean pointmap (remove internal nodes)
void clean(PointMap &pointMap, const int depth) {
    int id = 0;
#ifdef _DEBUG
    int count = 0;
    int count2 = 0;
#endif
    const auto time = Time(depth, GetHProject()->GetFPS());
    chor->CreateFrame(time);

    PointTreeZ t;
    POSITION pos = pointMap.GetStartPosition();
    while (pos != nullptr) {
        pointMap.GetNextAssoc(pos, id, t);
        if (t.cp == nullptr) {
            pointMap.RemoveKey(id);
#ifdef _DEBUG
            count ++;
#endif
        } else {
            if (pointMap[id].cp) {
                pointMap[id].pos = *pointMap[id].cp->GetWorldPosition();
            }
            pointMap[id].done = FALSE;
#ifdef _DEBUG
            count2 ++;
#endif
        }
    }
#ifdef _DEBUG
    if (debug == TRUE) {
        const String s = "cleaned: " + String(count) + " inner nodes removed, " + String(count2) + " leaf nodes cleaned.";
        AfxMessageBox(TEXT(s.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
    }
#endif
}

PointTreeZ *cluster(PointMap &pointMap, const Vector startPos, const float locality, const float regularity, const int depth) {
    clean(pointMap, depth);

    if (pointMap.GetCount() == 1) {
        PointTreeZ t;
        int id;
        POSITION pos = pointMap.GetStartPosition();
        pointMap.GetNextAssoc(pos, id, t);
        return &pointMap[id];
    }

    int dummy = 0;

    int id = maxid;
    auto *p = new PointTreeZ();
    while (pointMap.GetCount() > 1) {
        // find 2 closest points
        PointTreeZ p1, p2, t1, t2;
        p1.id = 0;
        float mindist = 9999999.0F;
        POSITION pos1 = pointMap.GetStartPosition();
        while (pos1 != nullptr) {
            pointMap.GetNextAssoc(pos1, dummy, t1);
            if (t1.done == FALSE) {
                POSITION pos2 = pos1;
                while (pos2 != nullptr) {
                    pointMap.GetNextAssoc(pos2, dummy, t2);
                    if (t2.done == FALSE) {
                        Vector t1t2 = t1.pos - t2.pos;

                        // decision locality
                        Vector t12 = (t1.pos + t2.pos) / 2;
                        Vector startt12 = startPos - t12;
                        const float dist = t1t2.Norm() * (1.F - locality) - startt12.Norm() * locality;

                        // add a random value (how large? based on startt12?) to dist to make clustering unsharp

                        if (dist < mindist) {
                            p1 = t1;
                            p2 = t2;
                            mindist = dist;
                        }
                    }
                }
            }
        }
        if (p1.id != 0) {
            // collapse points
            id++;
            p->id = id;
            p->cp = nullptr;

            //p->pos = (p1.pos + p2.pos) / 2;
            // weighted branching:
            p->pos = (p1.pos * (p1.depth * regularity + 1) + p2.pos * (p2.depth * regularity + 1)) / (2 + p1.depth * regularity + p2.depth * regularity);

            p->depth = MAX(p1.depth, p2.depth) + 1;
            p->child1 = p1.id;
            p1.parent = p->id;
            pointMap[p1.id].done = TRUE;
            p->child2 = p2.id;
            p2.parent = p->id;
            pointMap[p2.id].done = TRUE;
            p->done = FALSE;
            pointMap.SetAt(p->id, *p);
#ifdef _DEBUG
            if (debugfine == TRUE) {
                String s = "clustering " + String(p1.id) + " and " + String(p2.id) + " into " + String(p->id);
                AfxMessageBox(TEXT(s.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
            }
#endif
        } else {
            break;
        }
    }
#ifdef _DEBUG
    if (debug == TRUE) {
        const String s = "clustered: " + String(id - maxid) + " inner nodes (" + String((int)pointMap.GetCount()) + " total nodes)";
        AfxMessageBox(TEXT(s.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
    }
#endif
    return p;
}

//-------------------------------------------------------------------------- B R A N C H

float getPropertyValue(const HFloatProperty *hfp, const float defaultValue, const float time) {
    if (hfp != nullptr) {
        const auto t = Time(time);
        return hfp->GetValue(t);
    }
    return defaultValue;
}

float calcThickness(const HFloatProperty *hfp, const float along) {
    return getPropertyValue(hfp, along, 1.F - along);
}

float calcBranchlength(const HFloatProperty *hfp, const float along) {
    return getPropertyValue(hfp, 0.25F, along);
}

float calcLocality(const HFloatProperty *hfp, const float along) {
    return getPropertyValue(hfp, 0.F, along);
}

float calcRegularity(const HFloatProperty *hfp, const float along) {
    return getPropertyValue(hfp, 0.F, along);
}

int estimatedtotaldepth = 0;
int totaldepth = 0;

int branch(HModelCache *hmc, HActionCache *hac, HFloatProperty *p_thickness, HFloatProperty *p_branchlength, HFloatProperty *p_locality, HFloatProperty *p_regularity, HGroupCP *hg, const Vector lastPos, const Vector lastDir, PointMap &pointMap, const int depth, const BOOL mainbranch = TRUE) // returns total depth
{
    PointMap pointMapA;
    PointMap pointMapB;
    pointMapA.InitHashTable(997);
    pointMapB.InitHashTable(997);

    // transform "base" group
    if (depth == 0)
        transformGroup(hg, calcThickness(p_thickness, 1.F), lastDir, lastPos, 1.F);

    float along = 0.F;
    if (estimatedtotaldepth > 0)
        along = (float)depth / (float)estimatedtotaldepth;

    const PointTreeZ *p = cluster(pointMap, lastPos, calcLocality(p_locality, along), calcRegularity(p_regularity, along), depth);
    if (p->depth > estimatedtotaldepth)
        estimatedtotaldepth = p->depth;

    //float offshootBaseScale;// = 0.75f / (float)estimatedtotaldepth;
    //float mainIntBaseScale;// = 0.5f / (float)estimatedtotaldepth;

    if (depth > totaldepth)
        totaldepth = depth;

    collect(p->child1, pointMap, pointMapA);

#ifdef _DEBUG
    if (debug == TRUE) {
        const String str = "collected into A: " + String((int)pointMapA.GetCount()) + " leaves.";
        AfxMessageBox(TEXT(str.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
    }
#endif
    collect(p->child2, pointMap, pointMapB);

#ifdef _DEBUG
    if (debug == TRUE) {
        const String str = "collected into B: " + String((int)pointMapB.GetCount()) + " leaves.";
        AfxMessageBox(TEXT(str.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
    }
#endif
    Vector pos = lastPos + (p->pos - lastPos) * calcBranchlength(p_branchlength, (float)depth / (float)(p->depth + 1));
    Vector dir = pos - lastPos;

    HGroupCP *newgroup = nullptr;
    HGroupCP *newintgroup = nullptr;

    // draw branch from previous towards target plus branching part
    hmc->CopyExtrude(TRUE, hg, &newintgroup);
    hmc->CopyExtrude(TRUE, newintgroup, &newgroup);

    // TODO: add some random factor to (p->child1.dir) and (p->child2.dir)

    int childdepth = 0;
    int td = estimatedtotaldepth;

    if (p->cp == nullptr) // inner branch
    {
        int d1, d2;
        if (pointMap[p->child1].depth > pointMap[p->child2].depth) // switch main branch to deeper subtree
        {
            d1 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapA, depth + 1);
            d2 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapB, depth + 1, FALSE);
        } else {
            d2 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapB, depth + 1); // needs to be ordered first to take first extrusion
            d1 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapA, depth + 1, FALSE);
        }

        childdepth = MAX(d1, d2);

        td = totaldepth;
    } else // leaf branch
    {
        //		pos = p->pos;	// the leaf goes right to the target cp

        const Vector leafPos1 = pos + dir; // double of regular branch length
        const Vector leafDir1 = dir * 2.;
        const Vector leafPos2 = p->pos; // straight to target cp
        const Vector leafDir2 = leafPos2 - lastPos;
        if (leafDir2.Norm() < leafDir1.Norm()) // if target cp is closer than double regular length
        {
            pos = leafPos2;
            dir = leafDir2;
        } else {
            pos = leafPos1;
            dir = leafDir1;
        }
    }

    td += 1;
//    int branchdepth = childdepth + depth;

    const float branchScale = (float)childdepth / (float)td;

    transformGroup(newgroup, calcThickness(p_thickness, branchScale), dir, pos, branchScale);

    const String name = "level" + String(childdepth);
    HGroup *g = getGroup(hmc, name);

    if (mainbranch == FALSE) {
        const float offshootBaseScale = 0.75F / (float)td;
        transformGroup(newintgroup, calcThickness(p_thickness, branchScale + offshootBaseScale), (dir + lastDir) / 2, (pos + lastPos * 3. + lastDir) / 4, branchScale + offshootBaseScale);
    } else {
        const float mainIntBaseScale = 0.5F / (float)td;
        transformGroup(newintgroup, calcThickness(p_thickness, branchScale + mainIntBaseScale), (dir * 2. + lastDir) / 3, lastPos + (lastDir + dir) / 4, branchScale + mainIntBaseScale);
    }

    addGroupCPsToGroup(hg, g);
    addGroupCPsToGroup(newgroup, g);
    addGroupCPsToGroup(newintgroup, g);

    return childdepth + 1;
}

//-------------------------------------------------------------------------- D E C A L I N G

void addPatchUV(HPatch *patch, HDecalStamp *hds, int id) {
    Vector uv[12];

    for (auto &i: uv) {
        i.SetZero();
    }
    const float depth1 = getCPdecoration(patch->GetCP1()->GetHead());
    const float depth2 = getCPdecoration(patch->GetCP2()->GetHead());
    const float depth3 = getCPdecoration(patch->GetCP3()->GetHead());
    const float depth4 = getCPdecoration(patch->GetCP4()->GetHead());

    const float depthA = MIN(MIN(depth1, depth2), depth3);
    const float depthB = MAX(MAX(depth1, depth2), depth3);

    uv[0].y = depth1;
    uv[3].y = depth2;
    uv[6].y = depth3;
    uv[9].y = depth4;

    if (uv[0].y == uv[3].y && uv[0].y == depthA) {
        uv[0].x = 0.F;
        uv[3].x = 1.F;
    }
    if (uv[0].y == uv[3].y && uv[0].y == depthB) {
        uv[0].x = 1.F;
        uv[3].x = 0.F;
    }
    if (uv[3].y == uv[6].y && uv[3].y == depthA) {
        uv[3].x = 0.F;
        uv[6].x = 1.F;
    }
    if (uv[3].y == uv[6].y && uv[3].y == depthB) {
        uv[3].x = 1.F;
        uv[6].x = 0.F;
    }
    if (uv[6].y == uv[9].y && uv[6].y == depthA) {
        uv[6].x = 0.F;
        uv[9].x = 1.F;
    }
    if (uv[6].y == uv[9].y && uv[6].y == depthB) {
        uv[6].x = 1.F;
        uv[9].x = 0.F;
    }
    if (uv[9].y == uv[0].y && uv[9].y == depthA) {
        uv[9].x = 0.F;
        uv[0].x = 1.F;
    }
    if (uv[9].y == uv[0].y && uv[9].y == depthB) {
        uv[9].x = 1.F;
        uv[0].x = 0.F;
    }

    // correct overshoot
    for (auto &i: uv) {
        i.x = (i.x - 0.5F) * 0.99F + 0.5F;
        i.y = (i.y - 0.5F) * 0.99F + 0.5F;
    }

    // set between points to form straight line
    constexpr float a = 1.F;
    constexpr float b = 3.0F;
    uv[1] = (uv[0] * a + uv[3] * b) / (a + b);
    uv[2] = (uv[0] * b + uv[3] * a) / (a + b);
    uv[4] = (uv[3] * a + uv[6] * b) / (a + b);
    uv[5] = (uv[3] * b + uv[6] * a) / (a + b);
    uv[7] = (uv[6] * a + uv[9] * b) / (a + b);
    uv[8] = (uv[6] * b + uv[9] * a) / (a + b);
    uv[10] = (uv[9] * a + uv[0] * b) / (a + b);
    uv[11] = (uv[9] * b + uv[0] * a) / (a + b);

    hds->AddPatchUV(patch, uv);
}

void makeStamps(HModelCache *hmc, int patchesBefore) {
    HDecalContainer *hdc = hmc->GetChildDecalContainer();
    if (hdc == nullptr)
        return;
    HDecal *hd = hdc->GetChildDecal();
    if (hd == nullptr)
        return;
    //HDecal *hd = hmc->AddDecal();

    HDecalStamp *hds = hd->AddDecalStamp();

    for (UINT p = 0; p < hmc->GetPatchCount(); p++) {
        HPatch *patch = hmc->GetPatch(p);
        if (getCPdecoration(patch->GetCP1()->GetHead()) >= 0.F)
            if (patch != nullptr)
                addPatchUV(patch, hds, p);
    }

    // TODO: remove cp decoration (set inAlpha = 0 for all cps)
}

//-------------------------------------------------------------------------- M A I N

BOOL CHxtApp::TreeeZ(HModelCache *hmc, HActionCache *hac) {
    estimatedtotaldepth = 0;
    totaldepth = 0;
    PointMap pointMap;
    pointMap.InitHashTable(997);

    HSpline *spline = hmc->GetHeadSpline();
    while (spline != nullptr) {
        HCP *ccp = spline->GetHeadCP();
        while (ccp != nullptr) {
            HCP *cp = ccp;
            if (cp == ccp->GetHead()) {
                const int id_local = cp->GetID();
                if (id_local > maxid) {
                    maxid = id_local;
                }
                PointTreeZ p{};
                p.id = id_local;
                p.cp = cp;
                p.pos = *cp->GetPosition();
                p.done = FALSE;
                p.depth = 0;
                pointMap.SetAt(id_local, p);
            }
            if (ccp->IsLoop())
                break;
            ccp = ccp->GetNext();
        }
        spline = spline->GetNextSpline();
    }
    const String groupname = "base";
    HGroup *basegroup = FindGroup(hmc, groupname);
    if (basegroup == nullptr) {
        AfxMessageBox(TEXT("\"base\" group missing."), MB_OK | MB_ICONSTOP, 0);
        return TRUE;
    }
    CWaitCursor wait;
    for (HGroupCP *gcp = basegroup->GetGroupCP(); gcp; gcp = gcp->GetNext()) {
        HCP *cp = gcp->GetCP();
        if (cp == cp->GetHead()) {
            pointMap.RemoveKey(cp->GetID());
        }
    }
#ifdef _DEBUG
    if (debug == TRUE) {
        constexpr int id1 = 0;
        const String s = "input: " + String(id1) + " leaf nodes";
        AfxMessageBox(TEXT(s.Get_const_char()), MB_OK | MB_ICONSTOP, 0);
    }
#endif
    hmc->SetChanged();
    hmc->FindPatches();
    GetHProject()->UpdateAllViews();
    const int patchesBefore = hmc->GetPatchCount();

    // get properties
    HFloatProperty *p_thickness = nullptr;
    HFloatProperty *p_branchlength = nullptr;
    HFloatProperty *p_locality = nullptr;
    HFloatProperty *p_regularity = nullptr;
    HModel *hm = hac->EditWithModelCache(hmc);

    // create new chor with instance of model
    chor = hm->GetChor();

    try {
        //	HHashObject *hucp = (HHashObject *)hm->GetUserCategoryProperty(); // husercategoryproperty
        //	HHashObject *hucp = (HHashObject *)hm->FindChildByName("User Properties");	// TODO: try this. this might be compatible to versions prior to 11

        int i = 0;
        HHashObject *hucp = hm->GetPropertyAt(i);
        char *nameptr;
        while (hucp != nullptr && strcmp(nameptr = hucp->GetName(), "User Properties") != 0) {
            hucp = (HHashObject *)hm->GetPropertyAt(++i);
        }

        if (hucp) {
            p_thickness = (HFloatProperty *)hucp->FindChildByName("thickness");
            p_branchlength = (HFloatProperty *)hucp->FindChildByName("branchlength");
            p_locality = (HFloatProperty *)hucp->FindChildByName("locality");
            p_regularity = (HFloatProperty *)hucp->FindChildByName("regularity");
        }
    }
    catch (...) {}

    HGroupCP *newbase = nullptr;
    hmc->CopyExtrude(FALSE, basegroup->GetGroupCP(), &newbase); // copy the base

    branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newbase, Vector(0, 0, 0), Vector(0, 1, 0), pointMap, 0);

    try {
        hac->EndEditWithModelCache(hm);
    }
    catch (...) {}

    const String info = "TreeeZ 0.3\n(c) 2004 by kci:dnd\nMarcel Bricman\nhttp://www.kci-group.com/z/\n\nGenerated eZTree with " + String(totaldepth) + " levels.";  
    AfxMessageBox(info.Get(), MB_OK | MB_ICONINFORMATION, 0);

    hmc->SetChanged();
    hmc->FindPatches();
    GetHProject()->UpdateAllViews();
    makeStamps(hmc, patchesBefore);

    hmc->SetChanged(TRUE);
    GetHProject()->UpdateAllViews(TRUE);
    return TRUE;
}
