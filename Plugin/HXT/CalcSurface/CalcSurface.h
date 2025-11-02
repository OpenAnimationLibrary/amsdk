// CalcSurface.h : Haupt-Header-Datei für die DLL CALCSURFACE
//

#if !defined(AFX_CALCSURFACE_H__1723C3DC_550D_46B0_91C5_4168B779BAF6__INCLUDED_)
#define AFX_CALCSURFACE_H__1723C3DC_550D_46B0_91C5_4168B779BAF6__INCLUDED_

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
#include "SDK/HAction.h"

/////////////////////////////////////////////////////////////////////////////
// CCalcSurfaceApp
// Siehe CalcSurface.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

struct Detail {
    String name;
    double surface{};
};

struct Parameter {
    double surface{}; //calculatet surface
    HFloatProperty *fPSampleArea{}; //property sample area
    float fVSampleArea{}; //value sample area
    float fVSampleArea_org{}; //original value sample area
    HIntProperty *iPPhotonCast{}; //property photon number
    int iVPhotonCast{}; //value photon number
    int iVPhotonCast_org{}; //original value photon number
    HIntProperty *iPPhotonSample{}; //property photon samples
    int iVPhotonSample{}; //value photon samples
    int iVPhotonSample_org{}; //original value photon samples
    CArray<Detail, Detail> detail;
};

class CCalcSurfaceApp final : public CPluginApp {
public:
    CCalcSurfaceApp() = default;
    ~CCalcSurfaceApp() override = default;
    BOOL OnChor(HChor *hchor);
    BOOL CalculateChor(HChor *hchor) const;
    BOOL GetPropRecurse(HProperty *akt_prop) const;
    void GetProperty(HChor *obj) const;
    static double GetArea(HModel *hm);
    Parameter *para{nullptr};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CCalcSurfaceApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CCalcSurfaceApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CALCSURFACE_H__1723C3DC_550D_46B0_91C5_4168B779BAF6__INCLUDED_)
