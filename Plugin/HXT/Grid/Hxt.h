// KB  11/1/01  \Ken90\Plugin\HXT\Grid\Hxt.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#ifndef __HXT_H
#define __HXT_H

#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/Misc.h"
#include "resource.h"		// main symbols

class GridParameters {
public:
    float m_width, m_height, m_stepwidth, m_stepheight;

    enum { XZ=0, XY, YZ };

    int m_orientation;
    float m_turbmagnitude, m_turbscale;
};

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See Hxt.cpp for the implementation of this class
//
class HModelCache;
class HGroupCP;

class CHxtApp final : public CPluginApp {
public:
    GridParameters m_parameters{};
    BOOL makegroup{FALSE};

    CHxtApp();
    ~CHxtApp() override;

    BOOL OnGridWizard(HModelCache *hmc);
    BOOL NewShape(HModelCache *mch);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
    //}}AFX_VIRTUAL
    BOOL InitInstance() override;
    int ExitInstance() override;

    //{{AFX_MSG(CHxtApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif //__HXT_H
