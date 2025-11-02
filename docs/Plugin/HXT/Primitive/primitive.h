// primitive.h : Haupt-Header-Datei für die DLL PRIMITIVE
//

#if !defined(AFX_PRIMITIVE_H__CE792E14_2C0F_446C_A9EB_C287F55B6D3B__INCLUDED_)
#define AFX_PRIMITIVE_H__CE792E14_2C0F_446C_A9EB_C287F55B6D3B__INCLUDED_

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
#include "Quaterni.h"
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

#define S_PI (3.1415926535898*2)

struct PParameters {
    float m_radius1, m_radius2, m_hoehe, m_breite, m_tiefe, m_magnitude, m_magnitude2;
    int m_segment1, m_segment2, m_segment3, m_turn, m_type, m_subdiv;
    BOOL m_richtung, m_typcp, m_autobone;
    HINSTANCE hinstance;
};

/////////////////////////////////////////////////////////////////////////////
// CPrimitiveApp
// Siehe primitive.cpp für die Implementierung dieser Klasse
//

class HModelCache;
class HGroupCP;
class HProgressBar;

class CPrimitiveApp final : public CPluginApp
{
public:
    PParameters m_parameters{};
    HProgressBar *m_hprogressbar{};

    CPrimitiveApp();
    ~CPrimitiveApp() override;
    BOOL OnPrimitiveWizard(HModelCache *hmc);
    BOOL BuildModel(HModelCache *hmc);

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CPrimitiveApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CPrimitiveApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_PRIMITIVE_H__CE792E14_2C0F_446C_A9EB_C287F55B6D3B__INCLUDED_)
