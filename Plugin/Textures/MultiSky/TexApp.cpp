// Dan  3/24/2003  \DanLP105\Plugin\Textures\MultiSky\TexApp.cpp
//

// ReSharper disable CppClangTidyConcurrencyMtUnsafe
#include "StdAfx.h"
#include "TexApp.h"
#include "F_Protos.h"

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

    string.LoadString(IDS_BCOLOR);
    m_bcolorinfo = HColorPropertyInfo::New(string, "skycolor");
    m_bcolorinfo->GetRed()->SetDefaultValue(0.F);
    m_bcolorinfo->GetGreen()->SetDefaultValue(0.5F);
    m_bcolorinfo->GetBlue()->SetDefaultValue(0.78F);

    string.LoadString(IDS_C1COLOR);
    m_c1colorinfo = HColorPropertyInfo::New(string, "cloudcolor");
    m_c1colorinfo->GetRed()->SetDefaultValue(0.86F);
    m_c1colorinfo->GetGreen()->SetDefaultValue(0.86F);
    m_c1colorinfo->GetBlue()->SetDefaultValue(0.86F);

    string.LoadString(IDS_C2COLOR);
    m_c2colorinfo = HColorPropertyInfo::New(string, "shadowcolor");
    m_c2colorinfo->GetRed()->SetDefaultValue(0.5F);
    m_c2colorinfo->GetGreen()->SetDefaultValue(0.5F);
    m_c2colorinfo->GetBlue()->SetDefaultValue(0.5F);

    string.LoadString(IDS_HAZECOLOR);
    m_hcolorinfo = HColorPropertyInfo::New(string, "hazecolor");
    m_hcolorinfo->GetRed()->SetDefaultValue(1.F);
    m_hcolorinfo->GetGreen()->SetDefaultValue(1.F);
    m_hcolorinfo->GetBlue()->SetDefaultValue(1.F);

    string.LoadString(IDS_SUNCOLOR);
    m_scolorinfo = HColorPropertyInfo::New(string, "suncolor");
    m_scolorinfo->GetRed()->SetDefaultValue(1.F);
    m_scolorinfo->GetGreen()->SetDefaultValue(1.F);
    m_scolorinfo->GetBlue()->SetDefaultValue(0.94F);

    string.LoadString(IDS_HAZE);
    m_hazeinfo = HFloatPropertyInfo::New(string, "Haze");
    m_hazeinfo->SetDefaultValue(100.F);
    m_hazeinfo->SetMinValue(0.F);
    m_hazeinfo->SetMaxValue(100.F);
    m_hazeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_HEIGHT);
    m_heightinfo = HFloatPropertyInfo::New(string, "Height");
    m_heightinfo->SetDefaultValue(10.F);
    m_heightinfo->SetMinValue(0.F);
    m_heightinfo->SetMaxValue(10000.0F);
    m_heightinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SUN);
    m_suninfo = HVectorPropertyInfo::New(string, "Sun");
    m_suninfo->GetX()->SetDefaultValue(1.F);
    m_suninfo->GetX()->SetMinValue(-100.F);
    m_suninfo->GetX()->SetMaxValue(100.F);
    m_suninfo->GetY()->SetDefaultValue(1.F);
    m_suninfo->GetY()->SetMinValue(-100.F);
    m_suninfo->GetY()->SetMaxValue(100.F);
    m_suninfo->GetZ()->SetMinValue(1.F);
    m_suninfo->GetZ()->SetMinValue(-100.F);
    m_suninfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_OCTAVES);
    m_octavesinfo = HIntPropertyInfo::New(string, "complexity");
    m_octavesinfo->SetDefaultValue(5);
    m_octavesinfo->SetMinValue(1);
    m_octavesinfo->SetMaxValue(20);
    m_octavesinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SINTENSITY);
    m_sintensityinfo = HFloatPropertyInfo::New(string, "sunintensity");
    m_sintensityinfo->SetDefaultValue(100.F);
    m_sintensityinfo->SetMinValue(1.F);
    m_sintensityinfo->SetMaxValue(100.F);
    m_sintensityinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_COVER);
    m_coverinfo = HFloatPropertyInfo::New(string, "cover");
    m_coverinfo->SetDefaultValue(50.0F);
    m_coverinfo->SetMinValue(1.F);
    m_coverinfo->SetMaxValue(200.0F);
    m_coverinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

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
    m_scaleinfo->GetX()->SetMinValue(0.F);
    m_scaleinfo->GetX()->SetMaxValue(100.F);
    m_scaleinfo->GetX()->SetDefaultValue(50.0F);
    m_scaleinfo->GetY()->SetMinValue(0.F);
    m_scaleinfo->GetY()->SetMaxValue(100.F);
    m_scaleinfo->GetY()->SetDefaultValue(40.0F);
    m_scaleinfo->GetZ()->SetMinValue(0.F);
    m_scaleinfo->GetZ()->SetMaxValue(100.F);
    m_scaleinfo->GetZ()->SetDefaultValue(40.0F);

    string.LoadString(IDS_TRANSPARENCY);
    m_transinfo = HFloatPropertyInfo::New(string, "Transparency");
    m_sintensityinfo->SetDefaultValue(0.F);
    m_sintensityinfo->SetMinValue(0.F);
    m_sintensityinfo->SetMaxValue(1.F);
    m_transinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SI);
    m_siinfo = HBoolPropertyInfo::New(string, "SelfIlluminating");
    m_siinfo->SetDefaultValue(FALSE);
    m_siinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_typeinfoarray.SetArraySize(TYPE_NUMBER);
    m_typeinfoarray[0]->SetMatchName("TYPE_CLASSIC");
    string.LoadString(IDS_CLASSIC);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[1]->SetMatchName("TYPE_CIRRUS");
    string.LoadString(IDS_CIRRUS);
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[2]->SetMatchName("TYPE_FLUFFY");
    string.LoadString(IDS_FLUFFY);
    m_typeinfoarray[2]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[3]->SetMatchName("TYPE_OREN_NAYAR");
    string.LoadString(IDS_OREN_NAYAR);
    m_typeinfoarray[3]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[4]->SetMatchName("TYPE_SWIRL");
    string.LoadString(IDS_SWIRL);
    m_typeinfoarray[4]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[5]->SetMatchName("TYPE_PUFFY");
    string.LoadString(IDS_PUFFY);
    m_typeinfoarray[5]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_TYPE);
    m_typeinfo = HTypePropertyInfo::New(string, "Cloud Type", &m_typeinfoarray);
    m_typeinfo->SetDefaultIndex(TYPE_CLASSIC);
    m_typeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    delete m_hcolorinfo;
    delete m_scolorinfo;
    delete m_c1colorinfo;
    delete m_c2colorinfo;
    delete m_bcolorinfo;
    delete m_transinfo;
    delete m_heightinfo;
    delete m_coverinfo;
    delete m_octavesinfo;
    delete m_hazeinfo;
    delete m_sintensityinfo;
    delete m_typeinfo;
    delete m_siinfo;
    delete m_suninfo;
    delete m_offsetinfo;
    delete m_scaleinfo;

    return CPluginApp::ExitInstance();
}

void CTextureApp::InitNoiseTable() {
    Vector clouds[20];
    srand(73);  // NOLINT(cert-msc51-cpp)
    for (auto &cloud: clouds) {
        cloud.x = rand() / (float)RAND_MAX * MAXX;
        cloud.y = rand() / (float)RAND_MAX * MAXY;
        cloud.z = rand() / (float)RAND_MAX * MAXZ;
    }

    constexpr float thresh = 10.F;
    for (int i = MAXX; i-- > 0;) {
        for (int j = MAXY; j-- > 0;) {
            for (int k = MAXZ; k-- > 0;) {
                m_noiz_tbl[i][j][k] = rand() % 1000;
                float sum = 0.F;
                for (const auto cloud: clouds) {
                    Vector p(i, j, (float)k);
                    p = p - cloud;
                    float d = hash_math::abs(p.Dot(p));
                    if (d < thresh)
                        d = 1.F - d / thresh;
                    else
                        d = 0.F;

                    sum += d;
                }
                sum = sum > 1.F ? 1.F : sum;
                m_cloud_tbl[i][j][k] = sum;
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

float CTextureApp::CNoise(const Vector p) const {
    Vector p_n(p);
    p_n += 15000.F;
    int ix = (int)p_n.x % MAXX;
    if (ix < 0)
        ix += MAXX;
    int iy = (int)p_n.y % MAXY;
    if (iy < 0)
        iy += MAXY;
    int iz = (int)p_n.z % MAXZ;
    if (iz < 0)
        iz += MAXZ;

    const float ox = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.x - (int)p_n.x))) * .5F;
    const float oy = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.y - (int)p_n.y))) * .5F;
    const float oz = 1.F - (1.F + hash_math::cos(hash_constants::pi * (p_n.z - (int)p_n.z))) * .5F;

    const int ixp = ix + 1 >= MAXX ? 0 : ix + 1;
    const int iyp = iy + 1 >= MAXY ? 0 : iy + 1;
    const int izp = iz + 1 >= MAXZ ? 0 : iz + 1;

    const float A = m_cloud_tbl[ix][iy][iz];
    const float B = m_cloud_tbl[ixp][iy][iz];
    const float C = m_cloud_tbl[ixp][iyp][iz];
    const float D = m_cloud_tbl[ixp][iyp][izp];
    const float E = m_cloud_tbl[ixp][iy][izp];
    const float F = m_cloud_tbl[ix][iy][izp];
    const float G = m_cloud_tbl[ix][iyp][izp];
    const float H = m_cloud_tbl[ix][iyp][iz];
    float t1 = (1.F - ox) * A + ox * B;
    float t2 = (1.F - ox) * H + ox * C;
    const float t3 = (1.F - ox) * F + ox * E;
    const float t4 = (1.F - ox) * G + ox * D;
    t1 = (1.F - oy) * t1 + oy * t2;
    t2 = (1.F - oy) * t3 + oy * t4;
    t1 = (1.F - oz) * t1 + oz * t2;

    t2 = t1;
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
