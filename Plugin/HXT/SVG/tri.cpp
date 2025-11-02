// ReSharper disable CppTooWideScope
// ReSharper disable CppClangTidyMiscUseAnonymousNamespace
#include "StdAfx.h"
#include "Vector.h"
#include "Vector2.h"
#include "geom.h"
#include "tri.h"
#include "poly.h"
#include "Rnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

// Triangulation, based on paper:
//   FIST: Fast Industrial-Strength Triangulation of Polygons, by Martin Held

class Ear {
public:
    Ear *next{nullptr}; // in list of ears
    Edge *e{nullptr}; // ear is (e->Lprev()->Org(), e->Org(), e->Dst())
    double priority{0}; // desirablity of choosing (bigger : more desirable)

    explicit Ear(Edge *eare, const double pri) : e(eare), priority(pri) {}
    explicit Ear(const Subdiv *s, Edge *eare, bool isdegenerate);
//    ~Ear() = default;

    [[nodiscard]] int Vm2() const {
        return e->Lprev()->Lprev()->Org();
    }

    [[nodiscard]] int Vm1() const {
        return e->Lprev()->Org();
    }

    [[nodiscard]] int V0() const {
        return e->Org();
    }

    [[nodiscard]] int V1() const {
        return e->Dst();
    }

    [[nodiscard]] int V2() const {
        return e->Lnext()->Dst();
    }
};

static void JoinIslands(Subdiv *s, const PolygonalArea *a);
static BOOL IsDiagonal(Subdiv *s, Edge *polye, int p);
static void ClassifyAngles(const Subdiv *s, Edge *e);
static Ear *FindEars(Subdiv *s, Edge *polye);
static int IsEar(Subdiv *s, Edge *e);
static Ear *InsertEar(Ear *head, Ear *newear);
static Ear *DeleteEar(Ear *head, const Edge *eare);
//static Ear *FindEar(Ear *head, Edge *eare);
static BOOL InCone(Subdiv *s, int testv, int a, int b, int c, AngleKind kind);
static int _cdecl EdgeOrgCmp(const Edge **pe1, const Edge **pe2);
static const char *KindName(AngleKind k);
static double TriangleGoodness(const Subdiv *s, int a, int b, int c);
static Edge *TriangleRecoveryProcess(Subdiv *s, Edge *poly, Ear *&earqueue, int &numfaces, BOOL *pclipped);
static void MakeCDT(const Subdiv *s);

void Triangulate(Subdiv *s) {
    if (s->NumPoints() < 2)
        return;
    const PolygonalAreaArray *areas = FindPolygonalAreas(s);
    for (int i = 0; i < areas->Num(); ++i) {
        TriangulateArea(s, areas->Get(i));
        delete areas->Get(i);
    }
    delete areas;
}

// Return number of triangles.
// (Faces will have unique vals from -1 to #triangles-1, where
// -1 means "outside").
int TriangulateArea(Subdiv *s, const PolygonalArea *a) {
    gtrace("TriangulateArea\n");
    JoinIslands(s, a);
    Edge *b = a->boundary;
    // Use Val fields of face-to-face edges to hold a "face number"
    // for the orgin face.  Start with outside face == -1 and inside == 0.
    // As carve off ears, give each ear a successively higher number.
    // ReSharper disable once CppDeclaratorNeverUsed
    [[maybe_unused]] Edge *rtol = b->Rot(); // crosses b from right to left
    SetLeftFaceVal(b, 0);
    SetLeftFaceVal(b->Sym(), -1);
    int numfaces = 1;
    int numv = Subdiv::LeftFaceSize(b);
    if (numv <= 3)
        return numfaces;
    ClassifyAngles(s, b);
    EdgeList polylist;
    polylist.AddHead(b);
    while (polylist.Num() != 0) {
        b = polylist.RemoveHead();
        Ear *earqueue = FindEars(s, b);
        BOOL earclippedprev = FALSE;
        while (numv > 3) {
            gtraceLeftFace("Triangulate Face", b);
            if (earqueue != nullptr) {
                const Ear *ear = earqueue;
                earqueue = earqueue->next;
                Edge *e = ear->e;
                delete ear;
                const Edge *eprev = e->Lprev();
                Edge *eprev2 = eprev->Lprev();
                Edge *enext = e->Lnext();
                gtrace("TriangulateArea: chop ear (%d,%d,%d)\n", eprev->Org(), e->Org(), e->Dst());
                Edge *diag = s->Connect(eprev2, enext, s->NewSpline());
                SetLeftFaceVal(e, numfaces++);
                earclippedprev = TRUE;
                numv--;
                if (numv == 3)
                    break;
                diag->SetVal(s->LeftFaceAngleKind(diag));
                enext->SetVal(s->LeftFaceAngleKind(enext));
                if (b == eprev || b == e) {
                    b = enext;
                    gtrace("  new boundary rep: (%d,%d)\n", b->Org(), b->Dst());
                }
                // If eprev or enext were ears, they are not necessarily so any more
                // so remove them from queue
                earqueue = DeleteEar(earqueue, eprev);
                gtrace("  delete ear (%d,%d,%d)\n", eprev->Lprev()->Org(), eprev->Org(), eprev->Dst());
                earqueue = DeleteEar(earqueue, enext);
                gtrace("  delete ear (%d,%d,%d)\n", enext->Lprev()->Org(), enext->Org(), enext->Dst());
                int isear = IsEar(s, diag);
                if (isear) {
                    gtrace("  new ear (%d,%d,%d)\n", diag->Lprev()->Org(), diag->Org(), diag->Dst());
                    earqueue = InsertEar(earqueue, new Ear(s, diag, isear == 2));
                } else
                    gtrace("  not new ear (%d,%d,%d)\n", diag->Lprev()->Org(), diag->Org(), diag->Dst());
                isear = IsEar(s, enext);
                if (isear) {
                    gtrace("  new ear (%d,%d,%d)\n", enext->Lprev()->Org(), enext->Org(), enext->Dst());
                    earqueue = InsertEar(earqueue, new Ear(s, enext, isear == 2));
                } else
                    gtrace("  not new ear (%d,%d,%d)\n", enext->Lprev()->Org(), enext->Org(), enext->Dst());
            } else if (earclippedprev) {
                // Try rebuilding earqueue (maybe some reflex vertices in self-overlapping
                // polygons are now out of the picture
                gtrace("Can't find ear; try building ear queue again\n");
                ClassifyAngles(s, b);
                earqueue = FindEars(s, b);
                earclippedprev = FALSE;
            } else {
                b = TriangleRecoveryProcess(s, b, earqueue, numfaces, &earclippedprev);
//                b = TriangleRecoveryProcess(s, b, earqueue, polylist, numfaces, &earclippedprev);
                numv = Subdiv::LeftFaceSize(b);
            }
        }
        while (earqueue != nullptr) {
            const Ear *ear = earqueue;
            earqueue = earqueue->next;
            delete ear;
        }
    }
    gtrace("TriangulateArea found %d faces\n", numfaces);
    MakeCDT(s);
    return numfaces;
}

// Recovery process when TriangulateArea can't find an ear
// (presumably because the polygon isn't simple).
// This either inserts an ear into earqueue or splits
// the polygon in two, returning one half as the return value and
// the other half gets inserted into polylist.
// This routine also might clip an ear itself;set *pclipped to true if so.
static Edge *TriangleRecoveryProcess(Subdiv *s, Edge *poly, Ear *&earqueue, int &numfaces, BOOL *pclipped) {
    //AfxMessageBox("Recovery process invoked");
    gtrace("Can't find ear, doing recovery process\n");

    BOOL clipped = FALSE;
    gtrace("Look for local self intersection\n");
    LeftFaceIter it(poly);
    Edge *e;
    Edge *eprev = nullptr;
    Edge *enext = nullptr;
    for (; (e = it.Cur()) != nullptr; it.GetNext()) {
        e = it.Cur();
        eprev = e->Lprev();
        enext = e->Lnext();
        const int a = eprev->Org();
        const int b = e->Org();
        const int c = enext->Org();
        const int d = enext->Dst();
        if (s->SegsIntersect(a, b, c, d)) {
            gtrace("Local intersection of (%d,%d) (%d,%d)\n", a, b, c, d);
            break;
        }
    }
    if (e != nullptr) {
        gtrace("TriangleRecoveryProcess: chop \"ear\" (%d,%d,%d)\n", e->Org(), enext->Org(), enext->Dst());
        Edge *enext2 = enext->Lnext();
        Edge *diag = s->Connect(eprev, enext2, s->NewSpline());
        if (poly == e || poly == enext) {
            poly = enext2;
            gtrace("  new boundary rep: (%d,%d)\n", poly->Org(), poly->Dst());
        }
        SetLeftFaceVal(e, numfaces++);
        diag->SetVal(s->LeftFaceAngleKind(diag));
        enext2->SetVal(s->LeftFaceAngleKind(enext2));
        clipped = TRUE;
    } else {
        //AfxMessageBox("Can't find local self-intersection");
        gtrace("Can't find local self-intersections\n");
        gtrace("Pick random ear\n");
        int numconvex = 0;
        int numtot = 0;
        LeftFaceIter cit(poly);
        for (; cit.Cur() != nullptr; cit.GetNext()) {
            e = cit.Cur();
            const auto k = (AngleKind)e->Val();
            if (k == ANG_CONVEX || k == ANG_0)
                numconvex++;
            numtot++;
        }
        int choosei;
        if (numconvex > 0)
            choosei = Rnd_RandMax() % numconvex;
        else
            choosei = Rnd_RandMax() % numtot;
        int i = 0;
        LeftFaceIter dit(poly);
        for (; dit.Cur() != nullptr; dit.GetNext()) {
            e = dit.Cur();
            const auto k = (AngleKind)e->Val();
            if (numconvex == 0 || k == ANG_CONVEX || k == ANG_0) {
                if (i++ == choosei)
                    break;
            }
        }
        gtrace("Making (%d,%d,%d) an ear\n", e->Lprev()->Org(), e->Org(), e->Dst());
        Ear *newear = new Ear(s, e, true);
        earqueue = InsertEar(earqueue, newear);
    }
    *pclipped = clipped;
    return poly;
}

// Assume polygons in PolygonalArea a are given by
// their LeftFaceLowestOrg representatives.
// Sort (a copy of) the islands by leftmost vertices.
// For each island in turn, look for diagonal joining
// the leftmost vertex of the island to the current
// boundary, and join that island to the boundary.
static void JoinIslands(Subdiv *s, const PolygonalArea *a) {
    Edge *b = a->boundary;
    ASSERT(b != nullptr);
    gtrace("JoinIslands, boundary=(%d,%d)\n", b->Org(), b->Dst());
    if (a->islands == nullptr)
        return;
    const EdgeArray islands(*a->islands);
    islands.Sort(EdgeOrgCmp);
    for (int i = 0; i < islands.Num(); ++i) {
        Edge *isl = islands.Get(i);
        gtrace("Join Island (%d,%d) to boundary\n", isl->Org(), isl->Dst());
        const int islorg = isl->Org();
        const Vector2 islorgv = s->Coords2(islorg);
        // Look at vertices of b left of islorg, looking for shortest
        // connection that doesn't cross b
        double mindist2 = 1e30;
        const Edge *bestedge = nullptr;
        // Should be able to find a diagonal that connects a vertex of b
        // left of islorg to islorg without crossing b, but try two
        // more desperation passes after that to get SOME diagonal, even if
        // it might cross some edge somewhere.
        // First desperation pass (pass == 1): allow points right of islorg.
        // Second desperation pass (pass == 2) : allow crossing boundary poly
        for (int pass = 0; bestedge == nullptr && pass < 3; ++pass) {
            if (pass > 0)
                gtrace("Join Island needs desperation pass %d\n", pass);
            LeftFaceIter bit(b);
            for (; bit.Cur() != nullptr; bit.GetNext()) {
                Edge *be = bit.Cur();
                const int borg = be->Org();
                if (pass == 0 && borg > islorg)
                    continue;
                const Vector2 diff = islorgv - s->Coords2(borg);
                const double dist2 = diff.x * diff.x + diff.y * diff.y;
                if (bestedge != nullptr && mindist2 <= dist2)
                    continue;
                if (IsDiagonal(s, be, islorg) || pass == 2) {
                    bestedge = be;
                    mindist2 = dist2;
                }
            }
        }
        ASSERT(bestedge != nullptr);
        gtrace("diagonal for island: (%d,%d)\n", bestedge->Org(), bestedge->Dst());
        s->Connect(bestedge->Lprev(), isl, s->NewSpline());

        // For debugging
        gtraceLeftFace("New boundary", b);
    }
}

// An ear if a polygon consists of three consecutive vertices
// v(-1), v0, v1 such that v(-1) can connect to v1 without intersecting
// the polygon.
// One test for an ear is:
//   1. v1 is convex
//   2. Triangle v(-1),v0,v1 doesn't contain a reflex vertex (except
//      possibly v(-1) and v1) of polygon, even on boundary of triangle.
// For efficiency, and helping to deal with non-simple polygons,
// also check that v(-1) is in Cone(v0, v1, v2) and  v1 is in Cone(v(-2), v(-1), v0).
// (See InCone function for definition of Cone).
// Return list of ears of polygon that is left face of polye.
// Assume edge Val fields have angle classifications for angles in left face.
// The returned list is prioritorized in order of desirability
// of chopping.
static Ear *FindEars(Subdiv *s, Edge *polye) {
    gtrace("FindEars\n");
    Ear *head = nullptr;
    LeftFaceIter pit(polye);
    for (; pit.Cur() != nullptr; pit.GetNext()) {
        Edge *e = pit.Cur();
        const int isear = IsEar(s, e);
        if (isear) {
            Ear *newear = new Ear(s, e, isear == 2);
            head = InsertEar(head, newear);
        }
    }
    gtrace("FindEars returning:\n");
    for (const Ear *ee = head; ee != nullptr; ee = ee->next) {
        gtrace("  (%d,%d,%d) prio=%f\n", ee->e->Lprev()->Org(), ee->e->Org(), ee->e->Dst(), ee->priority);
    }

    return head;
}

Ear::Ear(const Subdiv *s, Edge *eare, const bool isdegenerate) : e(eare) {
    if (isdegenerate)
        priority = 1e6;
    else
        priority = TriangleGoodness(s, e->Lprev()->Org(), e->Org(), e->Dst());
}

// Insert into newear into queue of ears starting with head,
// maintaining highest priority first.
// Return new head.
static Ear *InsertEar(Ear *head, Ear *newear) {
    if (head == nullptr)
        head = newear;
    else {
        Ear *earprev = nullptr;
        Ear *ear = head;
        for (; ear != nullptr; ear = ear->next) {
            if (newear->priority >= ear->priority) {
                if (earprev == nullptr) {
                    newear->next = head;
                    head = newear;
                } else {
                    newear->next = earprev->next;
                    earprev->next = newear;
                }
                break;
            }
            earprev = ear;
        }
        if (ear == nullptr)
            earprev->next = newear;
    }
    return head;
}

// Remove and delete Ear with edge eare (if any)
// from Ear list beginning with head.
// Assume there is at most one in the list.
// Return new head.
static Ear *DeleteEar(Ear *head, const Edge *eare) {
    if (head != nullptr) {
        Ear *earprev = nullptr;
        Ear *ear = head;
        for (; ear != nullptr; ear = ear->next) {
            if (ear->e == eare) {
                if (earprev == nullptr) {
                    head = ear->next;
                } else {
                    earprev->next = ear->next;
                }
                delete ear;
                break;
            }
            earprev = ear;
        }
    }
    return head;
}

// Search Ear list for ear containing eare, returning it if found,
// else return 0.
/*
static Ear *FindEar(Ear *head, Edge *eare) {
    for (Ear *ear = head; ear != nullptr; ear = ear->next)
        if (ear->e == eare)
            return ear;
    return nullptr;
}
*/
// Return 0 if e is not an ear, 1 if it is, and 2 if it is a degenerate one.
// Assume angle classifications are in Val fields.
static int IsEar(Subdiv *s, Edge *e) {
    const auto kind = (AngleKind)e->Val();
    const Edge *elprev = e->Lprev();
    const Edge *elnext = e->Lnext();
    const int vm2 = elprev->Lprev()->Org();
    const int vm1 = elprev->Org();
    const int v0 = e->Org();
    const int v1 = e->Dst();
    const int v2 = elnext->Dst();
    gtrace("IsEar (%d, %d,%d) kind=%s\n", vm1, v0, v1, KindName(kind));

    if (v0 == v1 || v1 == v2) {
        gtrace("    degenerate EAR!\n");
        return 2; // degenerate ear
    }

    if (kind == ANG_CONVEX || kind == ANG_TANGENTIAL || kind == ANG_0) {
        const auto prevkind = (AngleKind)elprev->Val();
        const auto nextkind = (AngleKind)elnext->Val();
        if (InCone(s, vm1, v0, v1, v2, nextkind) && InCone(s, v1, vm2, vm1, v0, prevkind)) {
            LeftFaceIter it(e);
            for (; it.Cur() != nullptr; it.GetNext()) {
                const Edge *f = it.Cur();
                const int fv = f->Org();
                const auto k = (AngleKind)f->Val();
                if ((k == ANG_REFLEX || k == ANG_360) && fv != vm1 && fv != v0 && fv != v1) {
                    //gtrace("  test at %d, kind=%s\n", fv, KindName(k));
                    // is fv inside closure of triangle (vm1, v0, v1) ?
                    if (!(s->PointsAreCCW(v0, vm1, fv) || s->PointsAreCCW(vm1, v1, fv) || s->PointsAreCCW(v1, v0, fv))) {
                        gtrace("    %d inside (%d,%d,%d) -> not ear\n", fv, vm1, v0, v1);
                        return 0;
                    }
                }
            }
            gtrace("    EAR!\n");
            return 1;
        }
        gtrace("    Cone test fails -> not ear\n");
    }
    return 0;
}

// Return TRUE if point with index testv is in Cone of points with
// indices a, b, c, where angle abc has AngleKind kind.
// The Cone is the set of points "inside" the left face defined by
// segments ab and bc, disregarding all other segments of polygon for
// purposes of "inside" test.
static BOOL InCone(Subdiv *s, const int testv, const int a, const int b, const int c, const AngleKind kind) {
    BOOL ans;
    if (kind == ANG_REFLEX || kind == ANG_360) {
        ans = !InCone(s, testv, c, b, a, ANG_CONVEX);
        if (ans) {
            // ans is TRUE unless testv is on ray ba or ray bc
            if (!s->PointsAreCCW(b, a, testv) && !s->PointsAreCCW(b, testv, a) && s->PointsAreCCW(c, b, testv))
                ans = FALSE;
            if (!s->PointsAreCCW(b, c, testv) && !s->PointsAreCCW(b, testv, c) && s->PointsAreCCW(b, a, testv))
                ans = FALSE;
        }
    } else {
        ans = s->PointsAreCCW(a, b, testv) && s->PointsAreCCW(b, c, testv);
    }
    return ans;
}

// Return TRUE if segment connecting point with index p to
// origin of edge polye is a diagonal of left face of polye:
// p is in the cone of the angle with origin polye->Org(),
// and left face does not intersect the segment.
static BOOL IsDiagonal(Subdiv *s, Edge *polye, const int p) {
    const int q = polye->Org();
    const AngleKind kind = s->LeftFaceAngleKind(polye);
    BOOL ok = InCone(s, p, polye->Lprev()->Org(), q, polye->Dst(), kind);
    LeftFaceIter it(polye);
    for (; ok && it.Cur() != nullptr; it.GetNext()) {
        const Edge *f = it.Cur();
        ok = !s->SegsIntersect(q, p, f->Org(), f->Dst());
    }
    return ok;
}

// For sorting edges in ascending order of Org()
// (i.e., from left to right, ties broken bottom to top)
static int _cdecl EdgeOrgCmp(const Edge **pe1, const Edge **pe2) {
    const int org1 = (*pe1)->Org();
    const int org2 = (*pe2)->Org();
    return org1 - org2;
}

static BOOL IsReversed(const Subdiv *s, Edge *e) {
    if (e->QEdge()->FlagIsSet(QE_BOUNDARY))
        return FALSE;
    Edge *elnext = e->Lnext();
    const Edge *elnext2 = elnext->Lnext();
    Edge *ernext = e->Rnext();
    const Edge *ernext2 = ernext->Rnext();
    const int eorg = e->Org();
    // following should be true if really have a triangulation
    // and e is not on the boundary, but if original polygon
    // was degenerate or nonsimple, might be false
    if (elnext2->Dst() == eorg && ernext2->Org() == e->Dst()) {
        if (s->PointInCircle(eorg, e->Dst(), elnext->Dst(), ernext->Org())) {
            // gtrace("IsReversed (%d,%d) = TRUE\n", eorg, e->Dst());
            return TRUE;
        }
    }
    // gtrace("IsReversed (%d,%d) = FALSE\n", eorg, e->Dst());
    return FALSE;
}

// Assume s contains some number of disconnected triangulated polygonal areas,
// with the boundary edges having the QE_BOUNDARY flag set.
// Make the triangulations Constrained Delaunay by flipping "reversed" quadrilaterals
// until can flip no more.
static void MakeCDT(const Subdiv *s) {
    gtrace("MakeCDT\n");
    EdgeList q;
    SubdivEdgeIter sit(s);
    for (; sit.Cur() != nullptr; sit.GetNext()) {
        Edge *e = sit.Cur();
        if (IsReversed(s, e)) {
            q.AddTail(e);
        }
    }
    gtrace("Initially %d reversed edges\n", q.Num());
    while (q.Num() > 0) {
        Edge *e = q.RemoveHead();
        if (IsReversed(s, e)) {
            const int face1 = e->Rot()->Val();
            const int face2 = e->InvRot()->Val();
            Subdiv::RotateInFace(e);
            LeftFaceIter it1(e->Sym());
            for (; it1.Cur() != nullptr; it1.GetNext())
                it1.Cur()->InvRot()->SetVal(face1);
            LeftFaceIter it2(e);
            for (; it2.Cur() != nullptr; it2.GetNext())
                it2.Cur()->InvRot()->SetVal(face2);
            if (IsReversed(s, e->Lnext()))
                q.AddTail(e->Lnext());
            if (IsReversed(s, e->Lnext()->Lnext()))
                q.AddTail(e->Lnext()->Lnext());
            if (IsReversed(s, e->Sym()->Lnext()))
                q.AddTail(e->Sym()->Lnext());
            if (IsReversed(s, e->Sym()->Lnext()->Lnext()))
                q.AddTail(e->Sym()->Lnext()->Lnext());
        }
    }
}

// Set Val of left face of e to v.
void SetLeftFaceVal(Edge *e, const int v) {
    LeftFaceIter it(e);
    for (; it.Cur() != nullptr; it.GetNext())
        it.Cur()->InvRot()->SetVal(v);
}

// Fill in edge "Val" fields with classification of angles in left face of e
static void ClassifyAngles(const Subdiv *s, Edge *e) {
    LeftFaceIter it(e);
    for (; it.Cur() != nullptr; it.GetNext()) {
        Edge *f = it.Cur();
        f->SetVal(s->LeftFaceAngleKind(f));
        gtrace("angle at %d: %s\n", f->Org(), KindName((AngleKind)f->Val()));
    }
}

// Return a figure-of-merit for "goodness" of triangle abc
// we want higher numbers for triangles nearer to equilateral
static double TriangleGoodness(const Subdiv *s, const int a, const int b, const int c) {
    double a1 = s->Angle(a, b, c);
    double a2 = s->Angle(b, c, a);
    double a3 = s->Angle(c, a, b);
    a1 -= 60.0;
    a2 -= 60.0;
    a3 -= 60.0;
    const double d = a1 * a2 + a2 * a2 + a3 * a3;
    if (d == 0.0)
        return 2.0;
    if (d < 0)
        return 1.0 / hash_math::sqrt(-d);
    return 1.0 / hash_math::sqrt(d);
}

// For debugging
static const char *KindName(const AngleKind k) {
    const char *ans;
    switch (k) {
        case ANG_CONVEX:
            ans = "convex";
            break;
        case ANG_REFLEX:
            ans = "reflex";
            break;
        case ANG_TANGENTIAL:
            ans = "tangential";
            break;
        case ANG_0:
            ans = "0";
            break;
        case ANG_360:
            ans = "360";
            break;
        default:
            ans = "?";
            break;
    }
    return ans;
}
