// A:M spline conversion adapted from Hash's Font wizard (Noel, 2002).
// FontWiz2 stages Unicode glyphs and extrusion before touching a host model.
#include "FontWiz2.h"
#include "SDK/HModel.h"
#include "SDK/HCP.h"
#include "SDK/HPatch.h"
#include "SDK/HProject.h"
#include "SDK/HPropert.h"
#include "StampName.h"
#include "SurfaceColor.h"
#include "geometry/geom.h"
#include "geometry/poly.h"
#include "geometry/extrude.h"
#include <memory>
#include <vector>
#include <stdexcept>

static void SubdivToModel(const Subdiv *, HModelCache *, HGroup *);
static void SetBiases(HCP *, const Vector &, const Vector &);

namespace fw2 {
HModelCache *FindLiveModel(const void *identity) {
    if (!identity) return nullptr;
    HProject *project = GetHProject();
    if (!project) return nullptr;
    auto *container = project->GetChildObjectCacheContainer();
    if (!container) return nullptr;
    for (auto *model = container->GetChildModelCache(); model;
         model = static_cast<HModelCache *>(model->GetSiblingSame()))
        if (model == identity) return model;
    return nullptr;
}
static std::string GroupName(HModelCache *model, const std::wstring &text) {
    for (unsigned instance = 1; instance < 1000000; ++instance) {
        const auto wide = StampName(text, instance);
        // A:M's group-name API is ANSI; geometry text remains Unicode.
        const int size = WideCharToMultiByte(CP_ACP, 0, wide.data(), static_cast<int>(wide.size()), nullptr, 0, nullptr, nullptr);
        std::string name(static_cast<std::size_t>(size), '\0');
        if (!size || !WideCharToMultiByte(CP_ACP, 0, wide.data(), static_cast<int>(wide.size()), name.data(), size, nullptr, nullptr))
            throw std::runtime_error("The text group name could not be encoded.");
        bool found = false;
        if (auto *container = model->GetChildGroupContainer())
            for (auto *group = container->GetChildGroup(); group; group = static_cast<HGroup *>(group->GetSiblingSame()))
                if (name == group->GetName()) { found = true; break; }
        if (!found) return name;
    }
    throw std::runtime_error("A unique text group name could not be created.");
}
HModelCache *ResolveModel(HTreeObject *object) {
    if (!object) return nullptr;
    HHashObject *candidate = nullptr;
    if (object->GetObjectType() == HOT_MODEL) candidate = static_cast<HHashObject *>(object);
    else if (object->GetObjectType() == HOT_GROUP)
        candidate = static_cast<HHashObject *>(object)->GetParentOfType(HOT_MODEL);
    if (!candidate || !static_cast<HAnimObject *>(candidate)->IsCache()) return nullptr;
    return static_cast<HModelCache *>(candidate);
}

HModelCache *Generate(HModelCache *model, const Options &options, std::uint32_t &splines) {
    const auto contours = ReadGlyphOutlines(options.text, options.font, options.height);
    Subdiv subdivision;
    for (const auto &contour : contours) {
        const int spline = subdivision.NewSpline();
        const auto vec = [](Point p) { return Vector(p[0], p[1], 0); };
        Vector current = vec(contour.start);
        Edge *first = nullptr;
        Edge *previous = nullptr;
        for (std::size_t i = 0; i < contour.segments.size(); ++i) {
            const auto &segment = contour.segments[i];
            const Vector finish = vec(segment.end);
            Edge *edge = nullptr;
            if (!first) first = edge = subdivision.MakeEdge(current, finish, spline);
            else if (i + 1 == contour.segments.size() && segment.end == contour.start)
                edge = subdivision.Connect(previous, first, spline);
            else edge = subdivision.Connect(previous, finish, spline);
            if (!edge) throw std::runtime_error("The glyph contour could not be constructed.");
            if (segment.curved) {
                edge->SetBezCP(0, vec(segment.control1));
                edge->SetBezCP(1, vec(segment.control2));
            }
            previous = edge;
            current = finish;
        }
    }
    std::unique_ptr<PolygonalAreaArray> areas(FindPolygonalAreas(&subdivision));
    if (!areas || !areas->Num() || !areas->AllClosedSplines())
        throw std::runtime_error("The text does not form closed outlines.");
    if (areas->Crosses())
        throw std::runtime_error("Text outlines overlap or cross. Try another font or shorter text.");
    if ((options.flags & (EX_BEV_FRONT | EX_BEV_SIDE | EX_BEV_BACK)) &&
        options.bevel >= areas->MaxInset((options.flags & EX_INWARD) != 0))
        throw std::runtime_error("The bevel is too large for this text. Reduce its amount.");
    unsigned flags = options.flags;
    if ((flags & EX_CLOSE_FRONT) && (flags & EX_CLOSE_BACK) &&
        !(flags & (EX_BEV_FRONT | EX_BEV_BACK))) flags |= EX_MID;
    Extrude(&subdivision, areas.get(), flags, options.depth, options.bevel);
    if (subdivision.NumPoints() > 200000)
        throw std::runtime_error("Generated text is too complex. Shorten it or reduce subdivisions.");
    splines = 0;
    for (SubdivSplineIter i(&subdivision); i.Cur(); i.GetNext()) ++splines;
    if (!splines) throw std::runtime_error("The text produced no splines.");
    // All glyph parsing, cancellation and geometry checks precede host mutation.
    const bool creating = options.newModel || !model;
    if (creating) model = HModelCache::New("FontWiz2 Text");
    else model->SaveAllToUndo();
    if (!model) throw std::runtime_error("A:M could not create the text model.");
    model->MakeCurrent();
    const auto name = GroupName(model, options.text);
    HGroup *group = model->CreateGroup(name.c_str());
    if (!group) throw std::runtime_error("A:M could not create the text group.");
    group->SetTempGroup(FALSE);
    SubdivToModel(&subdivision, model, group);
    if (options.applyColor) {
        auto *attributes = group->GetAttr();
        auto *diffuse = attributes ? attributes->GetDiffuseColor() : nullptr;
        if (!diffuse) throw std::runtime_error("A:M could not apply the text group's surface color.");
        const auto rgb = NormalizedSurfaceColor(options.surfaceColor);
        // An unset group property inherits its color; enable this override and
        // use normalized RGB, rather than COLORREF's byte-valued components.
        diffuse->SetNull(FALSE, group);
        diffuse->SetValue(RGBFloat(rgb[0], rgb[1], rgb[2]));
    }
    model->FindPatches();
    model->SetChanged(TRUE);
    model->Update();
    model->OpenView();
    if (options.applyColor) {
        for (auto *instance = model->GetHeadInstance(); instance; instance = model->GetNextInstance(instance))
            if (instance->GetObjectType() == HOT_MODEL && !instance->IsCache())
                static_cast<HModel *>(instance)->ApplyAttrPropertyToPatches();
        group->RefreshInProjectBar();
    }
    if (creating) model->ZoomFit();
    if (creating) model->HilightInProjectBar();
    GetHProject()->UpdateAllViews(options.applyColor ? TRUE : FALSE);
    return model;
}
}  // namespace fw2

static void UpdateVertRoots(HCP **vertroots, const int i, HCP *cp, HModelCache *mch, HGroupCP **pgroup, HGroup *named, BOOL isloopback) {
    HCP *rootcp = vertroots[i];
    if (rootcp == nullptr) {
        vertroots[i] = cp;
    } else {
        isloopback = mch->AttachCPs(rootcp, cp);
    }
    // Note: if AttachCPs causes loopback, A:M deletes tail cp
    // before attaching, so can't add it to group
    if (!isloopback) {
        cp->AddToGroup(pgroup);
        if (!named->AddCP(cp) && !named->IsCPInGroup(cp))
            throw std::runtime_error("A:M could not add a point to the text group.");
    }
}

// Convert each spline in subdiv into a spline in the AM sense, in mch.
// Also, add them all to the "temporary group", which causes them to
// be selected (and the window to be resized to fit them) when the wizard returns.
static void SubdivToModel(const Subdiv *subdiv, HModelCache *mch, HGroup *named) {
    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    const int nv = subdiv->NumPoints();
    std::vector<HCP *> roots(static_cast<std::size_t>(nv), nullptr);
    HCP **vertroots = roots.data();
    HGroupCP *group = nullptr;
    SubdivSplineIter ssi(subdiv);
    for (; ssi.Cur() != nullptr; ssi.GetNext()) {
        Edge *se = ssi.Cur();
        SplineIter si(se);
        Edge *e = si.Cur();
        if (e == nullptr)
            continue;
        const BOOL islooped = e->SplineIsLooped();
        const int i0 = e->Org();
        int i = e->Dst();
        ASSERT(0 <= i0 && i0 < nv && 0 <= i && i < nv);
        Vector p0 = subdiv->Coords(i0);
        Vector p = subdiv->Coords(i);
        HSpline *sh = mch->StartSpline(&p0, &p);
        if (!sh) throw std::runtime_error("A:M could not create a spline.");
        HCP *firstcp = sh->GetHeadCP();
        UpdateVertRoots(vertroots, i0, firstcp, mch, &group, named, FALSE);
        HCP *cp = firstcp->GetNext();
        UpdateVertRoots(vertroots, i, cp, mch, &group, named, FALSE);
        si.GetNext();
        int nedges = 1;
        for (; si.Cur() != nullptr; si.GetNext()) {
            nedges++;
            e = si.Cur();
            i = e->Dst();
            ASSERT(0 <= i && i < nv);
            p = subdiv->Coords(i);
            cp = mch->AddCP(cp, &p);
            UpdateVertRoots(vertroots, i, cp, mch, &group, named, i == i0);
        }

        // Now set tangents
        // The SDK (8.5 version, at least) doesn't compute biases correctly
        // for end points of non-closed splines.
        // So, as a workaround, we peak all points on non-closed splines,
        // except possibly the first and last, when their respective segments
        // are curved (this seems to be necessary).
        if (nedges <= 1)
            continue;

        SplineIter si2(se);
        cp = firstcp;
        for (; si2.Cur() != nullptr; si2.GetNext()) {
            e = si2.Cur();
            Vector t1 = subdiv->StartTangent(e);
            if (islooped) {
                const Edge *eprev = e->Sprev();
                if (eprev != nullptr) {
                    Vector t2 = subdiv->EndTangent(eprev);
                    const float ang = Angle(t1, t2);
                    if (hash_math::abs(ang) > 1.F) {
                        cp->SetPeaked();
                    }
                }
            } else {
                // workaround for non-looped splines
                if (!e->IsCubic() || cp != firstcp)
                    cp->SetPeaked();
            }
            cp = cp->GetNext();
        }
        if (!islooped) {
            // last cp too
            ASSERT(e != nullptr && cp != nullptr);
            if (!e->IsCubic())
                cp->SetPeaked();
        }
        SplineIter si3(se);
        cp = firstcp;

        for (; si3.Cur() != nullptr; si3.GetNext()) {
            e = si3.Cur();
            Vector t1 = subdiv->StartTangent(e);
            const Edge *eprev = e->Sprev();
            SetBiases(cp, t1, eprev ? subdiv->EndTangent(eprev) : t1);
            cp = cp->GetNext();
        }
        if (!islooped) {
            // last cp
            Vector t1 = subdiv->EndTangent(e);
            SetBiases(cp, t1, t1);
        }
    }

    // make all the added CPs and Splines the (selected) temporary group
    if (group != nullptr)
        mch->AddToTemporaryGroup(group);

    mch->SetChanged();


}

// Compute A:M biases for cp, so that the tangent leading into t2 from
// previous cp is t1, and the tangent out of cp to next cp is t1.
static void SetBiases(HCP *cp, const Vector &t1, const Vector &t2) {
    const Vector tin(-t1.x, -t1.y, -t1.z);
    const Vector tout(-t2.x, -t2.y, -t2.z);
    float ina, ing, inm, outa, outg, outm;
    //   cp->SetBiasedNormal(TRUE);
    cp->ComputeInBias(tin, ina, ing, inm);
    cp->ComputeOutBias(tout, outa, outg, outm);
#ifdef _DEBUG
    gtrace(" InBias %f %f %f %f %f %f\n", tin.x, tin.y, tin.z, ina, ing, inm);
    gtrace("OutBias %f %f %f %f %f %f\n", tout.x, tout.y, tout.z, outa, outg, outm);
#endif
    if (hash_math::abs(ing) > .1f)
        cp->SetInGamma(ing);
    if (hash_math::abs(outg) > .1f)
        cp->SetOutGamma(outg);
    cp->SetInMagnitude(inm);
    cp->SetOutMagnitude(outm);
}
