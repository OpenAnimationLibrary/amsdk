#pragma once

// MDialog-Dialogfeld

class MDialog final : public CPluginDialog {

public:
    explicit MDialog(CWnd *pParent = nullptr); // Standardkonstruktor
    ~MDialog() override;
    static void Cleanup();
    void EnableControls(bool check) const;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung

DECLARE_MESSAGE_MAP()
protected:
    void OnOK() override;
    void OnCancel() override;

public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    BOOL OnInitDialog() override;
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck4();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedButton3();
};
