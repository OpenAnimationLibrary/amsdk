#pragma once
#include "afxwin.h"
// ImportModelDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog dialog

class CImportModelDialog final : public CPluginDialog {
    // Construction
public:
    SVGParameters *m_parameters;

    CImportModelDialog(): m_parameters{nullptr} {}
    // standard constructor
    explicit CImportModelDialog(SVGParameters *parameters);

    // Dialog Data
    //{{AFX_DATA(CImportModelDialog)
    enum { IDD = IDD_IMPORT_DIALOG };

    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CImportModelDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CImportModelDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnSelchangeCombo1();
};
