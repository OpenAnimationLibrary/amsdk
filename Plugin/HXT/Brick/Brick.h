// Brick.h : Haupt-Header-Datei für die DLL Brick
//

#if !defined(AFX_Brick_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
#define AFX_Brick_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_

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
#include "SDK/HConstra.h"

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

/////////////////////////////////////////////////////////////////////////////
// CBrickApp
// Siehe Brick.cpp für die Implementierung dieser Klasse
//

struct PParameter {
    HProject *hproject;
    HModelCache *hmc;
    int row;
    int column;
    BOOL scale;
    float position_z;
    float space_x;
    float space_y;
    BOOL add_bullet;
    float b_bounce;
    float b_friction;
    float b_density;
    float b_weight;
    BOOL b_calcweight;
    int b_shape;
    BOOL userfolder;
};

class CBrickApp final : public CPluginApp {
public:
    CBrickApp() noexcept = default;
    ~CBrickApp() override = default;
    BOOL OnChor(HChor *hchor);
    PParameter *para{};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CBrickApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CBrickApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Brick_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
