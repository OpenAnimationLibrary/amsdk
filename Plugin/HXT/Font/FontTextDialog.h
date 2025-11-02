#pragma once
#ifndef __FONTTEXTDIALOG_H
#define __FONTTEXTDIALOG_H

#include "Hxt.h"
#include "SDK/Misc.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CFontTextDialog dialog

class CFontTextDialog final : public CPluginDialog {
    // Construction
public:
    FontParameters *m_parameters;
    CFont m_dispfont;

    CFontTextDialog(): m_parameters{nullptr} {} // standard constructor
    explicit CFontTextDialog(FontParameters *parameters);

    [[nodiscard]] CRect PreviewRect() const;
    void UpdateSample();

    // Dialog Data
    //{{AFX_DATA(CFontTextDialog)
    enum { IDD = IDD_FONT };

    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CFontTextDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CFontTextDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    afx_msg void OnSelchangeFontlist();
    afx_msg void OnChangeFonttext();
    afx_msg void OnPaint();
    afx_msg void OnSelchangeFontstyle();
    afx_msg void OnBevelBacks();
    afx_msg void OnBevelFronts();
    afx_msg void OnBevelSides();
    afx_msg void OnBacks();
    afx_msg void OnFronts();
    afx_msg void OnSides();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#endif //FONTTEXTDIALOG_H
