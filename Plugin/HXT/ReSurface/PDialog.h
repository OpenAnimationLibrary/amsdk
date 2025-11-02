#pragma once
#include  "ReSurface.h"

// PDialog-Dialogfeld
class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    PARAMETER *para;
    PDialog(PARAMETER *m_para);
//    PDialog(CWnd *pParent = nullptr); // Standardkonstruktor
    ~PDialog() override;

    // Dialogfelddaten
    enum { IDD = IDD_DIALOG1 };

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    BOOL OnInitDialog() override;

    DECLARE_MESSAGE_MAP()
};
