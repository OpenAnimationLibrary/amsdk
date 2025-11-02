// MirrorBone.h : Haupt-Header-Datei für die DLL MirrorBone
//

#if !defined(AFX_MirrorBone_H__F3A64077_398D_48DD_865B_D553CD857BAC__INCLUDED_)
#define AFX_MirrorBone_H__F3A64077_398D_48DD_865B_D553CD857BAC__INCLUDED_

#pragma once

#ifndef __AFXWIN_H__
#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "Matrix34.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/HChor.h"
#include "SDK/HLight.h"
#include "SDK/HCamera.h"
#include "SDK/HAction.h"
#include "SDK/HConstra.h"
#include "SDK/HCPWeight.h"
#include "SDK/HNullObject.h"
#include "ArrayEx.h"

/////////////////////////////////////////////////////////////////////////////
// CMirrorBoneApp
// Siehe MirrorBone.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct MB_WEIGHT {
    HSegmentCache *hsc{nullptr};
    float weight{};
};

struct MB_WEIGHT_S {
    HSegmentCache *hsc{nullptr};
    float weight{};
    int mirror{};
    bool ismirror{false};
};

struct MB_CPW {
    HCP *cp{nullptr};
    Vector pos;
    Vector m_pos;
    bool haveweight{false};
    CArrayEx<MB_WEIGHT, MB_WEIGHT> weightlist;
};

struct MB_CPS {
    HCP *cp{nullptr};
    BOOL isassigned{FALSE};
    BOOL weightsource{FALSE};
    Vector pos;
    Vector m_pos;
};

struct MB_BONE {
    BOOL isnullbone{FALSE};
    BOOL ismidbone{FALSE};
    BOOL issource{FALSE}; //true, when on sourceside
    BOOL ischanged{FALSE};
    BOOL ismodelbone{FALSE};
    int mirror{-1}; //bonenumber , that is mirrorbone for this, -1 if no mirror->create
    HBoneCache *hbc{nullptr};
    HSegmentCache *hsc{nullptr};
    HNullObjectCache *hnoc{nullptr};
    Vector start;
    Vector end;
    Vector m_start; //mirrored
    Vector m_end; //mirrored
    HBoneCache *parent{nullptr};
    HBoneCache *child{nullptr};
};

struct Parameter {
    bool model_ischanged{};
    BOOL sourceside{}; //true left,false right
    BOOL groupunassigned{};
    BOOL groupnotmirrors{};
    BOOL excludestartbone{};
    BOOL use_tolerance_bones{};
    BOOL use_tolerance_cps{};
    BOOL correct_pos_mirrorbone{};
    BOOL name_only{}; //check mirror only for names
    BOOL write_log{}; //logfile for existing conflicts
    BOOL extended_log{};
    BOOL weight_unweighted{}; //only for cp's at X0
    BOOL clear_target{}; //clear all (!) cpweights from targetside, before assigning new
    BOOL start_from_group{};
    BOOL casesensitive{};
    float tolerance_bones{};
    float tolerance_cps{};
    float tolerance_midbone{};
    CString removestring{};
    CString addstring{};
    String path;
    HModelCache *hmc{nullptr};
};

class CMirrorBoneApp final : public CPluginApp {
public:
    Parameter *para = nullptr;
    CArrayEx<MB_BONE, MB_BONE> bone_list;
    CArrayEx<MB_CPS, MB_CPS> cps_list;
    CArrayEx<MB_CPW, MB_CPW> cpw_list;
    FileStream fs_log;
    String logname_ext;
    HProgressBar *bar = nullptr;

    CMirrorBoneApp();
    ~CMirrorBoneApp() override;
    BOOL OnBone(HModelCache *hmc, HBoneCache *hbc);
    BOOL OnGroup(HModelCache *hmc, HGroup *hg);

    BOOL Worker(HModelCache *hmc, HBoneCache *hbc);
    BOOL WorkerGroup(HModelCache *hmc, HGroup *hg);

    void FillBoneList(HModelCache *hmc);
    void FillBoneList(HModelCache *hmc, HBoneCache *hbc_start);
    void FillCPSList(HModelCache *hmc);
    BOOL CheckPositionBone(int bone1, int bone2);
    [[nodiscard]] BOOL CheckPositionBoneX0(Vector pos_start, Vector pos_end) const;
    void ReformatBoneName(const CString &oldname, CString &newname, bool always) const;
    //	CString ReformatBoneName(CString oldname,bool always);
    void MirrorBoneBranch(HModelCache *hmc, HBoneCache *start_hbc);
    HBoneCache *FindParentByName(CArrayEx<HBoneCache *, HBoneCache *> bcdup, HBoneCache *parent_org, bool isnullbone) const;
    HBoneCache *FindParentFromList(HBoneCache *parent_org, bool isnullbone);
    int FindBoneFromList(const HBoneCache *bonetofind);
    HSegmentCache *FindBoneFromList(const HSegmentCache *bonetofind);
    void MirrorSegmentBone(HSegmentCache *hsc_org, HSegmentCache *hsc_dup);
    [[nodiscard]] BOOL CheckPosition(Vector pos_tocheck, Vector pos) const;
    void GroupUnassigned(HModelCache *hmc);
    static void RemoveOldWeight(HCP *wcp);

    void FillWeightList(HModelCache *hmc, bool afterweighting);
    void MirrorWeight();
    bool ConflictsWeights();
    bool FindBoneFromList(const String &bonename);
    bool WeightAdd(int i, int k);
    void CheckUnWeighted(int i);
    void ClearTargetWeight();
    bool CPIsValidAssigned(HCP *cp);
    void CheckAssignment();
    void GroupNoMirrors(HModelCache *hmc);

    void SaveSettings();
    void LoadSettings() const;
    void Cleanup();

    void DebugWeightsBefore();
    void DebugWeightsAfter();

#ifdef _DEBUG
    void Debug();
    FileStream fs;
#endif
    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMirrorBoneApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMirrorBoneApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MirrorBone_H__F3A64077_398D_48DD_865B_D553CD857BAC__INCLUDED_)
