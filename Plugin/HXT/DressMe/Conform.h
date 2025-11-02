// Conform.h : main header file for the Conform DLL
//

#if !defined(AFX_CONFORM_H__055AB096_2E99_4D12_A1F7_3909F374F397__INCLUDED_)
#define AFX_CONFORM_H__055AB096_2E99_4D12_A1F7_3909F374F397__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// AM SDK Includes
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/HChor.h"
#include "SDK/HConstra.h"
#include "SDK/HRelatio.h"
#include "SDK/HProject.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CConformApp
// See Conform.cpp for the implementation of this class
//

// AM SDK Classes
class HModelCache;
class HGroupCP;

class CConformApp final : public CPluginApp {
public:
    CConformApp();
    ~CConformApp() override;
    BOOL OnConformPlugin(HModel *hm); // AM SDK

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConformApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CConformApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG

public:
    HChor *m_Chor{};
    [[nodiscard]] BOOL DoConform() const;
    [[nodiscard]] BOOL DoConformRelationship() const;
    HModel *m_ModelBody{};
    HModel *m_ModelClothing{};
    HChorAction *m_ChorAction{};

    BOOL InitInstance() override;
    int ExitInstance() override; // AM SDK

DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFORM_H__3A6EE968_7482_4FD4_A969_7E44093A154C__INCLUDED_)
