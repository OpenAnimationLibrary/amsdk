#pragma once
#include "resource.h"

// ADialog dialog

class ADialog final : public CPluginDialog {
public:
    ADialog(): mp{nullptr} {}
    explicit ADialog(PARAMETER *para);
    ~ADialog() override;
    PARAMETER *mp;

    // Dialog Data
    enum { IDD = IDD_DIALOG2 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support

DECLARE_MESSAGE_MAP()
};
