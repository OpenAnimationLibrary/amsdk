#pragma once

#include "Amplitude.h"

// BandDlg-Dialogfeld

class BandDlg final : public CPluginDialog {
public:
    BandDlg() noexcept = default;
    explicit BandDlg(int samplefreq);
    //	BandDlg(CWnd* pParent = NULL);   // Standardkonstruktor
    ~BandDlg() override;

    int low{0};
    int high{0};
    int _samplefreq{0};

    // Dialogfelddaten
    enum {
        IDD = IDD_DIALOG2
    };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    BOOL OnInitDialog() override;
    void OnOK() override;

DECLARE_MESSAGE_MAP()
};
