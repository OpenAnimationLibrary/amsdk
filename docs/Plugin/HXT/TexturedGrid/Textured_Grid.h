// Textured_Grid.h : Haupt-Header-Datei für die DLL Textured_Grid
//

#if !defined(AFX_Textured_Grid_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
#define AFX_Textured_Grid_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_

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

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

/////////////////////////////////////////////////////////////////////////////
// CTextured_GridApp
// Siehe Textured_Grid.cpp für die Implementierung dieser Klasse
//

struct PParameter {
    HClipCacheContainer *hclipcache{};
    HClip *clip{};
    Vector2 size;
    Vector2 subdiv;
    int num_models{};
    Vector2 offset;
    int m_orientation{};
    String modelname;
    int use_offset_first{};
};

class CTextured_GridApp final : public CPluginApp {
public:
    PParameter *para{};

    CTextured_GridApp() noexcept = default;
    ~CTextured_GridApp() override = default;
    BOOL OnPrimitiveWizard();
    static void Glue(HPatch *patch, HDecalStamp *stamp, float vertical_span, float horizontal_span, float start_y, float start_x, float ofs_x, float ofs_y);
    void BuildGrid(HModelCache *hmc, int modelnum) const;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CTextured_GridApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CTextured_GridApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Textured_Grid_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
