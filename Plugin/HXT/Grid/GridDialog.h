// KB  10/3/00  \Ken90\Plugin\Grids\Grid\GridDialog.h
#pragma once

#ifndef __GRIDDIALOG_H
#define __GRIDDIALOG_H
// GridDialog.h : header file
//
#include "Hxt.h"
#include "SDK/Misc.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGridDialog dialog

class CGridDialog final : public CPluginDialog {
    // Construction
public:
    GridParameters *m_parameters{};

    CGridDialog() = default; // standard constructor
    explicit CGridDialog(GridParameters *parameters);

    // Dialog Data
    //{{AFX_DATA(CGridDialog)
    enum { IDD = IDD_GRID };

    float m_height{};
    float m_stepheight{};
    float m_stepwidth{};
    float m_width{};
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGridDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CGridDialog)
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
#endif //GRIDDIALOG_H
