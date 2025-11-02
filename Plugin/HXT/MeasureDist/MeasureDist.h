// MeasureDist.h : Haupt-Header-Datei für die DLL MeasureDist
//

#if !defined(AFX_MeasureDist_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
#define AFX_MeasureDist_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "F_Protos.h"
#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"

/////////////////////////////////////////////////////////////////////////////
// CMeasureDistApp
// Siehe MeasureDist.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

class CMeasureDistApp final : public CPluginApp {
public:
    CMeasureDistApp();
    ~CMeasureDistApp() override;
    BOOL OnGroup(HGroup *hg) const;
    BOOL OnCP(HCP *cp) const;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMeasureDistApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMeasureDistApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MeasureDist_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
