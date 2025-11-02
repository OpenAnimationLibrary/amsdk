// KB  6/4/01  \Ken90\Plugin\HXT\Duplicator\Hxt.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#ifndef __HXT_H
#define __HXT_H
#include "SDK/Misc.h"

#include "resource.h"		// main symbols
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HDecal.h"

#include <vector>

#include "StrClass.h"

class HModelCache;

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See Hxt.cpp for the implementation of this class
//
class HGroupCP;
class HGroup;

class CHxtApp final : public CPluginApp {
public:
    CHxtApp();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
    //}}AFX_VIRTUAL
    BOOL InitInstance() override;
    BOOL ExitInstance() override;

    //{{AFX_MSG(CHxtApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()

public:
    BOOL OnInstallRig(HTreeObject *htreeobject);
    bool Evaluate(HTreeObject *htreeobject);
    int EvaluateBoneChildren(HTreeObject *htreeobject) const;

public:
    HBoneCacheContainer *m_bonesfolder{};
};

/////////////////////////////////////////////////////////////////////////////
#endif //__HXT_H
