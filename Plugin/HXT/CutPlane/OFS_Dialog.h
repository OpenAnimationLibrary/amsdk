#pragma once

// OFS_Dialog-Dialogfeld

class OFS_Dialog final : public CPluginDialog {

public:
    OFS_Dialog(CWnd *pParent = nullptr); // Standardkonstruktor
    ~OFS_Dialog() override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG2 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung

DECLARE_MESSAGE_MAP()
};
