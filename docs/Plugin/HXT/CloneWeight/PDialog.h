#pragma once

// PDialog-Dialogfeld

class PDialog final : public CPluginDialog {

public:
    Parameter *m_para{};
    PDialog() noexcept = default;
    ~PDialog() override;
    explicit PDialog(Parameter *parameters);
    BOOL OnInitDialog() override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

    //{{AFX_VIRTUAL(PDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    void OnOK() override;
    //}}AFX_VIRTUAL

public:
    //{{AFX_MSG(PDialog)
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
