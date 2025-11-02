// DeleteKeys.h : Haupt-Header-Datei für die DLL DeleteKeys
//

#if !defined(AFX_DeleteKeys_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
#define AFX_DeleteKeys_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_

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

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

/////////////////////////////////////////////////////////////////////////////
// CDeleteKeysApp
// Siehe DeleteKeys.cpp für die Implementierung dieser Klasse
//

class CDeleteKeysApp final : public CPluginApp {
public:
    CDeleteKeysApp();
    ~CDeleteKeysApp() override;
    static BOOL OnChor(HChor *hchor);

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CDeleteKeysApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CDeleteKeysApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DeleteKeys_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
