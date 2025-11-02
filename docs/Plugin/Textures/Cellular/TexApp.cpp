// Dan  3/24/2003  \DanLP105\Plugin\Textures\Cellular\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureApp

BEGIN_MESSAGE_MAP(CTextureApp, CWinApp)
        //{{AFX_MSG_MAP(CTextureApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureApp construction

CTextureApp::CTextureApp() = default;

BOOL CTextureApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    string.LoadString(IDS_AMPLITUDE);
    m_amplitudeinfo = HFloatPropertyInfo::New(string, "Amplitude");
    m_amplitudeinfo->SetDefaultValue(1.F);
    m_amplitudeinfo->SetMinValue(0.F);
    m_amplitudeinfo->SetMaxValue(100.F);
    m_amplitudeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FREFLECT);
    m_frefinfo = HFloatPropertyInfo::New(string, "FReflect");
    m_frefinfo->SetDefaultValue(0.F);
    m_frefinfo->SetMinValue(0.F);
    m_frefinfo->SetMaxValue(100.F);
    m_frefinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FOPAC);
    m_foinfo = HFloatPropertyInfo::New(string, "FOpacity");
    m_foinfo->SetDefaultValue(0.F);
    m_foinfo->SetMinValue(0.F);
    m_foinfo->SetMaxValue(100.F);
    m_foinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BREFLECT);
    m_brefinfo = HFloatPropertyInfo::New(string, "BReflect");
    m_brefinfo->SetDefaultValue(0.F);
    m_brefinfo->SetMinValue(0.F);
    m_brefinfo->SetMaxValue(100.F);
    m_brefinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BOPAC);
    m_boinfo = HFloatPropertyInfo::New(string, "BOpacity");
    m_boinfo->SetDefaultValue(0.F);
    m_boinfo->SetMinValue(0.F);
    m_boinfo->SetMaxValue(100.F);
    m_boinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_NOISE);
    m_noiseinfo = HFloatPropertyInfo::New(string, "Noise");
    m_noiseinfo->SetDefaultValue(0.F);
    m_noiseinfo->SetMinValue(0.F);
    m_noiseinfo->SetMaxValue(100.F);
    m_noiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FREQ);
    m_freqinfo = HFloatPropertyInfo::New(string, "Frequency");
    m_freqinfo->SetDefaultValue(0.F);
    m_freqinfo->SetMinValue(0.F);
    m_freqinfo->SetMaxValue(100.F);
    m_freqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BUMP);
    m_bumpinfo = HFloatPropertyInfo::New(string, "Bump");
    m_bumpinfo->SetDefaultValue(0.F);
    m_bumpinfo->SetMinValue(0.F);
    m_bumpinfo->SetMaxValue(100.F);
    m_bumpinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_MIX);
    m_mixinfo = HFloatPropertyInfo::New(string, "Mix");
    m_mixinfo->SetDefaultValue(100.F);
    m_mixinfo->SetMinValue(0.F);
    m_mixinfo->SetMaxValue(100.F);
    m_mixinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_offsetinfo = HTranslatePropertyInfo::New(string, "Offset");
    m_offsetinfo->GetX()->SetMinValue(-100.F);
    m_offsetinfo->GetX()->SetMaxValue(100.F);
    m_offsetinfo->GetY()->SetMinValue(-100.F);
    m_offsetinfo->GetY()->SetMaxValue(100.F);
    m_offsetinfo->GetZ()->SetMinValue(-100.F);
    m_offsetinfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_SCALE);
    m_scaleinfo = HScalePropertyInfo::New(string, "Scale");
    m_scaleinfo->GetX()->SetMinValue(-100.F);
    m_scaleinfo->GetX()->SetMaxValue(100.F);
    m_scaleinfo->GetY()->SetMinValue(-100.F);
    m_scaleinfo->GetY()->SetMaxValue(100.F);
    m_scaleinfo->GetZ()->SetMinValue(-100.F);
    m_scaleinfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_USECURRENT);
    m_usebackinfo = HBoolPropertyInfo::New(string, "UseCurrent");
    m_usebackinfo->SetDefaultValue(FALSE);
    m_usebackinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BCOLOR);
    m_bcolorinfo = HColorPropertyInfo::New(string, "BColor");
    m_bcolorinfo->GetRed()->SetDefaultValue(1.F);
    m_bcolorinfo->GetGreen()->SetDefaultValue(1.F);
    m_bcolorinfo->GetBlue()->SetDefaultValue(1.F);

    string.LoadString(IDS_FCOLOR);
    m_fcolorinfo = HColorPropertyInfo::New(string, "FColor");
    m_fcolorinfo->GetRed()->SetDefaultValue(0.F);
    m_fcolorinfo->GetGreen()->SetDefaultValue(0.F);
    m_fcolorinfo->GetBlue()->SetDefaultValue(0.F);

    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_amplitudeinfo;
    delete m_frefinfo;
    delete m_foinfo;
    delete m_brefinfo;
    delete m_boinfo;
    delete m_noiseinfo;
    delete m_freqinfo;
    delete m_bumpinfo;
    delete m_mixinfo;
    delete m_offsetinfo;
    delete m_scaleinfo;
    delete m_bcolorinfo;
    delete m_fcolorinfo;
    delete m_usebackinfo;

    return CPluginApp::ExitInstance();
}

void CTextureApp::InitNoiseTable() {
    srand(17);  // NOLINT(cert-msc51-cpp)
    for (int i = MAXX; i-- > 0;) {
        for (int j = MAXY; j-- > 0;) {
            for (int k = MAXZ; k-- > 0;) {
                m_noiz_tbl[i][j][k] = rand() % 1000;  // NOLINT(concurrency-mt-unsafe)
            }
        }
    }
}

float CTextureApp::Noise(const Vector p) const {
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

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
