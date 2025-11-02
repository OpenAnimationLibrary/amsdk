// Dan  3/24/2003  \DanLP105\Plugin\Textures\Joyce\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"
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
    // New Infos here
    string.LoadString(IDS_PAPERCOLOR);
    m_papercolorinfo = HColorPropertyInfo::New(string, "PaperColor");
    m_papercolorinfo->GetRed()->SetDefaultValue(1.F);
    m_papercolorinfo->GetGreen()->SetDefaultValue(1.F);
    m_papercolorinfo->GetBlue()->SetDefaultValue(1.F);

    string.LoadString(IDS_PENCILCOLOR);
    m_pencilcolorinfo = HColorPropertyInfo::New(string, "PencilColor");
    m_pencilcolorinfo->GetRed()->SetDefaultValue(0.68F);
    m_pencilcolorinfo->GetGreen()->SetDefaultValue(0.68F);
    m_pencilcolorinfo->GetBlue()->SetDefaultValue(0.68F);

    string.LoadString(IDS_PENCILNOISE);
    m_pencilnoiseinfo = HFloatPropertyInfo::New(string, "PencilNoise");
    m_pencilnoiseinfo->SetDefaultValue(10.F);
    m_pencilnoiseinfo->SetMinValue(0.F);
    m_pencilnoiseinfo->SetMaxValue(100.F);
    m_pencilnoiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_PENCILFREQ);
    m_pencilfreqinfo = HFloatPropertyInfo::New(string, "PencilFreq");
    m_pencilfreqinfo->SetDefaultValue(1.F);
    m_pencilfreqinfo->SetMinValue(0.F);
    m_pencilfreqinfo->SetMaxValue(100.F);
    m_pencilfreqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_PENCILSIZE);
    m_pencilsizeinfo = HFloatPropertyInfo::New(string, "PencilSize");
    m_pencilsizeinfo->SetDefaultValue(1.F);
    m_pencilsizeinfo->SetMinValue(0.F);
    m_pencilsizeinfo->SetMaxValue(100.F);
    m_pencilsizeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_WASHCOLOR);
    m_washcolorinfo = HColorPropertyInfo::New(string, "WashColor");
    m_washcolorinfo->GetRed()->SetDefaultValue(0.78F);
    m_washcolorinfo->GetGreen()->SetDefaultValue(0.78F);
    m_washcolorinfo->GetBlue()->SetDefaultValue(0.F);

    string.LoadString(IDS_WASHNOISE);
    m_washnoiseinfo = HFloatPropertyInfo::New(string, "WashNoise");
    m_washnoiseinfo->SetDefaultValue(10.F);
    m_washnoiseinfo->SetMinValue(0.F);
    m_washnoiseinfo->SetMaxValue(100.F);
    m_washnoiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_WASHFREQ);
    m_washfreqinfo = HFloatPropertyInfo::New(string, "WashFreq");
    m_washfreqinfo->SetDefaultValue(1.F);
    m_washfreqinfo->SetMinValue(0.F);
    m_washfreqinfo->SetMaxValue(100.F);
    m_washfreqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_WASHSIZE);
    m_washsizeinfo = HFloatPropertyInfo::New(string, "WashSize");
    m_washsizeinfo->SetDefaultValue(75.0F);
    m_washsizeinfo->SetMinValue(0.F);
    m_washsizeinfo->SetMaxValue(100.F);
    m_washsizeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DARK1COLOR);
    m_dark1colorinfo = HColorPropertyInfo::New(string, "Dark1Color");
    m_dark1colorinfo->GetRed()->SetDefaultValue(0.78F);
    m_dark1colorinfo->GetGreen()->SetDefaultValue(0.08F);
    m_dark1colorinfo->GetBlue()->SetDefaultValue(0.F);

    string.LoadString(IDS_DARK1NOISE);
    m_dark1noiseinfo = HFloatPropertyInfo::New(string, "Dark1Noise");
    m_dark1noiseinfo->SetDefaultValue(10.F);
    m_dark1noiseinfo->SetMinValue(0.F);
    m_dark1noiseinfo->SetMaxValue(100.F);
    m_dark1noiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DARK1FREQ);
    m_dark1freqinfo = HFloatPropertyInfo::New(string, "Dark1Freq");
    m_dark1freqinfo->SetDefaultValue(1.F);
    m_dark1freqinfo->SetMinValue(0.F);
    m_dark1freqinfo->SetMaxValue(100.F);
    m_dark1freqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DARK1SIZE);
    m_dark1sizeinfo = HFloatPropertyInfo::New(string, "Dark1Size");
    m_dark1sizeinfo->SetDefaultValue(15.0F);
    m_dark1sizeinfo->SetMinValue(0.F);
    m_dark1sizeinfo->SetMaxValue(100.F);
    m_dark1sizeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DARK2COLOR);
    m_dark2colorinfo = HColorPropertyInfo::New(string, "Dark2Color");
    m_dark2colorinfo->GetRed()->SetDefaultValue(1.F);
    m_dark2colorinfo->GetGreen()->SetDefaultValue(0.08F);
    m_dark2colorinfo->GetBlue()->SetDefaultValue(0.F);

    string.LoadString(IDS_DARK2NOISE);
    m_dark2noiseinfo = HFloatPropertyInfo::New(string, "Dark2Noise");
    m_dark2noiseinfo->SetDefaultValue(10.F);
    m_dark2noiseinfo->SetMinValue(0.F);
    m_dark2noiseinfo->SetMaxValue(100.F);
    m_dark2noiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DARK2FREQ);
    m_dark2freqinfo = HFloatPropertyInfo::New(string, "Dark2Freq");
    m_dark2freqinfo->SetDefaultValue(1.F);
    m_dark2freqinfo->SetMinValue(0.F);
    m_dark2freqinfo->SetMaxValue(100.F);
    m_dark2freqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DARK2SIZE);
    m_dark2sizeinfo = HFloatPropertyInfo::New(string, "Dark2Size");
    m_dark2sizeinfo->SetDefaultValue(1.F);
    m_dark2sizeinfo->SetMinValue(0.F);
    m_dark2sizeinfo->SetMaxValue(100.F);
    m_dark2sizeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_LIGHT);
    m_lightinfo = HVectorPropertyInfo::New(string, "Light");
    m_lightinfo->GetX()->SetDefaultValue(2.F);
    m_lightinfo->GetX()->SetMinValue(-100.F);
    m_lightinfo->GetX()->SetMaxValue(100.F);
    m_lightinfo->GetY()->SetDefaultValue(2.F);
    m_lightinfo->GetY()->SetMinValue(-100.F);
    m_lightinfo->GetY()->SetMaxValue(100.F);
    m_lightinfo->GetZ()->SetMinValue(-5.0F);
    m_lightinfo->GetZ()->SetMinValue(-100.F);
    m_lightinfo->GetZ()->SetMaxValue(100.F);

    string.LoadString(IDS_MIX);
    m_mixinfo = HFloatPropertyInfo::New(string, "Mix");
    m_mixinfo->SetDefaultValue(30.0F);
    m_mixinfo->SetMinValue(0.F);
    m_mixinfo->SetMaxValue(100.F);
    m_mixinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FREQ);
    m_freqinfo = HFloatPropertyInfo::New(string, "Freq");
    m_freqinfo->SetDefaultValue(1.F);
    m_freqinfo->SetMinValue(0.F);
    m_freqinfo->SetMaxValue(100.F);
    m_freqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BITMAP);
    m_bitmapinfo = HClipPropertyInfo::New(string, "Bitmap");

    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_papercolorinfo;

    delete m_pencilcolorinfo;
    delete m_pencilnoiseinfo;
    delete m_pencilfreqinfo;
    delete m_pencilsizeinfo;

    delete m_washcolorinfo;
    delete m_washnoiseinfo;
    delete m_washfreqinfo;
    delete m_washsizeinfo;

    delete m_dark1colorinfo;
    delete m_dark1noiseinfo;
    delete m_dark1freqinfo;
    delete m_dark1sizeinfo;

    delete m_dark2colorinfo;
    delete m_dark2noiseinfo;
    delete m_dark2freqinfo;
    delete m_dark2sizeinfo;

    delete m_lightinfo;
    delete m_mixinfo;
    delete m_freqinfo;
    delete m_bitmapinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

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

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
