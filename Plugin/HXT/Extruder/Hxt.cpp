// Dan  3/24/2003  \DanLP105\Plugin\HXT\Extruder\Hxt.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "ExtruderDialog.h"
#include "Matrix34.h"
#include "SDK/HProject.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHxtApp

BEGIN_MESSAGE_MAP(CHxtApp, CWinApp)
    //{{AFX_MSG_MAP(CHxtApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHxtApp construction

CHxtApp::CHxtApp() = default;

CHxtApp::~CHxtApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CHxtApp object

CHxtApp theApp;

BOOL CHxtApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

typedef struct structCP {
    Vector pos;
    HCP *cp{};
} typeCP;

BOOL CHxtApp::OnExtruderWizard(HModelCache *hmc, HGroup *hg) {
    if (!hmc)
        hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);

    CExtruderDialog dlg(hmc, hg);
    if (dlg.DoModal() != IDOK || !dlg.m_hpathgroup || !dlg.m_hxsectiongroup)
        return TRUE;

    HGroupCP *hgcp = dlg.m_hpathgroup->GetGroupCP();
    if (!hgcp)
        return FALSE;

    HCP *hcp = hgcp->GetCP();
    HSpline *hspline = hcp->GetSpline();
    if (!hspline)
        return FALSE;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }

    //change instances , if any, for preventing nonetheless realocation musclecp data
    BOOL chor_changed = hmc->IsInChorOrAction();
    HModelCache *hmc_temp = nullptr;
    if (chor_changed) {
        hmc_temp = HModelCache::New("temp__extmodel", true);
        hmc->ChangeShortCuts(hmc_temp);
    }

    hmc->MakeCurrent();

    hcp = hspline->GetHeadCP();
    int cpnum = 0;
    BOOL islooped = FALSE;
    if (dlg.m_method == EXTRUDE) {
        for (HCP *cp1 = hspline->GetHeadCP(); cp1; cp1 = cp1->GetNext()) {
            cpnum++;
            if (cp1->IsLoop()) {
                islooped = TRUE;
                break;
            }
        }
    }

    float sumlength = 0;
    float pathlength = hspline->GetLength();

    HGroupCP *lastgroup = dlg.m_hxsectiongroup->GetGroupCP();
    Matrix34 *groupmatrix = dlg.m_hxsectiongroup->GetMatrix();

    Vector position, direction;
    Matrix34 matrix = Identity34();

    // compute a matrix that will put the cross-section in local space
    matrix.SetTranslate(-groupmatrix->GetTranslate());

    int count = 0;
    float step = dlg.m_extrusiondistance / pathlength;
    Vector pos;
    BOOL lastone = FALSE;
    while (TRUE) {
        // move group to local space
        HGroupCP *currentgroupcp = lastgroup;
        while (currentgroupcp) {
            HCP *cp = currentgroupcp->GetCP();
            pos = *cp->GetPosition();
            pos *= matrix;
            cp->SetPosition(&pos);
            currentgroupcp = currentgroupcp->GetNext();
        }
        float ease;
        switch (dlg.m_extrusionmethod) {
            case COUNT:
                ease = (float)count / (dlg.m_extrusioncount - 1);
                if (count == dlg.m_extrusioncount - 1)
                    lastone = TRUE;
                break;
            case DISTANCE:
                ease = step * count;
                if (ease > 1.F) {
                    ease = 1.F;
                    lastone = TRUE;
                }
                break;
            case EVERYCP:
                if (sumlength == 0.F) {
                    ease = 0.F;
                } else {
                    ease = sumlength / pathlength;
                }
                sumlength += hcp->GetDistance();
                if (ease > 1.F)
                    ease = 1.F;
                hcp = hcp->GetNext();
                if (dlg.m_method == 1) {
                    if (count == cpnum)
                        lastone = TRUE;
                } else {
                    if (count == cpnum - 1)
                        lastone = TRUE;
                }
                if (!hcp)
                    lastone = TRUE;
                break;
            default: 
                ease = 0.F;
        }

        count++;

        // compute a matrix that will put the cross-section in path space @ property percentage along it
        hspline->GetPositionAndDirection(ease, position, direction);
        matrix = Rotate2V(Vector(direction.x, direction.y, -direction.z), Vector(0.F, 0.F, 1.F));
        matrix.SetTranslate(position);

        // move group to path space
        currentgroupcp = lastgroup;
        while (currentgroupcp) {
            HCP *cp = currentgroupcp->GetCP();
            pos = *cp->GetPosition();
            pos *= matrix;
            cp->SetPosition(&pos);
            currentgroupcp = currentgroupcp->GetNext();
        }

        if (lastone)
            break;

        // copy or extrude another cross-section and go through again
        HGroupCP *newgroup = nullptr;
        hmc->CopyExtrude(dlg.m_method, lastgroup, &newgroup);

        // set the matrix back to what will put the cross-section in local space
        matrix = matrix.Inverse();
        lastgroup = newgroup;
    }

    GetHProject()->DeselectAll();

    if (dlg.m_looped && islooped && dlg.m_method == EXTRUDE) {
        typeCP tempCP;
        std::vector<typeCP> cpcoord;
        HGroupCP *currentgroupcp = lastgroup;
        HSpline *attspl = nullptr;
        while (currentgroupcp) {
            HCP *cp = currentgroupcp->GetCP();
            pos = *cp->GetPosition();
            HCP *attach = cp->GetNextAttached();
            currentgroupcp = currentgroupcp->GetNext();
            if (attach) {
                attspl = cp->GetSpline();
                hmc->DetachCP(attach);
                tempCP.pos = pos;
                tempCP.cp = attach;
                cpcoord.push_back(tempCP);
            }
        }
        if (attspl) {
            hmc->DeleteSpline(attspl);
            hmc->Update();
            currentgroupcp = dlg.m_hxsectiongroup->GetGroupCP();
            while (currentgroupcp) {
                HCP *cp = currentgroupcp->GetCP();
                pos = *cp->GetPosition();
                currentgroupcp = currentgroupcp->GetNext();
                for (size_t i = 0; i < cpcoord.size(); ++i) {
                    Vector pos1 = cpcoord[i].pos;
                    if (pos1.IsEqual(pos, 1e-5F)) {
                        HCP *cp1 = cpcoord[i].cp;
                        hmc->AttachCPs(cp1, cp);
                        break;
                    }
                }
            }
        }
    }

    hmc->FindPatches();
    hmc->Update();
    if (chor_changed) {
        hmc_temp->ChangeShortCuts(hmc);
        HProject::DeleteHandle(hmc_temp);
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

int CHxtApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
