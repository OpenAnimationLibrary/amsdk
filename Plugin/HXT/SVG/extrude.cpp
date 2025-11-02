#include "StdAfx.h"
#include "Vector.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Vector2.h"
#include "geom.h"
#include "poly.h"
#include "extrude.h"
#include "quad.h"

static void Fix4ptSplines(Subdiv *subdiv, const PolygonalAreaArray *areas);

// Extrude some number of cross sections of the polygons in pa, according to flags.
// Possibly close the fronts and backs, using quadrify, if specified.
// Assume the polygons are in the xy plane, and use 'depth' as the distance between
// the front and the back (if a mid cross section is needed, put it at depth/2).
// Let bevels stick out in front of and behide "depth".
// Use 'inset' for any bevels.
// The original pa will used in the extrusion, perhaps modified somewhat.
void Extrude(Subdiv *subdiv, PolygonalAreaArray *pa, unsigned flags, const float depth, const float inset) {
    ASSERT(pa != nullptr);
    // need positive depth if mid or side
    if (depth == 0.F)
        flags &= ~(EX_MID | EX_BACK);
    // can't bevel or close back if no back
    if ((flags & EX_BACK) == 0)
        flags &= ~(EX_BEV_BACK | EX_CLOSE_BACK);
    // no sides if no mid or back
    if ((flags & EX_MID) == 0 && (flags & EX_BACK) == 0)
        flags &= ~EX_BEV_SIDE;
    // need positive inset amount if any bevels
    if (inset <= 0.F)
        flags &= ~(EX_BEV_FRONT | EX_BEV_SIDE | EX_BEV_BACK);

    const BOOL anybev = (flags & (EX_BEV_FRONT | EX_BEV_SIDE | EX_BEV_BACK)) != 0;

    const BOOL round = (flags & EX_ROUND) != 0;

    const BOOL inward = (flags & EX_INWARD) != 0 || !anybev;

//    BOOL anyclose = (flags & (EX_CLOSE_FRONT | EX_CLOSE_BACK)) != 0;

    const BOOL subdivide = flags & EX_SUB;
    const BOOL subdivall = flags & EX_SUB_ALL;

    // Cross sections needed will be some subset of:
    //
    // If beveling is inward:
    //
    // frontbev: inset copy of pa (if top is beveled)
    // front:    original pa, with corners cut if sids beveled (always)
    // mid:      copy of pa, with corners cut if sides beveled (if mid)
    // back:     copy of pa, with corners cut if sides beveled (if back)
    // backbev:  inset copy of pa (if back is beveled)
    //
    // If beveling is outward (and any beveling at all)
    //
    // frontbev: copy of pa (if top is beveled)
    // front:    outset original pa, with corners cut if sides beveled (always)
    // mid:      outset copy of pa, with corners cut if sides beveled (if mid)
    // back:     outset copy of pa, with corners cut (if back)
    // backbev:  copy of pa (if back is beveled)
    //

    PolygonalAreaArray *frontbev = nullptr;
    PolygonalAreaArray *front = pa;
    PolygonalAreaArray *mid = nullptr;
    PolygonalAreaArray *back = nullptr;
    PolygonalAreaArray *backbev = nullptr;

    Vector offset(0.F, 0.F, 0.F);

    if (subdivide)
        pa->Subdivide(subdivall);

    // make copies of pa for front/back bevels before possibly modifying pa
    if (flags & EX_BEV_FRONT) {
        offset.z = inset;
        frontbev = pa->Copy(offset);
        if (inward)
            frontbev->Inset(inset, TRUE);
    }
    if (flags & EX_BEV_BACK) {
        if (frontbev) {
            offset.z = -(inset + depth + inset);
            backbev = frontbev->Copy(offset);
        } else {
            offset.z = -(depth + inset);
            backbev = pa->Copy(offset);
            if (inward)
                backbev->Inset(inset, TRUE);
        }
    }
    if (!inward)
        front->Inset(inset, FALSE);
    if (flags & EX_BEV_SIDE)
        front->CutCorners(inset, round);
    if (flags & EX_MID) {
        offset.z = -0.5F * depth;
        mid = front->Copy(offset);
    }
    if (flags & EX_BACK) {
        offset.z = -depth;
        back = front->Copy(offset);
    }
    subdiv->SortPoints();

    PolygonalAreaArray *csecs[5];
    int n = 0;
    if (frontbev)
        csecs[n++] = frontbev;
    csecs[n++] = front;
    if (mid)
        csecs[n++] = mid;
    if (back)
        csecs[n++] = back;
    if (backbev)
        csecs[n++] = backbev;
    int firstcut = -1;
    int lastcut = -1;
    if (flags & EX_BEV_SIDE) {
        firstcut = frontbev ? 1 : 0;
        lastcut = backbev ? n - 2 : n - 1;
    }
    if (flags & EX_CLOSE_FRONT)
        QuadrifyAreas(subdiv, frontbev ? frontbev : front);
    if (flags & EX_CLOSE_BACK)
        QuadrifyAreas(subdiv, backbev ? backbev : back);

    Skin(subdiv, csecs, n, round, firstcut, lastcut);

    // Hack to deal with simple 4pt polygons (for Animation Master).
    // Do this after Skin, because Skin assumes all the cross section
    // polygons can be iterated through via SplineIters.
    if (flags & EX_CLOSE_FRONT)
        Fix4ptSplines(subdiv, frontbev ? frontbev : front);
    if (flags & EX_CLOSE_BACK)
        Fix4ptSplines(subdiv, backbev ? backbev : back);

    delete frontbev;
    delete mid;
    delete back;
    delete backbev;
}

// Hack to deal with problem that a simple 4-pt polygonal (with no islands)
// will be left alone by QuadrifyArea, yet won't render as a Hash patch.
// This routine splits such polygons into two splines, so that they will
// be converted into separate Hash splines, and thus give a rendered patch.
static void Fix4ptSplines(Subdiv *subdiv, const PolygonalAreaArray *areas) {
    for (int i = 0; i < areas->Num(); ++i) {
        const PolygonalArea *pa = areas->Get(i);
        if (pa->islands != nullptr && pa->islands->Num() > 0)
            continue;
        int nedges = 0;
        // ReSharper disable once CppTooWideScope
        SplineIter sit(pa->boundary);
        for (; sit.Cur() != nullptr; sit.GetNext())
            nedges++;
        if (nedges != 4)
            continue;
        // boundary is 4 pt spline, and there are no islands.
        // Split it into two splines.
        subdiv->SplitSpline(pa->boundary->Spline(), 2);
    }
}
