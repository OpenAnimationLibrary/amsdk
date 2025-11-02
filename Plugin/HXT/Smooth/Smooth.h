// Smooth.h : Haupt-Header-Datei für die DLL Smooth
//

#if !defined(AFX_Smooth_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
#define AFX_Smooth_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "HashFile.h"
#include "F_Protos.h"
#include "Matrix34.h"
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

/////////////////////////////////////////////////////////////////////////////
// CSmoothApp
// Siehe Smooth.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;

struct SPLINE {
    int azcp{};
    HSpline *hsp{};
    CArray<HCP *, HCP *> hcp;
    Vector *pos_org{};
    Vector *pos_new{};
    bool *pos_changed{};
};

struct CSPLINE {
    int azcp{};
    bool use{};
    HSpline *hsp{};
    CArray<HCP *, HCP *> hcp;
};

struct PARAMETER {
    int recurse;
    int azspline;
    bool lock_x;
    bool lock_y;
    bool lock_z;
    bool complet; //1 ganze Spline, 0 Teilstueck
    bool half; //1 50%, 0 100%
    int allsplines; // 0 1Spline meiste CP, 1 alle, 2 minimum CP's
    int min_cp;
    SPLINE *spline;
};

class CSmoothApp final : public CPluginApp {
public:
    CSmoothApp();
    ~CSmoothApp() override;
    BOOL OnGroup(HModelCache *hmc, HGroup *hg);
    BOOL Init(HModelCache *hmc, HGroup *hg);
    static int GetSplineaz(HModelCache *hmc, HGroup *hg, int az);
    BOOL Work(HModelCache *hmc, HGroup *hg) const;
    static int GetCPaz(HSpline *hsp);
    BOOL GetSplines(HModelCache *hmc, HGroup *hg) const;
    int ReorderCP(CSPLINE *sortspline, int splinenr, int azspline) const;
    BOOL SmoothSpline(HModelCache *hmc, int nr) const;
    BOOL SetSpline(HModelCache *hmc, int nr) const;
    BOOL CheckConnect(HModelCache *hmc) const;
    BOOL ChangeSplinePos(HModelCache *hmc, int nr) const;
    PARAMETER *para{};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CSmoothApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CSmoothApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Smooth_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
