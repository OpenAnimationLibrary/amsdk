#if !defined(AFX_PDIALOG_H__8B5FEDED_28B1_4F25_B32D_6274F602FDE7__INCLUDED_)
#define AFX_PDIALOG_H__8B5FEDED_28B1_4F25_B32D_6274F602FDE7__INCLUDED_

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
    PARAMETER *m_para{};
    PDialog() = default;
    PDialog(PARAMETER *parameter);
    void UpdateDialog() const;

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
    BOOL OnInitDialog() override;
    void OnOK() override;
    afx_msg void OnCheck1();
    afx_msg void OnCheck2();
    afx_msg void OnCheck3();
    afx_msg void OnCheck4();
    afx_msg void OnCheck5();
    afx_msg void OnCheck6();
    afx_msg void OnCheck7();
    afx_msg void OnCheck8();
    afx_msg void OnCheck10();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__8B5FEDED_28B1_4F25_B32D_6274F602FDE7__INCLUDED_
