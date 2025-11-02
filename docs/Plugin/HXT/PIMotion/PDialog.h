#if !defined(AFX_PDIALOG_H__3DB052CE_473E_4E74_84A3_141A71326C87__INCLUDED_)
#define AFX_PDIALOG_H__3DB052CE_473E_4E74_84A3_141A71326C87__INCLUDED_

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
    PParameters *para;
    PDialog(PParameters *m_para);
    void UpdateKamera();
    void UpdateObject();
    void GetPropCamera(HHashObject *obj) const;
    BOOL GetPropRecurseCamera(HProperty *akt_prop) const;
    static BOOL GetBoneRecurse(HBone *hb, CComboBox *id);
    static BOOL GetBoneSibling(HBone *hb, CComboBox *id, int &recurse);

    // Dialogfelddaten
    //{{AFX_DATA(PDialog)
    enum { IDD = IDD_DIALOG1 };

    int m_height;
    int m_width;
    float m_start;
    float m_end;
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
    afx_msg void OnSelchangeCombo1();
    afx_msg void OnSelchangeCombo2();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnSelchangeCombo3();
    afx_msg void OnSelchangeCombo4();
    afx_msg void OnButton1();
    afx_msg void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PDIALOG_H__3DB052CE_473E_4E74_84A3_141A71326C87__INCLUDED_
