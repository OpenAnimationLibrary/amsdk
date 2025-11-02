// ResampleSpline.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "ResampleSpline.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResampleSplineApp

BEGIN_MESSAGE_MAP(CResampleSplineApp, CWinApp)
        //{{AFX_MSG_MAP(CResampleSplineApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResampleSplineApp Konstruktion
CResampleSplineApp::CResampleSplineApp() = default;

CResampleSplineApp::~CResampleSplineApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CResampleSplineApp-Objekt

CResampleSplineApp theApp;

BOOL CResampleSplineApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CResampleSplineApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

/*
float Distance(Vector v) { return v.Norm(); }
float Distance(Vector v1, Vector v2) { return Distance(v2 - v1); }

Vector midPoint(Vector A, Vector B) {
    Vector m;
    m = A + B;
    m *= 0.5F;
    return m;
}

Vector newPos(HCP* cp1, HCP* cp2) {

    Vector p1 = *cp1->GetHead()->GetModelPosition();
    Vector p2 = cp1->GetModelInTangent();
    Vector p3 = cp2->GetModelOutTangent();
    Vector p4 = *cp2->GetHead()->GetModelPosition();
    Vector l2 = midPoint(p1, p2);
    Vector h = midPoint(p2, p3);
    Vector r3 = midPoint(p3, p4);
    Vector l3 = midPoint(l2, h);
    Vector r2 = midPoint(h, r3);
    Vector c = midPoint(l3, r2);
    return c;
}

Vector subdivideSegment(Vector pos_cp1, Vector it_cp1, Vector ot_cp2, Vector pos_cp2, float factor) {
    Vector a, b, c, p;
    c = 3 * (it_cp1 - pos_cp1);
    b = 3 * (ot_cp2 - it_cp1) - c;
    a = pos_cp2 - pos_cp1 - c - b;
    p = a * factor * factor * factor + b *factor * factor + c * factor + pos_cp1;
    return p;
}


float MeasureSpline(HCP *cp, int &cpcount) {
    HSpline *hsp;
    CArray <HCP *, HCP *> cparray;
    HCP *cp1, *cp2, *tempcp;
    Vector pos, pos_cp1, it_cp1, pos_cp2, ot_cp2, pos_old;
    float length = 0.F;

    hsp = cp->GetSpline();
    for (cp1 = hsp->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
        cparray.Add(cp1);
        if (cp1->IsLoop())
            break;
    }
    cpcount = cparray.GetSize();
    HModelCache *hmc = HModelCache::New("Temp", TRUE);
    hsp = hmc->CreateSpline();
    tempcp = nullptr;
    int	subdiv = 20;
    float subdiv_factor = 1.F / subdiv;
    for (int i = 1; i < cparray.GetSize(); ++i) {
        cp1 = cparray[i - 1];
        cp2 = cparray[i];
        pos = *cp1->GetModelPosition();
        tempcp = hsp->CreateCPAfter(tempcp, pos);
        pos_cp1 = *cp1->GetModelPosition();
        it_cp1 = cp1->GetModelInTangent();
        pos_cp2 = *cp2->GetModelPosition();
        ot_cp2 = cp2->GetModelOutTangent();
        pos_old = pos;
        for (int j = 0; j <= subdiv; ++j) {
            pos = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, subdiv_factor*j);
            length += Distance(pos_old, pos);
            tempcp = hsp->CreateCPAfter(tempcp, pos);
            pos_old = pos;
        }
    }
    cp1 = cparray[cparray.GetSize() - 1];
    pos = *cp1->GetModelPosition();
    tempcp = hsp->CreateCPAfter(tempcp, pos);
    length += Distance(pos_old, pos);
    HProject::DeleteHandle(hmc);
    //    hmc->DeleteSpline(hsp);
    return length;
}
*/

float MeasureSpline(HCP *cp, int &cpcount) {
    HSpline *spline = cp->GetSpline();
    int num_cp = 0;
    for (HCP *cp1 = spline->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
        num_cp++;
        if (cp1->IsLoop())
            break;
    }
    cpcount = num_cp;
    return spline->GetLength();
}

BOOL CResampleSplineApp::OnCP(HCP *cp) const {

    HTreeObject *parent = cp->GetParent();
    do {
        parent = parent->GetParent();
    } while (parent != nullptr && parent->GetObjectType() != HOT_MODEL);
    if (!parent) {
        AfxMessageBox("model not found", MB_OK);
        return TRUE;
    }
    auto *para = new PARAMETER;

    para->splinelength = MeasureSpline(cp, para->cpcount);
    para->neededdistance = GetRegistryValue("ResampleSpline HXT", "distance", 0.5F);
    para->iteration = RoundValue(para->splinelength / para->neededdistance);
    para->neededdistance = para->splinelength / para->iteration;
    para->zcount = -1;
    para->zvalue = 0.5F;
    para->extrude = FALSE;
    para->direction = 2;

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }

    //    GetHProject()->DeselectAll();
    CArray<Vector, Vector> pos_array;
    Vector pos, dir;
    const float ease = hash_math::rcp((float)para->iteration);
    const int iteration = para->iteration + 1;
    auto *hm = (HModel *)parent;
    hm->MakeCurrent();
    HSpline *spline_org = cp->GetSpline();
    for (int i = 0; i < iteration; ++i) {
        spline_org->GetPositionAndDirection(ease * i, pos, dir);
        pos_array.Add(pos);
    }

    HModelCache *hmc_neu = HModelCache::New("resampledspline", TRUE);
    HSpline *hsp = hmc_neu->CreateSpline();
    HCP *tempcp = nullptr;
    for (int i = 0; i < pos_array.GetCount(); ++i) {
        tempcp = hsp->CreateCPAfter(tempcp, pos_array[i]);
    }

    BOOL spline_islooped = FALSE;
    for (HCP *hcp2 = cp; hcp2; hcp2 = hcp2->GetNext()) {
        if (hcp2->IsLoop()) {
            spline_islooped = TRUE;
            break;
        }
    }
    if (spline_islooped) {
        hsp->DeleteCP(tempcp);
        hsp->MakeLooped(TRUE);
    }
    delete para;
    hmc_neu->Update();
    hmc_neu->OpenView(4);
    GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

BOOL CResampleSplineApp::OnCPInstance(HCPInstance *cp) const {

    HTreeObject *parent = cp->GetParent();
    do {
        parent = parent->GetParent();
    } while (parent != nullptr && parent->GetObjectType() != HOT_MODEL);
    if (!parent) {
        AfxMessageBox("model not found", MB_OK);
        return TRUE;
    }
    auto *para = new PARAMETER;
    HCP *hcp2 = cp->GetCP();
    para->splinelength = MeasureSpline(hcp2, para->cpcount);
    para->neededdistance = GetRegistryValue("ResampleSpline HXT", "distance", 0.5F);
    para->iteration = RoundValue(para->splinelength / para->neededdistance);
    para->neededdistance = para->splinelength / para->iteration;
    para->zcount = -1;
    para->zvalue = 0.5F;
    para->extrude = FALSE;
    para->direction = 2;

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }

    auto *spline_org = (HSplineInstance *)cp->GetTreeParent();
    CArray<Vector, Vector> pos_array;
    Vector pos, dir;
    const float ease = hash_math::rcp((float)para->iteration);
    const int iteration = para->iteration + 1;
    for (int i = 0; i < iteration; ++i) {
        spline_org->GetPositionAndDirection(ease * i, pos, dir);
        pos_array.Add(pos);
    }

    HModelCache *hmc_neu = HModelCache::New("resampledspline", TRUE);
    HSpline *hsp = hmc_neu->CreateSpline();
    HCP *tempcp = nullptr;
    for (int i = 0; i < pos_array.GetCount(); ++i) {
        tempcp = hsp->CreateCPAfter(tempcp, pos_array[i]);
    }

    BOOL spline_islooped = FALSE;
    for (HCP *hcp = cp->GetCP(); hcp; hcp = hcp->GetNext()) {
        if (hcp->IsLoop()) {
            spline_islooped = TRUE;
            break;
        }
    }
    if (spline_islooped) {
        hsp->DeleteCP(tempcp);
        hsp->MakeLooped(TRUE);
    }
    delete para;
    hmc_neu->Update();
    hmc_neu->OpenView(4);
    GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

void AddGroupCPToGroup(HGroupCP *hgcp, HGroup *hg) {
    while (hgcp) {
        hg->AddCP(hgcp->GetCP());
        hgcp = hgcp->GetNext();
    }
}

BOOL CResampleSplineApp::OnGroup(HGroup *hg) const {
    HCP *hcp2, *tempcp = nullptr;
    HCP *hcp1 = hcp2 = hg->GetGroupCP()->GetCP();
    HCPInstance *cpi = hcp1->GetCPInstance();
    if (!hg->GetGroupCP()->GetNext()) {
        if (cpi)
            return OnCPInstance(cpi);
        return OnCP(hcp1);
    }
    HGroupCP *accumgroup = nullptr;

    auto *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
    HSpline *spline_org = hcp1->GetSpline();

    auto *para = new PARAMETER;

    para->splinelength = MeasureSpline(hcp2, para->cpcount);
    para->neededdistance = GetRegistryValue("ResampleSpline HXT", "distance", 0.5F);
    para->iteration = RoundValue(para->splinelength / para->neededdistance);
    para->neededdistance = para->splinelength / para->iteration;
    para->zcount = GetRegistryValue("ResampleSpline HXT", "extrude count", 1);
    para->zvalue = GetRegistryValue("ResampleSpline HXT", "extrude distance", 0.5F);
    para->extrude = GetRegistryValue("ResampleSpline HXT", "extruding", FALSE);
    para->direction = GetRegistryValue("ResampleSpline HXT", "extrude direction", 1);

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }

    if (!hmc)
        hmc = HModelCache::New("newmodel", TRUE);
    else {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }

    GetHProject()->DeselectAll();
    hmc->MakeCurrent();
    const float ease = hash_math::rcp((float)para->iteration);
    const int iteration = para->iteration + 1;
    Vector pos;
    HSpline *hsp = hmc->CreateSpline();
    for (int i = 0; i < iteration; ++i) {
        Vector dir;
        spline_org->GetPositionAndDirection(ease * i, pos, dir);
        tempcp = hsp->CreateCPAfter(tempcp, pos);
    }
    hcp1 = spline_org->GetHeadCP();
    BOOL spline_islooped = FALSE;
    for (hcp2 = hcp1; hcp2; hcp2 = hcp2->GetNext()) {
        if (hcp2->IsLoop()) {
            spline_islooped = TRUE;
            break;
        }
    }
    if (spline_islooped) {
        hsp->DeleteCP(tempcp);
        hsp->MakeLooped(TRUE);
    }
    if (!para->extrude) {
        hmc->Update();
        delete para;
        GetHProject()->DeselectAll();
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        return TRUE;
    }
    for (tempcp = hsp->GetHeadCP(); tempcp; tempcp = tempcp->GetNext()) {
        tempcp->AddToGroup(&accumgroup);
        if (tempcp->IsLoop())
            break;
    }
    hmc->AddToTemporaryGroup(accumgroup);
    HGroupCP *currentgroup = accumgroup;
    for (int i = 0; i < para->zcount; ++i) {
        HGroupCP *newgroup = nullptr;
        hmc->CopyExtrude(true, currentgroup, &newgroup);
        currentgroup = newgroup;
        HGroupCP *currentgroupcp = currentgroup;
        while (currentgroupcp) {
            HCP *cp = currentgroupcp->GetCP();
            pos = *cp->GetPosition();
            switch (para->direction) {
                case 0:
                    pos.x += para->zvalue;
                    break;
                case 1:
                    pos.y += para->zvalue;
                    break;
                case 2:
                    pos.z += para->zvalue;
                    break;
            }
            cp->SetPosition(&pos);
            currentgroupcp = currentgroupcp->GetNext();
        }
    }
    delete para;
    hmc->Update();
    GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}
