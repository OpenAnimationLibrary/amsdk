#pragma once

// PDialog-Dialogfeld

class PDialog final : public CPluginDialog {
DECLARE_DYNAMIC(PDialog)
    W_PARA *m_para{};
    PDialog() = default;
PDialog(W_PARA *parameters);

    ~PDialog() override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung

DECLARE_MESSAGE_MAP()
};
