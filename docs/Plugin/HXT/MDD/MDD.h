// MDD.h : Haupt-Header-Datei für die DLL MDD
//

#if !defined(AFX_MDD_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
#define AFX_MDD_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_

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
#include "Files.h"
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

/////////////////////////////////////////////////////////////////////////////
// CMDDApp
// Siehe MDD.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HPropertyInfo;

struct W_PARA {
    String filename;
    float tolerance{};
    float scale{};
    float fps{};
    Time start;
    Time end;
    BOOL startatcurrenttime{};
    int subtype{};
};

struct W_CPPOS {
    BOOL inuse{};
    HCP *cp{};
    HCPInstance *cpinstance{};
    Vector position;
};

class CMDDApp final : public CPluginApp {
public:
    CMDDApp();
    ~CMDDApp() override;

    BOOL CPIsAddedToArray(const HCP *cp);
    int FindMatchingCP(Vector pos);

    BOOL OnImport(HModel *hm);
    BOOL OnExport(HModel *hm) const;

    BOOL OnExportModel(HModel *hm);
    BOOL OnImportModel(HModel *hm);
    void LoadSettings() const;
    void SaveSettings() const;

    //	BOOL OnExportASCII(HModel *hm);
    //	BOOL Test();

    W_PARA *parameter{};
    CArray<W_CPPOS, W_CPPOS &> allcps;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMDDApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMDDApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MDD_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
