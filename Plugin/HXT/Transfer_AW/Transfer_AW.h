// Transfer_AW.h : Haupt-Header-Datei für die DLL Transfer_AW
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#ifndef WINVER
#define WINVER 0x0400
#endif

#include "resource.h"		// Hauptsymbole
#include "Matrix34.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/HCPWeight.h"
#include "ArrayEx.h"

/////////////////////////////////////////////////////////////////////////////
// CTransfer_AWApp
// Siehe Transfer_AW.cpp für die Implementierung dieser Klasse
//
#define fround(A, B)   (float)(floor((A) * pow(10.F, (B)) + .5F) / pow(10.F, (B)))

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct TAW_REF {
    int group_nr{0};
    int cp_nr{0};
};

struct TAW_NOFLEX {
    HGroup *hg{nullptr};
    CArrayEx<int, int&> refer;
    CArrayEx<TAW_REF, TAW_REF&> ref;
};

struct TAW_DIST {
    float dist{0};
    UINT cp_id{0};
    int cp_nr{0};
    int cp_nr_w{0};
    int bone_nr{0};
};

struct TAW_DIST2 {
    TAW_DIST dist;
    int weight{0};
};

struct TAW_BONESORT {
    int bone_nr{0};
    int az{0};
};

struct ALIGN_BBOX {
    Vector bmin;
    Vector bmax;
};

struct TAW_BONELIST {
    ALIGN_BBOX bbox;
    Vector start;
    Vector end;
    HSegmentCache *hsc{nullptr};
};

struct MB_WEIGHT {
    HSegmentCache *hsc{nullptr};
    float weight{0};
};

struct TAW_LORES {
    int refer{0};
    bool has_weight{false};
    CArrayEx<MB_WEIGHT, MB_WEIGHT&> weightlist;
};

struct TAW_HIRES {
    int refer{0};
    bool isassigned{false};
    bool isnoflex{false};
    bool has_weight{false};
    int az_dist_lores{0};
    TAW_DIST lores_dist[16];
    int az_dist_hires{0};
    TAW_DIST hires_dist[16];
    CArrayEx<MB_WEIGHT, MB_WEIGHT&> weight_first;
    CArrayEx<MB_WEIGHT, MB_WEIGHT&> weight_second;
};

struct TAW_GROUP_HIRES {
    HGroup *hg{nullptr};
    CArrayEx<TAW_HIRES, TAW_HIRES&> cplist;
};

struct TAW_GROUP_LORES {
    HGroup *hg{nullptr};
    CArrayEx<TAW_LORES, TAW_LORES&> cplist;
};

struct TAW_GROUP_PAIR {
    TAW_GROUP_LORES lores;
    TAW_GROUP_HIRES hires;
};

struct CCW_CP {
    HCP *cp{nullptr};
    Vector pos;
    int bone_nr{0};
    UINT id{0};
};

struct W_PARA {
    int pass1_cp{0};
    int pass2_cp{0};
    float smooth{0};
    bool has_noflex{false};
    BOOL alternate_hiresdist{FALSE};
    int az_smoothpass{0};
    BOOL proceed_nohidden{FALSE};
    HProgressBar *p_bar{nullptr};
};

class CTransfer_AWApp final : public CPluginApp {
public:
    CTransfer_AWApp();
    ~CTransfer_AWApp() override;
    BOOL OnStart(HModelCache *hmc);
    void Cleanup();

    void Work(HModelCache *hmc);
    void Compute_Dist_LoRes(TAW_GROUP_LORES &lores, TAW_HIRES &hires); //aendern global zuviele copys für mac
    void Compute_Dist_HiRes(TAW_GROUP_HIRES &hires_group, TAW_HIRES &hires); //aendern global
    void Compute_Dist_HiRes_alternate(TAW_GROUP_HIRES &hires_group, TAW_HIRES &hires); //aendern global
    void Resort_Dist_HiRes(TAW_HIRES &hires); //aendern global
    void CorrectBones_Dist_Hires(TAW_HIRES &hires); //aendern global
    void AssignBones_Hires_FirstPass(TAW_HIRES &hires); //aendern global
    void AssignBones_Hires_SecondPass(TAW_HIRES &hires); //aendern global
    void CorrectBones_NoFlex(TAW_NOFLEX &noflex);
    void Weight_FirstPass(TAW_GROUP_LORES &lores, TAW_HIRES &hires, int az); //aendern global
    void Weight_SecondPass(TAW_GROUP_HIRES &hires_group, TAW_HIRES &hires, int az); //aendern global
    static void Merge_WeightPasses(TAW_HIRES &hires, float smooth); //aendern global
    void Assign_Weight(TAW_HIRES &hires);
    void CorrectWeight_NoFlex(TAW_NOFLEX &noflex);
    void GetSettings() const;
    void SaveSettings() const;

    W_PARA *para{nullptr};
    CArrayEx<TAW_GROUP_PAIR, TAW_GROUP_PAIR&> group_pair;
    CArrayEx<TAW_BONELIST, TAW_BONELIST&> bone_list;
    CArrayEx<CCW_CP, CCW_CP&> cp_list;
    CArrayEx<TAW_NOFLEX, TAW_NOFLEX&> flex_list;
    TAW_DIST *_dist{nullptr};

#ifdef _DEBUG
    FileStream fsd;
    void Debugoutput(TAW_HIRES hires);
#endif

    //{{AFX_VIRTUAL(CTransfer_AWApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CTransfer_AWApp)
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

extern CTransfer_AWApp theApp;
