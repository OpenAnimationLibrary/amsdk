#if !defined(AFX_ExportChorDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
#define AFX_ExportChorDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_

#pragma once

#include "StrClass.h"

// ExportChorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportChorDialog dialog

class CExportChorDialog final : public CPluginDialog {
    // Construction
public:
    CExportChorDialog(): m_iemp{nullptr},
                         m_hasactionobjects{0},
                         m_exportscale{0},
                         m_maxsize{0},
                         m_minsize{0},
                         m_subtype{0},
                         m_exportmethod{0},
                         m_generatemodelmaps{0},
                         m_applybump{0},
                         m_btriangles{0},
                         m_allframes{0},
                         m_rebuildnormals{0},
                         m_discardfaces{0},
                         m_exportnormals{0} {}

    // standard constructor
    explicit CExportChorDialog(const String &filename);

    void FillCombo(int id) const;

    // Dialog Data
    IEModelParms *m_iemp;
    String m_filename;
    BOOL m_hasactionobjects;

    //{{AFX_DATA(CExportChorDialog)
    enum { IDD = IDD_EXPORTCHORDIALOG };

    float m_exportscale;
    int m_maxsize;
    int m_minsize;
    int m_subtype;
    int m_exportmethod;
    BOOL m_generatemodelmaps;
    BOOL m_applybump;
    BOOL m_btriangles;
    BOOL m_allframes;
    BOOL m_rebuildnormals;
    BOOL m_discardfaces;
    BOOL m_exportnormals;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExportChorDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CExportChorDialog)
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

#endif // !defined(AFX_ExportChorDIALOG_H__58C09836_D8D2_11D3_83A5_00E0811049D9__INCLUDED_)
