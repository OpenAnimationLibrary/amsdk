// RC  6/4/2002  \Randy95\Plugin\Turb\CellTurb\TurbApp.cpp
//

#include "StdAfx.h"
#include "HashFile.h"

#include "TurbApp.h"
#include "F_Protos.h"
//#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurbApp

BEGIN_MESSAGE_MAP(CTurbApp, CWinApp)
    //{{AFX_MSG_MAP(CTurbApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurbApp construction

BOOL CTurbApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    m_typeinfoarray.SetArraySize(CELLTYPE_NUMBER);
    m_typeinfoarray[0]->SetMatchName("CELLTYPE_WEBBED");
    string.LoadString(IDS_WEBBED);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[1]->SetMatchName("CELLTYPE_PLATED");
    string.LoadString(IDS_PLATED);
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[2]->SetMatchName("CELLTYPE_RIDGED"); // crashes, don't know why yet
    string.LoadString(IDS_RIDGED);
    m_typeinfoarray[2]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[3]->SetMatchName("CELLTYPE_HARDEDGE");
    string.LoadString(IDS_HARDEDGE);
    m_typeinfoarray[3]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[4]->SetMatchName("CELLTYPE_CRYSTAL");
    string.LoadString(IDS_CRYSTAL);
    m_typeinfoarray[4]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[5]->SetMatchName("CELLTYPE_ROUNDER");
    string.LoadString(IDS_ROUNDER);
    m_typeinfoarray[5]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[6]->SetMatchName("CELLTYPE_THRESHOLD");
    string.LoadString(IDS_THRESHOLD);
    m_typeinfoarray[6]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_CELLTYPE);
    m_celltypeinfo = HTypePropertyInfo::New(string, "CellType", &m_typeinfoarray);
    m_celltypeinfo->SetDefaultIndex(CELLTYPE_WEBBED);
    m_celltypeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_OCTAVES);
    m_thresholdinfo = HFloatPropertyInfo::New(string, "Threshold");
    m_thresholdinfo->SetDefaultValue(10);
    m_thresholdinfo->SetMinValue(0);
    m_thresholdinfo->SetMaxValue(100);
    m_thresholdinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_OCT);
    m_octinfo = HIntPropertyInfo::New(string, "Octaves");
    m_octinfo->SetDefaultValue(1);
    m_octinfo->SetMinValue(0);
    m_octinfo->SetMaxValue(15);
    m_octinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DENSITY);
    m_densityinfo = HFloatPropertyInfo::New(string, "Density");
    m_densityinfo->SetDefaultValue(100);
    m_densityinfo->SetMinValue(0);
    m_densityinfo->SetMaxValue(100);
    m_densityinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_EUCLID);
    m_euclidinfo = HBoolPropertyInfo::New(string, "Euclid");
    m_euclidinfo->SetDefaultValue(TRUE);
    m_euclidinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

//    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTurbApp::ExitInstance() {
    // Delete Infos Here
    delete m_thresholdinfo;
    delete m_celltypeinfo;
    delete m_octinfo;
    delete m_densityinfo;
    delete m_euclidinfo;

    return CPluginApp::ExitInstance();
}

/*
void CTurbApp::InitNoiseTable() {
    srand(12345);  // NOLINT(cert-msc51-cpp)
    for (int i = MAXX; i-- > 0;) {
        for (int j = MAXY; j-- > 0;) {
            for (int k = MAXZ; k-- > 0;) {
                m_noiz_tbl[i][j][k] = rand() % 1000;  // NOLINT(concurrency-mt-unsafe)
            }
        }
    }
}
*/

float CTurbApp::Noise(const Vector &p) {
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

float CTurbApp::CellNoise(const Vector &p) {
    Vector p_n(p);
    p_n += 15000.0F;
    constexpr float d = 0.001F;
    int ix = fast_ftol_unsigned(p_n.x) % MAXX;
    if (ix < 0)
        ix += MAXX;
    int iy = fast_ftol_unsigned(p_n.y) % MAXY;
    if (iy < 0)
        iy += MAXY;
    int iz = fast_ftol_unsigned(p_n.z) % MAXZ;
    if (iz < 0)
        iz += MAXZ;

    const float t2 = m_noiz_tbl[ix][iy][iz];

    const float t1 = t2 * d;
    if (t1 > 0.F)
        return t1;
    return 0.F;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTurbApp object

CTurbApp theApp;
