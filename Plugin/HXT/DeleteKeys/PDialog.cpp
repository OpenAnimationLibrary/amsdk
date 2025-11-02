// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "DeleteKeys.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(HChor *chor) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_chor = chor;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Time(pDX, IDC_EDIT1, start, (int)GetHProject()->GetFPS(), GetTimeMode(), FALSE);
    DDX_Time(pDX, IDC_EDIT2, end, (int)GetHProject()->GetFPS(), GetTimeMode(), FALSE);
    //{{AFX_DATA_MAP(PDialog)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_EN_UPDATE(IDC_EDIT1, &PDialog::OnUpdateEdit1)
        ON_EN_UPDATE(IDC_EDIT2, &PDialog::OnUpdateEdit2)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::OnUpdateEdit1() {
    UpdateData(TRUE);
//    TimeRange timetodelete;
    const Time starttime = start, endtime = end;
    CString temp;
    temp.Format("Delete all keys for the selected objects in the range from frame %i to frame %i", starttime.GetFrameInt(GetHProject()->GetFPS()), endtime.GetFrameInt(GetHProject()->GetFPS()));
    SetDlgItemText(IDC_STATIC_TEXT, temp);
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    id1->ResetContent();
    if (int index; starttime == Time()) {
        for (HHashObject *hho = m_chor->GetChild(); hho; hho = hho->GetSibling()) {
            if (hho->CountKeys() > 0) {
                temp.Format("%s", hho->GetName());
                index = id1->AddString(temp);
                id1->SetItemDataPtr(index, hho);
            }
        }
    } else {
        for (HHashObject *hho = m_chor->GetChild(); hho; hho = hho->GetSibling()) {
            if (hho->CountKeys() > 1) {
                temp.Format("%s", hho->GetName());
                index = id1->AddString(temp);
                id1->SetItemDataPtr(index, hho);
            }
        }
    }
}

void PDialog::OnUpdateEdit2() {
    UpdateData(TRUE);
    const Time starttime = start, endtime = end;
    CString temp;
    temp.Format("Delete all keys for the selected objects in the range from frame %i to frame %i", starttime.GetFrameInt(GetHProject()->GetFPS()), endtime.GetFrameInt(GetHProject()->GetFPS()));
    SetDlgItemText(IDC_STATIC_TEXT, temp);
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;
    for (HHashObject *hho = m_chor->GetChild(); hho; hho = hho->GetSibling()) {
        if (hho->CountKeys() > 1) {
            temp.Format("%s", hho->GetName());
            const int index = id1->AddString(temp);
            id1->SetItemDataPtr(index, hho);
        }
    }
    //	id1->SetCurSel(0);
//    TimeRange timetodelete;
    const Time endtime(m_chor->GetTotalTime()->GetValue());
    Time starttime;
    starttime.StepFrame(GetHProject()->GetFPS());
    start = starttime;
    end = endtime;
    UpdateData(FALSE);
    temp.Format("Delete all keys for the selected objects in the range from frame %i to frame %i", starttime.GetFrameInt(GetHProject()->GetFPS()), endtime.GetFrameInt(GetHProject()->GetFPS()));
    SetDlgItemText(IDC_STATIC_TEXT, temp);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void BoneDeleteKeys(HBone *startbone, const TimeRange &timetodelete) {
    for (HBone *bone = startbone; bone; bone = bone->GetChildBone()) {
        if (bone->GetSiblingBone())
            BoneDeleteKeys(bone->GetSiblingBone(), timetodelete);
        bone->DeleteKeys(timetodelete);
    }
}

void PDialog::OnOK() {
    UpdateData(TRUE);
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CWaitCursor wait;
    const int nCount = id1->GetSelCount();
    CArray<int, int> selection;
    selection.SetSize(nCount);
    id1->GetSelItems(nCount, selection.GetData());
    TimeRange timetodelete;
    timetodelete.Set(start, end);
    for (int i = 0; i < selection.GetSize(); ++i) {
        const auto hho = (HHashObject *)id1->GetItemDataPtr(selection[i]);
        if (hho->GetObjectType() == HOT_MODEL) {
            auto *model = (HModel *)hho;
            for (HBone *bone = model->GetChildBone(); bone; bone = bone->GetSiblingBone()) {
                BoneDeleteKeys(bone, timetodelete);
            }
        }
        HTreeObject *hto = hho->GetParent();
        const int objecttype = hho->GetObjectType();
        hho->DeleteKeys(timetodelete);
        if (objecttype != HOT_CHANNELDRIVER) {
            hho->OnModified();
        } else {
            if (hho->CountKeys() > 0) {
                hho->OnModified();
            } else {
                HProject::DeleteHandle(hho);
                hto->OnModified();
            }
        }
    }
    CPluginDialog::OnOK();
}

/*
void PDialog::OnOK() 
{
	CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
   CWaitCursor wait;
   int nCount = id1->GetSelCount();
   int i;
   CArray <int,int> selection;
   selection.SetSize(nCount);
   id1->GetSelItems(nCount, selection.GetData());
   HModel *model;
   TimeRange timetodelete;
   Time starttime(0);
   starttime.StepFrame(GetHProject()->GetFPS());  
   timetodelete.Set(starttime,m_chor->GetTotalTime()->GetValue());
   for (i=0;i<selection.GetSize();++i) {
		   model = ((HModel *)id1->GetItemDataPtr(selection[i]));
         for (HBone *bone = model->GetChildBone();bone;bone = bone->GetSiblingBone()) {
            BoneDeleteKeys(bone, timetodelete);
         }
         model->DeleteKeys(timetodelete);
         model->OnModified();
   }
	CDialog::OnOK();
}
*/
