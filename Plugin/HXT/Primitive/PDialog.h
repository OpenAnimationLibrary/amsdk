#if !defined(AFX_PDIALOG_H__C7B066F3_570B_4428_A6F6_0613380D392A__INCLUDED_)
#define AFX_PDIALOG_H__C7B066F3_570B_4428_A6F6_0613380D392A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//
#include "primitive.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PDialog 
#define C_BILD 12

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    PParameters *m_parameters;
    PDialog() = default;
    PDialog(PParameters *parameters);
    void CalculatePatch();
    void SetItems(int index);
    HBITMAP aHbmBild[C_BILD]{};

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
    afx_msg void OnSelchangeCombo1();
    afx_msg void OnCheck1();
    afx_msg void OnCheck2();
    void OnOK() override;
    void OnCancel() override;
    BOOL OnInitDialog() override;
    afx_msg void OnUpdateEdit2();
    afx_msg void OnUpdateEdit4();
    afx_msg void OnUpdateEdit8();
    afx_msg void OnUpdateEdit12();
    afx_msg void OnCheck3();
    afx_msg void OnCheck4();
    afx_msg void OnCheck5();
    afx_msg void OnUpdateEdit10();
    afx_msg void OnButton2();
    afx_msg void OnButton3();
    afx_msg void OnKillfocusEdit2();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__C7B066F3_570B_4428_A6F6_0613380D392A__INCLUDED_
