// TestPlugin.h : Haupt-Header-Datei für die DLL TestPlugin
//

#if !defined(AFX_TestPlugin_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
#define AFX_TestPlugin_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_

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
#include "SDK/HRelatio.h"

/////////////////////////////////////////////////////////////////////////////
// CTestPluginApp
// Siehe TestPlugin.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;

struct PARAMETER
{
   float splinelength;
   float neededdistance;
   float zvalue;
   int   iteration;
   int   zcount;
   int   direction;
   int   cpcount;
   BOOL  extrude;
};


class CTestPluginApp : public CPluginApp
{
public:
	CTestPluginApp();
	virtual ~CTestPluginApp();

	BOOL OnCP(HCP *cp);
    BOOL OnChor(HChor *chor);
    BOOL OnActionCache(HActionCache *acc);
    BOOL OnAction(HAction *ac);

   BOOL OnGroup(HGroup *hg);
	BOOL OnGroup2(HGroup *hg);

  BOOL OnModel(HModelCache *hc);

  BOOL OnExportActionCache(HActionCache *ha);
// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTestPluginApp)
       virtual BOOL InitInstance();
       virtual int  ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTestPluginApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_TestPlugin_H__9D9587F4_F233_4DFC_AEF6_BCE153F57626__INCLUDED_)
