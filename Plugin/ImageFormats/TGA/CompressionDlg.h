// KB  01/19/2005  \Plugin\Image Formats\TGA\CompressionDlg.h
#pragma once
#include "afxwin.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CCompressionDlg dialog

class CCompressionDlg final : public CPluginDialog {
    DECLARE_DYNAMIC(CCompressionDlg)

    // Construction
    CCompressionDlg(CWnd *pParent = nullptr); // standard constructor

    // Dialog Data
    //{{AFX_DATA(CCompressionDlg)
    enum { IDD = IDD_COMPRESSION };

    BOOL m_compression;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCompressionDlg)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation

    // Generated message map functions
    //{{AFX_MSG(CCompressionDlg)
    // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
