// ==========================================================================
// CNewLabelTester.h
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 20/07/2000
// Last modification : 20/07/2000
// ==========================================================================

#if !defined(AFX_CNEWLABELTESTER_H__50B04096_5E0B_11D4_BC43_0050BAA38233__INCLUDED_)
#define AFX_CNEWLABELTESTER_H__50B04096_5E0B_11D4_BC43_0050BAA38233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ==========================================================================
// Les Includes
// ==========================================================================

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterApp:

class CCNewLabelTesterApp : public CWinApp
 {
  public :
           CCNewLabelTesterApp();

  public :
	//{{AFX_VIRTUAL(CCNewLabelTesterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCNewLabelTesterApp)
	//}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
 };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNEWLABELTESTER_H__50B04096_5E0B_11D4_BC43_0050BAA38233__INCLUDED_)
