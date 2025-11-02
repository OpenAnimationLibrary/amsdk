#include "StdAfx.h"
#include "Vector.h"
#include "Vector2.h"
#include "geom.h"
#include "Glyph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

class GlyphContour {
public:
    POINTFX pfxStart;
    TTPOLYCURVE **elems;
    int numelems;

    GlyphContour() : pfxStart{}, elems(nullptr), numelems(0) { }
    ~GlyphContour();

    GlyphContour(const GlyphContour&) = delete;
    GlyphContour &operator= (const GlyphContour&) = delete; 
    GlyphContour(GlyphContour &&) = delete; 
    GlyphContour &operator=(GlyphContour &&) = delete; 

    void Trace() const;
};

GlyphContour::~GlyphContour() {
    if (numelems > 0) {
        for (int i = 0; i < numelems; ++i)
            delete elems[i];
        delete elems;
    }
}

class GlyphInfo {
public:
    int charnum;
    ABC abc;
    GLYPHMETRICS metrics;
    GlyphContour **contours;
    int numcontours;

    GlyphInfo() : charnum(-1), abc{}, metrics{}, contours(nullptr), numcontours(0) { }
    explicit GlyphInfo(const int ch) : charnum(ch), abc{}, metrics{}, contours(nullptr), numcontours(0) { }
    ~GlyphInfo();

    GlyphInfo(const GlyphInfo&) = delete;
    GlyphInfo &operator= (const GlyphInfo&) = delete; 
    GlyphInfo(GlyphInfo &&) = delete; 
    GlyphInfo &operator=(GlyphInfo &&) = delete; 

    void GetContours(CFont *f);
    void Trace() const;
};

GlyphInfo::~GlyphInfo() {
    if (numcontours > 0) {
        for (int i = 0; i < numcontours; ++i)
            delete contours[i];
        delete contours;
    }
}

// Populate the contours array for this GlyphInfo.
// Also fills in abc and metrics.
void GlyphInfo::GetContours(CFont *f) {
    if (f == nullptr || charnum == -1)
        return;

    CClientDC dc(AfxGetMainWnd());

    CFont *oldf = dc.SelectObject(f);
    if (!dc.GetCharABCWidths(charnum, charnum, &abc)) {
        // treat as empty character
        memset(&abc, 0, sizeof(ABC));
        memset(&metrics, 0, sizeof(GLYPHMETRICS));
        return;
    }

    MAT2 mat{};

    mat.eM11.value = 1;
    mat.eM22.value = 1;

    // Would like to use GGO_BEZIER, but got nothing
    // when tried it with the GVX1
    const int bufsize = dc.GetGlyphOutline(charnum, GGO_NATIVE, &metrics, 0, nullptr, &mat);

    if (bufsize > 0) {
        char *buf = new char[bufsize];
        if (dc.GetGlyphOutline(charnum, GGO_NATIVE, &metrics, bufsize, buf, &mat)) {
            char *p = buf;
            char *savep = p;
            const char *ebuf = &buf[bufsize];
            // First, count number of contours
            numcontours = 0;
            while (p < ebuf) {
                const TTPOLYGONHEADER *h = (TTPOLYGONHEADER *)p;
                p += h->cb;
                if (p <= ebuf)
                    numcontours++;
            }
            contours = new GlyphContour *[numcontours];
            int cindex = 0;
            p = savep;
            while (p < ebuf) {
                const TTPOLYGONHEADER *h = (TTPOLYGONHEADER *)p;
                char *econtour = p + h->cb;
                if (econtour <= ebuf) {
                    auto *c = new GlyphContour();
                    ASSERT(cindex < numcontours);
                    contours[cindex++] = c;
                    c->pfxStart = h->pfxStart;
                    p += sizeof(TTPOLYGONHEADER);
                    // Count number of elements
                    savep = p;
                    int nelems = 0;
                    while (p < econtour) {
                        const TTPOLYCURVE *ehdr = (TTPOLYCURVE *)p;
                        const int nb = sizeof(TTPOLYCURVE) + (ehdr->cpfx - 1) * sizeof(POINTFX);
                        if (p + nb <= econtour) {
                            nelems++;
                            p += nb;
                        } else {
                            p = econtour;
                            break;
                        }
                    }
                    c->numelems = nelems;
                    c->elems = new TTPOLYCURVE *[nelems];
                    p = savep;
                    int eindex = 0;
                    while (p < econtour) {
                        const TTPOLYCURVE *ehdr = (TTPOLYCURVE *)p;
                        const int nb = sizeof(TTPOLYCURVE) + (ehdr->cpfx - 1) * sizeof(POINTFX);
                        if (p + nb <= econtour) {
                            auto *e = (TTPOLYCURVE *)new char[nb];
                            memmove(e, ehdr, nb);
                            ASSERT(eindex < nelems);
                            c->elems[eindex++] = e;
                            p += nb;
                        } else {
                            gtrace("partial contour buffer\n");
                            p = econtour;
                            break;
                        }
                    }
                } else {
                    gtrace("partial glyph buffer\n");
                    break;
                }
            }
        }
        delete [] buf;
    }
    dc.SelectObject(oldf);
    // Trace();
}

double FIXEDtod(const FIXED v) {
    const double d = v.value + (double)v.fract / 65535.;
    return d;
}

float FIXEDtof(const FIXED v) {
    const float f = v.value + (float)v.fract / 65535.0F;
    return f;
}

Vector POINTFXtov(const POINTFX p) {
    return Vector(FIXEDtof(p.x), FIXEDtof(p.y), 0.0F);
}

// Get contours for character ch in font with given name,
// putting the results into subdiv.
// Each contour is given a separate "spline" id.
// Scale the glyph coordinates by multiplying each by "scale",
// and use *porigin as the character origin.
// Update *porigin to place to put next character.
// Return TRUE if got the contours, else FALSE.
BOOL GetGlyphSplines(Subdiv *subdiv, const int ch, const CString &facename, const int weight, const int is_italic, Vector *porigin, const float scale) {
    if (ch < 0 || facename.IsEmpty())
        return 0;

    GlyphInfo gi(ch);

    CFont calcfont;

    if (!calcfont.CreateFont(-2048, 0, 0, 0, weight, is_italic, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, facename)) {
        return FALSE;
    }

    gi.GetContours(&calcfont);

    Vector origin = *porigin;
    origin.x += scale * gi.abc.abcA;

    gtrace("got %d contours\n", gi.numcontours);

    for (int i = 0; i < gi.numcontours; ++i) {
        const GlyphContour *gc = gi.contours[i];
        if (gc->numelems == 0)
            continue;
        Edge *econtour = nullptr;
        Edge *ecur = nullptr;
        const int scontour = subdiv->NewSpline();
        Vector curv = origin + scale * POINTFXtov(gc->pfxStart);
        Vector nextv;
        Vector controlv;
        for (int j = 0; j < gc->numelems; ++j) {
            const TTPOLYCURVE *e = gc->elems[j];
            switch (e->wType) {
                case TT_PRIM_LINE:
                    for (int k = 0; k < e->cpfx; ++k) {
                        nextv = origin + scale * POINTFXtov(e->apfx[k]);
                        if (econtour == nullptr)
                            ecur = econtour = subdiv->MakeEdge(curv, nextv, scontour);
                        else {
                            if (j < gc->numelems - 1 || k < e->cpfx - 1)
                                ecur = subdiv->Connect(ecur, nextv, scontour);
                            else {
                                // Don't add edge here if final elem and point is same as first point in contour.
                                // In latter case, just connect current edge to first one.
                                // In any case, make sure contour is closed now.
                                if (nextv != subdiv->Coords(econtour->Org()))
                                    ecur = subdiv->Connect(ecur, nextv, scontour);
                                ecur = subdiv->Connect(ecur, econtour, scontour);
                            }
                        }
                        curv = nextv;
                    }
                    break;
                case TT_PRIM_QSPLINE:
                    // all points in record except last are
                    // off-curve control points of the quadratic
                    // b-spline.  The last point in record is on-curve.
                    // for every off-curve point before the last, average
                    // that off-curve point and the next (off-curve) point
                    // to get the required on-curve point.
                    for (int k = 0; k < e->cpfx;) {
                        controlv = origin + scale * POINTFXtov(e->apfx[k++]);
                        if (k == e->cpfx - 1) {
                            // last on-curve point is in apfx list
                            nextv = origin + scale * POINTFXtov(e->apfx[k++]);
                        } else {
                            // other on-curve points are midway between apfx points
                            nextv = origin + scale * 0.5F * (POINTFXtov(e->apfx[k - 1]) + POINTFXtov(e->apfx[k]));
                        }
                        BOOL needclose = FALSE;
                        if (econtour == nullptr) {
                            ecur = econtour = subdiv->MakeEdge(curv, nextv, scontour);
                        } else {
                            if (j < gc->numelems - 1 || k < e->cpfx - 1) {
                                ecur = subdiv->Connect(ecur, nextv, scontour);
                            } else {
                                if (nextv != subdiv->Coords(econtour->Org())) {
                                    ecur = subdiv->Connect(ecur, nextv, scontour);
                                    needclose = TRUE;
                                } else {
                                    ecur = subdiv->Connect(ecur, econtour, scontour);
                                }
                            }
                        }
                        // controlv is quadratic Bezier control point between
                        // on-curve points curv and nextv.
                        // Degree-elevation theory says that cubic control points
                        // are 2/3 of the way from curv and nextv to controlv.
                        Vector cp0 = LinInterp(2.0F / 3.0F, curv, controlv);
                        Vector cp1 = LinInterp(2.0F / 3.0F, nextv, controlv);
                        ecur->SetBezCP(0, cp0);
                        ecur->SetBezCP(1, cp1);
                        if (needclose)
                            ecur = subdiv->Connect(ecur, econtour, scontour);
                        curv = nextv;
                    }
                    break;
                default:ASSERT(FALSE);
            }
        }
    }
    porigin->x += scale * (gi.abc.abcA + gi.abc.abcB + gi.abc.abcC);
    return TRUE;
}

static void TracePointFX(const POINTFX p) {
    const double x = FIXEDtod(p.x);
    const double y = FIXEDtod(p.y);
    gtrace("(%g,%g)", x, y);
}

/*
static void TraceWords(WORD *a, const int nwords) {
    for (int i = 0; i < nwords; ++i) {
        if (i > 0 && i % 5 == 0)
            gtrace("\n");
        gtrace("%6d", a[i]);
    }
}
*/

void GlyphContour::Trace() const {
    const int n = numelems;
    gtrace("\nContour, start=(%g,%g), %d polycurves\n", FIXEDtod(pfxStart.x), FIXEDtod(pfxStart.y), n);
    for (int i = 0; i < n; ++i) {
        const TTPOLYCURVE *e = elems[i];
        ASSERT(e != nullptr);
        const char *s;
        switch (e->wType) {
            case TT_PRIM_LINE:
                s = "line";
                break;
            case TT_PRIM_QSPLINE:
                s = "quadratic spline";
                break;
            default:
                s = "?unknown type";
        }
        gtrace("\t%s, %d points\n", s, e->cpfx);
        for (int j = 0; j < e->cpfx; ++j) {
            TracePointFX(e->apfx[j]);
            gtrace("\n");
        }
    }
}

void GlyphInfo::Trace() const {
    gtrace("\n\nGLYPH for char %c (%d), %d contours\n", charnum, charnum, numcontours);
    for (int i = 0; i < numcontours; ++i)
        contours[i]->Trace();
}
