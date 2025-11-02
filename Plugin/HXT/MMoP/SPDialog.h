#pragma once

// SPDialog-Dialogfeld

class SPDialog final : public CPluginDialog {
DECLARE_DYNAMIC(SPDialog)
    PParameter *mp = nullptr;

    SPDialog() = default;
    SPDialog(PParameter *para);
    ~SPDialog() override;
    void UpdatePoses() const;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG2 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    BOOL OnInitDialog() override;
    void OnOK() override;

DECLARE_MESSAGE_MAP()
};
