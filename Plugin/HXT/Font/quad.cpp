#include "StdAfx.h"
#include "Vector.h"
#include "Vector2.h"
#include "geom.h"
#include "poly.h"
#include "tri.h"
#include "quad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

static void SetAllFaceValsAndFvals(const Subdiv *s, int v, float fv);
static EdgeArray *EdgeRemovalGraph(const Subdiv *s, int numtri);
static EdgeArray *GreedyMatch(const EdgeArray *er, int numtri);
static EdgeArray *MaxMatch(EdgeArray *er, int numtri);
static EdgeArray *DCMatch(EdgeArray *er, int numtri, float *pmatchweight);
static EdgeArray *EMatch(const EdgeArray *er, int numtri, float *pmatchweight);
static void PartitionComps(const EdgeArray *er, const int *comp, int excepti, EdgeArray **pa_edges, EdgeArray **pb_edges, int compa, int compb);
static EdgeArray *CopyExcluding(const EdgeArray *er, int v0, int v1);
static int FindComponents(EdgeArray *er, int excepti, int *comp, int numtri);

// Weighting factors for multiplying max angle (in degrees)
// of quadrilateral formed by removing and edge,
// and sum of degrees of start and end vertices of the edge.
constexpr float angle_weight_factor = 1.0F;
constexpr float degree_weight_factor = 10.0F;

// Number of edges at or below which use EMatch exclusively.
constexpr int e_threshold = 2;

// Number of edges at or above which to use GreedyMatch
constexpr int g_threshold = 75;

void Quadrify(Subdiv *s) {
    if (s->NumPoints() < 4)
        return;
    const PolygonalAreaArray *areas = FindPolygonalAreas(s);
    for (int i = 0; i < areas->Num(); ++i) {
        QuadrifyArea(s, areas->Get(i));
        delete areas->Get(i);
    }
    delete areas;
}

void QuadrifyArea(Subdiv *s, const PolygonalArea *a) {
    gtrace("QuadrifyArea\n");
    // Set all face vals to -1, so can distinguish
    // faces of triangulated area from rest of subdivision.
    SetAllFaceValsAndFvals(s, -1, 0.0F);
    const int numtri = TriangulateArea(s, a);
    EdgeArray *er = EdgeRemovalGraph(s, numtri);
    if (er->Num() == 0)
        return;

    EdgeArray *match;
    if (er->Num() > g_threshold)
        match = GreedyMatch(er, numtri);
    else
        match = MaxMatch(er, numtri);

    // Convert face edges to their crossing edges (the ones to remove),
    // as face edges might change during deletion loop.
    const EdgeArray *deledges = new EdgeArray(match->Num());
    for (int i = 0; i < match->Num(); ++i)
        deledges->Set(i, match->Get(i)->Rot());

    // Now remove edges crossing those in match
    for (int i = 0; i < deledges->Num(); ++i) {
        Edge *e = deledges->Get(i);
        const int t1 = e->Rot()->Val();
        gtrace("Delete edge (%d,%d)\n", e->Org(), e->Dst());
        Edge *elnext = e->Lnext();
        s->DeleteEdge(e);
        SetLeftFaceVal(elnext, t1);
    }
    delete er;
    delete match;
    delete deledges;
}

void QuadrifyAreas(Subdiv *s, const PolygonalAreaArray *areas) {
    for (int i = 0; i < areas->Num(); ++i)
        QuadrifyArea(s, areas->Get(i));
}

// Find face edges in s such that:
//	- edge goes between two non-negative faces, with orgin Val < dest Val
//    (non-negative face Vals should be in range [0,numtri-1])
//  - removing edge that crosses the face edge yields a convex quadrilateral
// Assign each such edge a weight (in its Fval()), with higher weights meaning
// it is more desirable to remove the edge.
// The current edge weight scheme favors removing edges with high
// degree, and edges whose newly created internal angles are large.
static EdgeArray *EdgeRemovalGraph(const Subdiv *s, const int numtri) {
    gtrace("EdgeRemovalGraph\n");
    EdgeList erlist;
    SubdivEdgeIter sit(s);
    for (; sit.Cur() != nullptr; sit.GetNext()) {
        Edge *e = sit.Cur();
        Edge *f = e->Rot();
        Edge *ff = f->Sym();
        if (f->Val() < 0 || ff->Val() < 0)
            continue;
        ASSERT(f->Val() < numtri && ff->Val() < numtri);
        if (f->Val() > ff->Val())
            f = ff;
        Edge *esym = e->Sym();
        Edge *elnext = e->Lnext();
        Edge *esymlnext = esym->Lnext();
        if (elnext->Lnext()->Lnext() != e || esymlnext->Lnext()->Lnext() != esym) {
            gtrace("Face edge is not between two triangles!\n");
            continue;
        }
        // find angmax, the maximum of the two angles formed inside
        // the quadrilateral if edge e were removed.
        float a1 = s->Angle(e) + s->Angle(esymlnext);
        float a2 = s->Angle(esym) + s->Angle(elnext);
        const float angmax = a1 > a2 ? a1 : a2;
        gtrace("  edge (%d,%d) removal -> angmax = %f\n", e->Org(), e->Dst(), angmax);
        if (angmax > 180.0F)
            continue;
        const int degree = Subdiv::Degree(e) + Subdiv::Degree(esym);
        //gtrace("    degree = %d\n", degree);
        const float weight = (180.0F - angmax) * angle_weight_factor + degree * degree_weight_factor;
        //gtrace("    weight = %f\n", weight);
        f->SetFval(weight);
        f->Sym()->SetFval(weight);
        erlist.AddTail(f);
    }
    const int n = erlist.Num();
    auto *ans = new EdgeArray(n);
    int i = 0;
    while (erlist.Num() > 0) {
        Edge *f = erlist.RemoveHead();
        ans->Set(i, f);
        i++;
    }
    ASSERT(i == n);
    return ans;
}

static int FvalDecreasingCmp(const Edge **pa, const Edge **pb) {
    const float fa = (*pa)->Fval();
    const float fb = (*pb)->Fval();
    if (fa > fb)
        return -1;
    if (fa < fb)
        return 1;
    return 0;
}

// Return allocated EdgeArray of elements of er
// that form a maximal matching, using simply greedy method.
// numtri is number of triangles (so vertices are in range [0..nt-1])
static EdgeArray *GreedyMatch(const EdgeArray *er, const int numtri) {
    gtrace("GreedyMatch\n");
    // sort by decreasing weight
    er->Sort(FvalDecreasingCmp);
    // take edges in order unless involve already matched triangle
    BOOL *matched = new BOOL[numtri];
    auto *ans = new EdgeArray(0, er->Num()); // overestimate size
    for (int i = 0; i < numtri; ++i)
        matched[i] = 0;
    for (int i = 0; i < er->Num(); ++i) {
        Edge *f = er->Get(i);
        const int t1 = f->Val();
        const int t2 = f->Sym()->Val();
        if (!matched[t1] && !matched[t2]) {
            gtrace("Edge between faces %d and %d added to match\n", t1, t2);
            ans->Add(f);
            matched[t1] = 1;
            matched[t2] = 1;
        }
    }
    delete [] matched;
    return ans;
}

// Return allocated EdgeArray of elements of er
// that form a mzximum matching.
// numtri is number of triangles (so vertices are in range [0..nt-1])
static EdgeArray *MaxMatch(EdgeArray *er, const int numtri) {
    float answ;
    EdgeArray *ans = DCMatch(er, numtri, &answ);
#ifdef _DEBUG
    if (gdebug) {
        gtrace("Maximum match weight=%f\n", answ);
        for (int i = 0; i < ans->Num(); ++i) {
            Edge *f = ans->Get(i);
            gtrace("Edge between faces %d and %d\n", f->Val(), f->Sym()->Val());
        }
    }
#endif
    return ans;
}

// Find elements of er that form a maximum matching of elements of er.
// Return those elements, and put the corresponding sum of weights in *pmatchweight.
// Uses a divide and conquer method: try to find an edge that separates the
// er graph into two separate components.  If that fails, or size is small,
// use the exhaustive EMatch routine.
// numtri is number of triangles (so vertices are in range [0..nt-1]).
static EdgeArray *DCMatch(EdgeArray *er, const int numtri, float *pmatchweight) {
    const int ne = er->Num();

    if (ne == 0) {
        *pmatchweight = 0.0F;
        return new EdgeArray(0);
    }

    if (ne < e_threshold) {
        return EMatch(er, numtri, pmatchweight);
    }

    float answ;
    EdgeArray *match = nullptr;
    float wa, wb, wax, wbx;
    EdgeArray *a_edges;
    EdgeArray *b_edges;
    int *comp = new int[numtri];
    for (int i = 0; i < numtri; ++i)
        comp[i] = 0;
    for (int i = 0; i < ne && match == nullptr; ++i) {
        const int nc = FindComponents(er, i, comp, numtri);
        if (nc == 1)
            continue;

        Edge *f = er->Get(i);

        // We have a separation into separate components
        // Two cases:
        //   1) ends of f are in separate components
        //   2) ends of f are in same component
        const int v0 = f->Val();
        const int v1 = f->Sym()->Val();
        if (comp[v0] != comp[v1]) {
            // case 1: f is needed to separate graph
            PartitionComps(er, comp, i, &a_edges, &b_edges, comp[v0], comp[v1]);
            EdgeArray *ax_edges = CopyExcluding(a_edges, v0, v1);
            EdgeArray *bx_edges = CopyExcluding(b_edges, v0, v1);
            EdgeArray *ax_match = DCMatch(ax_edges, numtri, &wax);
            EdgeArray *bx_match = DCMatch(bx_edges, numtri, &wbx);
            EdgeArray *a_match;
            EdgeArray *b_match;
            if (ax_edges->Num() == a_edges->Num()) {
                wa = wax;
                a_match = ax_match;
            } else
                a_match = DCMatch(a_edges, numtri, &wa);
            if (bx_edges->Num() == b_edges->Num()) {
                wb = wbx;
                b_match = bx_match;
            } else
                b_match = DCMatch(b_edges, numtri, &wb);
            const float w = wa + wb;
            const float wx = wax + wbx + f->Fval();
            if (w > wx) {
                match = new EdgeArray(0, a_match->Num() + b_match->Num());
                match->Append(a_match);
                match->Append(b_match);
                answ = w;
            } else {
                match = new EdgeArray(0, a_match->Num() + b_match->Num() + 1);
                match->Add(f);
                match->Append(ax_match);
                match->Append(bx_match);
                answ = wx;
            }
            if (a_match != ax_match)
                delete a_match;
            delete ax_match;
            if (b_match != bx_match)
                delete b_match;
            delete bx_match;
            delete ax_edges;
            delete bx_edges;
        } else {
            // case 2: f is not needed to separate graph
            PartitionComps(er, comp, -1, &a_edges, &b_edges, 0, 0);
            const EdgeArray *a_match = DCMatch(a_edges, numtri, &wa);
            const EdgeArray *b_match = DCMatch(b_edges, numtri, &wb);
            match = new EdgeArray(0, a_match->Num() + b_match->Num());
            match->Append(a_match);
            match->Append(b_match);
            answ = wa + wb;
            delete a_match;
            delete b_match;
        }
        delete a_edges;
        delete b_edges;
    }
    if (match == nullptr)
        match = EMatch(er, numtri, &answ);
    delete [] comp;
    *pmatchweight = answ;
    return match;
}

// Does same thing as DCMatch, but exhaustively:
// Tries DCmatch on both cases of (a) first edge included
// and (b) first edge excluded.
static EdgeArray *EMatch(const EdgeArray *er, const int numtri, float *pmatchweight) {
    const int ne = er->Num();

    if (ne == 0) {
        *pmatchweight = 0.0F;
        return new EdgeArray(0);
    }

    EdgeArray *match;
    float answ, wa, wb;
    Edge *f0 = er->Get(0);
    if (ne == 1) {
        match = new EdgeArray(1);
        match->Set(0, f0);
        *pmatchweight = f0->Fval();
        return match;
    }

    const int v0 = f0->Val();
    const int v1 = f0->Sym()->Val();

    // case a. include f0.  exlude other edges that touch v0 or v1
    EdgeArray *a_edges = CopyExcluding(er, v0, v1);
    a_edges->Add(f0); // there is room, because f was excluded
    const EdgeArray *a_match = DCMatch(a_edges, numtri, &wa);
    wa += f0->Fval();

    // if a_edges has size ne-1, then f0 was disconnected from
    // rest of graph,  and the best match will always be the one
    // that takes f0, so skip call for case b
    EdgeArray *b_match = nullptr;
    EdgeArray *b_edges = nullptr;
    if (a_edges->Num() == ne - 1)
        wb = -1.0F;
    else {
        // case b. exclude f0.  include all other edges.
        b_edges = new EdgeArray(ne - 1);
        for (int i = 1; i < ne; ++i)
            b_edges->Set(i - 1, er->Get(i));
        b_match = DCMatch(b_edges, numtri, &wb);
    }

    if (wa >= wb) {
        match = new EdgeArray(0, a_match->Num() + 1);
        match->Add(f0);
        match->Append(a_match);
        answ = wa;
    } else {
        match = b_match;
        b_match = nullptr; // so won't delete it
        answ = wb;
    }
    delete a_match;
    delete a_edges;

    delete b_match;

    delete b_edges;
    *pmatchweight = answ;
    return match;
}

// Partition the edges of er (except er[excepti], if excepti != -1)
// int newly allocated a_edges and b_edges,
// so that edges with the same component number are in the same
// partition.
// Generally, put odd components into a_edges an even into b_edges,
// except that component compa goes into a_edges and compb into b_edges.
// (compa and/or compb can be 0 to avoid these exceptional cases).
// Return a_edges and b_edges through *pa_edges and *pb_edges.
static void PartitionComps(const EdgeArray *er, const int *comp, const int excepti, EdgeArray **pa_edges, EdgeArray **pb_edges, const int compa, const int compb) {
    const int ne = er->Num();
    auto *a_edges = new EdgeArray(0, ne);
    auto *b_edges = new EdgeArray(0, ne);
    for (int i = 0; i < ne; ++i) {
        if (i == excepti)
            continue;
        Edge *f = er->Get(i);
        const int c = comp[f->Val()];
        if (c == compa || (c != compb && (c & 1) == 1))
            a_edges->Add(f);
        else
            b_edges->Add(f);
    }
    *pa_edges = a_edges;
    *pb_edges = b_edges;
}

// Return copy of er, except for those whose Val or Sym's Val
// is v0 or v1.
// Returned array will have allocated size equal to er's size.
static EdgeArray *CopyExcluding(const EdgeArray *er, const int v0, const int v1) {
    const int ne = er->Num();
    auto *ans = new EdgeArray(0, ne);
    for (int i = 0; i < ne; ++i) {
        Edge *f = er->Get(i);
        const int t0 = f->Val();
        const int t1 = f->Sym()->Val();
        if (t0 == v0 || t0 == v1 || t1 == v0 || t1 == v1)
            continue;
        ans->Add(f);
    }
    return ans;
}

// Helper for FindComponents depth-first-search.
// Visit vertex and its unvisited directly-connected vertices.
void FCVisit(EdgeArray *er, const int excepti, int *comp, const int vertex, const int compnum) {
    comp[vertex] = compnum;
    for (int i = 0; i < er->Num(); ++i) {
        if (i == excepti)
            continue;
        Edge *f = er->Get(i);
        const int t0 = f->Val();
        const int t1 = f->Sym()->Val();
        if (t0 == vertex || t1 == vertex) {
            int v = t0;
            if (v == vertex)
                v = t1;
            if (comp[v] == 0)
                FCVisit(er, excepti, comp, v, compnum);
        }
    }
}

// Fill in component numbers in comp, where each connected component
// in graph of er (excluding er[excepti])
// gets a separate number, starting with 1 (so unused vertices get
// component number 0.
// Assume comp has size numtri.
// Return number of components found.
static int FindComponents(EdgeArray *er, const int excepti, int *comp, const int numtri) {
    int ncomps = 0;
    for (int i = 0; i < numtri; ++i)
        comp[i] = 0;
    const int ne = er->Num();
    for (int i = 0; i < ne; ++i) {
        Edge *f = er->Get(i);
        int v = f->Val();
        if (comp[v] == 0) {
            ++ncomps;
            FCVisit(er, excepti, comp, v, ncomps);
        }
        v = f->Sym()->Val();
        if (comp[v] == 0) {
            ++ncomps;
            FCVisit(er, excepti, comp, v, ncomps);
        }
    }

    return ncomps;
}

static void SetAllFaceValsAndFvals(const Subdiv *s, const int v, const float fv) {
    SubdivEdgeIter it(s);
    for (; it.Cur() != nullptr; it.GetNext()) {
        Edge *f = it.Cur()->Rot();
        f->SetVal(v);
        f->SetFval(fv);
        f->Sym()->SetVal(v);
        f->Sym()->SetFval(fv);
    }
}
