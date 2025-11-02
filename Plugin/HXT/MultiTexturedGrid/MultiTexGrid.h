// MultiTexGrid.h : Haupt-Header-Datei für die DLL MultiTexGrid
//

#if !defined(AFX_MultiTexGrid_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
#define AFX_MultiTexGrid_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_

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
#include "SDK/HImage.h"
#include "SDK/HDecal.h"
#include <vector>

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

/////////////////////////////////////////////////////////////////////////////
// CMultiTexGridApp
// Siehe MultiTexGrid.cpp für die Implementierung dieser Klasse
//
struct ImageParameters {
    Vector2 size;
    Vector2 gridsize;
    String filename;
    BOOL issequence;
};

struct PParameter {
    std::vector<ImageParameters> images{};
    HClipCacheContainer *hclipcache{};
    Vector2 subdiv;
    Vector fpos; //firstpos in chor
    Vector pos_ofs; //offset for position in chor can be negative (if 0 than viewaxis width/2 pic0 + width/2 pic1
    Vector2 offset;
    int m_orientation{};
    String modelname;
    int add_to_chor{};
    int use_model{}; //model or layer
    int create_cookie{};
};

class CMultiTexGridApp final : public CPluginApp
{
public:
    CMultiTexGridApp();
    ~CMultiTexGridApp() override;
    BOOL OnChor(HChor *hchor);
    static void Glue(HPatch *patch, HDecalStamp *stamp, float vertical_span, float horizontal_span, float start_y, float start_x);
    void BuildGrid(HModelCache *hmc, int modelnum) const;
    PParameter *para{};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMultiTexGridApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMultiTexGridApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MultiTexGrid_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
