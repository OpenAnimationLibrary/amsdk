// BulletBatch.h : Haupt-Header-Datei für die DLL BulletBatch
//

#if !defined(AFX_BulletBatch_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
#define AFX_BulletBatch_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "Matrix34.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HAction;

/////////////////////////////////////////////////////////////////////////////
// CBulletBatchApp
// Siehe BulletBatch.cpp für die Implementierung dieser Klasse
//

class CBulletBatchApp final : public CPluginApp {
public:
    CBulletBatchApp() noexcept = default;
    ~CBulletBatchApp() override = default;
    static BOOL OnChor(HChor *hchor);

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CBulletBatchApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CBulletBatchApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BulletBatch_H__69C0C710_7C9B_405B_B28B_DA88803D6655__INCLUDED_)
