// Connect.h : Haupt-Header-Datei für die DLL CONNECT
//

#if !defined(AFX_CONNECT_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
#define AFX_CONNECT_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_

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

/////////////////////////////////////////////////////////////////////////////
// CConnectApp
// Siehe Connect.cpp für die Implementierung dieser Klasse
//

#define EPS  1e-10
//#define EPS  0.00000001

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct PARA final {
    float tol;
    float min_toleranz;
    BOOL modus; //true spline, false cp
};

struct INTERSECT final {
    Vector pos_spline1;
    Vector pos_spline2;
    double distanz{};
};

struct BBOX final {
    Vector vMin;
    Vector vMax;
};

struct SEGMENT final {
    HCP *startcp{};
    HCP *endcp{};
    Vector cp1_pos;
    Vector cp1_it;
    Vector cp2_pos;
    Vector cp2_ot;
    Vector *pos{};
    int azpos{};
    BBOX boundingbox;
};

struct LINE final {
    int azsegment{};
    int id{};
    BBOX boundingbox;
    SEGMENT *segment{};
};

struct CPLIST final {
    HCP *hcp{};
    Vector pos;
};

class CConnectApp final : public CPluginApp {
public:
    CConnectApp();
    ~CConnectApp() override;
    BOOL OnModel(HModelCache *hmc);
    BOOL ModelWorking(HModelCache *hmc) const;
    BOOL ModelCPWorking(HModelCache *hmc) const;
    BOOL CheckIntersection(HModelCache *hmc, SEGMENT seg1, SEGMENT seg2, int &stop) const;
    PARA *para{};
    //	double toleranz;
    //	double min_toleranz;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CConnectApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CConnectApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CONNECT_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
