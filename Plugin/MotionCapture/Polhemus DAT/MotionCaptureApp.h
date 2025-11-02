// Dan  3/1/01  \Dan90\Plugin\MotionCapture\Polhemus DAT\MotionCaptureApp.h
//

#pragma once
#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/Misc.h"
#include "SDK/HPropert.h"

/////////////////////////////////////////////////////////////////////////////
// CMCApp
// See MC.cpp for the implementation of this class
//

class CMCApp final : public CPluginApp {
public:
    enum FACTORTYPE { CENTIMETERS=0, INCHES };

    //HBoolPropertyInfo *m_isbinaryinfo;
    HTypePropertyInfo *m_scalefactortypeinfo;
    HFilenamePropertyInfo *m_filenameinfo;
    TypeInfoArray m_typeinfoarray;

    CMCApp();

    BOOL InitInstance() override;
    int ExitInstance() override;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMCApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMCApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
