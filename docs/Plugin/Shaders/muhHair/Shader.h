// 
//

#pragma once
#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/HPropert.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CShaderApp
// See Shader.cpp for the implementation of this class
//
class CShaderApp final : public CPluginApp {
public:
    CShaderApp();

    HPercentPropertyInfo *m_primWidthInfo, *m_scndryWidthInfo, *m_transWidthInfo;
    HPercentPropertyInfo *m_primDevInfo, *m_scndryDevInfo, *m_transDevInfo;
    HPercentPropertyInfo *m_primStrengthInfo, *m_scndryStrengthInfo, *m_transStrengthInfo;
    HPercentPropertyInfo *m_fresInfo;
    HPercentPropertyInfo *m_directionAttenInfo;
    HPercentPropertyInfo *m_specBlendInfo;
    HFloatPropertyInfo *m_iorInfo;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CShaderApp)
    //}}AFX_VIRTUAL
    BOOL InitInstance() override;
    int ExitInstance() override;

    //{{AFX_MSG(CShaderApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
