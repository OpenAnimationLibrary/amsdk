// ==========================================================================
// CNewLabelTesterDlg.h
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 20/07/2000
// Last modification : 20/07/2000
// ==========================================================================

#if !defined(AFX_CNEWLABELTESTERDLG_H__50B04098_5E0B_11D4_BC43_0050BAA38233__INCLUDED_)
#define AFX_CNEWLABELTESTERDLG_H__50B04098_5E0B_11D4_BC43_0050BAA38233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ==========================================================================
// Les Includes
// ==========================================================================

#include "NewLabel.h"

#include "Codeguru Files\ColourPicker.h"
#include "Codeguru Files\MultiSlider.h"
#include "MMA Files\ComboBoxFont.h"

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterDlg dialog

class CCNewLabelTesterDlg : public CDialog
 {
  protected :
              HICON         m_hIcon;
              CMultiSlider  m_MSL_Horz;
              CMultiSlider  m_MSL_Vert;

  public :
           CCNewLabelTesterDlg(CWnd *pParent = NULL);

  public :
	//{{AFX_DATA(CCNewLabelTesterDlg)
	enum { IDD = IDD_CNEWLABELTESTER_DIALOG };
	CComboBox	m_CB_VertAlign;
	CComboBox	m_CB_HorzAlign;
	CColourPicker	m_PB_HighLightColor;
	CComboBoxFont	m_CB_Font;
	CColourPicker	m_PB_BkgndColor;
	CColourPicker	m_PB_TextBkColor;
	CColourPicker	m_PB_TextColor;
	CNewLabel	m_NL_TestZone;
	//}}AFX_DATA

  protected :
	//{{AFX_VIRTUAL(CCNewLabelTesterDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCNewLabelTesterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCB_TextColor();
	afx_msg void OnCB_TextBkColor();
	afx_msg void OnCB_BkgndColor();
	afx_msg void OnCB_SetFontBold();
	afx_msg void OnCB_SetFontItalic();
	afx_msg void OnCB_SetFontUnderline();
	afx_msg void OnPB_SetFontSize();
	afx_msg void OnSelchange_Font();
	afx_msg void OnCB_SetBorder();
	afx_msg void OnCB_SetSunken();
	afx_msg void OnCB_SetLink();
	afx_msg void OnCB_UseHighlighting();
	afx_msg void OnCB_UseBevelLine();
	afx_msg void OnSelchange_Horzalign();
	afx_msg void OnSelchange_Vertalign();
	afx_msg void OnCB_SetVerticalText();
	afx_msg void OnChange_Text();
	afx_msg void OnCB_TextFlash();
	afx_msg void OnCB_BkFlash();
	afx_msg void OnRB_Rotation0();
	afx_msg void OnRB_Rotation90();
	afx_msg void OnRB_Rotation180();
	afx_msg void OnRB_Rotation270();
	afx_msg void OnCB_UseToolTip();
	afx_msg void OnCB_UseHighLightingOnlyWithTooltip();
	afx_msg void OnCB_UseLeftButton();
	afx_msg void OnCB_UseTooltipOnMouseClick();
	afx_msg void OnCB_Disable();
	afx_msg void OnCB_UseBackImage();
	afx_msg void OnCB_LowerCase();
	afx_msg void OnCB_UpperCase();
	afx_msg void OnCB_StretchBitmap();
	//}}AFX_MSG
  afx_msg LONG OnSelEndOK(UINT, LONG);
  
  DECLARE_MESSAGE_MAP()
 };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNEWLABELTESTERDLG_H__50B04098_5E0B_11D4_BC43_0050BAA38233__INCLUDED_)
