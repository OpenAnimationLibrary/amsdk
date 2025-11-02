#pragma once

#include "afxtempl.h"
#include "StrClass.h"
#include "SDK/Misc.h"

class HActionCache;
class HActionCacheContainer;

class CExportActionsDialog final : public CPluginDialog {
    // Construction
public:
    ~CExportActionsDialog() override;
    CExportActionsDialog() noexcept = default; // standard constructor
    explicit CExportActionsDialog(HActionCacheContainer *hacc);

    enum { IDD = IDD_EXPORTACTIONS };

    CCheckListBox m_checklistbox;

    CList<HActionCache *, HActionCache *> m_selected;
    HActionCacheContainer *m_hacc{};
    String m_dir;
    BOOL m_ispadmotion{};
    BOOL m_nomotion{};
    int m_exportstate{};
    float m_errortolerance{};

protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support

    // Implementation
protected:
    BOOL OnInitDialog() override;
    void OnOK() override;
    afx_msg void OnBrowse();
DECLARE_MESSAGE_MAP()
};
