#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "Select.h"

#define HI_PI 3.14159265358979323846264338327950288419716939937510E+00
#define RAYAABB_EPSILON 0.00001f
#define IR(x)	((unsigned&)(x))

class EPatch {
public:
    EPatch() noexcept = default;
    EPatch(HPatch *hp, const Matrix34 &screen);
    EPatch(HPatch5 *hp, const Matrix34 &screen);
    void Init(HPatch *hp, const Matrix34 &screen);
    void Init(HPatch5 *hp, const Matrix34 &screen);
    bool IsNeighbor(const EPatch *ep, bool side) const;
    bool HitTest(Vector start, Vector direction, Vector &hitpoint, double &distanz, bool subpatch) const;
    //subpatch true all subpatches checked for minimum distance

    bool ishooked{}; //Patch is builded with a hook, cannot compute complementary CP's at this time
    int numpoint{}; //3 4 5 Pointpatch
    Vector cppos[6]; //Patchcenter,CP1,CP2,CP3,CP4,CP5
    Vector ndir[6]; //Patchcenter,CP1,CP2,CP3,CP4,CP5
    Vector sdpos[6]; //3P Patchcenter,CP1-CP2,CP2-CP3,CP3-CP1
    //4P Patchcenter,CP1-CP2,CP2-CP3,CP3-CP4,CP4-CP1
    //5P Patchcenter,CP1-CP2,CP2-CP3,CP3-CP4,CP4-CP5,CP5-CP1
    Vector pos[16]; //same as getpatchpoint
    UINT pid1{}, pid2{}, pid3{}, pid4{}, pid5{}; //PatchID
    Vector bb_min[6]; //Bbox minimum OrgPatch,SDPatch1,SDPatch2,SDPatch3,SDPatch4,SDPatch5
    Vector bb_max[6]; //Bbox maximum OrgPatch,SDPatch1,SDPatch2,SDPatch3,SDPatch4,SDPatch5
    HCP *cp1_1{}, *cp2_1{}, *cp3_1{}, *cp4_1{}, *cp5_1{}; //original CP's from GetCP1 and so one
    HCP *cp1_2{}, *cp2_2{}, *cp3_2{}, *cp4_2{}, *cp5_2{}; //complementary CP's (next CP on the spline from the Original CP)
    HPatch *opatch{}; //referenzierter Originalpatch
    HPatch5 *opatch5{}; //referenzierter Originalpatch
};
