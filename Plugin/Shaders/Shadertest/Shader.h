// RC  2/11/2002  \Randy90\Plugin\Shaders\Gradient\Shader.h
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef __SHADER_H
#define __SHADER_H

#include "resource.h"		// main symbols

#ifndef __HPROPERT_H
#include "SDK/HPropert.h"
#endif

#ifndef __HMODEL_H
#include "SDK/HModel.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CShaderApp
// See Shader.cpp for the implementation of this class
//
class CShaderApp : public CWinApp
{
public:
	HFloatPropertyInfo	  *m_RayDistanceInfo;
	HIntPropertyInfo	  *m_SamplesInfo;
	CShaderApp();
	virtual ~CShaderApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShaderApp)
	//}}AFX_VIRTUAL
	virtual BOOL InitInstance();
   virtual int  ExitInstance();

	//{{AFX_MSG(CShaderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CShaderApp &GetApp();


/////////////////////////////////////////////////////////////////////////////
#endif __SHADER_H