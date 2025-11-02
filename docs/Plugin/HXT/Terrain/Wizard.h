// KB  3/8/00  \Ken85\Plugin\Wizards\Grid\Wizard.h
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#ifndef __WIZARD_H
#define __WIZARD_H
#include "SDK/HModel.h"
#include "resource.h"		// main symbols
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/Misc.h"

class WizardParameters {
public:
    float m_width, m_height, m_stepwidth, m_stepheight;
    float m_turbmagnitude, m_turbscale;

    enum { XY, XZ, YZ };

    int m_orientation;
    BOOL m_flatedges;
};

#include "WizardDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CWizardApp
// See Wizard.cpp for the implementation of this class
//
class ModelCacheHandle;
class GroupCPHandle;
class CWizardDialog;

class CWizardApp final : public CPluginApp {
public:
    CWizardApp();
    ~CWizardApp() override;
    WizardParameters m_parameters{};
    BOOL makegroup{};

    BOOL OnGridWizard(HModelCache *hmc);
    BOOL NewShape(HModelCache *hmc, const CWizardDialog *dlg);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWizardApp)
    //}}AFX_VIRTUAL
    BOOL InitInstance() override;
    int ExitInstance() override;

    //{{AFX_MSG(CWizardApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif //__WIZARD_H
