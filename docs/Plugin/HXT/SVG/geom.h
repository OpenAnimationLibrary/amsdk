// include vector.h and vector2.h before this
#pragma once

class QuadEdge;
class Edge;
class Subdiv;
class Points;
class Bezier;
class Bezier2;

// Classification of polygon angles
enum AngleKind {
    ANG_CONVEX,
    // angle > 0, < 180
    ANG_REFLEX,
    // angle > 180, < 360
    ANG_TANGENTIAL,
    // angle == 180 (approx)
    ANG_0,
    // angle == 0 (approx) (extreme of convex)
    ANG_360 // angle == 360 (approx) (extreme of reflex)
};

// Flags for use in QuadEdge flags
enum QEFlag {
    QE_DELETED    = 1,
    QE_BOUNDARY   = 2,
    QE_CUT_CORNER = 4
};

// Some additional vector operations

// Linear interpolation: (1-alpha)*a + alpha*b
Vector LinInterp(float alpha, const Vector &a, const Vector &b);
Vector2 LinInterp(float alpha, const Vector2 &a, const Vector2 &b);

Vector Rot90CCW(const Vector &a);
Vector2 Rot90CCW(const Vector2 &a);
Vector Rot90CW(const Vector &a);
Vector2 Rot90CW(const Vector2 &a);

float Angle(const Vector &a, const Vector &b);

class Edge {
    int num{0}; // index of this in containing QuadEdge
    int val{0}; // for user use
    float fval{0}; // also for user use
    Edge *next{nullptr}; // Onext pointer

public:
    Edge() = default;
    Edge *Rot(); // crosses this edge from right to left
    Edge *InvRot(); // crosses this edge from left to right
    Edge *Sym(); // its origin is this edge's dest, & vice versa
    [[nodiscard]] Edge *Onext() const; // next ccw around origin ring
    Edge *Oprev(); // next cw around origin ring
    Edge *Dnext(); // next ccw (into) around destination ring
    Edge *Dprev(); // next cw around destination ring
    Edge *Lnext(); // next ccw around left face (if this is an "edge" edge)
    [[nodiscard]] Edge *Lprev() const; // next cw around left face (if this is an "edge" edge)
    Edge *Rnext(); // next ccw around right face (if this is an "edge" edge)
    Edge *Rprev(); // next cw around right face (if this is an "edge" edge)

    Edge *Snext(); // next edge in spline chain (or 0, at end of unlooped chain)
    Edge *Sprev(); // prev edge in spline chain (or 0)

    // The Org and Dst are indices into points (of containing subdivision)
    // of the beginning and end of this directed edge.
    // They are only defined if num==0 or num==2 (i.e., not for the dual face-to-face edges).
    // The BezCPs are also only defined for num==0 or num==2, and give the
    // intermediate cubic bezier control points (if IsCubic() is defined) from org->dst.
    // The Spline is an id number that lets the user keep track of a chain of Edges.
    // It is > 0 if directed the same as the Edge, else < 0 (and 0 means unused).
    // The values are kept in the containing QuadEdge.
    void SetOrg(int org) const;
    void SetDst(int dst) const;
    void SetSpline(int spline) const;

    void SetVal(const int v) {
        val = v;
    }

    void SetFval(const float f) {
        fval = f;
    }

    void SetBezCP(int cpnum, const Vector &v) const;

    [[nodiscard]] QuadEdge *QEdge() const; // containing QuadEdge

    [[nodiscard]] int Org() const;
    [[nodiscard]] int Dst() const;
    [[nodiscard]] int Spline() const;
    [[nodiscard]] BOOL SplineIsForward() const;
    Edge *SplineHead();
    BOOL SplineIsLooped();
    [[nodiscard]] Vector *BezCP(int cpnum) const;

    [[nodiscard]] int Val() const {
        return val;
    }

    [[nodiscard]] float Fval() const {
        return fval;
    }

    [[nodiscard]] BOOL IsCubic() const;

    static void Splice(Edge *, Edge *);

    Edge(const Edge &) = delete; // not implemented
    Edge &operator=(const Edge &) = delete; // not implemented

    friend class QuadEdge;
};

class QuadEdge {
    Edge edges[4]{};
    QuadEdge *next{nullptr}; // in list of all QuadEdges of a subdivision
    int org{0}; // index into subdivision's points of edge[0] origin
    int dst{0}; // index into subdivision's points of edge[0] destination
    // (reverse them for edge[2])
    int spline{0}; // id number for spline (chain of Edges) that edge[0] is
    // part of (positive if directed same as edge[0], negative
    // if directed opposite).
    Vector *bezcps{nullptr}; // if nonzero, then the edge is bezier cubic and
    // this points to array of two cps between org and dst
    unsigned long flags{0}; // for user use
    friend class SubdivEdgeIter;

public:
    QuadEdge();
    ~QuadEdge();

    Edge *Edges() {
        return edges;
    }

    [[nodiscard]] BOOL IsCubic() const {
        return bezcps != nullptr;
    }

    void SetBezCP(int cpnum, const Vector &v); // cpnum should be 0 or 1; allocates bezcps if nec
    [[nodiscard]] Vector *BezCP(int cpnum) const; // nonzero only if a cp has been set
    void SetFlag(const unsigned long f) {
        flags |= f;
    }

    void ClearFlag(const unsigned long f) {
        flags &= ~f;
    }

    [[nodiscard]] BOOL FlagIsSet(const unsigned long f) const {
        return (flags & f) != 0;
    }

    [[nodiscard]] unsigned long Flags() const {
        return flags;
    }

    friend class Subdiv;
    friend class Edge;
};

// Iterate over edges (one representative per QuadEdge)
class SubdivEdgeIter {
    QuadEdge *qecur{nullptr};

public:
    SubdivEdgeIter(const Subdiv *subd);
    [[nodiscard]] Edge *Cur() const;
    void GetNext();
};

// Iterate ccw over edges of left face
class LeftFaceIter {
    Edge *start;
    Edge *cur;

public:
    LeftFaceIter(Edge *estart) : start{estart}, cur{estart} {}

    [[nodiscard]] Edge *Cur() const {
        return cur;
    }

    void GetNext();
};

// Iterate ccw over edges around origin ring
class OnextIter {
    Edge *start;
    Edge *cur;

public:
    OnextIter(Edge *estart) : start{estart}, cur{estart} {}

    [[nodiscard]] Edge *Cur() const {
        return cur;
    }

    void GetNext();
};

// Iterate over edges with same spline id,
// either until reach starting edge again
// or until there is no continuation Edge
// with same id (should be at most one such
// continuation edge).
class SplineIter {
    Edge *start;
    Edge *cur;

public:
    SplineIter(Edge *estart) : start{estart}, cur{estart} {}

    [[nodiscard]] Edge *Cur() const {
        return cur;
    }

    void GetNext();
};

// Iterate over all splines of subdiv
// (just head spline for each)
class SubdivSplineIter {
    int cursp{0};
    const Subdiv *subdiv{nullptr};
    Edge *cur{nullptr};

public:
    SubdivSplineIter(const Subdiv *subd);
    ~SubdivSplineIter() = default;

    [[nodiscard]] Edge *Cur() const {
        return cur;
    }

    void GetNext();
};

class Points {
    Vector *v{nullptr}; // array of points
    int numv{0}; // number of valid entries in v
    int allocv{25}; // current allocated size of v
    BOOL sorted{TRUE}; // true when v is sorted

public:
    Points();
    ~Points();

    // add v to set of points, return its index
    int AddPoint(const Vector &p);

    // sort points ascending lexicographically on (x,y,z), eliminate duplicates,
    // return allocated array of length (original) Num() mapping old indices to new.
    int *Sort();

    [[nodiscard]] int Num() const {
        return numv;
    }

    [[nodiscard]] const Vector &Coords(const int i) const {
        return v[i];
    }

    [[nodiscard]] const Vector2 &Coords2(const int i) const {
        return (const Vector2 &)v[i];
    }

    void ChangeCoords(const int i, const Vector &val) {
        v[i] = val;
        sorted = FALSE;
    }

    [[nodiscard]] BOOL IsSorted() const {
        return sorted;
    }
};

// Array of edge pointers, with bundled length
class EdgeArray {
    Edge **edges{nullptr}; // array of Edge pointers stored here
    int num{0};
    int allocnum{0}; // can be greater than num

public:
    typedef int (*EdgeSorter)(const Edge **, const Edge **);

    EdgeArray(int n);
    EdgeArray(int n, int allocn);
    EdgeArray(const EdgeArray &other);
    ~EdgeArray();

    void Set(const int i, Edge *e) const {
        edges[i] = e;
    }

    void Add(Edge *e);
    void GrowTo(int n);
    void Append(const EdgeArray *earr);

    [[nodiscard]] Edge *Get(const int i) const {
        return edges[i];
    }

    EdgeArray &operator=(const EdgeArray &other);

    [[nodiscard]] int Num() const {
        return num;
    }

    void Sort(EdgeSorter sortfun) const;
};

// List of edge pointers
class EdgeList;

class EdgeListElem {
    EdgeListElem *next;
    Edge *edge;

    EdgeListElem(Edge *e, EdgeListElem *tail) : next(tail), edge(e) { }
    ~EdgeListElem() = default;
    friend class EdgeList;
};

class EdgeList {
    EdgeListElem *head{nullptr};
    EdgeListElem *tail{nullptr};
    int num{0};

public:
    EdgeList() = default;
    ~EdgeList();

    [[nodiscard]] Edge *Head() const {
        return head ? head->edge : nullptr;
    }

    [[nodiscard]] Edge *Tail() const {
        return tail ? tail->edge : nullptr;
    }

    void AddHead(Edge *e);
    void AddTail(Edge *e);
    Edge *RemoveHead();

    [[nodiscard]] int Num() const {
        return num;
    }
};

class Bezier {
public:
    Vector cp[4];
    void Subdivide(float alpha, Bezier *abez, Bezier *bbez) const;
};

class Bezier2 {
public:
    Vector2 cp[4];

    void BB(Vector2 *pmin, Vector2 *pmax) const;
    void Subdivide(float alpha, Bezier2 *abez, Bezier2 *bbez) const;
    BOOL IntersectsBB(const Bezier2 *bbez) const;
    BOOL Intersects(const Bezier2 *bbez, unsigned long &asig, unsigned long &bsig) const;
    BOOL Intersects(const Vector2 *org, const Vector2 *dst, unsigned long &asig) const;
    [[nodiscard]] int FlatDepth(double epsilon) const;
};

class Subdiv {
    QuadEdge *qedges{nullptr}; // all QuadEdges in subdivision (linked through next)
    Points *points{nullptr}; // vertex coords stored here
    EdgeArray splines; // points to spline head edges
    // indexed by spline id
    // spline id 0 is unused (can't negate)

    friend class SubdivEdgeIter;
    friend class SubdivSplineIter;

public:
    Subdiv();
    ~Subdiv();

    static Edge *MakeEdge();
    Edge *MakeEdge(const Vector &org, const Vector &dst, int spline);
    Edge *MakeEdge(int orgi, int dsti, int spline);
    Edge *Connect(Edge *a, const Vector &dst, int spline);
    Edge *Connect(Edge *a, int dsti, int spline);
    Edge *Connect(Edge *a, Edge *b, int spline);
    Edge *Subdivide(float alpha, Edge *e); // subdivide e at alpha, make a first half, return second half
    void BisectRecursive(Edge *e, unsigned long sig, int kid = 0);
    static void RotateInFace(Edge *e);
    void DeleteEdge(Edge *e) const;
    void SortPoints() const; // sorts points, remaps orgs and dsts in edges
    [[nodiscard]] BOOL IsEmpty() const {
        return qedges == nullptr;
    }

    [[nodiscard]] const Vector &Coords(const int i) const {
        return points->Coords(i);
    }

    [[nodiscard]] const Vector2 &Coords2(const int i) const {
        return points->Coords2(i);
    }

    void ChangeCoords(const int i, const Vector &v) const {
        points->ChangeCoords(i, v);
    }

    void FillEdgeBezier(const Edge *e, Bezier *bez) const; // fill bez with control polygon for e
    void FillEdgeBezier2(const Edge *e, Bezier2 *bez) const; // fill bez with control polygon for e
    [[nodiscard]] int NumPoints() const {
        return points->Num();
    }

    [[nodiscard]] BOOL PointsAreCCW(int a, int b, int c) const; // points a,b,c form CCW triangle
    [[nodiscard]] BOOL PointInCircle(int a, int b, int c, int d) const; // CCW circle through a,b,c contains d
    [[nodiscard]] BOOL SegsIntersect(int a, int b, int c, int d) const; // ab intersects cd
    AngleKind LeftFaceAngleKind(Edge *e) const; // classification of angle in left face of e (at its org)
    float Angle(Edge *e) const; // angle in left face of e (at its org), in degrees
    [[nodiscard]] float Angle(int a, int b, int c) const; // angle abc in range [0,180)
    Vector StartTangent(const Edge *e) const; // starting at e->Org, out of it
    Vector EndTangent(const Edge *e) const; // ending at e->Dst, into it
    static int Degree(Edge *e); // number of edges in Onext() ring around e
    BOOL InsideLeftFace(Edge *eface, Vector2 p) const; // TRUE if p inside (not one of vertices) of left face of e
    static int LeftFaceSize(Edge *e); // number of edges in left face of e
    double LeftFaceArea(Edge *e) const; // signed area of left face of e (+ve if CCW)
    void SetAllEdgeVals(int v) const;
    [[nodiscard]] int NewSpline() const; // return an unused spline id
    Edge *SplitSpline(int sp, int after); // after "after" spline edges starting at rep for spline sp,
    // assign new spline id until end or wraparound
};

// For debugging
extern int gdebug;
void gtrace(const char *fmt, ...);
void gtraceLeftFace(const char *lab, Edge *e);
