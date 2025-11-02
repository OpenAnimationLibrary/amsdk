// passes.h : Haupt-Header-Datei für die DLL passes
//

#if !defined(AFX_passes_H__90CDD89E_3FDD_4BD6_A467_0CD4A9209D6E__INCLUDED_)
#define AFX_passes_H__90CDD89E_3FDD_4BD6_A467_0CD4A9209D6E__INCLUDED_

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
#include "SDK/HLight.h"
#include "SDK/HDecal.h"
#include "SDK/HMaterial.h"
#include "structuren.h"

/////////////////////////////////////////////////////////////////////////////
// CPassesApp
// Siehe passes.cpp für die Implementierung dieser Klasse
//
//#define QUAD(A)        ((A) * (A))
//#define S_PI           3.1415926535898
//#define SD_PI          (2*3.1415926535898)
//static double fround(const double n, const int d) {
//    return hash_math::floor(n * hash_math::pow(10., d) + .5) / hash_math::pow(10., d);
//}
//#define fround(A, B) floor((A) * pow(10., B) + .5) / pow(10., B)

class HCP;
class HModel;
class HModelCache;
class HGroup;
class HGroupCP;
class HProgressBar;
class HCamera;
class HLight;
class HMaterial;
class HDecal;

class CPassesApp final : public CPluginApp
{
public:
    CPassesApp();
    ~CPassesApp() override;
    BOOL OnChor(HChor *htreeobject);
    BOOL ReadChor(HChor *hchor) const;
    static void ChangeChorName(HChor *hchor, const String &newname);

    PARAMETER *para{};

    static BOOL DiffuseShadingPass(HChor *hchor);
    static BOOL SpecularityPass(HChor *hchor);
    static BOOL ShadowPass(HChor *hchor);
    static BOOL DofPass(HChor *hchor);
    BOOL RecurseMaterial_add(HHashObject *hobj, HHashObject *hobj1, int j, int &i) const;
    BOOL RecurseMaterial_add_group(HHashObject *hobj, HHashObject *hobj1, int j, int i, int &k) const;
    void Usershading(HChor *hchor) const;
    void FreeStruct() const;

    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CPassesApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CPassesApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_passes_H__90CDD89E_3FDD_4BD6_A467_0CD4A9209D6E__INCLUDED_)
