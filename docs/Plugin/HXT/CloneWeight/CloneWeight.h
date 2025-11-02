// CloneWeight.h : Haupt-Header-Datei für die DLL CloneWeight
//

#if !defined(AFX_CloneWeight_H__F3A64077_398D_48DD_865B_D553CD857BAC__INCLUDED_)
#define AFX_CloneWeight_H__F3A64077_398D_48DD_865B_D553CD857BAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
// CCloneWeightApp
// Siehe CloneWeight.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

#ifdef _DEBUG
struct _WEIGHT {
    HSegmentCache *hsc;
    float weight;
};

struct _CPW {
    HCP *cp{};
    Vector pos;
    BOOL haveweight{};
    CArrayEx<_WEIGHT, _WEIGHT> weightlist;
};

struct _CPS {
    HCP *cp{};
    BOOL isassigned{};
    BOOL weightsource{};
    Vector pos;
};
#endif

struct CCW_CP {
    HCP *cp{};
    Vector pos;
};

struct Parameter {
    HModelCache *hmc;
    BOOL reassigncp;
    float max_dist;
};

class CCloneWeightApp final : public CPluginApp {
public:
    CCloneWeightApp();
    ~CCloneWeightApp() override;
    BOOL OnModel(HModelCache *hmc);
    BOOL Worker(HModelCache *hmc_org, HModelCache *hmc);
    void FillCPList(HModelCache *hmc_org, HModelCache *hmc);
    [[nodiscard]] BOOL CheckPosition(Vector pos_tocheck, Vector pos) const;
    static void RemoveOldWeight(HCP *cp);

    Parameter *para{};
    CArrayEx<CCW_CP, CCW_CP> cp_org;
    CArrayEx<CCW_CP, CCW_CP> cp_dest;
#ifdef _DEBUG
    CArrayEx<_CPS, _CPS> cps_list;
    CArrayEx<_CPW, _CPW> cpw_list;

    void DebugWeights(HModelCache *hmc, bool end = true);
    void FillCPSList(HModelCache *hmc);
    void FillWeightList(HModelCache *hmc, bool afterweighting);
#endif

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CCloneWeightApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CCloneWeightApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CloneWeight_H__F3A64077_398D_48DD_865B_D553CD857BAC__INCLUDED_)
