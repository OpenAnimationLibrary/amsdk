#ifndef AFX_PDIALOG_H__8A6FD58A_636A_4299_B77A_E47EE18B9EE9__INCLUDED_
#define AFX_PDIALOG_H__8A6FD58A_636A_4299_B77A_E47EE18B9EE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//
//#ifndef __SPLITPATCHDIALOG_H
//#define __SPLITPATCHDIALOG_H

#include "Splitpatch.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPDialog 

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    Parameter *m_parameters{};
    PDialog() = default;
    PDialog(Parameter *parameters);

    // Dialogfelddaten
    //{{AFX_DATA(CPDialog)
    enum { IDD = IDD_DIALOG2 };

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
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    BOOL OnInitDialog() override;
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.
//#endif SPLITPATCHDIALOG_H

#endif // AFX_PDIALOG_H__8A6FD58A_636A_4299_B77A_E47EE18B9EE9__INCLUDED_
