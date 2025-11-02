#if !defined(AFX_EXPORTMODELDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_EXPORTMODELDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_

#pragma once

#include "StrClass.h"

// ExportModelDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportModelDialog dialog

class CExportModelDialog final : public CPluginDialog {
    // Construction
public:
    CExportModelDialog(): m_iemp{nullptr}, m_exportscale{0}, m_maxsize{0}, m_minsize{0}, m_subtype{0}, m_generatemodelmaps{0}, m_applybump{0}, m_btriangles{0}, m_discardfaces{0}, m_exportnormals{0}, m_visibility{0} {}
    // standard constructor
    explicit CExportModelDialog(const String &filename);

    void FillCombo(int id) const;

    // Dialog Data
    IEModelParms *m_iemp;
    String m_filename;

    //{{AFX_DATA(CExportModelDialog)
    enum { IDD = IDD_EXPORTMODELDIALOG };

    float m_exportscale;
    int m_maxsize;
    int m_minsize;
    int m_subtype;
    BOOL m_generatemodelmaps;
    BOOL m_applybump;
    BOOL m_btriangles;
    BOOL m_discardfaces;
    BOOL m_exportnormals;
    BOOL m_visibility;

    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExportModelDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CExportModelDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    afx_msg void OnBrowse();
    afx_msg void OnMaxSize();
    afx_msg void OnMinSize();
    afx_msg void OnGeneratemodelmaps();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTMODELDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
