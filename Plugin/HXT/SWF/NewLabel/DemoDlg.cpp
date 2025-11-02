// ==========================================================================
// DemoDlg.cpp
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 28/07/2000
// Last modification : 28/07/2000
// ==========================================================================

// ==========================================================================
// Les Includes
// ==========================================================================

#include "stdafx.h"
#include "cnewlabeltester.h"
#include "DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd *pParent) : CDialog(CDemoDlg::IDD, pParent)
 {
	//{{AFX_DATA_INIT(CDemoDlg)
	//}}AFX_DATA_INIT
 }

// --------------------------------------------------------------------------

void CDemoDlg::DoDataExchange(CDataExchange *pDX)
 {
  CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDST_TRANSPARENT, m_NL_Transparent);
	DDX_Control(pDX, IDST_BITMAPWITHTEXT, m_NL_BitmapWithText);
	DDX_Control(pDX, IDST_BITMAPWITHOUTTEXT, m_NL_BitmapWithoutText);
	DDX_Control(pDX, IDST_VERTICALTEXT, m_NL_VerticalText);
	DDX_Control(pDX, IDST_ANGLE0, m_NL_Angle0);
	DDX_Control(pDX, IDST_BEVELTEXTVCENTER, m_NL_BevelTextVCenter);
	DDX_Control(pDX, IDST_BEVELTEXTBOTTOM, m_NL_BevelTextBottom);
	DDX_Control(pDX, IDST_BEVELTEXTTOP, m_NL_BevelTextTop);
	DDX_Control(pDX, IDST_BEVELTEXTRIGHT, m_NL_bevelTextRight);
	DDX_Control(pDX, IDST_BEVELTEXTLEFT, m_NL_bevelTextLeft);
	DDX_Control(pDX, IDST_BEVELTEXTCENTER, m_NL_bevelTextCenter);
	DDX_Control(pDX, IDST_TEXTWITHTOOLTIP3, m_NL_TextWithToolTip3);
	DDX_Control(pDX, IDST_TEXTWITHTOOLTIP2, m_NL_TextWithToolTip2);
	DDX_Control(pDX, IDST_TEXTWITHTOOLTIP1, m_NL_TextWithToolTip1);
	DDX_Control(pDX, IDST_HIGHLIGHTINGTEXT, m_NL_HighLightingText);
	DDX_Control(pDX, IDST_LINKTEXT, m_NL_LinkText);
	DDX_Control(pDX, IDST_DISABLEDTEXT, m_NL_DisabledText);
	DDX_Control(pDX, IDST_FLASHBACK, m_NL_FlashBack);
	DDX_Control(pDX, IDST_FLASHTEXT, m_NL_FlashingText);
	DDX_Control(pDX, IDST_MULTILINETEXT, m_NL_MultiLineText);
	DDX_Control(pDX, IDST_FONTTEXT, m_NL_FontText);
	DDX_Control(pDX, IDST_ANGLE180, m_NL_Angle180);
	DDX_Control(pDX, IDST_ANGLE270, m_NL_Angle270);
	DDX_Control(pDX, IDST_ANGLE90, m_NL_Angle90);
	DDX_Control(pDX, IDST_BACKTEXTCOLOR, m_NL_BackTextColor);
	DDX_Control(pDX, IDST_BACKGNDCOLOR, m_NL_BackgndColor);
	DDX_Control(pDX, IDST_TEXTCOLOR, m_NL_TextColor);
	//}}AFX_DATA_MAP
 }

// --------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::DestroyWindow() 
 {
	
  return CDialog::DestroyWindow();
 }

// --------------------------------------------------------------------------

BOOL CDemoDlg::OnInitDialog() 
 {
  CDialog::OnInitDialog();

  m_NL_TextColor.SetTextColor(RGB(255,0,0));

  m_NL_BackgndColor.SetBkColor(RGB(255,255,0));

  m_NL_BackTextColor.SetTextBackColor(RGB(0,255,0));
  m_NL_BackTextColor.SetBkColor(RGB(255,255,0));

  m_NL_Angle0.SetAngle(0);

  m_NL_Angle90.SetAngle(90);
	
  m_NL_Angle180.SetAngle(180);

  m_NL_Angle270.SetAngle(270);

  m_NL_FontText.SetText("Font Text\n+Border");
  m_NL_FontText.SetFontBold(TRUE);
  m_NL_FontText.SetFontName("Times New Roman");
  m_NL_FontText.SetFontSize(20);
  m_NL_FontText.SetBorder(TRUE);

  m_NL_MultiLineText.SetText("Multi Line Text\nRight Aligned\nBottom Aligned\nSunken effect");
  m_NL_MultiLineText.SetAlignment(CNewLabel::HORZ_RIGHT | CNewLabel::VERT_BOTTOM);
  m_NL_MultiLineText.SetSunken(TRUE);

  m_NL_FlashingText.FlashText(TRUE);

  m_NL_FlashBack.FlashBackground(TRUE, 600);

  m_NL_DisabledText.SetDisabled(TRUE);

  m_NL_LinkText.SetLink(TRUE);
  m_NL_LinkText.SetLinkCursor(IDC_HAND);
  m_NL_LinkText.SetTextColor(RGB(0,0,255));

  m_NL_HighLightingText.UseHighLighting(TRUE);
  m_NL_HighLightingText.SetHighLightColor(RGB(255,0,255));

  m_NL_TextWithToolTip1.UseToolTip(TRUE);
  m_NL_TextWithToolTip1.SetToolTipText("Tooltip text over control");
  m_NL_TextWithToolTip1.ShowToolTipOnlyOnMouseClick(FALSE);

  m_NL_TextWithToolTip2.UseToolTip(TRUE);
  m_NL_TextWithToolTip2.SetToolTipText("Tooltip text under control + highlighting");
  m_NL_TextWithToolTip2.SetToolTipPosition(1);
  m_NL_TextWithToolTip2.UseHighLighting(TRUE);
  m_NL_TextWithToolTip2.SetHighLightColor(RGB(255,0,255));

  m_NL_TextWithToolTip3.UseToolTip(TRUE);
  m_NL_TextWithToolTip3.SetToolTipText("Tooltip text above control + highlighting");
  m_NL_TextWithToolTip3.SetToolTipPosition(2);
  m_NL_TextWithToolTip3.UseLeftMouseButtonForToolTip(FALSE);
  m_NL_TextWithToolTip3.UseHighLighting(TRUE);
  m_NL_TextWithToolTip3.SetHighLightColor(RGB(255,0,255));

  m_NL_bevelTextRight.UseBevelLine(TRUE);

  m_NL_bevelTextCenter.UseBevelLine(TRUE);

  m_NL_bevelTextLeft.UseBevelLine(TRUE);

  m_NL_BevelTextTop.UseBevelLine(TRUE);
  m_NL_BevelTextTop.SetAngle(90);

  m_NL_BevelTextVCenter.UseBevelLine(TRUE);
  m_NL_BevelTextVCenter.SetAngle(90);

  m_NL_BevelTextBottom.UseBevelLine(TRUE);
  m_NL_BevelTextBottom.SetAngle(90);
  m_NL_BevelTextBottom.SetAlignment(CNewLabel::HORZ_LEFT | CNewLabel::VERT_BOTTOM);

  m_NL_VerticalText.SetVerticalText(TRUE);
  m_NL_VerticalText.SetUpperCase(TRUE);

  m_NL_BitmapWithoutText.SetBackImage(IDB_MIKE);
  m_NL_BitmapWithoutText.StretchBitmap(TRUE);

  m_NL_BitmapWithText.SetBackImage(IDB_MIKE);
  m_NL_BitmapWithText.SetTextColor(RGB(255,255,0));
  m_NL_BitmapWithText.SetAlignment(CNewLabel::HORZ_CENTER | CNewLabel::VERT_BOTTOM);
  m_NL_BitmapWithText.StretchBitmap(TRUE);

  m_NL_Transparent.SetTextColor(RGB(0,0,255));
  m_NL_Transparent.SetBkColor(RGB(255,255,0));

  return TRUE;
 }

// --------------------------------------------------------------------------
