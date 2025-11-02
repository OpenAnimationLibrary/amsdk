// include geom.h before this
#pragma once

// A boundary polygon and some number of directly-contained island polygons (perhaps unclosed).
// For now, the various routines that traverse the edges of the boundary and
// islands assume that each polygon consists of one spline.
// (This allows the Copy operation, etc, to work even after the area has had extra diagonal
// edges added.)
class PolygonalArea {
public:
    Edge *boundary; // a representative edge in CCW-oriented outer boundary
    EdgeArray *islands; // representative edges in CW-oriented islands directly inside outer boundary
    Subdiv *subdiv; // the subdivision in which all the edges live

    PolygonalArea() : boundary(nullptr), islands(nullptr), subdiv(nullptr) { }

    ~PolygonalArea() {

        delete islands;
    }

    // Create copy in subdiv, with each vertex offset by "offset"
    [[nodiscard]] PolygonalArea *Copy(const Vector &offset) const;

    // Inset in place
    void Inset(float inset, BOOL inward) const;

    // Cut corners in place
    void CutCorners(float inset, BOOL round) const;

    // Split edges into two, in place.  If not "all", split only "curvy" edges, else split all.
    void Subdivide(BOOL all) const;

    [[nodiscard]] float MaxInset(BOOL inward) const; // calculate inset that causes edge meets
    [[nodiscard]] BOOL AllClosedSplines() const; // TRUE if all polygons are single closed splines
    [[nodiscard]] BOOL Crosses() const; // TRUE if some polygon crosses itself or another

    // unimplemented
    PolygonalArea &operator=(const PolygonalArea &other) = delete;
    PolygonalArea(const PolygonalArea &other) = delete;
};

// Array of Polygonal Area pointers
class PolygonalAreaArray {
    PolygonalArea **areas; // array of PolygonalArea pointers stored here
    int num;
    int allocnum; // can be greater than num

public:
    explicit PolygonalAreaArray(int n);
    PolygonalAreaArray(int n, int allocn);
    PolygonalAreaArray(const PolygonalAreaArray &other);
    ~PolygonalAreaArray();

    void Set(int i, PolygonalArea *a);
    void Add(PolygonalArea *a);
    void GrowTo(int n);

    [[nodiscard]] PolygonalArea *Get(const int i) const {
        return areas[i];
    }

    [[nodiscard]] int Num() const {
        return num;
    }

    // Return new array, with copies of original offset by "offset"
    [[nodiscard]] PolygonalAreaArray *Copy(const Vector &offset) const;

    // Inset in place
    void Inset(float inset, BOOL inward) const;

    // Cut corners in place
    void CutCorners(float inset, BOOL round) const;

    // Split edges into two, in place.  If not "all", split only "curvy" edges, else split all.
    void Subdivide(BOOL all) const;

    [[nodiscard]] float MaxInset(BOOL inward) const; // calculate inset that causes edge meets
    [[nodiscard]] BOOL AllClosedSplines() const; // TRUE if AllClosedSplines() is true for every area
    [[nodiscard]] BOOL Crosses() const; // TRUE if Crosses() is true for any area

    // unimplemented
    PolygonalAreaArray &operator=(const PolygonalAreaArray &other) = delete;
};

EdgeArray *FindPolys(Subdiv *s);
PolygonalAreaArray *FindPolygonalAreas(Subdiv *s);
Edge *LeftFaceLowestOrg(Edge *e);
void Skin(Subdiv *subdiv, PolygonalAreaArray **a, int numarrays, BOOL round, int firstcut, int lastcut);
