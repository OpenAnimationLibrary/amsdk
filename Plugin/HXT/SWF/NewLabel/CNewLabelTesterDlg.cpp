// ==========================================================================
// CNewLabelTesterDlg.cpp
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 20/07/2000
// Last modification : 20/07/2000
// ==========================================================================

// ==========================================================================
// Les Includes
// ==========================================================================

#include "stdafx.h"
#include "CNewLabelTester.h"
#include "CNewLabelTesterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterDlg dialog

CCNewLabelTesterDlg::CCNewLabelTesterDlg(CWnd *pParent)
 : CDialog(CCNewLabelTesterDlg::IDD, pParent)
 {
	//{{AFX_DATA_INIT(CCNewLabelTesterDlg)
	//}}AFX_DATA_INIT
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::DoDataExchange(CDataExchange* pDX)
 {
  CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCNewLabelTesterDlg)
	DDX_Control(pDX, IDCB_VERTALIGN, m_CB_VertAlign);
	DDX_Control(pDX, IDCB_HORZALIGN, m_CB_HorzAlign);
	DDX_Control(pDX, IDPB_HIGHLIGHTCOLOR, m_PB_HighLightColor);
	DDX_Control(pDX, IDCB_FONT, m_CB_Font);
	DDX_Control(pDX, IDPB_BKGNDCOLOR, m_PB_BkgndColor);
	DDX_Control(pDX, IDPB_TEXTBKCOLOR, m_PB_TextBkColor);
	DDX_Control(pDX, IDPB_TEXTCOLOR, m_PB_TextColor);
	DDX_Control(pDX, IDST_TESTZONE, m_NL_TestZone);
	//}}AFX_DATA_MAP
 }

// --------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CCNewLabelTesterDlg, CDialog)
	//{{AFX_MSG_MAP(CCNewLabelTesterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCB_TEXTCOLOR, OnCB_TextColor)
	ON_BN_CLICKED(IDCB_TEXTBKCOLOR, OnCB_TextBkColor)
	ON_BN_CLICKED(IDCB_BKGNDCOLOR, OnCB_BkgndColor)
	ON_BN_CLICKED(IDCB_SETFONTBOLD, OnCB_SetFontBold)
	ON_BN_CLICKED(IDCB_SETFONTITALIC, OnCB_SetFontItalic)
	ON_BN_CLICKED(IDCB_SETFONTUNDERLINE, OnCB_SetFontUnderline)
	ON_BN_CLICKED(IDPB_SETFONTSIZE, OnPB_SetFontSize)
	ON_CBN_SELCHANGE(IDCB_FONT, OnSelchange_Font)
	ON_BN_CLICKED(IDCB_SETBORDER, OnCB_SetBorder)
	ON_BN_CLICKED(IDCB_SETSUNKEN, OnCB_SetSunken)
	ON_BN_CLICKED(IDCB_SETLINK, OnCB_SetLink)
	ON_BN_CLICKED(IDCB_USEHIGHLIGHTING, OnCB_UseHighlighting)
	ON_BN_CLICKED(IDCB_USEBEVELLINE, OnCB_UseBevelLine)
	ON_CBN_SELCHANGE(IDCB_HORZALIGN, OnSelchange_Horzalign)
	ON_CBN_SELCHANGE(IDCB_VERTALIGN, OnSelchange_Vertalign)
	ON_BN_CLICKED(IDCB_SETVERTICALTEXT, OnCB_SetVerticalText)
	ON_EN_CHANGE(IDED_TEXT, OnChange_Text)
	ON_BN_CLICKED(IDCB_TEXTFLASH, OnCB_TextFlash)
	ON_BN_CLICKED(IDCB_BKFLASH, OnCB_BkFlash)
	ON_BN_CLICKED(IDRB_ROTATION_0, OnRB_Rotation0)
	ON_BN_CLICKED(IDRB_ROTATION_90, OnRB_Rotation90)
	ON_BN_CLICKED(IDRB_ROTATION_180, OnRB_Rotation180)
	ON_BN_CLICKED(IDRB_ROTATION_270, OnRB_Rotation270)
	ON_BN_CLICKED(IDCB_USETOOLTIP, OnCB_UseToolTip)
	ON_BN_CLICKED(IDCB_USEHIGHLIGHTINGONLYWITHTOOLTIP, OnCB_UseHighLightingOnlyWithTooltip)
	ON_BN_CLICKED(IDCB_USELEFTBUTTON, OnCB_UseLeftButton)
	ON_BN_CLICKED(IDCB_USETOOLTIPONMOUSECLICK, OnCB_UseTooltipOnMouseClick)
	ON_BN_CLICKED(IDCB_DISABLE, OnCB_Disable)
	ON_BN_CLICKED(IDCB_USEBACKIMAGE, OnCB_UseBackImage)
	ON_BN_CLICKED(IDCB_LOWERCASE, OnCB_LowerCase)
	ON_BN_CLICKED(IDCB_UPPERCASE, OnCB_UpperCase)
	ON_BN_CLICKED(IDCB_STRETCHBITMAP, OnCB_StretchBitmap)
	//}}AFX_MSG_MAP
  ON_MESSAGE(CPN_SELENDOK, OnSelEndOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterDlg message handlers

BOOL CCNewLabelTesterDlg::OnInitDialog()
 {
  CDialog::OnInitDialog();

  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon

  m_CB_Font.Initialize();
  m_CB_Font.UsePrinterFonts(TRUE);

//   m_MSL_Horz.SubclassDlgItem(IDMSL_HORZ, this);
//   m_MSL_Vert.SubclassDlgItem(IDMSL_VERT, this);
// 
//   if (IsWindow(m_MSL_Horz.GetSafeHwnd()))
//    {
//     m_MSL_Horz.SetRanges(0,100);
//     m_MSL_Horz.SetTicFreq(10);
//     m_MSL_Horz.m_NumMarkers = 2;
//    }
//   else GetDlgItem(IDMSL_HORZ)->ShowWindow(SW_HIDE);
// 
//   if (IsWindow(m_MSL_Vert.GetSafeHwnd()))
//    {
//     m_MSL_Vert.SetRanges(0,100);
//     m_MSL_Vert.SetTicFreq(10);
//     m_MSL_Vert.m_NumMarkers = 2;
//    }
//   else GetDlgItem(IDMSL_VERT)->ShowWindow(SW_HIDE);

  //m_NL_TestZone.ForceNoOwnerDraw(TRUE);
  m_NL_TestZone.SetToolTipPosition(1);
  m_NL_TestZone.SetToolTipText("TOOLTIP TEXT");

  SetDlgItemText(IDED_FLASHTEXTTIME, "500");
  SetDlgItemText(IDED_FLASHBACKTIME, "500");

  SetDlgItemText(IDED_TEXT, m_NL_TestZone.GetText());

  ((CButton *)GetDlgItem(IDCB_TEXTCOLOR  ))->SetCheck( !m_NL_TestZone.IsDefaultTextColor() );
  ((CButton *)GetDlgItem(IDCB_TEXTBKCOLOR))->SetCheck( !m_NL_TestZone.IsDefaultTextBackColor() );
  ((CButton *)GetDlgItem(IDCB_BKGNDCOLOR ))->SetCheck( !m_NL_TestZone.IsDefaultBkColor() );

  m_PB_TextColor.SetColour( m_NL_TestZone.GetTextColor() );
  m_PB_TextBkColor.SetColour( m_NL_TestZone.GetTextBackColor() );
  m_PB_BkgndColor.SetColour( m_NL_TestZone.GetBkColor() );

  ((CButton *)GetDlgItem(IDCB_SETFONTBOLD     ))->SetCheck( m_NL_TestZone.GetFontBold() );
  ((CButton *)GetDlgItem(IDCB_SETFONTITALIC   ))->SetCheck( m_NL_TestZone.GetFontItalic() );
  ((CButton *)GetDlgItem(IDCB_SETFONTUNDERLINE))->SetCheck( m_NL_TestZone.GetFontUnderline() );

  SetDlgItemInt(IDED_FONTSIZE, m_NL_TestZone.GetFontSize(), TRUE);

  m_CB_Font.SetFaceName( m_NL_TestZone.GetFontName() );
  
  ((CButton *)GetDlgItem(IDCB_SETBORDER))->SetCheck( m_NL_TestZone.GetBorder() );
  ((CButton *)GetDlgItem(IDCB_SETSUNKEN))->SetCheck( m_NL_TestZone.GetSunken() );
  ((CButton *)GetDlgItem(IDCB_SETLINK  ))->SetCheck( m_NL_TestZone.GetLink() );

  m_PB_HighLightColor.SetColour( m_NL_TestZone.GetHighLightColor() );

  ((CButton *)GetDlgItem(IDCB_USEBEVELLINE))->SetCheck( m_NL_TestZone.GetBevelLine() );

  m_CB_HorzAlign.SetCurSel( m_NL_TestZone.GetHorzAlignmentIndex() );
  m_CB_VertAlign.SetCurSel( m_NL_TestZone.GetVertAlignmentIndex() );

  ((CButton *)GetDlgItem(IDCB_SETVERTICALTEXT))->SetCheck( m_NL_TestZone.GetVerticalText() );

  ((CButton *)GetDlgItem(IDRB_ROTATION_0))->SetCheck(TRUE);

  ((CButton *)GetDlgItem(IDCB_USETOOLTIP))->SetCheck( m_NL_TestZone.IsToolTipUsed() );

  ((CButton *)GetDlgItem(IDCB_USEHIGHLIGHTINGONLYWITHTOOLTIP))->SetCheck( m_NL_TestZone.UseHighLightingOnlyWithToolTip() );
  
  ((CButton *)GetDlgItem(IDCB_USELEFTBUTTON))->SetCheck( m_NL_TestZone.UseToolTipOnLeftMouseClick() );
  
  ((CButton *)GetDlgItem(IDCB_USETOOLTIPONMOUSECLICK))->SetCheck( m_NL_TestZone.UseToolTipWithMouseClick() );

  ((CButton *)GetDlgItem(IDCB_DISABLE))->SetCheck( m_NL_TestZone.IsDisabled() );

  ((CButton *)GetDlgItem(IDCB_LOWERCASE))->SetCheck( m_NL_TestZone.IsLowerCase() );

  ((CButton *)GetDlgItem(IDCB_UPPERCASE))->SetCheck( m_NL_TestZone.IsUpperCase() );

  ((CButton *)GetDlgItem(IDCB_STRETCHBITMAP))->SetCheck( m_NL_TestZone.IsBitmapStretched() );

  UpdateData(FALSE);

  return TRUE;
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnPaint() 
 {
  if (IsIconic())
   {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
   }
  else CDialog::OnPaint();
 }

// --------------------------------------------------------------------------

HCURSOR CCNewLabelTesterDlg::OnQueryDragIcon()
 {
  return (HCURSOR) m_hIcon;
 }

// --------------------------------------------------------------------------

BOOL CCNewLabelTesterDlg::DestroyWindow() 
 {
  return CDialog::DestroyWindow();
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnChange_Text() 
 {
  CString str1, str2;

  GetDlgItemText(IDED_TEXT, str1);

  for (int I=0; I<str1.GetLength(); I++)
   {
    if (str1[I] != '\r') str2 += str1[I];
   }

  m_NL_TestZone.SetText(str2);
 }

// --------------------------------------------------------------------------

LONG CCNewLabelTesterDlg::OnSelEndOK(UINT lParam, LONG wParam)
 {
  int nID = (int)wParam;

  if (nID == m_PB_TextColor.GetDlgCtrlID())
   {
    OnCB_TextColor();
   }
  else if (nID == m_PB_TextBkColor.GetDlgCtrlID())
   {
    OnCB_TextBkColor();
   }
  else if (nID == m_PB_BkgndColor.GetDlgCtrlID())
   {
    OnCB_BkgndColor();
   }

  else if (nID == m_PB_HighLightColor.GetDlgCtrlID())
   {
    m_NL_TestZone.SetHighLightColor( m_PB_HighLightColor.GetColour() );
   }

  return TRUE;
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_TextColor() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_TEXTCOLOR))->GetCheck();

  if (bChecked)
   {
    m_NL_TestZone.SetTextColor(m_PB_TextColor.GetColour());
   }
  else m_NL_TestZone.SetDefaultTextColor();
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_TextBkColor() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_TEXTBKCOLOR))->GetCheck();

  if (bChecked)
   {
    m_NL_TestZone.SetTextBackColor(m_PB_TextBkColor.GetColour());
   }
  else m_NL_TestZone.SetDefaultTextBackColor();
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_BkgndColor() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_BKGNDCOLOR))->GetCheck();

  if (bChecked)
   {
    m_NL_TestZone.SetBkColor(m_PB_BkgndColor.GetColour());
   }
  else m_NL_TestZone.SetDefaultBkColor();
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetFontBold() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETFONTBOLD))->GetCheck();

  m_NL_TestZone.SetFontBold(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetFontItalic() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETFONTITALIC))->GetCheck();

  m_NL_TestZone.SetFontItalic(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetFontUnderline() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETFONTUNDERLINE))->GetCheck();

  m_NL_TestZone.SetFontUnderline(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnPB_SetFontSize() 
 {
  CString str;
  
  GetDlgItemText(IDED_FONTSIZE, str);

  int iSize = atoi_replace(str);

  m_NL_TestZone.SetFontSize(iSize);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnSelchange_Font() 
 {
  CString strFaceName = m_CB_Font.GetFaceName();

  m_NL_TestZone.SetFontName(strFaceName);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetBorder() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETBORDER))->GetCheck();

  m_NL_TestZone.SetBorder(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetSunken() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETSUNKEN))->GetCheck();

  m_NL_TestZone.SetSunken(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetLink() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETLINK))->GetCheck();

  m_NL_TestZone.SetLink(bChecked);

  if (bChecked)
   {
    m_NL_TestZone.SetText("www.microsoft.com");
    m_NL_TestZone.SetLinkCursor(IDC_HAND);
   }
  else {
        m_NL_TestZone.SetText("This is a string");
        m_NL_TestZone.SetLinkCursor((UINT)0);
       }
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseHighlighting() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USEHIGHLIGHTING))->GetCheck();
  
  m_NL_TestZone.UseHighLighting(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseBevelLine() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USEBEVELLINE))->GetCheck();
  
  m_NL_TestZone.UseBevelLine(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnSelchange_Horzalign() 
 {
  int iHorzSel = m_CB_HorzAlign.GetCurSel();
  int iVertSel = m_CB_VertAlign.GetCurSel();

  if (iHorzSel == CB_ERR || iVertSel == CB_ERR) return;

  DWORD dwAlign = 0;

  switch(iHorzSel)
   {
    case 0 : dwAlign |= CNewLabel::HORZ_LEFT; break;
    case 1 : dwAlign |= CNewLabel::HORZ_CENTER; break;
    case 2 : dwAlign |= CNewLabel::HORZ_RIGHT; break;
   }

  switch(iVertSel)
   {
    case 0 : dwAlign |= CNewLabel::VERT_TOP; break;
    case 1 : dwAlign |= CNewLabel::VERT_CENTER; break;
    case 2 : dwAlign |= CNewLabel::VERT_BOTTOM; break;
   }

  m_NL_TestZone.SetAlignment(dwAlign);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnSelchange_Vertalign() 
 {
  OnSelchange_Horzalign();
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_SetVerticalText() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_SETVERTICALTEXT))->GetCheck();
  
  m_NL_TestZone.SetVerticalText(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_TextFlash() 
 {
  BOOL    bChecked = ((CButton *)GetDlgItem(IDCB_TEXTFLASH))->GetCheck();
  CString strTime;

  GetDlgItemText(IDED_FLASHTEXTTIME, strTime);

  m_NL_TestZone.FlashText(bChecked, atoi_replace(strTime));
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_BkFlash() 
 {
  BOOL    bChecked = ((CButton *)GetDlgItem(IDCB_BKFLASH))->GetCheck();
  CString strTime;

  GetDlgItemText(IDED_FLASHBACKTIME, strTime);

  m_NL_TestZone.FlashBackground(bChecked, atoi_replace(strTime));
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnRB_Rotation0() 
 {
  m_NL_TestZone.SetAngle(0);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnRB_Rotation90() 
 {
  m_NL_TestZone.SetAngle(90);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnRB_Rotation180() 
 {
  m_NL_TestZone.SetAngle(180);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnRB_Rotation270() 
 {
  m_NL_TestZone.SetAngle(270);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseToolTip() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USETOOLTIP))->GetCheck();

  m_NL_TestZone.UseToolTip(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseHighLightingOnlyWithTooltip() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USEHIGHLIGHTINGONLYWITHTOOLTIP))->GetCheck();

  m_NL_TestZone.UseHighLightingOnlyWithToolTip(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseLeftButton() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USELEFTBUTTON))->GetCheck();

  m_NL_TestZone.UseLeftMouseButtonForToolTip(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseTooltipOnMouseClick() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USETOOLTIPONMOUSECLICK))->GetCheck();
  
  m_NL_TestZone.ShowToolTipOnlyOnMouseClick(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_Disable() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_DISABLE))->GetCheck();

  m_NL_TestZone.SetDisabled(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UseBackImage() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_USEBACKIMAGE))->GetCheck();

  m_NL_TestZone.SetBackImage(bChecked ? IDB_MIKE : -1);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_LowerCase() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_LOWERCASE))->GetCheck();

  ((CButton *)GetDlgItem(IDCB_UPPERCASE))->SetCheck(FALSE);

  m_NL_TestZone.SetLowerCase(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_UpperCase() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_UPPERCASE))->GetCheck();

  ((CButton *)GetDlgItem(IDCB_LOWERCASE))->SetCheck(FALSE);

  m_NL_TestZone.SetUpperCase(bChecked);
 }

// --------------------------------------------------------------------------

void CCNewLabelTesterDlg::OnCB_StretchBitmap() 
 {
  BOOL bChecked = ((CButton *)GetDlgItem(IDCB_STRETCHBITMAP))->GetCheck();

  m_NL_TestZone.StretchBitmap(bChecked);
 }

// --------------------------------------------------------------------------
