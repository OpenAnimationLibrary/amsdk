// KB  1/20/05  \Plugin\HXT\Duplicator\Hxt.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef __HXT_H
#define __HXT_H

#include "resource.h"		// main symbols
#include "Matrix34.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"

class HModelCache;
/*
class DupParameters
{
public:
	HModelCache      *m_hmc;
	Vector            m_translate;
	RotateEuler       m_sweeprotate;
	RotateEuler       m_tumblerotate;
	float             m_offsetdisttocenter;
	Vector            m_tumblepivotoffset;
	Vector            m_tumblescale;
	float             m_stopatdist;
	int               m_repeat;
	BOOL              m_isextrude;
};
*/
/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See Hxt.cpp for the implementation of this class
//
class HGroupCP;
class HGroup;
class HModelCache;
class HActionCache;

class CHxtApp final : public CPluginApp {
public:
    //   DupParameters  m_parameters;

    CHxtApp();

    BOOL OnTreeeZ(HModelCache *hmc, HActionCache *hac) const;
    static BOOL TreeeZ(HModelCache *hmc, HActionCache *hac);

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
