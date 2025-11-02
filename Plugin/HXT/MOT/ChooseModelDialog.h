#if !defined(AFX_CHOOSEMODELDIALOG_H__CD4BCDF1_DF19_11D3_83AD_00E0811049D9__INCLUDED_)
#define AFX_CHOOSEMODELDIALOG_H__CD4BCDF1_DF19_11D3_83AD_00E0811049D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseModelDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseModelDialog dialog

class HObjectCacheContainer;
class HModelCache;

class CChooseModelDialog final : public CPluginDialog {
    // Construction
public:
    HObjectCacheContainer *m_hocc{};
    HModelCache *m_hmc{};
    String m_actioncachename;
    BOOL m_bMultipleActions{};

    CChooseModelDialog() = default; // standard constructor
    CChooseModelDialog(HObjectCacheContainer *hocc, const String &actioncachename, HModelCache *hmc, BOOL bMultipleActions);

    // Dialog Data
    //{{AFX_DATA(CChooseModelDialog)
    enum { IDD = IDD_CHOOSEMODEL };

    BOOL m_bUseForAllActions{};
    float m_fErrorTol{};
    float m_fFps{};
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChooseModelDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CChooseModelDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    afx_msg void OnSelchangeModellistCombo();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEMODELDIALOG_H__CD4BCDF1_DF19_11D3_83AD_00E0811049D9__INCLUDED_)
