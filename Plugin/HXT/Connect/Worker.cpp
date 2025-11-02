#include "StdAfx.h"
#include "Connect.h"

float Distance(const Vector v) {
    return v.Norm();
}

float Distance(const Vector v1, const Vector v2) {
    return Distance(v2 - v1);
}

Vector subdivideSegment(const Vector pos_cp1, const Vector it_cp1, const Vector ot_cp2, const Vector pos_cp2, const float factor) {
    const Vector c = 3. * (it_cp1 - pos_cp1);
    const Vector b = 3. * (ot_cp2 - it_cp1) - c;
    const Vector a = pos_cp2 - pos_cp1 - c - b;
    const Vector p = a * factor * factor * factor + b * factor * factor + c * factor + pos_cp1;
    return p;
}

void vectorPushMinMax(const Vector &p, Vector &minv, Vector &maxv) {
    if (p.x > maxv.x)
        maxv.x = p.x;
    if (p.x < minv.x)
        minv.x = p.x;
    if (p.y > maxv.y)
        maxv.y = p.y;
    if (p.y < minv.y)
        minv.y = p.y;
    if (p.z > maxv.z)
        maxv.z = p.z;
    if (p.z < minv.z)
        minv.z = p.z;
}

bool BBox_Intersect(const BBOX &box1, const BBOX &box2) {
    if (box1.vMax.x < box2.vMin.x || box2.vMax.x < box1.vMin.x)
        return false;
    if (box1.vMax.y < box2.vMin.y || box2.vMax.y < box1.vMin.y)
        return false;
    if (box1.vMax.z < box2.vMin.z || box2.vMax.z < box1.vMin.z)
        return false;
    return true;
}

bool LineLineIntersect(const Vector p1, const Vector p2, const Vector p3, const Vector p4, Vector &pa, Vector &pb, const double toleranz, double &distanz, float &min_toleranz) {

    distanz = 1.F;
    pa.Set(0.F);
    pb.Set(0.F);
    const Vector p13 = p1 - p3;
    const Vector p43 = p4 - p3;
    if (hash_math::abs(p43.x) < EPS && hash_math::abs(p43.y) < EPS && hash_math::abs(p43.z) < EPS)
        return false;
    const Vector p21 = p2 - p1;
    if (hash_math::abs(p21.x) < EPS && hash_math::abs(p21.y) < EPS && hash_math::abs(p21.z) < EPS)
        return false;

    const double d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
    const double d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
    const double d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
    const double d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
    const double d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

    const double denom = d2121 * d4343 - d4321 * d4321;
    if (hash_math::abs(denom) < EPS)
        return false;
    const double numer = d1343 * d4321 - d1321 * d4343;

    const double mua = numer / denom;
    const double mub = (d1343 + d4321 * mua) / d4343;
    //   if ((mua < 0) || (mua > 1.0) || (mub < 0) || (mub > 1.0)) return false; 
    if (mua < -1.0 || mua > 1.0 || mub < -1.0 || mub > 1.0)
        return false;

    pa.x = (float)(p1.x + mua * p21.x);
    pa.y = (float)(p1.y + mua * p21.y);
    pa.z = (float)(p1.z + mua * p21.z);
    pb.x = (float)(p3.x + mub * p43.x);
    pb.y = (float)(p3.y + mub * p43.y);
    pb.z = (float)(p3.z + mub * p43.z);

    distanz = Distance(pa, pb);
    if (distanz > toleranz) {
        if (min_toleranz > distanz)
            min_toleranz = (float)distanz;
        return false;
    }
    return true;
}

HCP *CheckforCreateCP(HCP *headcp, const Vector i_pos, double toleranz) {

    if (toleranz < 0.0001)
        toleranz = 0.0001;
    for (HCP *hcp = headcp; hcp; hcp = hcp->GetNext()) {
        const Vector pos = *hcp->GetModelPosition();
        if (Distance(pos, i_pos) < toleranz)
            return hcp;
        if (hcp->IsLoop())
            break;
    }
    return nullptr;
}

BOOL CheckforAttach(HCP *ncp_spline1, const HCP *ncp_spline2) {
    for (HCP *hcp = ncp_spline1->GetHead(); hcp; hcp = hcp->GetNextAttached()) {
        if (hcp == ncp_spline2)
            return false;
    }
    return true;
}

int GetSubdforSegment(const SEGMENT &seg) {

    int az_sd = 50;
    float sd_factor = hash_math::rcp((float)az_sd);

    const Vector pos_cp1 = seg.cp1_pos;
    const Vector it_cp1 = seg.cp1_it;
    const Vector pos_cp2 = seg.cp2_pos;
    const Vector ot_cp2 = seg.cp2_ot;
    Vector pos_temp1 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, ((float)az_sd / 2 - 1.F) * sd_factor);
    Vector pos_temp2 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, (float)az_sd / 2 * sd_factor);
    double distanz = Distance(pos_temp1, pos_temp2);
    while (distanz > 0.05) {
        az_sd += 50;
        sd_factor = hash_math::rcp((float)az_sd);
        pos_temp1 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, ((float)az_sd / 2 - 1.F) * sd_factor);
        pos_temp2 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, (float)az_sd / 2 * sd_factor);
        distanz = Distance(pos_temp1, pos_temp2);
    }
    while (distanz < 0.025 && az_sd > 10) {
        az_sd -= 5;
        sd_factor = hash_math::rcp((float)az_sd);
        pos_temp1 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, ((float)az_sd / 2 - 1.F) * sd_factor);
        pos_temp2 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, (float)az_sd / 2 * sd_factor);
        distanz = Distance(pos_temp1, pos_temp2);
    }
    return az_sd;
}

BOOL CConnectApp::CheckIntersection(HModelCache *hmc, SEGMENT seg1, SEGMENT seg2, int &stop) const {
    CArray<INTERSECT, INTERSECT> intersect;
    Vector pb;
    INTERSECT intersect_temp;
    HCP *hcp_head, *hcp;

    intersect.SetSize(0, 100);
    for (int i = 0; i < seg1.azpos - 1; ++i) {
        if (EscapeKeyDown()) {
            stop = true;
            break;
        }
        for (int j = 0; j < seg2.azpos - 1; ++j) {
            if (Vector pa; LineLineIntersect(seg1.pos[i], seg1.pos[i + 1], seg2.pos[j], seg2.pos[j + 1], pa, pb, para->tol, intersect_temp.distanz, para->min_toleranz)) {
                intersect_temp.pos_spline1 = pa;
                intersect_temp.pos_spline2 = pb;
                intersect.Add(intersect_temp);
            }
        }
    }

    if (stop)
        return false;
    if (intersect.GetSize() == 0)
        return false;
    if (intersect.GetSize() > 1) {
        intersect_temp = intersect[0];
        for (int i = 1; i < intersect.GetSize(); ++i) {
            if (intersect[i].distanz < intersect_temp.distanz)
                intersect_temp = intersect[i];
        }
    } else {
        intersect_temp = intersect[0];
    }

    hcp_head = seg1.startcp->GetSpline()->GetHeadCP();
    HCP *ncp_spline1 = CheckforCreateCP(hcp_head, intersect_temp.pos_spline1, para->tol);
    if (ncp_spline1 == nullptr) {
        hcp = seg1.endcp;
        while (hcp->GetPrev() != seg1.startcp) {
            hcp = hcp->GetPrev();
        }
        while (Distance(Vector(*hcp->GetModelPosition()), seg1.cp1_pos) < Distance(intersect_temp.pos_spline1, seg1.cp1_pos) && hcp != seg1.endcp) {
            hcp = hcp->GetNext();
        }
        ncp_spline1 = hmc->InsertCP(&hcp_head, hcp, &intersect_temp.pos_spline1);
    }

    hcp_head = seg2.startcp->GetSpline()->GetHeadCP();
    HCP *ncp_spline2 = CheckforCreateCP(hcp_head, intersect_temp.pos_spline2, para->tol);
    if (ncp_spline2 == nullptr) {
        hcp = seg2.endcp;
        while (hcp->GetPrev() != seg2.startcp) {
            hcp = hcp->GetPrev();
        }
        while (Distance(Vector(*hcp->GetModelPosition()), seg2.cp1_pos) < Distance(intersect_temp.pos_spline2, seg2.cp1_pos) && hcp != seg2.endcp) {
            hcp = hcp->GetNext();
        }
        ncp_spline2 = hmc->InsertCP(&hcp_head, hcp, &intersect_temp.pos_spline2);
    }
    if (CheckforAttach(ncp_spline1, ncp_spline2)) {
        hmc->AttachCPs(ncp_spline2, ncp_spline1);
        return true;
    }
    return false;
}

BOOL CConnectApp::ModelCPWorking(HModelCache *hmc) const {
    HSpline *hsp;
    HCP *hcp;
    CArray<CPLIST, CPLIST &> cplist;
    CPLIST t_cplist;
//    float distance;

    bool changed = false;
    int azsplines = 0;

    for (hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        azsplines++;
    }

    if (azsplines < 2) {
        AfxMessageBox("Nothing to do\nOnly one spline found in this model",MB_OK);
        return true; //nur 1 Spline vorhanden
    }

    GetHProject()->DeselectAll();
    CWaitCursor wait;

    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("Working....");
        p_bar->SetMessage2("");
        p_bar->SetProgress(0);
    }

    for (hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        for (hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
            t_cplist.hcp = hcp;
            t_cplist.pos = *hcp->GetModelPosition();
            cplist.Add(t_cplist);
            if (hcp->IsLoop())
                break;
        }
    }

    const int cplist1 = cplist.GetSize() - 1;
    const int cplist2 = cplist.GetSize();
    const double counter = 100. / cplist1;
    bool stop = false;
    for (int i = 0; i < cplist1; ++i) {
        const double akt_count = counter * (i + 1);
        if (p_bar)
            p_bar->SetProgress((int)akt_count);
        if (EscapeKeyDown() || stop) {
            stop = true;
            break;
        }
        for (int j = i + 1; j < cplist2; ++j) {
            if (cplist[i].hcp->GetSpline() != cplist[j].hcp->GetSpline()) {
                if (Distance(cplist[i].pos, cplist[j].pos) <= para->tol) {
                    bool found = false;
                    for (hcp = cplist[j].hcp->GetHead(); hcp; hcp = hcp->GetNextAttached()) {
                        if (hcp == cplist[i].hcp) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        hmc->AttachCPs(cplist[j].hcp, cplist[i].hcp);
                        changed = true;
                    }
                }
            }
        }
    }

    //end
    if (stop) {
        if (changed) {
            hmc->SetChanged(true);
            AfxMessageBox("Plugin canceled\nCp's have been attached before",MB_OK | MB_ICONSTOP);
        } else {
            AfxMessageBox("Plugin canceled",MB_OK | MB_ICONSTOP);
        }
    } else {
        if (!changed)
            AfxMessageBox("There are non cp's to attach in the given distance",MB_OK);
    }
    cplist.RemoveAll();
    if (p_bar)
        p_bar->Uninitialize();
    GetHProject()->UpdateAllViews(true);
    delete para;
    if (changed) {
        hmc->SetChanged(true);
        return true;
    }
    return true;
}

BOOL CConnectApp::ModelWorking(HModelCache *hmc) const {
    CArray<Vector, Vector> pos1;
    HSpline *hsp;
    HCP *hcp;
//    LINE spline_temp;
    int j, k;
    HGroupCP *gh;
    bool changed = false;
    CString temp;

    pos1.SetSize(0, 50);

    int azsplines = 0;
    for (hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        azsplines++;
    }

    if (azsplines < 2) {
        AfxMessageBox("Nothing to do\nOnly one spline found in this model",MB_OK);
        return true; //nur 1 Spline vorhanden
    }

    GetHProject()->DeselectAll();
    CWaitCursor wait;

    HProgressBar *p_bar = GetProgressBar();
    if (p_bar) {
        p_bar->Initialize();
        p_bar->SetMessage1("Calculate Splines");
        p_bar->SetMessage2("");
        p_bar->SetProgress(0);
    }

    auto *spline = new LINE[azsplines + 1];

    constexpr int az_subdivision = 50;
    const float sd_factor = hash_math::rcp((float)az_subdivision);
    int i = 0;
    for (hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        int azcp = 0;
        for (hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
            azcp++;
            if (hcp->IsLoop())
                break;
        }
        spline[i].id = hsp->GetHeadCP()->GetID();
        temp.Format("Spline #%d", spline[i].id);
        if (p_bar)
            p_bar->SetMessage2(temp);
        spline[i].segment = new SEGMENT[azcp + 1];
        azcp = 0;
        for (hcp = hsp->GetHeadCP(); hcp; hcp = hcp->GetNext()) {
            if (hcp->GetNext() && !hcp->IsHook() && !hcp->GetNext()->IsHook()) {
                spline[i].segment[azcp].startcp = hcp;
                spline[i].segment[azcp].cp1_pos = *spline[i].segment[azcp].startcp->GetModelPosition();
                spline[i].segment[azcp].cp1_it = spline[i].segment[azcp].startcp->GetModelInTangent();
                spline[i].segment[azcp].endcp = hcp->GetNext();
                spline[i].segment[azcp].cp2_pos = *spline[i].segment[azcp].endcp->GetModelPosition();
                spline[i].segment[azcp].cp2_ot = spline[i].segment[azcp].endcp->GetModelOutTangent();
                azcp++;
            }
            if (hcp->IsLoop())
                break;
        }
        spline[i].azsegment = azcp;
        for (j = 0; j < spline[i].azsegment; ++j) {
            //BBox fuer Segmente erstellen
            const Vector pos_cp1 = spline[i].segment[j].cp1_pos;
            const Vector it_cp1 = spline[i].segment[j].cp1_it;
            const Vector pos_cp2 = spline[i].segment[j].cp2_pos;
            const Vector ot_cp2 = spline[i].segment[j].cp2_ot;
            pos1.RemoveAll();
            for (k = 0; k <= az_subdivision; ++k) {
                pos1.Add(subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, sd_factor * k));
            }
            spline[i].segment[j].boundingbox.vMin = spline[i].segment[j].boundingbox.vMax = pos1[0];
            for (k = 1; k < pos1.GetSize(); ++k) {
                vectorPushMinMax(pos1[k], spline[i].segment[j].boundingbox.vMin, spline[i].segment[j].boundingbox.vMax);
            }
            //Segmentsubdivide
            spline[i].segment[j].azpos = GetSubdforSegment(spline[i].segment[j]);
            spline[i].segment[j].pos = new Vector [spline[i].segment[j].azpos + 2];
            const float sd_factor_segment = hash_math::rcp((float)spline[i].segment[j].azpos);
            for (k = 0; k <= spline[i].segment[j].azpos; ++k) {
                spline[i].segment[j].pos[k] = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, sd_factor_segment * k);
            }
        }
        //BBox fuer Spline erstellen
        spline[i].boundingbox = spline[i].boundingbox = spline[i].segment[0].boundingbox;
        for (j = 1; j < spline[i].azsegment; ++j) {
            vectorPushMinMax(spline[i].segment[j].boundingbox.vMin, spline[i].boundingbox.vMin, spline[i].boundingbox.vMax);
            vectorPushMinMax(spline[i].segment[j].boundingbox.vMax, spline[i].boundingbox.vMin, spline[i].boundingbox.vMax);
        }
        i++;
    }
    const double counter = 100. / (azsplines - 1);
    int stop = false;

    for (i = 0; i < azsplines - 1; ++i) {
        temp.Format("Spline #%d", spline[i].id);
        const double akt_count = counter * (i + 1);
        if (p_bar)
            p_bar->SetProgress((int)akt_count);
        if (p_bar)
            p_bar->SetMessage1(temp);
        if (EscapeKeyDown() || stop) {
            stop = true;
            break;
        }
        for (j = i + 1; j < azsplines; ++j) {
            temp.Format("Spline #%d", spline[j].id);
            if (p_bar)
                p_bar->SetMessage2(temp);
            if (EscapeKeyDown() || stop) {
                stop = true;
                break;
            }
            if (BBox_Intersect(spline[i].boundingbox, spline[j].boundingbox)) {
                //splinebbox intersect
                for (k = 0; k < spline[i].azsegment; ++k) {
                    if (EscapeKeyDown() || stop) {
                        stop = true;
                        break;
                    }
                    for (int l = 0; l < spline[j].azsegment; l++) {
                        if (EscapeKeyDown() || stop) {
                            stop = true;
                            break;
                        }
                        if (BBox_Intersect(spline[i].segment[k].boundingbox, spline[j].segment[l].boundingbox)) {
                            //segmentbbox intersect
                            gh = nullptr;
                            if (CheckIntersection(hmc, spline[i].segment[k], spline[j].segment[l], stop)) {
                                changed = true;
                                spline[i].segment[k].startcp->AddToGroup(&gh);
                                spline[i].segment[k].endcp->AddToGroup(&gh);
                                spline[j].segment[l].startcp->AddToGroup(&gh);
                                spline[j].segment[l].endcp->AddToGroup(&gh);
                                hmc->AddToTemporaryGroup(gh);
                                GetHProject()->DeselectAll();
                            }
                        }
                    }
                }
            }
        }
    }

    delete [] spline;
    if (stop) {
        if (changed) {
            hmc->SetChanged(true);
            AfxMessageBox("Plugin canceled\nNew cp's have been added before",MB_OK | MB_ICONSTOP);
        } else {
            AfxMessageBox("Plugin canceled",MB_OK | MB_ICONSTOP);
        }
    } else {
        if (!changed) {
            if (para->min_toleranz != 1e12F) {
                temp.Format("%f is the calculatet minimum tolerance for connect\n%f is the actual maximal tolerance for connect", para->min_toleranz, para->tol);
            } else {
                temp.Format("all intersecting splines already connectet");
            }
            AfxMessageBox(temp,MB_OK);
        } else {
            hmc->SetChanged(true);
        }
    }
    if (p_bar)
        p_bar->Uninitialize();
    GetHProject()->UpdateAllViews(true);
    delete para;
    return true;
}
