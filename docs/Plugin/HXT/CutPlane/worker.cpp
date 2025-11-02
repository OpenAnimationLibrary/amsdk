#include "StdAfx.h"
#include "CutPlane.h"

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

#ifdef _DEBUG
void CCutPlaneApp::DebugOut() {
    if (hmc)
        fsd << nl << hmc->GetName() << nl;
    if (sp_list.IsEmpty()) {
        fsd << "Splineliste ist leer !" << nl;
        return;
    }
    for (int i = 0; i < sp_list.GetSize(); ++i) {
        fsd << "Spline " << i << " " << sp_list[i].sp->GetMatchName() << nl;
        fsd << "  Segments " << sp_list[i].seg.GetSize() << nl;
        fsd << nl;
    }
}
#endif

float GetSDLength(const int sd, const Vector pos_cp1, const Vector it_cp1, const Vector ot_cp2, const Vector pos_cp2) {
    const float sd_factor = hash_math::rcp((float)sd);
    Vector pos_old = pos_cp1;
    float length = 0;
    for (int j = 1; j <= sd; ++j) {
        const Vector pos = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, sd_factor * j);
        length += Distance(pos_old, pos);
        pos_old = pos;
    }
    return length;
}

int GetSubdivision(const Vector pos_cp1, const Vector it_cp1, const Vector ot_cp2, const Vector pos_cp2) {
    float o_length = Distance(pos_cp1, pos_cp2);
    int sd = 2;
    float length = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    if (o_length == length)
        return 1; //no sd needed
    sd = 512;
    length = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    sd = 2;
    float length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 2;
    sd = 4;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 4;
    sd = 8;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 8;
    sd = 16;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 16;
    sd = 32;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 32;
    sd = 64;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 64;
    sd = 128;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 128;
    sd = 256;
    length1 = GetSDLength(sd, pos_cp1, it_cp1, ot_cp2, pos_cp2);
    o_length = length - length1;
    if (o_length < 0.0005)
        return 256;
    return 512;
}

void PushMaxValue(const Vector p, float &value) {
    if (value < hash_math::abs(p.x))
        value = hash_math::abs(p.x);
    if (value < hash_math::abs(p.y))
        value = hash_math::abs(p.y);
    if (value < hash_math::abs(p.z))
        value = hash_math::abs(p.z);
}

BOOL CCutPlaneApp::UpdateSplineList() {
    CUT_SPLINE temp_spline;
    CUT_HCP temp_hcp;
//    Vector pos1, pos2;

    sp_list.RemoveAll();
    move_cp.RemoveAll();
    for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
        temp_spline.sp = nullptr;
        temp_spline.seg.RemoveAll();
        if (plane.hg && (hsp == plane.sp1 || hsp == plane.sp2))
            continue;
        temp_spline.sp = hsp;
        for (HCP *cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (cp->GetNext()) {
                CUT_SEGMENT temp_segment;
                temp_segment.cp1 = cp;
                temp_segment.cp2 = cp->GetNext();
                const Vector pos_cp1 = *temp_segment.cp1->GetModelPosition();
                const Vector pos_cp2 = *temp_segment.cp2->GetModelPosition();
                const Vector it_cp1 = temp_segment.cp1->GetModelInTangent();
                const Vector ot_cp2 = temp_segment.cp2->GetModelOutTangent();
                const int subdiv = GetSubdivision(pos_cp1, it_cp1, ot_cp2, pos_cp2);
                if (subdiv == 1) {
                    temp_segment.pos_cp1 = pos_cp1;
                    temp_segment.pos_cp2 = pos_cp2;
                    PushMaxValue(temp_segment.pos_cp1, plane.max_value);
                    PushMaxValue(temp_segment.pos_cp2, plane.max_value);
                    temp_spline.seg.Add(temp_segment);
                } else {
                    const float subdiv_factor = hash_math::rcp((float)subdiv);
                    for (int j = 0; j < subdiv; ++j) {
                        temp_segment.pos_cp1 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, subdiv_factor * j);
                        temp_segment.pos_cp2 = subdivideSegment(pos_cp1, it_cp1, ot_cp2, pos_cp2, subdiv_factor * (j + 1));
                        PushMaxValue(temp_segment.pos_cp1, plane.max_value);
                        PushMaxValue(temp_segment.pos_cp2, plane.max_value);
                        temp_spline.seg.Add(temp_segment);
                    }
                }
            }
            temp_hcp.cp = cp;
            temp_hcp.pos = *cp->GetWorldPosition();
            temp_hcp.tomove = false;
            //         if (cp->IsHide()) {
            //			temp_hcp.cp = cp;
            //         }
            move_cp.Add(temp_hcp);
            if (cp->IsLoop())
                break;
        }
        sp_list.Add(temp_spline);
        //		temp_spline.seg.RemoveAll();
    }
    return !sp_list.IsEmpty();
}

BOOL CCutPlaneApp::CreatePlane() {
    Vector pos;
    if (plane.hg) {
        HModelCache::DeleteHandle(plane.hg);
        hmc->DeleteSpline(plane.sp1);
        hmc->DeleteSpline(plane.sp2);
        hmc->SetChanged(true);
        plane.hg = nullptr;
        //		delete plane.hg;
    }
    pos.Set(0.F);
    const UINT u_max_value = (UINT)(plane.max_value + plane.max_value);
    const auto max_value = (float)u_max_value;
#ifdef _DEBUG
    fsd << "max_value org " << plane.max_value << nl;
    fsd << "max_value neu " << max_value << nl << nl;
#endif
    plane.sp1 = hmc->CreateSpline();
    pos.x = -max_value;
    pos.z = -max_value;
    plane.cp[0] = plane.sp1->CreateCPAtTail(pos);
    pos.x = -max_value;
    pos.z = max_value;
    plane.cp[1] = plane.sp1->CreateCPAtTail(pos);
    pos.x = max_value;
    pos.z = max_value;
    plane.cp[2] = plane.sp1->CreateCPAtTail(pos);
    plane.sp2 = hmc->CreateSpline();
    pos.x = max_value;
    pos.z = max_value;
    plane.cp[3] = plane.sp2->CreateCPAtTail(pos);
    pos.x = max_value;
    pos.z = -max_value;
    plane.cp[4] = plane.sp2->CreateCPAtTail(pos);
    pos.x = -max_value;
    pos.z = -max_value;
    plane.cp[5] = plane.sp2->CreateCPAtTail(pos);
    hmc->AttachCPs(plane.cp[3], plane.cp[2]);
    hmc->AttachCPs(plane.cp[0], plane.cp[5]);
    plane.cp[0]->SetPeaked();
    plane.cp[1]->SetPeaked();
    plane.cp[2]->SetPeaked();
    plane.cp[3]->SetPeaked();
    plane.cp[4]->SetPeaked();
    plane.cp[5]->SetPeaked();
    plane.hg = hmc->CreateGroup("CutPlane");
    plane.hg->AddCP(plane.cp[0]);
    plane.hg->AddCP(plane.cp[1]);
    plane.hg->AddCP(plane.cp[2]);
    plane.hg->AddCP(plane.cp[3]);
    plane.hg->AddCP(plane.cp[4]);
    plane.hg->AddCP(plane.cp[5]);
    plane.infinite = false;
    plane.addring = false;
    hmc->OnModified();
    hmc->SetChanged(true);
    hmc->FindPatches();
    plane.hp = hmc->FindPatch(plane.cp[0], plane.cp[1], plane.cp[2], plane.cp[3]);
    plane.hg->HilightInProjectBar();
    return true;
}

void CCutPlaneApp::Cleanup() {
#ifdef _DEBUG
    DebugOut();
    fsd.Close();
#endif
    sp_list.RemoveAll();
    move_cp.RemoveAll();
    if (hmc) {
        for (int i = 0; i < cp_list.GetSize(); ++i) {
            hmc->DeleteSpline(cp_list[i].hsp);
        }
    }
    cp_list.RemoveAll();
    if (plane.hg && hmc) {
        HModelCache::DeleteHandle(plane.hg);
        //		delete plane.hg;
        hmc->DeleteSpline(plane.sp1);
        hmc->DeleteSpline(plane.sp2);
        plane.hg = nullptr;
    }
    if (mdlg) {
        mdlg->EndDialog(0);
        delete mdlg;
    }
    mdlg = nullptr;
    if (hmc) {
        hmc->OnModified();
        hmc->SetChanged(true);
        hmc->FindPatches();
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
}

float distRayPlane(const Vector RayOrig, const Vector RayDir, const Vector PlanePoint, const Vector PlaneNormal) {
    const float numer = PlaneNormal.Dot(PlanePoint - RayOrig);
    const float denom = PlaneNormal.Dot(RayDir - RayOrig);
    if (denom == 0.F)
        return -1.F;
    const float dist = numer / denom;
    if (dist >= 0.F && dist < 1.F) {
        return dist;
    }
    return -1;
}

bool CollideTest(const Vector rOrigin, const Vector rDest, const Vector pOrigin, const Vector pNormal, Vector &collisionPoint) {
    collisionPoint.Set(0.F);
    const float dist = distRayPlane(rOrigin, rDest, pOrigin, pNormal);
    if (dist == -1.F)
        return false;
    collisionPoint = (rDest - rOrigin) * dist + rOrigin;
    return true;
}

bool SameSide(const Vector p1, const Vector p2, const Vector a, const Vector b) {
    const Vector cp1 = Cross(b - a, p1 - a);
    const Vector cp2 = Cross(b - a, p2 - a);
    return Dot(cp1, cp2) >= 0.F;
}

bool PointInside(const Vector p, const Vector a, const Vector b, const Vector c) {
    return SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b);
}

void CCutPlaneApp::UpdateCutCPs() {
    Vector normal, point;//, direction;
    Vector ipoint;//, ipoint1;
    CCW_CP temp_cp;
    Vector a, b, c, d;
    HBone *hb = hmc->GetCurrentBone();
    for (int i = 0; i < cp_list.GetSize(); ++i) {
        hmc->DeleteSpline(cp_list[i].hsp);
    }
    cp_list.RemoveAll();
    hmc->OnModified();
    normal.Set(0.F);
    point.Set(0.F);
    if (hb) {
        const Matrix34 m1 = hb->GetScreenToModelMatrix();
        point = plane.hp->GetPointNormalOnPatch(0.5F, 0.5F, normal);
        normal *= m1;
        normal.FixZero();
        point *= m1;
        point.FixZero();
    } else {
        AfxMessageBox("Should never be reached",MB_OK);
        return;
    }
    plane.normal = normal.Normalized();
    plane.point = point;
#ifdef _DEBUG
    fsd << nl << " Intersections" << nl;
    fsd << "  point  " << point << nl;
    fsd << " normal  " << normal << nl << nl;
#endif
    a = *plane.hp->GetCP1()->GetWorldPosition();
    b = *plane.hp->GetCP2()->GetWorldPosition();
    c = *plane.hp->GetCP3()->GetWorldPosition();
    d = *plane.hp->GetCP4()->GetWorldPosition();
    for (int i = 0; i < sp_list.GetSize(); ++i) {
        for (int j = 0; j < sp_list[i].seg.GetSize(); ++j) {
            if (CollideTest(sp_list[i].seg[j].pos_cp1, sp_list[i].seg[j].pos_cp2, point, normal, ipoint)) {
                temp_cp.new_cp = nullptr;
                if (abs(Distance(ipoint, sp_list[i].seg[j].pos_cp1)) < 1e-5f)
                    temp_cp.new_cp = sp_list[i].seg[j].cp1;
                if (abs(Distance(ipoint, sp_list[i].seg[j].pos_cp2)) < 1e-5f)
                    temp_cp.new_cp = sp_list[i].seg[j].cp2;
#ifdef _DEBUG
                fsd << "Spline " << i << " " << sp_list[i].sp->GetMatchName() << nl;
                fsd << "Segment " << j << nl;
                fsd << "CP1 #" << sp_list[i].seg[j].cp1->GetID() << nl;
                fsd << "CP2 #" << sp_list[i].seg[j].cp2->GetID() << nl;
                fsd << "intersection point  " << ipoint << nl;
#endif
                if (!plane.infinite) {
                    if (PointInside(ipoint, a, b, c) || PointInside(ipoint, a, c, d)) {
#ifdef _DEBUG
                        fsd << "inside1  " << PointInside(ipoint, a, b, c) << nl;
                        fsd << "inside2  " << PointInside(ipoint, a, c, d) << nl;
                        fsd << "inside1r " << PointInside(ipoint, a, d, c) << nl;
                        fsd << "inside2r " << PointInside(ipoint, a, c, b) << nl << nl;
#endif
                        temp_cp.pos = ipoint;
                        if (!sp_list[i].seg[j].cp1->IsHide() && !sp_list[i].seg[j].cp2->IsHide() && !sp_list[i].seg[j].cp1->IsLocked() && !sp_list[i].seg[j].cp2->IsLocked()) {
                            temp_cp.before_cp = sp_list[i].seg[j].cp1;
                            temp_cp.after_cp = sp_list[i].seg[j].cp2;
                            //                     temp_cp.hp = hmc->FindPatch(sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp1);
#ifdef _DEBUG
                            [[maybe_unused]] UINT id1 = temp_cp.before_cp->GetID();
                            [[maybe_unused]] UINT id2 = temp_cp.after_cp->GetID();
#endif
                            //                     temp_cp.hp = hmc->FindPatch(sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp2,nullptr,nullptr);
                            cp_list.Add(temp_cp);
                        }
                    }
                } else {
                    temp_cp.pos = ipoint;
                    if (!sp_list[i].seg[j].cp1->IsHide() && !sp_list[i].seg[j].cp2->IsHide() && !sp_list[i].seg[j].cp1->IsLocked() && !sp_list[i].seg[j].cp2->IsLocked()) {
                        temp_cp.before_cp = sp_list[i].seg[j].cp1;
                        temp_cp.after_cp = sp_list[i].seg[j].cp2;
                        //                  temp_cp.hp = hmc->FindPatch(sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp1,sp_list[i].seg[j].cp1);
                        cp_list.Add(temp_cp);
                    }
                }
            }
        }
    }

    for (int i = 0; i < cp_list.GetSize(); ++i) {
        cp_list[i].hsp = hmc->CreateSpline();
        cp_list[i].cp_create = cp_list[i].hsp->CreateCPAtTail(cp_list[i].pos);
    }
    hmc->OnModified();
    GetHProject()->UpdateAllViews(TRUE);
}

void W_Sort_5(CArrayEx<CCW_CP, CCW_CP &> &pos) {
    const int iSize = pos.GetSize();

    for (int i = 1; i < iSize; ++i) {
        int iCurrentPos = i - 1;
        const CCW_CP pos_temp = pos[i];
        while (iCurrentPos >= 0 && pos[iCurrentPos].pos.y < pos_temp.pos.y) {
            pos[iCurrentPos + 1] = pos[iCurrentPos];
            iCurrentPos--;
        }
        pos[iCurrentPos + 1] = pos_temp;
    }
}

void W_Sort_4(CArrayEx<CCW_CP, CCW_CP &> &pos) {
    const int iSize = pos.GetSize();

    for (int i = 1; i < iSize; ++i) {
        int iCurrentPos = i - 1;
        const CCW_CP pos_temp = pos[i];
        while (iCurrentPos >= 0 && pos[iCurrentPos].pos.y > pos_temp.pos.y) {
            pos[iCurrentPos + 1] = pos[iCurrentPos];
            iCurrentPos--;
        }
        pos[iCurrentPos + 1] = pos_temp;
    }
}

void W_Sort_3(CArrayEx<CCW_CP, CCW_CP &> &pos) {
    const int iSize = pos.GetSize();

    for (int i = 1; i < iSize; ++i) {
        int iCurrentPos = i - 1;
        const CCW_CP pos_temp = pos[i];
        while (iCurrentPos >= 0 && pos[iCurrentPos].pos.z < pos_temp.pos.z) {
            pos[iCurrentPos + 1] = pos[iCurrentPos];
            iCurrentPos--;
        }
        pos[iCurrentPos + 1] = pos_temp;
    }
}

void W_Sort_2(CArrayEx<CCW_CP, CCW_CP &> &pos) {
    const int iSize = pos.GetSize();

    for (int i = 1; i < iSize; ++i) {
        int iCurrentPos = i - 1;
        const CCW_CP pos_temp = pos[i];
        while (iCurrentPos >= 0 && pos[iCurrentPos].pos.z > pos_temp.pos.z) {
            pos[iCurrentPos + 1] = pos[iCurrentPos];
            iCurrentPos--;
        }
        pos[iCurrentPos + 1] = pos_temp;
    }
}

void W_Sort_1(CArrayEx<CCW_CP, CCW_CP &> &pos) {
    const int iSize = pos.GetSize();

    for (int i = 1; i < iSize; ++i) {
        int iCurrentPos = i - 1;
        const CCW_CP pos_temp = pos[i];
        while (iCurrentPos >= 0 && pos[iCurrentPos].pos.x < pos_temp.pos.x) {
            pos[iCurrentPos + 1] = pos[iCurrentPos];
            iCurrentPos--;
        }
        pos[iCurrentPos + 1] = pos_temp;
    }
}

void W_Sort_0(CArrayEx<CCW_CP, CCW_CP &> &pos) {
    const int iSize = pos.GetSize();

    for (int i = 1; i < iSize; ++i) {
        int iCurrentPos = i - 1;
        const CCW_CP pos_temp = pos[i];
        while (iCurrentPos >= 0 && pos[iCurrentPos].pos.x > pos_temp.pos.x) {
            pos[iCurrentPos + 1] = pos[iCurrentPos];
            iCurrentPos--;
        }
        pos[iCurrentPos + 1] = pos_temp;
    }
}

bool GetCrossingPeaked(HCP *cp1, HCP *cp2) {
    HCP *cp_1, *cp_2;
    const HSpline *hsp1 = cp1->GetSpline();
    const HSpline *hsp2 = cp2->GetSpline();
    for (cp_1 = cp1->GetHead(); cp_1; cp_1 = cp_1->GetNextAttached()) {
        if (cp_1->GetSpline() != hsp1)
            break;
    }
    for (cp_2 = cp2->GetHead(); cp_2; cp_2 = cp_2->GetNextAttached()) {
        if (cp_2->GetSpline() != hsp2)
            break;
    }
    if (!cp_1 || !cp_2)
        return false;
    if (cp_1->IsPeaked() && cp_2->IsPeaked())
        return true;
    return false;
}

float GetCrossingMagnitude(HCP *cp1, HCP *cp2, const Vector pos) {
    if (!cp1 || !cp2)
        return 1.F;
    HCP *cp_1, *cp_2;
    float new_mag = 1.F;
    const HSpline *hsp1 = cp1->GetSpline();
    const HSpline *hsp2 = cp2->GetSpline();
    for (cp_1 = cp1->GetHead(); cp_1; cp_1 = cp_1->GetNextAttached()) {
        if (cp_1->GetSpline() != hsp1)
            break;
    }
    for (cp_2 = cp2->GetHead(); cp_2; cp_2 = cp_2->GetNextAttached()) {
        if (cp_2->GetSpline() != hsp2)
            break;
    }
    if (!cp_1 || !cp_2)
        return new_mag;

    const Vector pos_cp1 = *cp1->GetWorldPosition();
    const Vector pos_cp2 = *cp2->GetWorldPosition();
    const float dist = Distance(pos_cp1, pos_cp2);
    //	dist = Distance(*cp1->GetWorldPosition(),*cp2->GetWorldPosition());
    if (dist == 0)
        return 1.F;
    const float dist_1 = Distance(pos, pos_cp1);
    const float dist_2 = Distance(pos, pos_cp2);
    //	dist_1 = Distance(pos,*cp1->GetWorldPosition());
    //	dist_2 = Distance(pos,*cp2->GetWorldPosition());
    float proc_1 = dist_1 / dist;
    float proc_2 = dist_2 / dist;
    float p = proc_1 + proc_2;
    if (p > 1.F) {
        p = (proc_1 + proc_2 - 1.F) / 2.F;
        proc_1 -= p;
        proc_2 -= p;
    }
    if (p < 1.F) {
        p = (1.F - (proc_1 + proc_2)) / 2.F;
        proc_1 += p;
        proc_2 += p;
    }
    float mag_1 = (cp_1->GetInMagnitude() + cp_1->GetOutMagnitude()) / 2.F;
    mag_1 = mag_1 * proc_2;
    float mag_2 = (cp_2->GetInMagnitude() + cp_2->GetOutMagnitude()) / 2.F;
    mag_2 = mag_2 * proc_1;
    new_mag = (mag_1 + mag_2) / 100.F;
#ifndef _DEBUG
    if (!isfinite(new_mag))
        return 1.F;
#endif
    return new_mag;
}

float WDistancePointToPlane(const Vector &point, const Vector &pointonplane, const Vector &normal) {
    Vector delta = point;
    delta -= pointonplane;
    return Dot(delta, normal);
}

void CCutPlaneApp::MovePartModel() {
    for (int i = 0; i < move_cp.GetSize(); ++i) {
        if (move_cp[i].tomove)
            continue;
        move_cp[i].pos = *move_cp[i].cp->GetWorldPosition();
        const float dist = WDistancePointToPlane(move_cp[i].pos, plane.point, plane.normal);
        if (dist > 0)
            move_cp[i].tomove = true;
    }
    const Vector offset = plane.normal * plane.offset;
    for (int i = 0; i < move_cp.GetSize(); ++i) {
        if (!move_cp[i].tomove)
            continue;
#ifdef _DEBUG
        fsd << "CP#" << move_cp[i].cp->GetID() << nl;
        fsd << move_cp[i].pos << nl;
#endif
        move_cp[i].pos += offset;
#ifdef _DEBUG
        fsd << move_cp[i].pos << nl << nl;
#endif
        move_cp[i].cp->SetPosition(&move_cp[i].pos);
    }
}

/*
static int _cdecl PSRcmp(const void *a1, const void *a2) {
    CCW_CP *r1 = (CCW_CP *)a1;
    CCW_CP *r2 = (CCW_CP *)a2;
    if (r1->pos.x > r2->pos.x)
        return -1;
    if (r1->pos.x < r2->pos.x)
        return 1;
    if (r1->pos.y > r2->pos.y)
        return -1;
    if (r1->pos.y < r2->pos.y)
        return 1;
    if (r1->pos.z > r2->pos.z)
        return -1;
    if (r1->pos.z < r2->pos.z)
        return 1;
    return 0;
}
*/
/*
void _Sort_Patch(CArrayEx<CCW_CP,CCW_CP &> &pos) {
	CCW_CP pos_temp;
	int iCurrentPos = 0;
	int iSize = pos.GetSize();

	for (int i = 1;i<iSize;++i) {
		iCurrentPos = i-1;
		pos_temp = pos[i];
      while ((iCurrentPos >= 0) && !IsNeighborPatch(pos[iCurrentPos].hp, pos_temp.hp)) {
			 pos[iCurrentPos + 1] = pos[iCurrentPos];
			 iCurrentPos--;
		}
		pos[iCurrentPos + 1] = pos_temp;
	}
}
*/
BOOL IsCPInPatch(HPatch *patch, HCP *cp) {
    const HCP *head = cp->GetHead();
    if (patch->GetCP1() == cp || patch->GetCP2() == cp || patch->GetCP3() == cp || patch->GetCP4() == cp || patch->GetCP1() == head || patch->GetCP2() == head || patch->GetCP3() == head || patch->GetCP4() == head) {
        return TRUE;
    }
    return FALSE;
}

BOOL IsNeighbor(HModelCache *hmc, HCP *cp1, HCP *cp2, HCP *cp3, HCP *cp4) {
    const UINT azpatches = hmc->GetPatchCount();
    for (UINT i = 0; i < azpatches; ++i) {
        HPatch *patch = hmc->GetPatch(i);
        if (IsCPInPatch(patch, cp1) && IsCPInPatch(patch, cp2)) {
            if (IsCPInPatch(patch, cp3) && IsCPInPatch(patch, cp4)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void CCutPlaneApp::ApplyCutCPs() {
    HSpline *hsp{nullptr};
    HCP *cp1{nullptr};
    if (plane.addring) {
        float magnitude;
        Vector direction;
        Vector temp_pos;
        HSpline *hsp_ring1{nullptr};
        HCP *cp0{nullptr}, *cp2{nullptr};
        HCP *cp0_1{nullptr}, *cp1_1{nullptr}, *cp2_1{nullptr};
        bool sameposition;
        HSpline *hsp_ring = hmc->CreateSpline();
        if (plane.cut_splines)
            hsp_ring1 = hmc->CreateSpline();
        CArrayEx<CCW_CP, CCW_CP &> c_list;
        CArrayEx<CCW_CP, CCW_CP &> q8_list, q7_list, q6_list, q5_list, q4_list, q3_list, q2_list, q1_list, q0_list;
        //center point for new cp's
        temp_pos.Set(0.F);
        for (int i = 0; i < cp_list.GetSize(); ++i) {
            temp_pos += cp_list[i].pos;
        }
        temp_pos /= (float)cp_list.GetSize();
        for (int i = 0; i < cp_list.GetSize(); ++i) {
            cp_list[i].pos_sort = cp_list[i].pos - temp_pos;
        }

        //finding quadrants
        for (int i = 0; i < cp_list.GetSize(); ++i) {
            temp_pos = cp_list[i].pos_sort - plane.point;
            if (plane.normal.x == 1 || plane.normal.x == -1) {
                if (temp_pos.z < 0 && temp_pos.y == 0)
                    q0_list.Add(cp_list[i]);
                if (temp_pos.z < 0 && temp_pos.y < 0)
                    q1_list.Add(cp_list[i]);
                if (temp_pos.z == 0 && temp_pos.y < 0)
                    q2_list.Add(cp_list[i]);
                if (temp_pos.z > 0 && temp_pos.y < 0)
                    q3_list.Add(cp_list[i]);
                if (temp_pos.z > 0 && temp_pos.y == 0)
                    q4_list.Add(cp_list[i]);
                if (temp_pos.z > 0 && temp_pos.y > 0)
                    q5_list.Add(cp_list[i]);
                if (temp_pos.z == 0 && temp_pos.y > 0)
                    q6_list.Add(cp_list[i]);
                if (temp_pos.z < 0 && temp_pos.y > 0)
                    q7_list.Add(cp_list[i]);
                if (temp_pos.z == 0 && temp_pos.y == 0)
                    q8_list.Add(cp_list[i]);
            } else {
                if (plane.normal.z == 1 || plane.normal.z == -1) {
                    if (temp_pos.x > 0 && temp_pos.y == 0)
                        q0_list.Add(cp_list[i]);
                    if (temp_pos.x > 0 && temp_pos.y < 0)
                        q1_list.Add(cp_list[i]);
                    if (temp_pos.x == 0 && temp_pos.y < 0)
                        q2_list.Add(cp_list[i]);
                    if (temp_pos.x < 0 && temp_pos.y < 0)
                        q3_list.Add(cp_list[i]);
                    if (temp_pos.x < 0 && temp_pos.y == 0)
                        q4_list.Add(cp_list[i]);
                    if (temp_pos.x < 0 && temp_pos.y > 0)
                        q5_list.Add(cp_list[i]);
                    if (temp_pos.x == 0 && temp_pos.y > 0)
                        q6_list.Add(cp_list[i]);
                    if (temp_pos.x > 0 && temp_pos.y > 0)
                        q7_list.Add(cp_list[i]);
                    if (temp_pos.x == 0 && temp_pos.y == 0)
                        q8_list.Add(cp_list[i]);
                } else {
                    if (temp_pos.x > 0 && temp_pos.z == 0)
                        q0_list.Add(cp_list[i]);
                    if (temp_pos.x > 0 && temp_pos.z > 0)
                        q1_list.Add(cp_list[i]);
                    if (temp_pos.x == 0 && temp_pos.z > 0)
                        q2_list.Add(cp_list[i]);
                    if (temp_pos.x < 0 && temp_pos.z > 0)
                        q3_list.Add(cp_list[i]);
                    if (temp_pos.x < 0 && temp_pos.z == 0)
                        q4_list.Add(cp_list[i]);
                    if (temp_pos.x < 0 && temp_pos.z < 0)
                        q5_list.Add(cp_list[i]);
                    if (temp_pos.x == 0 && temp_pos.z < 0)
                        q6_list.Add(cp_list[i]);
                    if (temp_pos.x > 0 && temp_pos.z < 0)
                        q7_list.Add(cp_list[i]);
                    if (temp_pos.x == 0 && temp_pos.z == 0)
                        q8_list.Add(cp_list[i]);
                }
            }

            /*
                        if ((temp_pos.x > 0) && (temp_pos.z == 0)) q0_list.Add(cp_list[i]);
                        if ((temp_pos.x > 0) && (temp_pos.z > 0)) q1_list.Add(cp_list[i]);
                        if ((temp_pos.x == 0) && (temp_pos.z > 0)) q2_list.Add(cp_list[i]);
                        if ((temp_pos.x < 0) && (temp_pos.z > 0)) q3_list.Add(cp_list[i]);
                        if ((temp_pos.x < 0) && (temp_pos.z == 0)) q4_list.Add(cp_list[i]);
                        if ((temp_pos.x < 0) && (temp_pos.z < 0)) q5_list.Add(cp_list[i]);
                        if ((temp_pos.x == 0) && (temp_pos.z < 0)) q6_list.Add(cp_list[i]);
                        if ((temp_pos.x > 0) && (temp_pos.z < 0)) q7_list.Add(cp_list[i]);
                        if ((temp_pos.x == 0) && (temp_pos.z == 0)) q8_list.Add(cp_list[i]);
            */
        }

#ifdef _DEBUG
        fsd << nl << "Unsortet " << cp_list.GetSize() << nl;
        for (int i = 0; i < cp_list.GetSize(); ++i) {
            fsd << " Pos " << cp_list[i].pos << nl;
        }
#endif
        if (plane.normal.x == 1 || plane.normal.x == -1) {
            if (q8_list.GetSize() > 0) {
                W_Sort_4(q8_list);
                for (int i = 0; i < q8_list.GetSize(); ++i) {
                    c_list.Add(q8_list[i]);
                }
                q8_list.RemoveAll();
            }
            if (q7_list.GetSize() > 0) {
                W_Sort_4(q7_list);
                for (int i = 0; i < q7_list.GetSize(); ++i) {
                    c_list.Add(q7_list[i]);
                }
                q7_list.RemoveAll();
            }
            if (q6_list.GetSize() > 0) {
                W_Sort_5(q6_list);
                for (int i = 0; i < q6_list.GetSize(); ++i) {
                    c_list.Add(q6_list[i]);
                }
                q6_list.RemoveAll();
            }
            if (q5_list.GetSize() > 0) {
                W_Sort_5(q5_list);
                for (int i = 0; i < q5_list.GetSize(); ++i) {
                    c_list.Add(q5_list[i]);
                }
                q5_list.RemoveAll();
            }
            if (q4_list.GetSize() > 0) {
                W_Sort_3(q4_list);
                for (int i = 0; i < q4_list.GetSize(); ++i) {
                    c_list.Add(q4_list[i]);
                }
                q4_list.RemoveAll();
            }
            if (q3_list.GetSize() > 0) {
                W_Sort_5(q3_list);
                for (int i = 0; i < q3_list.GetSize(); ++i) {
                    c_list.Add(q3_list[i]);
                }
                q3_list.RemoveAll();
            }
            if (q2_list.GetSize() > 0) {
                W_Sort_4(q2_list);
                for (int i = 0; i < q2_list.GetSize(); ++i) {
                    c_list.Add(q2_list[i]);
                }
                q2_list.RemoveAll();
            }
            if (q1_list.GetSize() > 0) {
                W_Sort_4(q1_list);
                for (int i = 0; i < q1_list.GetSize(); ++i) {
                    c_list.Add(q1_list[i]);
                }
                q1_list.RemoveAll();
            }
            if (q0_list.GetSize() > 0) {
                W_Sort_3(q0_list);
                for (int i = 0; i < q0_list.GetSize(); ++i) {
                    c_list.Add(q0_list[i]);
                }
                q0_list.RemoveAll();
            }
        } else {
            if (plane.normal.z == 1 || plane.normal.z == -1) {
                if (q8_list.GetSize() > 0) {
                    W_Sort_4(q8_list);
                    for (int i = 0; i < q8_list.GetSize(); ++i) {
                        c_list.Add(q8_list[i]);
                    }
                    q8_list.RemoveAll();
                }
                if (q7_list.GetSize() > 0) {
                    W_Sort_1(q7_list);
                    for (int i = 0; i < q7_list.GetSize(); ++i) {
                        c_list.Add(q7_list[i]);
                    }
                    q7_list.RemoveAll();
                }
                if (q6_list.GetSize() > 0) {
                    W_Sort_5(q6_list);
                    for (int i = 0; i < q6_list.GetSize(); ++i) {
                        c_list.Add(q6_list[i]);
                    }
                    q6_list.RemoveAll();
                }
                if (q5_list.GetSize() > 0) {
                    W_Sort_1(q5_list);
                    for (int i = 0; i < q5_list.GetSize(); ++i) {
                        c_list.Add(q5_list[i]);
                    }
                    q5_list.RemoveAll();
                }
                if (q4_list.GetSize() > 0) {
                    W_Sort_0(q4_list);
                    for (int i = 0; i < q4_list.GetSize(); ++i) {
                        c_list.Add(q4_list[i]);
                    }
                    q4_list.RemoveAll();
                }
                if (q3_list.GetSize() > 0) {
                    W_Sort_0(q3_list);
                    for (int i = 0; i < q3_list.GetSize(); ++i) {
                        c_list.Add(q3_list[i]);
                    }
                    q3_list.RemoveAll();
                }
                if (q2_list.GetSize() > 0) {
                    W_Sort_4(q2_list);
                    for (int i = 0; i < q2_list.GetSize(); ++i) {
                        c_list.Add(q2_list[i]);
                    }
                    q2_list.RemoveAll();
                }
                if (q1_list.GetSize() > 0) {
                    W_Sort_0(q1_list);
                    for (int i = 0; i < q1_list.GetSize(); ++i) {
                        c_list.Add(q1_list[i]);
                    }
                    q1_list.RemoveAll();
                }
                if (q0_list.GetSize() > 0) {
                    W_Sort_0(q0_list);
                    for (int i = 0; i < q0_list.GetSize(); ++i) {
                        c_list.Add(q0_list[i]);
                    }
                    q0_list.RemoveAll();
                }
            } else {
                if (q8_list.GetSize() > 0) {
                    W_Sort_4(q8_list);
                    for (int i = 0; i < q8_list.GetSize(); ++i) {
                        c_list.Add(q8_list[i]);
                    }
                    q8_list.RemoveAll();
                }
                if (q7_list.GetSize() > 0) {
                    W_Sort_1(q7_list);
                    for (int i = 0; i < q7_list.GetSize(); ++i) {
                        c_list.Add(q7_list[i]);
                    }
                    q7_list.RemoveAll();
                }
                if (q6_list.GetSize() > 0) {
                    W_Sort_2(q6_list);
                    for (int i = 0; i < q6_list.GetSize(); ++i) {
                        c_list.Add(q6_list[i]);
                    }
                    q6_list.RemoveAll();
                }
                if (q5_list.GetSize() > 0) {
                    W_Sort_1(q5_list);
                    for (int i = 0; i < q5_list.GetSize(); ++i) {
                        c_list.Add(q5_list[i]);
                    }
                    q5_list.RemoveAll();
                }
                if (q4_list.GetSize() > 0) {
                    W_Sort_0(q4_list);
                    for (int i = 0; i < q4_list.GetSize(); ++i) {
                        c_list.Add(q4_list[i]);
                    }
                    q4_list.RemoveAll();
                }
                if (q3_list.GetSize() > 0) {
                    W_Sort_0(q3_list);
                    for (int i = 0; i < q3_list.GetSize(); ++i) {
                        c_list.Add(q3_list[i]);
                    }
                    q3_list.RemoveAll();
                }
                if (q2_list.GetSize() > 0) {
                    W_Sort_3(q2_list);
                    for (int i = 0; i < q2_list.GetSize(); ++i) {
                        c_list.Add(q2_list[i]);
                    }
                    q2_list.RemoveAll();
                }
                if (q1_list.GetSize() > 0) {
                    W_Sort_0(q1_list);
                    for (int i = 0; i < q1_list.GetSize(); ++i) {
                        c_list.Add(q1_list[i]);
                    }
                    q1_list.RemoveAll();
                }
                if (q0_list.GetSize() > 0) {
                    W_Sort_0(q0_list);
                    for (int i = 0; i < q0_list.GetSize(); ++i) {
                        c_list.Add(q0_list[i]);
                    }
                    q0_list.RemoveAll();
                }
            }
        }
#ifdef _DEBUG
        fsd << nl << "Sortet " << c_list.GetSize() << nl;
        for (int i = 0; i < c_list.GetSize(); ++i) {
            fsd << " Pos " << c_list[i].pos << nl;
        }
#endif
        //Patch sorting
        for (int i = 1; i < c_list.GetSize(); ++i) {
            if (!IsNeighbor(hmc, c_list[i - 1].after_cp, c_list[i - 1].before_cp, c_list[i].after_cp, c_list[i].before_cp)) {
                for (int j = i + 1; j < c_list.GetSize(); ++j) {
                    if (IsNeighbor(hmc, c_list[i - 1].after_cp, c_list[i - 1].before_cp, c_list[j].after_cp, c_list[j].before_cp)) {
                        CCW_CP t_cp = c_list[i];
                        c_list[i] = c_list[j];
                        c_list[j] = t_cp;
                    }
                }
            }
        }

#ifdef _DEBUG
        fsd << nl << "Sortet Patch " << c_list.GetSize() << nl;
        for (int i = 0; i < c_list.GetSize(); ++i) {
            fsd << " Pos " << c_list[i].pos << nl;
        }
#endif

        for (int i = 0; i < c_list.GetSize(); ++i) {
            hsp = c_list[i].after_cp->GetSpline();
            sameposition = static_cast<bool>(c_list[i].new_cp);
            if (!sameposition)
                c_list[i].new_cp = cp1 = hsp->CreateCPBefore(c_list[i].after_cp, c_list[i].pos);
            if (plane.cut_splines) {
                direction = (*c_list[i].after_cp->GetWorldPosition() - c_list[i].pos).Normalize();
                if (Dot(plane.normal, direction) >= 0.F) {
                    c_list[i].new_cp1 = cp1_1 = hsp->CreateCPBefore(c_list[i].after_cp, c_list[i].pos);
                } else {
                    c_list[i].new_cp1 = cp1_1 = hsp->CreateCPBefore(c_list[i].new_cp, c_list[i].pos);
                }
            }
            if (i == 0) {
                cp0 = c_list[i].new_cp;
                if (plane.cut_splines)
                    cp0_1 = cp1_1;
            }
            if (!sameposition) {
                cp2 = hsp_ring->CreateCPAtTail(c_list[i].pos);
                if (GetCrossingPeaked(c_list[i].before_cp, c_list[i].after_cp)) {
                    cp2->SetPeaked();
                } else {
                    cp2->SetSmooth();
                    magnitude = GetCrossingMagnitude(c_list[i].before_cp, c_list[i].after_cp, c_list[i].pos);
                    cp2->SetInMagnitude(magnitude * 100);
                    cp2->SetOutMagnitude(magnitude * 100);
                }
                hmc->AttachCPs(cp1, cp2);
            }
            if (plane.cut_splines) {
                cp2_1 = hsp_ring1->CreateCPAtTail(c_list[i].pos);
                if (GetCrossingPeaked(c_list[i].before_cp, c_list[i].after_cp)) {
                    cp2_1->SetPeaked();
                } else {
                    cp2_1->SetSmooth();
                    magnitude = GetCrossingMagnitude(c_list[i].before_cp, c_list[i].after_cp, c_list[i].pos);
                    cp2_1->SetInMagnitude(magnitude * 100);
                    cp2_1->SetOutMagnitude(magnitude * 100);
                }
                hmc->AttachCPs(cp1_1, cp2_1);
            }
            hmc->DeleteSpline(c_list[i].hsp);
            c_list[i].hsp = nullptr;
        }
        if (c_list.GetSize() > 2) {
            cp2 = hsp_ring->CreateCPAtTail(c_list[0].pos);
            if (GetCrossingPeaked(c_list[0].before_cp, c_list[0].after_cp)) {
                cp2->SetPeaked();
            } else {
                cp2->SetSmooth();
                magnitude = GetCrossingMagnitude(c_list[0].before_cp, c_list[0].after_cp, c_list[0].pos);
                cp2->SetInMagnitude(magnitude * 100);
                cp2->SetOutMagnitude(magnitude * 100);
            }
            hmc->AttachCPs(cp2, cp0);
            if (plane.cut_splines) {
                cp2_1 = hsp_ring1->CreateCPAtTail(c_list[0].pos);
                if (GetCrossingPeaked(c_list[0].before_cp, c_list[0].after_cp)) {
                    cp2_1->SetPeaked();
                } else {
                    cp2_1->SetSmooth();
                    magnitude = GetCrossingMagnitude(c_list[0].before_cp, c_list[0].after_cp, c_list[0].pos);
                    cp2_1->SetInMagnitude(magnitude * 100);
                    cp2_1->SetOutMagnitude(magnitude * 100);
                }
                hmc->AttachCPs(cp2_1, cp0_1);
            }
        }
        if (plane.break_splines) {
            hmc->OnModified();
            hmc->SetChanged(true);
            for (int i = 0; i < c_list.GetSize(); ++i) {
                direction = (*c_list[i].after_cp->GetWorldPosition() - c_list[i].pos).Normalize();
                if (Dot(plane.normal, direction) >= 0.F) {
                    if (c_list[i].new_cp)
                        hmc->BreakSpline(c_list[i].new_cp);
                } else {
                    if (c_list[i].before_cp)
                        hmc->BreakSpline(c_list[i].before_cp);
                }
            }
        }
        if (plane.cut_splines) {
            CUT_HCP temp_hcp;
            hmc->OnModified();
            hmc->SetChanged(true);
            for (int i = 0; i < c_list.GetSize(); ++i) {
                direction = (*c_list[i].after_cp->GetWorldPosition() - *c_list[i].before_cp->GetWorldPosition()).Normalize();
                if (Dot(plane.normal, direction) >= 0.F) {
                    temp_hcp.pos = c_list[i].pos;
                    temp_hcp.tomove = true;
                    for (HCP *cph = c_list[i].new_cp1->GetHead(); cph; cph = cph->GetNextAttached()) {
                        temp_hcp.cp = cph;
                        move_cp.Add(temp_hcp);
                    }
                } else {
                    temp_hcp.pos = c_list[i].pos;
                    temp_hcp.tomove = true;
                    for (HCP *cph = c_list[i].new_cp->GetHead(); cph; cph = cph->GetNextAttached()) {
                        temp_hcp.cp = cph;
                        move_cp.Add(temp_hcp);
                    }
                }

                direction = (*c_list[i].after_cp->GetWorldPosition() - c_list[i].pos).Normalize();
                if (Dot(plane.normal, direction) >= 0.F) {
                    hmc->BreakSpline(c_list[i].new_cp);
                } else {
                    hmc->BreakSpline(c_list[i].new_cp1);
                }
            }
            if (plane.offset > 0.F)
                MovePartModel();
        }
        c_list.RemoveAll();
    } else {
        for (int i = 0; i < cp_list.GetSize(); ++i) {
            hsp = cp_list[i].after_cp->GetSpline();
            cp1 = hsp->CreateCPBefore(cp_list[i].after_cp, cp_list[i].pos);
            hmc->DeleteSpline(cp_list[i].hsp);
        }
    }
    cp_list.RemoveAll();
    hmc->OnModified();

    //    HGroupCP *accumgroup = nullptr;
    HGroup *hg_temp = hmc->CreateGroup("CutPlane_temp");
    for (HSpline *hsp_0 = hmc->GetHeadSpline(); hsp_0; hsp_0 = hsp_0->GetNextSpline()) {
        for (HCP *cp = hsp_0->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (!plane.hg->IsCPInGroup(cp)) {
                hg_temp->AddCP(cp);
                //		    	cp->AddToGroup(&accumgroup);
            }
            if (cp->IsLoop())
                break;
        }
    }
    //	hmc->AddToTemporaryGroup(accumgroup);
    GetHProject()->DeselectAll();
    for (HSpline *hsp_0 = hmc->GetHeadSpline(); hsp_0; hsp_0 = hsp_0->GetNextSpline()) {
        for (HCP *cp = hsp_0->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (!plane.hg->IsCPInGroup(cp)) {
                hg_temp->RemoveCP(cp);
                //		    	cp->AddToGroup(&accumgroup);
            }
            if (cp->IsLoop())
                break;
        }
    }
    GetHProject()->DeselectAll();
    HModelCache::DeleteHandle(hg_temp);
    UpdateSplineList();
    if (mdlg)
        mdlg->ShowWindow(SW_SHOWNORMAL);

    plane.hp = hmc->FindPatch(plane.cp[0], plane.cp[1], plane.cp[2], plane.cp[3]);

    plane.hg->HilightInProjectBar();
}
