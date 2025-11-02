#if !defined(AFX_EXPORTMODELSDIALOG_H__58C09837_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_EXPORTMODELSDIALOG_H__58C09837_D8D2_11D3_83A5_00E0811049D9__INCLUDED_

#pragma once
// ExportModelsDialog.h : header file
//
#include <afxtempl.h>
#include "StrClass.h"

/////////////////////////////////////////////////////////////////////////////
// CExportModelsDialog dialog

class HModelCache;
class HObjectCacheContainer;

class CExportModelsDialog final : public CPluginDialog {
    // Construction
public:
    CExportModelsDialog(): m_maxsize{0}, m_minsize{0}, m_subtype{0}, m_exportscale{0}, m_generatemodelmaps{0}, m_btriangles{0}, m_applybump{0}, m_discardfaces{0}, m_exportnormals{0} {}
    // standard constructor
    explicit CExportModelsDialog(HObjectCacheContainer *hocc);

    void FillCombo(int id) const;

    // Dialog Data
    IEModelParms *m_iemp = nullptr;
    HObjectCacheContainer *m_hocc = nullptr;
    CCheckListBox m_checklistbox;
    CList<HModelCache *, HModelCache *> m_selected;
    String m_dir;

    //{{AFX_DATA(CExportModelsDialog)
    enum {
        IDD = IDD_EXPORTMODELSDIALOG
    };

    int m_maxsize;
    int m_minsize;
    int m_subtype;
    float m_exportscale;
    BOOL m_generatemodelmaps;
    BOOL m_btriangles;
    BOOL m_applybump;
    BOOL m_discardfaces;
    BOOL m_exportnormals;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExportModelsDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CExportModelsDialog)
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

#endif // !defined(AFX_EXPORTMODELSDIALOG_H__58C09837_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
