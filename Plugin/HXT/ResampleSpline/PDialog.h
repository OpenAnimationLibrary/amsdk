#pragma once
#include  "ResampleSpline.h"

// PDialog-Dialogfeld
class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    PARAMETER *para = nullptr;
    BOOL z_unsed;
    PDialog(PARAMETER *m_para);
//    PDialog(CWnd *pParent = nullptr); // Standardkonstruktor
    ~PDialog() override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterst³tzung
    BOOL OnInitDialog() override;
    void OnOK() override;

DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnKillfocusEdit2();
    afx_msg void OnEnKillfocusEdit1();
};
