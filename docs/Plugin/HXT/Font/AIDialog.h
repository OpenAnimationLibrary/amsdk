#if !defined(AFX_AIDIALOG_H__6D742C11_0C25_11D5_97D6_00A0C9E016B4__INCLUDED_)
#define AFX_AIDIALOG_H__6D742C11_0C25_11D5_97D6_00A0C9E016B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AIDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAIDialog dialog

class CAIDialog final : public CPluginDialog {
    FontParameters *m_parameters{};

// Construction
public:
    CAIDialog() = default;   // standard constructor
    CAIDialog(FontParameters *parameters);

// Dialog Data
    //{{AFX_DATA(CAIDialog)
    enum { IDD = IDD_AI };

    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAIDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override;    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CAIDialog)
    afx_msg void OnBrowseAi();
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIDIALOG_H__6D742C11_0C25_11D5_97D6_00A0C9E016B4__INCLUDED_)
