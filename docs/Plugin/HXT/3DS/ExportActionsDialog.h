#if !defined(AFX_EXPORTACTIONSDIALOG_H__98884FB3_DA64_11D3_83A6_00E0811049D9__INCLUDED_)
#define AFX_EXPORTACTIONSDIALOG_H__98884FB3_DA64_11D3_83A6_00E0811049D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportActionsDialog.h : header file
//
//#include <AfxTempl.h>
#ifndef __STRCLASS_H
#include "StrClass.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportActionsDialog dialog

class CExportActionsDialog final : public CPluginDialog {
    // Construction
public:
    CExportActionsDialog() noexcept = default; // standard constructor
    explicit CExportActionsDialog(HActionCacheContainer *hacc); // standard constructor

    void FillCombo(int id) const;

    // Dialog Data
    IEModelParms *m_iemp{nullptr};
    HActionCacheContainer *m_hacc{};
    String m_dir;
    CCheckListBox m_checklistbox;
    CList<HActionCache *, HActionCache *> m_selected;

    //{{AFX_DATA(CExportActionsDialog)
    enum { IDD = IDD_EXPORTMODELS_DIALOG };

    BOOL m_generatemodelmaps{};
    BOOL m_applybump{};
    int m_maxsize{};
    int m_minsize{};
    int m_subtype{};
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExportActionsDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CExportActionsDialog)
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

#endif // !defined(AFX_EXPORTACTIONSDIALOG_H__98884FB3_DA64_11D3_83A6_00E0811049D9__INCLUDED_)
