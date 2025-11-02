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

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See Hxt.cpp for the implementation of this class
//
class HModelCache;
class HGroupCP;

class CHxtApp final : public CPluginApp {
public:
    CHxtApp();
    ~CHxtApp() override;

    enum EMETHOD {
        COUNT,
        DISTANCE,
        EVERYCP
    };

    enum ETYPE {
        COPY,
        EXTRUDE
    };

    static BOOL OnExtruderWizard(HModelCache *hmc, HGroup *hg);

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
