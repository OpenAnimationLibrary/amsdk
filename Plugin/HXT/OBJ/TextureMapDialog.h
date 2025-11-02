#if !defined(AFX_TEXTUREMAPDIALOG_H__DC63F492_5816_11D4_841D_00E0811049D9__INCLUDED_)
#define AFX_TEXTUREMAPDIALOG_H__DC63F492_5816_11D4_841D_00E0811049D9__INCLUDED_

#pragma once
// TextureMapDialog.h : header file
//

class CHxtApp;
class IEPolyModel;

/////////////////////////////////////////////////////////////////////////////
// CTextureMapDialog dialog

class CTextureMapDialog final : public CPluginDialog {
    // Construction
public:
    CTextureMapDialog(CHxtApp *app, IEPolyModel *model); // standard constructor
    CHxtApp *m_app;
    IEPolyModel *m_model;
    BOOL m_copymaps;

    // Dialog Data
    //{{AFX_DATA(CTextureMapDialog)
    enum { IDD = IDD_TEXTUREMAP_DIALOG };

    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTextureMapDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    void MakeUnique(String &filename, int count = 1) const;

    // Generated message map functions
    //{{AFX_MSG(CTextureMapDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    afx_msg void OnCopyMapsYes();
    afx_msg void OnCopyMapsNo();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTUREMAPDIALOG_H__DC63F492_5816_11D4_841D_00E0811049D9__INCLUDED_)
