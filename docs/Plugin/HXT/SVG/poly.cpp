// ReSharper disable CppTooWideScope
#include "StdAfx.h"
#include "Vector.h"
#include "Vector2.h"
#include "geom.h"
#include "poly.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

static void DivideCrossingEdges(Subdiv *s, const EdgeArray *polys);
static void SkinPolys(Subdiv *subdiv, const EdgeArray *polys, BOOL round, int firstcut, int lastcut, int pass);

// Assume s contains a number of disjoint polygons, each of which
// is either outside all the other polygons or fully contained within
// one of the others (so that a containment tree is formed).
// (We will try to deal with the case of overlapping polygons by
// using the area of the polygon to break the tie: the bigger one
// will be assumed to contain the smaller one.)
// Partition the polygons into a number of "Polygonal Areas", where each
// area consists of a boundary polygon (oriented CCW) and a number
// island polygons (each oriented CW) directly contained within the boundary.
// "Directly contains" means without some intervening polygon, so that if
// we have A contains B contains C contains D, the answer will be two areas:
// (A as boundary, B as island) and (C as boundary, D as island).
// For convenience, we return the LeftFaceLowestOrg representative edge
// of each polygon.
// A side effect of this routine is that the points of s will be sorted
// (see Subdiv::SortPoints).
PolygonalAreaArray *FindPolygonalAreas(Subdiv *s) {
    gtrace("FindPolygonalAreas\n");
    int numareas = 0;
    s->SortPoints();
    const EdgeArray *polys = FindPolys(s);
    const int numpolys = polys->Num();
    if (numpolys == 0) {
        delete polys;
        return new PolygonalAreaArray(0);
    }
    // Set contains[i][j] to number of vertices of polygon j that polygon i contains
    int **contains = new int *[numpolys];
    int *polysize = new int[numpolys];
    auto *area = new double[numpolys];
    int i, j, k;
    for (i = 0; i < numpolys; ++i) {
        Edge *polyi = polys->Get(i);
        contains[i] = new int[numpolys];
        area[i] = s->LeftFaceArea(polyi);
        // Orient polygon representative so that left face is inside
        if (area[i] < 0.0) {
            polyi = polyi->Sym();
            polys->Set(i, polyi);
            area[i] = -area[i];
        }
        polysize[i] = Subdiv::LeftFaceSize(polyi);
    }
    for (i = 0; i < numpolys; ++i) {
        Edge *polyi = polys->Get(i);
        for (j = 0; j < numpolys; ++j) {
            contains[i][j] = 0;
            if (j == i)
                continue;
            LeftFaceIter jit(polys->Get(j));
            for (; jit.Cur() != nullptr; jit.GetNext()) {
                const Edge *ej = jit.Cur();
                if (s->InsideLeftFace(polyi, s->Coords2(ej->Org()))) {
                    // gtrace("polygon %d contains polygon %d (at point %d)\n", i, j, ej->Org());
                    contains[i][j]++;
                }
            }
        }
    }
    // Now set contains[i][j] to 1 if poly i contains at least 55% of poly j's vertices
    // (This low percentage is partly because we are dealing with polygonal approximations
    // to curves, sometimes, and the containment relation may seem worse than it actually is.)
    for (i = 0; i < numpolys; ++i) {
        for (j = 0; j < numpolys; ++j) {
            const int cij = contains[i][j];
            if (cij) {
                const int sizej = polysize[j];
                const double j_in_i_frac = (double)cij / (double)sizej;
                if (j_in_i_frac >= .55) {
                    gtrace("polygon %d contains polygon %d\n", i, j);
                    contains[i][j] = 1;
                } else {
                    // gtrace("polygon %d doesn't contain polygon %d, cij=%d, sizej=%d\n", i, j, cij, sizej);
                    contains[i][j] = 0;
                }
                if (i > j && contains[i][j] && contains[j][i]) {
                    // still have a tie: use area to break
                    if (area[i] > area[j]) {
                        gtrace("break tie by revoking contains[%d][%d]\n", j, i);
                        contains[j][i] = 0;
                    } else {
                        gtrace("break tie by revoking contains[%d][%d]\n", i, j);
                        contains[i][j] = 0;
                    }
                }
            }
        }
    }

    // Loop, looking for polygons not yet assigned to any area
    // (areaindex is -1) and contained in no other unassigned polygon.
    // Make that the boundary of a new area, then find the islands for
    // that area.

    // Overestimate needed size of answer array (for allocation)
    auto *ans = new PolygonalAreaArray(0, numpolys);
    const EdgeArray icontains(numpolys); // used inside loop, but construct only once, here
    int *areaindex = new int[numpolys];
    for (i = 0; i < numpolys; ++i)
        areaindex[i] = -1;
    int numassigned = 0;
    while (numassigned < numpolys) {
        for (i = 0; i < numpolys; ++i) {
            if (areaindex[i] != -1)
                continue;
            BOOL i_is_boundary = TRUE;
            for (j = 0; j < numpolys; ++j) {
                if (j != i && areaindex[j] == -1 && contains[j][i]) {
                    i_is_boundary = FALSE;
                }
            }
            if (i_is_boundary) {
                auto *pa = new PolygonalArea();
                ans->Set(numareas, pa);
                pa->boundary = LeftFaceLowestOrg(polys->Get(i));
                pa->subdiv = s;
                areaindex[i] = numareas;
                numassigned++;
                for (j = 0; j < numpolys; ++j) {
                    if (i != j && areaindex[j] == -1 && contains[i][j])
                        icontains.Set(j, polys->Get(j));
                    else
                        icontains.Set(j, nullptr);
                }
                // Now icontains[j] is set if polygon j is to be regarded
                // as inside polygon i.
                // Remove those elements of icontains that are inside
                // other elements of icontains, leaving only those edges that
                // are directly inside.
                int numislands = 0;
                for (j = 0; j < numpolys; ++j) {
                    if (!icontains.Get(j))
                        continue;
                    for (k = 0; k < numpolys; ++k) {
                        if (k == j || !icontains.Get(k))
                            continue;
                        if (contains[k][j]) {
                            icontains.Set(j, nullptr);
                        }
                    }
                    if (icontains.Get(j) != nullptr)
                        numislands++;
                }
                if (numislands > 0) {
                    pa->islands = new EdgeArray(numislands);
                    k = 0;
                    for (j = 0; j < numpolys; ++j) {
                        Edge *e = icontains.Get(j);
                        if (e != nullptr) {
                            ASSERT(k < numislands);
                            // Set island edges to opposite orientation (CW now)
                            pa->islands->Set(k, LeftFaceLowestOrg(e->Sym()));
                            k++;
                            areaindex[j] = numareas;
                            numassigned++;
                        }
                    }
                    ASSERT(k == numislands);
                }
                numareas++;
            }
        }
    }
    delete [] area;
    delete [] areaindex;
    delete [] polysize;
    delete polys;
    for (i = 0; i < numpolys; ++i)
        delete contains[i];
    delete [] contains;
    for (i = 0; i < numareas; ++i) {
        gtrace("Polygonal Area %d: \n", i);
        const PolygonalArea *pa = ans->Get(i);
        ASSERT(pa != nullptr && pa->boundary != nullptr);
        gtrace("  Boundary: (%d,%d)\n", pa->boundary->Org(), pa->boundary->Dst());
        if (pa->islands) {
            for (j = 0; j < pa->islands->Num(); ++j)
                gtrace("      Island %d: (%d,%d)\n", j, pa->islands->Get(j)->Org(), pa->islands->Get(j)->Dst());
        }
    }
    return ans;
}

// Partition edges of s into "polygons" by
// starting from an unassigned edge and walking around its
// left face until hit the same edge.
// Use the Val() field of edge to hold polygon number (starting from 0).
// Return an allocated EdgeArray (size == number of polygons)
// with a pointer to a representative edge from each polygon.
// The representative will be the Edge with the lowest-index origin.
// Another thing this routine does is set the QE_BOUNDARY flag for the
// quadedges in the boundary.
// Also, looks for nonadjacent edges that cross each other and subdivides
// them if that helps the crossing go away.
EdgeArray *FindPolys(Subdiv *s) {
    gtrace("FindPolys\n");
    s->SetAllEdgeVals(-1);

    int numpolys = 0;
    SubdivEdgeIter sit(s);
    Edge *e;
    for (; sit.Cur() != nullptr; sit.GetNext()) {
        e = sit.Cur();
        if (e->Val() == -1) {
            LeftFaceIter fit(e);
            for (; fit.Cur() != nullptr; fit.GetNext()) {
                Edge *fe = fit.Cur();
                if (fe->Val() == -1) {
                    fe->SetVal(numpolys);
                    fe->Sym()->SetVal(numpolys);
                    fe->QEdge()->SetFlag(QE_BOUNDARY);
                }
            }
            numpolys++;
        }
    }
    if (numpolys > 0) {
        auto *ans = new EdgeArray(numpolys);
        int i;
        for (i = 0; i < numpolys; ++i)
            ans->Set(i, nullptr);
        SubdivEdgeIter it(s);
        for (; it.Cur() != nullptr; it.GetNext()) {
            e = it.Cur();
            const int k = e->Val();
            ASSERT(k >= 0 && k < numpolys);
            const Edge *f = ans->Get(k);
            if (f == nullptr || e->Org() < f->Org())
                ans->Set(k, e);
        }
        DivideCrossingEdges(s, ans);
        for (i = 0; i < numpolys; ++i) {
            ASSERT(ans->Get(i) != nullptr);
            gtrace("Polygon %d: (%d,%d)\n", i, ans->Get(i)->Org(), ans->Get(i)->Dst());
        }
        return ans;
    }
    return new EdgeArray(0);
}

// Assumes points are sorted
static void DivideCrossing(Subdiv *s, Edge *polye) {
    LeftFaceIter it(polye);
    for (; it.Cur() != nullptr; it.GetNext()) {
        Edge *e = it.Cur();
        const int eorg = e->Org();
        const int edst = e->Dst();
        Bezier2 ebez;
        ebez.cp[0] = s->Coords2(eorg);
        ebez.cp[3] = s->Coords2(edst);
        const BOOL eline = e->BezCP(0) == nullptr;
        s->FillEdgeBezier2(e, &ebez);
        LeftFaceIter it2(polye);
        for (; it2.Cur() != nullptr; it2.GetNext()) {
            Edge *f = it2.Cur();
            if (f == e || f->Org() == edst || f->Dst() == eorg)
                continue;
            // f and e are in same face, not adjacent
            const int forg = f->Org();
            const int fdst = f->Dst();
            if (s->SegsIntersect(eorg, edst, forg, fdst)) {
                Bezier2 fbez;
                const BOOL fline = f->BezCP(0) == nullptr;
                s->FillEdgeBezier2(f, &fbez);
                unsigned long esig, fsig;
                BOOL subdiv_e = FALSE;
                BOOL subdiv_f = FALSE;
                if (!eline && !fline) {
                    if (!ebez.Intersects(&fbez, esig, fsig)) {
                        subdiv_e = TRUE;
                        subdiv_f = TRUE;
                    }
                } else if (!eline && fline) {
                    if (!ebez.Intersects(&fbez.cp[0], &fbez.cp[3], esig))
                        subdiv_e = TRUE;
                } else if (eline && !fline) {
                    if (!fbez.Intersects(&ebez.cp[0], &ebez.cp[3], fsig))
                        subdiv_f = TRUE;
                }
                if (subdiv_e)
                    s->BisectRecursive(e, esig);
                if (subdiv_f)
                    s->BisectRecursive(f, fsig);
                if (subdiv_e || subdiv_f) {
                    s->SortPoints();
                    DivideCrossing(s, polye);
                    return;
                }
            }
        }
    }
}

// Assumes points are sorted; leaves with that true too.
static void DivideCrossingEdges(Subdiv *s, const EdgeArray *polys) {
    for (int i = 0; i < polys->Num(); ++i) {
        Edge *polye = polys->Get(i);
        DivideCrossing(s, polye);
    }
}

// Return Edge in left face of e with lowest origin index
// (i.e., assuming points are sorted, the edge with the leftmost origin,
// with ties broken by going for bottommost origin).
Edge *LeftFaceLowestOrg(Edge *e) {
    int minorg = e->Org();
    Edge *minedge = e;
    LeftFaceIter it(e);
    for (; it.Cur() != nullptr; it.GetNext()) {
        Edge *f = it.Cur();
        if (f->Org() < minorg) {
            minorg = f->Org();
            minedge = f;
        }
    }
    return minedge;
}

// Assume Edge e is an edge that represents a polygon (got by traversing using SplineIter).
// Return the corresponding edge of a copy of the polygon, with each vertex offset
// by the given amount.
// Copy flags of corresponding edges, too.
static Edge *CopyPoly(Subdiv *s, Edge *e, const Vector &offset) {
    ASSERT(s != nullptr && e != nullptr);
    Vector vo = s->Coords(e->Org());
    Vector vd = s->Coords(e->Dst());
    vo += offset;
    vd += offset;
    const int sp = s->NewSpline();
    Edge *ans = s->MakeEdge(vo, vd, sp);
    const Edge *eprev = e->Sprev();
    Edge *prev = ans;
    SplineIter pit(e);
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        const Edge *f = pit.Cur();
        Edge *fcopy;
        if (f == e)
            fcopy = ans;
        else if (f == eprev) {
            // loopback
            fcopy = s->Connect(prev, ans, sp);
        } else {
            vd = s->Coords(f->Dst());
            vd += offset;
            fcopy = s->Connect(prev, vd, sp);
        }
        if (f->IsCubic()) {
            Vector v = *f->BezCP(0);
            v += offset;
            fcopy->SetBezCP(0, v);
            v = *f->BezCP(1);
            v += offset;
            fcopy->SetBezCP(1, v);
        }
        fcopy->QEdge()->SetFlag(f->QEdge()->Flags());
        prev = fcopy;
    }
    return ans;
}

// Return normalized vector that bisects an angle formed by din going
// into a point and dout leaving it.
//(Bisector will be in "left face" of the so-formed angle.)
// Assume they are all in same xy plane.
static Vector Bisector(const Vector &din, const Vector &dout) {
    const Vector uin = din.Normalized();
    const Vector uout = dout.Normalized();
    Vector uavg = uin + uout;
    uavg.Normalize();
    return Rot90CCW(uavg);
}

// Return p inset (moved left or right in xy plane, as inward is TRUE or FALSE)
// along bisector of directions din and dout.
static Vector InsetV(const Vector &p, const Vector &din, const Vector &dout, float inset, const BOOL inward) {
    const Vector uout = dout.Normalized();
    Vector perp = Bisector(din, uout);
    const double costheta = Dot(perp, uout);
    if (hash_math::abs(costheta) > 1e-4) // not smooth; move by inset/sintheta
        inset = inset / (float)hash_math::sqrt(1.0 - costheta * costheta);
    if (!inward)
        perp = -perp;
    return p + inset * perp;
}

// To inset each point, we need the coords of the
// point and the tangent vectors in and out of the point.
// However, this tends to inset too much if the angle between
// the tangent vectors is much smaller than the angle between
// the edges-if-this-were-a-polygon, and the inset amount is
// comparable to the length of the polygon edges.
// (E.g., the cusp at center right in a "B").
// So we sometimes use the polygon angle.
// This function says, for a given vector difference between
// the endpoints of an edge, whether to use the tangents (returns
// TRUE) or to use the polygon edge (returns FALSE).
static BOOL InsetUseTangents(const Vector &diff, const float inset) {
    const float difflen = diff.Norm();
    return difflen == 0.F || inset / difflen <= 0.4F;
}

// Helper class to remember vector values for an edge
class EdgeVectors {
public:
    Vector orgcoords;
    Vector dstcoords;
    Vector starttangent;
    Vector endtangent;

    EdgeVectors() = default;

    EdgeVectors(const Subdiv *s, const Edge *e) {
        Set(s, e);
    }

    EdgeVectors(const EdgeVectors &other);
    ~EdgeVectors() = default;

    void Set(const Subdiv *s, const Edge *e);

    EdgeVectors &operator=(const EdgeVectors &other);
    EdgeVectors(EdgeVectors &&) = delete;
    EdgeVectors &operator=(EdgeVectors &&) = delete;
};

void EdgeVectors::Set(const Subdiv *s, const Edge *e) {
    ASSERT(s != nullptr);
    if (e == nullptr)
        return;
    orgcoords = s->Coords(e->Org());
    dstcoords = s->Coords(e->Dst());
    starttangent = s->StartTangent(e);
    endtangent = s->EndTangent(e);
}

EdgeVectors::EdgeVectors(const EdgeVectors &other) {
    orgcoords = other.orgcoords;
    dstcoords = other.dstcoords;
    starttangent = other.starttangent;
    endtangent = other.endtangent;
}

EdgeVectors &EdgeVectors::operator=(const EdgeVectors &other) = default;

// Inset (in place) the edges into left face (assumed to be in xy plane) by "inset" amount.
// If inward, inset is into left face, else it is in the opposite direction.
static void PolyInset(Subdiv *s, Edge *e, float inset, BOOL inward) {
    ASSERT(s != nullptr && e != nullptr);
    Edge *eprev = e->Sprev();
    [[maybe_unused]] Edge *enext = e->Snext();

    EdgeVectors eprevv(s, eprev);
    EdgeVectors ev(s, e);

    // Start f vectors as previous versions of e vectors.
    // Want these to always hold the values BEFORE insetting.
    EdgeVectors fprevv(s, eprev == nullptr ? nullptr : eprev->Sprev());
    EdgeVectors fv(eprevv);
    EdgeVectors fnextv(ev);

    Vector din;
    Vector dout;

    SplineIter pit(e);
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        Edge *f = pit.Cur();
        Edge *fprev = f->Sprev();
        Edge *fnext = f->Snext();

        fprevv = fv;
        fv = fnextv;
        if (fnext == eprev)
            fnextv = eprevv;
        else if (fnext == e)
            fnextv = ev;
        else
            fnextv.Set(s, fnext);

        Vector org = fv.orgcoords;
        Vector dst = fv.dstcoords;
        Vector diff = dst - org;
        float difflen = diff.Norm();
        BOOL usetangents = InsetUseTangents(diff, inset);
        // TODO: problem with "usetangents" test is that it should
        // really be done independently for both ends of the edge,
        // and made to agree with the decision on the adjacent edge.
        // Right now, only dst will pay attention to usetangents
        // unless this is the first iteration of the loop (when f==e)

        Vector neworg;
        if (f == e) {
            if (usetangents) {
                dout = fv.starttangent;
                din = fprev == nullptr ? dout : fprevv.endtangent;
            } else {
                dout = diff;
                din = fprev == nullptr ? dout : org - fprevv.orgcoords;
            }
            neworg = InsetV(org, din, dout, inset, inward);
        } else
            neworg = s->Coords(f->Org()); // was changed in previous loop iter

        if (usetangents) {
            din = fv.endtangent;
            dout = fnext == nullptr ? din : fnextv.starttangent;
        } else {
            din = diff;
            dout = fnext == nullptr ? din : fnextv.dstcoords - dst;
        }
        Vector newdst = InsetV(dst, din, dout, inset, inward);

        if (f == e)
            s->ChangeCoords(f->Org(), neworg);
        if (fnext != e)
            s->ChangeCoords(f->Dst(), newdst);

        if (f->IsCubic()) {
            Vector newdiff = newdst - neworg;
            if (difflen > 1e-4) {
                float scale = newdiff.Norm() / difflen;
                Vector cp0 = *f->BezCP(0);
                Vector cp1 = *f->BezCP(1);
                din = cp0 - org;
                Vector newcp0 = neworg + scale * din;
                f->SetBezCP(0, newcp0);
                din = cp1 - dst;
                Vector newcp1 = newdst + scale * din;
                f->SetBezCP(1, newcp1);
            }
        }
    }
}

// Split edges into two, in place.  If not "all", split only "curvy" edges, else split all.
static void PolySubdivide(Subdiv *s, Edge *e, const BOOL all) {
    SplineIter pit(e);
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        Edge *f = pit.Cur();
        BOOL dosplit = all;
        if (!all) {
            if (f->IsCubic()) {
                // split if ratio of control polygon length to direct length is "large"
                Bezier bez;
                s->FillEdgeBezier(f, &bez);
                const float len1 = (bez.cp[3] - bez.cp[0]).Norm();
                const float len2 = (bez.cp[1] - bez.cp[0]).Norm() + (bez.cp[2] - bez.cp[1]).Norm() + (bez.cp[3] - bez.cp[2]).Norm();
                const float ratio = len2 / len1;
                if (ratio > 1.05F) // TODO: experiment to find good value
                    dosplit = TRUE;
            }
        }
        if (dosplit) {
            s->Subdivide(0.5F, f);
            pit.GetNext(); // skip over second half
        }
    }
}

// Estimate arc length of Bezier edge by formula:
// .5(L0+L1) where L0 = |P0 P3| and L1 = |P0 P1| + |P1 P2| + |P2 P3|
static float BezArcLen(const Subdiv *s, const Edge *e) {
    const Vector p0 = s->Coords(e->Org());
    const Vector p3 = s->Coords(e->Dst());
    const float len0 = (p3 - p0).Norm();
    if (e->IsCubic()) {
        Bezier bez;
        s->FillEdgeBezier(e, &bez);
        const float len1 = (bez.cp[1] - p0).Norm();
        const float len2 = (bez.cp[2] - bez.cp[1]).Norm();
        const float len3 = (p3 - bez.cp[2]).Norm();
        return (len0 + len1 + len2 + len3) / 2.F;
    }
    return len0;
}

// Cut the corners of the polygon by, replacing each non-smooth vertex
// by two that are "inset" away from the replaced vertex.
// If "round" is TRUE, the new vertices are joined by a circular arc,
// else they are joined by a straight line.
// We set the QE_CUT_CORNER flag on the edges the represent the cut-off corners.
// (This will help line up corresponding vertices in original of copy.)
//
// Approximating a circular arc via Bezier cubics:
// Suppose we want the arc of a unit radius circle, center at the origin,
// with the arc straddling the positive x-axis, going angle "a" below
// to "a" above, that is, from P0=(cos a, -sin a) to P3=(cos a, sin a).
// Then place the inside control points in the directions of the tangents,
// with a scale factor "beta".
// According to calculations on Ian C G Bell's website, the "beta" that
// gives the best approximation is
//        beta = (4/3) * (1 - cos a)/ sin a
// In our case, we don't have a unit circle, but we have the vectors in
// the directions of the tangents, of a length that gives their meeting point, Q.
// So we can derive a fraction kappa of the P0--Q vector that corresponds to the
// above b, scaled by the radius of the desired circle.  That answer is:
//        kappa = (4/3) * (cos a) * (1 - cos a) / (sin a)^2
// We don't have angle a, but rather angle b = 90-a, between either din or dout
// and the bisector of din and dout.
// So
//        kappa = (4/3) * (sin b) * (1 - sin b) / (cos b)^2
// Note that when a = 45 degrees, so that we have a quarter-circle arc,
//        kappa = (4/3) * (sqrt(2) - 1)
// which is the value used in Skin(), below.
static void PolyCutCorners(Subdiv *s, Edge *e, const float inset, const BOOL round) {
    SplineIter pit(e);
    Vector cp0;
    Vector cp1;
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        Edge *f = pit.Cur();
        Edge *fprev = f->Sprev();
        if (fprev == nullptr)
            continue;
        [[maybe_unused]] Vector prevpt = s->Coords(fprev->Org());
        Vector pt = s->Coords(f->Org());
        [[maybe_unused]] Vector nextpt = s->Coords(f->Dst());
        Vector din = s->EndTangent(fprev);
        Vector dout = s->StartTangent(f);
        din.Normalize();
        dout.Normalize();
        const double cosphi = Dot(din, dout);
        if (1.0 - hash_math::abs(cosphi) < 0.1)
            continue;

        // Use ratio of inset to estimate of arc length to get subdividing fraction
        // (Not clear what is best for calculating alpha, the splitting
        // parameter, because we don't have an arc-length parameterization.)

        const float prevlen = BezArcLen(s, fprev);
        const float len = BezArcLen(s, f);
        if (prevlen < 1.1F * inset || len < 1.1F * inset)
            continue; // spacing too narrow
        const float alpha1 = 1.F - inset / prevlen;
        const float alpha2 = inset / len;
        Edge *newfprevend = s->Subdivide(alpha1, fprev);
        s->Subdivide(alpha2, f);
        // Now have newfprevend and f as inset-length segments on either side of old corner.
        // We delete newfprevend (so pit() won't get invalid, as it would if we deleted f!)
        // and splice f to fprev's end.
        const int orgi = newfprevend->Org();
        Vector org = s->Coords(orgi);
        Vector dst = s->Coords(f->Dst());
        if (round) {
            const Vector bis = Bisector(din, dout);
            const double cosb = Dot(din, bis);
            double cossquaredb = cosb * cosb;
            // If cosb == 1, all the CPs will be on top of each other,
            // so fudge a bit so that doesn't quite happen.
            if (cossquaredb >= 1.0 - 1e-7)
                cossquaredb = 1.0 - 1e-7;
            const double sinb = hash_math::sqrt(1.0 - cossquaredb);
            const auto kappa = (float)(4.0 * sinb * (1.0 - sinb) / (3.0 * cossquaredb));
            cp0 = LinInterp(kappa, org, pt);
            cp1 = LinInterp(kappa, dst, pt);
        } else {
            cp0 = LinInterp(1.F / 3.0F, org, dst);
            cp1 = LinInterp(2.F / 3.0F, org, dst);
        }
        s->DeleteEdge(newfprevend);
        Edge::Splice(f, fprev->Lnext());
        f->SetOrg(orgi);
        f->SetBezCP(0, cp0);
        f->SetBezCP(1, cp1);
        f->QEdge()->SetFlag(QE_CUT_CORNER);
        pit.GetNext(); // don't want to work on pt again
    }
}

// Make new PolygonalArea with copies of all polys in the PolygonalArea
PolygonalArea *PolygonalArea::Copy(const Vector &offset) const {
    auto *ans = new PolygonalArea;
    ans->subdiv = subdiv;
    ans->boundary = CopyPoly(subdiv, boundary, offset);
    if (islands && islands->Num() > 0) {
        ans->islands = new EdgeArray(islands->Num());
        for (int i = 0; i < islands->Num(); ++i)
            ans->islands->Set(i, CopyPoly(subdiv, islands->Get(i), offset));
    }
    return ans;
}

// Apply Inset to all polys in the PolygonalArea
void PolygonalArea::Inset(const float inset, const BOOL inward) const {
    PolyInset(subdiv, boundary, inset, inward);
    if (islands && islands->Num() > 0) {
        for (int i = 0; i < islands->Num(); ++i)
            PolyInset(subdiv, islands->Get(i), inset, inward);
    }
}

// Apply CutCorners to all polys in the PolygonalArea
void PolygonalArea::CutCorners(const float inset, const BOOL round) const {
    PolyCutCorners(subdiv, boundary, inset, round);
    if (islands && islands->Num() > 0) {
        for (int i = 0; i < islands->Num(); ++i)
            PolyCutCorners(subdiv, islands->Get(i), inset, round);
    }
}

// Subdivide each edge in half.  If not "all", subdivide only "curvy" edges.
void PolygonalArea::Subdivide(const BOOL all) const {
    PolySubdivide(subdiv, boundary, all);
    if (islands && islands->Num() > 0) {
        for (int i = 0; i < islands->Num(); ++i)
            PolySubdivide(subdiv, islands->Get(i), all);
    }
}

// Return the inset amount at which the first "Edge event" happens:
// That is, look for where an inset edge disappears because the
// two vertex bisectors forming its endpoints meet.
// The inset amount is the distance to the edge when that happens.
// If inward is TRUE, the edges move into the left face, else
// the move in the other direction.
static float PolyFirstEdgeEvent(const Subdiv *subdiv, Edge *e, const BOOL inward) {
    float ans = 1000000.0F;
    SplineIter pit(e);
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        Edge *f = pit.Cur();
        const Edge *fnext = f->Snext();
        const Edge *fprev = f->Sprev();
        if (fprev == nullptr || fnext == nullptr)
            continue;
        const Vector p = subdiv->Coords(f->Org());
        const Vector pdir = Bisector(subdiv->EndTangent(fprev), subdiv->StartTangent(f));
        const Vector q = subdiv->Coords(fnext->Org());
        const Vector qdir = Bisector(subdiv->EndTangent(f), subdiv->StartTangent(fnext));
        // Find intersection point of ray from p in direction pdir and q in direction qdir
        // (in xy plane).
        // Do by method of conversion to homogeneous coords in 3d.
        const Vector pline = Cross(Vector(p.x, p.y, 1.F), Vector(p.x + pdir.x, p.y + pdir.y, 1.F));
        const Vector qline = Cross(Vector(q.x, q.y, 1.F), Vector(q.x + qdir.x, q.y + qdir.y, 1.F));
        const Vector v = Cross(pline, qline);
        if (v.z != 0.F) {
            const Vector2 v2(v.x / v.z, v.y / v.z); // intersection point
            Vector2 u(q.x - p.x, q.y - p.y);
            u.Normalize();
            const Vector2 uperp = Rot90CW(u); // direction of altitude from v to pq
            Vector2 vp(p.x - v2.x, p.y - v2.y);
            float h = vp.Dot(uperp);
            if (!inward)
                h = -h;
            if (h >= 0.F) {
                if (ans > h)
                    ans = h;
            }
        }
    }
    return ans;
}

// Return amount of first "split event": where an inset edge is split by
// an advancing reflex vertex.
// We are looking for the distance h such that there is a point s, between q and r
// leading to a point v that is h away from s, perpendicular to qr, to its left
// (or right, if !inward).
// Furthermore, v is on the line going from p in direction pdir (-pdir if !inward),
// and the distance pv is h/sintheta.
// All action takes place in the xy plane.
// If there is no such event, return -1.F.
//
// I derived the equations for this by:
//   v = (h/sintheta)n + p  (where n is unit vector in direction pdir)
//   v = hm + s  (where m is unit vector perp to qr, pointing leftward)
//   s = q + tu  (where u is unit vector in direction qr), some t to be determined
// Then eliminate h from first two equations to get one equation where s is only unknown,
// then substitute for s.x and s.y, and solve for t.
// The expression for t turns out to be easily represented by dot products with various
// perp vectors.
static float SplitEvent(const Vector &p, const Vector &pdir, const float sintheta, const Vector &q, const Vector &r, const BOOL inward) {
    if (sintheta < 1e-7F)
        return -1.F; // angle at p is too cuspy; numeric error will be too great
    Vector2 n(pdir.x, pdir.y);
    n.Normalize();
    if (!inward)
        n = -n;
    const Vector2 qr(r.x - q.x, r.y - q.y);
    const Vector2 u = qr.Normalized();
    const Vector2 m = Rot90CCW(u);
    const Vector2 a = hash_math::rcp(sintheta) * n - m;
    if (a.x == 0.F && a.y == 0.F)
        return -1.F; // m points in wrong direction (same as n)
    const float tdenom = -a.Dot(m);
    if (hash_math::abs(tdenom) < 1e-6F)
        return -1.F;
    const Vector2 pminusq(p.x - q.x, p.y - q.y);
    const Vector2 pminusqperp = Rot90CW(pminusq);
    const float tnumerator = a.Dot(pminusqperp);
    const float t = tnumerator / tdenom;
    if (t < 0.0 || t > qr.Norm())
        return -1.F; // s not between q and r
    float h;
    if (hash_math::abs(a.x) > hash_math::abs(a.y))
        h = (u.x * t - pminusq.x) / a.x;
    else
        h = (u.y * t - pminusq.y) / a.y;
    if (h < 0.F)
        h = -1.F;
    return h;
}

// Return max possible inset (where first edge or split event happens).
float PolygonalArea::MaxInset(const BOOL inward) const {
    float ans = PolyFirstEdgeEvent(subdiv, boundary, inward);
    const int n = islands ? islands->Num() : 0;
    if (n > 0) {
        for (int i = 0; i < islands->Num(); ++i) {
            const float v = PolyFirstEdgeEvent(subdiv, islands->Get(i), inward);
            if (v < ans)
                ans = v;
        }
    }
    // For split events, need to consider all reflex vertices against
    // all non-adjacent edges, across all polys in the area.
    // Let "-1" represent the boundary in a loop over all polys in area.
    for (int i = -1; i < n; ++i) {
        Edge *polyi = i < 0 ? boundary : islands->Get(i);
        for (int j = -1; j < n; ++j) {
            Edge *polyj = j < 0 ? boundary : islands->Get(j);
            SplineIter iit(polyi);
            for (; iit.Cur() != nullptr; iit.GetNext()) {
                Edge *ie = iit.Cur();
                // Note: this code assumes faces haven't been closed yet,
                // but this function is called as a prelude to closing, so OK.
                const AngleKind iak = subdiv->LeftFaceAngleKind(ie);
                if (iak != ANG_REFLEX)
                    continue; // TODO: consider ANG_360 too
                Vector p = subdiv->Coords(ie->Org());
                Vector din = subdiv->EndTangent(ie->Lprev());
                Vector dout = subdiv->StartTangent(ie);
                Vector bisector = Bisector(din, dout);
                dout.Normalize();
                const double costheta = Dot(bisector, dout);
                const auto sintheta = (float)hash_math::sqrt(1.0 - costheta * costheta);

                SplineIter jit(polyj);
                for (; jit.Cur() != nullptr; jit.GetNext()) {
                    const Edge *je = jit.Cur();
                    if (je == ie || je == ie->Sprev() || je == ie->Snext())
                        continue;
                    [[maybe_unused]] BOOL ccw = subdiv->PointsAreCCW(ie->Org(), je->Org(), je->Dst());
                    //if((inward && !ccw) || (!inward && ccw))
                    //	continue;
                    Vector q = subdiv->Coords(je->Org());
                    Vector r = subdiv->Coords(je->Dst());
                    const float v = SplitEvent(p, bisector, sintheta, q, r, inward);
                    if (v != -1.F && v < ans) {
                        ans = v;
                    }
                }
            }
        }
    }
    return ans;
}

// Return TRUE if following Snext() edges from e, loop back.
// Furthermore, following Lnext() and Rprev() edges goes around
// the same loop.
static BOOL PolyIsClosedSpline(Subdiv *subdiv, Edge *e) {
    SplineIter pit(e);
    if (e->Sprev() == nullptr)
        return FALSE;
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        Edge *f = pit.Cur();
        const Edge *fnext = f->Snext();
        if (fnext == nullptr)
            return FALSE;
        if (fnext != f->Lnext() || fnext != f->Rprev())
            return FALSE;
    }
    return TRUE;
}

// Return TRUE if PolyIsClosedSpline is TRUE for the boundary
// and all islands.
BOOL PolygonalArea::AllClosedSplines() const {
    if (!PolyIsClosedSpline(subdiv, boundary))
        return FALSE;
    const int n = islands ? islands->Num() : 0;
    if (n > 0) {
        for (int i = 0; i < islands->Num(); ++i)
            if (!PolyIsClosedSpline(subdiv, islands->Get(i)))
                return FALSE;
    }
    return TRUE;
}

// Return TRUE if some polygon crosses (not just touches) itself or another.
// This test regards all edges as straight --- i.e., we disregard
// any bezier information.
BOOL PolygonalArea::Crosses() const {
    subdiv->SortPoints(); // should be a noop, but just be sure
    const int n = islands ? islands->Num() : 0;
    for (int i = -1; i < n; ++i) {
        Edge *polyi = i < 0 ? boundary : islands->Get(i);
        for (int j = -1; j < n; ++j) {
            Edge *polyj = j < 0 ? boundary : islands->Get(j);
            SplineIter iit(polyi);
            for (; iit.Cur() != nullptr; iit.GetNext()) {
                Edge *ie = iit.Cur();
                const int ieorg = ie->Org();
                const int iedst = ie->Dst();
                SplineIter jit(polyj);
                for (; jit.Cur() != nullptr; jit.GetNext()) {
                    const Edge *je = jit.Cur();
                    if (je == ie || je == ie->Sprev() || je == ie->Snext())
                        continue;
                    if (subdiv->SegsIntersect(ieorg, iedst, je->Org(), je->Dst()))
                        return TRUE;
                }
            }
        }
    }
    return FALSE;
}

PolygonalAreaArray::PolygonalAreaArray(const int n) {
    areas = n > 0 ? new PolygonalArea *[n] : nullptr;
    num = n;
    allocnum = n;
}

PolygonalAreaArray::PolygonalAreaArray(const int n, const int allocn) {
    areas = allocn > 0 ? new PolygonalArea *[allocn] : nullptr;
    num = n;
    allocnum = allocn;
}

PolygonalAreaArray::PolygonalAreaArray(const PolygonalAreaArray &other) {
    if (other.num > 0) {
        areas = new PolygonalArea *[other.num];
        memcpy(areas, other.areas, other.num * sizeof(PolygonalArea *));  // NOLINT(bugprone-sizeof-expression)
    } else
        areas = nullptr;
    num = other.num;
    allocnum = other.num;
}

PolygonalAreaArray::~PolygonalAreaArray() {
    if (areas != nullptr) {
        for (int i = 0; i < num; ++i)
            delete areas[i];
        delete [] areas;
    }
}

void PolygonalAreaArray::Set(const int i, PolygonalArea *a) {
    if (i >= num)
        GrowTo(i + 1);
    areas[i] = a;
}

void PolygonalAreaArray::Add(PolygonalArea *a) {
    if (num >= allocnum)
        GrowTo(num + 1);
    areas[num++] = a;
}

// Make array's "num" be at least the argument.
// If it needs to grow, allow slop for faster grow next time
void PolygonalAreaArray::GrowTo(const int n) {
    if (n > this->allocnum) {
        const int newallocn = n * 2;
        ASSERT(newallocn >0);
        auto **newareas = new PolygonalArea *[newallocn];
        memcpy(newareas, this->areas, this->num * sizeof(PolygonalArea *));  // NOLINT(bugprone-sizeof-expression)
        for (int i = this->num; i < newallocn; ++i)
            newareas[i] = nullptr;
        delete [] this->areas;
        this->areas = newareas;
        this->allocnum = newallocn;
    }
    this->num = n;
}

// Return new array, with copies using corresponding PolygonalArea member functions
PolygonalAreaArray *PolygonalAreaArray::Copy(const Vector &offset) const {
    auto *ans = new PolygonalAreaArray(num);
    for (int i = 0; i < num; ++i)
        ans->Set(i, areas[i]->Copy(offset));
    return ans;
}

void PolygonalAreaArray::Inset(const float inset, const BOOL inward) const {
    for (int i = 0; i < num; ++i)
        areas[i]->Inset(inset, inward);
}

void PolygonalAreaArray::CutCorners(const float inset, const BOOL round) const {
    for (int i = 0; i < num; ++i)
        areas[i]->CutCorners(inset, round);
}

void PolygonalAreaArray::Subdivide(const BOOL all) const {
    for (int i = 0; i < num; ++i)
        areas[i]->Subdivide(all);
}

float PolygonalAreaArray::MaxInset(const BOOL inward) const {
    float ans = 1000000.0F;
    for (int i = 0; i < num; ++i) {
        const float v = areas[i]->MaxInset(inward);
        if (v < ans)
            ans = v;
    }
    return ans;
}

BOOL PolygonalAreaArray::AllClosedSplines() const {
    for (int i = 0; i < num; ++i)
        if (!areas[i]->AllClosedSplines())
            return FALSE;
    return TRUE;
}

BOOL PolygonalAreaArray::Crosses() const {
    for (int i = 0; i < num; ++i)
        if (areas[i]->Crosses())
            return TRUE;
    return FALSE;
}

// "a" is an array of numarrays PolygonalAreaArrays.
// Each array should have the same length, and the PolygonalAreas within each array
// should all be copies (using Copy, CopyInset, or CopyCutCorners) of some common PolygonalArea.
// All should use the same subdivision, subdiv.
// If any of the copies came from CopyCutCorners, they should form a contiguous range within
// the "a" array: from index firstcut to lastcut, inclusive.
// This routine "skins" the copies by connecting corresponding vertices with splines.
// Within the range [firstcut .. lastcut] there will be two splines needed for the cut-off corners
// (identified by being the ends of QE_CUT_CORNER edges), and those two splines will have to
// extend and joine at firstcut-1 and lastcut+1, if there are copies at those indices.
// If "round" is TRUE, any splines joining vertices with different (x,y) coordinates are made
// into circular arcs.  (This presumes the copies are basically offset in the z direction.)
// If firstcut < 0, there are not cut-corners copies.
void Skin(Subdiv *subdiv, PolygonalAreaArray **a, const int numarrays, const BOOL round, const int firstcut, const int lastcut) {
    if (numarrays == 0)
        return;
    const PolygonalAreaArray *a0 = a[0];
    const int n = a0->Num();
    if (n == 0)
        return;
    int j;
    const EdgeArray polys(numarrays);
    int pass = 0;
    if (firstcut >= 0 && (firstcut > 0 || lastcut < numarrays - 1))
        pass = 1;
    for (int i = 0; i < n; ++i) {
        const PolygonalArea *a0i = a0->Get(i);
        const int numislands = a0i->islands ? a0i->islands->Num() : 0;
        // first, skin the boundaries
        PolygonalArea *aji;
        for (j = 0; j < numarrays; ++j) {
            ASSERT(a[j]->Num() == n);
            aji = a[j]->Get(i);
            polys.Set(j, aji->boundary);
        }
        SkinPolys(subdiv, &polys, round, firstcut, lastcut, pass);
        if (pass == 1)
            SkinPolys(subdiv, &polys, round, firstcut, lastcut, 2);
        // now the islands
        for (int k = 0; k < numislands; ++k) {
            for (j = 0; j < numarrays; ++j) {
                aji = a[j]->Get(i);
                ASSERT(aji->islands->Num() == numislands);
                polys.Set(j, aji->islands->Get(k));
            }
            SkinPolys(subdiv, &polys, round, firstcut, lastcut, pass);
            if (pass == 1)
                SkinPolys(subdiv, &polys, round, firstcut, lastcut, 2);
        }
    }
}

// Like Skin(), but now have only copies of polygons to connect.
// The polys array contains (corresponding) representative edges in the polygons.
// If pass == 0, don't treat cut-corners specially (all polygons will have same number of vertices).
// If pass == 1, there will be some cut-corners: we connect up to the first vertex of the corner pair
// and skip the second.
// If pass == 2, then we only connect from MAX(firstcut-1,0) to MIN(lastcut+1, n-1) and we connect
// up to the second vertex of corner pairs.
// Note: if pass is 1 or 2, either the first or the last polygon will not be the the "cut" range,
// and and one can be used to control the non-cut-corner iteration.
static void SkinPolys(Subdiv *subdiv, const EdgeArray *polys, const BOOL round, const int firstcut, const int lastcut, const int pass) {
    const int n = polys->Num();
    if (n <= 1)
        return;
    // we will connect polygons in polys[istart .. iend],
    // using curedges to iterate over edges of polygons we are connecting
    const EdgeArray curedges(*polys);
    int istart = 0;
    int iend = n - 1;
    if (pass == 2) {
        if (firstcut > 0)
            istart = firstcut - 1;
        if (lastcut < n - 1)
            iend = lastcut + 1;
    }
    int controli = 0;
    if (pass != 0 && firstcut == 0)
        controli = n - 1; // should be a non-cut-corners polygon

    SplineIter sit(polys->Get(controli));
    int i;
    Edge *e;
    for (; sit.Cur() != nullptr; sit.GetNext()) {
        BOOL doconnect = TRUE;
        if (pass == 2) {
            // skip over first vertex of cut-corner edges
            doconnect = FALSE;
            for (i = firstcut; i <= lastcut; ++i) {
                e = curedges.Get(i);
                if (e->QEdge()->FlagIsSet(QE_CUT_CORNER)) {
                    curedges.Set(i, e->Snext());
                    doconnect = TRUE;
                }
            }
        }
        if (doconnect) {
            const int sp = subdiv->NewSpline();
//            Edge *esp = nullptr;
            for (i = istart; i < iend; ++i) {
                // connect current vertex at i to the one at i+1
                e = curedges.Get(i);
                Edge *f = curedges.Get(i + 1);
                const Edge *esp = subdiv->Connect(e->Sym(), f, sp);
                if (round && (i == 0 || i == n - 2)) {
                    Vector org = subdiv->Coords(esp->Org());
                    const Vector dst = subdiv->Coords(esp->Dst());
                    const Vector evec = dst - org;
                    Vector2 evec2(evec.x, evec.y);
                    const float hdist = evec2.Norm();
                    if (hdist != 0.F && evec.z != 0.F) {
                        // Make tangent horizontal at the end that is at the top or bottom.
                        // Make tangent vertical at the other end.
                        // The control points should be kappa = (4/3)*(sqrt(2)-1) = .5523...
                        // of the way along the arms of the right triangle that includes
                        // org and dst. (This gets circular approx. if arms are equal length.)
                        // (See comment on PolyCutCorners, above. )
                        constexpr float kappa = 0.5522847498F;
                        Vector cp0;
                        Vector cp1;
                        if (i == 0) {
                            cp0 = org + kappa * Vector(evec.x, evec.y, 0.F);
                            cp1 = dst + kappa * Vector(0.F, 0.F, -evec.z);
                        } else {
                            cp0 = org + kappa * Vector(0.F, 0.F, evec.z);
                            cp1 = dst - kappa * Vector(evec.x, evec.y, 0.F);
                        }
                        esp->SetBezCP(0, cp0);
                        esp->SetBezCP(1, cp1);
                    }
                }
            }
        }
        if (pass == 1) {
            // skip over second vertex of cut-corner edges
            for (i = firstcut; i <= lastcut; ++i) {
                e = curedges.Get(i);
                if (e->QEdge()->FlagIsSet(QE_CUT_CORNER))
                    curedges.Set(i, e->Snext());
            }
        }
        // bump all edges
        for (i = istart; i <= iend; ++i) {
            e = curedges.Get(i);
            curedges.Set(i, e->Snext());
        }
    }
}
