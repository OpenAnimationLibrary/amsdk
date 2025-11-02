#if !defined(AFX_ASSIGN_H__417A9DC8_02FF_48F1_A26B_2BE876B697C2__INCLUDED_)
#define AFX_ASSIGN_H__417A9DC8_02FF_48F1_A26B_2BE876B697C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Assign.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Assign 

class Assign final : public CPluginDialog {
    // Konstruktion
public:
    PARAMETER *m_para{nullptr};
    int zaehler{0};
    double m_min_val{0.};
    double m_max_val{0.};

    Assign() = default;
    explicit Assign(PARAMETER *para);
    void FillLB2();
    void UpdateLB2();
    static void CALLBACK CBMidiOpen(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
    void MidiOpenNotify(HMIDIIN midi_in, UINT msg_type, DWORD midi_msg, DWORD param2);
    static void CALLBACK CBMidiOpen2(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
    void MidiOpenNotify2(HMIDIIN midi_in, UINT msg_type, DWORD midi_msg, DWORD param2);
    void UpdateControllerRun();

    // Dialogfelddaten
    //{{AFX_DATA(Assign)
    enum { IDD = IDD_DIALOG2 };

    //}}AFX_DATA

    // Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
    //{{AFX_VIRTUAL(Assign)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV-Unterstützung
    //}}AFX_VIRTUAL

    // Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    //{{AFX_MSG(Assign)
    BOOL OnInitDialog() override;
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnRadio5();
    afx_msg void OnSelendokCombo1();
    afx_msg void OnSelendokCombo2();
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnButton1();
    afx_msg void OnButton2();
    afx_msg void OnChangeEdit1();
    afx_msg void OnChangeEdit2();
    afx_msg void OnButton6();
    afx_msg void OnButton3();
    afx_msg void OnButton4();
    afx_msg void OnRadio6();
    afx_msg void OnRadio7();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnButton7();
    afx_msg void OnButton8();
    afx_msg void OnButton9();
    afx_msg void OnButton10();
    void OnOK() override;
    afx_msg void OnCheck1();
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ASSIGN_H__417A9DC8_02FF_48F1_A26B_2BE876B697C2__INCLUDED_
