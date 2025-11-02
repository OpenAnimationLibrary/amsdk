// Volume.cpp
//

#include "StdAfx.h"
#include "Volume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeApp

BEGIN_MESSAGE_MAP(CVolumeApp, CWinApp)
    //{{AFX_MSG_MAP(CVolumeApp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeApp Konstruktion

CVolumeApp::CVolumeApp() = default;

CVolumeApp::~CVolumeApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CVolumeApp-Objekt

CVolumeApp theApp;

void Subexpressions(const float &w0, const float &w1, const float &w2, float &f1, float &f2, float &f3, float &g0, float &g1, float &g2) {
    const float temp0 = w0 + w1;
    f1 = temp0 + w2;
    const float temp1 = w0 * w0;
    const float temp2 = temp1 + w1 * temp0;
    f2 = temp2 + w2 * f1;
    f3 = w0 * temp1 + w1 * temp2 + w2 * f2;
    g0 = f2 + w0 * (f1 + w0);
    g1 = f2 + w1 * (f1 + w1);
    g2 = f2 + w2 * (f1 + w2);
}

double ComputeVolumeInertia(CArray<Trianglelist, Trianglelist> *list) {
    long double mult[10];
    double intg[10];
    float f1x, f2x, f3x, g0x, g1x, g2x;
    float f1y, f2y, f3y, g0y, g1y, g2y;
    float f1z, f2z, f3z, g0z, g1z, g2z;
    intg[0] = 0;
    intg[1] = 0;
    intg[2] = 0;
    intg[3] = 0;
    intg[4] = 0;
    intg[5] = 0;
    intg[6] = 0;
    intg[7] = 0;
    intg[8] = 0;
    intg[9] = 0;
    mult[0] = 1.0 / 6;
    mult[1] = 1.0 / 24;
    mult[2] = 1.0 / 24;
    mult[3] = 1.0 / 24;
    mult[4] = 1.0 / 60;
    mult[5] = 1.0 / 60;
    mult[6] = 1.0 / 60;
    mult[7] = 1.0 / 120;
    mult[8] = 1.0 / 120;
    mult[9] = 1.0 / 120;

    const int count = list->GetSize();
    for (int t = 0; t < count; ++t) {
        const Trianglelist temp_triangle = list->ElementAt(t);
        float x0 = temp_triangle.point0.x;
        float y0 = temp_triangle.point0.y;
        float z0 = temp_triangle.point0.z;
        float x1 = temp_triangle.point1.x;
        float y1 = temp_triangle.point1.y;
        float z1 = temp_triangle.point1.z;
        float x2 = temp_triangle.point2.x;
        float y2 = temp_triangle.point2.y;
        float z2 = temp_triangle.point2.z;
        const float a1 = x1 - x0;
        const float b1 = y1 - y0;
        const float c1 = z1 - z0;
        const float a2 = x2 - x0;
        const float b2 = y2 - y0;
        const float c2 = z2 - z0;
        const float d0 = b1 * c2 - b2 * c1;
        const float d1 = a2 * c1 - a1 * c2;
        const float d2 = a1 * b2 - a2 * b1;
        Subexpressions(x0, x1, x2, f1x, f2x, f3x, g0x, g1x, g2x);
        Subexpressions(y0, y1, y2, f1y, f2y, f3y, g0y, g1y, g2y);
        Subexpressions(z0, z1, z2, f1z, f2z, f3z, g0z, g1z, g2z);
        intg[0] += d0 * f1x;
        intg[1] += d0 * f2x;
        intg[2] += d1 * f2y;
        intg[3] += d2 * f2z;
        intg[4] += d0 * f3x;
        intg[5] += d1 * f3y;
        intg[6] += d2 * f3z;
        intg[7] += d0 * (y0 * g0x + y1 * g1x + y2 * g2x);
        intg[8] += d1 * (z0 * g0y + z1 * g1y + z2 * g2y);
        intg[9] += d2 * (x0 * g0z + x1 * g1z + x2 * g2z);
    }

    for (int i = 0; i < 10; ++i) {
        intg[i] *= mult[i];
    }
    return intg[0];
}

BOOL CVolumeApp::OnModel(HModel *hm) const {
    IEPolyModelParms m_iemp;
    CString ausgabe;

    const Time time = hm->GetChor()->GetTime();
    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = ST_16;
    m_iemp.m_ignorevisibility = TRUE;

    IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, nullptr);
    const int count = model->m_polyarray.GetSize();
    IEPoly **polyarray = model->m_polyarray.GetArray();
    CArray<Trianglelist, Trianglelist> *triangle = new CArray<Trianglelist, Trianglelist>;
    for (int i = 0; i < count; ++i) {
        Trianglelist temp_triangle;
        temp_triangle.point0 = model->m_vertexlist[polyarray[i]->m_vertexid[0]];
        temp_triangle.point1 = model->m_vertexlist[polyarray[i]->m_vertexid[1]];
        temp_triangle.point2 = model->m_vertexlist[polyarray[i]->m_vertexid[2]];
        triangle->Add(temp_triangle);
        if (polyarray[i]->m_vertexid[0] != polyarray[i]->m_vertexid[3]) {
            temp_triangle.point0 = model->m_vertexlist[polyarray[i]->m_vertexid[0]];
            temp_triangle.point1 = model->m_vertexlist[polyarray[i]->m_vertexid[2]];
            temp_triangle.point2 = model->m_vertexlist[polyarray[i]->m_vertexid[3]];
            triangle->Add(temp_triangle);
        }
    }
    DeleteIEModel(model);
    const double volume = ComputeVolumeInertia(triangle);
    triangle->RemoveAll();
    delete triangle;
    ausgabe.Format("%s\nVolume %.3f cm3", hm->GetName(), volume);
    AfxMessageBox(ausgabe, MB_OK | MB_ICONINFORMATION);
    return true;
}

BOOL CVolumeApp::OnModelCache(HModelCache *hmc) const {
    IEPolyModelParms m_iemp;
    CString ausgabe;
    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = ST_16;
    m_iemp.m_ignorevisibility = TRUE;
    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, nullptr);
    const int count = model->m_polyarray.GetSize();
    IEPoly **polyarray = model->m_polyarray.GetArray();
    CArray<Trianglelist, Trianglelist> *triangle = new CArray<Trianglelist, Trianglelist>;
    for (int i = 0; i < count; ++i) {
        Trianglelist temp_triangle;
        temp_triangle.point0 = model->m_vertexlist[polyarray[i]->m_vertexid[0]];
        temp_triangle.point1 = model->m_vertexlist[polyarray[i]->m_vertexid[1]];
        temp_triangle.point2 = model->m_vertexlist[polyarray[i]->m_vertexid[2]];
        triangle->Add(temp_triangle);
        if (polyarray[i]->m_vertexid[0] != polyarray[i]->m_vertexid[3]) {
            temp_triangle.point0 = model->m_vertexlist[polyarray[i]->m_vertexid[0]];
            temp_triangle.point1 = model->m_vertexlist[polyarray[i]->m_vertexid[2]];
            temp_triangle.point2 = model->m_vertexlist[polyarray[i]->m_vertexid[3]];
            triangle->Add(temp_triangle);
        }
    }
    DeleteIEModel(model);
    const double volume = ComputeVolumeInertia(triangle);
    triangle->RemoveAll();
    delete triangle;
    ausgabe.Format("%s\nVolume %.3f cm3", hmc->GetName(), volume);
    AfxMessageBox(ausgabe, MB_OK | MB_ICONINFORMATION);
    return true;
}

BOOL CVolumeApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CVolumeApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
