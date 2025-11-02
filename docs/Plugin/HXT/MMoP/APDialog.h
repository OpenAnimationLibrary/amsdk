#pragma once

// APDialog-Dialogfeld

class APDialog final : public CPluginDialog {
DECLARE_DYNAMIC(APDialog)
    PParameter *mp = nullptr;

    APDialog() = default;
    APDialog(PParameter *para);
    ~APDialog() override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG3 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    BOOL OnInitDialog() override;
    void OnOK() override;

DECLARE_MESSAGE_MAP()
};
