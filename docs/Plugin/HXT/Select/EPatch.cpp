#include "StdAfx.h"
#include "Select.h"

HCP *findsecondcp(HCP *cp1, const HCP *cp2) {
    HSpline *hsp = cp1->GetSpline();
    for (HCP *temp = hsp->GetHeadCP(); temp; temp = temp->GetNext()) {
        for (HCP *temp1 = temp->GetHead(); temp1; temp1 = temp1->GetNextAttached()) {
            if (temp1 == cp2)
                return temp;
            //			if ((temp1 == cp2) && (temp != cp2)) return temp;
        }
        if (temp->IsLoop())
            return nullptr;
    }
    return nullptr;
}

void swapcp(HCP **cp1, HCP **cp2) {
    HCP *temp = *cp1;
    *cp1 = *cp2;
    *cp2 = temp;
}

inline double elength(const Vector v) {
    return hash_math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline double elength(const Vector v1, const Vector v2) {
    return elength(v2 - v1);
}

inline void CalcTangent(const Vector &p0, const Vector &p1, const Vector &p2, const Vector &p3, Vector &t) {
    t = (-p0 - p1 + p2 + p3) * 0.75F;
}

Vector emidPoint(const Vector A, const Vector B) {
    Vector m = A + B;
    m *= 0.5F;
    return m;
}

Vector espMid(const Vector p1, const Vector p2, const Vector p3, const Vector p4) {
    const Vector l2 = emidPoint(p1, p2);
    const Vector h = emidPoint(p2, p3);
    const Vector r3 = emidPoint(p3, p4);
    const Vector l3 = emidPoint(l2, h);
    const Vector r2 = emidPoint(h, r3);
    const Vector c = emidPoint(l3, r2);
    return c;
}

void eGetPatchMid_3(EPatch *ep) {
    Vector pos[16];

    pos[0] = ep->pos[0];
    pos[2] = ep->pos[3];
    pos[4] = ep->pos[6];
    ep->sdpos[1] = pos[1] = espMid(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3]);
    ep->sdpos[2] = pos[3] = espMid(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6]);
    ep->sdpos[3] = pos[5] = espMid(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9]);
    const Vector mp_temp = (pos[1] + pos[3] + pos[5]) / 3.F;
    ep->sdpos[0] = mp_temp;
}

void eGetPatchMid_4(EPatch *ep) {
    Vector pos[16];

    pos[0] = ep->pos[0];
    pos[2] = ep->pos[3];
    pos[4] = ep->pos[6];
    pos[6] = ep->pos[9];
    ep->sdpos[1] = pos[1] = espMid(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3]);
    ep->sdpos[2] = pos[3] = espMid(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6]);
    ep->sdpos[3] = pos[5] = espMid(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9]);
    ep->sdpos[4] = pos[7] = espMid(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[0]);
    Vector mp_temp = (pos[1] - pos[0] + (pos[5] - pos[6])) * 0.5F;
    mp_temp += (pos[1] - pos[2] + (pos[5] - pos[4])) * 0.5F;
    mp_temp += (pos[3] - pos[2] + (pos[7] - pos[0])) * 0.5F;
    mp_temp += (pos[3] - pos[4] + (pos[7] - pos[6])) * 0.5F;
    mp_temp /= 4;
    pos[8] = (pos[1] + pos[3] + pos[5] + pos[7]) / 4.F;
    ep->sdpos[0] = pos[8] + mp_temp;
}

void eGetPatchMid_5(EPatch *ep) {
    Vector pos[16];

    pos[0] = ep->pos[0];
    pos[2] = ep->pos[3];
    pos[4] = ep->pos[6];
    pos[6] = ep->pos[9];
    pos[8] = ep->pos[12];
    ep->sdpos[1] = pos[1] = espMid(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3]);
    ep->sdpos[2] = pos[3] = espMid(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6]);
    ep->sdpos[3] = pos[5] = espMid(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9]);
    ep->sdpos[4] = pos[7] = espMid(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[12]);
    ep->sdpos[5] = pos[9] = espMid(ep->pos[12], ep->pos[13], ep->pos[14], ep->pos[0]);
    Vector mp_temp = (pos[1] - pos[0] + (pos[7] - pos[8])) * 0.5F;
    mp_temp += (pos[3] - pos[2] + (pos[9] - pos[0])) * 0.5F;
    mp_temp += (pos[5] - pos[4] + (pos[1] - pos[2])) * 0.5F;
    mp_temp += (pos[7] - pos[6] + (pos[3] - pos[4])) * 0.5F;
    mp_temp += (pos[9] - pos[8] + (pos[5] - pos[6])) * 0.5F;
    mp_temp /= 5;
    pos[10] = (pos[1] + pos[3] + pos[5] + pos[7] + pos[9]) / 5.F;
    ep->sdpos[0] = pos[10] + mp_temp;
}

void eGetNormal_3(EPatch *ep) {
    Vector t;
    CalcTangent(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3], t);
    Vector delta1 = ep->pos[0];
    delta1 -= ep->pos[11];
    Vector delta2 = ep->pos[3];
    delta2 -= ep->pos[4];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (ep->opatch->GetCP1()->IsFlip())
        normal1.Negate();
    ep->ndir[1] = normal1;
    CalcTangent(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6], t);
    delta1 = ep->pos[3];
    delta1 -= ep->pos[2];
    delta2 = ep->pos[6];
    delta2 -= ep->pos[7];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (ep->opatch->GetCP2()->IsFlip())
        normal2.Negate();
    ep->ndir[2] = normal2;
    CalcTangent(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[0], t);
    delta1 = ep->pos[6];
    delta1 -= ep->pos[5];
    delta2 = ep->pos[0];
    delta2 -= ep->pos[1];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal3 = Cross(delta1, t);
    normal3.Normalize();
    if (ep->opatch->GetCP3()->IsFlip())
        normal3.Negate();
    ep->ndir[3] = normal3;
    const Vector normal = (normal1 + normal2 + normal3) / 3.F;
    ep->ndir[0] = normal;
}

void eGetNormal_4(EPatch *ep) {
    Vector t;
    CalcTangent(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3], t);
    Vector delta1 = ep->pos[0];
    delta1 -= ep->pos[11];
    Vector delta2 = ep->pos[3];
    delta2 -= ep->pos[4];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (ep->opatch->GetCP1()->IsFlip())
        normal1.Negate();
    ep->ndir[1] = normal1;
    CalcTangent(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6], t);
    delta1 = ep->pos[3];
    delta1 -= ep->pos[2];
    delta2 = ep->pos[6];
    delta2 -= ep->pos[7];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (ep->opatch->GetCP2()->IsFlip())
        normal2.Negate();
    ep->ndir[2] = normal2;
    CalcTangent(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9], t);
    delta1 = ep->pos[6];
    delta1 -= ep->pos[5];
    delta2 = ep->pos[9];
    delta2 -= ep->pos[10];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal3 = Cross(delta1, t);
    normal3.Normalize();
    if (ep->opatch->GetCP3()->IsFlip())
        normal3.Negate();
    ep->ndir[3] = normal3;
    CalcTangent(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[0], t);
    delta1 = ep->pos[9];
    delta1 -= ep->pos[8];
    delta2 = ep->pos[0];
    delta2 -= ep->pos[1];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal4 = Cross(delta1, t);
    normal4.Normalize();
    if (ep->opatch->GetCP4()->IsFlip())
        normal4.Negate();
    ep->ndir[4] = normal4;
    const Vector normal = (normal1 + normal2 + normal3 + normal4) / 4.F;
    ep->ndir[0] = normal;
}

void eGetNormal_5(EPatch *ep) {
    Vector t;
    CalcTangent(ep->pos[0], ep->pos[1], ep->pos[2], ep->pos[3], t);
    Vector delta1 = ep->pos[0];
    delta1 -= ep->pos[11];
    Vector delta2 = ep->pos[3];
    delta2 -= ep->pos[4];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal1 = Cross(delta1, t);
    normal1.Normalize();
    if (ep->opatch5->GetCP1()->IsFlip())
        normal1.Negate();
    ep->ndir[1] = normal1;
    CalcTangent(ep->pos[3], ep->pos[4], ep->pos[5], ep->pos[6], t);
    delta1 = ep->pos[3];
    delta1 -= ep->pos[2];
    delta2 = ep->pos[6];
    delta2 -= ep->pos[7];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal2 = Cross(delta1, t);
    normal2.Normalize();
    if (ep->opatch5->GetCP2()->IsFlip())
        normal2.Negate();
    ep->ndir[2] = normal2;
    CalcTangent(ep->pos[6], ep->pos[7], ep->pos[8], ep->pos[9], t);
    delta1 = ep->pos[6];
    delta1 -= ep->pos[5];
    delta2 = ep->pos[9];
    delta2 -= ep->pos[10];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal3 = Cross(delta1, t);
    normal3.Normalize();
    if (ep->opatch5->GetCP3()->IsFlip())
        normal3.Negate();
    ep->ndir[3] = normal3;
    CalcTangent(ep->pos[9], ep->pos[10], ep->pos[11], ep->pos[12], t);
    delta1 = ep->pos[9];
    delta1 -= ep->pos[8];
    delta2 = ep->pos[12];
    delta2 -= ep->pos[13];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal4 = Cross(delta1, t);
    normal4.Normalize();
    if (ep->opatch5->GetCP4()->IsFlip())
        normal4.Negate();
    ep->ndir[4] = normal4;
    CalcTangent(ep->pos[12], ep->pos[13], ep->pos[14], ep->pos[0], t);
    delta1 = ep->pos[12];
    delta1 -= ep->pos[11];
    delta2 = ep->pos[0];
    delta2 -= ep->pos[1];
    delta1 += delta2;
    delta1 *= .5f;
    Vector normal5 = Cross(delta1, t);
    normal5.Normalize();
    if (ep->opatch5->GetCP5()->IsFlip())
        normal5.Negate();
    ep->ndir[5] = normal5;
    const Vector normal = (normal1 + normal2 + normal3 + normal4 + normal5) / 5.F;
    ep->ndir[0] = normal;
}

bool RayAABB(Vector origin, Vector dir, Vector &coord, Vector MinB, Vector MaxB) {
    //	A method to compute a ray-AABB intersection.
    //	Original code by Andrew Woo, from "Graphics Gems", Academic Press, 1990
    //	Optimized code by Pierre Terdiman, 2000 (~20-30% faster on my Celeron 500)
    //	Epsilon value added by Klaus Hartmann. (discarding it saves a few cycles only)
    bool Inside = true;
    Vector MaxT;

    MaxT.x = MaxT.y = MaxT.z = -1.F;

    for (unsigned i = 0; i < 3; ++i) {
        if (origin[i] < MinB[i]) {
            coord[i] = MinB[i];
            Inside = FALSE;
            if (IR(dir[i]))
                MaxT[i] = (MinB[i] - origin[i]) / dir[i];
        } else {
            if (origin[i] > MaxB[i]) {
                coord[i] = MaxB[i];
                Inside = FALSE;
                if (IR(dir[i]))
                    MaxT[i] = (MaxB[i] - origin[i]) / dir[i];
            }
        }
    }

    if (Inside) {
        coord = origin;
        return true;
    }

    unsigned WhichPlane = 0;
    if (MaxT[1] > MaxT[WhichPlane])
        WhichPlane = 1;
    if (MaxT[2] > MaxT[WhichPlane])
        WhichPlane = 2;

    if (IR(MaxT[WhichPlane]) & 0x80000000)
        return false;

    for (unsigned i = 0; i < 3; ++i) {
        if (i != WhichPlane) {
            coord[i] = origin[i] + MaxT[WhichPlane] * dir[i];
#ifdef RAYAABB_EPSILON
            if (coord[i] < MinB[i] - RAYAABB_EPSILON || coord[i] > MaxB[i] + RAYAABB_EPSILON)
                return false;
#else
			if(coord[i] < MinB[i] || coord[i] > MaxB[i])	return false;
#endif
        }
    }
    return true;
}

bool EPatch::HitTest(const Vector start, const Vector direction, Vector &hitpoint, double &distanz, const bool subpatch) const {
    Vector testhit, maxhit;
    //Check BBox complete Patch
    if (!RayAABB(start, direction, hitpoint, this->bb_min[0], this->bb_max[0])) {
        distanz = 0.;
        hitpoint.Set(0.F);
        return false; //no hit
    }

    if (!subpatch) {
        distanz = elength(start, hitpoint);
        return true;
    }
    //check subdivided patches BBox
    Vector minhit = maxhit = hitpoint;
    switch (this->numpoint) {
        case 3:
            if (RayAABB(start, direction, testhit, this->bb_min[1], this->bb_max[1]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[2], this->bb_max[2]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[3], this->bb_max[3]))
                testhit.PushMinMax(minhit, maxhit);
            break;
        case 4:
            if (RayAABB(start, direction, testhit, this->bb_min[1], this->bb_max[1]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[2], this->bb_max[2]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[3], this->bb_max[3]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[4], this->bb_max[4]))
                testhit.PushMinMax(minhit, maxhit);
            break;
        case 5:
            if (RayAABB(start, direction, testhit, this->bb_min[1], this->bb_max[1]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[2], this->bb_max[2]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[3], this->bb_max[3]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[4], this->bb_max[4]))
                testhit.PushMinMax(minhit, maxhit);
            if (RayAABB(start, direction, testhit, this->bb_min[5], this->bb_max[5]))
                testhit.PushMinMax(minhit, maxhit);
            break;
        default:ASSERT(false);
            break;
    }
    hitpoint = minhit; //nearest hitpoint
    distanz = elength(start, minhit);
    return true;
}

bool EPatch::IsNeighbor(const EPatch *ep, const bool side) const {
    if (this == ep)
        return false;
    int found = 0;
    // 2 x 5 pointers
    if (this->numpoint == 5 && ep->numpoint == 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4 || this->pid1 == ep->pid5)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4 || this->pid2 == ep->pid5)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4 || this->pid3 == ep->pid5)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4 || this->pid4 == ep->pid5)
            found++;
        if (this->pid5 == ep->pid1 || this->pid5 == ep->pid2 || this->pid5 == ep->pid3 || this->pid5 == ep->pid4 || this->pid5 == ep->pid5)
            found++;
    }
    // 2 x 4 pointers
    if (this->numpoint != 5 && ep->numpoint != 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4)
            found++;
    }
    // 5 point - 4 point
    if (this->numpoint == 5 && ep->numpoint != 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4)
            found++;
        if (this->pid5 == ep->pid1 || this->pid5 == ep->pid2 || this->pid5 == ep->pid3 || this->pid5 == ep->pid4)
            found++;
    }
    // 4 point - 5 point
    if (this->numpoint != 5 && ep->numpoint == 5) {
        if (this->pid1 == ep->pid1 || this->pid1 == ep->pid2 || this->pid1 == ep->pid3 || this->pid1 == ep->pid4 || this->pid1 == ep->pid5)
            found++;
        if (this->pid2 == ep->pid1 || this->pid2 == ep->pid2 || this->pid2 == ep->pid3 || this->pid2 == ep->pid4 || this->pid2 == ep->pid5)
            found++;
        if (this->pid3 == ep->pid1 || this->pid3 == ep->pid2 || this->pid3 == ep->pid3 || this->pid3 == ep->pid4 || this->pid3 == ep->pid5)
            found++;
        if (this->pid4 == ep->pid1 || this->pid4 == ep->pid2 || this->pid4 == ep->pid3 || this->pid4 == ep->pid4 || this->pid4 == ep->pid5)
            found++;
    }
    if (side) {
        if (found > 1) {
            return true; // 1 side neighbor  // NOLINT(readability-simplify-boolean-expr)
        }
        return false;
    }
    if (found > 0) {
        return true; // 1 point neighbor
    }
    return false;
}

void EPatch::Init(HPatch *hp, const Matrix34 &screen) {
    Vector local_pos[16];

    this->opatch5 = nullptr;
    this->opatch = hp;
    const PatchID pid = hp->GetPatchID();
    this->pid1 = pid.m_id1;
    this->pid2 = pid.m_id2;
    this->pid3 = pid.m_id3;
    this->pid4 = pid.m_id4;
    this->pid5 = 0;
    hp->GetPatchPoints(local_pos); //works only for frontview
    for (int i = 0; i < 16; ++i) {
        this->pos[i] = local_pos[i] * screen;
    }

    this->cppos[1] = local_pos[0] * screen;
    this->cppos[2] = local_pos[3] * screen;
    this->cppos[3] = local_pos[6] * screen;
    this->cp1_1 = hp->GetCP1();
    this->cp2_1 = hp->GetCP2();
    this->cp3_1 = hp->GetCP3();
    switch (hp->GetNumPoints()) {
        case 3:
            this->numpoint = 3;
            if (hp->IsUseHook1() || hp->IsUseHook2() || hp->IsUseHook3()) {
                this->ishooked = true;
                this->cp1_2 = this->cp2_2 = this->cp3_2 = nullptr;
            } else {
                this->ishooked = false;
                this->cp1_2 = findsecondcp(this->cp1_1, this->cp2_1);
                this->cp2_2 = findsecondcp(this->cp2_1, this->cp3_1);
                this->cp3_2 = findsecondcp(this->cp3_1, this->cp1_1);
                if (this->cp1_1->GetNext() != this->cp1_2)
                    swapcp(&this->cp1_1, &this->cp1_2);
                if (this->cp2_1->GetNext() != this->cp2_2)
                    swapcp(&this->cp2_1, &this->cp2_2);
                if (this->cp3_1->GetNext() != this->cp3_2)
                    swapcp(&this->cp3_1, &this->cp3_2);
            }
            eGetPatchMid_3(this);
            eGetNormal_3(this);
            this->bb_min[1] = this->bb_max[1] = this->pos[0]; //bbox Subdivided Patch1
            this->sdpos[1].PushMinMax(this->bb_min[1], this->bb_max[1]);
            this->sdpos[0].PushMinMax(this->bb_min[1], this->bb_max[1]);
            this->sdpos[3].PushMinMax(this->bb_min[1], this->bb_max[1]);
            this->bb_min[2] = this->bb_max[2] = this->sdpos[1]; //bbox Subdivided Patch2
            this->pos[3].PushMinMax(this->bb_min[2], this->bb_max[2]);
            this->sdpos[2].PushMinMax(this->bb_min[2], this->bb_max[2]);
            this->sdpos[0].PushMinMax(this->bb_min[2], this->bb_max[2]);
            this->bb_min[3] = this->bb_max[3] = this->sdpos[2]; //bbox Subdivided Patch3
            this->pos[6].PushMinMax(this->bb_min[3], this->bb_max[3]);
            this->sdpos[3].PushMinMax(this->bb_min[3], this->bb_max[3]);
            this->sdpos[0].PushMinMax(this->bb_min[3], this->bb_max[3]);
            this->bb_min[0] = this->bb_max[0] = this->pos[0]; //bbox Patch
            this->pos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->pos[6].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[0].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[1].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[2].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
            break;
        case 4:
            this->cppos[4] = local_pos[9] * screen;
            this->numpoint = 4;
            this->cp4_1 = hp->GetCP4();
            if (hp->IsUseHook1() || hp->IsUseHook2() || hp->IsUseHook3() || hp->IsUseHook4()) {
                this->ishooked = true;
                this->cp1_2 = this->cp2_2 = this->cp3_2 = this->cp4_2 = nullptr;
            } else {
                this->ishooked = false;
                this->cp1_2 = findsecondcp(this->cp1_1, this->cp2_1);
                this->cp2_2 = findsecondcp(this->cp2_1, this->cp3_1);
                this->cp3_2 = findsecondcp(this->cp3_1, this->cp4_1);
                this->cp4_2 = findsecondcp(this->cp4_1, this->cp1_1);
                if (this->cp1_1->GetNext() != this->cp1_2)
                    swapcp(&this->cp1_1, &this->cp1_2);
                if (this->cp2_1->GetNext() != this->cp2_2)
                    swapcp(&this->cp2_1, &this->cp2_2);
                if (this->cp3_1->GetNext() != this->cp3_2)
                    swapcp(&this->cp3_1, &this->cp3_2);
                if (this->cp4_1->GetNext() != this->cp4_2)
                    swapcp(&this->cp4_1, &this->cp4_2);
            }
            eGetPatchMid_4(this);
            eGetNormal_4(this);
            this->bb_min[1] = this->bb_max[1] = this->pos[0]; //bbox Subdivided Patch1
            this->sdpos[1].PushMinMax(this->bb_min[1], this->bb_max[1]);
            this->sdpos[0].PushMinMax(this->bb_min[1], this->bb_max[1]);
            this->sdpos[4].PushMinMax(this->bb_min[1], this->bb_max[1]);
            this->bb_min[2] = this->bb_max[2] = this->sdpos[1]; //bbox Subdivided Patch2
            this->pos[3].PushMinMax(this->bb_min[2], this->bb_max[2]);
            this->sdpos[2].PushMinMax(this->bb_min[2], this->bb_max[2]);
            this->sdpos[0].PushMinMax(this->bb_min[2], this->bb_max[2]);
            this->bb_min[3] = this->bb_max[3] = this->sdpos[2]; //bbox Subdivided Patch3
            this->pos[6].PushMinMax(this->bb_min[3], this->bb_max[3]);
            this->sdpos[3].PushMinMax(this->bb_min[3], this->bb_max[3]);
            this->sdpos[0].PushMinMax(this->bb_min[3], this->bb_max[3]);
            this->bb_min[4] = this->bb_max[4] = this->sdpos[3]; //bbox Subdivided Patch4
            this->pos[9].PushMinMax(this->bb_min[4], this->bb_max[4]);
            this->sdpos[4].PushMinMax(this->bb_min[4], this->bb_max[4]);
            this->sdpos[0].PushMinMax(this->bb_min[4], this->bb_max[4]);
            this->bb_min[0] = this->bb_max[0] = this->pos[0]; //bbox Patch
            this->pos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->pos[6].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->pos[9].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[0].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[1].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[2].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
            this->sdpos[4].PushMinMax(this->bb_min[0], this->bb_max[0]);
            break;
        default:ASSERT(false);
            break;
    }
    this->cppos[0] = this->sdpos[0];
}

void EPatch::Init(HPatch5 *hp, const Matrix34 &screen) {
    Vector local_pos[16];

    this->opatch = nullptr;
    this->opatch5 = hp;
    this->numpoint = 5;
    const PatchID5 pid = hp->GetPatchID();
    this->pid1 = pid.m_id1;
    this->pid2 = pid.m_id2;
    this->pid3 = pid.m_id3;
    this->pid4 = pid.m_id4;
    this->pid5 = pid.m_id5;
    hp->GetPatchPoints(local_pos); //works only for frontview
    for (int i = 0; i < 16; ++i) {
        this->pos[i] = local_pos[i] * screen;
    }
    this->cppos[1] = local_pos[0] * screen;
    this->cppos[2] = local_pos[3] * screen;
    this->cppos[3] = local_pos[6] * screen;
    this->cppos[4] = local_pos[9] * screen;
    this->cppos[5] = local_pos[12] * screen;
    this->cp1_1 = hp->GetCP1();
    this->cp2_1 = hp->GetCP2();
    this->cp3_1 = hp->GetCP3();
    this->cp4_1 = hp->GetCP4();
    this->cp5_1 = hp->GetCP5();
    if (hp->IsUseHook1() || hp->IsUseHook2() || hp->IsUseHook3() || hp->IsUseHook4()) {
        this->ishooked = true;
        this->cp1_2 = this->cp2_2 = this->cp3_2 = this->cp4_2 = this->cp5_2 = nullptr;
    } else {
        this->ishooked = false;
        this->cp1_2 = findsecondcp(this->cp1_1, this->cp2_1);
        this->cp2_2 = findsecondcp(this->cp2_1, this->cp3_1);
        this->cp3_2 = findsecondcp(this->cp3_1, this->cp4_1);
        this->cp4_2 = findsecondcp(this->cp4_1, this->cp5_1);
        this->cp5_2 = findsecondcp(this->cp5_1, this->cp1_1);
        if (this->cp1_1->GetNext() != this->cp1_2)
            swapcp(&this->cp1_1, &this->cp1_2);
        if (this->cp2_1->GetNext() != this->cp2_2)
            swapcp(&this->cp2_1, &this->cp2_2);
        if (this->cp3_1->GetNext() != this->cp3_2)
            swapcp(&this->cp3_1, &this->cp3_2);
        if (this->cp4_1->GetNext() != this->cp4_2)
            swapcp(&this->cp4_1, &this->cp4_2);
        if (this->cp5_1->GetNext() != this->cp5_2)
            swapcp(&this->cp5_1, &this->cp5_2);
    }
    eGetPatchMid_5(this);
    eGetNormal_5(this);
    this->bb_min[1] = this->bb_max[1] = this->pos[0]; //bbox Subdivided Patch1
    this->sdpos[1].PushMinMax(this->bb_min[1], this->bb_max[1]);
    this->sdpos[0].PushMinMax(this->bb_min[1], this->bb_max[1]);
    this->sdpos[5].PushMinMax(this->bb_min[1], this->bb_max[1]);
    this->bb_min[2] = this->bb_max[2] = this->sdpos[1]; //bbox Subdivided Patch2
    this->pos[3].PushMinMax(this->bb_min[2], this->bb_max[2]);
    this->sdpos[2].PushMinMax(this->bb_min[2], this->bb_max[2]);
    this->sdpos[0].PushMinMax(this->bb_min[2], this->bb_max[2]);
    this->bb_min[3] = this->bb_max[3] = this->sdpos[2]; //bbox Subdivided Patch3
    this->pos[6].PushMinMax(this->bb_min[3], this->bb_max[3]);
    this->sdpos[3].PushMinMax(this->bb_min[3], this->bb_max[3]);
    this->sdpos[0].PushMinMax(this->bb_min[3], this->bb_max[3]);
    this->bb_min[4] = this->bb_max[4] = this->sdpos[3]; //bbox Subdivided Patch4
    this->pos[9].PushMinMax(this->bb_min[4], this->bb_max[4]);
    this->sdpos[4].PushMinMax(this->bb_min[4], this->bb_max[4]);
    this->sdpos[0].PushMinMax(this->bb_min[4], this->bb_max[4]);
    this->bb_min[5] = this->bb_max[5] = this->sdpos[4]; //bbox Subdivided Patch5
    this->pos[12].PushMinMax(this->bb_min[5], this->bb_max[5]);
    this->sdpos[5].PushMinMax(this->bb_min[5], this->bb_max[5]);
    this->sdpos[0].PushMinMax(this->bb_min[5], this->bb_max[5]);
    this->bb_min[0] = this->bb_max[0] = this->pos[0]; //bbox Patch
    this->pos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->pos[6].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->pos[9].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->pos[12].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[0].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[1].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[2].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[3].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[4].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->sdpos[5].PushMinMax(this->bb_min[0], this->bb_max[0]);
    this->cppos[0] = this->sdpos[0];
}

EPatch::EPatch(HPatch *hp, const Matrix34 &screen) {
    Init(hp, screen);
}

EPatch::EPatch(HPatch5 *hp, const Matrix34 &screen) {
    Init(hp, screen);
}
