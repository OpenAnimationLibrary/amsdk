// ==========================================================================
// ComboBoxFont.h
// 
// Author : Mike Marquet
//          mike.marquet@altavista.net
//
// Last Modified : 27/10/1999
// by            : Mike marquet
// ==========================================================================

#if !defined(AFX_COMBOBOXFONT_H__5FA6AE43_8C53_11D3_A0B9_004005555C30__INCLUDED_)
#define AFX_COMBOBOXFONT_H__5FA6AE43_8C53_11D3_A0B9_004005555C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CComboBoxFontTip window

class CComboBoxFontTip : public CWnd
 {
  protected :
              CString m_strFont;
              CFont   m_Font;

  public :
           CComboBoxFontTip();
           virtual ~CComboBoxFontTip();

           BOOL Create(CWnd *pParentWnd);
           void ShowTips(CPoint pt, const CString &str, BOOL bForceChange = FALSE);

  public :
	//{{AFX_VIRTUAL(CComboBoxFontTip)
	//}}AFX_VIRTUAL

  protected :
	//{{AFX_MSG(CComboBoxFontTip)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
 };

/////////////////////////////////////////////////////////////////////////////
// Class CFontObject

class CFontObject : public CObject
 {
  protected :
              BOOL            m_bScreenFont;
              CString         m_strFaceName;
              ENUMLOGFONTEX   m_stELF;
              NEWTEXTMETRICEX m_stNTM;
              int             m_iFontType;
              
  public :
           CFontObject();
           virtual ~CFontObject();

           void SetFontObject(CFontObject *pFontObject);
           void SetEnumLogFontExStructure(ENUMLOGFONTEX *pstELF);
           void SetNewTextMetricExStructure(NEWTEXTMETRICEX *pstNTM);
           void SetFontType(int iFontType);

           // INLINE
           CString GetFaceName() { return m_strFaceName; }
           int GetFontType() { return m_iFontType; }

           void SetScreenFont() { m_bScreenFont = TRUE; }
           void SetPrinterFont() { m_bScreenFont = FALSE; }
 };

/////////////////////////////////////////////////////////////////////////////
// CComboBoxFont window

class CComboBoxFont : public CComboBox
 {
  protected :
              BOOL             m_bInitialized;
              CObArray         m_obaFontList;
              CObList          m_oblMRU;
              CComboBoxFontTip m_cFontTip;
              BOOL             m_bUseScreenFonts;
              BOOL             m_bUsePrinterFonts;
              CString          m_strFontSave;
              int              m_iMRUSize;
              CImageList       m_cImageList;
              UINT             m_uIDBitmapGlyphs;
              int              m_iGlyphsWidth;
              COLORREF         m_clrMRUBk;
              COLORREF         m_clrMRUText;
              COLORREF         m_clrListBk;
              COLORREF         m_clrListText;
              BYTE             m_lfCharSet;
              CString          m_lfFaceName;
              BYTE             m_lfPitchAndFamily; // 0 or MONO_FONT

              static BOOL CALLBACK AFX_EXPORT EnumFamPrinterCallBackEx(ENUMLOGFONTEX   *,
                                                                       NEWTEXTMETRICEX *,
                                                                       int,
                                                                       LPVOID);

              static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBackEx(ENUMLOGFONTEX   *,
                                                                      NEWTEXTMETRICEX *,
                                                                      int,
                                                                      LPVOID);

              BOOL         AddFont(BOOL, ENUMLOGFONTEX *, NEWTEXTMETRICEX *, int);
              void         ClearFontList();
              void         ClearMRUList();
              void         DisplayTips(BOOL bForceChange = FALSE);
              BOOL         EnumeratePrinterFonts();
              BOOL         EnumerateScreenFonts();
              BOOL         FontAlreadyInList(CString);
              BOOL         FontAlreadyInMRUList(CString);
              CFontObject *GetFontObject(const CString &strFaceName);
              void         SetMRUFont(const CString &strFont);

  public :
           CComboBoxFont(int iMRUSize = 5);
           virtual ~CComboBoxFont();

           BOOL Initialize();

           void SetFaceName(CString lfFaceName = "");

           // INLINE
           BOOL IsInitialized() { return m_bInitialized; }
           BOOL IsPrinterFontsUsed() { return m_bUsePrinterFonts; }
           BOOL IsScreenFontsUsed() { return m_bUseScreenFonts; }

           BYTE     GetCharSet() { return m_lfCharSet; }
           CString  GetFaceName() { return m_lfFaceName; }
           COLORREF GetListBkColor() { return m_clrListBk; }
           COLORREF GetListTextColor() { return m_clrListText; }
           COLORREF GetMRUBkColor() { return m_clrMRUBk; }
           int      GetMRUSize() { return m_iMRUSize; }
           COLORREF GetMRUTextColor() { return m_clrMRUText; }
           BYTE     GetPitchAndFamily() { return m_lfPitchAndFamily; }

           void SetCharSet(BYTE lfCharSet = DEFAULT_CHARSET) { m_lfCharSet = lfCharSet; }
           void SetGlyphsImage(UINT uIDBitmapGlyphs, int iGlyphsWidth) { m_uIDBitmapGlyphs = uIDBitmapGlyphs; m_iGlyphsWidth = iGlyphsWidth; }
           void SetListBkColor(COLORREF clrListBk) { m_clrListBk = clrListBk; }
           void SetListTextColor(COLORREF clrListText) { m_clrListText = clrListText; }
           void SetMRUBkColor(COLORREF clrMRUBk) { m_clrMRUBk = clrMRUBk; }
           void SetMRUSize(int iMRUSize) { m_iMRUSize = iMRUSize; }
           void SetMRUTextColor(COLORREF clrMRUText) { m_clrMRUText = clrMRUText; }
           void SetPitchAndFamily(BYTE lfPitchAndFamily = 0) { m_lfPitchAndFamily = lfPitchAndFamily; }
           
           void UsePrinterFonts(BOOL bUsePrinterFonts) { m_bUsePrinterFonts = bUsePrinterFonts; }
           void UseScreenFonts(BOOL bUseScreenFonts) { m_bUseScreenFonts = bUseScreenFonts; }

  public :
	//{{AFX_VIRTUAL(CComboBoxFont)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

  protected :
	//{{AFX_MSG(CComboBoxFont)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnCloseup();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillfocus();
	afx_msg void OnSetfocus();
	afx_msg void OnDropdown();
	afx_msg void OnSelendok();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP()
 };

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXFONT2_H__5FA6AE43_8C53_11D3_A0B9_004005555C30__INCLUDED_)
