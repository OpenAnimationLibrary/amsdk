// MaPD.h : Haupt-Header-Datei für die DLL MaPD
//

#if !defined(AFX_MaPD_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
#define AFX_MaPD_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "F_Protos.h"
#include "HashFile.h"
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
#include "ArrayEx.h"

/////////////////////////////////////////////////////////////////////////////
// CMaPDApp
// Siehe MaPD.cpp für die Implementierung dieser Klasse
//

class HModelCache;
class HGroupCP;
class HGroup;

struct MyStampData {
    HPatch *hp{};
    Vector uvs[15];
};

struct MyStamp {
    HDecalStamp *hds{};
    CArrayEx<MyStampData, MyStampData> stampdata;
};

struct MyDecal {
    HDecal *hd{};
    bool isdeletet{};
    CArrayEx<MyStamp, MyStamp> stamp;
};

class CMaPDApp final : public CPluginApp {
public:

    CMaPDApp();
    ~CMaPDApp() override;
    BOOL OnModel(HModelCache *hmc);
    static BOOL GetDecalList(HModelCache *hmc, CArrayEx<MyDecal, MyDecal> &decallist);
    static bool IsMatchDecal(const MyDecal &org, const MyDecal &check);
    static void CopyDecalData(const MyDecal &org, MyDecal tocopy);
#ifdef _DEBUG
    FileStream fs;
#endif

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMaPDApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMaPDApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MaPD_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
