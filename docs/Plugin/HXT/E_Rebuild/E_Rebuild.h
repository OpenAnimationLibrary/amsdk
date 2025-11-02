// E_Rebuild.h : Haupt-Header-Datei für die DLL E_REBUILD
//

#if !defined(AFX_E_REBUILD_H__479F6AD3_03BD_428C_A830_9178CE44FC6F__INCLUDED_)
#define AFX_E_REBUILD_H__479F6AD3_03BD_428C_A830_9178CE44FC6F__INCLUDED_

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
#include "EPatch.h"
#include "ArrayEx.h"

/////////////////////////////////////////////////////////////////////////////
// CE_RebuildApp
// Siehe E_Rebuild.cpp für die Implementierung dieser Klasse
//
class EPatch;
class PatchList;
class Re_Patch;
class Re_PatchList;

struct EXTRUDEPOINTLIST {
    Vector pos;
    Vector newpos;
    Vector n_normal; //negatet normal
    float distance{}; //collission distance
    int az{}; //number of cp's on same pos
};

struct NPOINT {
    HCP *cp{};
    Vector pos;
    //	Vector n_normal; //negatet normal
    bool attached{};
    bool ismid{}; //workaround for extrude, midpoint of a org patch , should not be connectet
    int referpatch{}; //refer to originalpatch, where the cp is constructet from
};

struct GRUPPE {
    HGroup *hgroup{};
    Vector g_center;
    CString name{};
    CArrayEx<NPOINT, NPOINT> pointlist;
    CArrayEx<EXTRUDEPOINTLIST, EXTRUDEPOINTLIST> extrudelist;
    CArrayEx<EPatch, EPatch> patchlist_org;
    CArrayEx<EPatch, EPatch> patchlist_new;
};

struct PIDLIST {
    UINT id; //CP ID
    UINT az; //anzahl
};

struct PParameter {
    BOOL hasExplodegroups; //TRUE Model hat Exp_ Gruppen
    BOOL groupstrict; //true Nachbar 1Seite, FALSE Nachbar 1CP
    int maxPatches; //maximum Patches fuer Gruppe
    BOOL check_minextrude; //minimale Extrudiertief checken 
    BOOL reverseextrude; //extruding in normaldirection (for flat models)
    float minextrude; //minimale Extrudiertiefe
    float near_average; //fuer Extrudeposition averaging normals und distance
    float scale; //scalefactor for extruded patches
    BOOL randomscale;
    float minscale;
    float maxscale;

};

class CE_RebuildApp final : public CPluginApp {
public:
    CE_RebuildApp();
    ~CE_RebuildApp() override;
    BOOL OnModelCache(HModelCache *hmc);
    BOOL RebuildModelVariabel(HModelCache *hmc_org) const;
    BOOL RebuildModelGroups(HModelCache *hmc_org) const;
    void LoadSettings() const;
    void SaveSettings() const;

    PParameter *para{};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CE_RebuildApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CE_RebuildApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_E_REBUILD_H__479F6AD3_03BD_428C_A830_9178CE44FC6F__INCLUDED_)
