// TestPlugin.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "TestPlugin.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestPluginApp

BEGIN_MESSAGE_MAP(CTestPluginApp, CWinApp)
   //{{AFX_MSG_MAP(CTestPluginApp)
      // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
      //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPluginApp Konstruktion
CTestPluginApp::CTestPluginApp()
{
}

CTestPluginApp::~CTestPluginApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CTestPluginApp-Objekt

CTestPluginApp theApp;

BOOL CTestPluginApp::InitInstance()
{
   SetRegistryKey( "Hash, Inc." );
   free((void*)m_pszProfileName);
   m_pszProfileName = _tcsdup("AM Plugins");
   return CWinApp::InitInstance();
}

int CTestPluginApp::ExitInstance()
{
   return CWinApp::ExitInstance();
}

float Distance(Vector v) { return v.Norm();}
float Distance(Vector v1,Vector v2) { return Distance(v2-v1);}

Vector midPoint(Vector A, Vector B) {
       Vector m;
       m = A + B;
       m *= 0.5f;
       return m;
}

Vector newPos (HCP* cp1,HCP* cp2) {

   Vector p1 = *cp1->GetHead()->GetModelPosition();
    Vector p2 = cp1->GetModelInTangent();
   Vector p3 = cp2->GetModelOutTangent();
    Vector p4 = *cp2->GetHead()->GetModelPosition();	
    Vector l2 = midPoint(p1,p2);
    Vector h = midPoint(p2,p3);
    Vector r3 = midPoint(p3,p4);
    Vector l3 = midPoint(l2,h);
    Vector r2 = midPoint(h,r3);
    Vector c = midPoint(l3,r2);
    return c;
}

Vector subdivideSegment(Vector pos_cp1,Vector it_cp1,Vector ot_cp2,Vector pos_cp2,float factor){
   Vector a,b,c,p;
   c = 3 * (it_cp1 - pos_cp1);
   b = 3 * (ot_cp2 - it_cp1) - c;
   a = pos_cp2 - pos_cp1 - c - b;
   p = a * factor * factor * factor + b *factor * factor + c * factor + pos_cp1;
   return p;
}

float MeasureSpline(HCP *cp,HModelCache *hmc, int &cpcount) {
   HSpline *hsp;
   CArray <HCP *,HCP *> cparray;
   HCP *cp1,*cp2,*tempcp;
   Vector pos,pos_cp1,it_cp1,pos_cp2,ot_cp2,pos_old;
   float length = 0.f;

   if (!cp->IsCache()) cp = (HCP *)cp->GetCache();
   hsp = cp->GetSpline();
   for (cp1 = hsp->GetHeadCP();cp1;cp1 = cp1->GetNext()) {
      cparray.Add(cp1);
      if (cp1->IsLoop()) break;
   }
   cpcount = cparray.GetSize();
   hsp = hmc->CreateSpline();
   tempcp = nullptr;
   int	subdiv = 20;
   float subdiv_factor = 1.f/subdiv;
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
      for (int j=0;j<=subdiv;j++) {
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

#include <smmintrin.h>
__forceinline float minimumOf(float a, float b) {
    return _mm_cvtss_f32(_mm_min_ps(
        _mm_set_ss(a),
        _mm_set_ss(b)
    ));
}

BOOL CTestPluginApp::OnChor(HChor *chor) {
    TimeRange tt = chor->GetPlayRange();
    float xa = minimumOf(0.1f, 0.5f);
    tt.m_end.StepFramesBack(5*xa, GetHProject()->GetFPS());
    chor->SetPlayRange(tt);
    return TRUE;
}


BOOL CTestPluginApp::OnActionCache(HActionCache *chor) {
    TimeRange tt = chor->GetPlayRange();
    tt.m_end.StepFramesBack(5, GetHProject()->GetFPS());
    chor->SetPlayRange(tt);
    return TRUE;
}

BOOL CTestPluginApp::OnAction(HAction *chor) {
    TimeRange tt = chor->GetPlayRange();
    tt.m_end.StepFrames(5, GetHProject()->GetFPS());
    chor->SetPlayRange(tt);
    return TRUE;
}

BOOL CTestPluginApp::OnCP(HCP *cp) {

   HCP *hcp1,*hcp2,*tempcp;
   Vector pos1,pos2;
  
   HModelCache *hmc;
   HTreeObject *parent = nullptr;
   parent = cp->GetParent(); 
   do {
      parent = parent->GetParent();
   } while(parent != nullptr && parent->GetObjectType() != HOT_MODEL); 
   if (parent == nullptr) {
      AfxMessageBox("model not found",MB_OK);
      return false;
   }
   hmc = (HModelCache *)parent;
   UINT cpid = cp->GetID();
   hmc->DetachCP(cp);
/*
   hcp1 = hcp2 = tempcp = nullptr;
   hcp1 = hcp2 = cp;
   PARAMETER *para = new PARAMETER;

   para->splinelength = MeasureSpline(hcp2,hmc,para->cpcount);
   para->neededdistance = GetRegistryValue("TestPlugin HXT","distance",0.5f);
   para->iteration = RoundValue(para->splinelength/para->neededdistance);
   para->neededdistance = para->splinelength/para->iteration;
   para->zcount = -1;
   para->zvalue = 0.5f;
   para->extrude = FALSE;
   para->direction = 2;

   PDialog dlg(para);
   if (dlg.DoModal()!= IDOK) {
      delete para;
      return TRUE;
   }

   HSpline *spline_org = hcp1->GetSpline();
   hmc = HModelCache::New("resampledspline",true);
   GetHProject()->DeselectAll();
   Vector pos,dir;
   float ease = 1.f/para->iteration;
   int iteration = para->iteration+1;
   HSpline *hsp = hmc->CreateSpline();
   for (int i = 0;i<iteration;++i) {
      spline_org->GetPositionAndDirection(ease*i,pos,dir);
      tempcp = hsp->CreateCPAfter(tempcp,pos);
   }
   BOOL spline_islooped = FALSE;
   for (hcp2 = hcp1;hcp2;hcp2 = hcp2->GetNext()) {
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
   hmc->Update();
   GetHProject()->DeselectAll();
   GetHProject()->UpdateAllViews(TRUE);
   RefreshAllTrees();
*/
   return true;
}

void AddGroupCPToGroup (HGroupCP *hgcp, HGroup *hg)
{
	while (hgcp) {
		hg->AddCP(hgcp->GetCP());
		hgcp=hgcp->GetNext();
	}
}
/*
BOOL CTestPluginApp::OnGroup(HGroup *hg)
{
   HModelCache *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);

	hmc->FindPatches();
	int azpatches = hmc->GetPatchCount();
   String result;
	for (HPatch5 *hp5 = hmc->GetHeadPatch5();hp5;hp5 = hp5->GetNextPatch5()) {
		if (hg->IsPatchInGroup(hp5)) {
         PatchID5 id = hp5->GetPatchID();
         result += "Patch5 "+ (String)id.m_id1 + " " + (String)id.m_id2 +" "+(String)id.m_id3 +" "+(String)id.m_id4 +" "+(String)id.m_id5+"\n";
		}
	}

	if (azpatches > 0) {
	    for (int aktpatch = 0;aktpatch < azpatches; aktpatch++) {
			if (hg->IsPatchInGroup(hmc->GetPatch(aktpatch))) {
            HPatch *hp = hmc->GetPatch(aktpatch);
            PatchID id = hp->GetPatchID();
            result += "Patch  "+ (String)id.m_id1 + " " + (String)id.m_id2 +" "+(String)id.m_id3 +" "+(String)id.m_id4 +"\n";
			}
		}
	}
   AfxMessageBox(result.Get(),MB_OK);
   return TRUE;
}
*/
BOOL CTestPluginApp::OnGroup(HGroup *hg)
{
   HCP *hcp1,*hcp2;
   hcp1 = hg->GetGroupCP()->GetCP();
   hcp2 = hg->GetGroupCP()->GetNext()->GetCP();
   HModelCache *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
   hmc->JoinSpline(hcp1, hcp2);
   GetHProject()->UpdateAllViews(TRUE);
   RefreshAllTrees();
   return TRUE;
}

static void SetTypeCP(HSpline *sph) {
    HCP *cp = sph->GetHeadCP();
    cp->SetPeaked();
    while ((cp = cp->GetNext()) != nullptr) {
        cp->SetPeaked();
        if (cp->IsLoop()) 
            break;
    }
}

static void GroupAdd(HSpline *spline,HGroup *group) {
    HCP *cp = spline->GetHeadCP();
    group->AddCP(cp);
    while ((cp = cp->GetNext()) != nullptr) {
        group->AddCP(cp);
        if (cp->IsLoop())
            break;
    }
}

BOOL CTestPluginApp::OnModel(HModelCache *hc)
{
    PARAMETER *para = new PARAMETER;

    para->neededdistance = GetRegistryValue("TestPlugin HXT", "distance", 0.5f);
    para->iteration = RoundValue(para->splinelength / para->neededdistance);
    para->neededdistance = para->splinelength / para->iteration;
    para->zcount = -1;
    para->zvalue = 0.5f;
    para->extrude = FALSE;
    para->direction = 2;

    PDialog dlg(para);
    if (dlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }
    delete para;
    return TRUE;

    Vector firstpos, pos;
    HCP *lastcp = nullptr;
    HSpline *spline;
    HGroup *group;
/*
    group = hc->CreateGroup("5Patch_curl0");
    firstpos.Set(13.976202, 57.852280, 13.073701);
    pos.Set(0.344288, 57.947006, 17.362434);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(0.586216, 50.918945, 18.346107);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(1.809548, 49.444248, 17.834351);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(14.319487, 48.472683, 13.035395);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);


    group = hc->CreateGroup("5Patch_curl1");
    firstpos.Set(14.430204, 57.866760, 13.670502);
    pos.Set(0.404813, 58.056213, 18.101969);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(0.866208, 51.021290, 19.034315);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(1.772676, 49.077995, 18.487801);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(14.831073, 48.488865, 13.583590);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);


    group = hc->CreateGroup("4Patch_curl0");
    firstpos.Set(13.976202, 57.852280, 13.073701);
    pos.Set(14.319487, 48.472683, 13.035395);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(20.366272, 48.416695, -1.681411);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(20.885733, 57.786034, -0.557530);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);

    group = hc->CreateGroup("4Patch_curl1");
    firstpos.Set(14.430204, 57.866760, 13.670502);
    pos.Set(14.831073, 48.488865, 13.583590);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(21.114944, 48.376888, -1.701502);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(21.627966, 57.734268, -0.463139);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
*/
    group = hc->CreateGroup("Patch0_0");
    firstpos.Set(-15.5116, 57.8378, 12.4616);
    pos.Set(-8.57457, 57.8378, 16.3376);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-7.08792, 53.0593, 16.8114);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-15.5009, 53.1471, 12.4592);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch0_1");
    firstpos.Set(-14.933, 57.8394, 11.9844);
    pos.Set(-8.28904, 57.7839, 15.728);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.82987, 53.1194, 16.2409);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-14.9033, 53.1487, 12.0071);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch0_2");
    firstpos.Set(-14.3544, 57.8409, 11.5072);
    pos.Set(-8.00351, 57.73, 15.1184);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.57182, 53.1794, 15.6705);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-14.3056, 53.1503, 11.5551);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch1_0");
    firstpos.Set(0.283764, 57.8378, 16.6229);
    pos.Set(0.294994, 54.3272, 17.1404);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-7.08792, 53.0593, 16.8114);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-8.57457, 57.8378, 16.3376);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch1_1");
    firstpos.Set(0.276228, 57.7284, 15.881);
    pos.Set(0.435343, 54.2225, 16.4269);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.82987, 53.1194, 16.2409);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-8.28904, 57.7839, 15.728);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch1_2");
    firstpos.Set(0.268692, 57.619, 15.139);
    pos.Set(0.575695, 54.1177, 15.7133);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.57182, 53.1794, 15.6705);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-8.00351, 57.73, 15.1184);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch2_0");
    firstpos.Set(0.306223, 50.8166, 17.6579);
    pos.Set(-0.421953, 50.3104, 17.4255);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-7.08792, 53.0593, 16.8114);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(0.294994, 54.3272, 17.1404);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch2_1");
    firstpos.Set(0.594461, 50.7165, 16.9728);
    pos.Set(-0.370686, 50.5135, 16.8224);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.82987, 53.1194, 16.2409);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(0.435343, 54.2225, 16.4269);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch2_2");
    firstpos.Set(0.882696, 50.6164, 16.2876);
    pos.Set(-0.31942, 50.7166, 16.2192);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.57182, 53.1794, 15.6705);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(0.575695, 54.1177, 15.7133);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch3_0");
    firstpos.Set(-1.15013, 49.8041, 17.1931);
    pos.Set(-8.92587, 48.8647, 16.9078);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-7.08792, 53.0593, 16.8114);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-0.421953, 50.3104, 17.4255);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch3_1");
    firstpos.Set(-1.33584, 50.3105, 16.6719);
    pos.Set(-8.71039, 49.1187, 16.4338);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.82987, 53.1194, 16.2409);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-0.370686, 50.5135, 16.8224);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch3_2");
    firstpos.Set(-1.52154, 50.8168, 16.1508);
    pos.Set(-8.49491, 49.3727, 15.9598);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.57182, 53.1794, 15.6705);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-0.31942, 50.7166, 16.2192);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch4_0");
    firstpos.Set(-15.4902, 48.4565, 12.4567);
    pos.Set(-15.5009, 53.1471, 12.4592);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-7.08792, 53.0593, 16.8114);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-8.92587, 48.8647, 16.9078);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch4_1");
    firstpos.Set(-14.8735, 48.4581, 12.0298);
    pos.Set(-14.9033, 53.1487, 12.0071);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.82987, 53.1194, 16.2409);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-8.71039, 49.1187, 16.4338);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);
    group = hc->CreateGroup("Patch4_2");
    firstpos.Set(-14.2569, 48.4598, 11.603);
    pos.Set(-14.3056, 53.1503, 11.5551);
    spline = hc->StartSpline(&firstpos, &pos);
    lastcp = spline->GetHeadCP()->GetNext();
    pos.Set(-6.57182, 53.1794, 15.6705);
    lastcp = hc->AddCP(lastcp, &pos);
    pos.Set(-8.49491, 49.3727, 15.9598);
    lastcp = hc->AddCP(lastcp, &pos);
    lastcp = hc->AddCP(lastcp, &firstpos);
    hc->AttachCPs(lastcp, spline->GetHeadCP());
    SetTypeCP(spline);
    GroupAdd(spline, group);

    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

BOOL CTestPluginApp::OnExportActionCache(HActionCache *hac) {

   HProject *hproject = GetHProject();
   float fps = hproject->GetFPS();
//   int start = dlg.m_startframe;
//   int end = dlg.m_endframe;
   float errortolerance = 1.f;//dlg.m_errortolerance;

   HModelCache *hmc = hac->GetDefaultModelCache();
   HModel *hm = hac->EditWithModelCache(hmc);

//   HActionCache *hunconstrainedac = HActionCache::New("Unconstrained Action", TRUE, TRUE);
//   hunconstrainedac->SetDefaultModelCache(hmc);

   HActionCache *hunconstrainedac = hac->Bake(hm, errortolerance);

   HHashObject *hho = hac->GetParentOfType(HOT_ACTIONS);
   hunconstrainedac->SetName("Unconstrained Action");
   hunconstrainedac->SetDefaultModelCache(hmc);
   hho->InsertChildAtTail(hunconstrainedac);

   hm = hunconstrainedac->EditWithModelCache(hmc);

//   HAnimObjectShortcut *bonesfolder_clone = (HAnimObjectShortcut *) hunconstrainedac->FindChildByName("Bones");
   HAnimObjectShortcut *bonesfolder = (HAnimObjectShortcut *) hac->FindChildByName("Bones");

   HTranslateProperty *btp_o,*btp_c;
   HRotateProperty *brp_o,*brp_c;
   HScaleProperty *bsp_o,*bsp_c;

   Time totaltime = hac->GetTotalTime();

   Vector pos, scale;
   Quaternion quat;

   for (HAnimObjectShortcut *boneshortcut = (HAnimObjectShortcut *)bonesfolder->GetChild(); boneshortcut; boneshortcut=(HAnimObjectShortcut *)boneshortcut->GetSibling()) {
       HBone *bone = (HBone *)boneshortcut->GetAnimObject();
//       HBone *bone_clone = (HBone *)hmc->FindChildByName(bone->GetMatchName().Get());

          btp_o = bone->GetTransform()->GetTranslate();
          brp_o = bone->GetTransform()->GetRotate();
          bsp_o = bone->GetTransform()->GetScale();

//          btp_c = bone_clone->GetTransform()->GetTranslate();
//          brp_c = bone_clone->GetTransform()->GetRotate();
//          bsp_c = bone_clone->GetTransform()->GetScale();

          for (Time time; time<=totaltime; time.StepFrame(fps)) {

              pos = btp_o->GetValue(time);
              quat = brp_o->GetValue(time);

            btp_o->StoreValue(time, pos, FALSE);
            brp_o->StoreValue(time, quat, TRUE, TRUE);
           }
   }

  hunconstrainedac->EndEditWithModelCache(hm);

  GetHProject()->UpdateAllViews();
  return TRUE;
}
