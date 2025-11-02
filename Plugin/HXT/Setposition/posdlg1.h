#if !defined(AFX_POSDLG1_H__9F43064C_9ACA_4D67_BA8E_21105E20D4E6__INCLUDED_)
#define AFX_POSDLG1_H__9F43064C_9ACA_4D67_BA8E_21105E20D4E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// posdlg1.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld posdlg1 

class posdlg1 final : public CPluginDialog {
    // Konstruktion
public:
    PParameters *m_parameters;
    posdlg1(PParameters *parameters);

    // Dialogfelddaten
    //{{AFX_DATA(posdlg1)
    enum { IDD = IDD_DIALOG3 };

    // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(posdlg1)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:
    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(posdlg1)
    afx_msg void OnButton1();
    afx_msg void OnCheck1();
    afx_msg void OnCheck2();
    BOOL OnInitDialog() override;
    void OnOK() override;
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_POSDLG1_H__9F43064C_9ACA_4D67_BA8E_21105E20D4E6__INCLUDED_
