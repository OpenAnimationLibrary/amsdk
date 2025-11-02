#if !defined(AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_)
#define AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PDialog.h : Header-Datei
//
#include "mlistctl.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PDialog 

class PDialog final : public CPluginDialog {
    // Konstruktion
public:
    int sd_x{}, sd_y{};
    float pix_unit{};
    int height{};
    int width{};
    int offsetx{};
    int offsety{};
    int nummodel{};
    int maxmodel{};
    PParameter *m_para{};
    PDialog() = default;
    PDialog(PParameter *parameters);
    void UpdateListbox();
    void CalculateGrid();

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG1 };

    CMyListCtrl m_listctrl;
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
    afx_msg void OnButton1();
    afx_msg void OnButton2();
    afx_msg void OnEnKillfocusEdit1();
    afx_msg void OnEnKillfocusEdit2();
    afx_msg void OnEnKillfocusEdit3();
    afx_msg void OnEnKillfocusEdit4();
    afx_msg void OnEnKillfocusEdit5();
    afx_msg void OnEnKillfocusEdit8();
    afx_msg void OnEnKillfocusEdit9();
    afx_msg void OnEnKillfocusEdit10();
    afx_msg void OnEnKillfocusEdit11();
    afx_msg void OnEnKillfocusEdit6();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnAddEntry();
    afx_msg void OnRemoveEntry();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__6846B95C_AD41_44C0_82D9_CCD1212D314E__INCLUDED_
