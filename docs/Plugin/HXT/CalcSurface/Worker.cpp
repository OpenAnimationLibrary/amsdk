#include "StdAfx.h"
#include "CalcSurface.h"

double VectorLength(const Vector a) {
    return hash_math::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double TriArea(const Vector p1, const Vector p2, const Vector p3) {
    const Vector CrossP = Cross(p2 - p1, p3 - p1);
    if (CrossP.z < 0.F)
        return VectorLength(CrossP) * -1;
    return VectorLength(CrossP);
}

double CCalcSurfaceApp::GetArea(HModel *hm) {
    IEPolyModelParms m_iemp;

    m_iemp.m_isbuildmodelmap = (BITFIELDS16)FALSE;
    m_iemp.m_isbuildattrarray = (BITFIELDS16)FALSE;
    m_iemp.m_isbuildbonelist = (BITFIELDS16)FALSE;
    m_iemp.m_isdisplaypercentbar = (BITFIELDS16)FALSE;
    m_iemp.m_isbuildmaparray = (BITFIELDS16)FALSE;
    m_iemp.m_ignorevisibility = (BITFIELDS16)TRUE;
    m_iemp.m_subtype = ST_4;

    IEPolyModel *model = hm->BuildExportModel(&m_iemp, Time(), nullptr);
    const int count = model->m_polyarray.GetSize();
    IEPoly **polyarray = model->m_polyarray.GetArray();

    double sumarea = 0;
    for (int i = 0; i < count; ++i) {
        double area = TriArea(model->m_vertexlist[polyarray[i]->m_vertexid[0]], model->m_vertexlist[polyarray[i]->m_vertexid[1]], model->m_vertexlist[polyarray[i]->m_vertexid[2]]);
        if (polyarray[i]->m_vertexid[0] != polyarray[i]->m_vertexid[3]) {
            area += TriArea(model->m_vertexlist[polyarray[i]->m_vertexid[2]], model->m_vertexlist[polyarray[i]->m_vertexid[3]], model->m_vertexlist[polyarray[i]->m_vertexid[0]]);
        }
        if (area < 0.)
            area *= -1.;
        area *= 0.5;
        sumarea += area;
    }
    DeleteIEModel(model);
    return sumarea;
}

BOOL CCalcSurfaceApp::CalculateChor(HChor *hchor) const {

    double sumArea = 0;
    for (HModel *hm = hchor->GetChildModel(); hm; hm = hm->GetNextModelInChor()) {
        if (hm->GetActive()->GetValue()) {
            Detail tdetail;
            const double sum = GetArea(hm);
            sumArea += sum;
            tdetail.surface = sum;
            tdetail.name = hm->GetName();
            para->detail.Add(tdetail);
        }
    }

    para->surface = ROUNDOFF(sumArea);
    return true;
}

BOOL CCalcSurfaceApp::GetPropRecurse(HProperty *akt_prop) const {
    HProperty *prop;

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (!prop)
            return TRUE;
        if (!GetPropRecurse(prop)) {
            String temp1 = prop->GetMatchName();
            if (temp1.Find("PhotonRaysCast") != -1) {
                para->iPPhotonCast = (HIntProperty *)prop;
                para->iVPhotonCast = para->iVPhotonCast_org = para->iPPhotonCast->GetValue(Time());

            }
            if (temp1.Find("PhotonSamples") != -1) {
                para->iPPhotonSample = (HIntProperty *)prop;
                para->iVPhotonSample = para->iVPhotonSample_org = para->iPPhotonSample->GetValue(Time());
            }
            if (temp1.Find("PhotonSampleArea") != -1) {
                para->fPSampleArea = (HFloatProperty *)prop;
                para->fVSampleArea = para->fVSampleArea_org = para->fPSampleArea->GetValue(Time()) * 100.F;
            }
        }
    }
    return FALSE;
}

void CCalcSurfaceApp::GetProperty(HChor *obj) const {
    HProperty *prop;

    for (int i = 0; (prop = obj->GetPropertyAt(i)); ++i) {
        if (prop) {
            String temp1 = prop->GetMatchName();
            if (temp1.Find("PhotonMap") != -1) {
                GetPropRecurse(prop);
            }
        }
    }
}
