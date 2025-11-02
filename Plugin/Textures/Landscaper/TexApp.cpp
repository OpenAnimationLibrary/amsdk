// Dan  3/24/2003  \DanLP105\Plugin\Textures\Landscaper\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"
#include "F_Protos.h"
#include "resource.h"		// main symbols

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
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;

    string.LoadString(IDS_FCOLOR1);
    m_fcolor1info = HColorPropertyInfo::New(string, "flatcolor1");
    m_fcolor1info->GetRed()->SetDefaultValue(0.F);
    m_fcolor1info->GetGreen()->SetDefaultValue(0.5F);
    m_fcolor1info->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_FCOLOR2);
    m_fcolor2info = HColorPropertyInfo::New(string, "flatcolor2");
    m_fcolor2info->GetRed()->SetDefaultValue(0.F);
    m_fcolor2info->GetGreen()->SetDefaultValue(0.5F);
    m_fcolor2info->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_FCOLOR3);
    m_fcolor3info = HColorPropertyInfo::New(string, "flatcolor3");
    m_fcolor3info->GetRed()->SetDefaultValue(0.F);
    m_fcolor3info->GetGreen()->SetDefaultValue(0.5F);
    m_fcolor3info->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_FOCT);
    m_foctinfo = HFloatPropertyInfo::New(string, "foct");
    m_foctinfo->SetDefaultValue(5.0F);
    m_foctinfo->SetMinValue(1.F);
    m_foctinfo->SetMaxValue(20.0F);
    m_foctinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FFREQ);
    m_ffreqinfo = HFloatPropertyInfo::New(string, "ffreq");
    m_ffreqinfo->SetDefaultValue(44.0F);
    m_ffreqinfo->SetMinValue(1.F);
    m_ffreqinfo->SetMaxValue(10000.0F);
    m_ffreqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SCOLOR1);
    m_scolor1info = HColorPropertyInfo::New(string, "slopecolor1");
    m_scolor1info->GetRed()->SetDefaultValue(0.F);
    m_scolor1info->GetGreen()->SetDefaultValue(0.5F);
    m_scolor1info->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_SCOLOR2);
    m_scolor2info = HColorPropertyInfo::New(string, "slopecolor2");
    m_scolor2info->GetRed()->SetDefaultValue(0.F);
    m_scolor2info->GetGreen()->SetDefaultValue(0.5F);
    m_scolor2info->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_SCOLOR3);
    m_scolor3info = HColorPropertyInfo::New(string, "slopecolor3");
    m_scolor3info->GetRed()->SetDefaultValue(0.F);
    m_scolor3info->GetGreen()->SetDefaultValue(0.5F);
    m_scolor3info->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_SOCT);
    m_soctinfo = HFloatPropertyInfo::New(string, "soct");
    m_soctinfo->SetDefaultValue(5.0F);
    m_soctinfo->SetMinValue(1.F);
    m_soctinfo->SetMaxValue(20.0F);
    m_soctinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SFREQ);
    m_sfreqinfo = HFloatPropertyInfo::New(string, "sfreq");
    m_sfreqinfo->SetDefaultValue(44.0F);
    m_sfreqinfo->SetMinValue(1.F);
    m_sfreqinfo->SetMaxValue(10000.0F);
    m_sfreqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SBUMP);
    m_sbumpinfo = HFloatPropertyInfo::New(string, "Bump");
    m_sbumpinfo->SetDefaultValue(0.F);
    m_sbumpinfo->SetMinValue(0.F);
    m_sbumpinfo->SetMaxValue(100.F);
    m_sbumpinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FALLOFF);
    m_falloffinfo = HFloatPropertyInfo::New(string, "falloff");
    m_falloffinfo->SetDefaultValue(3.0F);
    m_falloffinfo->SetMinValue(0.F);
    m_falloffinfo->SetMaxValue(100.F);
    m_falloffinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_OFFSET);
    m_offsetinfo = HTranslatePropertyInfo::New(string, "Offset");
    m_offsetinfo->GetX()->SetMinValue(-100.F);
    m_offsetinfo->GetX()->SetMaxValue(100.F);
    m_offsetinfo->GetY()->SetMinValue(-100.F);
    m_offsetinfo->GetY()->SetMaxValue(100.F);
    m_offsetinfo->GetZ()->SetMinValue(-100.F);
    m_offsetinfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_SCALE);
    m_scaleinfo = HScalePropertyInfo::New(string, "Scale");
    m_scaleinfo->GetX()->SetDefaultValue(50.0F);
    m_scaleinfo->GetX()->SetMinValue(-100.F);
    m_scaleinfo->GetX()->SetMaxValue(100.F);
    m_scaleinfo->GetY()->SetDefaultValue(40.0F);
    m_scaleinfo->GetY()->SetMinValue(-100.F);
    m_scaleinfo->GetY()->SetMaxValue(100.F);
    m_scaleinfo->GetZ()->SetDefaultValue(40.0F);
    m_scaleinfo->GetZ()->SetMinValue(-100.F);
    m_scaleinfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_HEIGHT);
    m_heightinfo = HFloatPropertyInfo::New(string, "height");
    m_heightinfo->SetDefaultValue(0.F);
    m_heightinfo->SetMinValue(0.F);
    m_heightinfo->SetMaxValue(10000.0F);
    m_heightinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_altinfoarray.SetArraySize(ALTTYPE_NUMBER);
    m_altinfoarray[0]->SetMatchName("ALTTYPE_SLOPE");
    string.LoadString(IDS_ALTSLOPE);
    m_altinfoarray[0]->SetLocalizedName(string.GetBuffer());
    m_altinfoarray[1]->SetMatchName("ALTTYPE_FLAT");
    string.LoadString(IDS_FLAT);
    m_altinfoarray[1]->SetLocalizedName(string.GetBuffer());
    string.LoadString(IDS_ASLOPE);
    m_aslopeinfo = HTypePropertyInfo::New(string, "AltType", &m_altinfoarray);
    m_aslopeinfo->SetDefaultIndex(ALTTYPE_SLOPE);
    m_aslopeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_typeinfoarray.SetArraySize(NOISETYPE_NUMBER);
    m_typeinfoarray[0]->SetMatchName("NOISETYPE_NONOISE");
    string.LoadString(IDS_NONOISE);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[1]->SetMatchName("NOISETYPE_FRACTAL");
    string.LoadString(IDS_FRACTAL);
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[2]->SetMatchName("NOISETYPE_STRATA"); // crashes, don't know why yet
    string.LoadString(IDS_STRATA);
    m_typeinfoarray[2]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[3]->SetMatchName("NOISETYPE_FBM");
    string.LoadString(IDS_FBM);
    m_typeinfoarray[3]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[4]->SetMatchName("NOISETYPE_TURBULENCE");
    string.LoadString(IDS_TURB);
    m_typeinfoarray[4]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[5]->SetMatchName("NOISETYPE_STRETCHEDX");
    string.LoadString(IDS_STRETCHEDX);
    m_typeinfoarray[5]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[6]->SetMatchName("NOISETYPE_BUMPTURB");
    string.LoadString(IDS_BUMPTURB);
    m_typeinfoarray[6]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[7]->SetMatchName("NOISETYPE_BUMPFBM");
    string.LoadString(IDS_BUMPFBM);
    m_typeinfoarray[7]->SetLocalizedName(string.GetBuffer());
    m_typeinfoarray[8]->SetMatchName("NOISETYPE_BUMPFOURIER");
    string.LoadString(IDS_BUMPFOURIER);
    m_typeinfoarray[8]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_FNT);
    m_fntinfo = HTypePropertyInfo::New(string, "FNoiseType", &m_typeinfoarray);
    m_fntinfo->SetDefaultIndex(NOISETYPE_NONOISE);
    m_fntinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SNT);
    m_sntinfo = HTypePropertyInfo::New(string, "SNoiseType", &m_typeinfoarray);
    m_sntinfo->SetDefaultIndex(NOISETYPE_NONOISE);
    m_sntinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    delete m_fcolor1info;
    delete m_fcolor2info;
    delete m_fcolor3info;
    delete m_foctinfo;
    delete m_ffreqinfo;
    delete m_scolor1info;
    delete m_scolor2info;
    delete m_scolor3info;
    delete m_soctinfo;
    delete m_sfreqinfo;
    delete m_sbumpinfo;
    delete m_falloffinfo;
    delete m_offsetinfo;
    delete m_scaleinfo;
    delete m_heightinfo;
    delete m_aslopeinfo;
    delete m_fntinfo;
    delete m_sntinfo;

    return CPluginApp::ExitInstance();
}

void CTextureApp::InitNoiseTable() {
    srand(17); // NOLINT(cert-msc51-cpp)
    for (int i = MAXX; i-- > 0;) {
        for (int j = MAXY; j-- > 0;) {
            for (int k = MAXZ; k-- > 0;) {
                m_noiz_tbl[i][j][k] = rand() % 1000; // NOLINT(concurrency-mt-unsafe)
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
