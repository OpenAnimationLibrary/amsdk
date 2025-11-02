// RC  6/4/2002  \Randy95\Plugin\Turb\GridTurb\TurbApp.cpp
//

#include "StdAfx.h"
#include "TurbApp.h"
#include "F_Protos.h"
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
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
    m_typeinfoarray[0]->SetMatchName("CELLTYPE_XYZ");
    string.LoadString(IDS_XYZ);
    m_typeinfoarray[0]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[1]->SetMatchName("CELLTYPE_XY");
    string.LoadString(IDS_XY);
    m_typeinfoarray[1]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[2]->SetMatchName("CELLTYPE_SPHEREMAPPED"); // crashes, don't know why yet
    string.LoadString(IDS_SPHEREMAPPED);
    m_typeinfoarray[2]->SetLocalizedName(string.GetBuffer());

    m_typeinfoarray[3]->SetMatchName("CELLTYPE_CYLINDERMAPPED");
    string.LoadString(IDS_CYLINDERMAPPED);
    m_typeinfoarray[3]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_CELLTYPE);
    m_celltypeinfo = HTypePropertyInfo::New(string, "CellType", &m_typeinfoarray);
    m_celltypeinfo->SetDefaultIndex(CELLTYPE_XYZ);

    string.LoadString(IDS_OCTAVES);
    m_octavesinfo = HIntPropertyInfo::New(string, "Octaves");
    m_octavesinfo->SetDefaultValue(10);
    m_octavesinfo->SetMinValue(0);
    m_octavesinfo->SetMaxValue(100);

    string.LoadString(IDS_GRIDSIZE);
    m_gridsizeinfo = HIntPropertyInfo::New(string, "Grid Size");
    m_gridsizeinfo->SetDefaultValue(10);
    m_gridsizeinfo->SetMinValue(0);
    m_gridsizeinfo->SetMaxValue(100);

//    InitNoiseTable();

    return CPluginApp::InitInstance();
}

int CTurbApp::ExitInstance() {
    // Delete Infos Here
    delete m_octavesinfo;
    delete m_gridsizeinfo;
    delete m_celltypeinfo;

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
