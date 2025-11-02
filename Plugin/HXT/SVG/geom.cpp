// KB  12/3/01  \Ken90\Plugin\HXT\FontMac\geom.cpp

// ReSharper disable CppTooWideScope
#include "StdAfx.h"
#include "Vector.h"
#include "Vector2.h"
#include "geom.h"

#ifdef _DEBUG
#define new DEBUG_NEW  // NOLINT(cppcoreguidelines-macro-usage, clang-diagnostic-keyword-macro)
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

constexpr double Tolerance = 1e-7;
constexpr double Sqrt2 = 1.41421356237;
constexpr double Log4 = 1.38629436112;
constexpr float OneThird = 1.F / 3.F;
constexpr float TwoThirds = 2.F / 3.F;

//was static
constexpr int LeftKid(const int i) {
    return 2 * i + 1;
}

constexpr int RightKid(const int i) {
    return 2 * i + 2;
}

constexpr void setbit(unsigned long &v, const int bit) {
    v |= 1U << bit;
}

constexpr int isbitset(const unsigned long v, const int bit) {
    return v & 1U << bit;
}

// *** Vector, Vector2 ***
Vector LinInterp(const float alpha, const Vector &a, const Vector &b) {
    return (1.F - alpha) * a + alpha * b;
}

Vector2 LinInterp(const float alpha, const Vector2 &a, const Vector2 &b) {
    return (1.F - alpha) * a + alpha * b;
}

// Return vector that is "a" rotated 90 degrees counterclockwise in xy plane
Vector Rot90CCW(const Vector &a) {
    return Vector(-a.y, a.x, a.z);
}

Vector2 Rot90CCW(const Vector2 &a) {
    return Vector2(-a.y, a.x);
}

// Return vector that is "a" rotated 90 degrees clockwise in xy plane
Vector Rot90CW(const Vector &a) {
    return Vector(a.y, -a.x, a.z);
}

Vector2 Rot90CW(const Vector2 &a) {
    return Vector2(a.y, -a.x);
}

// Return angle between a and b, in degrees, in range [0. 180)
float Angle(const Vector &a, const Vector &b) {
    const float norm1 = a.Norm();
    const float norm2 = b.Norm();
    double ang = 0.0;
    if (norm1 != 0.F && norm2 != 0.F) {
        double costheta = Dot(a, b) / (norm1 * norm2);
        if (costheta > 1.)
            costheta = 1.;
        else if (costheta < -1.)
            costheta = -1.;
        ang = acos(costheta) * 180.0 / hash_constants::double_pi;
    }
    return (float)ang;
}

// *** Edge ***

// crosses this edge from right to left
Edge *Edge::Rot() {
    return num < 3 ? this + 1 : this - 3;
}

// crosses this edge from left to right
Edge *Edge::InvRot() {
    return num > 0 ? this - 1 : this + 3;
}

// its origin is this edge's dest, & vice versa
Edge *Edge::Sym() {
    return num < 2 ? this + 2 : this - 2;
}

// next ccw around origin ring
Edge *Edge::Onext() const {
    return next;
}

// next cw around origin ring
Edge *Edge::Oprev() {
    return Rot()->next->Rot();
}

// next ccw (into) around origin ring
Edge *Edge::Dnext() {
    return Sym()->next->Sym();
}

// next cw (into) around origin ring
Edge *Edge::Dprev() {
    return InvRot()->next->InvRot();
}

// next ccw around left face (if this is an "edge" edge)
Edge *Edge::Lnext() {
    return InvRot()->next->Rot();
}

// next cw around left face (if this is an "edge" edge)
Edge *Edge::Lprev() const {
    return next->Sym();
}

// next ccw around right face (if this is an "edge" edge)
// (proceeding around right face "backwards" from this edge's direction)
Edge *Edge::Rnext() {
    return Rot()->next->InvRot();
}

// next cw around right face (if this is an "edge" edge)
// (proceeding around right face "forwards", i.e., with edge's direction)
Edge *Edge::Rprev() {
    return Sym()->next;
}

// next edge in spline chain (or 0, at end of unlooped chain)
Edge *Edge::Snext() {
    const int sp = this->Spline();
    OnextIter oit(this->Sym());
    for (; oit.Cur() != nullptr; oit.GetNext()) {
        Edge *c = oit.Cur();
        if (c->Spline() == sp) {
            return c;
        }
    }
    return nullptr;
}

// prev edge in spline chain (or 0, at end of unlooped chain)
Edge *Edge::Sprev() {
    const int sp = -this->Spline();
    OnextIter oit(this);
    for (; oit.Cur() != nullptr; oit.GetNext()) {
        Edge *c = oit.Cur();
        if (c->Spline() == sp) {
            return c->Sym();
        }
    }
    return nullptr;
}

// containing QuadEdge
QuadEdge *Edge::QEdge() const {
    return (QuadEdge*)(this - num);
}

// set origin of this edge
// (caller should ensure that whole Onext ring has same value)
void Edge::SetOrg(const int org) const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        QEdge()->org = org;
    else
        QEdge()->dst = org;
}

// set destination of this edge
// (caller should ensure that whole Dnext ring has same value)
void Edge::SetDst(const int dst) const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        QEdge()->dst = dst;
    else
        QEdge()->org = dst;
}

void Edge::SetBezCP(const int cpnum, const Vector &v) const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        QEdge()->SetBezCP(cpnum, v);
    else
        QEdge()->SetBezCP(1 - cpnum, v);
}

void Edge::SetSpline(const int spline) const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        QEdge()->spline = spline;
    else
        QEdge()->spline = -spline;
}

int Edge::Org() const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        return QEdge()->org;
    return QEdge()->dst;
}

int Edge::Dst() const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        return QEdge()->dst;
    return QEdge()->org;
}

Vector *Edge::BezCP(const int cpnum) const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        return QEdge()->BezCP(cpnum);
    return QEdge()->BezCP(1 - cpnum);
}

BOOL Edge::IsCubic() const {
    return QEdge()->IsCubic();
}

int Edge::Spline() const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        return QEdge()->spline;
    return -QEdge()->spline;
}

BOOL Edge::SplineIsForward() const {
    ASSERT(num == 0 || num == 2);
    if (num == 0)
        return QEdge()->spline > 0;
    return -QEdge()->spline > 0;
}

// Primitive operation for building subdivisions.
// See Guibas & Stolfi paper on QuadEdges.
// Connects or splits edge rings around origins of a
// and b, depending on whether they were separate or connected.
// Connects or splits left faces of a and be depending
// on whether they were separate or connected.
void Edge::Splice(Edge *a, Edge *b) {
    Edge *alpha = a->next->Rot();
    Edge *beta = b->next->Rot();

    Edge *t1 = b->next;
    Edge *t2 = a->next;
    Edge *t3 = beta->next;
    Edge *t4 = alpha->next;

    a->next = t1;
    b->next = t2;
    alpha->next = t3;
    beta->next = t4;
}

// "head" of spline is first of Sprev chain, or, if the spline
// is looped, the Edge with lowest indexed Origin.
Edge *Edge::SplineHead() {
    Edge *e = this;
    if (!e->SplineIsForward())
        e = e->Sym();
    const Edge *orige = e;
    Edge *elowestorg = e;
    int lowestorg = elowestorg->Org();
    Edge *head = e;
    for (e = e->Sprev(); e != nullptr; e = e->Sprev()) {
        if (e == orige)
            return elowestorg; // looped back
        const int i = e->Org();
        if (i < lowestorg) {
            elowestorg = e;
            lowestorg = i;
        }
        head = e;
    }
    return head;
}

BOOL Edge::SplineIsLooped() {
    Edge *e = this;
    if (!e->SplineIsForward())
        e = e->Sym();
    const Edge *orige = e;
    for (e = e->Sprev(); e != nullptr; e = e->Sprev()) {
        if (e == orige)
            return TRUE;
    }
    return FALSE;
}

// *** QuadEdge ***

QuadEdge::QuadEdge() {
    for (int i = 0; i < 4; ++i) {
        edges[i].num = i;
        edges[i].val = 0;
        edges[i].fval = 0.F;
    }
    edges[0].next = &edges[0];
    edges[1].next = &edges[3];
    edges[2].next = &edges[2];
    edges[3].next = &edges[1];
}

QuadEdge::~QuadEdge() {
    delete [] bezcps;
}

// cpnum should be 0 or 1; allocates bezcps if nec
void QuadEdge::SetBezCP(const int cpnum, const Vector &v) {
    ASSERT(cpnum == 0 || cpnum == 1);
    if (bezcps == nullptr)
        bezcps = new Vector[2];
    bezcps[cpnum] = v;
}

Vector *QuadEdge::BezCP(const int cpnum) const {
    ASSERT(cpnum == 0 || cpnum == 1);
    if (bezcps == nullptr)
        return nullptr;
    return &bezcps[cpnum];
}

// *** Subdiv ***

// start out with spline array having only slot 0,
// which is unused (so that spline id's can always be positive or negative)
Subdiv::Subdiv() : splines(1) {
    qedges = nullptr;
    points = new Points;
    splines.Set(0, nullptr);
}

Subdiv::~Subdiv() {
    const QuadEdge *qe = qedges;
    while (qe != nullptr) {
        const QuadEdge *nextqe = qe->next;
        delete qe;
        qe = nextqe;
    }
    delete points;
}

Edge *Subdiv::MakeEdge() {
    auto *qe = new QuadEdge;
    return &qe->edges[0];
}

Edge *Subdiv::MakeEdge(const Vector &org, const Vector &dst, const int spline) {
    const int orgi = points->AddPoint(org);
    const int dsti = points->AddPoint(dst);
    return this->MakeEdge(orgi, dsti, spline);
}

Edge *Subdiv::MakeEdge(const int orgi, const int dsti, const int spline) {
    ASSERT(0 <= orgi && orgi < points->Num());
    ASSERT(0 <= dsti && dsti < points->Num());

    auto *qe = new QuadEdge;
    qe->org = orgi;
    qe->dst = dsti;
    qe->spline = spline;
    qe->next = this->qedges;
    this->qedges = qe;
    Edge *ans = &qe->edges[0];

    // Make sure there's an edge representative for spline in splines array
    int sp = spline;
    if (sp < 0)
        sp = -sp;
    if (sp != 0) {
        if (this->splines.Num() <= sp)
            this->splines.GrowTo(sp + 1);
        if (this->splines.Get(sp) == nullptr)
            this->splines.Set(sp, ans);
    }

    return ans;
}

int Subdiv::NewSpline() const {
    return this->splines.Num();
}

// Add a new edge connecting the destination of a
// to origin of b, making all have same left face.
// Also, make origin and destination of new edge
// match those of connecting places.
Edge *Subdiv::Connect(Edge *a, Edge *b, const int spline) {
    Edge *e = MakeEdge(a->Dst(), b->Org(), spline);
    Edge::Splice(e, a->Lnext());
    Edge::Splice(e->Sym(), b);
    return e;
}

// Add a new edge connecting the destination of a to
// a new point in the left face of a.
Edge *Subdiv::Connect(Edge *a, const Vector &dst, const int spline) {
    const int dsti = points->AddPoint(dst);
    Edge *e = MakeEdge(a->Dst(), dsti, spline);
    Edge::Splice(e, a->Lnext());
    return e;
}

Edge *Subdiv::Connect(Edge *a, const int dsti, const int spline) {
    ASSERT(0 <= dsti && dsti < points->Num());
    Edge *e = MakeEdge(a->Dst(), dsti, spline);
    Edge::Splice(e, a->Lnext());
    return e;
}

// subdivide a at alpha, make a first half, return second half
Edge *Subdiv::Subdivide(const float alpha, Edge *e) {
    int mid;
    Bezier ebez, bez1, bez2;
    BOOL usebez;
    ASSERT(0.0 <= alpha && alpha <= 1.0 && e != nullptr);
    if (e->BezCP(0) == nullptr) {
        // e is straight line
        mid = points->AddPoint(LinInterp(alpha, Coords(e->Org()), Coords(e->Dst())));
        usebez = FALSE;
    } else {
        this->FillEdgeBezier(e, &ebez);
        ebez.Subdivide(alpha, &bez1, &bez2);
        mid = points->AddPoint(bez2.cp[0]);
        usebez = TRUE;
    }
    Edge *f = MakeEdge(mid, e->Dst(), e->Spline());
    Edge *elnextorig = e->Lnext();
    if (elnextorig == e->Sym()) {
        // dst end of e is not connect to anything else
        Edge::Splice(f, e->Lnext());
    } else {
        // first disconnect dst end of e
        Edge::Splice(e->Sym(), elnextorig);
        // connect f from dst of e to origin of elnextorig
        Edge::Splice(f, e->Lnext());
        Edge::Splice(f->Sym(), elnextorig);
    }
    e->SetDst(mid);
    if (usebez) {
        e->SetBezCP(0, bez1.cp[1]);
        e->SetBezCP(1, bez1.cp[2]);
        f->SetBezCP(0, bez2.cp[1]);
        f->SetBezCP(1, bez2.cp[2]);
    }
    return f;
}

// Keep bisecting e recursively according to signature sig
// (sig&1 is set if need to subdivide; thereafter, check
// left and right kids recursively).
// The edge e has id "kid".
void Subdiv::BisectRecursive(Edge *e, const unsigned long sig, const int kid) {
    if (isbitset(sig, kid)) {
        Edge *f = this->Subdivide(0.5F, e);
        this->BisectRecursive(e, sig, LeftKid(kid));
        this->BisectRecursive(f, sig, RightKid(kid));
    }
}

// Rotate e ccw in enclosing face (combined left-right faces)
void Subdiv::RotateInFace(Edge *e) {
    Edge *a = e->Oprev();
    Edge *b = e->Sym()->Oprev();
    Edge::Splice(e, a);
    Edge::Splice(e->Sym(), b);
    Edge::Splice(e, a->Lnext());
    Edge::Splice(e->Sym(), b->Lnext());
    e->SetOrg(a->Dst());
    e->SetDst(b->Dst());
}

// Disconnect e from subdivision, then mark
// it as "deleted".
// (Removing its QuadEdge from list of all subdivision
// edges is expensive, since the list is singly-linked.
// The SubdivEdgeIter used to iterate over edges of
// the subdivision will ignore those marked "deleted".
void Subdiv::DeleteEdge(Edge *e) const {
    // First, if e is current representative of its spline, try to
    // find a new representative (Sprev() or Snext()), or set the
    // representative to 0 to indicate "none".
    int sp = e->Spline();
    if (sp < 0)
        sp = -sp;
    if (sp != 0) {
        ASSERT(sp < this->splines.Num());
        const Edge *cure = this->splines.Get(sp);
        if (e == cure || e->Sym() == cure) {
            // e has a predecessor or successor, use that instead
            Edge *newrep = e->Sprev();
            if (newrep == nullptr)
                newrep = e->Snext();
            this->splines.Set(sp, newrep); // will be 0 if no edges for sp now
        }
    }

    Edge::Splice(e, e->Oprev());
    Edge::Splice(e->Sym(), e->Sym()->Oprev());
    ASSERT(e->Onext() == e && e->Dnext() == e
        && e->Rot()->Onext() == e->InvRot()
        && e->InvRot()->Onext() == e->Rot());

    QuadEdge *qe = e->QEdge();
    qe->SetFlag(QE_DELETED);

}

// After "after" spline edges starting at rep for spline sp,
// assign new spline id until end or wraparound.
// Return start of new spline section.
// Assume after > 1.
Edge *Subdiv::SplitSpline(int sp, const int after) {
    ASSERT(after >= 1);
    if (sp < 0)
        sp = -sp;
    Edge *e = this->splines.Get(sp);
    if (e == nullptr)
        return nullptr;
    int sofar = 0;
    int newsp = -1;
    Edge *ans = nullptr;
    Edge *f = e;
    while (f != nullptr) {
        // Get f for next iteration here, because
        // f's spline might change
        Edge *fnext = f->Snext();
        if (fnext == e)
            fnext = nullptr;
        if (sofar == after) {
            newsp = this->NewSpline();
            this->splines.GrowTo(newsp + 1);
            this->splines.Set(newsp, f);
            f->SetSpline(newsp);
            ans = f;
        } else if (sofar > after)
            f->SetSpline(newsp);
        sofar++;
        f = fnext;
    }
    return ans;
}

void Subdiv::SortPoints() const {
    if (points->IsSorted())
        return;
    const int *map = points->Sort();
    if (map == nullptr)
        return;

    for (QuadEdge *qe = qedges; qe != nullptr; qe = qe->next) {
        qe->org = map[qe->org];
        qe->dst = map[qe->dst];
    }
    delete [] map;
}

// fill bez with control polygon for e
void Subdiv::FillEdgeBezier(const Edge *e, Bezier *bez) const {
    ASSERT(e != nullptr && bez != nullptr);
    bez->cp[0] = Coords(e->Org());
    bez->cp[3] = Coords(e->Dst());
    const Vector *v1 = e->BezCP(0);
    if (v1 != nullptr) {
        bez->cp[1] = *v1;
        bez->cp[2] = *e->BezCP(1);
    } else {
        bez->cp[1] = LinInterp(OneThird, bez->cp[0], bez->cp[1]);
        bez->cp[2] = LinInterp(TwoThirds, bez->cp[0], bez->cp[1]);
    }
}

void Subdiv::FillEdgeBezier2(const Edge *e, Bezier2 *bez) const {
    ASSERT(e != nullptr && bez != nullptr);
    bez->cp[0] = Coords2(e->Org());
    bez->cp[3] = Coords2(e->Dst());
    Vector *v1 = e->BezCP(0);
    if (v1 != nullptr) {
        bez->cp[1] = *(Vector2*)v1;
        bez->cp[2] = *(Vector2*)e->BezCP(1);
    } else {
        bez->cp[1] = LinInterp(OneThird, bez->cp[0], bez->cp[1]);
        bez->cp[2] = LinInterp(TwoThirds, bez->cp[0], bez->cp[1]);
    }
}

// Return TRUE if points with indices a, b, c form
// clockwise oriented triangle (projected in xy plane)
// (Will get FALSE if colinear, within Tolerance).
// For consistency with subsequent tests, always order
// the vertices so that a <= b <= c in determinant test,
// adjusting sign as necessary.
//   | xa ya 1 |
//   | xb yb 1 | > 0
//   | xc yc 1 |
BOOL Subdiv::PointsAreCCW(int a, int b, int c) const {
    int sign = 1;
    int t;
    if (a > b) {
        t = a;
        a = b;
        b = t;
        sign = -sign;
    }
    if (a > c) {
        t = a;
        a = c;
        c = t;
        sign = -sign;
    }
    if (b > c) {
        t = b;
        b = c;
        c = t;
        sign = -sign;
    }
    ASSERT(a <= b && b <= c);
    ASSERT(a < NumPoints() && b < NumPoints() && c < NumPoints());
    const Vector2 &va = points->Coords2(a);
    const Vector2 &vb = points->Coords2(b);
    const Vector2 &vc = points->Coords2(c);
    const double xa = va.x;
    const double ya = va.y;
    const double xb = vb.x;
    const double yb = vb.y;
    const double xc = vc.x;
    const double yc = vc.y;
    const double det = xa * yb - xb * ya - xa * yc + xc * ya + xb * yc - xc * yb;
    return sign == 1 ? det > Tolerance : -det > Tolerance;
}

// Return TRUE if circle through points with indices a, b, c
// contains point with index d, (projected in xy plane),
// except that if a, b, c forms a clockwise oriented triangle
// the test is reversed: return TRUE if d is outside the circle.
// (Will get FALSE if cocircular, within Tolerance)
// For consistency with subsequent tests, always order
// the vertices so that a <= b <= c <= d in determinant test,
// adjusting sign as necessary.
//   | xa ya xa^2+ya^2 1 |
//   | xb yb xb^2+yb^2 1 | > 0
//   | xc yc xc^2+yc^2 1 |
//   | xd yd xd^2+yd^2 1 |

BOOL Subdiv::PointInCircle(const int a, const int b, const int c, const int d) const {
    int w[4];
    w[0] = a;
    w[1] = b;
    w[2] = c;
    w[3] = d;
    int i;
    int sign = 1;
    for (i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (w[i] > w[j]) {
                const int t = w[i];
                w[i] = w[j];
                w[j] = t;
                sign = -sign;
            }
        }
    }
    double x[4];
    double y[4];
    double z[4];
    for (i = 0; i < 4; ++i) {
        ASSERT(w[i] < NumPoints() && (i == 3 || w[i] <= w[i+1]));
        const Vector2 &v = points->Coords2(w[i]);
        x[i] = (double)v.x;
        y[i] = (double)v.y;
        z[i] = x[i] * x[i] + y[i] * y[i];
    }
    const double det =
        x[0] * (y[1] * z[2] - y[2] * z[1] - y[1] * z[3] + y[3] * z[1] + y[2] * z[3] - y[3] * z[2])
        - x[1] * (y[0] * z[2] - y[2] * z[0] - y[0] * z[3] + y[3] * z[0] + y[2] * z[3] - y[3] * z[2])
        + x[2] * (y[0] * z[1] - y[1] * z[0] - y[0] * z[3] + y[3] * z[0] + y[1] * z[3] - y[3] * z[1])
        - x[3] * (y[0] * z[1] - y[1] * z[0] - y[0] * z[2] + y[2] * z[0] + y[1] * z[2] - y[2] * z[1]);

    return sign == 1 ? det > Tolerance : -det > Tolerance;
}

// Return TRUE if segment ab intersects (not just touches) segment cd
// Sort so a <= b and c <= d and a <= c before comparison.
BOOL Subdiv::SegsIntersect(int a, int b, int c, int d) const {
    int t;
    if (a > b) {
        t = a;
        a = b;
        b = t;
    }
    if (c > d) {
        t = c;
        c = d;
        d = t;
    }
    if (a > c) {
        t = a;
        a = c;
        c = t;
        t = b;
        b = d;
        d = t;
    }
    ASSERT(a <= b && c <= d && a <= c);
    if (b < c || (b == c && a != d) || (a == c && b != d) || (b == d && a != c)) {
        return FALSE;
    }
    // If cd crosses ab from ab's right to its left, all following are true.
    // if cd crosses ab from ab's left to its right, all are false.
    // All are also false if segments overlap (to within tolerance of CCW test)
    const BOOL CCWacb = PointsAreCCW(a, c, b);
    const BOOL CCWabd = PointsAreCCW(a, b, d);
    const BOOL CCWcbd = PointsAreCCW(c, b, d);
    return CCWacb == CCWabd && CCWabd == CCWcbd;
}

// classification of angle in left face of e (at its org)
AngleKind Subdiv::LeftFaceAngleKind(Edge *e) const {
    const Edge *eprev = e->Lprev();
    const int a = eprev->Org();
    const int b = e->Org();
    const int c = e->Dst();
    AngleKind ans;
    if (PointsAreCCW(a, b, c))
        ans = ANG_CONVEX;
    else if (PointsAreCCW(a, c, b))
        ans = ANG_REFLEX;
    else {
        const Vector2 u = Coords2(b) - Coords2(a);
        const Vector2 v = Coords2(c) - Coords2(b);
        const float udotv = Dot(u, v);
        if (udotv > 0.F)
            ans = ANG_TANGENTIAL;
        else {
            // Really should do global analysis (walking
            // edges CW and CCW until get edges that don't
            // overlap, and then do case analysis).
            // Cheap cheat: just see if a small "random" perturbation
            // of e->Org() is inside or outside the left face
            Vector2 p = Coords2(b);
            p.x *= 1.0000457F;
            p.y -= 1.0000292F;
            if (InsideLeftFace(e, p))
                ans = ANG_360;
            else
                ans = ANG_0;
        }
    }
    return ans;
}

// Angle in left face of e (at its org), in degrees
float Subdiv::Angle(Edge *e) const {
    const AngleKind k = LeftFaceAngleKind(e);
    float ang = 0.F;
    switch (k) {
        case ANG_CONVEX:
        case ANG_REFLEX:
            ang = this->Angle(e->Lprev()->Org(), e->Org(), e->Dst());
            if (k == ANG_REFLEX)
                ang = 360.0F - ang;
            break;
        case ANG_TANGENTIAL:
            ang = 180.0F;
            break;
        case ANG_0:
            ang = 0.F;
            break;
        case ANG_360:
            ang = 360.0F;
            break;
    }
    return ang;
}

// Like previous, but a,b,c are point indices,
// and don't care about orientation, so answer is in range [0,180)
float Subdiv::Angle(const int a, const int b, const int c) const {
    const Vector2 u = Coords2(c) - Coords2(b);
    const Vector2 v = Coords2(a) - Coords2(b);
    const float norm1 = u.Norm();
    const float norm2 = v.Norm();
    double ang = 0.0;
    if (norm1 != 0.F && norm2 != 0.F) {
        double costheta = Dot(u, v) / (norm1 * norm2);
        if (costheta > 1.)
            costheta = 1.;
        else if (costheta < -1.)
            costheta = -1.;
        ang = acos(costheta) * 180.0 / hash_constants::double_pi;
    }
    return (float)ang;
}

// starting at Org, out of it
Vector Subdiv::StartTangent(const Edge *e) const {
    const Vector p0 = Coords(e->Org());
    Vector p;
    if (e->IsCubic()) {
        p = 3.0F * (*e->BezCP(0) - p0);
    } else {
        p = Coords(e->Dst()) - p0;
    }
    return p;
}

// ending at Dst, into it
Vector Subdiv::EndTangent(const Edge *e) const {
    const Vector pe = Coords(e->Dst());
    Vector p;
    if (e->IsCubic()) {
        p = 3.0F * (pe - *e->BezCP(1));
    } else {
        p = pe - Coords(e->Org());
    }
    return p;
}

// Return signed area of left face (projected onto xy plane) of e in subdivision s.
// For simple polygons, answer is positive if left face is "inside" (ccw oriented),
// and negative if left face is "outside" (cw oriented).
// For non-simple polygons, contributions of differently oriented parts are
// combined algebraically.
double Subdiv::LeftFaceArea(Edge *e) const {
    double a = 0;
    LeftFaceIter it(e);
    for (; it.Cur() != nullptr; it.GetNext()) {
        const Edge *f = it.Cur();
        const Vector2 &org = Coords2(f->Org());
        const Vector2 &dst = Coords2(f->Dst());
        a += org.x * dst.y - dst.x * org.y;
    }
    return a / 2.0;
}

// Return number of edges in left face of e.
int Subdiv::LeftFaceSize(Edge *e) {
    int ans = 0;
    LeftFaceIter it(e);
    for (; it.Cur() != nullptr; it.GetNext())
        ans++;
    return ans;
}

// Return number of edges around Oring of e
int Subdiv::Degree(Edge *e) {
    int ans = 0;
    OnextIter it(e);
    for (; it.Cur() != nullptr; it.GetNext())
        ans++;
    return ans;
}

// Return TRUE if p inside left face of e (and not equal to one of vertices)
// CF Eric Haines ptinpoly.c in Graphics Gems IV
BOOL Subdiv::InsideLeftFace(Edge *eface, const Vector2 p) const {
    Vector2 vt0 = Coords2(eface->Lprev()->Org());
    if (vt0 == p)
        return 0;

    int yflag0 = vt0.y > p.y;
    int inside_flag = 0;

    LeftFaceIter it(eface);
    for (; it.Cur() != nullptr; it.GetNext()) {
        const Edge *e = it.Cur();
        Vector2 vt1 = Coords2(e->Org());
        if (vt1 == p)
            return 0;
        const int yflag1 = vt1.y > p.y;
        if (yflag0 != yflag1) {
            const int xflag0 = vt0.x >= p.x;
            if (xflag0 == vt1.x >= p.x) {
                if (xflag0)
                    inside_flag = !inside_flag;
            } else {
                if (vt1.x - (vt1.y - p.y) * (vt0.x - vt1.x) / (vt0.y - vt1.y) >= p.x)
                    inside_flag = !inside_flag;
            }
        }
        yflag0 = yflag1;
        vt0 = vt1;
    }
    return inside_flag;
}

void Subdiv::SetAllEdgeVals(const int v) const {
    SubdivEdgeIter sit(this);
    for (; sit.Cur() != nullptr; sit.GetNext()) {
        sit.Cur()->SetVal(v);
        sit.Cur()->Sym()->SetVal(v);
    }
}

SubdivEdgeIter::SubdivEdgeIter(const Subdiv *subd) {
    qecur = subd->qedges;
    while (qecur && qecur->flags & QE_DELETED)
        qecur = qecur->next;
}

Edge *SubdivEdgeIter::Cur() const {
    if (qecur)
        return &qecur->Edges()[0];
    return nullptr;
}

void SubdivEdgeIter::GetNext() {
    if (qecur) {
        qecur = qecur->next;
        while (qecur && qecur->flags & QE_DELETED)
            qecur = qecur->next;
    }
}

SubdivSplineIter::SubdivSplineIter(const Subdiv *subd) : subdiv(subd) {
    for (; cursp < subd->splines.Num(); ++cursp) {
        Edge *e = subd->splines.Get(cursp);
        if (e != nullptr) {
            cur = e->SplineHead();
            return;
        }
    }
}


void SubdivSplineIter::GetNext() {
    cursp++;
    for (; cursp < subdiv->splines.Num(); ++cursp) {
        Edge *e = subdiv->splines.Get(cursp);
        if (e != nullptr) {
            cur = e->SplineHead();
            return;
        }
    }
    cur = nullptr;
}

void LeftFaceIter::GetNext() {
    if (cur) {
        cur = cur->Lnext();
        if (cur == start)
            cur = nullptr;
    }
}

void OnextIter::GetNext() {
    if (cur) {
        cur = cur->Onext();
        if (cur == start)
            cur = nullptr;
    }
}

void SplineIter::GetNext() {
    if (cur) {
        cur = cur->Snext();
        if (cur == start)
            cur = nullptr;
    }
}

Points::Points() {
    v = new Vector[allocv];
}

Points::~Points() {
    delete [] v;
}

int Points::AddPoint(const Vector &p) {
    ASSERT(numv <= allocv);
    const int n = numv;
    if (n == allocv) {
        const int newallocv = 2 * allocv;
        ASSERT(newallocv > n);
        auto *newv = new Vector[newallocv];
        memmove(newv, v, n * sizeof v[0]);
        delete v;
        v = newv;
        allocv = newallocv;
    }
    v[n] = p;
    numv++;
    sorted = FALSE;
    return n;
}

// class for sorting Vectors lexicographically
// and keeping track of original index
class PointSortRec {
public:
    Vector p;
    int oldindex{0};
//    PointSortRec() = default;
//    ~PointSortRec() = default;
};

static int _cdecl PSRcmp(const void *a1, const void *a2) {
    const PointSortRec *r1 = (PointSortRec*)a1;
    const PointSortRec *r2 = (PointSortRec*)a2;
    if (r1->p.x < r2->p.x)
        return -1;
    if (r1->p.x > r2->p.x)
        return 1;
    if (r1->p.y < r2->p.y)
        return -1;
    if (r1->p.y > r2->p.y)
        return 1;
    if (r1->p.z < r2->p.z)
        return -1;
    if (r1->p.z > r2->p.z)
        return 1;
    return 0;
}

int *Points::Sort() {
    if (numv == 0) {
        sorted = TRUE;
        return nullptr;
    }

    auto *psr = new PointSortRec[numv];
    int i;
    for (i = 0; i < numv; ++i) {
        psr[i].p = v[i];
        psr[i].oldindex = i;
    }
    qsort(psr, numv, sizeof(PointSortRec), PSRcmp);

    int *map = new int[numv];
    int newvindex = 0;
    for (i = 0; i < numv;) {
        const Vector pi = psr[i].p;
        v[newvindex] = pi;
        map[psr[i].oldindex] = newvindex;
        ++i;
        // remove duplicates
        while (i < numv && psr[i].p == pi) {
            map[psr[i].oldindex] = newvindex;
            i++;
        }
        newvindex++;
    }
    numv = newvindex;
    delete [] psr;
    sorted = TRUE;
    return map;
}

EdgeArray::EdgeArray(const int n) {
    edges = n > 0 ? new Edge* [n] : nullptr;
    num = n;
    allocnum = n;
}

EdgeArray::EdgeArray(const int n, const int allocn) {
    edges = allocn > 0 ? new Edge* [allocn] : nullptr;
    num = n;
    allocnum = allocn;
}

EdgeArray::EdgeArray(const EdgeArray &other) {
    if (other.num > 0) {
        edges = new Edge* [other.num];
        memcpy(edges, other.edges, other.num * sizeof(Edge*));  // NOLINT(bugprone-sizeof-expression)
    } else
        edges = nullptr;
    num = other.num;
    allocnum = other.num;
}

// Make array's "n" be at least the argument.
// If it needs to grow, allow slop for faster grow next time
void EdgeArray::GrowTo(const int n) {
    if (n > this->allocnum) {
        const int newallocn = n * 2;
        ASSERT(newallocn > 0);
        Edge **newedges = new Edge* [newallocn];
        memcpy(newedges, this->edges, this->num * sizeof(Edge*));// NOLINT(bugprone-sizeof-expression)
        for (int i = this->num; i < newallocn; ++i)
            newedges[i] = nullptr;
        delete [] this->edges;
        this->edges = newedges;
        this->allocnum = newallocn;
    }
    this->num = n;
}

EdgeArray::~EdgeArray() {
    delete [] edges;
}

void EdgeArray::Add(Edge *e) {
    if (num >= allocnum)
        GrowTo(num + 1);
    edges[num++] = e;
}

void EdgeArray::Append(const EdgeArray *earr) {
    if (earr == nullptr)
        return;
    const int oldnum = num;
    const int newnum = oldnum + earr->Num();
    GrowTo(newnum);
    for (int i = 0; i < earr->Num(); ++i)
        edges[oldnum + i] = earr->edges[i];
}

EdgeArray &EdgeArray::operator=(const EdgeArray &other) {
    if (this != &other) {
        delete [] edges;
        if (other.num > 0) {
            edges = new Edge* [other.num];
            memcpy(edges, other.edges, other.num * sizeof(Edge*));// NOLINT(bugprone-sizeof-expression)
        } else
            edges = nullptr;
        num = other.num;
        allocnum = other.num;
    }
    return *this;
}

// Use sortfun to sort edges
void EdgeArray::Sort(const EdgeSorter sortfun) const {
    if (num > 1)
        qsort(edges, num, sizeof(Edge*), (int (_cdecl *)(const void *, const void *))sortfun);// NOLINT(bugprone-sizeof-expression)
}

EdgeList::~EdgeList() {
    const EdgeListElem *el = head;
    while (el != nullptr) {
        const EdgeListElem *nextel = el->next;
        delete el;
        el = nextel;
    }
}

void EdgeList::AddHead(Edge *e) {
    auto *el = new EdgeListElem(e, head);
    head = el;
    if (tail == nullptr)
        tail = el;
    num++;
}

void EdgeList::AddTail(Edge *e) {
    auto *el = new EdgeListElem(e, nullptr);
    if (head == nullptr) {
        head = el;
        tail = el;
    } else {
        tail->next = el;
        tail = el;
    }
    num++;
}

Edge *EdgeList::RemoveHead() {
    if (head == nullptr)
        return nullptr;
    Edge *ans = head->edge;
    const EdgeListElem *oldhead = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;
    delete oldhead;
    num--;
    return ans;
}
/*
static void gtracebezier2(char *lab, const Bezier2 *b) {
    gtrace("%s: (%g,%g)(%g,%g)(%g,%g)(%g,%g)\n", lab,
           b->cp[0].x, b->cp[0].y,
           b->cp[1].x, b->cp[1].y,
           b->cp[2].x, b->cp[2].y,
           b->cp[3].x, b->cp[3].y);
}
*/
// Subdivide at parameter alpha, putting the first half in abez
// and the second half in bbez (abez and bbez should point to allocated Bezier's)
void Bezier::Subdivide(const float alpha, Bezier *abez, Bezier *bbez) const {
    Vector b[4][4];
    int i;
    for (i = 0; i <= 3; ++i)
        b[0][i] = cp[i];

    const float alpha2 = 1.F - alpha;
    for (int r = 1; r <= 3; ++r) {
        const int ilim = 3 - r;
        for (i = 0; i <= ilim; ++i)
            b[r][i] = alpha2 * b[r - 1][i] + alpha * b[r - 1][i + 1];
    }
    for (i = 0; i <= 3; ++i) {
        abez->cp[i] = b[i][0];
        bbez->cp[i] = b[3 - i][i];
    }
}

// Subdivide at parameter alpha, putting the first half in abez
// and the second half in bbez (abez and bbez should point to allocated Bezier2's)
void Bezier2::Subdivide(const float alpha, Bezier2 *abez, Bezier2 *bbez) const {
    Vector2 b[4][4];
    int i;
    for (i = 0; i <= 3; ++i) {
        b[0][i] = cp[i];
    }

    const float alpha2 = 1.F - alpha;
    for (int r = 1; r <= 3; ++r) {
        const int ilim = 3 - r;
        for (i = 0; i <= ilim; ++i) {
            b[r][i] = alpha2 * b[r - 1][i] + alpha * b[r - 1][i + 1];
        }
    }
    for (i = 0; i <= 3; ++i) {
        abez->cp[i] = b[i][0];
        bbez->cp[i] = b[3 - i][i];
    }
}

// Set *pmin and *pmax so that they are the min and max corners
// of the bounding box of this Bezier2
void Bezier2::BB(Vector2 *pmin, Vector2 *pmax) const {
    *pmin = cp[0];
    *pmax = cp[0];
    for (int i = 1; i < 4; ++i) {
        if (cp[i].x < pmin->x)
            pmin->x = cp[i].x;
        else if (cp[i].x > pmax->x)
            pmax->x = cp[i].x;
        if (cp[i].y < pmin->y)
            pmin->y = cp[i].y;
        else if (cp[i].y > pmax->y)
            pmax->y = cp[i].y;
    }
}

// Return TRUE if the bounding box of the bezier intersects (not just touches)
// the bounding box of bbez.
BOOL Bezier2::IntersectsBB(const Bezier2 *bbez) const {
    const Bezier2 *abez = this;
    Vector2 amin, amax, bmin, bmax;
    abez->BB(&amin, &amax);
    bbez->BB(&bmin, &bmax);
    if (amin.x > bmax.x || amin.y > bmax.y || bmin.x > amax.x || bmin.y > amax.y) {
        return FALSE;
    }
    return TRUE;
}

// Return subdivision recursion depth needed to guarantee that the line
// segment approximation to the Bezier2 at that depth differs from the
// curve by at most epsilon.
// Wang's theorem says: compute three vectors between the cps, then
// differences between adjacent vectors. let L be length of longest difference.
// Needed depth is ceil(log_base_4 (3*sqrt(2)*L/(4*epsilon))).
// We use code from Klassen (Graphics Gems 4).
int Bezier2::FlatDepth(const double epsilon) const {
    ASSERT(epsilon > 0.0);
    const Vector2 a1 = (cp[2] - cp[1] - (cp[1] - cp[0])).Absolute();
    const Vector2 a2 = (cp[3] - cp[2] - (cp[2] - cp[1])).Absolute();
    Vector2 a;
    a.x = a1.x > a2.x ? a1.x : a2.x;
    a.y = a1.y > a2.y ? a1.y : a2.y;
    const double L = a.x > a.y ? a.x : a.y;
    int r;
    if (L * 0.75 * Sqrt2 + 1.0 == 1.0)
        r = 0;
    else
        r = (int)hash_math::ceil(hash_math::log(Sqrt2 * 3.0 * L / (4.0 * epsilon)) / Log4);
    return r;
}

static BOOL RecurInter(const Bezier2 *abez, const Bezier2 *bbez,
                       unsigned long &asig, unsigned long &bsig,
                       const int anode, const int bnode,
                       int adepth, int bdepth) {
    Bezier2 abezl, abezr, bbezl, bbezr;
    BOOL ans = FALSE;
    if (adepth > 0) {
        abez->Subdivide(0.5F, &abezl, &abezr);
        setbit(asig, anode);
        adepth--;
        if (bdepth > 0) {
            bbez->Subdivide(0.5F, &bbezl, &bbezr);
            setbit(bsig, bnode);
            bdepth--;
            if (abezl.IntersectsBB(&bbezl))
                ans |= RecurInter(&abezl, &bbezl, asig, bsig,
                                  LeftKid(anode), LeftKid(bnode), adepth, bdepth);
            if (abezr.IntersectsBB(&bbezl))
                ans |= RecurInter(&abezr, &bbezl, asig, bsig,
                                  RightKid(anode), LeftKid(bnode), adepth, bdepth);
            if (abezl.IntersectsBB(&bbezr))
                ans |= RecurInter(&abezl, &bbezr, asig, bsig,
                                  LeftKid(anode), RightKid(bnode), adepth, bdepth);
            if (abezr.IntersectsBB(&bbezr))
                ans |= RecurInter(&abezr, &bbezr, asig, bsig,
                                  RightKid(anode), RightKid(bnode), adepth, bdepth);
        } else {
            if (abezl.IntersectsBB(bbez))
                ans |= RecurInter(&abezl, bbez, asig, bsig,
                                  LeftKid(anode), bnode, adepth, bdepth);
            if (abezr.IntersectsBB(bbez))
                ans |= RecurInter(&abezr, bbez, asig, bsig,
                                  RightKid(anode), bnode, adepth, bdepth);
        }
    } else if (bdepth > 0) {
        bbez->Subdivide(0.5F, &bbezl, &bbezr);
        setbit(bsig, bnode);
        bdepth--;
        if (abez->IntersectsBB(&bbezl))
            ans |= RecurInter(abez, &bbezl, asig, bsig,
                              anode, LeftKid(bnode), adepth, bdepth);
        if (abez->IntersectsBB(&bbezr))
            ans |= RecurInter(abez, &bbezr, asig, bsig,
                              anode, RightKid(bnode), adepth, bdepth);
    } else {
        const double xlk = abez->cp[3].x - abez->cp[0].x;
        const double ylk = abez->cp[3].y - abez->cp[0].y;
        const double xnm = bbez->cp[3].x - bbez->cp[0].x;
        const double ynm = bbez->cp[3].y - bbez->cp[0].y;
        const double xmk = bbez->cp[0].x - abez->cp[0].x;
        const double ymk = bbez->cp[0].y - abez->cp[0].y;
        const double det = xnm * ylk - ynm * xlk;
        if (1.0 + det != 1.0) {
            const double detinv = 1.0 / det;
            const double s = (xnm * ymk - ynm * xmk) * detinv;
            const double t = (xlk * ymk - ylk * xmk) * detinv;
            if (s >= 0.0 && s <= 1.0 && (t >= 0.0 && t <= 1.0)) {
                // intersection at t-of-the-way along abez
                // with s-of-the-way along bbez
                ans = TRUE;
            }
        }

    }
    return ans;
}

// Return TRUE if abez (== this) intersects bbez, FALSE if it doesn't (within tolerance).
// Also, set the "signature" parameters to reflect the subdivision that happened
// to prove or disprove intersection: in a signature, let each child of the subdivision
// tree be indexed according to a heap representation of the tree: the children of node i
// are at 2i+1 and 2i+2.  The signatures have bit i set if there was a subdivision
// at the corresponding node.
BOOL Bezier2::Intersects(const Bezier2 *bbez, unsigned long &asig, unsigned long &bsig) const {
    const Bezier2 *abez = this;
    asig = 0;
    bsig = 0;
    if (!abez->IntersectsBB(bbez))
        return FALSE;
    int ra = abez->FlatDepth(Tolerance);
    int rb = bbez->FlatDepth(Tolerance);
    // for signature scheme to work (and fit in unsigned long),
    // need to recur just 4 levels, at most
    if (ra > 4)
        ra = 4;
    if (rb > 4)
        rb = 4;
    return RecurInter(abez, bbez, asig, bsig, 0, 0, ra, rb);
}

// Like Intersects, but intersect with straight line segment from org to dst.
BOOL Bezier2::Intersects(const Vector2 *org, const Vector2 *dst, unsigned long &asig) const {
    const Bezier2 *abez = this;
    asig = 0;
    unsigned long bsig;
    Bezier2 bbez;
    bbez.cp[0] = *org;
    bbez.cp[1] = LinInterp(OneThird, *org, *dst);
    bbez.cp[2] = LinInterp(TwoThirds, *org, *dst);
    bbez.cp[3] = *dst;
    if (!abez->IntersectsBB(&bbez))
        return FALSE;
    int ra = abez->FlatDepth(Tolerance);
    if (ra > 4)
        ra = 4;
    return RecurInter(abez, &bbez, asig, bsig, 0, 0, ra, 0);
}

// For debugging
#ifdef _DEBUG
int gdebug = 3;
#else
int gdebug = 0;
#endif

void gtrace(const char *fmt, ...) {
    if (!gdebug)
        return;
    static FILE *dbgf = nullptr;
    va_list ap;
    va_start(ap, fmt);
    char msg[1024];
    vsprintf_s(msg, 1024, fmt, ap);
    va_end(ap);
    if (gdebug & 1)
#ifdef _DEBUG
        ::OutputDebugString(msg);
#else
        TRACE(msg);
#endif
    if (gdebug & 2) {
        if (dbgf == nullptr)
            fopen_s(&dbgf, "D:\\temp\\gtraceout.txt", "w");
        if (dbgf != nullptr) {
            fprintf(dbgf, "%s", (const char*)msg);
            fflush(dbgf);
        }
    }
}

void gtraceLeftFace(const char *lab, Edge *e) {
    gtrace("%s: ", lab);
    if (e == nullptr) {
        gtrace("(empty)\n");
        return;
    }
    LeftFaceIter it(e);
    int i = 0;
    for (; it.Cur() != nullptr; it.GetNext()) {
        gtrace("%d ", it.Cur()->Org());
        if (++i == 20) {
            gtrace("\n");
            i = 0;
        }
    }
    gtrace("\n");
}
