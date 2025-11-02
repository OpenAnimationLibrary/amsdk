//KB  5/14/98  \KenB\Include\Curves.h
#pragma once

//#define FR(x)         ((x) + 0x8000 >> 16)
//#define ff(x)         ((long)(x) << 16)
//#define fmoveto(x, y) MoveTo(FR(x), FR(y))
//#define flineto(x, y) LineTo(FR(x), FR(y))
//#define AVE(a, b)     (((a) + (b)) / 2)

//constexpr int kCurveLimit = 3;
constexpr int anyNumber = 1;


//#define kCurveLimit 3
//#define anyNumber 1

typedef long newfixed;

typedef struct {
    newfixed x;
    newfixed y;
} point;

typedef struct {
    point start;
    point control;
    point end;
} curve;

typedef struct {
    long vectors;
    long controlBits[anyNumber];
    point vector[anyNumber];
} path;

typedef struct {
    long contours;
    path contour[anyNumber];
} paths;

int OnCurve(long *bits, long index);
void FrameCurve(curve *cur, int level);
path *FramePath(path *, int closed);
void FramePaths(paths *, int closed);
void MarkPaths(paths *);
paths *AppendPaths(paths *, paths *);
void GetPathsBounds(paths *, Rect *);
void DisposePaths(paths *);

void OffsetPaths(paths *, newfixed dx, newfixed dy);
void ScalePaths(paths *, newfixed sx, newfixed sy);
void MapPaths(paths *, Rect *src, Rect *dst);

long SizeOfPaths(paths *p);
paths *CopyPaths(paths *p);

typedef struct {
    int isLine;
    curve c;

    /* private */
    long index;
    long ep;
    long *bits;
    point *p;
} pathWalker;

path *NextPath(path *aPath);
void InitPathWalker(pathWalker *w, path *aPath);
int NextPathSegment(pathWalker *w); /* returns false when the path if finished */
