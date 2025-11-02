// Simple_Scatter.h : Haupt-Header-Datei für die DLL Simple_Scatter
//

#if !defined(AFX_Simple_Scatter_H__388FA50E_AC8A_4925_AA7B_174C02F9C170__INCLUDED_)
#define AFX_Simple_Scatter_H__388FA50E_AC8A_4925_AA7B_174C02F9C170__INCLUDED_

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
//#include "Rnd.h"

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

/////////////////////////////////////////////////////////////////////////////
// CSimple_ScatterApp
// Siehe Simple_Scatter.cpp für die Implementierung dieser Klasse
//

struct PARAMETER {
    HModelCache *hmc_target{};
    HModel *hm_target{};
    HModelCache *hmc_source{};
    HGroup *hgroup{};
    BOOL isgroup{};
    int azimport{};
    Vector rotate_min;
    Vector rotate_max;
    Vector scale_min;
    Vector scale_max;
    float uscale_min{};
    float uscale_max{};
    BOOL align{};
    BOOL xrotate{};
    BOOL yrotate{};
    BOOL zrotate{};
    BOOL xscale{};
    BOOL yscale{};
    BOOL zscale{};
    BOOL uniformscale{};
    //Bullet
    BOOL add_bullet{};
    float b_bounce{};
    float b_friction{};
    float b_density{};
    float b_weight{};
    BOOL b_calcweight{};
    int b_shape{};
};

struct MODELLIST {
    Vector bbmin;
    Vector bbmax;
};

class CSimple_ScatterApp final : public CPluginApp {
public:
    CSimple_ScatterApp() noexcept = default;
    ~CSimple_ScatterApp() override = default;
    CSimple_ScatterApp(const CSimple_ScatterApp&) = delete;
    CSimple_ScatterApp &operator= (const CSimple_ScatterApp&) = delete; 
    CSimple_ScatterApp(CSimple_ScatterApp &&) = delete; 
    CSimple_ScatterApp &operator=(CSimple_ScatterApp &&) = delete; 

    bool OnChorModel(HModel *hmodel);
    bool OnChorGroup(HGroup *hgroup);
    [[nodiscard]] bool ImportandSimulate() const;
    void GetSettings() const;
    void SaveSettings() const;

    PARAMETER *para{nullptr};

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CSimple_ScatterApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CSimple_ScatterApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Simple_Scatter_H__388FA50E_AC8A_4925_AA7B_174C02F9C170__INCLUDED_)
