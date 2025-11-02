// Align.h : Haupt-Header-Datei für die DLL Align
//

#if !defined(AFX_Align_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
#define AFX_Align_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_

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

/////////////////////////////////////////////////////////////////////////////
// CAlignApp
// Siehe Align.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HPropertyInfo;
class HChor;

//class HBone;

struct ALIGN_BBOX {
    Vector min;
    Vector max;
};

struct ALIGN_POINT {
    Vector pos;
    Vector hitp;
    Vector neededmove;
    Quaternion quat;
    BOOL isintersect{};
};

class CAlignApp final : public CPluginApp {
public:
    CAlignApp() noexcept = default;
    ~CAlignApp() override = default;
    CAlignApp(const CAlignApp &) = delete;
    CAlignApp &operator=(const CAlignApp &) = delete;
    CAlignApp(CAlignApp &&) = delete;
    CAlignApp &operator=(CAlignApp &&) = delete;

    static BOOL OnModel(HModel *hm);
    /*
        BOOL TestModel(HModel *hm);
        BOOL TestModel1(HModel *hm);
        BOOL TestModel2(HModelCache *hm);
        BOOL TestModelCache(HModelCache *hm);
        BOOL TestBone(HBone *hb);
        void ComputeBones(HModelCache *hmc);
        */
    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CAlignApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CAlignApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_Align_H__822E1E97_69E8_4F0A_9B08_F041BC35ED14__INCLUDED_)
