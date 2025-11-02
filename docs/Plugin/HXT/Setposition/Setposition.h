// Setposition.h : Haupt-Header-Datei für die DLL SETPOSITION
//

#if !defined(AFX_SETPOSITION_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
#define AFX_SETPOSITION_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "F_Protos.h"
#include "HashFile.h"
#include "Vector.h"
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
// CSetpositionApp
// Siehe Setposition.cpp für die Implementierung dieser Klasse
//

class HModelCache;
class HGroupCP;
class HGroup;

class PParameters {
public:
    // Translate
    BOOL translate{};
    Vector translate_bone;
    // Rotate
    BOOL rotate{};
    RotateEuler rotate_bone;
    // modus
    // absolut false
    // relative true
    BOOL modus{};
    // Axis cp
    BOOL m_x{}, m_y{}, m_z{};
    // CP Modus
    BOOL cp_group{};
    // CP Group mirror
    BOOL mirror_x{}, mirror_y{}, mirror_z{};
};

class CSetpositionApp final : public CPluginApp {
public:
    PParameters m_parameters;

    CSetpositionApp();
    ~CSetpositionApp() override;
    BOOL OnSetGroup(HModelCache *hmc, HGroup *gh);
    BOOL SetPosition(HModelCache *hmc, HGroup *gh) const;
    BOOL OnSetBone(HModelCache *hmc, HBone *hb);
    BOOL SetBone(HModelCache *hmc, HBone *hb);

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CSetpositionApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CSetpositionApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_SETPOSITION_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
