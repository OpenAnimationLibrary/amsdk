// ImportDlg.cpp: Implementierungsdatei

#include "StdAfx.h"
#include "Amplitude.h"
#include "ImportDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

#define ErrorExit() goto Error_Exit

ImportDlg::ImportDlg(Parameter &para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    dlg_para = &para;
    timing = 0;
    repeat = 0;
    isplaying = FALSE;
    max_valuei = dlg_para->m_maxi + 1;
    min_valuei = dlg_para->m_mini - 1;
    max_valuef = dlg_para->m_maxf + 1;
    min_valuef = dlg_para->m_minf - 1;
    if (dlg_para->m_property) {
        switch (dlg_para->m_objtype) {
            case HOT_COLOR:
                break;
            case HOT_INTEGER:
            {
                const HIntPropertyInfo *hpi = (HIntPropertyInfo *)dlg_para->m_property->GetPropertyInfo();
                min_valuei = hpi->GetMinValue();
                max_valuei = hpi->GetMaxValue();
            }
            break;
            case HOT_EULERFLOAT:
            case HOT_FLOAT:
            {
                const HFloatPropertyInfo *hpi = (HFloatPropertyInfo *)dlg_para->m_property->GetPropertyInfo();
                min_valuef = hpi->GetMinValue();
                if (min_valuef != -hash_constants::max_float)
                    min_valuef *= hpi->GetFactorValue();
                max_valuef = hpi->GetMaxValue();
                if (max_valuef != hash_constants::max_float)
                    max_valuef *= hpi->GetFactorValue();
            }
            break;
            case HOT_PERCENT:
            {
                const HPercentPropertyInfo *hpi = (HPercentPropertyInfo *)dlg_para->m_property->GetPropertyInfo();
                const float factor = hpi->GetFactorValue();
                min_valuef = hpi->GetMinValue();
                if (min_valuef != -hash_constants::max_float)
                    min_valuef *= factor;
                max_valuef = hpi->GetMaxValue();
                if (max_valuef != hash_constants::max_float)
                    max_valuef *= factor;
            }
            break;
            default:
   break;
        }
    }
    if (dlg_para->m_maxi > max_valuei)
        dlg_para->m_maxi = max_valuei;
    if (dlg_para->m_mini < min_valuei)
        dlg_para->m_mini = min_valuei;
    if (dlg_para->m_maxf > max_valuef)
        dlg_para->m_maxf = max_valuef;
    if (dlg_para->m_minf < min_valuef)
        dlg_para->m_minf = min_valuef;
}

ImportDlg::~ImportDlg() = default;

void ImportDlg::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RADIO1, timing);
    DDX_Radio(pDX, IDC_RADIO4, dlg_para->m_channels);
    DDX_Time(pDX, IDC_EDIT2, dlg_para->m_wave.m_startpos, (int)dlg_para->m_fps, dlg_para->m_timemode, FALSE);
    DDX_Time(pDX, IDC_EDIT3, dlg_para->m_wave.m_endpos, (int)dlg_para->m_fps, dlg_para->m_timemode, FALSE);
    DDX_Check(pDX, IDC_CHECK1, repeat);
    DDX_Check(pDX, IDC_CHECK2, dlg_para->add_tocurrentvalue);
    DDX_Text(pDX, IDC_EDIT4, dlg_para->m_minf);
    DDV_MinMaxFloat(pDX, dlg_para->m_minf, min_valuef, max_valuef);
    DDX_Text(pDX, IDC_EDIT5, dlg_para->m_maxf);
    DDV_MinMaxFloat(pDX, dlg_para->m_maxf, min_valuef, max_valuef);
    DDX_Text(pDX, IDC_EDIT6, dlg_para->m_mini);
    DDV_MinMaxInt(pDX, dlg_para->m_mini, min_valuei, max_valuei);
    DDX_Text(pDX, IDC_EDIT6, dlg_para->m_maxi);
    DDV_MinMaxInt(pDX, dlg_para->m_maxi, min_valuei, max_valuei);
    DDX_Radio(pDX, IDC_RADIO7, dlg_para->m_band);
    DDX_Check(pDX, IDC_CHECK3, dlg_para->m_useband);
    DDX_Radio(pDX, IDC_RADIO18, dlg_para->m_halfframe);
}

BEGIN_MESSAGE_MAP(ImportDlg, CDialog)
    ON_WM_DRAWITEM()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_BUTTON1, &ImportDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_RADIO1, &ImportDlg::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &ImportDlg::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &ImportDlg::OnBnClickedRadio3)
    ON_BN_CLICKED(IDC_CHECK1, &ImportDlg::OnBnClickedCheck1)
    ON_EN_KILLFOCUS(IDC_EDIT3, &ImportDlg::OnEnKillfocusEdit3)
    ON_EN_KILLFOCUS(IDC_EDIT2, &ImportDlg::OnEnKillfocusEdit2)
    ON_BN_CLICKED(IDC_BUTTON2, &ImportDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &ImportDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &ImportDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &ImportDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

// ImportDlg-Meldungshandler

BOOL ImportDlg::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    if (dlg_para->m_wavefilename.IsEmpty()) {
        const String text = "Select a wave file";
        CWnd *dlgitem = GetDlgItem(IDC_EDIT1);
        dlgitem->SetWindowText(text.Get());
        dlgitem = GetDlgItem(IDC_STATIC_INFO);
        dlgitem->SetWindowText(text.Get());
    } else {
        BOOL isloading_success = FALSE;
        if (dlg_para->m_wave.IsSound(dlg_para->m_wavefilename)) {
            if (dlg_para->m_wave.LoadWAV(dlg_para->m_wavefilename)) {
                isloading_success = TRUE;
            }
        }
        WaveLoaded(isloading_success);
    }

    const CRect rct(12, 175, 587, 255);
    m_graph_left.Create("STATIC", _T(""), WS_VISIBLE | WS_CHILD, rct, this, 5000);
    const CRect rrct(12, 255, 587, 335);
    m_graph_right.Create("STATIC", _T(""), WS_VISIBLE | WS_CHILD, rrct, this, 5001);
    UpdateTiming();
    UpdateDisplay();
    return TRUE; // return TRUE unless you set the focus to a control
}

void ImportDlg::WaveLoaded(const BOOL load_success) {
    String text;
    CWnd *dlgitem;
    if (!load_success) {
        dlg_para->m_wavefilename = "";
        text = "Select a wave file";
        dlgitem = GetDlgItem(IDC_EDIT1);
        dlgitem->SetWindowText(text.Get());
        text = "Error loading the selected file";
        dlgitem = GetDlgItem(IDC_STATIC_INFO);
        dlgitem->SetWindowText(text.Get());
        return;
    }
    if (dlg_para->m_timing == 0) {
        dlg_para->m_wave.m_startpos = 0;
        dlg_para->m_wave.m_endpos = dlg_para->m_chorlength;
    }
    if (dlg_para->m_timing == 1) {
        dlg_para->m_wave.m_startpos = 0;
        dlg_para->m_wave.m_endpos = Time(dlg_para->m_wave.m_length);
    }
    if (dlg_para->m_timing == 2) {
        if (dlg_para->m_wave.m_endpos.GetSeconds() > dlg_para->m_wave.m_length) {
            dlg_para->m_wave.m_endpos = Time(dlg_para->m_wave.m_length);
        }
        if (dlg_para->m_wave.m_endpos <= dlg_para->m_wave.m_startpos) {
            dlg_para->m_wave.m_startpos.StepFrameBack(dlg_para->m_fps);
        }
    }
    dlgitem = GetDlgItem(IDC_EDIT1);
    text = dlg_para->m_wavefilename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
    text = dlg_para->m_wave.GetSoundDescription(dlg_para->m_fps, (TimeUnit)dlg_para->m_timemode);
    text += " , Choreography Length " + dlg_para->m_chorlength.ToString(dlg_para->m_fps, (TimeUnit)dlg_para->m_timemode);
    dlgitem = GetDlgItem(IDC_STATIC_INFO);
    dlgitem->SetWindowText(text.Get());
    if (dlg_para->m_wave.GetNumChannels() == 2) {
        dlgitem = GetDlgItem(IDC_RADIO5);
        dlgitem->EnableWindow(TRUE);
        dlgitem = GetDlgItem(IDC_RADIO6);
        dlgitem->EnableWindow(TRUE);
    } else {
        dlg_para->m_channels = 0;
        dlgitem = GetDlgItem(IDC_RADIO5);
        dlgitem->EnableWindow(FALSE);
        dlgitem = GetDlgItem(IDC_RADIO6);
        dlgitem->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}

void ImportDlg::UpdateDisplay() {
    CWnd *dlgitem;
    CString temp;
    String name;
    if (dlg_para->m_wave.GetNumChannels() == 2) {
        dlgitem = GetDlgItem(IDC_RADIO5);
        dlgitem->EnableWindow(TRUE);
        dlgitem = GetDlgItem(IDC_RADIO6);
        dlgitem->EnableWindow(TRUE);
    } else {
        dlg_para->m_channels = 0;
        dlgitem = GetDlgItem(IDC_RADIO5);
        dlgitem->EnableWindow(FALSE);
        dlgitem = GetDlgItem(IDC_RADIO6);
        dlgitem->EnableWindow(FALSE);
        UpdateData(FALSE);
    }
    switch (dlg_para->m_objtype) {
        case HOT_COLOR:
            dlgitem = GetDlgItem(IDC_EDIT4);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_EDIT5);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_EDIT6);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_EDIT7);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_BUTTON2);
            dlgitem->ShowWindow(SW_SHOW);
            dlgitem = GetDlgItem(IDC_BUTTON3);
            dlgitem->ShowWindow(SW_SHOW);
            dlgitem = GetDlgItem(IDC_CHECK2);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_STATIC_MIN);
            name = "Minimum";
            dlgitem->SetWindowText(name.Get());
            dlgitem = GetDlgItem(IDC_STATIC_MAX);
            name = "Maximum";
            dlgitem->SetWindowText(name.Get());
            break;
        case HOT_INTEGER:
            dlgitem = GetDlgItem(IDC_EDIT4);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_EDIT5);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_EDIT6);
            dlgitem->ShowWindow(SW_SHOW);
            dlgitem = GetDlgItem(IDC_EDIT7);
            dlgitem->ShowWindow(SW_SHOW);
            dlgitem = GetDlgItem(IDC_BUTTON2);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_BUTTON3);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_CHECK2);
            dlgitem->ShowWindow(SW_SHOW);
            temp.Format("Minimum (%d)", min_valuei);
            dlgitem = GetDlgItem(IDC_STATIC_MIN);
            name = (String)temp;
            dlgitem->SetWindowText(name.Get());
            temp.Format("Maximum (%d)", max_valuei);
            dlgitem = GetDlgItem(IDC_STATIC_MAX);
            name = (String)temp;
            dlgitem->SetWindowText(name.Get());
            break;
        default:
            dlgitem = GetDlgItem(IDC_EDIT4);
            dlgitem->ShowWindow(SW_SHOW);
            dlgitem = GetDlgItem(IDC_EDIT5);
            dlgitem->ShowWindow(SW_SHOW);
            dlgitem = GetDlgItem(IDC_EDIT6);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_EDIT7);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_BUTTON2);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_BUTTON3);
            dlgitem->ShowWindow(SW_HIDE);
            dlgitem = GetDlgItem(IDC_CHECK2);
            dlgitem->ShowWindow(SW_SHOW);
            if (min_valuef == -hash_constants::max_float)
                temp.Format("Minimum Value (%.4e)", min_valuef);
            else
                temp.Format("Minimum Value (%8.2f)", min_valuef);
            dlgitem = GetDlgItem(IDC_STATIC_MIN);
            name = (String)temp;
            dlgitem->SetWindowText(name.Get());
            if (max_valuef == hash_constants::max_float)
                temp.Format("Maximum Value (%.4e)", max_valuef);
            else
                temp.Format("Maximum Value (%8.2f)", max_valuef);
            dlgitem = GetDlgItem(IDC_STATIC_MAX);
            name = (String)temp;
            dlgitem->SetWindowText(name.Get());
            break;
    }
    dlgitem = GetDlgItem(IDC_STATIC_PROP);
    if (dlg_para->m_fullname.Find("Surface.")) {
        name = "";
        for (HTreeObject *hto = dlg_para->m_property; hto && hto->GetObjectType() != HOT_MODEL && hto->GetObjectType() != HOT_CHOR; hto = hto->GetParent()) {
            auto *hho = (HHashObject *)hto;
            if (hho) {
                if (name.IsEmpty())
                    name = hho->GetName();
                else
                    name = hho->GetName() + (String)" -- " + name;
            }
        }
        if (dlg_para->m_hmodel)
            temp.Format("%s -- %s", dlg_para->m_hmodel->GetName(), name.Get());
        else
            temp.Format("%s", name.Get());
    } else {
        if (dlg_para->m_hmodel)
            temp.Format("%s -- %s", dlg_para->m_hmodel->GetName(), dlg_para->m_name.Get());
        else
            temp.Format("%s", dlg_para->m_name.Get());
    }
    name = (String)temp;
    dlgitem->SetWindowText(name.Get());

    temp.Format("%iHz - %iHz", dlg_para->m_wave.m_bands[10].start_freq, dlg_para->m_wave.m_bands[10].end_freq);
    dlgitem = GetDlgItem(IDC_BUTTON5);
    name = (String)temp;
    dlgitem->SetWindowText(name.Get());

}

void ImportDlg::UpdateTiming() const {
    CWnd *dlgitem;
    switch (timing) {
        case 0:
            dlgitem = GetDlgItem(IDC_CHECK1);
            if (dlg_para->m_chorlength.GetSeconds() > dlg_para->m_wave.m_length)
                dlgitem->EnableWindow(TRUE);
            else
                dlgitem->EnableWindow(FALSE);
            dlgitem = GetDlgItem(IDC_EDIT2);
            dlgitem->EnableWindow(FALSE);
            dlgitem = GetDlgItem(IDC_EDIT3);
            dlgitem->EnableWindow(FALSE);
            break;
        case 1:
            dlgitem = GetDlgItem(IDC_CHECK1);
            dlgitem->EnableWindow(FALSE);
            dlgitem = GetDlgItem(IDC_EDIT2);
            dlgitem->EnableWindow(FALSE);
            dlgitem = GetDlgItem(IDC_EDIT3);
            dlgitem->EnableWindow(FALSE);
            break;
        case 2:
            dlgitem = GetDlgItem(IDC_CHECK1);
            dlgitem->EnableWindow(FALSE);
            dlgitem = GetDlgItem(IDC_EDIT2);
            dlgitem->EnableWindow(TRUE);
            dlgitem = GetDlgItem(IDC_EDIT3);
            dlgitem->EnableWindow(TRUE);
            break;
    }
}

void ImportDlg::OnBnClickedRadio1() {
    UpdateData(TRUE);
    dlg_para->m_timing = timing = 0;
    dlg_para->m_wave.m_startpos = 0;
    dlg_para->m_wave.m_endpos = dlg_para->m_chorlength;
    UpdateData(FALSE);
    UpdateTiming();
    UpdateWaveform();
}

void ImportDlg::OnBnClickedRadio2() {
    UpdateData(TRUE);
    dlg_para->m_timing = timing = 1;
    dlg_para->m_wave.m_startpos = 0;
    dlg_para->m_wave.m_endpos = Time(dlg_para->m_wave.m_length);
    UpdateData(FALSE);
    UpdateTiming();
    UpdateWaveform();
}

void ImportDlg::OnBnClickedRadio3() {
    UpdateData(TRUE);
    dlg_para->m_timing = timing = 2;
    UpdateTiming();
    UpdateWaveform();
}

void ImportDlg::OnBnClickedCheck1() {}

void ImportDlg::OnEnKillfocusEdit2() {
    UpdateData(TRUE);
    if (dlg_para->m_wave.m_startpos >= dlg_para->m_wave.m_endpos) {
        dlg_para->m_wave.m_startpos = dlg_para->m_wave.m_endpos;
        dlg_para->m_wave.m_endpos += dlg_para->m_wave.m_startpos;
        if (dlg_para->m_wave.m_endpos >= dlg_para->m_chorlength) {
            dlg_para->m_wave.m_endpos = dlg_para->m_chorlength;
            dlg_para->m_wave.m_startpos.StepFrameBack(dlg_para->m_fps);
        }
        UpdateData(FALSE);
    }
    UpdateWaveform();
}

void ImportDlg::OnEnKillfocusEdit3() {
    UpdateData(TRUE);
    if (dlg_para->m_wave.m_endpos <= dlg_para->m_wave.m_startpos) {
        dlg_para->m_wave.m_endpos = dlg_para->m_wave.m_startpos;
        dlg_para->m_wave.m_endpos.StepFrame(dlg_para->m_fps);
        UpdateData(FALSE);
    }
    UpdateWaveform();
}

void ImportDlg::OnDrawItem(const int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
    if (nIDCtl == IDC_BUTTON2) {
        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, dlg_para->m_minc);
    }
    if (nIDCtl == IDC_BUTTON3) {
        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, dlg_para->m_maxc);
    }

    CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void ImportDlg::OnBnClickedButton1() {
    CString filters, title;
    title.LoadString(IDS_IMPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);
    String filename;
    const String ext("wav");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(title, filters, filename, ext.Get(), ext.Get()))
            return;
    }
    BOOL isloading_success = FALSE;
    if (dlg_para->m_wave.IsSound(filename)) {
        if (dlg_para->m_wave.LoadWAV(filename)) {
            dlg_para->m_wavefilename = filename;
            isloading_success = TRUE;
        }
    }
    WaveLoaded(isloading_success);
    UpdateTiming();
    UpdateWaveform();
}

void ImportDlg::OnBnClickedButton2() {
    const COLORREF color = dlg_para->m_minc;
    CColorDialog cdlg(color, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        dlg_para->m_minc = cdlg.GetColor();
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id1->Invalidate(TRUE);
    }
}

void ImportDlg::OnBnClickedButton3() {
    CColorDialog cdlg(dlg_para->m_maxc, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        dlg_para->m_maxc = cdlg.GetColor();
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
        id1->Invalidate(TRUE);
    }
}

void ImportDlg::OnPaint() {
    CPaintDC dc(this); // device context for painting
    UpdateWaveform();
}

void ImportDlg::UpdateWaveform() const {
    CWnd *dlgitem = GetDlgItem(IDC_STATIC_TEST);
    CRect clientrect;
    dlgitem->GetClientRect(&clientrect);

    CDC *dc = dlgitem->GetDC();
    CRect backrect(clientrect);
    clientrect.right -= 1;
    int numpixels = clientrect.Width();
    if (0 == numpixels - 1)
        return;

    dc->FillSolidRect(backrect, GetSysColor(COLOR_BTNFACE));
    if (!dlg_para->m_wave.IsBufferReady())
        return;
    if (dlg_para->m_wave.GetNumChannels() == 2) {
        const int mid = (clientrect.top + clientrect.bottom) * 0.5F;
        int top = clientrect.top + mid - (clientrect.top + mid) / 2 - 10;
        int bottom = top + 20;
        dc->SetTextColor(RGB(0, 0, 0));
        dc->SetBkMode(TRANSPARENT);
        CRect text_rectl(clientrect.left, top, 10, bottom);
        dc->DrawText("L", text_rectl, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        top = mid + mid / 2 - 10;
        bottom = top + 20;
        CRect text_rectr(clientrect.left, top, 10, bottom);
        dc->DrawText("R", text_rectr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        numpixels -= 10;
        clientrect.left += 10;
    }

    const double samplesperpixel = dlg_para->m_wave.m_length * dlg_para->m_wave.GetSampleRate() / numpixels;

    BOOL clipped = FALSE;
    CRect clippedrect(clientrect);
    if (isplaying || (timing != 1 && Time(dlg_para->m_wave.m_length) >= dlg_para->m_wave.m_endpos)) {
        const double startpos = dlg_para->m_wave.m_startpos.GetSecondsDouble();
        const double endpos = dlg_para->m_wave.m_endpos.GetSecondsDouble();
        const double to_select = (endpos - startpos) / dlg_para->m_wave.m_length;
        const int width = clippedrect.Width();
        if (startpos != 0) {
            clippedrect.left = clientrect.left + width * (startpos / dlg_para->m_wave.m_length);
            clippedrect.right = clippedrect.left + width * to_select;
        } else {
            clippedrect.right = clippedrect.left + width * to_select;
        }
        clipped = TRUE;
    }

    static COLORREF yellow = RGB(200, 200, 0);
    static COLORREF blue = RGB(0, 0, 200);
    static COLORREF red = RGB(200, 0, 0);
    const COLORREF col = clipped ? yellow : blue;
    if (clipped && !isplaying) {
        dc->FillSolidRect(clippedrect, red);
    }
    if (!dlg_para->m_wave.waveform_ready) {
        dlg_para->m_wave.DrawWaveform(clientrect, 0, dlg_para->m_wave.m_length, samplesperpixel);
    }
    CPen wavePen(PS_SOLID, 0, col);
    CPen *pOldPen = dc->SelectObject(&wavePen);
    dc->Polyline(dlg_para->m_wave.Points_Left.GetData(), dlg_para->m_wave.Points_Left.GetSize());
    if (dlg_para->m_wave.Points_Right.GetSize() > 0) {
        dc->Polyline(dlg_para->m_wave.Points_Right.GetData(), dlg_para->m_wave.Points_Right.GetSize());
    }
    if (clipped && isplaying) {
        dc->FillSolidRect(clippedrect, red);
    }
    dc->SelectObject(pOldPen);
}

void ImportDlg::OnBnClickedButton5() {
    BandDlg bdlg(dlg_para->m_wave.GetSampleRate());
    bdlg.low = dlg_para->m_wave.m_bands[10].start_freq;
    bdlg.high = dlg_para->m_wave.m_bands[10].end_freq;
    if (bdlg.DoModal() == IDOK) {
        dlg_para->m_wave.m_bands[10].start_freq = bdlg.low;
        dlg_para->m_wave.m_bands[10].end_freq = bdlg.high;
        CString temp;
        temp.Format("%iHz - %iHz", dlg_para->m_wave.m_bands[10].start_freq, dlg_para->m_wave.m_bands[10].end_freq);
        CWnd *dlgitem = GetDlgItem(IDC_BUTTON5);
        const String name = temp;
        dlgitem->SetWindowText(name.Get());
    }
}

void ImportDlg::OnBnClickedButton4() {
    Visualize();
}

void ImportDlg::Visualize() {
    CWnd *dlgitem = GetDlgItem(IDC_BUTTON4);
    dlgitem->SetWindowText("Stop with Escape");

    dlgitem = GetDlgItem(IDC_STATIC_SAMPLE);
    CString temp;

    std::vector<int> outBuf_L;
    std::vector<int> outBuf_R;
    //   fftTransformer = std::auto_ptr<Fft>(new Fft(1024, dlg_para->m_wave.GetSampleRate()));
    const auto fftTransformer = std::make_unique<Fft>(1024, dlg_para->m_wave.GetSampleRate());
    double fdraw[11];

    //Calculate the bands
    for (int i = 0; i < 11; ++i) {
        dlg_para->m_wave.m_bands[i].start = fftTransformer->HzToNearestPoint(dlg_para->m_wave.m_bands[i].start_freq);
        dlg_para->m_wave.m_bands[i].end = fftTransformer->HzToNearestPoint(dlg_para->m_wave.m_bands[i].end_freq);
        dlg_para->m_wave.m_bands[i].az_freq = dlg_para->m_wave.m_bands[i].end - dlg_para->m_wave.m_bands[i].start;
        //      ASSERT(dlg_para->m_wave.m_bands[i].az_freq != 0);
        dlg_para->m_wave.m_bands[i].az_freq += 1;
    }

    const Time org_start = dlg_para->m_wave.m_startpos;
    const Time org_end = dlg_para->m_wave.m_endpos;
    const int startframe = dlg_para->m_wave.m_startpos.GetFrameInt(dlg_para->m_fps);
    const int endframe = dlg_para->m_wave.m_endpos.GetFrameInt(dlg_para->m_fps);
    const double one_framestep = 1. / dlg_para->m_fps;
    const double step = 1.0 / dlg_para->m_wave.GetSampleRate();
    outBuf_L.resize(1024);
    outBuf_R.resize(1024);
    const double step_length = one_framestep / step; //in samples
    const double offset_pos = step * ((step_length - 1024) / 2);
    Time stepping;
    stepping.StepFrames(1, dlg_para->m_fps);
    dlg_para->m_wave.m_endpos = dlg_para->m_wave.m_startpos;
    dlg_para->m_wave.m_startpos -= stepping;
    Time endtime;
    isplaying = TRUE;
    for (int i = startframe; i < endframe; ++i) {
        if (EscapeKeyDown())
            ErrorExit();

        dlg_para->m_wave.m_startpos += stepping;
        dlg_para->m_wave.m_endpos += stepping;
        if (dlg_para->m_wave.m_endpos > Time(dlg_para->m_wave.m_length)) {
            dlg_para->m_wave.m_startpos = Time(dlg_para->m_wave.m_length) - stepping;
            dlg_para->m_wave.m_endpos = dlg_para->m_wave.m_length;
        }
        UpdateWaveform();
        temp.Format("Frame %i", i);
        String name = temp;
        dlgitem->SetWindowText(name.Get());

        endtime.SetFrame(i, dlg_para->m_fps);
        double pos = endtime.GetSecondsDouble() + offset_pos; //for fitting windowsize 1024 
        if (pos < 0)
            pos = 0;
        for (int j = 0; j < 1024; ++j) {
            if (pos < dlg_para->m_wave.m_length) {
                const PCMSample_16bitStereo sample = dlg_para->m_wave.GetSample(pos);
                pos += step;
                outBuf_L[j] = sample.left;
                outBuf_R[j] = sample.right;
            } else {
                outBuf_L[j] = 0;
                outBuf_R[j] = 0;
            }
        }
        float value_left = 0.F, value_right = 0.F;
        pos = endtime.GetSecondsDouble(); //for fitting windowsize 1024 
        for (int j = 0; j < step_length; ++j) {
            if (pos < dlg_para->m_wave.m_length) {
                const PCMSample_16bitStereo sample = dlg_para->m_wave.GetSample(pos);
                if (abs(sample.left) > value_left)
                    value_left = hash_math::abs(sample.left);
                if (abs(sample.right) > value_right)
                    value_right = hash_math::abs(sample.right);
                pos += step;
            }
        }
        value_left = value_left / MAX16BIT / dlg_para->m_wave.m_peaksample;
        value_right = value_right / MAX16BIT / dlg_para->m_wave.m_peaksample;
        // left channel
        double fmax = -hash_constants::max_float;
        double fmin = hash_constants::max_float;
        fftTransformer->Transform(outBuf_L);
        for (int j = 0; j < 11; ++j) {
            double sfmax = -hash_constants::max_float;
            for (int z = dlg_para->m_wave.m_bands[j].start; z < dlg_para->m_wave.m_bands[j].start + dlg_para->m_wave.m_bands[j].az_freq; ++z) {
                const double temp_value = fftTransformer->GetIntensity(z);
                if (temp_value > sfmax)
                    sfmax = temp_value;
            }
            fdraw[j] = sfmax;
            if (fdraw[j] > fmax)
                fmax = fdraw[j];
            if (fdraw[j] < fmin)
                fmin = fdraw[j];
        }
        double scale;
        if (value_left < 0.001)
            scale = 0;
        else
            scale = 256.0 / fmax;
        for (double &j: fdraw) {
            j = j * scale * value_left;
        }
        m_graph_left.Update(11, fdraw);

        // right channel
        fmax = -hash_constants::max_float;
        fmin = hash_constants::max_float;
        fftTransformer->Transform(outBuf_R);
        for (int j = 0; j < 11; ++j) {
            double sfmax = -hash_constants::max_float;
            for (int z = dlg_para->m_wave.m_bands[j].start; z < dlg_para->m_wave.m_bands[j].start + dlg_para->m_wave.m_bands[j].az_freq; ++z) {
                const double temp_value = fftTransformer->GetIntensity(z);
                if (temp_value > sfmax)
                    sfmax = temp_value;
            }
            fdraw[j] = sfmax;
            if (fdraw[j] > fmax)
                fmax = fdraw[j];
            if (fdraw[j] < fmin)
                fmin = fdraw[j];
        }
        if (value_right < 0.001)
            scale = 0;
        else
            scale = 256.0 / fmax;
        for (double &j: fdraw) {
            j = j * scale * value_right;
        }
        m_graph_right.Update(11, fdraw);

        Sleep(100);
    }
Error_Exit: dlg_para->m_wave.m_startpos = org_start;
    dlg_para->m_wave.m_endpos = org_end;
    isplaying = FALSE;
#ifndef _DEBUG
    UpdateWaveform();
    dlgitem->SetWindowText("");
    m_graph_left.Clear();
    m_graph_right.Clear();
#endif
    dlgitem = GetDlgItem(IDC_BUTTON4);
    dlgitem->SetWindowText("Visualize");
}
