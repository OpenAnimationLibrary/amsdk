// ResampleSpline.h : Haupt-Header-Datei für die DLL ResampleSpline
//

#if !defined(AFX_ResampleSpline_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
#define AFX_ResampleSpline_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_

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

/////////////////////////////////////////////////////////////////////////////
// CResampleSplineApp
// Siehe ResampleSpline.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct PARAMETER {
    float splinelength;
    float neededdistance;
    float zvalue;
    int iteration;
    int zcount;
    int direction;
    int cpcount;
    BOOL extrude;
};

class CResampleSplineApp final : public CPluginApp {
public:
    CResampleSplineApp();
    ~CResampleSplineApp() override;

    BOOL OnCP(HCP *cp) const;
    BOOL OnCPInstance(HCPInstance *cp) const;

    BOOL OnGroup(HGroup *hg) const;
    //	BOOL OnGroup2(HGroup *hg);

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CResampleSplineApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CResampleSplineApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ResampleSpline_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
