// Midicontrol.h : Haupt-Header-Datei für die DLL MIDICONTROL
//

#if !defined(AFX_MIDICONTROL_H__6A1DE8E0_A071_444C_ADA4_9A2561A5B457__INCLUDED_)
#define AFX_MIDICONTROL_H__6A1DE8E0_A071_444C_ADA4_9A2561A5B457__INCLUDED_

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
#include "SDK/HCamera.h"
#include "SDK/HAction.h"
#include "SDK/HMaterial.h"
#include "SDK/HLight.h"
#include <mmsystem.h>
#include "structuren.h"

/////////////////////////////////////////////////////////////////////////////
// CMidicontrolApp
// Siehe Midicontrol.cpp für die Implementierung dieser Klasse
//
class HCP;
class HModel;
class HModelCache;
class HAction;
class HGroup;
class HGroupCP;
class HLight;

class CMidicontrolApp final : public CPluginApp {
public:
    CMidicontrolApp();
    ~CMidicontrolApp() override;
    PARAMETER *para{};
    [[nodiscard]] BOOL Init() const;
    BOOL Objectstart(HHashObject *hobject);
    BOOL Chorstart(HChor *hchor);
    BOOL Chorworking(HChor *hchor) const;
    BOOL GetPropertiesRecurse(HProperty *akt_prop, int nummer, int &azprop) const;
    BOOL GetObjRecurse(HHashObject *obj, int nummer, int &azprop) const;
    void GetProperties(int nummer) const;
    static BOOL GetAzPropRecurse(HProperty *akt_prop, int &azprop);
    static BOOL GetAzObjRecurse(HHashObject *obj, int &azprop);
    static int GetAzProp(HHashObject *obj);
//    BOOL GetModels();
    void DeleteKeys() const;
//    void SetZeroFrame();
    void SaveEmbed() const;
    void LoadEmbed() const;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMidicontrolApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMidicontrolApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MIDICONTROL_H__6A1DE8E0_A071_444C_ADA4_9A2561A5B457__INCLUDED_)
