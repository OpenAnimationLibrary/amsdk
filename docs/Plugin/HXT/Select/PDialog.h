#if !defined(AFX_PDIALOG_H__8F96BFEF_17E6_4938_B7D9_64BA634FC702__INCLUDED_)
#define AFX_PDIALOG_H__8F96BFEF_17E6_4938_B7D9_64BA634FC702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPDialog 

class CPDialog final : public CPluginDialog
//class CPDialog : public CDialog
{
    // Konstruktion
public:
    Parameter *m_para{};
    CPDialog() = default;
    CPDialog(Parameter *parameters);
    void Init() const;

    // Dialogfelddaten
    //{{AFX_DATA(CPDialog)
    enum { IDD = IDD_DIALOG1 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(CPDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:
    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(CPDialog)
    BOOL OnInitDialog() override;
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnRadio5();
    afx_msg void OnRadio6();
    afx_msg void OnRadio7();
    afx_msg void OnRadio8();
    afx_msg void OnRadio9();
    afx_msg void OnCbnSelchangeCombo1();
    afx_msg void OnEnKillfocusEdit7();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__8F96BFEF_17E6_4938_B7D9_64BA634FC702__INCLUDED_
