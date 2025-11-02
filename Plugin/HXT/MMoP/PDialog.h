#pragma once

class PDialog final : public CPluginDialog {
DECLARE_DYNAMIC(PDialog)
    PParameter *mp = nullptr;

    PDialog() = default;
    PDialog(PParameter *para);
    ~PDialog() override;
    void UpdateSettings();

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //{{AFX_MSG(PDialog)
    BOOL OnInitDialog() override;
    void OnOK() override;
    afx_msg void OnSelchangeList1();
    afx_msg void OnUpdateEdit1();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
};
