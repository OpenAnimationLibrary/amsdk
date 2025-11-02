#pragma once

// PDialog-Dialogfeld

class PDialog final : public CPluginDialog {
public:
    PDialog() = default;
    explicit PDialog(MC_PARAMETER *para);
    ~PDialog() override;
    MC_PARAMETER *mp{};

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    BOOL OnInitDialog() override;
    void OnOK() override;

DECLARE_MESSAGE_MAP()
};
