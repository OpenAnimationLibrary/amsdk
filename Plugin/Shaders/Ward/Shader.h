// Yves Poissant  2005/10/18  \Master13.0\Plugin\Shaders\Ward\Shader.h
//

#pragma once
#ifndef __AFXWIN_H__
	#error include 'StdAfx.h' before including this file for PCH
#endif

#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "resource.h"		// main symbols

#define NPRESETS 30

/////////////////////////////////////////////////////////////////////////////
// CShaderApp
// See Shader.cpp for the implementation of this class
//
class CShaderApp final : public CPluginApp {
public:
    TypeInfoArray m_MaterialInfoArray;
    TypeInfoArray m_AlignmentInfoArray;
    HTypePropertyInfo *m_MaterialInfo;
    HPercentPropertyInfo *m_RoughnessXInfo;
    HPercentPropertyInfo *m_RoughnessYInfo;
    HTypePropertyInfo *m_AlignmentInfo;
    HBoolPropertyInfo *m_IsIsotropicInfo;
    HBoolPropertyInfo *m_IsBRDFInfo;
    HPointerPropertyInfo *m_AxisBoneInfo;
    CShaderApp();

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

CShaderApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
