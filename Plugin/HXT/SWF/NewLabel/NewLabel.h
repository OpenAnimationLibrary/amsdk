// ==========================================================================
// CNewLabel.h
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 20/07/2000
// Last modification : 07/08/2000
// ==========================================================================

// REMARQUE : ROTATION WORKS ONLY ON WINDOWS NT/2000 !!!!!

#if !defined(AFX_NEWLABEL_H__50B040A0_5E0B_11D4_BC43_0050BAA38233__INCLUDED_)
#define AFX_NEWLABEL_H__50B040A0_5E0B_11D4_BC43_0050BAA38233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ==========================================================================
// Les Includes
// ==========================================================================

#include "ControlToolTip.h"

/////////////////////////////////////////////////////////////////////////////
// class CTextRotator

class CTextRotator {
protected :
    HDC m_hSourceDC;
    HDC m_hRotatedMemDC;
    CRect m_rectRotated;
    UINT m_uiHorzAlignment;
    UINT m_uiVertAlignment;
    UINT m_uiAngle;
    BOOL m_bDisabled;
    BOOL m_bDrawBevelLine;
    CString m_strText;
    COLORREF m_clrBackground;
    COLORREF m_clrText;

    static void AngleBlt(HDC hSourceDC, HDC hDestDC, RECT rectSource, UINT uiAngle);
    void Clear();
    static CSize GetLengthlyTextSize(HDC hDC, CStringArray *parrayText);

public :
    CTextRotator(HDC hSourceDC, LPCTSTR lpszText = "", UINT uiHorzAlignment = DT_LEFT, UINT uiVertAlignment = 0);
    virtual ~CTextRotator();

    [[nodiscard]] BOOL BitBltText(int X, int Y) const;
    BOOL BitBltText(CRect rectSource);
    void GetRotatedDC(CDC *pDC) const;
    void GetRotatedRect(RECT *pstRect) const;
    BOOL RotateText(UINT uiAngle = 0);

    // INLINE
    [[nodiscard]] HDC GetRotatedDC() const {
        return m_hRotatedMemDC;
    }

    [[nodiscard]] CRect GetRotatedRect() const {
        return m_rectRotated;
    }

    void DrawBevelLine(const BOOL bDraw) {
        m_bDrawBevelLine = bDraw;
    }

    void SetBackgroundColor(const COLORREF clr) {
        m_clrBackground = clr;
    }

    void SetDisabledText(const BOOL bDisable) {
        m_bDisabled = bDisable;
    }

    void SetHorzAlignment(const UINT uiHorzAlignment = DT_LEFT) {
        m_uiHorzAlignment = uiHorzAlignment;
    }

    void SetText(const LPCTSTR lpszText) {
        m_strText = lpszText;
    }

    void SetTextColor(const COLORREF clr) {
        m_clrText = clr;
    }

    void SetVertAlignment(const UINT uiVertAlignment = 0) {
        m_uiVertAlignment = uiVertAlignment;
    }
};

/////////////////////////////////////////////////////////////////////////////
// CNewLabel window

class CNewLabel : public CStatic {
public :
    enum {
        HORZ_LEFT = 0x01,
        HORZ_CENTER = 0x02,
        HORZ_RIGHT = 0x04,
        VERT_TOP = 0x08,
        VERT_CENTER = 0x10,
        VERT_BOTTOM = 0x20
    };

protected :
    COLORREF m_clrBackColor;
    COLORREF m_clrTextBackColor;
    COLORREF m_clrTextColor;
    COLORREF m_clrHightLight;
    COLORREF m_clrSaveTextColor;
    HBRUSH m_hBackBrush;
    BOOL m_bForceNoOwnerDraw;
    BOOL m_bUseDefaultBackColor;
    BOOL m_bUseDefaultTextBackColor;
    BOOL m_bUseDefaultTextColor;
    BOOL m_bLink;
    BOOL m_bUseBevelLine;
    BOOL m_bUseHighLighting;
    BOOL m_bVerticalText;
    BOOL m_bInside;
    BOOL m_bTextFlash;
    BOOL m_bBackFlash;
    BOOL m_bFlashTextState;
    BOOL m_bFlashBackState;
    BOOL m_bUseToolTip;
    BOOL m_bUseHighLightingOnlyWithToolTip;
    BOOL m_bBlockMessage;
    BOOL m_bLowerCase;
    BOOL m_bUpperCase;
    BOOL m_bStretchBitmap;
    LOGFONT m_stLF{};
    CFont m_cFont;
    HCURSOR m_hCursor;
    HBITMAP m_hBackImage;
    UINT m_uiAlignment;
    UINT m_uiAngle;
    CString m_strText;
    CControlToolTip m_cControlToolTip;

    void DrawAlignedText(CDC *pDC, LPCSTR lpszText, RECT stRect, UINT uiAlignment) const;
    int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount);
    void GetWindowText(CString &rString);
    static BOOL IsMultiLineString(LPCSTR lpszText);
    CString MakeVerticalText(LPCSTR lpszText = nullptr) const;
    BOOL ReconstructFont();
    void SetWindowText(LPCTSTR lpszString);
    void TrackMouse(BOOL bHover, BOOL bLeave) const;

public :
    CNewLabel();
    ~CNewLabel() override;

    static BOOL IsWindowsNT2000();

    // Color functions
    CNewLabel &SetBkColor(COLORREF clr = GetSysColor(COLOR_3DFACE));
    CNewLabel &SetDefaultBkColor();
    CNewLabel &SetDefaultTextBackColor();
    CNewLabel &SetDefaultTextColor();
    CNewLabel &SetHighLightColor(COLORREF clr = GetSysColor(COLOR_HIGHLIGHT));
    CNewLabel &SetTextBackColor(COLORREF clr = GetSysColor(COLOR_3DFACE));
    CNewLabel &SetTextColor(COLORREF clr = GetSysColor(COLOR_WINDOWTEXT));

    // Font functions
    CNewLabel &SetFontBold(BOOL bBold);
    CNewLabel &SetFontItalic(BOOL bItalic);
    CNewLabel &SetFontName(LPCTSTR szFaceName);
    CNewLabel &SetFontSize(int iSize);
    CNewLabel &SetFontUnderline(BOOL bUnderline);

    // Other functions
    CNewLabel &FlashBackground(BOOL bActivate, UINT uiTime = 500);
    CNewLabel &FlashText(BOOL bActivate, UINT uiTime = 500);

    void ForceNoOwnerDraw(BOOL bForce);

    [[nodiscard]] BOOL GetBorder() const;
    [[nodiscard]] UINT GetHorzAlignment() const;
    [[nodiscard]] UINT GetHorzAlignmentIndex() const;
    [[nodiscard]] BOOL GetSunken() const;
    [[nodiscard]] CString GetText() const;
    [[nodiscard]] UINT GetVertAlignment() const;
    [[nodiscard]] UINT GetVertAlignmentIndex() const;

    CNewLabel &SetAlignment(UINT uiAlign = HORZ_LEFT | VERT_TOP);
    CNewLabel &SetAngle(UINT uiAngle = 0);
    CNewLabel &SetBackImage(UINT nID = -1);
    CNewLabel &SetBorder(BOOL bSet);
    CNewLabel &SetCursor(HCURSOR hCursor);
    CNewLabel &SetCursor(UINT uiCursorID);
    CNewLabel &SetDisabled(BOOL bSet);
    CNewLabel &SetLink(BOOL bSet);
    CNewLabel &SetLinkCursor(HCURSOR hCursor);
    CNewLabel &SetLinkCursor(UINT uiCursorID);
    CNewLabel &SetLowerCase(BOOL bSet);
    CNewLabel &SetText(LPCTSTR szText);
    CNewLabel &SetSunken(BOOL bSet);
    CNewLabel &SetToolTipPosition(int iPosition = 0);
    CNewLabel &SetToolTipText(LPCTSTR lpszText = "");
    CNewLabel &SetUpperCase(BOOL bSet);
    CNewLabel &SetVerticalText(BOOL bSet);
    CNewLabel &ShowToolTipOnlyOnMouseClick(BOOL bUse);
    CNewLabel &StretchBitmap(BOOL bStretch);
    CNewLabel &UseBevelLine(BOOL bUse);
    CNewLabel &UseHighLighting(BOOL bUse);
    CNewLabel &UseHighLightingOnlyWithToolTip(BOOL bUse);
    CNewLabel &UseLeftMouseButtonForToolTip(BOOL bUse);
    CNewLabel &UseToolTip(BOOL bUse);

    // INLINE
    [[nodiscard]] COLORREF GetBkColor() const {
        return m_clrBackColor;
    }

    [[nodiscard]] COLORREF GetHighLightColor() const {
        return m_clrHightLight;
    }

    [[nodiscard]] COLORREF GetTextBackColor() const {
        return m_clrTextBackColor;
    }

    [[nodiscard]] COLORREF GetTextColor() const {
        return m_clrTextColor;
    }

    [[nodiscard]] BOOL IsDefaultBkColor() const {
        return m_bUseDefaultBackColor;
    }

    [[nodiscard]] BOOL IsDefaultTextBackColor() const {
        return m_bUseDefaultTextBackColor;
    }

    [[nodiscard]] BOOL IsDefaultTextColor() const {
        return m_bUseDefaultTextColor;
    }

    [[nodiscard]] BOOL GetFontBold() const {
        return (m_stLF.lfWeight & FW_BOLD) == FW_BOLD ? TRUE : FALSE;
    }

    [[nodiscard]] BOOL GetFontItalic() const {
        return m_stLF.lfItalic;
    }

    [[nodiscard]] CString GetFontName() const {
        return m_stLF.lfFaceName;
    }

    [[nodiscard]] LONG GetFontSize() const {
        return m_stLF.lfHeight;
    }

    [[nodiscard]] BOOL GetFontUnderline() const {
        return m_stLF.lfUnderline;
    }

    [[nodiscard]] UINT GetAlignment() const {
        return m_uiAlignment;
    }

    [[nodiscard]] UINT GetAngle() const {
        return m_uiAngle;
    }

    [[nodiscard]] BOOL GetBevelLine() const {
        return m_bUseBevelLine;
    }

    [[nodiscard]] BOOL GetLink() const {
        return m_bLink;
    }

    [[nodiscard]] BOOL GetVerticalText() const {
        return m_bVerticalText;
    }

    [[nodiscard]] BOOL IsBitmapStretched() const {
        return m_bStretchBitmap;
    }

    [[nodiscard]] BOOL IsDisabled() const {
        return (GetStyle() & WS_DISABLED) == WS_DISABLED;
    }

    [[nodiscard]] BOOL IsLowerCase() const {
        return m_bLowerCase;
    }

    [[nodiscard]] BOOL IsToolTipUsed() const {
        return m_bUseToolTip;
    }

    [[nodiscard]] BOOL IsUpperCase() const {
        return m_bUpperCase;
    }

    [[nodiscard]] BOOL UseHighLightingOnlyWithToolTip() const {
        return m_bUseHighLightingOnlyWithToolTip;
    }

    [[nodiscard]] BOOL UseToolTipOnLeftMouseClick() const {
        return m_cControlToolTip.IsLeftMouseButtonUsed();
    }

    [[nodiscard]] BOOL UseToolTipWithMouseClick() const {
        return m_cControlToolTip.ShowOnlyOnMouseClickDown();
    }

public :
    //{{AFX_VIRTUAL(CNewLabel)
public:
    BOOL DestroyWindow() override;
protected:
    void PreSubclassWindow() override;
    LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
    //}}AFX_VIRTUAL

protected :
    //{{AFX_MSG(CNewLabel)
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg HBRUSH CtlColor(CDC *pDC, UINT nCtlColor);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG

DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWLABEL_H__50B040A0_5E0B_11D4_BC43_0050BAA38233__INCLUDED_)
