// Dan  12/27/00  \Dan90\Plugin\HXT\Duplicator\DupDialog.h

#ifndef __DUPDIALOG_H
#define __DUPDIALOG_H
// DupDialog.h : header file
//
#include "SDK/Misc.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDupDialog dialog

class DupParameters;

class CDupDialog final : public CPluginDialog {
    // Construction
public:
    DupParameters *m_parameters{};

    CDupDialog() noexcept = default; // standard constructor
    explicit CDupDialog(DupParameters *parameters);

    // Dialog Data
    //{{AFX_DATA(CDupDialog)
    enum { IDD = IDD_DUP };

    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDupDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CDupDialog)
    void OnOK() override;
    BOOL OnInitDialog() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
#endif //DUPDIALOG_H
