#include "stdafx.h"
//Structuren
/*
struct Point
{
    HCP *cp;
	UINT id;
    Vector pos;
	Vector extrudedir;
    bool attached;
};

struct Patch
{
	Point *point;
	int az_point;
};

struct Org_Patch
{
	HPatch   *hpatch;
	HPatch5  *hpatch5;
	HCP      *hcp[5];
	int      patchpoint; //3,4,5 Pointpatch
	PatchID  pid;
	PatchID5 pid5;
	Vector   pos[15]; //Positionen mit tangenten
	Vector   newpos[11]; //neue Positionen berechnet
	Vector   normaldir;
	Vector   normalreverse;
	Vector   extrudedeep;
	Vector   patchmid;
	Vector   bb_min;
	Vector   bb_max;
};

struct Gruppe
{
	Patch *patch;
	Org_Patch *org_patch;
	HGroup *hg;
	int  az_patch;
};
*/

struct Gruppe
{
	PatchList *o_patch;
//	Org_Patch *org_patch;
	HGroup *hg;
	int  az_patch;
};

struct PParameter
{
	bool hasExplodegroups; // true Model hat Exp_ Gruppen
	int  azExplodegroups; //Anzahl Explodegroups 
	int  minPatches; //minimum Patches fuer Gruppe
	int  maxPatches; //maximum Patches fuer Gruppe
};