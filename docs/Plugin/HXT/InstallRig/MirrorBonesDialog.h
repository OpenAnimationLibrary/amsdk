#if !defined(AFX_MirrorBonesDialog_H__92BBE998_909B_4B9D_B08C_21CEF4F4CF7C__INCLUDED_)
#define AFX_MirrorBonesDialog_H__92BBE998_909B_4B9D_B08C_21CEF4F4CF7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MirrorBonesDialog.h : header file
//
#include "resource.h"
#include "StrClass.h"
/////////////////////////////////////////////////////////////////////////////
// MirrorBonesDialog dialog

class MirrorBonesDialog final : public CDialog {
    // Construction
public:
    explicit MirrorBonesDialog(CWnd *pParent = nullptr); // standard constructor

    // Dialog Data
    //{{AFX_DATA(MirrorBonesDialog)
    enum { IDD = IDD_MIRRORBONES_DIALOG };

    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MirrorBonesDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(MirrorBonesDialog)
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()

public:
    int m_adjustright;
    int m_assignvertices;
    int m_createbones;
    float m_tolerance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MirrorBonesDialog_H__92BBE998_909B_4B9D_B08C_21CEF4F4CF7C__INCLUDED_)
