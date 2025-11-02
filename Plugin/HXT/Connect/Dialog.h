#if !defined(AFX_DIALOG_H__CE9FEA50_0249_4AF8_9BA2_FEC9A4969B53__INCLUDED_)
#define AFX_DIALOG_H__CE9FEA50_0249_4AF8_9BA2_FEC9A4969B53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog.h : Header-Datei
//
#include "resource.h"
#include "Connect.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dialog 

class Dialog final : public CPluginDialog {
    // Konstruktion
public:
    Dialog() noexcept = default;
    explicit Dialog(PARA *para);
    PARA *m_para{};

    //	Dialog(CWnd* pParent = nullptr);   // Standardkonstruktor

    // Dialogfelddaten
    //{{AFX_DATA(Dialog)
    enum { IDD = IDD_DIALOG1 };

    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(Dialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(Dialog)
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOG_H__CE9FEA50_0249_4AF8_9BA2_FEC9A4969B53__INCLUDED_
