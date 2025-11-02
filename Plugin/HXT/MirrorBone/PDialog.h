#pragma once

// PDialog-Dialogfeld

class PDialog final : public CPluginDialog {

public:
    Parameter *m_para{};
    PDialog() = default;
    ~PDialog() override;
    PDialog(Parameter *parameters);
    BOOL OnInitDialog() override;
    void SetViewing() const;

    // Dialogfelddaten
    enum {
        IDD = IDD_DIALOG1
    };

    //{{AFX_VIRTUAL(PDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

public:
    //{{AFX_MSG(PDialog)
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck6();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnBnClickedButton1();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
