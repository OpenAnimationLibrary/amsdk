// Push.h : Haupt-Header-Datei für die DLL Push
//

#if !defined(AFX_Push_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
#define AFX_Push_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

//#include "resource.h"		// Hauptsymbole
//#include "Matrix34.h"
#include "HashFile.h"
//#include "F_Protos.h"
//#include "SDK/Entry.h"
#include "SDK/Misc.h"
//#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
//#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
//#include "SDK/HProgres.h"
//#include "SDK/HChor.h"
//#include "SDK/HLight.h"
#include "SDK/HCamera.h"
//#include "SDK/HAction.h"
//#include "SDK/HConstra.h"
//#include "SDK/HRelatio.h"

/////////////////////////////////////////////////////////////////////////////
// CPushApp
// Siehe Push.cpp für die Implementierung dieser Klasse
//

class HModelCache;

struct PARAMETER final {
    HModelCache *hmc;
    float distance[10];
    int frame[10];
    BOOL keyframe[10];
    int makekeys; //0 model,1 Pose, 2 Action
    BOOL pose0; //false pose 0->100, true pose -100 -> 100
};

class CPushApp final : public CPluginApp {
public:
    CPushApp();
    ~CPushApp() override;

    BOOL OnModelInstance(HModel *hm);
    BOOL OnModel(HModelCache *hmc);
    BOOL OnGroupInstance(HGroup *hg);
    BOOL OnGroup(HGroup *hg);
    BOOL WorkInstance(HActionCache *hactioncache, HChor *hchor, BOOL isaction);
    BOOL Work();
    void CalculateAllNormalsInstance();
    void CalculateAllNormals();

    PARAMETER *para{nullptr};
    CArray<HCP *, HCP *> groupcps;
    CMap<HCP *, HCP *, Vector, Vector> AllCPs;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CPushApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CPushApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Push_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
