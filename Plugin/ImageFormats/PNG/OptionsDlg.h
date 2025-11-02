#pragma once
#include "afxwin.h"
#include "SDK/Misc.h"

// OptionsDlg dialog

class OptionsDlg final : public CPluginDialog {
    DECLARE_DYNAMIC(OptionsDlg)

    int m_interlaced;
    int m_8bit;
    int m_compression;

    OptionsDlg(CWnd *pParent = nullptr); // standard constructor
    ~OptionsDlg() override;

    OptionsDlg(const OptionsDlg &) = delete;
    OptionsDlg &operator=(const OptionsDlg &) = delete;
    OptionsDlg(OptionsDlg &&) = delete;
    OptionsDlg &operator=(OptionsDlg &&) = delete;

    // Dialog Data
    enum { IDD = IDD_COMPRESSION };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    BOOL OnInitDialog() override;
    void OnOK() override;

    DECLARE_MESSAGE_MAP()
};
