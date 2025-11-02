#pragma once
#include "resource.h"

// PDialog-Dialogfeld

class PDialog final : public CPluginDialog {
public:
    PDialog(): mp{nullptr} {}
    explicit PDialog(PARAMETER *para);
    ~PDialog() override;
    void UpdateControls();

    PARAMETER *mp;

    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG1 };

    //}}AFX_DATA

    //{{AFX_VIRTUAL(PDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterst³tzung
    //}}AFX_VIRTUAL

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(PDialog)
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedRadio4();
};
