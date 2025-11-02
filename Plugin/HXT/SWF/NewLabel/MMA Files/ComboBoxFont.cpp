// ==========================================================================
// ComboBoxFont.cpp
// 
// Author : Mike Marquet
//          mike.marquet@altavista.net
//
// Last Modified : 27/10/1999
// by            : Mike marquet
// ==========================================================================

// ==========================================================================
// Les Includes
// ==========================================================================

#include "stdafx.h"
#include "comboboxfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Class CComboBoxFontTip

CComboBoxFontTip::CComboBoxFontTip()
 {
 }

// --------------------------------------------------------------------------

CComboBoxFontTip::~CComboBoxFontTip()
 {
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFontTip::Create(CWnd *pParentWnd)
 {
  return CWnd::CreateEx(0,
                        AfxRegisterWndClass(0),
                        NULL,
                        WS_BORDER | WS_POPUP,
                        0,
                        0,
                        0,
                        0,
                        NULL,
                        (HMENU)0);
 }

// --------------------------------------------------------------------------

void CComboBoxFontTip::ShowTips(CPoint pt, const CString &str, BOOL bForceChange)
 {
  CSize  sz;
  CDC   *pDC = GetDC();

  // Create new font if the selection has changed
  if (bForceChange || m_strFont != str)
   {
    m_strFont = str;

    LOGFONT stLF;
    
    ZeroMemory(&stLF, sizeof(stLF));

    stLF.lfHeight = -18;

    strcpy(stLF.lfFaceName, m_strFont);

    // Delete old font
    m_Font.DeleteObject();
    m_Font.CreateFontIndirect(&stLF);

    CFont *pOldFont = pDC->SelectObject(&m_Font);

    // String demensions of font on screen
    sz = pDC->GetTextExtent(m_strFont);

    // Give some space round the font
    sz.cx += 8;
    sz.cy += 8;

    pDC->SelectObject(pOldFont);
    ReleaseDC(pDC);

    SetWindowPos(0, pt.x, pt.y, sz.cx, sz.cy, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    RedrawWindow(); // Force immediate redraw
   }
 }

// --------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CComboBoxFontTip, CWnd)
	//{{AFX_MSG_MAP(CComboBoxFontTip)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxFontTip message handlers

BOOL CComboBoxFontTip::OnEraseBkgnd(CDC *pDC) 
 {
  CBrush cBrush(GetSysColor(COLOR_INFOBK));
  CRect  cRect;

  pDC->GetClipBox(cRect);

  CBrush *pOldBrush = pDC->SelectObject(&cBrush);

  pDC->PatBlt(cRect.left, cRect.top, cRect.Width(), cRect.Height(), PATCOPY);
  pDC->SelectObject(pOldBrush);

  return TRUE;
  //return CWnd::OnEraseBkgnd(pDC);
 }

// --------------------------------------------------------------------------

void CComboBoxFontTip::OnPaint() 
 {
  CPaintDC dc(this); // device context for painting
  CRect    cRect;

  dc.SelectObject(&m_Font);
  GetClientRect(cRect);
  dc.SetBkMode(TRANSPARENT);
  dc.SetTextColor(GetSysColor(COLOR_INFOTEXT));
  dc.DrawText(m_strFont, cRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
 }

/////////////////////////////////////////////////////////////////////////////
// Class CFontObject

CFontObject::CFontObject()
 {
  m_bScreenFont = TRUE;

  m_strFaceName.Empty();

  ZeroMemory(&m_stELF, sizeof(m_stELF));
  ZeroMemory(&m_stNTM, sizeof(m_stNTM));

  m_iFontType = 0;
 }

// --------------------------------------------------------------------------

CFontObject::~CFontObject()
 {
 }

// --------------------------------------------------------------------------

void CFontObject::SetFontObject(CFontObject *pFontObject)
 {
  m_bScreenFont = pFontObject->m_bScreenFont;
  m_strFaceName = pFontObject->m_strFaceName;
  m_iFontType   = pFontObject->m_iFontType;

  memcpy(&m_stELF, &pFontObject->m_stELF, sizeof(ENUMLOGFONTEX));
  memcpy(&m_stNTM, &pFontObject->m_stNTM, sizeof(NEWTEXTMETRICEX));
 }

// --------------------------------------------------------------------------

void CFontObject::SetEnumLogFontExStructure(ENUMLOGFONTEX *pstELF)
 {
  memcpy(&m_stELF, pstELF, sizeof(ENUMLOGFONTEX));

  m_strFaceName = pstELF->elfLogFont.lfFaceName;
 }

// --------------------------------------------------------------------------

void CFontObject::SetNewTextMetricExStructure(NEWTEXTMETRICEX *pstNTM)
 {
  memcpy(&m_stNTM, pstNTM, sizeof(NEWTEXTMETRICEX));
 }

// --------------------------------------------------------------------------

void CFontObject::SetFontType(int iFontType)
 {
  m_iFontType = iFontType;
 }

/////////////////////////////////////////////////////////////////////////////
// CComboBoxFont

CComboBoxFont::CComboBoxFont(int iMRUSize)
 {
  m_bInitialized     = FALSE;
  m_bUseScreenFonts  = TRUE;
  m_bUsePrinterFonts = FALSE;
  m_iMRUSize         = iMRUSize;
  m_uIDBitmapGlyphs  = 0;
  m_iGlyphsWidth     = 0;
  m_clrMRUBk         = RGB(255,255,255);
  m_clrMRUText       = RGB(0,0,0);
  m_clrListBk        = RGB(255,255,255);
  m_clrListText      = RGB(0,0,0);
  m_lfCharSet        = DEFAULT_CHARSET;
  m_lfFaceName       = "";
  m_lfPitchAndFamily = 0;
 }

// --------------------------------------------------------------------------

CComboBoxFont::~CComboBoxFont()
 {
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFont::AddFont(BOOL bScreenFont, ENUMLOGFONTEX *pstELF, NEWTEXTMETRICEX *pstNTM, int iFontType)
 {
  CString strFaceName = pstELF->elfLogFont.lfFaceName;

  if (FontAlreadyInList(strFaceName)) return TRUE;

  CFontObject *pFontObject = new CFontObject;

  if (!pFontObject) return FALSE;

  if (!bScreenFont) pFontObject->SetPrinterFont();

  pFontObject->SetEnumLogFontExStructure(pstELF);
  pFontObject->SetNewTextMetricExStructure(pstNTM);
  pFontObject->SetFontType(iFontType);

  m_obaFontList.Add(pFontObject);

  return TRUE;
 }

// --------------------------------------------------------------------------

void CComboBoxFont::ClearFontList()
 {
  for (int I=0; I<m_obaFontList.GetSize(); I++)
   {
    CFontObject *pFontObject = (CFontObject *)m_obaFontList.GetAt(I);

    if (!pFontObject) continue;

    delete pFontObject;
   }

  m_obaFontList.RemoveAll();
 }

// --------------------------------------------------------------------------

void CComboBoxFont::ClearMRUList()
 {
  int iCount = m_oblMRU.GetCount();

  for (int I=0; I<iCount; I++)
   {
    delete m_oblMRU.RemoveTail();
   }
 }

// --------------------------------------------------------------------------

void CComboBoxFont::DisplayTips(BOOL bForceChange)
 {
  int iSel      = GetCurSel();
  int iFirstVis = GetTopIndex();

  // Selected
  if (iSel != -1 && iFirstVis <= iSel)
   {
    CRect cRect;

    GetDroppedControlRect(cRect);

    int iItemHeight = GetItemHeight(0);
    int iLastVis    = iFirstVis + ((cRect.Height() - iItemHeight) / iItemHeight);

    if (iSel <= iLastVis)
     {
      int iHeight = iItemHeight * ((iSel - iFirstVis) + 1);

      CPoint pt(cRect.right + 5, cRect.top + iHeight);

      // Show tip in correct position
      CString str;

      GetLBText(iSel, str);

      m_cFontTip.ShowTips(pt, str, TRUE);
     }
   }
 }

// --------------------------------------------------------------------------

void CComboBoxFont::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
 {
  ASSERT(lpDIS->CtlType == ODT_COMBOBOX); // We've gotta be a combo

  int iMRUCount = m_oblMRU.GetCount();

  // Lets make a CDC for ease of use
  CDC *pDC = CDC::FromHandle(lpDIS->hDC);

  ASSERT(pDC); // Attached failed

  CRect cItemRect(lpDIS->rcItem);

  // Draw focus rectangle
  if (lpDIS->itemState & ODS_FOCUS) pDC->DrawFocusRect(cItemRect);

  // Save off context attributes
  int iIndexDC = pDC->SaveDC();

  CBrush cFillBrush;

  // Draw selection state
  if (lpDIS->itemState & ODS_SELECTED)
   {
    cFillBrush.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
    pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
   }
  else if (iMRUCount && (int)lpDIS->itemID < iMRUCount)
        {
         cFillBrush.CreateSolidBrush(m_clrMRUBk);
        }
       else {
             cFillBrush.CreateSolidBrush(m_clrListBk);
             //cFillBrush.CreateSolidBrush(pDC->GetBkColor());
            }

  pDC->SetBkMode(TRANSPARENT);
  pDC->FillRect(cItemRect, &cFillBrush);

  CString strCurFont;
  CString strNextFont;

  GetLBText(lpDIS->itemID, strCurFont);

  int iX = cItemRect.left; // Save for lines

  // Render Bitmaps
  if (m_uIDBitmapGlyphs)
   {
    CFontObject *pFontObject = GetFontObject(strCurFont);

    if (pFontObject)
     {
      if (pFontObject->GetFontType() & TRUETYPE_FONTTYPE)
       {
        m_cImageList.Draw(pDC, 1, CPoint(cItemRect.left,cItemRect.top), ILD_TRANSPARENT);
       }
      
      if (pFontObject->GetFontType() & PRINTER_FONTTYPE)
       {
        m_cImageList.Draw(pDC, 0, CPoint(cItemRect.left + m_iGlyphsWidth + 1,cItemRect.top), ILD_TRANSPARENT);
       }

      int iMultiplier = 1;
      
      if (m_bUsePrinterFonts) iMultiplier++;

      cItemRect.left += (iMultiplier * (m_iGlyphsWidth + 2)); // Text Position
     }
   }

  COLORREF clrOldText = pDC->GetTextColor();

  if (iMRUCount && (int)lpDIS->itemID < iMRUCount) pDC->SetTextColor(m_clrMRUText);
  else pDC->SetTextColor(m_clrListText);

  pDC->TextOut(cItemRect.left, cItemRect.top, strCurFont);

  pDC->SetTextColor(clrOldText);

  if (iMRUCount && iMRUCount == (int)lpDIS->itemID + 1)
   {
    // Draw font MRU separator
    TEXTMETRIC stTM;

    pDC->GetTextMetrics(&stTM);

    pDC->MoveTo(iX             , cItemRect.top + stTM.tmHeight);
    pDC->LineTo(cItemRect.right, cItemRect.top + stTM.tmHeight);

    pDC->MoveTo(iX             , cItemRect.top + stTM.tmHeight + 2);
    pDC->LineTo(cItemRect.right, cItemRect.top + stTM.tmHeight + 2);
   }

  // Restore state of context
  pDC->RestoreDC(iIndexDC);
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFont::EnumeratePrinterFonts()
 {
  CPrintDialog cPrintDlg(FALSE);

  if (AfxGetApp()->GetPrinterDeviceDefaults(&cPrintDlg.m_pd))
   {
    HDC hDC = cPrintDlg.CreatePrinterDC();

    if (hDC)
     {
      LOGFONT stLF;

      ZeroMemory(&stLF, sizeof(stLF));

      stLF.lfCharSet = m_lfCharSet;
      strcpy(stLF.lfFaceName, m_lfFaceName);
      stLF.lfPitchAndFamily = m_lfPitchAndFamily;

      if (!EnumFontFamiliesEx(hDC,                                    // Handle to device context
                              &stLF,                                  // Pointer to logical font information
                              (FONTENUMPROC)EnumFamPrinterCallBackEx, // Pointer to callback function
                              (LPARAM)this,                           // Application-supplied data
                              (DWORD)0))
       {
        return FALSE;
       }
     }
   }

  return TRUE;
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFont::EnumerateScreenFonts()
 {
  HDC     hDC = ::GetWindowDC(NULL);
  LOGFONT stLF;

  ZeroMemory(&stLF, sizeof(stLF));

  stLF.lfCharSet = m_lfCharSet;
  strcpy(stLF.lfFaceName, m_lfFaceName);
  stLF.lfPitchAndFamily = m_lfPitchAndFamily;

  if (!EnumFontFamiliesEx(hDC,                                   // Handle to device context
                          &stLF,                                 // Pointer to logical font information
                          (FONTENUMPROC)EnumFamScreenCallBackEx, // Pointer to callback function
                          (LPARAM)this,                          // Application-supplied data
                          (DWORD)0))
   {
    return FALSE;
   }

  ::ReleaseDC(NULL, hDC);

  return TRUE;
 }

// --------------------------------------------------------------------------

BOOL CALLBACK AFX_EXPORT CComboBoxFont::EnumFamPrinterCallBackEx(ENUMLOGFONTEX   *pstELF,
                                                                 NEWTEXTMETRICEX *pstNTM,
                                                                 int              iFontType,
                                                                 LPVOID           pThis)
 {
  //TRACE("(CComboBoxFont) EnumFamPrinterCallBackEx(,, iFontType = 0x%X,) : FaceName = %s\n", iFontType, pstELF->elfLogFont.lfFaceName);

  iFontType |= PRINTER_FONTTYPE;

  ((CComboBoxFont *)pThis)->AddFont(TRUE, pstELF, pstNTM, iFontType);

  return TRUE; // Call me back
 }

// --------------------------------------------------------------------------

BOOL CALLBACK AFX_EXPORT CComboBoxFont::EnumFamScreenCallBackEx(ENUMLOGFONTEX   *pstELF,
                                                                NEWTEXTMETRICEX *pstNTM,
                                                                int              iFontType,
                                                                LPVOID           pThis)
 {
  //TRACE("(CComboBoxFont) EnumFamScreenCallBackEx(,, iFontType = 0x%X,) : FaceName = %s\n", iFontType, pstELF->elfLogFont.lfFaceName);

  ((CComboBoxFont *)pThis)->AddFont(TRUE, pstELF, pstNTM, iFontType);

  return TRUE; // Call me back
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFont::FontAlreadyInList(CString strFaceName)
 {
  for (int I=0; I<m_obaFontList.GetSize(); I++)
   {
    CFontObject *pFontObject = (CFontObject *)m_obaFontList.GetAt(I);

    if (!pFontObject) continue;

    if (pFontObject->GetFaceName() == strFaceName) return TRUE;
   }

  return FALSE;
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFont::FontAlreadyInMRUList(CString strFaceName)
 {
  for (POSITION pos = m_oblMRU.GetHeadPosition(); pos != NULL;)
   {
    CFontObject *pFontObject = (CFontObject *)m_oblMRU.GetAt(pos);

    if (pFontObject && pFontObject->GetFaceName() == strFaceName) return TRUE;

    m_oblMRU.GetNext(pos);
   }

  return FALSE;
 }

// --------------------------------------------------------------------------

CFontObject *CComboBoxFont::GetFontObject(const CString &strFaceName)
 {
  for (int I=0; I<m_obaFontList.GetSize(); I++)
   {
    CFontObject *pFontObject = (CFontObject *)m_obaFontList.GetAt(I);

    if (pFontObject && pFontObject->GetFaceName() == strFaceName) return pFontObject;
   }

  return NULL;
 }

// --------------------------------------------------------------------------

BOOL CComboBoxFont::Initialize()
 {
  if (m_bInitialized)
   {
    KillTimer(1);
    ResetContent();
    m_cImageList.DeleteImageList();
    m_cFontTip.DestroyWindow();
    ClearFontList();
    ClearMRUList();
    m_bInitialized = FALSE;
   }

  // Load up glyphs
  if (m_uIDBitmapGlyphs)
   {
    if (!m_cImageList.Create(m_uIDBitmapGlyphs, m_iGlyphsWidth, 1, RGB(255,0,255)))
     {
      m_uIDBitmapGlyphs = 0;
     }
   }

  // Create tip window
  m_cFontTip.Create(this);

  if (m_bUseScreenFonts && !EnumerateScreenFonts())
   {
    ClearFontList();
    return FALSE;
   }

  if (m_bUsePrinterFonts && !EnumeratePrinterFonts())
   {
    ClearFontList();
    return FALSE;
   }

  // Ajouter les polices dans la combobox
  for (int I=0; I<m_obaFontList.GetSize(); I++)
   {
    CFontObject *pFontObject = (CFontObject *)m_obaFontList.GetAt(I);

    if (!pFontObject) continue;

    AddString(pFontObject->GetFaceName());
   }

  // We set the timer because its the only way we know when a selection
  // has changed - use for tip window
  SetTimer(1, 500, NULL);

  m_bInitialized = TRUE;

  return TRUE;
 }

// --------------------------------------------------------------------------

void CComboBoxFont::PreSubclassWindow()
 {
  CComboBox::PreSubclassWindow();

//   LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
// 
//   lStyle |= CBS_OWNERDRAWFIXED;
//   lStyle |= CBS_HASSTRINGS;
// 
//   SetWindowLong(GetSafeHwnd(), GWL_STYLE, lStyle);
// 
//   SetWindowPos(NULL, 0, 0, 0, 0,  SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);

  Initialize();
 }

// --------------------------------------------------------------------------

void CComboBoxFont::SetFaceName(CString lfFaceName)
 {
  int iPos = FindStringExact(-1, lfFaceName);

  if (iPos != CB_ERR)
   {
    SetCurSel(iPos);
    
    m_lfFaceName = lfFaceName;
   }
 }

// --------------------------------------------------------------------------

void CComboBoxFont::SetMRUFont(const CString &strFont)
 {
  if (!m_iMRUSize) return;

  CFontObject *pFontObject = GetFontObject(strFont);

  if (!pFontObject) return;

  if (!FontAlreadyInMRUList(strFont))
   {
    int iCount = m_oblMRU.GetCount();

    if (iCount == m_iMRUSize)
     {
      DeleteString(m_iMRUSize - 1);

      delete m_oblMRU.RemoveTail();
     } 

    CFontObject *pNewFontObject = new CFontObject;

    pNewFontObject->SetFontObject(pFontObject);

    m_oblMRU.AddHead(pNewFontObject);

    InsertString(0, strFont);
   }
 }

// --------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CComboBoxFont, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxFont)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_WM_TIMER()
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillfocus)
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetfocus)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxFont message handlers

void CComboBoxFont::OnCloseup() 
 {
  CString strFont;
  int     iSel = GetCurSel();

  if (iSel != CB_ERR)
   {
    GetLBText(iSel, strFont);
    SetMRUFont(strFont);
   }
  
  m_cFontTip.ShowWindow(SW_HIDE);
 }

// --------------------------------------------------------------------------

void CComboBoxFont::OnSelendok() 
 {
  CString strFont;
  int     iSel = GetCurSel();

  if (iSel != CB_ERR)
   {
    GetLBText(iSel, strFont);
    m_lfFaceName = strFont;
   }
 }

// --------------------------------------------------------------------------

int CComboBoxFont::OnCreate(LPCREATESTRUCT lpCreateStruct) 
 {
  if (CComboBox::OnCreate(lpCreateStruct) == -1) return -1;

  Initialize();
	
  return 0;
 }

// --------------------------------------------------------------------------

void CComboBoxFont::OnDestroy() 
 {
  m_cFontTip.DestroyWindow();

  ClearMRUList();
  ClearFontList();

  CComboBox::OnDestroy();
 }

// --------------------------------------------------------------------------

void CComboBoxFont::OnDropdown() 
 {
  DisplayTips(TRUE);
 }

// --------------------------------------------------------------------------

void CComboBoxFont::OnKillfocus() 
 {
  CString strSelFont;

  // Change font in edit box if a known font
  // otherwise reject and restore original
  int iSel = GetCurSel();

  if (iSel == CB_ERR)
   {
    GetWindowText(strSelFont);
    iSel = FindStringExact(-1, strSelFont);

    if (iSel == CB_ERR) SetWindowText(m_strFontSave);
    else {
          GetLBText(iSel, strSelFont);
          SetWindowText(strSelFont);
         }
   }
 }

// --------------------------------------------------------------------------

void CComboBoxFont::OnSetfocus() 
 {
  // Save off original font
  GetWindowText(m_strFontSave);
 }

// --------------------------------------------------------------------------

void CComboBoxFont::OnTimer(UINT nIDEvent) 
 {
  // If combo open ?
  if (GetDroppedState()) DisplayTips();
	
  CComboBox::OnTimer(nIDEvent);
 }

// ==========================================================================
// ==========================================================================
