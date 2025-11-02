// KB  2/17/00  \Ken85\Plugin\Wizards\Grid\WizardDialog.cpp
//
// ReSharper disable CppClangTidyConcurrencyMtUnsafe
// ReSharper disable CppClangTidyModernizeLoopConvert
// ReSharper disable CppClangTidyCertErr33C
#include "StdAfx.h"
#include "WizardDialog.h"
#include "SDK/Misc.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "BitmapNo.h"
#include "resource.h"
#include <random>
#include <CommCtrl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

//static float bitsmall[3][3] = {{0.25, 0.5, 0.25}, {0.5, 1, 0.5}, {0.25, 0.5, 0.25}};
//static float bitmed[5][5] = {{0.0, 0.25, 0.25, 0.25, 0}, {0.25, 1, 1, 1, 0.25}, {0.25, 1, 1, 1, 0.25}, {0.25, 1, 1, 1, 0.25}, {0.0, 0.25, 0.25, 0.25, 0}};
namespace {
 float bitbig[7][7] = {
    {0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0}, {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, {0.5, 0.5, 1, 1, 1, 0.5, 0.5}, {0.5, 0.5, 1, 1, 1, 0.5, 0.5}, {0.5, 0.5, 1, 1, 1, 0.5, 0.5}, {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, {0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0}};
}

float smoothstep(const float a, const float b, const float x) {
    if (x < a)
        return 0.F;
    if (x >= b)
        return 1.F;
    const float x1 = (x - a) / (b - a);
    return hash_math::sqr(x1) * (3.F - 2.F * x1);
}

/////////////////////////////////////////////////////////////////////////////
// CWizardDialog dialog

CWizardDialog::CWizardDialog(WizardParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {  // NOLINT(cppcoreguidelines-pro-type-member-init)
    //{{AFX_DATA_INIT(CWizardDialog)
    m_parameters = parameters;
    //    m_grey = 0;
    //}}AFX_DATA_INIT
    // Init dialog from stored registry values
    m_parameters->m_height = GetRegistryValue("Terrain HXT", "Height", 30.0F);
    m_parameters->m_width = GetRegistryValue("Terrain HXT", "Width", 30.0F);
    m_parameters->m_stepheight = GetRegistryValue("Terrain HXT", "Step Height", 5.0F);
    m_parameters->m_stepwidth = GetRegistryValue("Terrain HXT", "Step Width", 5.0F);
    m_parameters->m_orientation = GetRegistryValue("Terrain HXT", "Orientation", 0);
    m_parameters->m_turbscale = GetRegistryValue("Terrain HXT", "Turb Scale", 80.0F);
    m_parameters->m_turbmagnitude = GetRegistryValue("Terrain HXT", "Turb Magnitude", 20.0F);
    m_parameters->m_flatedges = GetRegistryBOOL("Terrain HXT", "Flat Edges", FALSE);
    m_grey = GetRegistryValue("Terrain HXT", "Grey Value", 128);
    m_paintmode = GetRegistryValue("Terrain HXT", "Paint Mode", 0);
    // create my bitmap....
    //	CBitmap *temp = new CBitmap();
    //temp->CreateBitmap(200,200,1,24,nullptr);

    //	temp->LoadBitmap(IDB_BITMAP2);
    //temp->GetBitmapBits(200*200*3,m_bits);
    // init the bitmap...
    m_bitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_bitmap.bmiHeader.biWidth = 200;
    m_bitmap.bmiHeader.biHeight = 200;
    m_bitmap.bmiHeader.biPlanes = 1;
    m_bitmap.bmiHeader.biBitCount = 24;
    m_bitmap.bmiHeader.biCompression = BI_RGB;

    //
    //delete (temp);
    //
    srand(1);  // NOLINT(cert-msc51-cpp)
    InitNoiseTable();
    m_lacunarity = 2.1F;
    m_gain = 0.4678F;
    m_octaves = 6.0F;
    m_smoothfrom = 0.F;
    m_smoothto = 1.F;
    m_scale = 100.F;

    m_seed = 1;
    m_invert = false;
    for (auto &m_bit: m_bits) {
        for (int y = 0; y < 200; ++y) {
            m_bit[y][0] = 0;
            m_bit[y][1] = 0;
            m_bit[y][2] = 0;
        }
    }
    m_imagerect.left = 56;
    m_imagerect.right = 256;
    m_imagerect.top = 20;
    m_imagerect.bottom = 220;
    m_painting = false;
    m_createdbitmap = false;
    //   m_paintmode=0;//paint
}

float CWizardDialog::fBmM(const Vector &p, const float oct, const float lac, const float gain) const {
    float g = gain;
    Vector pp(p);
    // get first...
    float sum = Noise(pp) * g;
    float weight = sum;
    pp *= lac;
    g *= g;
    const int o = (int)oct;
    for (int i = 0; i < o - 1; ++i) {
        sum += Noise(pp) * weight;
        g *= gain;
        pp *= lac;
        weight *= gain;
    }
    return sum;
}

float CWizardDialog::fBm(const Vector &p, const float oct, const float lac, const float gain) const {
    float sum = 0;
    float g = gain;
    Vector pp(p);
    const int o = (int)oct;
    for (int i = 0; i < o; ++i) {
        sum += Noise(pp) * g;
        g *= gain;
        pp *= lac;
    }
    return sum;
}

float CWizardDialog::sineN(const Vector &p, const float oct, const float lac, const float gain) const {
    float sum = 0;
    float g = gain;
    Vector pp(p);
    const int o = (int)oct;
    for (int i = 0; i < o; ++i) {
        sum += hash_math::sin(Noise(pp) * hash_constants::pi_div2) * g;
        g *= gain;
        pp *= lac;
    }
    return sum;
}

float CWizardDialog::Ripples(const Vector &p, const float oct, const float lac, const float gain) const {
    float sum = 0;
    float g = gain;
    Vector pp(p);
    const int o = (int)oct;
    for (int i = 0; i < o; ++i) {
        sum += hash_math::abs(hash_math::sin(pp[0] * Noise(Vector(i + 10)) + pp[1] * Noise(Vector(i + 20)) + Noise(Vector(i)) * hash_constants::pi_div2)) * g;
        g *= gain;
        pp *= lac;
    }
    return sum;
}

float CWizardDialog::turbulence(const Vector &p, const float oct, const float lac, const float gain) const {
    float sum = 0;
    float g = gain;
    Vector pp(p);
    const int o = (int)oct;
    for (int i = 0; i < o; ++i) {
        sum += hash_math::abs(SNoise(pp)) * g;
        g *= gain;
        pp *= lac;
    }
    return sum;
}

float CWizardDialog::turbulenceM(const Vector &p, const float oct, const float lac, const float gain) const {
    float sum = 0;
    float g = gain;
    Vector pp(p);
    sum += (1.F - hash_math::abs(SNoise(pp))) * g;
    g *= gain;
    pp *= lac;
    float weight = sum;
    const int o = (int)oct;
    for (int i = 0; i < o - 1; ++i) {
        sum += (1.F - hash_math::abs(SNoise(pp))) * weight;
        g *= gain;
        pp *= lac;
        weight *= gain;
    }
    return sum;
}

float CWizardDialog::turbulenceM2(const Vector &p, const float oct, const float lac, const float gain) const {
    float sum = 0;
    float g = gain;
    Vector pp(p);
    sum += (1.F - hash_math::abs(SNoise(pp))) * g;
    g *= gain;
    pp *= lac;
    sum *= sum;
    float weight = sum;
    const int o = (int)oct;
    for (int i = 0; i < o - 1; ++i) {
        float signal = 1.F - hash_math::abs(SNoise(pp));
        signal *= signal;
        signal *= weight;
        g *= gain;
        pp *= lac;
        weight *= gain;
        sum += signal;
    }
    return sum;
}

void CWizardDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_HEIGHT, m_parameters->m_height);
    DDV_MinMaxFloat(pDX, m_parameters->m_height, .01F, 100000.0F);
    DDX_Text(pDX, IDC_STEPHEIGHT, m_parameters->m_stepheight);
    DDV_MinMaxFloat(pDX, m_parameters->m_stepheight, .01F, 100000.0F);
    DDX_Text(pDX, IDC_STEPWIDTH, m_parameters->m_stepwidth);
    DDV_MinMaxFloat(pDX, m_parameters->m_stepwidth, .01F, 100000.0F);
    DDX_Text(pDX, IDC_WIDTH, m_parameters->m_width);
    DDV_MinMaxFloat(pDX, m_parameters->m_width, .01F, 100000.0F);
    DDX_Text(pDX, IDC_MAGNITUDE, m_parameters->m_turbmagnitude);
    DDV_MinMaxFloat(pDX, m_parameters->m_turbmagnitude, 0.F, 100000.0F);

    DDX_Check(pDX, IDC_FLATEDGES, m_parameters->m_flatedges);
    DDX_Radio(pDX, IDC_RADIOXY, m_parameters->m_orientation);
    DDX_Radio(pDX, IDC_PAINT, m_paintmode);

    //{{AFX_DATA_MAP(CWizardDialog)
    DDX_Control(pDX, IDC_GREY_VALUE, m_greyctrl);
    DDX_Control(pDX, IDC_FILTER_TYPE, m_filtertype);
    DDX_Control(pDX, IDC_NOISE_TYPE, m_noisetype);
    DDX_Text(pDX, IDC_SCALE1, m_scale);
    DDV_MinMaxFloat(pDX, m_scale, 1.F, 10000.F);
    DDX_Slider(pDX, IDC_GREY_VALUE, m_grey);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
    //{{AFX_MSG_MAP(CWizardDialog)
    ON_WM_DRAWITEM() 
    ON_WM_LBUTTONDOWN() 
    ON_WM_PAINT() 
    ON_WM_LBUTTONUP() 
    ON_WM_MOUSEMOVE() 
    ON_WM_VSCROLL() 
    ON_BN_CLICKED(IDC_RENDERNOISE, &CWizardDialog::OnRendernoise) 
    ON_EN_KILLFOCUS(IDC_SCALE1, &CWizardDialog::OnKillfocusScale)
    ON_EN_KILLFOCUS(IDC_GAIN, &CWizardDialog::OnKillfocusGain) 
    ON_BN_CLICKED(IDC_INVERT, &CWizardDialog::OnInvert) 
    ON_EN_KILLFOCUS(IDC_LACUNARITY, &CWizardDialog::OnKillfocusLacunarity) 
    ON_EN_KILLFOCUS(IDC_OCTAVES, &CWizardDialog::OnKillfocusOctaves)
    ON_EN_KILLFOCUS(IDC_SMOOTH_FROM, &CWizardDialog::OnKillfocusSmoothFrom) 
    ON_EN_KILLFOCUS(IDC_SMOOTH_TO, &CWizardDialog::OnKillfocusSmoothTo) 
    ON_BN_CLICKED(IDC_FILTER, &CWizardDialog::OnFilter) 
    ON_BN_CLICKED(IDC_LOAD, &CWizardDialog::OnLoad)
    ON_EN_KILLFOCUS(IDC_SEED, &CWizardDialog::OnKillfocusSeed) 
    ON_BN_CLICKED(IDC_FILL, &CWizardDialog::OnFill) 
    ON_BN_CLICKED(IDC_RENDERSHAPED, &CWizardDialog::OnRendershaped) 
    ON_BN_CLICKED(IDC_LOWER, &CWizardDialog::OnLower)
    ON_BN_CLICKED(IDC_PAINT, &CWizardDialog::OnModePaint) 
    ON_BN_CLICKED(IDC_RAISE, &CWizardDialog::OnRaise) 
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_GREY_VALUE, &CWizardDialog::OnReleasedcaptureGreyValue)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardDialog message handlers

void CWizardDialog::OnOK() {
    // save dialog values to registry
    CPluginDialog::OnOK();
    SetRegistryValue("Terrain HXT", "Height", m_parameters->m_height);
    SetRegistryValue("Terrain HXT", "Width", m_parameters->m_width);
    SetRegistryValue("Terrain HXT", "Step Height", m_parameters->m_stepheight);
    SetRegistryValue("Terrain HXT", "Step Width", m_parameters->m_stepwidth);
    SetRegistryValue("Terrain HXT", "Orientation", m_parameters->m_orientation);
    SetRegistryValue("Terrain HXT", "Turb Scale", m_parameters->m_turbscale);
    SetRegistryValue("Terrain HXT", "Turb Magnitude", m_parameters->m_turbmagnitude);
    SetRegistryBOOL("Terrain HXT", "Flat Edges", m_parameters->m_flatedges);
    SetRegistryValue("Terrain HXT", "Grey Value", m_grey);
    SetRegistryValue("Terrain HXT", "Paint Mode", m_paintmode);
}

void CWizardDialog::OnCancel() {
    CPluginDialog::OnCancel();
}

/*
BOOL CWizardDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
   //HBITMAP hbm = (HBITMAP)m_bitmap;
   //m_bitmap->SetBitmapBits(200*200*3,m_bits);
   //hbm=m_image.SetBitmap(hbm);
   BOOL success= CDialog::PreCreateWindow(cs);  
   // add the noises....
   char text[255];
   sprintf_s( text, "%.2f", m_smoothto);
   SetDlgItemText( IDC_SMOOTH_TO, text );
   return success;
}
*/
void CWizardDialog::OnDrawItem(const int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CWizardDialog::InitNoiseTable() {
    std::mt19937 mt{5489UL};  // NOLINT(cert-msc51-cpp)
    std::uniform_int_distribution dist(0, RAND_MAX);
    for (int i = MAXX; i-- > 0;) {
        for (int j = MAXY; j-- > 0;) {
            for (int k = MAXZ; k-- > 0;) {
                m_noiz_tbl[i][j][k] = dist(mt) % 1000;
//                m_noiz_tbl[i][j][k] = rand() % 1000;  // NOLINT(concurrency-mt-unsafe)
            }
        }
    }
}

float CWizardDialog::SNoise(const Vector &p) const {
    return 2.F * Noise(p) - 1.F;
}

float CWizardDialog::Noise(const Vector &p) const {
    Vector p_n(p);
    p_n += 15000.0F;
    int ix = fast_ftol_unsigned(p_n.x) % MAXX;
    if (ix < 0)
        ix += MAXX;
    int iy = fast_ftol_unsigned(p_n.y) % MAXY;
    if (iy < 0)
        iy += MAXY;
    int iz = fast_ftol_unsigned(p_n.z) % MAXZ;
    if (iz < 0)
        iz += MAXZ;

    const float ox = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.x - fast_ftol_unsigned(p_n.x)))) * .5F;
    const float oy = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.y - fast_ftol_unsigned(p_n.y)))) * .5F;
    const float oz = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.z - fast_ftol_unsigned(p_n.z)))) * .5F;

    const int ixp = ix + 1 >= MAXX ? 0 : ix + 1;
    const int iyp = iy + 1 >= MAXY ? 0 : iy + 1;
    const int izp = iz + 1 >= MAXZ ? 0 : iz + 1;

    const float A = m_noiz_tbl[ix][iy][iz];
    const float B = m_noiz_tbl[ixp][iy][iz];
    const float C = m_noiz_tbl[ixp][iyp][iz];
    const float D = m_noiz_tbl[ixp][iyp][izp];
    const float E = m_noiz_tbl[ixp][iy][izp];
    const float F = m_noiz_tbl[ix][iy][izp];
    const float G = m_noiz_tbl[ix][iyp][izp];
    const float H = m_noiz_tbl[ix][iyp][iz];
    float t1 = (1.F - ox) * A + ox * B;
    float t2 = (1.F - ox) * H + ox * C;
    const float t3 = (1.F - ox) * F + ox * E;
    const float t4 = (1.F - ox) * G + ox * D;
    t1 = (1.F - oy) * t1 + oy * t2;
    t2 = (1.F - oy) * t3 + oy * t4;
    t1 = (1.F - oz) * t1 + oz * t2;

    t2 = t1 * .001F;
    if (t2 > 0.F)
        return t2;
    return 0.F;
}

float CWizardDialog::getDisplacement(const int x, const int y) const {
    const int px = 200 / m_parameters->m_width * x;
    const int py = 200 / m_parameters->m_height * y;
    return m_bits[199 - (px + 100)][(py + 100)][0] / 255.0F;
}

void CWizardDialog::OnRendernoise() {
    float x;
    const int type = m_noisetype.GetCurSel();
    for (int i = 0; i < 200; ++i) {
        for (int j = 0; j < 200; ++j) {
            const Vector p(i / m_scale, j / m_scale, 0);

            switch (type) {
                case 0:
                    x = fBm(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 1:
                    x = turbulence(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 2:
                    x = fBmM(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 3:
                    x = turbulenceM(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 4:
                    x = turbulenceM2(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 5:
                    x = sineN(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 6:
                    x = Ripples(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;

                default:
                    x = turbulence(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
            }
            x = x > 1.0 ? 1.0 : x;
            if (m_invert)
                x = 1.F - x;
            m_bits[i][j][0] = x * 255;
            m_bits[i][j][1] = x * 255;
            m_bits[i][j][2] = x * 255;
        }
    }
    //m_bitmap->SetBitmapBits(200*200*3,m_bits);
    InvalidateRect(&m_imagerect,TRUE);
}

void CWizardDialog::OnKillfocusScale() {
    char text[255];
    GetDlgItemText(IDC_SCALE1, text, 255);
    const float temp = atof_replace(text);
    m_scale = MIN(10000.0F, MAX(1.F, temp));
    sprintf_s(text, 255, "%.2f", m_scale);
    SetDlgItemText(IDC_SCALE1, text);
}

void CWizardDialog::OnKillfocusGain() {
    char text[255];
    GetDlgItemText(IDC_GAIN, text, 255);
    const float temp = atof_replace(text);
    m_gain = MIN(10.F, MAX(0.01F, temp));
    sprintf_s(text, 255, "%.2f", m_gain);
    SetDlgItemText(IDC_GAIN, text);
}

void CWizardDialog::OnInvert() {
    m_invert = ((CButton *)GetDlgItem(IDC_INVERT))->GetCheck();
}

void CWizardDialog::OnKillfocusLacunarity() {
    char text[255];
    GetDlgItemText(IDC_LACUNARITY, text, 255);
    const float temp = atof_replace(text);
    m_lacunarity = MIN(10000.0F, MAX(1.F, temp));
    sprintf_s(text, 255, "%.2f", m_lacunarity);
    SetDlgItemText(IDC_LACUNARITY, text);
}

void CWizardDialog::OnKillfocusOctaves() {
    char text[255];
    GetDlgItemText(IDC_OCTAVES, text, 255);
    const float temp = atof_replace(text);
    m_octaves = MIN(100.F, MAX(1.F, temp));
    sprintf_s(text, 255, "%.2f", m_octaves);
    SetDlgItemText(IDC_OCTAVES, text);
}

void CWizardDialog::OnKillfocusSmoothFrom() {
    char text[255];
    GetDlgItemText(IDC_SMOOTH_FROM, text, 255);
    const float temp = atof_replace(text);
    m_smoothfrom = MIN(1.F, MAX(0.F, temp));
    sprintf_s(text, 255, "%.2f", m_smoothfrom);
    SetDlgItemText(IDC_SMOOTH_FROM, text);
}

void CWizardDialog::OnKillfocusSmoothTo() {
    char text[255];
    GetDlgItemText(IDC_SMOOTH_TO, text, 255);
    const float temp = atof_replace(text);
    m_smoothto = MIN(1.F, MAX(0.F, temp));
    sprintf_s(text, 255, "%.2f", m_smoothto);
    SetDlgItemText(IDC_SMOOTH_TO, text);
}

BOOL CWizardDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    char text[255];
    sprintf_s(text, 255, "%.2f", m_smoothto);
    SetDlgItemText(IDC_SMOOTH_TO, text);
    sprintf_s(text, 255, "%.2f", m_smoothfrom);
    SetDlgItemText(IDC_SMOOTH_FROM, text);
    sprintf_s(text, 255, "%.2f", m_lacunarity);
    SetDlgItemText(IDC_LACUNARITY, text);
    sprintf_s(text, 255, "%.2f", m_octaves);
    SetDlgItemText(IDC_OCTAVES, text);
    sprintf_s(text, 255, "%.2f", m_gain);
    SetDlgItemText(IDC_GAIN, text);
    sprintf_s(text, 255, "%.2f", m_scale);
    SetDlgItemText(IDC_SCALE1, text);
    sprintf_s(text, 255, "%d", m_seed);
    SetDlgItemText(IDC_SEED, text);

    m_noisetype.AddString("fBm");
    m_noisetype.AddString("Turbulence");
    m_noisetype.AddString("fBm- multi");
    m_noisetype.AddString("Turbulence - multi");
    m_noisetype.AddString("Turbulence - multi 2");
    m_noisetype.AddString("Sine");
    m_noisetype.AddString("SineRipples");

    m_noisetype.SetCurSel(0);
    m_filtertype.AddString("Make Mountain");
    m_filtertype.AddString("Blur");
    m_filtertype.AddString("Sharpen");
    m_filtertype.AddString("Erode");
    m_filtertype.AddString("Dilate");
    m_filtertype.AddString("Noise");
    m_filtertype.AddString("Raise");
    m_filtertype.AddString("Lower");
    m_filtertype.AddString("Weather");
    m_filtertype.AddString("Crater");

    m_filtertype.SetCurSel(0);
    m_greyctrl.SetRange(0, 255,TRUE);
    m_greyctrl.SetPos(255 - m_grey);
    CString sText;
    sText.Format("%d", m_grey);
    SetDlgItemText(IDC_STATICGREY, sText);
    OnRendernoise();
    return TRUE; // return TRUE unless you set the focus to a control
}

void CWizardDialog::filterMountain() {
    for (int x = 0; x < 200; ++x)
        for (int y = 0; y < 200; ++y) {
            const float dx = (100.F - x) / 110.0F;
            const float dy = (100.F - y) / 110.0F;
            float squ = hash_math::sqrt(dx * dx + dy * dy);
            if (squ > 1.F)
                squ = 1.F;
            squ = hash_math::sin(squ * hash_constants::pi_div2);

            m_bits[x][y][0] *= 1.F - squ;
            m_bits[x][y][1] *= 1.F - squ;
            m_bits[x][y][2] *= 1.F - squ;
        }
}

void CWizardDialog::filterScale(const float scalar) {
    for (auto &m_bit: m_bits) {
        for (int y = 0; y < 200; ++y) {
            float dx = m_bit[y][0] / scalar;
            dx = m_bit[y][0] + dx;
            m_bit[y][0] = dx > 255 ? 255 : dx;
            m_bit[y][1] = dx > 255 ? 255 : dx;
            m_bit[y][2] = dx > 255 ? 255 : dx;
        }
    }
}

void CWizardDialog::filterNoise() {
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 200; ++y) {
            const Vector p(x, y, 0.F);
            float mul = Noise(p) * 10.F;
            mul += m_bits[x][y][0];
            m_bits[x][y][0] = mul;
            m_bits[x][y][1] = mul;
            m_bits[x][y][2] = mul;
        }
    }
}

void CWizardDialog::filterKernal(const int type) {
    BYTE temp[200][200]{};
    int x, y;
    for (x = 0; x < 200; ++x) {
        for (y = 0; y < 200; ++y) {
            temp[x][y] = m_bits[x][y][0];
        }
    }
    for (x = 1; x < 199; ++x)
        for (y = 1; y < 199; ++y) {
            int tc = 0;
            if (type == 1) {
                for (int c = -1; c < 2; ++c)
                    for (int d = -1; d < 2; ++d) {
                        tc += temp[x + c][y + d];
                    }
                tc /= 9;
            } else {
                tc += temp[x][y] * 5;
                tc -= temp[x + 1][y + 1];
                tc -= temp[x - 1][y + 1];
                tc -= temp[x - 1][y - 1];
                tc -= temp[x + 1][y - 1];
                tc = tc > 255 ? 255 : tc;
                tc = tc < 0 ? 0 : tc;
            }
            m_bits[x][y][0] = (BYTE)tc;
            m_bits[x][y][1] = (BYTE)tc;
            m_bits[x][y][2] = (BYTE)tc;
        }
}

void CWizardDialog::filterErode() {
    BYTE temp[200][200]{};
    int x, y;
    for (x = 0; x < 200; ++x) {
        for (y = 0; y < 200; ++y) {
            temp[x][y] = m_bits[x][y][0];
        }
    }
    int tc = 0;
    for (x = 0; x < 200; ++x)
        for (y = 0; y < 200; ++y) {
            BYTE minP = 255;
            for (int c = -1; c < 2; ++c)
                for (int d = -1; d < 2; ++d) {
                    if (x + c > 0 && x + c < 200 && y + d > 0 && y + d < 200)
                        tc = temp[x + c][y + d];
                    if (tc < minP)
                        minP = tc;
                }
            m_bits[x][y][0] = minP;
            m_bits[x][y][1] = minP;
            m_bits[x][y][2] = minP;
        }
}

void CWizardDialog::filterDilate() {
    BYTE temp[200][200]{};
    int x, y;
    for (x = 0; x < 200; ++x)
        for (y = 0; y < 200; ++y) {
            temp[x][y] = m_bits[x][y][0];
        }
    int tc = 0;
    for (x = 0; x < 200; ++x)
        for (y = 0; y < 200; ++y) {
            BYTE minP = 0;
            for (int c = -1; c < 2; ++c)
                for (int d = -1; d < 2; ++d) {
                    if (x + c > 0 && x + c < 200 && y + d > 0 && y + d < 200)
                        tc = temp[x + c][y + d];
                    if (tc > minP)
                        minP = tc;
                }
            m_bits[x][y][0] = minP;
            m_bits[x][y][1] = minP;
            m_bits[x][y][2] = minP;
        }
}

void CWizardDialog::filterWeather() {
    int newx = 0;
    int newy = 0;
    for (int i = 0; i < 21075; ++i) {
        int count = 0;
        int posx = rand() / (float)RAND_MAX * 198 + 1;
        int posy = rand() / (float)RAND_MAX * 198 + 1;
        do {
            const BYTE mv = m_bits[posx][posy][0];
            int smallest = 0;
            for (int x = -1; x < 2; ++x)
                for (int y = -1; y < 2; ++y) {
                    const int grad = m_bits[posx + x][posy + y][0] - mv;
                    if (grad < 0 && (x != 0 || y != 0))
                        if (grad < smallest) {
                            smallest = grad;
                            newx = posx + x;
                            newy = posy + y;
                        }
                }
            // subtract a little from our previous pos;
            if (smallest == 0) {
                // we haven't moved,so deposit
                if (m_bits[posx][posy][0] < 249) {
                    m_bits[posx][posy][0] += (BYTE)1;
                    m_bits[posx][posy][1] += (BYTE)1;
                    m_bits[posx][posy][2] += (BYTE)1;
                }
                count = 50;
            } else {
                if (m_bits[posx][posy][0] > 6) {
                    m_bits[posx][posy][0] -= (BYTE)1;
                    m_bits[posx][posy][1] -= (BYTE)1;
                    m_bits[posx][posy][2] -= (BYTE)1;
                }
                newx = newx > 0 ? newx : 0;
                newy = newy > 0 ? newy : 0;
                newx = newx < 200 ? newx : 198;
                newy = newy < 200 ? newy : 198;

                posx = newx;
                posy = newy;
            }
            count++;
        } while (count < 40);
    }
}

void CWizardDialog::OnFilter() {
    switch (m_filtertype.GetCurSel()) {
        case 0:
            filterMountain();
            break;
        case 1:
            filterKernal(1);
            break;
        case 2:
            filterKernal(0);
            break;
        case 3:
            filterErode();
            break;
        case 4:
            filterDilate();
            break;
        case 5:
            filterNoise();
            break;
        case 6:
            filterScale(10.F);
            break;
        case 7:
            filterScale(-10.F);
            break;
        case 8:
            filterWeather();
            break;

        default:
            filterMountain();
    }
    //	m_bitmap->SetBitmapBits(200*200*3,m_bits);
    InvalidateRect(&m_imagerect,FALSE);
}

void CWizardDialog::OnLoad() {
    // file selection dialog....
    auto choose = CFileDialog(true);
    if (choose.DoModal() == IDOK) {
        const CString nom = choose.GetPathName();
        const String nam(nom);
        HBitmapNode *tempbitmap = HBitmapNode::New();
        if (const int loaded = tempbitmap->LoadFrame(nam); loaded != HBitmapNode::LOAD_FAILED) {
            const float xstep = tempbitmap->GetWidth() / 200.F;
            const float ystep = tempbitmap->GetHeight() / 200.F;
            float y = 0.F;
            for (int i = 199; i >= 00; i--) {
                float x = 0;
                for (int j = 0; j < 200; ++j) {
                    RGBFloat diffuse;
                    tempbitmap->ReadPixel((int)x, (int)y, diffuse);
                    x += xstep;
                    const UBYTE luminance = FLOATTOBYTE(diffuse.GetLuminance());
                    m_bits[i][j][0] = luminance; //v11.1 this was all Green() was that a copy paste error?
                    m_bits[i][j][1] = luminance;
                    m_bits[i][j][2] = luminance;
                }
                char temp[22];
                sprintf_s(temp, 22, "%d", i);
                y += ystep;
            }
        }
        delete tempbitmap;
    }
    //	m_bitmap->SetBitmapBits(200*200*3,m_bits);
    InvalidateRect(&m_imagerect,FALSE);
//    delete choose;
}

void CWizardDialog::OnLButtonDown(const UINT nFlags, const CPoint point) {
    const int x = point.x;
    //char stri[100];
    //sprintf_s(stri,"x= %d : y= %d",x,y);
    //CString temp(stri);
    //MessageBox(temp,"hit",MB_OK);

    if (const int y = point.y; x > 56 && x < 256 && y > 20 && y < 220) {
        m_painting = true;
        switch (m_paintmode) {
            case 0:
                PaintSplodge(x - 56, 200 - (y - 20));
                break;
            case 1:
                PaintRaise(x - 56, 200 - (y - 20));
                break;
            case 2:
                PaintLower(x - 56, 200 - (y - 20));
                break;
            default:;
        }
        ///		m_bitmap->SetBitmapBits(200*200*3,m_bits);
        InvalidateRect(&m_imagerect,FALSE);
    } else {
        CDialog::OnLButtonDown(nFlags, point);
    }
}

void CWizardDialog::OnKillfocusSeed() {
    char text[255];
    GetDlgItemText(IDC_SEED, text, 255);
    m_seed = MIN(100000, MAX(0, atoi_replace(text)));
    sprintf_s(text, 255, "%d", m_seed);
    SetDlgItemText(IDC_SEED, text);
    srand(m_seed);
    InitNoiseTable();
}

void CWizardDialog::OnPaint() {
    //CDC* dc = CDC::FromHandle(lpDrawItemStruct->hDC);
    //CDC mdc; // memory DC
    //mdc.CreateCompatibleDC(&dc);
    //	CBitmap* pOld = mdc.SelectObject(m_bitmap);
    //	StretchDIBits(hDC, 56, 20, (WORD)200, 200, 0, 0, (WORD)200,	(WORD)-200, m_bits, &m_bitmap, DIB_RGB_COLORS,SRCCOPY);
    //BOOL bRet = dc.BitBlt(56,20,200,200,&mdc,0,0,SRCCOPY);
    //	mdc.SelectObject(pOld);
    const CPaintDC dc(this); // device context for painting
    const HDC hDC = dc.GetSafeHdc();
    if (!m_createdbitmap) {
        m_hbitmap = CreateCompatibleBitmap(hDC, 200, 200);
        m_createdbitmap = true;
    }
    const HDC hMemDC = CreateCompatibleDC(hDC);
    SetDIBits(hDC, m_hbitmap, 0, 200, m_bits, &m_bitmap, DIB_RGB_COLORS);
    auto *const hBitmap = (HBITMAP)SelectObject(hMemDC, m_hbitmap);
    BitBlt(hDC, 56, 20, 200, 200, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hBitmap);
    DeleteDC(hMemDC);

    // Do not call CDialog::OnPaint() for painting messages
}

void CWizardDialog::PaintSplodge(const int x, const int y) {
    const int dx = y - 2;
    const int dy = x - 2;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            const float m = bitbig[i][j];
            const float b = m * m_grey;
            const float o = m_bits[dx + i][dy + j][0] * (1.F - m);
            m_bits[dx + i][dy + j][0] = (BYTE)(b + o);
            m_bits[dx + i][dy + j][1] = (BYTE)(b + o);
            m_bits[dx + i][dy + j][2] = (BYTE)(b + o);
        }
    }
}

void CWizardDialog::PaintRaise(const int x, const int y) {
    const int dx = y - 2;
    const int dy = x - 2;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            const float m = bitbig[i][j];
            const float b = m * MIN(m_bits[dx + i][dy + j][0] + 2, 250);
            const float o = m_bits[dx + i][dy + j][0] * (1.F - m);
            m_bits[dx + i][dy + j][0] = (BYTE)(b + o);
            m_bits[dx + i][dy + j][1] = (BYTE)(b + o);
            m_bits[dx + i][dy + j][2] = (BYTE)(b + o);
        }
    }
}

void CWizardDialog::PaintLower(const int x, const int y) {
    const int dx = y - 2;
    const int dy = x - 2;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            const float m = bitbig[i][j];
            const float b = m * MAX(m_bits[dx + i][dy + j][0] - 2, 3);
            const float o = m_bits[dx + i][dy + j][0] * (1.F - m);
            m_bits[dx + i][dy + j][0] = (BYTE)(b + o);
            m_bits[dx + i][dy + j][1] = (BYTE)(b + o);
            m_bits[dx + i][dy + j][2] = (BYTE)(b + o);
        }
    }
}

void CWizardDialog::OnLButtonUp(const UINT nFlags, const CPoint point) {
    const int x = point.x;
    if (const int y = point.y; x > 56 && x < 256 && y > 20 && y < 220) {
        m_painting = false;
        //		m_bitmap->SetBitmapBits(200*200*3,m_bits);
        InvalidateRect(&m_imagerect,FALSE);
    } else {
        CDialog::OnLButtonUp(nFlags, point);
    }
}

void CWizardDialog::OnMouseMove(const UINT nFlags, const CPoint point) {
    if (m_painting) {
        const int x = point.x;
        if (const int y = point.y; x > 56 && x < 256 && y > 20 && y < 220) {
            switch (m_paintmode) {
                case 0:
                    PaintSplodge(x - 56, 200 - (y - 20));
                    break;
                case 1:
                    PaintRaise(x - 56, 200 - (y - 20));
                    break;
                case 2:
                    PaintLower(x - 56, 200 - (y - 20));
                    break;
                default:
                    break;
            }
            //		m_bitmap->SetBitmapBits(200*200*3,m_bits);
            InvalidateRect(&m_imagerect,FALSE);
        } else {
            m_painting = false;
        }
    } else {
        CDialog::OnMouseMove(nFlags, point);
    }
}

void CWizardDialog::OnReleasedcaptureGreyValue(NMHDR *pNMHDR, LRESULT *pResult) {
    m_grey = 255 - m_greyctrl.GetPos();
    *pResult = 0;
}

void CWizardDialog::OnFill() {
    for (auto &m_bit: m_bits) {
        for (int y = 0; y < 200; ++y) {
            m_bit[y][0] = m_grey;
            m_bit[y][1] = m_grey;
            m_bit[y][2] = m_grey;
        }
    }
    InvalidateRect(&m_imagerect,FALSE);
}

void CWizardDialog::OnRendershaped() {
    float x;
    const int type = m_noisetype.GetCurSel();
    for (int i = 0; i < 200; ++i)
        for (int j = 0; j < 200; ++j) {
            const Vector p(i / m_scale, j / m_scale, 0.F);

            switch (type) {
                case 0:
                    x = fBm(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 1:
                    x = turbulence(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 2:
                    x = fBmM(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 3:
                    x = turbulenceM(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 4:
                    x = turbulenceM2(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;
                case 5:
                    x = sineN(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
                    break;

                default:
                    x = turbulence(p, m_octaves, m_lacunarity, m_gain);
                    x = smoothstep(m_smoothfrom, m_smoothto, x);
            }
            x = x > 1.F ? 1.F : x;
            if (m_invert)
                x = 1.F - x;
            float mul = m_bits[i][j][0] / 255.0F;
            mul *= x;
            m_bits[i][j][0] = mul * 255;
            m_bits[i][j][1] = mul * 255;
            m_bits[i][j][2] = mul * 255;
        }
    InvalidateRect(&m_imagerect,TRUE);
}

void CWizardDialog::OnLower() {
    m_paintmode = 2;
}

void CWizardDialog::OnModePaint() {
    m_paintmode = 0;
}

void CWizardDialog::OnRaise() {
    m_paintmode = 1;
}

void CWizardDialog::OnVScroll(const UINT nSBCode, const UINT nPos, CScrollBar *pScrollBar) {
    CString sText;
    m_grey = 255 - m_greyctrl.GetPos();
    sText.Format("%d", m_grey);
    SetDlgItemText(IDC_STATICGREY, sText);
    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

