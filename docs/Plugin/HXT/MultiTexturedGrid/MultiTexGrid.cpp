// MultiTexGrid.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "MultiTexGrid.h"
#include "PDialog.h"
#include "F_Protos.h"
#include "SDK/HLayer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiTexGridApp

BEGIN_MESSAGE_MAP(CMultiTexGridApp, CWinApp)
    //{{AFX_MSG_MAP(CMultiTexGridApp)
    // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiTexGridApp Konstruktion

CMultiTexGridApp::CMultiTexGridApp() = default;

CMultiTexGridApp::~CMultiTexGridApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMultiTexGridApp-Objekt

CMultiTexGridApp theApp;

BOOL CMultiTexGridApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMultiTexGridApp::ExitInstance() {
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
    for (float i = from; count <= maxindex; i += step, ++count) {
        constexpr float turboffset = 0.F;
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

void CMultiTexGridApp::Glue(HPatch *patch, HDecalStamp *stamp, const float vertical_span, const float horizontal_span, const float start_y, const float start_x) {
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

    uv[0].x = start_x;
    uv[0].y = start_y;

    uv[3].x = start_x + horizontal_span;
    uv[3].y = start_y;

    uv[6].x = start_x + horizontal_span;
    uv[6].y = start_y - vertical_span;

    uv[9].x = start_x;
    uv[9].y = start_y - vertical_span;

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

void CMultiTexGridApp::BuildGrid(HModelCache *hmc, const int modelnum) const {
    int index;
    float u, v;

    int unumsplines = ROUNDOFF(para->subdiv.x);
    int vnumsplines = ROUNDOFF(para->subdiv.y);

    if (unumsplines == 0)
        unumsplines = 1; //prevent a zero division
    if (vnumsplines == 0)
        vnumsplines = 1;
    const float m_stepwidth = para->images[modelnum].gridsize.x / unumsplines;
    const float m_stepheight = para->images[modelnum].gridsize.y / vnumsplines;
    unumsplines++;
    vnumsplines++;

    auto **usplines = new HSpline *[unumsplines];
    auto **vsplines = new HSpline *[vnumsplines];

    const float startu = -para->images[modelnum].gridsize.x / 2.F;
    const float endu = -startu;
    const float stepu = m_stepwidth;
    const float startv = -para->images[modelnum].gridsize.y / 2.F;
    const float endv = -startv;
    const float stepv = m_stepheight;

    // build vertical splines
    for (u = startu, index = 0; index < unumsplines; u += stepu, ++index)
        BuildSpline(para, TRUE, hmc, &usplines[index], u, startv, endv, stepv);
// build horizontal splines
    for (v = startv, index = 0; index < vnumsplines; v += stepv, ++index)
        BuildSpline(para, FALSE, hmc, &vsplines[index], v, startu, endu, stepu);
// walk through splines and attach CPs

    HGroup *group = hmc->CreateGroup("DecaledGroup");
    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    for (int uindex = 0; uindex < unumsplines; ++uindex) {
        for (int vindex = 0; vindex < vnumsplines; ++vindex) {
            HCP *cp1 = GetIndexedCP(usplines[uindex], vindex);
            HCP *cp2 = GetIndexedCP(vsplines[vindex], uindex);
            if (cp1 && cp2) {
                const BOOL cp2deleted = hmc->AttachCPs(cp1, cp2);
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
    HClip *clip = para->hclipcache->CreateClip(para->images[modelnum].filename.Get(), para->images[modelnum].issequence);
    HDecal *decal = hmc->AddDecal(clip);
    if (para->create_cookie) {
        HDecalClip *hdc = decal->GetChildDecalClipContainer()->GetChildDecalClip();
        if (hdc) {
            hdc->GetKind()->StoreValue(Time(), HDecalClip::COOKIECUTMAP, FALSE);
        }
    }
    HDecalStamp *stamp1 = decal->AddDecalStamp();
    float start_y = 1.F;
    float start_x = 0.F;
    for (int i = 0; i < pcount; ++i) {
        HPatch *patch = hmc->GetPatch(i);
        Glue(patch, stamp1, vertical_span, horizontal_span, start_y, start_x);
        start_y -= vertical_span;
        if (start_y <= 0.F) {
            start_x += horizontal_span;
            start_y = 1.F;
        }
    }

    HGroupCP *lastgroup = group->GetGroupCP();
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

BOOL CMultiTexGridApp::OnChor(HChor *hchor) {
    HProject *project = GetHProject();
    HClipCacheContainer *hclipcache = project->GetChildClipCacheContainer();

    para = new PParameter;
    para->hclipcache = hclipcache;
    para->fpos.Set(0.F);
    para->pos_ofs.Set(0.F);
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        RefreshAllTrees();
        delete para;
        return TRUE;
    }

    if (!para->use_model) {
        Vector chor_pos;
        HModel *hm;
        for (size_t i = 0; i < para->images.size(); ++i) {
            HModelCache *hmc = HModelCache::New(para->modelname.Get(), TRUE);
            BuildGrid(hmc, i);
            if (para->add_to_chor) {
                if (i == 0) {
                    chor_pos = para->fpos;
                    hm = hmc->NewInstance(hchor);
                    hm->OnModified();
                    hm->GetTransform()->GetTranslate()->StoreValue(Time(), chor_pos, FALSE);
                } else {
                    chor_pos += para->pos_ofs;
                    switch (para->m_orientation) {
                        case 0:
                            chor_pos.x += para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 1:
                            chor_pos.x -= para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 2:
                            chor_pos.z += para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 3:
                            chor_pos.z -= para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 4:
                            chor_pos.y += para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 5:
                            chor_pos.y -= para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                    }
                    hm = hmc->NewInstance(hchor);
                    hm->OnModified();
                    hm->GetTransform()->GetTranslate()->StoreValue(Time(), chor_pos, FALSE);
                }
            }
        }
    } else {
        Vector chor_pos;
        for (size_t i = 0; i < para->images.size(); ++i) {
            HClip *clip = hclipcache->CreateClip(para->images[i].filename.Get(), para->images[i].issequence);
            HLayerCache *layer = HLayerCache::New(para->modelname.Get(), clip, para->images[i].gridsize.x, para->images[i].gridsize.y);
            if (para->add_to_chor) {
                if (i == 0) {
                    chor_pos = para->fpos;
                    HLayer *hlc = layer->NewInstance(hchor);
                    hlc->GetTransform()->GetTranslate()->StoreValue(Time(), chor_pos, FALSE);
                } else {
                    chor_pos += para->pos_ofs;
                    switch (para->m_orientation) {
                        case 0:
                            chor_pos.x += para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 1:
                            chor_pos.x -= para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 2:
                            chor_pos.z += para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 3:
                            chor_pos.z -= para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 4:
                            chor_pos.y += para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                        case 5:
                            chor_pos.y -= para->images[i - 1].gridsize.x / 2 + para->images[i].gridsize.x / 2;
                            break;
                    }
                    HLayer *hlc = layer->NewInstance(hchor);
                    hlc->GetTransform()->GetTranslate()->StoreValue(Time(), chor_pos, FALSE);
                }
            }
        }
    }
    project->UpdateAllViews(true);
    RefreshAllTrees();
    delete para;
    return TRUE;
}
