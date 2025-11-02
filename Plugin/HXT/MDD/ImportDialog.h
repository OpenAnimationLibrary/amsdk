#pragma once
#include "afxwin.h"

// ImportDialog dialog

class ImportDialog final : public CPluginDialog {

public:
    ImportDialog() = default;
    ImportDialog(W_PARA *parameters);
    ~ImportDialog() override;

    // Dialog Data
    enum { IDD = IDD_DIALOG2 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support

DECLARE_MESSAGE_MAP()
public:
    W_PARA *m_para{};
    afx_msg void OnClickedButton1();
    void OnOK() override;
    BOOL OnInitDialog() override;
};
