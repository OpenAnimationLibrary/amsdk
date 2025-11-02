// viewassigned.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Midicontrol.h"
#include "viewassigned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

viewassigned::viewassigned(PARAMETER *para): CPluginDialog(IDD, AfxGetMainWnd()) {
    //{{AFX_DATA_INIT(viewassigned)
    m_para = para;
    // HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
    //}}AFX_DATA_INIT
}

void viewassigned::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(viewassigned)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(viewassigned, CDialog)
        //{{AFX_MSG_MAP(viewassigned)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten viewassigned 
BOOL viewassigned::OnInitDialog() {
    CString temp;
    CSize sz;
    CPluginDialog::OnInitDialog();

    CClientDC dc(this);
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CFont *f = id1->GetFont();
    dc.SelectObject(f);
    int width = 0;

    for (int i = 0; i < m_para->azobject; ++i) {
        for (int j = 0; j < m_para->obj[i].azprop; ++j) {
            if (m_para->obj[i].prop[j].driven) {
                switch (m_para->obj[i].prop[j].driven_value[0]) {
                    case 0x90:
                        temp.Format("Note On        | Channel %2d | Pitch  %3d", m_para->obj[i].prop[j].driven_value[1], m_para->obj[i].prop[j].driven_value[2]);
                        break;
                    case 0xA0:
                        temp.Format("Key Pressure   | Channel %2d | Pitch  %3d", m_para->obj[i].prop[j].driven_value[1], m_para->obj[i].prop[j].driven_value[2]);
                        break;
                    case 0xB0:
                        temp.Format("Control Change | Channel %2d | Number %3d", m_para->obj[i].prop[j].driven_value[1], m_para->obj[i].prop[j].driven_value[2]);
                        break;
                    default:
                        temp.Format("");
                        break;
                }
                CString temp1 = temp + " <-> " + m_para->obj[i].prop[j].Fullname.Get();
                id1->AddString(temp1);
                sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
                if (sz.cx > width) {
                    width = sz.cx;
                }
            }
        }
    }

    id1->SetHorizontalExtent(width);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
