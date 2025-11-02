// Textured_Grid.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Textured_Grid.h"
#include "PDialog.h"
#include "F_Protos.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextured_GridApp

BEGIN_MESSAGE_MAP(CTextured_GridApp, CWinApp)
    //{{AFX_MSG_MAP(CTextured_GridApp)
    // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextured_GridApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CTextured_GridApp-Objekt

CTextured_GridApp theApp;

BOOL CTextured_GridApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CTextured_GridApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

static HCP *GetIndexedCP(HSpline *sph, const int index) {
    HCP *cp = sph->GetHeadCP();
    for (int i = 0; cp && i < index; cp = cp->GetNext(), ++i) { }
    return cp;
}

static HSpline *BuildSpline(PParameter *wp, const BOOL vertical, HModelCache *hmc, HSpline **sphptr, const float over, const float from, const float to, const float step) {
    int count = 0;
    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    const int maxindex = ROUNDOFF((to - from) / step);
    constexpr float turboffset = 0.F;
    for (float i = from; count <= maxindex; i += step, ++count) {
        if (vertical) {
            if (count == 0)
                firstpos.Set(turboffset, over, i);
            else
                pos.Set(turboffset, over, i);
        } else {
            // horizontal
            if (count == 0)
                firstpos.Set(i, over, turboffset);
            else
                pos.Set(i, over, turboffset);
        }
        // Begin the spline, must have 2 points or it isn't a spline
        if (count == 1) {
            *sphptr = hmc->StartSpline(&firstpos, &pos);
            lastcp = (*sphptr)->GetHeadCP()->GetNext();
        } else if (count > 1)
            lastcp = hmc->AddCP(lastcp, &pos);
    }
    return *sphptr;
}

void CTextured_GridApp::Glue(HPatch *patch, HDecalStamp *stamp, const float vertical_span, const float horizontal_span, const float start_y, const float start_x, const float ofs_x, const float ofs_y) {
    /*
    0 1 2 3
    11     4
    10     5
    9 8 7 6
    */
    Vector uv[12];
    for (int i = 0; i < 12; ++i) {
        uv->SetZero();
    }

    const float v_add = vertical_span / 3.F;
    const float h_add = horizontal_span / 3.F;

    uv[0].x = start_x - ofs_x;
    uv[0].y = start_y + ofs_y;

    uv[3].x = start_x + horizontal_span - ofs_x;
    uv[3].y = start_y + ofs_y;

    uv[6].x = start_x + horizontal_span - ofs_x;
    uv[6].y = start_y - vertical_span + ofs_y;

    uv[9].x = start_x - ofs_x;
    uv[9].y = start_y - vertical_span + ofs_y;

    for (auto &i: uv) {
        i.x = (i.x - 0.5F) * 0.99F + 0.5F;
        i.y = (i.y - 0.5F) * 0.99F + 0.5F;
    }

    uv[1] = uv[0];
    uv[1].x += h_add;
    uv[2] = uv[1];
    uv[2].x += h_add;

    uv[8] = uv[9];
    uv[8].x += h_add;
    uv[7] = uv[8];
    uv[7].x += h_add;

    uv[10] = uv[9];
    uv[10].y += v_add;
    uv[11] = uv[10];
    uv[11].y += v_add;

    uv[5] = uv[6];
    uv[5].y += v_add;
    uv[4] = uv[5];
    uv[4].y += v_add;

    stamp->AddPatchUV(patch, uv);
}

void CTextured_GridApp::BuildGrid(HModelCache *hmc, int modelnum) const {
    int index;
    float u, v;

    int unumsplines = ROUNDOFF(para->subdiv.x);
    int vnumsplines = ROUNDOFF(para->subdiv.y);

    if (unumsplines == 0)
        unumsplines = 1; //prevent a zero division
    if (vnumsplines == 0)
        vnumsplines = 1;
    const float m_stepwidth = para->size.x / unumsplines;
    const float m_stepheight = para->size.y / vnumsplines;
    unumsplines++;
    vnumsplines++;

    auto **usplines = new HSpline *[unumsplines];
    auto **vsplines = new HSpline *[vnumsplines];

    const float startu = -para->size.x / 2.F;
    const float endu = -startu;
    const float stepu = m_stepwidth;
    const float startv = -para->size.y / 2.F;
    const float endv = -startv;
    const float stepv = m_stepheight;

    // build vertical splines
    for (u = startu, index = 0; index < unumsplines /*u < endu*/; u += stepu, ++index)
        BuildSpline(para, TRUE, hmc, &usplines[index], u, startv, endv, stepv);
// build horizontal splines
    for (v = startv, index = 0; index < vnumsplines /*v < endv*/; v += stepv, ++index)
        BuildSpline(para, FALSE, hmc, &vsplines[index], v, startu, endu, stepu);
// walk through splines and attach CPs

    HGroup *group = hmc->CreateGroup("DecaledGroup");
    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    for (int uindex = 0; uindex < unumsplines; ++uindex) {
        for (int vindex = 0; vindex < vnumsplines; ++vindex) {
            HCP *cp1 = GetIndexedCP(usplines[uindex], vindex);
            HCP *cp2 = GetIndexedCP(vsplines[vindex], uindex);
            if (cp1 && cp2) {
                BOOL cp2deleted = hmc->AttachCPs(cp1, cp2);
                // Note: if AttachCPs causes loopback, A:M deletes tail cp
                // before attaching, so can't add it to group
                group->AddCP(cp1);
                if (!cp2deleted)
                    group->AddCP(cp2);
            }
        }
    }
    delete[] usplines;
    delete[] vsplines;
    hmc->FindPatches();

    const float vertical_span = hash_math::rcp((float)vnumsplines - 1);
    const float horizontal_span = hash_math::rcp((float)unumsplines - 1);
    const int pcount = hmc->GetPatchCount();
    for (int i = 0; i < pcount; ++i) {
        HPatch *patch = hmc->GetPatch(i);
        patch->ReverseNormal();
    }

    if (para->use_offset_first) {
        modelnum += 1;
    }
    const float ofs_x = para->offset.x * modelnum;
    const float ofs_y = para->offset.y * modelnum;

    HDecal *decal = hmc->AddDecal(para->clip);
    HDecalStamp *stamp1 = decal->AddDecalStamp();
    float start_y = 1.F;
    float start_x = 0.F;
    for (int i = 0; i < pcount; ++i) {
        HPatch *patch = hmc->GetPatch(i);
        Glue(patch, stamp1, vertical_span, horizontal_span, start_y, start_x, ofs_x, ofs_y);
        start_y -= vertical_span;
        if (start_y <= 0.F) {
            start_x += horizontal_span;
            start_y = 1.F;
        }
    }

    if (ofs_y != 0) {
        start_y = 1.F;
        start_x = 0.F;
        HDecalStamp *stamp = decal->AddDecalStamp();
        for (int i = 0; i < pcount; ++i) {
            HPatch *patch = hmc->GetPatch(i);
            Glue(patch, stamp, vertical_span, horizontal_span, start_y, start_x, ofs_x, ofs_y - 1.F);
            start_y -= vertical_span;
            if (start_y <= 0.F) {
                start_x += horizontal_span;
                start_y = 1.F;
            }
        }
    }

    if (ofs_x != 0) {
        start_y = 1.F;
        start_x = 0.F;
        HDecalStamp *stamp = decal->AddDecalStamp();
        for (int i = 0; i < pcount; ++i) {
            HPatch *patch = hmc->GetPatch(i);
            Glue(patch, stamp, vertical_span, horizontal_span, start_y, start_x, ofs_x - 1.F, ofs_y);
            start_y -= vertical_span;
            if (start_y <= 0.F) {
                start_x += horizontal_span;
                start_y = 1.F;
            }
        }
    }

    if (ofs_x != 0 && ofs_y != 0) {
        start_y = 1.F;
        start_x = 0.F;
        HDecalStamp *stamp = decal->AddDecalStamp();
        for (int i = 0; i < pcount; ++i) {
            HPatch *patch = hmc->GetPatch(i);
            Glue(patch, stamp, vertical_span, horizontal_span, start_y, start_x, ofs_x - 1.F, ofs_y - 1.F);
            start_y -= vertical_span;
            if (start_y <= 0.F) {
                start_x += horizontal_span;
                start_y = 1.F;
            }
        }
    }

    //    Matrix34 *groupmatrix = group->GetMatrix();
    HGroupCP *lastgroup = group->GetGroupCP();
    //    Vector position, direction;
    Matrix34 matrix = Identity34();
    switch (para->m_orientation) {
        case 0:
            matrix = Rotate2V(Vector(0, 0, 0), Vector(0, 0, 1)); //FrontView original
            break;
        case 1:
            matrix = Rotate2V(Vector(0, 0, -1), Vector(0, 0, 1)); //BackView
            break;
        case 2:
            matrix = Rotate2V(Vector(1, 0, 0), Vector(0, 0, 1)); //LeftView
            break;
        case 3:
            matrix = Rotate2V(Vector(-1, 0, 0), Vector(0, 0, 1)); //RightView
            break;
        case 4:
            matrix = Rotate2V(Vector(0, -1, 0), Vector(0, 0, 1)); //TopView
            break;
        case 5:
            matrix = Rotate2V(Vector(0, 1, 0), Vector(0, 0, 1)); //BottomView
            break;
    }
    HGroupCP *currentgroupcp = lastgroup;
    while (currentgroupcp) {
        HCP *cp = currentgroupcp->GetCP();
        Vector pos = *cp->GetPosition();
        pos *= matrix;
        cp->SetPosition(&pos);
        currentgroupcp = currentgroupcp->GetNext();
    }

    hmc->OnModified();
    hmc->SetChanged();
}

BOOL CTextured_GridApp::OnPrimitiveWizard() {
    HProject *project = GetHProject();
    HClipCacheContainer *hclipcache = project->GetChildClipCacheContainer();

    para = new PParameter;
    para->clip = nullptr;
    para->hclipcache = hclipcache;
    PDialog pdlg(para);

    if (pdlg.DoModal() != IDOK) {
        delete para->clip;
        RefreshAllTrees();
        delete para;
        return TRUE;
    }
    HModelCache *hmc;
    HModelCache *hmc_first = hmc = HModelCache::New(para->modelname.Get(), TRUE);
    BuildGrid(hmc, 0);
    for (int i = 1; i < para->num_models; ++i) {
        hmc = HModelCache::New(para->modelname.Get(), TRUE);
        BuildGrid(hmc, i);
    }
    hmc_first->OpenView(para->m_orientation);
    delete para;
    return TRUE;
}
