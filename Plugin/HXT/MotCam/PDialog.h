#pragma once

// PDialog-Dialogfeld

class PDialog final : public CPluginDialog {

public:
    PDialog(W_PARA *m_para);
    ~PDialog() override;
    W_PARA *para;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung

DECLARE_MESSAGE_MAP()
public:
    BOOL OnInitDialog() override;
    afx_msg void OnBnClickedButton1();
    afx_msg void OnEnChangeEdit6();
    afx_msg void OnBnClickedOk();
};
