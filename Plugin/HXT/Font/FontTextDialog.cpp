//

#include "StdAfx.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "FontTextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

BOOL IsFontUsable(unsigned char *name);

/////////////////////////////////////////////////////////////////////////////
// CFontTextDialog dialog

CFontTextDialog::CFontTextDialog(FontParameters *parameters): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(CFontTextDialog)
    m_parameters = parameters;
    //}}AFX_DATA_INIT
    // Init dialog from stored registry values
    const String text = GetRegistryString("Font HXT", "Text", "A");
    const String face = GetRegistryString("Font HXT", "Face", "Arial");
    const String style = GetRegistryString("Font HXT", "Style", "Regular");
    m_parameters->m_buildtext = CString(text.Get());
    m_parameters->m_facename = CString(face.Get());
    m_parameters->m_style = CString(style.Get());
    m_parameters->m_fronts = GetRegistryValue("Font HXT", "Fronts", TRUE);
    m_parameters->m_sides = GetRegistryValue("Font HXT", "Sides", TRUE);
    m_parameters->m_backs = GetRegistryValue("Font HXT", "Backs", FALSE);
    m_parameters->m_bevfronts = GetRegistryValue("Font HXT", "BevFronts", TRUE);
    m_parameters->m_bevsides = GetRegistryValue("Font HXT", "BevSides", FALSE);
    m_parameters->m_bevbacks = GetRegistryValue("Font HXT", "BevBacks", FALSE);
    m_parameters->m_bevround = GetRegistryValue("Font HXT", "BevRound", FALSE);
    m_parameters->m_bevinward = GetRegistryValue("Font HXT", "BevInward", TRUE);
    m_parameters->m_subdivkind = GetRegistryValue("Font HXT", "SubdivKind", FontParameters::SUB_NONE);
    m_parameters->m_bevamt = GetRegistryValue("Font HXT", "BevAmount", 2.0F);
    if (!m_parameters->m_fronts)
        m_parameters->m_bevfronts = FALSE;
    if (!m_parameters->m_sides)
        m_parameters->m_bevsides = FALSE;
    if (!m_parameters->m_backs)
        m_parameters->m_bevbacks = FALSE;
    m_parameters->m_depth = GetRegistryValue("Font HXT", "ExtrudeDepthFont", 2.5F);
}

void CFontTextDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_FONTTEXT, m_parameters->m_buildtext);
    DDX_LBString(pDX, IDC_FONTLIST, m_parameters->m_facename);
    DDX_CBString(pDX, IDC_FONTSTYLE, m_parameters->m_style);
    DDX_Check(pDX, IDC_FRONTS, m_parameters->m_fronts);
    DDX_Check(pDX, IDC_SIDES, m_parameters->m_sides);
    DDX_Check(pDX, IDC_BACKS, m_parameters->m_backs);
    DDX_Check(pDX, IDC_BEVEL_FRONTS, m_parameters->m_bevfronts);
    DDX_Check(pDX, IDC_BEVEL_SIDES, m_parameters->m_bevsides);
    DDX_Check(pDX, IDC_BEVEL_BACKS, m_parameters->m_bevbacks);
    int roundradio = m_parameters->m_bevround ? 0 : 1;
    DDX_Radio(pDX, IDC_BEVEL_ROUND, roundradio);
    m_parameters->m_bevround = roundradio == 0;
    DDX_Check(pDX, IDC_BACKS, m_parameters->m_backs);
    int inwardradio = m_parameters->m_bevinward ? 0 : 1;
    DDX_Radio(pDX, IDC_BEVEL_INWARD, inwardradio);
    m_parameters->m_bevinward = inwardradio == 0;
    DDX_Text(pDX, IDC_BEVAMOUNT, m_parameters->m_bevamt);
    DDV_MinMaxFloat(pDX, m_parameters->m_bevamt, 0.0F, 1000.0F);
    int subdivradio = m_parameters->m_subdivkind;
    DDX_Radio(pDX, IDC_SUB_NONE, subdivradio);
    m_parameters->m_subdivkind = subdivradio;
    DDX_Text(pDX, IDC_EDIT1, m_parameters->m_depth);
    DDV_MinMaxFloat(pDX, m_parameters->m_depth, 0.01F, 10000.0F);
    //{{AFX_DATA_MAP(CFontTextDialog)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontTextDialog, CDialog)
    //{{AFX_MSG_MAP(CFontTextDialog)
    ON_LBN_SELCHANGE(IDC_FONTLIST, &CFontTextDialog::OnSelchangeFontlist)
    ON_EN_CHANGE(IDC_FONTTEXT, &CFontTextDialog::OnChangeFonttext)
    ON_WM_PAINT()
    ON_CBN_SELCHANGE(IDC_FONTSTYLE, &CFontTextDialog::OnSelchangeFontstyle)
    ON_BN_CLICKED(IDC_BEVEL_BACKS, &CFontTextDialog::OnBevelBacks)
    ON_BN_CLICKED(IDC_BEVEL_FRONTS, &CFontTextDialog::OnBevelFronts)
    ON_BN_CLICKED(IDC_BEVEL_SIDES, &CFontTextDialog::OnBevelSides)
    ON_BN_CLICKED(IDC_BACKS, &CFontTextDialog::OnBacks)
    ON_BN_CLICKED(IDC_FRONTS, &CFontTextDialog::OnFronts)
    ON_BN_CLICKED(IDC_SIDES, &CFontTextDialog::OnSides)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontTextDialog message handlers

void CFontTextDialog::OnOK() {
    CPluginDialog::OnOK();
    // save dialog values to registry
    const String text((LPCTSTR)m_parameters->m_buildtext);
    const String face((LPCTSTR)m_parameters->m_facename);
    const String style((LPCTSTR)m_parameters->m_style);
    SetRegistryString("Font HXT", "Text", text);
    SetRegistryString("Font HXT", "Face", face);
    SetRegistryString("Font HXT", "Style", style);
    SetRegistryValue("Font HXT", "Fronts", m_parameters->m_fronts);
    SetRegistryValue("Font HXT", "Sides", m_parameters->m_sides);
    SetRegistryValue("Font HXT", "Backs", m_parameters->m_backs);
    SetRegistryValue("Font HXT", "BevFronts", m_parameters->m_bevfronts);
    SetRegistryValue("Font HXT", "BevSides", m_parameters->m_bevsides);
    SetRegistryValue("Font HXT", "BevBacks", m_parameters->m_bevbacks);
    SetRegistryValue("Font HXT", "BevRound", m_parameters->m_bevround);
    SetRegistryValue("Font HXT", "BevInward", m_parameters->m_bevinward);
    SetRegistryValue("Font HXT", "BevAmount", m_parameters->m_bevamt);
    SetRegistryValue("Font HXT", "SubdivKind", m_parameters->m_subdivkind);
    SetRegistryValue("Font HXT", "ExtrudeDepth", m_parameters->m_depth);
}

int CALLBACK EnumFontFamProc(ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm, const int nFontType, const LPARAM lParam) {
    const CFontTextDialog *f = (CFontTextDialog *)lParam;
    auto *lb = (CListBox *)f->GetDlgItem(IDC_FONTLIST);

    if (nFontType & TRUETYPE_FONTTYPE)
        lb->AddString(lpelf->elfLogFont.lfFaceName);
    return 1;
}

BOOL CFontTextDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    auto *lb = (CListBox *)GetDlgItem(IDC_FONTLIST);

    const CClientDC dc(this);
    ::EnumFontFamilies(dc, nullptr, (FONTENUMPROC)EnumFontFamProc, (LPARAM)this);

    int i = lb->FindStringExact(-1, m_parameters->m_facename);
    if (i == LB_ERR)
        i = 0;
    lb->SetCurSel(i);
    OnSelchangeFontlist(); // the previous call doesn't cause this

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CFontTextDialog::OnSelchangeFontlist() {
    const CListBox *lb = (CListBox *)GetDlgItem(IDC_FONTLIST);
    if (lb == nullptr)
        return;
    const int i = lb->GetCurSel();
    if (i != LB_ERR) {
        lb->GetText(i, m_parameters->m_facename);
        UpdateSample();
    }
}

void CFontTextDialog::OnSelchangeFontstyle() {
    const CComboBox *cb = (CComboBox *)GetDlgItem(IDC_FONTSTYLE);
    if (cb == nullptr)
        return;
    const int i = cb->GetCurSel();
    if (i != CB_ERR) {
        cb->GetLBText(i, m_parameters->m_style);
        UpdateSample();
    }
}

void CFontTextDialog::UpdateSample() {
    CRect r = PreviewRect();
    int sz = r.Height();
    if (r.Width() < sz)
        sz = r.Width();
    sz -= 10;
    if (sz > 20) {
        if ((HFONT)m_dispfont != nullptr)
            m_dispfont.DeleteObject();

        m_dispfont.CreateFont(-sz, 0, 0, 0, m_parameters->FaceWeight(), m_parameters->IsItalicFace(), 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_parameters->m_facename);
    }
    InvalidateRect(r);
    UpdateWindow();
}

// Return area suitable for displaying
// a preview of one letter.
CRect CFontTextDialog::PreviewRect() const {
    const CWnd *refw = GetDlgItem(IDC_FONTSTYLE);
    CRect refr;
    CRect viewr;
    refw->GetWindowRect(&refr);
    ScreenToClient(&refr);
    GetWindowRect(&viewr);
    ScreenToClient(&viewr);
    CRect ans = viewr;
    ans.top = refr.bottom;
    ans.right = refr.right;
    ans.DeflateRect(30, 30, 30, 30);
    if (ans.bottom < ans.top)
        ans.bottom = ans.top;
    if (ans.right < ans.left)
        ans.right = ans.left;
    return ans;
}

void CFontTextDialog::OnChangeFonttext() {
    CRect r = PreviewRect();
    if (r.Width() > 0 && r.Height() > 0) {
        InvalidateRect(r);
        UpdateWindow();
    }
}

void CFontTextDialog::OnPaint() {
    CPaintDC dc(this); // device context for painting

    if ((HFONT)m_dispfont == nullptr)
        return;

    CRect r = PreviewRect();

    const CEdit *e = (CEdit *)GetDlgItem(IDC_FONTTEXT);
    CString s;
    e->GetWindowText(s);
    s.TrimLeft();
    if (s.GetLength() == 0)
        return;
    const CString firstchar(s[0]);

    dc.IntersectClipRect(r);
    dc.SelectObject(m_dispfont);
    dc.DrawText(firstchar, r, DT_CENTER);
    dc.SelectObject(GetStockObject(SYSTEM_FONT));

    // Do not call CDialog::OnPaint() for painting messages
}

// Enable backs if back bevels just enabled
void CFontTextDialog::OnBevelBacks() {
    const CButton *cb = (CButton *)GetDlgItem(IDC_BEVEL_BACKS);
    if (cb->GetCheck()) {
        auto *bb = (CButton *)GetDlgItem(IDC_BACKS);
        if (!bb->GetCheck())
            bb->SetCheck(1);
    }
}

// Enable fronts if front bevels just enabled
void CFontTextDialog::OnBevelFronts() {
    const CButton *cb = (CButton *)GetDlgItem(IDC_BEVEL_FRONTS);
    if (cb->GetCheck()) {
        auto *fb = (CButton *)GetDlgItem(IDC_FRONTS);
        if (!fb->GetCheck())
            fb->SetCheck(1);
    }
}

// Enable sides if side bevels just enabled
void CFontTextDialog::OnBevelSides() {
    const CButton *cb = (CButton *)GetDlgItem(IDC_BEVEL_SIDES);
    if (cb->GetCheck()) {
        auto *sb = (CButton *)GetDlgItem(IDC_SIDES);
        if (!sb->GetCheck())
            sb->SetCheck(1);
    }
}

// Disable back bevels if backs just disabled
void CFontTextDialog::OnBacks() {
    const CButton *cb = (CButton *)GetDlgItem(IDC_BACKS);
    if (!cb->GetCheck()) {
        auto *bb = (CButton *)GetDlgItem(IDC_BEVEL_BACKS);
        if (bb->GetCheck())
            bb->SetCheck(0);
    }
}

// Disable front bevels if fronts just disabled
void CFontTextDialog::OnFronts() {
    const CButton *cb = (CButton *)GetDlgItem(IDC_FRONTS);
    if (!cb->GetCheck()) {
        auto *fb = (CButton *)GetDlgItem(IDC_BEVEL_FRONTS);
        if (fb->GetCheck())
            fb->SetCheck(0);
    }
}

// Disable side bevels if sides just disabled
void CFontTextDialog::OnSides() {
    const CButton *cb = (CButton *)GetDlgItem(IDC_SIDES);
    if (!cb->GetCheck()) {
        auto *sb = (CButton *)GetDlgItem(IDC_BEVEL_SIDES);
        if (sb->GetCheck())
            sb->SetCheck(0);
    }
}
