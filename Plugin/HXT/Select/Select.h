// Select.h : Haupt-Header-Datei für die DLL SELECT
//

#if !defined(AFX_SELECT_H__86C92CDF_B0C3_4BD5_9977_FA9848D31F45__INCLUDED_)
#define AFX_SELECT_H__86C92CDF_B0C3_4BD5_9977_FA9848D31F45__INCLUDED_

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
#include "struct.h"
#include "EPatch.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectApp
// Siehe Select.cpp für die Implementierung dieser Klasse
//
class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;
class EPatch;

class CSelectApp final : public CPluginApp {
public:
    CSelectApp();
    ~CSelectApp() override;
    BOOL OnWork(HModelCache *hmc);
    BOOL Work(HModelCache *hmc) const;
    Parameter *para{};
    Matrix34 screen;
    void LoadSettings() const;
    void SaveSettings() const;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CSelectApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CSelectApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_SELECT_H__86C92CDF_B0C3_4BD5_9977_FA9848D31F45__INCLUDED_)
