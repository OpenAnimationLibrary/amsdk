//
#pragma once
#include "StrClass.h"
#include "SDK/Misc.h"

class HActionCache;

class CExportActionDialog final : public CPluginDialog {
DECLARE_DYNAMIC(CExportActionDialog)
    float m_errortolerance;
    String m_filename;
    BOOL m_ispadmotion;
    BOOL m_nomotion;
    int m_exportstate;
public:
explicit CExportActionDialog(HActionCache *hac);
private:
    BOOL OnInitDialog() override;
    void OnOK() override;
    void DoDataExchange(CDataExchange *pDX) override;
    afx_msg void OnBrowse();
DECLARE_MESSAGE_MAP()
};
