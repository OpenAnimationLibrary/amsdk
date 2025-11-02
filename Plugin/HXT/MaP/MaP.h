// MaP.h : Haupt-Header-Datei für die DLL MaP
//

#if !defined(AFX_MaP_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
#define AFX_MaP_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "F_Protos.h"
#include "HashFile.h"
#include "Matrix34.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HDecal.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CMaPApp
// Siehe MaP.cpp für die Implementierung dieser Klasse
//

class HModelCache;
class HGroupCP;
class HGroup;

class CMaPApp final : public CPluginApp {
public:

    CMaPApp();
    ~CMaPApp() override;
    BOOL OnModel(HModelCache *hmc);
    static BOOL FindMatch(HGroup *fgroup, CArray<HGroup *, HGroup *> &grouplist);
    static void GetGroupList(HModelCache *hmc, CArray<HGroup *, HGroup *> &grouplist);
    static void RemoveEmptyGroups(CArray<HGroup *, HGroup *> &grouplist);

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMaPApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMaPApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MaP_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
