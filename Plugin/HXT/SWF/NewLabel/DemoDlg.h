// ==========================================================================
// DemoDlg.h
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 28/07/2000
// Last modification : 28/07/2000
// ==========================================================================

#if !defined(AFX_DEMODLG_H__EA769802_6449_11D4_BC44_0050BAA38233__INCLUDED_)
#define AFX_DEMODLG_H__EA769802_6449_11D4_BC44_0050BAA38233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ==========================================================================
// Les Includes
// ==========================================================================

#include "NewLabel.h"

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
 {
  public :
           CDemoDlg(CWnd *pParent = NULL);

  public :
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMODLG };
	CNewLabel	m_NL_Transparent;
	CNewLabel	m_NL_BitmapWithText;
	CNewLabel	m_NL_BitmapWithoutText;
	CNewLabel	m_NL_VerticalText;
	CNewLabel	m_NL_Angle0;
	CNewLabel	m_NL_BevelTextVCenter;
	CNewLabel	m_NL_BevelTextBottom;
	CNewLabel	m_NL_BevelTextTop;
	CNewLabel	m_NL_bevelTextRight;
	CNewLabel	m_NL_bevelTextLeft;
	CNewLabel	m_NL_bevelTextCenter;
	CNewLabel	m_NL_TextWithToolTip3;
	CNewLabel	m_NL_TextWithToolTip2;
	CNewLabel	m_NL_TextWithToolTip1;
	CNewLabel	m_NL_HighLightingText;
	CNewLabel	m_NL_LinkText;
	CNewLabel	m_NL_DisabledText;
	CNewLabel	m_NL_FlashBack;
	CNewLabel	m_NL_FlashingText;
	CNewLabel	m_NL_MultiLineText;
	CNewLabel	m_NL_FontText;
	CNewLabel	m_NL_Angle180;
	CNewLabel	m_NL_Angle270;
	CNewLabel	m_NL_Angle90;
	CNewLabel	m_NL_BackTextColor;
	CNewLabel	m_NL_BackgndColor;
	CNewLabel	m_NL_TextColor;
	//}}AFX_DATA

  protected :
	//{{AFX_VIRTUAL(CDemoDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
 };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__EA769802_6449_11D4_BC44_0050BAA38233__INCLUDED_)
