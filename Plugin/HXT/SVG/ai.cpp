// ReSharper disable CppTooWideScope
#include "StdAfx.h"
#include "Vector.h"
#include "Vector2.h"
#include "geom.h"
#include "poly.h"
#include "aiformat.h"
#include "ai.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

static void GetAIObjSplines(Subdiv *subdiv, AIObject *obj);
static Edge *GetAIPathSpline(Subdiv *subdiv, const AIPath *path);

//static const float aiscale = 1.F;

static Vector ScaledV(const double x, const double y) {
    return Vector((float)x, (float)y, 0.F);
    //	return Vector(aiscale*(float)x, aiscale*(float)y, 0.F);
}

PolygonalAreaArray *BuildAIEdges(Subdiv *subdiv, const AIParser *aip) {
    AIObject *obj = aip->objects.Head();
    while (obj != nullptr) {
        GetAIObjSplines(subdiv, obj);
        obj = AIObjectList::Next(obj);
    }
    return FindPolygonalAreas(subdiv);
}

void GetAIObjSplines(Subdiv *subdiv, AIObject *obj) {
    AIPath *path;
    if (obj->kind == AIOCompoundPath) {
        const AICompoundPath *cpath = (AICompoundPath*)obj;
        AIObject *pathobj = cpath->members.Head();
        for (; pathobj != nullptr; pathobj = AIObjectList::Next(pathobj)) {
            ASSERT(pathobj->kind == AIOPath);
            path = (AIPath*)pathobj;
            GetAIPathSpline(subdiv, path);
        }
    } else if (obj->kind == AIOPath) {
        ASSERT(obj->kind == AIOPath);
        path = (AIPath*)obj;
        GetAIPathSpline(subdiv, path);
    }
}

// Makes a new spline in subdiv corresponding to path,
// scaled by global aiscale, and return a representative Edge*.
// Return 0 if the path has only a moveto.
// There should be exactly one moveto, at the beginning.
Edge *GetAIPathSpline(Subdiv *subdiv, const AIPath *path) {
    AIObject *obj = path->pathops.Head();
    if (obj == nullptr)
        return nullptr;
    ASSERT(obj->kind == AIOPathOp);
    const auto *pop = (AIPathOp*)obj;
    if (pop->opkind != AIPMoveto) {
        gtrace("Path doesn't begin with moveto\n");
        return nullptr;
    }
    const Vector origin = ScaledV(pop->x1, pop->y1);
    Vector curv = origin;
    obj = AIObjectList::Next(pop);
    if (obj == nullptr)
        return nullptr;
    Edge *epath = nullptr;
    Edge *ecur = nullptr;
    const int spath = subdiv->NewSpline();
    Vector nextv;
    BOOL needclose = path->close;
    for (; obj != nullptr; obj = AIObjectList::Next(obj)) {
        ASSERT(obj->kind == AIOPathOp);
        pop = (AIPathOp*)obj;
        if (pop->opkind == AIPLineto) {
            nextv = ScaledV(pop->x1, pop->y1);
        } else if (pop->opkind == AIPCurveto) {
            nextv = ScaledV(pop->x3, pop->y3);
        } else {
            gtrace("Unexpected path op\n");
            break;
        }
        if (curv != nextv) {
            if (epath == nullptr)
                ecur = epath = subdiv->MakeEdge(curv, nextv, spath);
            else {
                if (nextv == origin && AIObjectList::Next(pop) == nullptr) {
                    // close is done explicitly in path
                    ecur = subdiv->Connect(ecur, epath, spath);
                    needclose = FALSE;
                } else
                    ecur = subdiv->Connect(ecur, nextv, spath);
            }
            if (pop->opkind == AIPCurveto) {
                Vector cp0 = ScaledV(pop->x1, pop->y1);
                Vector cp1 = ScaledV(pop->x2, pop->y2);
                if (cp0 == curv) {
                    // This results from 'v' commands.
                    // Make the start tangent slightly nonzero,
                    // so that rest of program won't get confused.
                    // At a tiny delta from the start point, the tangent
                    // points to the next cp.
                    cp0 = LinInterp(.01f, cp0, cp1);
                }
                if (cp1 == nextv) {
                    // Similarly, from 'y' commands...
                    cp1 = LinInterp(.01f, cp1, cp0);
                }
                ecur->SetBezCP(0, cp0);
                ecur->SetBezCP(1, cp1);
            }
        }
        curv = nextv;
    }
    if (needclose && ecur != nullptr && epath != nullptr)
        subdiv->Connect(ecur, epath, spath);
    return epath;
}
