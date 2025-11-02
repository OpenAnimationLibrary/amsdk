// Correct_Normals.h : Haupt-Header-Datei für die DLL Correct_Normals
//

#if !defined(AFX_Correct_Normals_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
#define AFX_Correct_Normals_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_

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
#include "EPatch.h"

/////////////////////////////////////////////////////////////////////////////
// CCorrect_NormalsApp
// Siehe Correct_Normals.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HModelCache;
class HGroupCP;
class HGroup;
class HChor;

class CCorrect_NormalsApp final : public CPluginApp {
public:
    CCorrect_NormalsApp();
    ~CCorrect_NormalsApp() override;
    static BOOL ReverseNormals(HModelCache *hmc);
    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CCorrect_NormalsApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CCorrect_NormalsApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Correct_Normals_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
