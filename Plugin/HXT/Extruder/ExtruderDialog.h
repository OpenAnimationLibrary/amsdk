#if !defined(AFX_PAVERDIALOG_H__F76B0CF2_B22C_4B0F_B32B_415136F0B816__INCLUDED_)
#define AFX_PAVERDIALOG_H__F76B0CF2_B22C_4B0F_B32B_415136F0B816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDK/Misc.h"

// ExtruderDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtruderDialog dialog

class CExtruderDialog final : public CPluginDialog {
    // Construction
public:
    HModelCache *m_hmodel;
    HGroup *m_hpathgroup, *m_hxsectiongroup;

    explicit CExtruderDialog(HModelCache *hmc, HGroup *hg = nullptr); // standard constructor
    // Dialog Data
    //{{AFX_DATA(CExtruderDialog)
    enum {
        IDD = IDD_PAVER
    };

    CComboBox m_pathgroupcombo;
    CComboBox m_xsectiongroupcombo;
    int m_extrusionmethod;
    int m_extrusioncount;
    float m_extrusiondistance;
    int m_method;
    int m_looped;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CExtruderDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CExtruderDialog)
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnSelchangePathgroupCombo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAVERDIALOG_H__F76B0CF2_B22C_4B0F_B32B_415136F0B816__INCLUDED_)
