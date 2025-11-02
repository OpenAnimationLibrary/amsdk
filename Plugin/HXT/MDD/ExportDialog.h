#pragma once
#include "afxwin.h"

// ExportDialog dialog

class ExportDialog final : public CPluginDialog {

public:
    ExportDialog() = default;
    ExportDialog(W_PARA *parameters);
    ~ExportDialog() override;

    // Dialog Data
    enum { IDD = IDD_EXPORTDIALOG };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support

DECLARE_MESSAGE_MAP()
public:
    W_PARA *m_para{};
    afx_msg void OnClickedButton1();
    void OnOK() override;
    BOOL OnInitDialog() override;
};
