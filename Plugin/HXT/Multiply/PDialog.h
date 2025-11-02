#if !defined(AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_)
#define AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PDialog 

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    PParameter *m_para{};
    PDialog() = default;
    PDialog(PParameter *parameters);
    void SetCalculatedExtents(HModel *hm_org);
    void SetCalculatedExtents(HModelCache *hmc);

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

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(PDialog)
    afx_msg void OnSelchangeList1();
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_
