// BandDlg.cpp: Implementierungsdatei
#include "StdAfx.h"
#include "Amplitude.h"
#include "BandDlg.h"

BandDlg::BandDlg(const int samplefreq) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    _samplefreq = samplefreq;
}

BOOL BandDlg::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    //   fftTransformer = std::auto_ptr<Fft> (new Fft(1024, _samplefreq));
    const auto fftTransformer = std::make_unique<Fft>(1024, _samplefreq);
    auto *listbox1 = (CListBox *)GetDlgItem(IDC_LIST1);
    auto *listbox2 = (CListBox *)GetDlgItem(IDC_LIST2);
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < fftTransformer->Points_asInt(); ++i) {
        const int frequence = fftTransformer->GetFrequency(i);
        String temp = frequence;
        if (frequence == low) {
            idx1 = listbox1->AddString(temp.Get());
        } else {
            listbox1->AddString(temp.Get());
        }
        if (frequence == high) {
            idx2 = listbox2->AddString(temp.Get());
        } else {
            listbox2->AddString(temp.Get());
        }
    }
    if (idx1 != -1) {
        listbox1->SetCurSel(idx1);
    }
    if (idx2 != -1) {
        listbox2->SetCurSel(idx2);
    }
    return TRUE;
}

void BandDlg::OnOK() {
    CPluginDialog::OnOK();
    const auto *listbox1 = (CListBox *)GetDlgItem(IDC_LIST1);
    const auto *listbox2 = (CListBox *)GetDlgItem(IDC_LIST2);
    CString str2;
    int index1 = listbox1->GetCurSel();
    int index2 = listbox2->GetCurSel();
    if (index2 <= index1) {
        if (index1 >= listbox1->GetCount()) {
            index1 = listbox1->GetCount() - 2;
        }
        index2 = index1 + 1;
    }
    listbox1->GetText(index1, str2);
    low = atoi_replace(str2.GetBuffer());
    listbox2->GetText(index2, str2);
    high = atoi_replace(str2.GetBuffer());
}

BandDlg::~BandDlg() = default;

void BandDlg::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(BandDlg, CDialog)
END_MESSAGE_MAP()
