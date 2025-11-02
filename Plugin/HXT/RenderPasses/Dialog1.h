#if !defined(AFX_DIALOG1_H__77209FF3_D707_42CC_8A07_B9D0880986B1__INCLUDED_)
#define AFX_DIALOG1_H__77209FF3_D707_42CC_8A07_B9D0880986B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog1.h : Header-Datei
//
#include "RenderPasses.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dialog1 

class Dialog1 final : public CDialog {
    // Konstruktion
public:
    int option{};
    PARAMETER *m_para{};
    Dialog1() = default;
    explicit Dialog1(PARAMETER *para);

    // Dialogfelddaten
    //{{AFX_DATA(Dialog1)
    enum { IDD = IDD_DIALOG1 };

    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(Dialog1)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(Dialog1)
    void OnOK() override;
    void OnCancel() override;
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnRadio5();
    BOOL OnInitDialog() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOG1_H__77209FF3_D707_42CC_8A07_B9D0880986B1__INCLUDED_
