// ReSurface.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "ReSurface.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReSurfaceApp

BEGIN_MESSAGE_MAP(CReSurfaceApp, CWinApp)
        //{{AFX_MSG_MAP(CReSurfaceApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReSurfaceApp Konstruktion
CReSurfaceApp::CReSurfaceApp() = default;

CReSurfaceApp::~CReSurfaceApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CReSurfaceApp-Objekt

CReSurfaceApp theApp;

BOOL CReSurfaceApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CReSurfaceApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

void CReSurfaceApp::LoadSettings() {
    para = new PARAMETER;
    para->distance = GetRegistryValue("Resurface HXT", "distance", 1.F);
    para->instancing = GetRegistryValue("Resurface HXT", "instancing", false);
    para->reversenormal = GetRegistryValue("Resurface HXT", "reversenormal", false);
    para->maxdistance = GetRegistryValue("Resurface HXT", "maxhitdistance", 100.F);
    para->usegroupcenter = GetRegistryValue("Resurface HXT", "groupcenter", false);
    para->ignore_x = GetRegistryValue("Resurface HXT", "ignore_x", false);
    para->ignore_y = GetRegistryValue("Resurface HXT", "ignore_y", false);
    para->ignore_z = GetRegistryValue("Resurface HXT", "ignore_z", false);
    para->isinchor = false;
}

void CReSurfaceApp::SaveSettings() const {
    SetRegistryValue("Resurface HXT", "distance", para->distance);
    SetRegistryValue("Resurface HXT", "reversenormal", para->reversenormal);
    SetRegistryValue("Resurface HXT", "instancing", para->instancing);
    SetRegistryValue("Resurface HXT", "maxhitdistance", para->maxdistance);
    SetRegistryValue("Resurface HXT", "groupcenter", para->usegroupcenter);
    SetRegistryValue("Resurface HXT", "ignore_x", para->ignore_x);
    SetRegistryValue("Resurface HXT", "ignore_y", para->ignore_y);
    SetRegistryValue("Resurface HXT", "ignore_z", para->ignore_z);
    delete para;
}

float Distance(const Vector v) {
    return v.Norm();
}

float Distance(const Vector v1, const Vector v2) {
    return Distance(v2 - v1);
}

Vector subdivideSegment(const Vector pos_cp1, const Vector it_cp1, const Vector ot_cp2, const Vector pos_cp2, const float factor) {
    const Vector c = 3. * (it_cp1 - pos_cp1);
    const Vector b = 3. * (ot_cp2 - it_cp1) - c;
    const Vector a = pos_cp2 - pos_cp1 - c - b;
    const Vector p = a * factor * factor * factor + b * factor * factor + c * factor + pos_cp1;
    return p;
}

/*
float MeasureSpline(HCP *cp,HModelCache *hmc) {
   HSpline *hsp;
   CArray <HCP *,HCP *> cparray;
   HCP *cp1,*cp2,*tempcp;
   Vector pos,pos_cp1,it_cp1,pos_cp2,ot_cp2,pos_old;
   float length = 0.F;

   if (!cp->IsCache()) cp = (HCP *)cp->GetCache();
   hsp = cp->GetSpline();
   for (cp1 = hsp->GetHeadCP();cp1;cp1 = cp1->GetNext()) {
      cparray.Add(cp1);
      if (cp1->IsLoop()) break;
   }
   if (!hmc) hmc = HModelCache::New("test",true);
   hsp = hmc->CreateSpline();
   tempcp = nullptr;
   int	subdiv = 20;
   float subdiv_factor = 1.F/subdiv;
   for (int i = 1;i<cparray.GetSize();++i) {
      cp1 = cparray[i-1];
      cp2 = cparray[i];
      pos = *cp1->GetModelPosition();
      tempcp = hsp->CreateCPAfter(tempcp,pos);
      pos_cp1 = *cp1->GetModelPosition();
      it_cp1 = cp1->GetModelInTangent();
      pos_cp2 = *cp2->GetModelPosition();
      ot_cp2 = cp2->GetModelOutTangent();
      pos_old = pos;
      for (int j=0;j<=subdiv;++j) {
        pos = subdivideSegment(pos_cp1,it_cp1,ot_cp2,pos_cp2,subdiv_factor*j);
        length += Distance(pos_old,pos);
        tempcp = hsp->CreateCPAfter(tempcp,pos);
        pos_old = pos;
      }
   }
   cp1 = cparray[cparray.GetSize()-1];
   pos = *cp1->GetModelPosition();
   tempcp = hsp->CreateCPAfter(tempcp,pos);
   length += Distance(pos_old,pos);
   hmc->DeleteSpline(hsp);
   return length;
}
*/
void CPGroupCenter(CPLIST &cpl, const Vector center) {
    //   cpl.normal = (center-*cpl.cp->GetWorldPosition()).Normalize();
    cpl.normal = (center - cpl.org_pos).Normalize();
}

void CPRing(CPLIST &cpl) {
    Vector midpoint;
    midpoint.Set(0.F);
    int az = 0;
    for (HCP *hcp_spline = cpl.cp->GetSpline()->GetHeadCP(); hcp_spline; hcp_spline = hcp_spline->GetNext(), ++az) {
        midpoint += *hcp_spline->GetPosition();
        if (hcp_spline->IsLoop())
            break;
    }
    midpoint /= (float)az;
    cpl.normal = (midpoint - *cpl.cp->GetWorldPosition()).Normalize();
}

bool CPPatch(HPatch *hp, CPLIST &cpl) {
    cpl.org_pos = *cpl.cp->GetWorldPosition();
    Vector normal;
    Vector pos = hp->GetPointNormalOnPatch(0.F, 0.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal;
        cpl.normal.Negate();
        return true;
    }
    pos = hp->GetPointNormalOnPatch(1.F, 0.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal;
        cpl.normal.Negate();
        return true;
    }
    pos = hp->GetPointNormalOnPatch(0.F, 1.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal;
        cpl.normal.Negate();
        return true;
    }
    pos = hp->GetPointNormalOnPatch(1.F, 1.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal;
        cpl.normal.Negate();
        return true;
    }
    return false;
}

bool CPPatchAlternate(HPatch *hp, CPLIST &cpl) {
    cpl.org_pos = *cpl.cp->GetWorldPosition();
    Vector normal;
    constexpr Vector normal_patch;
    Vector pos = hp->GetPointNormalOnPatch(0.F, 0.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal_patch;
        cpl.normal.Negate();
        return true;
    }
    pos = hp->GetPointNormalOnPatch(1.F, 0.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal_patch;
        cpl.normal.Negate();
        return true;
    }
    pos = hp->GetPointNormalOnPatch(0.F, 1.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal_patch;
        cpl.normal.Negate();
        return true;
    }
    pos = hp->GetPointNormalOnPatch(1.F, 1.F, normal);
    if (pos == cpl.org_pos) {
        cpl.normal = normal_patch;
        cpl.normal.Negate();
        return true;
    }
    return false;
}

void DumpCPList(HashArray<CPLIST, CPLIST> &cplist, const CString &name) {
    FileStream fs;
    CString filename;
    if (name.IsEmpty()) {
        filename = "e://am_debug//cp.txt";
    } else {
        filename = "e://am_debug//" + name;
    }
    fs.Open(filename, FileMode::HS_ASCII);
    const int listsize = cplist.GetSize();
    fs << "Az CP" << tab << listsize << nl << nl;
    for (int i = 0; i < listsize; ++i) {
        fs << "ID " << cplist[i].cp->GetID() << nl;
        fs << tab << "Pos   " << cplist[i].org_pos << nl;
        fs << tab << "NPos  " << cplist[i].new_pos << nl;
        fs << tab << "Normal" << cplist[i].normal << nl;
    }
    fs.Close();
}

bool CPListfindCP(const HCP *cp, HashArray<CPLIST, CPLIST> &cplist) {
    const int listsize = cplist.GetSize();
    for (int i = 0; i < listsize; ++i) {
        if (cp == cplist[i].cp)
            return true;
    }
    return false;
}

bool CPNormal(HModelCache *hmc, CPLIST &cpl) {
    HCP *head_cp = cpl.cp->GetHead();
    const Vector pos = *head_cp->GetWorldPosition();
    cpl.org_pos = pos;
    Vector ref;
    ref.Set(0, 1, 0);
    HCP *nextattached = nullptr;
    for (nextattached = head_cp; nextattached && nextattached->GetNextAttached(); nextattached = nextattached->GetNextAttached()) {}
    if (nextattached && nextattached != cpl.cp) {
        Vector normal = (head_cp->GetWorldInTangent() - pos ^ nextattached->GetWorldOutTangent() - pos).Normalize();
        if (normal.Dot(ref) < 0)
            normal.Negate();
        cpl.normal = normal;
        return true;
    }
    return false;
}

BOOL CReSurfaceApp::OnGroup(HGroup *hg) {
    LoadSettings();
    para->isinchor = false;

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        return true;
    }
    if (para->ignore_x && para->ignore_y && para->ignore_z) {
        AfxMessageBox("Ignoring al normal axis no possible choice.\nAborting plugin", MB_OK | MB_ICONERROR);
        delete para;
        return true;
    }
    if (para->distance == 0)
        para->distance = 1e-30F;

    CWaitCursor wait;

    auto *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }
    if (hmc->IsModified())
        hmc->FindPatches();

    pbar = GetProgressBar();
    if (pbar) {
        pbar->Initialize();
        pbar->SetMessage1("ReSurface");
        pbar->SetMessage2("Calculating Patches");
        pbar->SetProgress(0);
    }

    HashArray<CPLIST, CPLIST> cplist;
    CPLIST cpl_temp;
    UINT listsize, az;
    const UINT azpatches = hmc->GetPatchCount();
    cpl_temp.cpinstance = nullptr;
    cpl_temp.new_pos.Set(0.F);
    for (UINT i = 0; i < azpatches; ++i) {
        HPatch *hp = hmc->GetPatch(i);
        if (hg->IsPatchInGroup(hp)) {
            if (hp->GetNumPoints() == 4) {
                cpl_temp.cp = hp->GetCP1();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
                cpl_temp.cp = hp->GetCP2();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
                cpl_temp.cp = hp->GetCP3();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
                cpl_temp.cp = hp->GetCP4();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
            } else {
                cpl_temp.cp = hp->GetCP1();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
                cpl_temp.cp = hp->GetCP2();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
                cpl_temp.cp = hp->GetCP3();
                if (CPPatch(hp, cpl_temp)) {
                    cplist.Add(cpl_temp);
                }
            }
        }
    }
#ifdef DEBUG
    DumpCPList(cplist, "cp.txt");
#endif
    if (pbar) {
        pbar->SetMessage2("Matching Group");
        pbar->SetProgress(25);
    }
    HGroupCP *currentgroupcp = hg->GetGroupCP();
    while (currentgroupcp) {
        cpl_temp.cp = currentgroupcp->GetCP();
        if (!CPListfindCP(cpl_temp.cp, cplist)) {
            if (CPNormal(hmc, cpl_temp)) {
                cplist.Add(cpl_temp);
            } else {
                CPRing(cpl_temp);
                cplist.Add(cpl_temp);
            }
        }
        currentgroupcp = currentgroupcp->GetNext();
    }

    listsize = cplist.GetSize();
    if (0 == listsize) {
        delete para;
        return true;
    }

    if (para->usegroupcenter) {
        const Vector groupcenter = hg->GetMatrix()->GetTranslate();
        for (UINT i = 0; i < listsize; ++i) {
            CPGroupCenter(cplist[i], groupcenter);
        }
    }
#ifdef DEBUG
    DumpCPList(cplist, "cp1.txt");
#endif

    if (pbar) {
        pbar->SetMessage2("Calculating new position");
        pbar->SetProgress(50);
    }
    constexpr float flatness = 0.16F;
    PVOID oldrinfo = nullptr;
    PVOID newrinfo = nullptr;
    PVOID thread = nullptr;
    HChor *hchor = HChor::New();
    [[maybe_unused]] HModel *hmodel = hmc->NewInstance(hchor);
    hchor->MultIntersect_Init(flatness, oldrinfo, newrinfo, thread);
    Vector pos, hitp, hitn;
    for (UINT i = 0; i < listsize; ++i) {
        pos = cplist[i].org_pos;
        Vector dir = cplist[i].normal;
        if (para->ignore_x) {
            dir.x = 0;
            dir.Normalize();
        }
        if (para->ignore_y) {
            dir.y = 0;
            dir.Normalize();
        }
        if (para->ignore_z) {
            dir.z = 0;
            dir.Normalize();
        }
        //      dir.y = 0; //restrict axis
        //      dir.Normalize();
        if (para->reversenormal)
            dir.Negate();
        if (hchor->MultIntersect(pos, dir, hitp, hitn, para->maxdistance, thread)) {
            Vector new_dir = (pos - hitp).Normalize();
            Vector new_pos = hitp - pos + para->distance * new_dir;
            new_pos += pos;
            cplist[i].new_pos = new_pos;
            cplist[i].pos_set = true;
        } else {
            cplist[i].new_pos = pos;
            cplist[i].pos_set = false;
        }
    }
#ifdef DEBUG
    DumpCPList(cplist, "cp2.txt");
#endif

    if (pbar) {
        pbar->SetMessage2("Set new position");
        pbar->SetProgress(75);
    }
    HGroupCP *accumgroup = nullptr;
    for (UINT i = 0; i < listsize; ++i) {
        if (cplist[i].pos_set) {
            az = 0;
            pos.Set(0.F);
            for (UINT j = i; j < listsize; ++j) {
                if (cplist[i].org_pos == cplist[j].org_pos && cplist[j].pos_set) {
                    cplist[j].pos_set = false;
                    pos += cplist[j].new_pos;
                    az++;
                }
            }
            if (az > 1)
                pos /= (float)az;
            cplist[i].cp->GetHead()->SetPosition(&pos);
            cplist[i].cp->GetHead()->AddStackToGroup(&accumgroup);
        }
    }

    if (pbar) {
        pbar->SetMessage2("Finished");
        pbar->SetProgress(100);
    }

    cplist.RemoveAll();
    hmc->AddToTemporaryGroup(accumgroup);
    hmc->Update();
    GetHProject()->DeselectAll();
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();

    SaveSettings();
    if (pbar)
        pbar->Uninitialize();
    return true;
}

BOOL CReSurfaceApp::OnModel(HModel *hm) {
    BOOL rc;
    LoadSettings();
    para->isinchor = true;

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        return true;
    }

    if (para->distance == 0)
        para->distance = 1e-30F;
    CWaitCursor wait;
    auto *hmc = (HModelCache *)hm->GetCache();
    if (hm->IsModified() || hmc->IsModified()) {
        hmc->FindPatches();
    }
    pbar = GetProgressBar();
    if (pbar) {
        pbar->Initialize();
        pbar->SetMessage1("ReSurface");
        pbar->SetMessage2("Calculating Patches");
        pbar->SetProgress(0);
    }

    if (para->instancing)
        rc = OnModelInstance(hm);
    else
        rc = OnModelCache(hm);

    if (rc) {
        GetHProject()->DeselectAll();
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        SaveSettings();
    }
    if (pbar)
        pbar->Uninitialize();
    return true;
}

BOOL CReSurfaceApp::OnModelCache(HModel *hm) const {
    auto *hmc = (HModelCache *)hm->GetCache();
    HashArray<CPLIST, CPLIST> cplist;
    CPLIST cpl_temp;
    UINT listsize, az;
    const UINT azpatches = hmc->GetPatchCount();
    cpl_temp.cpinstance = nullptr;
    cpl_temp.new_pos.Set(0.F);
    GetHProject()->DeselectAll();
    for (UINT i = 0; i < azpatches; ++i) {
        HPatch *hp = hmc->GetPatch(i);
        if (hp->GetNumPoints() == 4) {
            cpl_temp.cp = hp->GetCP1();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP2();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP3();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP4();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
        } else {
            cpl_temp.cp = hp->GetCP1();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP2();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP3();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
        }
    }
#ifdef DEBUG
    DumpCPList(cplist, "cp.txt");
#endif
    listsize = cplist.GetSize();
    if (0 == listsize) {
        return false;
    }
    if (pbar) {
        pbar->SetMessage2("Calculating new position");
        pbar->SetProgress(50);
    }
    constexpr float flatness = 0.16F;
    PVOID oldrinfo = nullptr;
    PVOID newrinfo = nullptr;
    PVOID thread = nullptr;
    HChor *hchor = hm->GetChor();
    hchor->MultIntersect_Init(flatness, oldrinfo, newrinfo, thread);
    Vector pos, hitp, hitn;
    for (UINT i = 0; i < listsize; ++i) {
        pos = cplist[i].org_pos;
        Vector dir = cplist[i].normal;
        if (para->reversenormal)
            dir.Negate();
        if (hchor->MultIntersect(pos, dir, hitp, hitn, para->maxdistance, thread)) {
            const Vector new_dir = (pos - hitp).Normalize();
            Vector new_pos = hitp - pos + para->distance * new_dir;
            new_pos += pos;
            cplist[i].new_pos = new_pos;
            cplist[i].pos_set = true;
        } else {
            cplist[i].new_pos = pos;
            cplist[i].pos_set = false;
        }
    }
#ifdef DEBUG
    DumpCPList(cplist, "cp2.txt");
#endif

    if (pbar) {
        pbar->SetMessage2("Set new position");
        pbar->SetProgress(75);
    }
    HGroupCP *accumgroup = nullptr;
    for (UINT i = 0; i < listsize; ++i) {
        if (cplist[i].pos_set) {
            az = 0;
            pos.Set(0.F);
            for (UINT j = i; j < listsize; ++j) {
                if (cplist[i].org_pos == cplist[j].org_pos && cplist[j].pos_set) {
                    cplist[j].pos_set = false;
                    pos += cplist[j].new_pos;
                    az++;
                }
            }
            if (az > 1)
                pos /= (float)az;
            cplist[i].cp->GetHead()->SetPosition(&pos);
            cplist[i].cp->GetHead()->AddStackToGroup(&accumgroup);
        }
    }

    if (pbar) {
        pbar->SetMessage2("Finished");
        pbar->SetProgress(100);
    }

    cplist.RemoveAll();
    hmc->AddToTemporaryGroup(accumgroup);
    hmc->Update();
    return true;
}

BOOL CReSurfaceApp::OnModelInstance(HModel *hm) const {
    auto *hmc = (HModelCache *)hm->GetCache();

    AFX_MANAGE_STATE(AfxGetAppModuleState())

    HashArray<CPLIST, CPLIST> cplist;
    CPLIST cpl_temp;
    UINT listsize;
    const UINT azpatches = hmc->GetPatchCount();
    cpl_temp.cpinstance = nullptr;
    cpl_temp.new_pos.Set(0.F);
    GetHProject()->DeselectAll();
    for (UINT i = 0; i < azpatches; ++i) {
        HPatch *hp = hmc->GetPatch(i);
        if (hp->GetNumPoints() == 4) {
            cpl_temp.cp = hp->GetCP1();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP2();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP3();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP4();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
        } else {
            cpl_temp.cp = hp->GetCP1();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP2();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
            cpl_temp.cp = hp->GetCP3();
            if (CPPatch(hp, cpl_temp)) {
                cplist.Add(cpl_temp);
            }
        }
    }
#ifdef DEBUG
    DumpCPList(cplist, "cp.txt");
#endif
    listsize = cplist.GetSize();
    if (0 == listsize) {
        return false;
    }
    if (pbar) {
        pbar->SetMessage2("Calculating new position");
        pbar->SetProgress(50);
    }
    HashArray<CP_INSTANCE, CP_INSTANCE> framecp;
    CP_INSTANCE _framecp;
    Vector pos, hitp, hitn;

    constexpr float flatness = 0.16F;
    PVOID oldrinfo = nullptr;
    PVOID newrinfo = nullptr;
    PVOID thread = nullptr;
    HChor *hchor = hm->GetChor();
    Time chor_time = hchor->GetTotalTime()->GetValue();
    Time start_time = hchor->GetTime();
    const int fps = (int)GetHProject()->GetFPS();
    const int start = (int)start_time.GetFrame(fps);
    int end = (int)chor_time.GetFrame(fps);
    if (end == 0)
        end = start; //for actions , when length is 0 and start different from 0
    Time akt_time;
    if (pbar) {
        pbar->SetMessage2("Calculating Distances");
    }
    float inc_start = 25;
    const float increment = 50.F / (end - start);
    for (int frame = start; frame <= end; ++frame) {
        if (pbar) {
            pbar->SetProgress((int)inc_start);
            inc_start += increment;
        }
        akt_time.SetFrame(frame, fps);
        hchor->SetTime(akt_time);
        GetHProject()->UpdateAllViews(TRUE);
        hchor->MultIntersect_Init(flatness, oldrinfo, newrinfo, thread);
        for (UINT i = 0; i < listsize; ++i) {
            pos = cplist[i].org_pos;
            Vector dir = cplist[i].normal;
            if (para->reversenormal)
                dir.Negate();
            if (hchor->MultIntersect(pos, dir, hitp, hitn, para->maxdistance, thread)) {
                Vector new_dir = (pos - hitp).Normalize();
                Vector new_pos = hitp - pos + para->distance * new_dir;
                new_pos += pos;
                cplist[i].new_pos = new_pos;
                cplist[i].pos_set = true;
            } else {
                cplist[i].new_pos = pos;
                cplist[i].pos_set = false;
            }
        }
        for (UINT i = 0; i < listsize; ++i) {
            if (cplist[i].pos_set) {
                int az = 0;
                pos.Set(0.F);
                for (UINT j = i; j < listsize; ++j) {
                    if (cplist[i].org_pos == cplist[j].org_pos && cplist[j].pos_set) {
                        cplist[j].pos_set = false;
                        pos += cplist[j].new_pos;
                        az++;
                    }
                }
                if (az > 1)
                    pos /= (float)az;
                for (UINT k = 0; k < listsize; ++k) {
                    if (cplist[i].cp->GetHead() == cplist[k].cp) {
                        if (!cplist[k].cpinstance)
                            cplist[k].cpinstance = cplist[k].cp->CreateCPInstance();
                        _framecp.cpinstance = cplist[k].cpinstance;
                        _framecp.frame = frame;
                        _framecp.pos = pos - cplist[k].org_pos;
                        framecp.Add(_framecp);
                    }
                }
            }
        }

        /*
              for (UINT i=0;i<listsize;++i) {
                 if (cplist[i].pos_set) {
                   if (!cplist[i].cpinstance) cplist[i].cpinstance = cplist[i].cp->CreateCPInstance();
                   _framecp.cpinstance = cplist[i].cpinstance;
                   _framecp.Frame = frame;
                   _framecp.pos = cplist[i].new_pos-cplist[i].org_pos;
                   framecp.Add(_framecp);
                   cplist[i].pos_set = false;
                }
             }
        */
        hchor->MultIntersect_Exit(oldrinfo, newrinfo, thread);
        oldrinfo = nullptr;
        newrinfo = nullptr;
        thread = nullptr;
    }
    if (pbar) {
        pbar->SetMessage2("Creating action");
        pbar->SetProgress(75);
    }
    cplist.RemoveAll();
    listsize = framecp.GetSize();
    for (UINT i = 0; i < listsize; ++i) {
        akt_time.SetFrame(framecp[i].frame, fps);
        framecp[i].cpinstance->GetPosition()->StoreValue(akt_time, framecp[i].pos, FALSE);
    }
    if (pbar) {
        pbar->SetMessage2("Finished");
        pbar->SetProgress(100);
    }
    framecp.RemoveAll();
    akt_time.SetFrame(start, fps);
    hchor->SetTime(akt_time);
    return true;
}
