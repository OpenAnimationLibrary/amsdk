// ReSurface.h : Haupt-Header-Datei für die DLL ReSurface
//

#if !defined(AFX_ReSurface_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
#define AFX_ReSurface_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_

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
// CReSurfaceApp
// Siehe ReSurface.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct CPLIST {
    HCP *cp{};
    HCPInstance *cpinstance{};
    Vector org_pos;
    Vector new_pos;
    Vector normal;
    bool pos_set{};
};

struct CP_INSTANCE {
    int frame{};
    HCPInstance *cpinstance{};
    Vector pos;
};

struct PARAMETER {
    float distance;
    float maxdistance;
    BOOL isinchor;
    BOOL instancing;
    BOOL reversenormal;
    BOOL usegroupcenter;
    BOOL ignore_x;
    BOOL ignore_y;
    BOOL ignore_z;
};

class CReSurfaceApp final : public CPluginApp {
public:
    CReSurfaceApp();
    ~CReSurfaceApp() override;
    BOOL OnGroup(HGroup *hg);
    BOOL OnModel(HModel *hm);
    BOOL OnModelCache(HModel *hm) const;
    BOOL OnModelInstance(HModel *hm) const;
    void LoadSettings();
    void SaveSettings() const;
    PARAMETER *para{};
    HProgressBar *pbar{};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CReSurfaceApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CReSurfaceApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ReSurface_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
