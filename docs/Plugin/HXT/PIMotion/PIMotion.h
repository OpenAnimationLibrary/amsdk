// PIMotion.h : Haupt-Header-Datei für die DLL PIMOTION
//

#if !defined(AFX_PIMOTION_H__2B64BA4A_2520_4302_8061_4ED08D086CB0__INCLUDED_)
#define AFX_PIMOTION_H__2B64BA4A_2520_4302_8061_4ED08D086CB0__INCLUDED_

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

/////////////////////////////////////////////////////////////////////////////
// CPIMotionApp
// Siehe PIMotion.cpp für die Implementierung dieser Klasse
//
class PParameters {
public:
    HChor *hchor{}; //benutzte Chor
    HCamera *hcam{}; // benutzte Kamera
    HObject *htracking{}; // zu trackendes Model;
    HBone *hbone{};
    HGroup *hgroup{};
    String filename;
    float fps{};
    float startframe{};
    float endframe{};
    int height{}; //Bildhoehe
    int width{}; //Bildbreite
    int trackpoint{}; //0 Pivot,1 Center,2 Gruppencenter,3 Bonepivot
};

class CPIMotionApp final : public CPluginApp {
public:
    CPIMotionApp();
    ~CPIMotionApp() override;
    BOOL OnChor(HChor *htreeobject);
    BOOL ChorWorking(HChor *hchor);
    BOOL GetPropRecurseCamera(HProperty *akt_prop);
    void GetPropCamera(HHashObject *obj);

    PParameters *m_para{};

    //for debug
    FileStream fs;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CPIMotionApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CPIMotionApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_PIMOTION_H__2B64BA4A_2520_4302_8061_4ED08D086CB0__INCLUDED_)
