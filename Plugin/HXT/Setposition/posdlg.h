#if !defined(AFX_POS_H__B3111D8A_1846_43BE_BB76_B45FE0472FF1__INCLUDED_)
#define AFX_POS_H__B3111D8A_1846_43BE_BB76_B45FE0472FF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// posdlg.h : Header-Datei
//
#include "Setposition.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld pos 

class posdlg final : public CPluginDialog {
    // Konstruktion
public:
    PParameters *m_parameters;
    posdlg(PParameters *parameters); // Standardkonstruktor
    void update_dlg() const;

    // Dialogfelddaten
    //{{AFX_DATA(posdlg)
    enum { IDD = IDD_DIALOG1 };

    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(posdlg)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:
    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(posdlg)
    BOOL OnInitDialog() override;
    afx_msg void OnButton1();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnCheck4();
    afx_msg void OnCheck5();
    afx_msg void OnCheck6();
    afx_msg void OnCheck1();
    afx_msg void OnCheck2();
    afx_msg void OnCheck3();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_POS_H__B3111D8A_1846_43BE_BB76_B45FE0472FF1__INCLUDED_
