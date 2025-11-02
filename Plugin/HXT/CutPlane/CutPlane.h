// CutPlane.h : Haupt-Header-Datei für die DLL CutPlane
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
#include "MDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CCutPlaneApp
// Siehe CutPlane.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct CUT_SEGMENT {
    HCP *cp1{};
    HCP *cp2{};
    Vector pos_cp1;
    Vector pos_cp2;
};

struct CUT_SPLINE {
    HSpline *sp{};
    CArrayEx<CUT_SEGMENT, CUT_SEGMENT> seg;
};

struct CUT_PLANE {
    BOOL infinite{};
    BOOL addring{};
    BOOL break_splines{};
    BOOL cut_splines{};
    float max_value{};
    HCP *cp[6]{};
    HSpline *sp1{}, *sp2{};
    HGroup *hg{};
    HPatch *hp{};
    Vector normal;
    Vector point;
    float offset{};
};

struct CCW_CP {
    Vector pos;
    Vector pos_sort;
    HSpline *hsp{};
    HCP *cp_create{};
    HCP *before_cp{};
    HCP *after_cp{};
    HCP *new_cp{};
    HCP *new_cp1{};
    //   HPatch *hp;
};

struct CUT_HCP {
    HCP *cp{};
    Vector pos;
    BOOL tomove{};
};

class CCutPlaneApp final : public CPluginApp {
public:
    CCutPlaneApp();
    ~CCutPlaneApp() override;
    BOOL OnStart(HModelCache *_hmc);
    BOOL UpdateSplineList();
    BOOL CreatePlane();
    void Cleanup();
    void OnSelectionChanged(bool check) const;
    void UpdateCutCPs();
    void ApplyCutCPs();
    void MovePartModel();

    CArrayEx<CUT_SPLINE, CUT_SPLINE&> sp_list;
    CArrayEx<CCW_CP, CCW_CP&> cp_list;
    CArrayEx<CUT_HCP, CUT_HCP&> move_cp;
    CUT_PLANE plane;
    HModelCache *hmc{};
    MDialog *mdlg;

#ifdef _DEBUG
    FileStream fsd;
    void DebugOut();
#endif

    //{{AFX_VIRTUAL(CCutPlaneApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CCutPlaneApp)
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

extern CCutPlaneApp theApp;
