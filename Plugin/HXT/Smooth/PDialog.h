#if !defined(AFX_PDIALOG_H__090A78F9_597D_47C7_95DA_20AB38CF827A__INCLUDED_)
#define AFX_PDIALOG_H__090A78F9_597D_47C7_95DA_20AB38CF827A__INCLUDED_

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
    PDialog(PARAMETER *parameters);

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG2 };

    int m_cp{};
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
    afx_msg void OnCheck1();
    afx_msg void OnCheck2();
    afx_msg void OnCheck3();
    afx_msg void OnCheck4();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    BOOL OnInitDialog() override;
    afx_msg void OnCheck5();
    afx_msg void OnCheck6();
    afx_msg void OnCheck7();
    void OnOK() override;
    afx_msg void OnRadio4();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__090A78F9_597D_47C7_95DA_20AB38CF827A__INCLUDED_
