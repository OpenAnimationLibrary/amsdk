#if !defined(AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_)
#define AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
// PDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PDialog 

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    HChor *m_chor{};
    BOOL calculate_weight{};
    BOOL anisotropic{};
    float weight{};
    float density{};
    float bounce{};
    float friction{};
    float spinningfriction{};
    float rollingfriction{};
    float lindamp{};
    float angdamp{};
    float margin{};
    int hulltype{};

    PDialog() noexcept = default;
    explicit PDialog(HChor *chor);

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG1 };

    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(PDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:
    CToolTipCtrl m_ToolTip;
    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(PDialog)
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedCheck1();
    BOOL PreTranslateMessage(MSG *pMsg) override;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_
