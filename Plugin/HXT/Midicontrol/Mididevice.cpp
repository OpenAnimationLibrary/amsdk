// Mididevice.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Midicontrol.h"
#include "Mididevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

Mididevice::Mididevice(PARAMETER *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(Mididevice)
    m_para = para;
    //}}AFX_DATA_INIT
}

void Mididevice::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Mididevice)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Mididevice, CDialog)
        //{{AFX_MSG_MAP(Mididevice)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Mididevice 

BOOL Mididevice::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;
    const int max = midiInGetNumDevs();
    MIDIINCAPS midi_in_caps;
    for (int i = 0; i < max; ++i) {
        midiInGetDevCaps(i, &midi_in_caps, sizeof midi_in_caps);
        temp.Format("%3d %s", i, midi_in_caps.szPname);
        id1->AddString(temp);
    }
    id1->SetCurSel(m_para->midi_device);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Mididevice::OnOK() {
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);

    m_para->midi_device = id1->GetCurSel();
    CPluginDialog::OnOK();
}
