// NAP  5/21/2002  \Noel95\Plugin\HXT\Font\Evaluate.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "F_Protos.h"
#include "geom.h"
#include "poly.h"
#include "Glyph.h"
#include "aiformat.h"
#include "ai.h"
#include "extrude.h"

// amount to scale glyph coords by
// (original glyph coords use 2048 for design size)
static constexpr float scale = 0.01F;

// depth (z-extent) of created characters, after scaling
//static const float depth = 2.5f;

static PolygonalAreaArray *BuildFontString(Subdiv *subdiv, FontParameters *parms);
static PolygonalAreaArray *BuildAI(Subdiv *subdiv, const CString &filename);
static void SubdivToModel(const Subdiv *subdiv, HModelCache *mch, BOOL makegroup);
static void SetBiases(HCP *cp, const Vector &t1, const Vector &t2);

BOOL CHxtApp::NewShape(HModelCache *mch) {
    CWaitCursor wait;
    auto *s = new Subdiv();
    PolygonalAreaArray *areas;
    if (m_parameters.m_isfont) {
        areas = BuildFontString(s, &m_parameters);
    } else {
        areas = BuildAI(s, m_parameters.m_aifile);
    }
    if (areas == nullptr) {
        delete s;
        return TRUE;
    }
    if (!areas->AllClosedSplines()) {
        if (AfxMessageBox("The specified geometry contains some paths " "that are not single closed splines, and thus will probably " "extrude and/or close badly.  Continue anyway?", MB_YESNO) != IDYES)
            return TRUE;
    }
    if (areas->Crosses()) {
        if (AfxMessageBox("Some edges (regarded as straight) cross each other " ", and thus will probably extrude and/or close badly.  Continue anyway?", MB_YESNO) != IDYES)
            return TRUE;
    }
    float inset = m_parameters.m_bevamt * 0.1F;
    const BOOL anybevels = m_parameters.m_bevfronts || m_parameters.m_bevsides || m_parameters.m_bevbacks;
    const BOOL inward = m_parameters.m_bevinward;
    if (anybevels) {
        const float maxinset = areas->MaxInset(inward);
        if (inset >= maxinset) {
            const float suggest_inset = .9f * maxinset;
            const double o_i = inset / 0.1;
            const double n_i = suggest_inset / 0.1;
            CString msg;
            msg.Format("The specified inset (%g) will likely produce edge overlaps. Do you want to use the maximum suggested inset (%g) instead?", o_i, n_i);
            if (AfxMessageBox(msg, MB_YESNO) == IDYES) {
                inset = suggest_inset;
                SetRegistryValue("Font HXT", "BevAmount", RoundValue(inset * 10.F, 0.1F));
            }
        }
    }
    unsigned flags = 0;
    if (m_parameters.m_fronts)
        flags |= EX_CLOSE_FRONT;
    if (m_parameters.m_backs)
        flags |= EX_CLOSE_BACK | EX_BACK;
    if (m_parameters.m_sides)
        flags |= EX_BACK;
    if (m_parameters.m_bevfronts)
        flags |= EX_BEV_FRONT;
    if (m_parameters.m_bevbacks)
        flags |= EX_BEV_BACK;
    if (m_parameters.m_bevsides)
        flags |= EX_BEV_SIDE;
    if (m_parameters.m_bevround)
        flags |= EX_ROUND;
    if (m_parameters.m_fronts && m_parameters.m_backs && !m_parameters.m_bevfronts && !m_parameters.m_bevbacks)
        flags |= EX_MID;
    if (inward)
        flags |= EX_INWARD;
    if (m_parameters.m_subdivkind != FontParameters::SUB_NONE) {
        flags |= EX_SUB;
        if (m_parameters.m_subdivkind == FontParameters::SUB_ALL)
            flags |= EX_SUB_ALL;
    }
    Extrude(s, areas, flags, m_parameters.m_depth, inset);
    SubdivToModel(s, mch, makegroup);
    delete areas;
    delete s;
    mch->SetChanged(TRUE);
    mch->OpenView();
    if (!makegroup)
        mch->HilightInProjectBar();
    return TRUE;
}

static PolygonalAreaArray *BuildFontString(Subdiv *subdiv, FontParameters *parms) {
    Vector origin(0.0F, 0.0F, 0.0F);
    for (int textpos = 0; textpos < parms->m_buildtext.GetLength(); ++textpos) {
        const int ch = parms->m_buildtext[textpos];
        GetGlyphSplines(subdiv, ch, parms->m_facename, parms->FaceWeight(), parms->IsItalicFace(), &origin, scale);
    }
    return FindPolygonalAreas(subdiv);
}

static PolygonalAreaArray *BuildAI(Subdiv *subdiv, const CString &filename) {
    AIParser parser;
    if (parser.TokenizeFile(filename)) {
        parser.ParseTokens();
        return BuildAIEdges(subdiv, &parser);
    }
    return nullptr;
}

// The vertroots array is being used to keep track of which CP is the "root"
// (first) CP for a given subdivision point (indexed by integers).
// This routine is being called to say that a new CP, cp, has just been made
// for subdiv point i.  If this is the first such, make it the root,
// otherwise attach it to the root using mch.
// Also, add the new cp to pgroup, if not a loopback edge
static void UpdateVertRoots(HCP **vertroots, const int i, HCP *cp, HModelCache *mch, HGroupCP **pgroup, BOOL isloopback) {
    HCP *rootcp = vertroots[i];
    if (rootcp == nullptr) {
        vertroots[i] = cp;
    } else {
        isloopback = mch->AttachCPs(rootcp, cp);
    }
    // Note: if AttachCPs causes loopback, A:M deletes tail cp
    // before attaching, so can't add it to group
    if (!isloopback)
        cp->AddToGroup(pgroup);
}

// Convert each spline in subdiv into a spline in the AM sense, in mch.
// Also, add them all to the "temporary group", which causes them to
// be selected (and the window to be resized to fit them) when the wizard returns.
static void SubdivToModel(const Subdiv *subdiv, HModelCache *mch, BOOL makegroup) {
    if (mch->GetHeadInstance()) // There is at least one visible model, so lets selected the points
        makegroup = TRUE;
    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    const int nv = subdiv->NumPoints();
    HCP **vertroots = new HCP *[nv];
    for (int j = 0; j < nv; ++j)
        vertroots[j] = nullptr;
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
        HCP *firstcp = sh->GetHeadCP();
        UpdateVertRoots(vertroots, i0, firstcp, mch, &group, FALSE);
        HCP *cp = firstcp->GetNext();
        UpdateVertRoots(vertroots, i, cp, mch, &group, FALSE);
        si.GetNext();
        int nedges = 1;
        for (; si.Cur() != nullptr; si.GetNext()) {
            nedges++;
            e = si.Cur();
            i = e->Dst();
            ASSERT(0 <= i && i < nv);
            p = subdiv->Coords(i);
            cp = mch->AddCP(cp, &p);
            UpdateVertRoots(vertroots, i, cp, mch, &group, i == i0);
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
    if (group != nullptr && makegroup)
        mch->AddToTemporaryGroup(group);

    mch->SetChanged();

    delete[] vertroots;
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
