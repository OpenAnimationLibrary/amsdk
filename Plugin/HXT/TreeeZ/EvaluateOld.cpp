// KB  6/4/01  \Ken90\Plugin\HXT\Duplicator\Evaluate.cpp
// Z 04-03-18 ZPiDER/Marcel Bricman/kci:dnd

#include "stdafx.h"
#include "Hxt.h"

#include "HashFile.h"

#include "SDK\Misc.h"
#include "SDK\HModel.h"
#include "SDK\HChor.h"
#include "SDK\HProject.h"
#include "SDK\HDecal.h"

//-------------------------------------------------------------------------- H E L P E R S

// returns the group named like <name>
HGroup *FindGroup( HModelCache *hmc, String &name)
{
	try
	{
		return (HGroup *)hmc->GetChildGroupContainer()->FindChildByName(name.buf);
	}
	catch (...)
	{
	}
	return nullptr;
}

void setCPdecoration(HCP *cp, float value)
{
	cp->SetInAlpha(1.0f+value);
}

float getCPdecoration(HCP *cp)
{
	return cp->GetInAlpha()-1.0f;
}

void transformGroup(HGroupCP *gcp, float s, Vector r, Vector t, float along)
{
	while (gcp)
	{
		HCP *cp = gcp->GetCP();
		Vector cppos = *cp->GetPosition();
		cppos *= ScaleV(s);
		cppos *= Rotate2V(Vector(0.0f,1.0f,0.0f), r);
		cppos *= TranslateV(t);
		cp->SetPosition( &cppos );

		// decorate cps with level info
		setCPdecoration(cp, along);

		gcp = gcp->GetNext();
	}
}

HGroup *getGroup(HModelCache *hmc, String &name)
{
	HGroup *group = FindGroup(hmc, name);
#ifdef V11
	if (group == nullptr) group = hmc->CreateGroup(name);
#endif
	return group;
}

void addGroupCPsToGroup(HGroupCP *from, HGroup *to)
{
#ifdef V11
	while (from && to)
	{
		HCP *cp = from->GetCP();
		to->AddCP(cp);
		from = from->GetNext();
	}
#endif
}

//-------------------------------------------------------------------------- C L U S T E R I N G
// clustered tracking

struct Point
{
	int id;
	HCP *cp;
	Vector pos;
	int depth;
	int parent;
	int child1;
	int child2;
	BOOL done;
};

typedef CMap<int, int, Point, Point> PointMap;
typedef CMap<int, int, HCP *, HCP *> CPMap;

int maxid = 0;
BOOL debug = FALSE;
BOOL debugfine = FALSE;
HChor *chor = nullptr;

// collects all leaves descending of p into pointMap
void collect(int start, PointMap &pointMap, PointMap &output)
{
	if (debugfine == TRUE)
	{
		String s = "collecting " + String(start);
		AfxMessageBox(TEXT(s.buf), MB_OK|MB_ICONSTOP, 0);
	}

	Point *p = &pointMap[start];
	if ((p != nullptr) && (p->id != 0))
	{
		if (p->cp != nullptr)
		{
			output.SetAt(p->id, *p);
		}
		else
		{
			collect(p->child1, pointMap, output);
			collect(p->child2, pointMap, output);
		}
	}
}

// clean pointmap (remove internal nodes)
void clean(PointMap &pointMap, int depth)
{
	int id = 0;
	int count = 0;
	int count2 = 0;

	Time time = Time(depth,GetHProject()->GetFPS());
	chor->CreateFrame(time);

	Point t;
	POSITION pos = pointMap.GetStartPosition();
	while (pos != nullptr)
	{
		pointMap.GetNextAssoc(pos, id, t);
		if (t.cp == nullptr)
		{
			pointMap.RemoveKey(id);
			count ++;
		}
		else
		{
			if (pointMap[id].cp) { pointMap[id].pos = *(pointMap[id].cp->GetWorldPosition()); }
			pointMap[id].done = FALSE;
			count2 ++;
		}
	}
	if (debug == TRUE)
	{
		String s = "cleaned: " + String(count) + " inner nodes removed, " + String(count2) + " leaf nodes cleaned.";
		AfxMessageBox(TEXT(s.buf), MB_OK|MB_ICONSTOP, 0);
	}
}

Point *cluster(PointMap &pointMap, Vector startPos, float locality, float regularity, int depth)
{
	clean(pointMap, depth);

	if (pointMap.GetCount() == 1)
	{
		Point t;
		int id;
		POSITION pos = pointMap.GetStartPosition();
		pointMap.GetNextAssoc(pos, id, t);
		return &pointMap[id];
	}

	int dummy = 0;

	int id = maxid;
	Point *p = new Point();
	while (pointMap.GetCount() > 1)
	{
		// find 2 closest points
		Point p1, p2, t1, t2;
		p1.id = 0;
		float mindist;
		mindist = 9999999.0f;
		POSITION pos1 = pointMap.GetStartPosition();
		while (pos1 != nullptr)
		{
			pointMap.GetNextAssoc(pos1, dummy, t1);
			if (t1.done == FALSE)
			{
				POSITION pos2 = pos1;
				while (pos2 != nullptr)
				{
					pointMap.GetNextAssoc(pos2, dummy, t2);
					if (t2.done == FALSE)
					{
						Vector t1t2 = t1.pos - t2.pos;

						// decision locality
						Vector t12 = (t1.pos + t2.pos) / 2;
						Vector startt12 = startPos - t12;
						float dist = t1t2.Norm()*(1.0f-locality) - startt12.Norm()*locality;

						// add a random value (how large? based on startt12?) to dist to make clustering unsharp

						if (dist < mindist)
						{
							p1 = t1;
							p2 = t2;
							mindist = dist;
						}
					}
				}
			}
		}
		if (p1.id != 0)
		{
			// collapse points
			id++;
			p->id = id;
			p->cp = nullptr;

			//p->pos = (p1.pos + p2.pos) / 2;
			// weighted branching:
			p->pos = (p1.pos*(p1.depth*regularity+1) + p2.pos*(p2.depth*regularity+1)) / (2 + p1.depth*regularity + p2.depth*regularity);

			p->depth = MAX(p1.depth, p2.depth) + 1;
			p->child1 = p1.id;	p1.parent = p->id;	pointMap[p1.id].done = TRUE;
			p->child2 = p2.id;	p2.parent = p->id;	pointMap[p2.id].done = TRUE;
			p->done = FALSE;
			pointMap.SetAt(p->id, *p);

			if (debugfine == TRUE)
			{
				String s = "clustering " + String(p1.id) + " and " + String(p2.id) + " into " + String(p->id);
				AfxMessageBox(TEXT(s.buf), MB_OK|MB_ICONSTOP, 0);
			}
		}
		else
		{
			break;
		}
	}
	if (debug == TRUE)
	{
		String s = "clustered: " + String(id-maxid) + " inner nodes (" + String(pointMap.GetCount()) + " total nodes)";
		AfxMessageBox(TEXT(s.buf), MB_OK|MB_ICONSTOP, 0);
	}
	return p;
}

//-------------------------------------------------------------------------- B R A N C H

float getPropertyValue(HFloatProperty *hfp, float defaultValue, float time)
{
	if (hfp != nullptr)
	{
		Time t = Time(time);
		return hfp->GetValue(t);
	}
	else
	{
		return defaultValue;
	}
}

float calcThickness(HFloatProperty *hfp, float along)
{
	return getPropertyValue(hfp, along, 1.0f-along);
}

float calcBranchlength(HFloatProperty *hfp, float along)
{
	return getPropertyValue(hfp, 0.25f, along);
}

float calcLocality(HFloatProperty *hfp, float along)
{
	return getPropertyValue(hfp, 0.0f, along);
}

float calcRegularity(HFloatProperty *hfp, float along)
{
	return getPropertyValue(hfp, 0.0f, along);
}

int estimatedtotaldepth = 0;
int totaldepth = 0;

int branch(HModelCache *hmc, HActionCache *hac, HFloatProperty *p_thickness, HFloatProperty *p_branchlength, HFloatProperty *p_locality, HFloatProperty *p_regularity,
		   HGroupCP *hg, Vector lastPos, Vector lastDir, PointMap &pointMap, int depth, BOOL mainbranch=TRUE) // returns total depth
{
	PointMap pointMapA;
	PointMap pointMapB;
	pointMapA.InitHashTable(997);
	pointMapB.InitHashTable(997);

	// transform "base" group
	if (depth == 0) transformGroup(hg, calcThickness(p_thickness, 1.0f), lastDir, lastPos, 1.0f);

	float along = 0.0f;
	if (estimatedtotaldepth > 0) along = (float)depth/(float)estimatedtotaldepth;

	Point *p = cluster(pointMap, lastPos, calcLocality(p_locality, along), calcRegularity(p_regularity, along), depth);
	if (p->depth > estimatedtotaldepth) estimatedtotaldepth = p->depth;

	//float offshootBaseScale;// = 0.75f / (float)estimatedtotaldepth;
	//float mainIntBaseScale;// = 0.5f / (float)estimatedtotaldepth;

	if (depth > totaldepth) totaldepth = depth;

	collect(p->child1, pointMap, pointMapA);

	if (debug == TRUE)
	{
		String str = "collected into A: " + String(pointMapA.GetCount()) + " leaves.";
		AfxMessageBox(TEXT(str.buf), MB_OK|MB_ICONSTOP, 0);
	}

	collect(p->child2, pointMap, pointMapB);

	if (debug == TRUE)
	{
		String str = "collected into B: " + String(pointMapB.GetCount()) + " leaves.";
		AfxMessageBox(TEXT(str.buf), MB_OK|MB_ICONSTOP, 0);
	}

	Vector pos = lastPos + (p->pos-lastPos) * calcBranchlength(p_branchlength, ((float)depth)/(float)(p->depth+1));
	Vector dir = pos - lastPos;

	HGroupCP *newgroup = nullptr;
	HGroupCP *newintgroup = nullptr;

	// draw branch from previous towards target plus branching part
	hmc->CopyExtrude(TRUE, hg, &newintgroup);
	hmc->CopyExtrude(TRUE, newintgroup, &newgroup);

	// TODO: add some random factor to (p->child1.dir) and (p->child2.dir)

	int childdepth = 0;
	int td = estimatedtotaldepth;

	if (p->cp == nullptr)	// inner branch
	{
		int d1=1, d2=1;
		if (pointMap[p->child1].depth > pointMap[p->child2].depth)	// switch main branch to deeper subtree
		{
			d1 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapA, depth+1);
			d2 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapB, depth+1, FALSE);
		}
		else
		{
			d2 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapB, depth+1);	// needs to be ordered first to take first extrusion
			d1 = branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newgroup, pos, dir, pointMapA, depth+1, FALSE);
		}

		childdepth = MAX(d1, d2);

		td = totaldepth;
	}
	else	// leaf branch
	{
//		pos = p->pos;	// the leaf goes right to the target cp

		Vector leafPos1 = pos + dir;	// double of regular branch length
		Vector leafDir1 = dir  *2;
		Vector leafPos2 = p->pos;		// straight to target cp
		Vector leafDir2 = leafPos2 - lastPos;
		if (leafDir2.Norm() < leafDir1.Norm())	// if target cp is closer than double regular length
		{
			pos = leafPos2;
			dir = leafDir2;
		}
		else
		{
			pos = leafPos1;
			dir = leafDir1;
		}
	}

	td += 1;
	int branchdepth = childdepth + depth;

	float branchScale = (float)childdepth / (float)td;

	transformGroup(newgroup, calcThickness(p_thickness, branchScale), dir, pos, branchScale );

	String name = "level" + String(childdepth);
	HGroup *g = getGroup(hmc, name);

	if (mainbranch == FALSE)
	{
		float offshootBaseScale = 0.75f / (float)td;
		transformGroup(newintgroup, calcThickness(p_thickness, branchScale + offshootBaseScale), (dir+lastDir)/2, (pos+lastPos*3+lastDir)/4, branchScale + offshootBaseScale );
	}
	else
	{
		float mainIntBaseScale = 0.5f / (float)td;
		transformGroup(newintgroup, calcThickness(p_thickness, branchScale + mainIntBaseScale), (dir*2+lastDir)/3, (lastPos+(lastDir+dir)/4), branchScale + mainIntBaseScale );
	}

	addGroupCPsToGroup(hg, g);
	addGroupCPsToGroup(newgroup, g);
	addGroupCPsToGroup(newintgroup, g);

	return childdepth+1;
}

//-------------------------------------------------------------------------- D E C A L I N G

void addPatchUV(HPatch *patch, HDecalStamp *hds, int id)
{
	Vector2 uv[12];

	float depth1 = getCPdecoration(patch->GetCP1()->GetHead());
	float depth2 = getCPdecoration(patch->GetCP2()->GetHead());
	float depth3 = getCPdecoration(patch->GetCP3()->GetHead());
	float depth4 = getCPdecoration(patch->GetCP4()->GetHead());

	float depthA = MIN(MIN(depth1, depth2), depth3);
	float depthB = MAX(MAX(depth1, depth2), depth3);

	uv[0].y = depth1;
	uv[3].y = depth2;
	uv[6].y = depth3;
	uv[9].y = depth4;

	if ((uv[0].y == uv[3].y) && (uv[0].y == depthA)) { uv[0].x = 0.0f; uv[3].x = 1.0f; }
	if ((uv[0].y == uv[3].y) && (uv[0].y == depthB)) { uv[0].x = 1.0f; uv[3].x = 0.0f; }
	if ((uv[3].y == uv[6].y) && (uv[3].y == depthA)) { uv[3].x = 0.0f; uv[6].x = 1.0f; }
	if ((uv[3].y == uv[6].y) && (uv[3].y == depthB)) { uv[3].x = 1.0f; uv[6].x = 0.0f; }
	if ((uv[6].y == uv[9].y) && (uv[6].y == depthA)) { uv[6].x = 0.0f; uv[9].x = 1.0f; }
	if ((uv[6].y == uv[9].y) && (uv[6].y == depthB)) { uv[6].x = 1.0f; uv[9].x = 0.0f; }
	if ((uv[9].y == uv[0].y) && (uv[9].y == depthA)) { uv[9].x = 0.0f; uv[0].x = 1.0f; }
	if ((uv[9].y == uv[0].y) && (uv[9].y == depthB)) { uv[9].x = 1.0f; uv[0].x = 0.0f; }

	// correct overshoot
	for (int i=0;i<12;i++) uv[i] = (uv[i]-0.5f)*0.99f+0.5f;

	// set between points to form straight line
	float a = 1.0f;
	float b = 3.0f;
	uv[1]  = (uv[0] * a + uv[3] * b) / (a+b);
	uv[2]  = (uv[0] * b + uv[3] * a) / (a+b);
	uv[4]  = (uv[3] * a + uv[6] * b) / (a+b);
	uv[5]  = (uv[3] * b + uv[6] * a) / (a+b);
	uv[7]  = (uv[6] * a + uv[9] * b) / (a+b);
	uv[8]  = (uv[6] * b + uv[9] * a) / (a+b);
	uv[10] = (uv[9] * a + uv[0] * b) / (a+b);
	uv[11] = (uv[9] * b + uv[0] * a) / (a+b);

	hds->AddPatchUV(patch, uv);
}

void makeStamps(HModelCache *hmc, int patchesBefore)
{
	HDecalContainer *hdc = hmc->GetChildDecalContainer();	if (hdc == nullptr) return;
	HDecal *hd = hdc->GetChildDecal();						if (hd == nullptr) return;
	//HDecal *hd = hmc->AddDecal();

	HDecalStamp *hds = hd->AddDecalStamp();

	for (UINT p=0; p<hmc->GetPatchCount(); p++)
	{
		HPatch *patch = hmc->GetPatch(p);
		if (getCPdecoration(patch->GetCP1()->GetHead()) >= 0.0f)
			if (patch != nullptr) addPatchUV(patch, hds, p);
	}

	// TODO: remove cp decoration (set inAlpha = 0 for all cps)
}

//-------------------------------------------------------------------------- M A I N

BOOL CHxtApp::TreeeZ( HModelCache *hmc, HActionCache *hac )
{
	// init
	int id = 0;
	estimatedtotaldepth = 0;
	totaldepth = 0;
	PointMap pointMap;
	pointMap.InitHashTable(997);

	HSpline *spline = hmc->GetHeadSpline();
	while (spline != nullptr)
	{
		HCP *ccp = spline->GetHeadCP();
		while (ccp != nullptr)
		{
			HCP *cp = ccp;
			if (cp == ccp->GetHead())
			{
				id = cp->GetID();
				if (id > maxid) { maxid = id; }
				Point p;
				p.id = id;
				p.cp = cp;
				p.pos = *(cp->GetPosition());
				p.done = FALSE;
				p.depth = 0;
				pointMap.SetAt(id, p);
			}
			if (ccp->IsLoop()) break;
			ccp = ccp->GetNext();
		}
		spline = spline->GetNextSpline();
	}

	HGroup *basegroup = FindGroup(hmc, String("base"));
	if (basegroup == nullptr)
	{
		AfxMessageBox(TEXT("\"base\" group missing."), MB_OK|MB_ICONSTOP, 0);
		return FALSE;
	}
	HGroupCP *gcp = nullptr;
	for (gcp = basegroup->GetGroupCP(); gcp; gcp = gcp->GetNext())
	{
		HCP *cp = gcp->GetCP();
		if (cp == cp->GetHead())
		{
			pointMap.RemoveKey(cp->GetID());
		}
	}

	if (debug == TRUE)
	{
		String s = "input: " + String(id) + " leaf nodes";
		AfxMessageBox(TEXT(s.buf), MB_OK|MB_ICONSTOP, 0);
	}

	hmc->SetChanged();
	hmc->FindPatches();
	GetHProject()->UpdateAllViews();
	int patchesBefore = hmc->GetPatchCount();

	// get properties
	HFloatProperty *p_thickness = nullptr;
	HFloatProperty *p_branchlength = nullptr;
	HFloatProperty *p_locality = nullptr;
	HFloatProperty *p_regularity = nullptr;
	HModel *hm = hac->EditWithModelCache(hmc);

	// create new chor with instance of model
	chor = hm->GetChor();

	try{
	//	HHashObject *hucp = (HHashObject *)hm->GetUserCategoryProperty(); // husercategoryproperty
	//	HHashObject *hucp = (HHashObject *)hm->FindChildByName("User Properties");	// TODO: try this. this might be compatible to versions prior to 11

		int i = 0;
		HHashObject *hucp = (HHashObject *)hm->GetPropertyAt(i);
		while ((hucp != nullptr) && (strcmp(hucp->GetName(),"User Properties") != 0))
		{
			hucp = (HHashObject *)hm->GetPropertyAt(++i);
		}

		p_thickness = (HFloatProperty *)hucp->FindChildByName("thickness");
		p_branchlength = (HFloatProperty *)hucp->FindChildByName("branchlength");
		p_locality = (HFloatProperty *)hucp->FindChildByName("locality");
		p_regularity = (HFloatProperty *)hucp->FindChildByName("regularity");
	}catch(...){}

	HGroupCP *newbase = nullptr;
	hmc->CopyExtrude(FALSE, basegroup->GetGroupCP(), &newbase);	// copy the base

	branch(hmc, hac, p_thickness, p_branchlength, p_locality, p_regularity, newbase, Vector(0,0,0), Vector(0,1,0), pointMap, 0);

	try{ hac->EndEditWithModelCache(hm); }catch(...){}

	String info = "TreeeZ 0.3\n(c) 2004 by kci:dnd\nMarcel Bricman\nhttp://www.kci-group.com/z/\n\nGenerated eZTree with " + String(totaldepth) + " levels.";
	AfxMessageBox(TEXT(info.buf), MB_OK|MB_ICONINFORMATION, 0);

	hmc->SetChanged();
	hmc->FindPatches();
	GetHProject()->UpdateAllViews();
	makeStamps(hmc, patchesBefore);

	hmc->SetChanged();
	return TRUE;
}