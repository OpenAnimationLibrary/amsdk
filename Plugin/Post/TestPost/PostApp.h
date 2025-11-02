// NAP  3/3/2003  \Noel105\Plugin\Post\Add\PostApp.h
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#ifndef __HPROPERT_H
#include "SDK/HPropert.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostApp
// See Post.cpp for the implementation of this class
//


//enum {STYLE_BW, STYLE_COBALT, STYLE_SEPIA, STYLE_XRAY, STYLE_CUSTOM, NUM_STYLES};

class CPostApp : public CWinApp
{
public:
   HPercentPropertyInfo     *m_percentinfo1;
   HPercentPropertyInfo     *m_percentinfo2;
   HPercentPropertyInfo     *m_percentinfo3;

	CPostApp();
   virtual BOOL              InitInstance();
   virtual int               ExitInstance();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPostApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CPostApp &GetApp();

/////////////////////////////////////////////////////////////////////////////
