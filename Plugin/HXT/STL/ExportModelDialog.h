#if !defined(AFX_EXPORTMODELDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_EXPORTMODELDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __STRCLASS_H
#include "StrClass.h"
#endif
// ExportModelDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportModelDialog dialog

class CExportModelDialog final : public CDialog {
    // Construction
public:
    String m_filename;
    BOOL m_applybump{FALSE};
    BOOL m_binary{FALSE};
    int m_subtype{0};

    CExportModelDialog() = default;
    // standard constructor
    explicit CExportModelDialog(const String &filename);

    //{{AFX_DATA(CExportModelDialog)
    enum { IDD = IDD_EXPORTMODELDIALOG };

    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExportModelDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
    // Generated message map functions
    //{{AFX_MSG(CExportModelDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    afx_msg void OnBrowse();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTMODELDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
