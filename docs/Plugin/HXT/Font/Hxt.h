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

class FontParameters {
public:
    enum { SUB_NONE, SUB_ALL, SUB_AUTO } SubdivKind;

    CString m_buildtext;
    CString m_facename;
    CString m_style;
    CString m_aifile;	// if aifile is non-empty, use it rather than font stuff
    CString m_aifolder;
    BOOL m_fronts;
    BOOL m_sides;
    BOOL m_backs;
    BOOL m_bevfronts;
    BOOL m_bevbacks;
    BOOL m_bevsides;
    BOOL m_bevround;
    BOOL m_bevinward;
    int m_subdivkind;
    float m_bevamt;
    float m_depth;
    [[nodiscard]] int FaceWeight() const;
    [[nodiscard]] int IsItalicFace() const;
    BOOL m_isfont; //selection what to do via m_aifile fails, if first a aifile is importet  
};

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See Hxt.cpp for the implementation of this class
//
class HModelCache;
class HGroupCP;

class CHxtApp final : public CPluginApp {
public:
    CHxtApp();
    FontParameters m_parameters;
    BOOL makegroup;

    BOOL OnFontWizard(HModelCache *hmc);
    BOOL OnAIWizard(HModelCache *hmc);
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
