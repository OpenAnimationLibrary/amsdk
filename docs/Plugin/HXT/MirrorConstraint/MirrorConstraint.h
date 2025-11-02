// MirrorConstraint.h : Haupt-Header-Datei für die DLL MirrorConstraint
//

// ReSharper disable CppUnusedIncludeDirective
#if !defined(AFX_MirrorConstraint_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
#define AFX_MirrorConstraint_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "Matrix34.h"
#include "HashFile.h"
#include "F_Protos.h"
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
#include "ArrayEx.h"

/////////////////////////////////////////////////////////////////////////////
// CMirrorConstraintApp
// Siehe MirrorConstraint.cpp für die Implementierung dieser Klasse
//

class HModelCache;

struct MC_PARAMETER {
    String search;
    String replace;
    HModelCache *hmc{};
    CArray<HPropertyShortcut *, HPropertyShortcut *> poses;
};

class CMirrorConstraintApp final : public CPluginApp {
public:
    MC_PARAMETER *para{};

    CMirrorConstraintApp() = default;
    ~CMirrorConstraintApp() override = default;

    CMirrorConstraintApp(const CMirrorConstraintApp &) = delete;
    CMirrorConstraintApp &operator=(const CMirrorConstraintApp &) = delete;
    CMirrorConstraintApp(CMirrorConstraintApp &&) = delete;
    CMirrorConstraintApp &operator=(CMirrorConstraintApp &&) = delete;

    BOOL OnModel(HModelCache *hmc);
    BOOL OnAction(HActionCache *hac);

    BOOL Work();
    BOOL WorkAction(HActionCache *hac);
    BOOL HandleSpecial(HPropertyDriver *src, HPropertyDriver *dst);
    void CopyPropertyDrivers(HHashObject *srcparent, HHashObject *dstparent);
    void DuplicateConstraint(HTreeObject *hto, HAnimObjectShortcut *haos);
    BOOL GetBranch(HHashObject *hho);
    void GetSettings() const;
    void SaveSettings() const;

#ifdef _DEBUG
    FileStream fsd;
#endif
    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMirrorConstraintApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMirrorConstraintApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MirrorConstraint_H__D1DEA169_AFE3_4713_BC10_B9769465C5B6__INCLUDED_)
