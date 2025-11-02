#pragma once

#include "StdAfx.h"
#ifndef __AFXWIN_H__
#error include 'StdAfx.h' before including this file for PCH
#endif

#include "E_Rebuild.h"

#ifndef MyClassEPatch
#define MyClassEPatch

class EPatch {
public:
    BOOL ishooked{}; //Patch is builded with a hook, cannot compute complementary CP's at this time
    int numpoint{}; //3 4 5 Pointpatch
    Vector cppos[6]; //Patchcenter,CP1,CP2,CP3,CP4,CP5 , cpposition
    Vector ndir[6]; //Patchcenter,CP1,CP2,CP3,CP4,CP5 , normaldirection
    Vector sdpos[6]; //3P Patchcenter,CP1-CP2,CP2-CP3,CP3-CP1 position
    //4P Patchcenter,CP1-CP2,CP2-CP3,CP3-CP4,CP4-CP1
    //5P Patchcenter,CP1-CP2,CP2-CP3,CP3-CP4,CP4-CP5,CP5-CP1
    Vector pos[16]; //same as getpatchpoint
    UINT pid1{}, pid2{}, pid3{}, pid4{}, pid5{}; //PatchID
    Vector bb_min[6]; //Bbox minimum OrgPatch,SDPatch1,SDPatch2,SDPatch3,SDPatch4,SDPatch5
    Vector bb_max[6]; //Bbox maximum OrgPatch,SDPatch1,SDPatch2,SDPatch3,SDPatch4,SDPatch5
    BOOL isinuse{}; //fuer Groupcreation Explode true in Gruppe, false frei
    HPatch* opatch{}; //refered Originalpatch
    HPatch5* opatch5{}; //refered Originalpatch5
    float dist[6]{}; //Collission Distance Patchcenter - Collission with other Patch in the same model (negatet Normaldirection)

    EPatch() noexcept = default;
    explicit EPatch(HPatch* hp);
    explicit EPatch(HPatch5* hp);
    void Init(HPatch* hp);
    void Init(HPatch5* hp);
    BOOL IsNeighbor(const EPatch* ep, BOOL side) const;
    [[nodiscard]] UINT LowestPID() const;
};

struct NachBar {
    int neighbor[10]; //Nachbarpatches ueber Patchlist
    int azneighbor;
};

class PatchList {
public:
    PatchList();
    explicit PatchList(const EPatch &epatch);
    explicit PatchList(const NachBar &neighbor);
    void Sort(HProgressBar* p_bar);
    void HitDistance(HProgressBar* p_bar, HModelCache* hmc);
    void GetNeighbors(HProgressBar* p_bar, BOOL strict); //strict=true nur Patches mit 1 Seite als Nachbar,false 1 CP als Nachbar
    void LowestID();
    CArray<EPatch, EPatch> patchlist;
    CArray<NachBar, NachBar> neighborlist;
};
#endif
