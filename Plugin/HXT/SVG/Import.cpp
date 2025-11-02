// \Plugin\HXT\SVG\Import.cpp

// ReSharper disable CppTooWideScope
#include "StdAfx.h"
#include "StringLi.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "ImportModelDialog.h"
#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HProgres.h"
#include "geom.h"
#include "poly.h"
#include "aiformat.h"
#include "ai.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "quad.h"
#include "extrude.h"
#include "SDK/HProject.h"

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) {
#ifdef _DEBUG1
    ImportSVG_Path("E:\\bugs\\SVGTest\\10_impact.svg", hmc);
#else
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("SVG");
    StringList *namelist;
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }

    if (namelist == nullptr) {
        CString caption1;
        caption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTING);
        MessageBox(GetMainApplicationWnd(), text, caption1, MB_OK);
        return TRUE;
    }
    m_parameters.center = GetRegistryBOOL("SVG HXT", "Center", FALSE);
    m_parameters.resolution = GetRegistryValue("SVG HXT", "Resolution", 96);
    m_parameters.unit = GetRegistryValue("SVG HXT", "Unit", 0);
    m_parameters.importaspathonly = GetRegistryBOOL("SVG HXT", "OnlyPath", FALSE);
    m_parameters.m_fronts = GetRegistryValue("SVG HXT", "Fronts", TRUE);
    m_parameters.m_sides = GetRegistryValue("SVG HXT", "Sides", TRUE);
    m_parameters.m_backs = GetRegistryValue("SVG HXT", "Backs", FALSE);
    m_parameters.m_bevfronts = GetRegistryValue("SVG HXT", "BevFronts", TRUE);
    m_parameters.m_bevsides = GetRegistryValue("SVG HXT", "BevSides", FALSE);
    m_parameters.m_bevbacks = GetRegistryValue("SVG HXT", "BevBacks", FALSE);
    m_parameters.m_bevround = GetRegistryValue("SVG HXT", "BevRound", FALSE);
    m_parameters.m_bevinward = GetRegistryValue("SVG HXT", "BevInward", TRUE);
    m_parameters.m_subdivkind = GetRegistryValue("SVG HXT", "SubdivKind", SVGParameters::SUB_NONE);
    m_parameters.m_bevamt = GetRegistryValue("SVG HXT", "BevAmount", 10.F);
    m_parameters.m_depth = GetRegistryValue("SVG HXT", "ExtrudeDepth", 10.F);

    CImportModelDialog cdlg(&m_parameters);
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }

    SetRegistryBOOL("SVG HXT", "Center", m_parameters.center);
    SetRegistryValue("SVG HXT", "Resolution", m_parameters.resolution);
    SetRegistryValue("SVG HXT", "Unit", m_parameters.unit);
    SetRegistryBOOL("SVG HXT", "OnlyPath", m_parameters.importaspathonly);
    SetRegistryValue("SVG HXT", "Fronts", m_parameters.m_fronts);
    SetRegistryValue("SVG HXT", "Sides", m_parameters.m_sides);
    SetRegistryValue("SVG HXT", "Backs", m_parameters.m_backs);
    SetRegistryValue("SVG HXT", "BevFronts", m_parameters.m_bevfronts);
    SetRegistryValue("SVG HXT", "BevSides", m_parameters.m_bevsides);
    SetRegistryValue("SVG HXT", "BevBacks", m_parameters.m_bevbacks);
    SetRegistryValue("SVG HXT", "BevRound", m_parameters.m_bevround);
    SetRegistryValue("SVG HXT", "BevInward", m_parameters.m_bevinward);
    SetRegistryValue("SVG HXT", "BevAmount", m_parameters.m_bevamt);
    SetRegistryValue("SVG HXT", "SubdivKind", m_parameters.m_subdivkind);
    SetRegistryValue("SVG HXT", "ExtrudeDepth", m_parameters.m_depth);

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        ImportSVG_Path(filename, hmc);
    }
    DeleteStringList(namelist);
#endif
    return TRUE;
}

BOOL CHxtApp::OnImportObjectCacheContainer(HObjectCacheContainer *hocc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("SVG");
    StringList *namelist;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }

    if (namelist == nullptr) {
        CString caption1;
        caption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTING);
        MessageBox(GetMainApplicationWnd(), text, caption1, MB_OK);
        return TRUE;
    }
    m_parameters.center = GetRegistryBOOL("SVG HXT", "Center", FALSE);
    m_parameters.resolution = GetRegistryValue("SVG HXT", "Resolution", 96);
    m_parameters.unit = GetRegistryValue("SVG HXT", "Unit", 0);
    m_parameters.importaspathonly = GetRegistryBOOL("SVG HXT", "OnlyPath", FALSE);
    m_parameters.m_fronts = GetRegistryValue("SVG HXT", "Fronts", TRUE);
    m_parameters.m_sides = GetRegistryValue("SVG HXT", "Sides", TRUE);
    m_parameters.m_backs = GetRegistryValue("SVG HXT", "Backs", FALSE);
    m_parameters.m_bevfronts = GetRegistryValue("SVG HXT", "BevFronts", TRUE);
    m_parameters.m_bevsides = GetRegistryValue("SVG HXT", "BevSides", FALSE);
    m_parameters.m_bevbacks = GetRegistryValue("SVG HXT", "BevBacks", FALSE);
    m_parameters.m_bevround = GetRegistryValue("SVG HXT", "BevRound", FALSE);
    m_parameters.m_bevinward = GetRegistryValue("SVG HXT", "BevInward", TRUE);
    m_parameters.m_subdivkind = GetRegistryValue("SVG HXT", "SubdivKind", SVGParameters::SUB_NONE);
    m_parameters.m_bevamt = GetRegistryValue("SVG HXT", "BevAmount", 10.F);
    m_parameters.m_depth = GetRegistryValue("SVG HXT", "ExtrudeDepth", 10.F);

    CImportModelDialog cdlg(&m_parameters);
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }
    SetRegistryBOOL("SVG HXT", "Center", m_parameters.center);
    SetRegistryValue("SVG HXT", "Resolution", m_parameters.resolution);
    SetRegistryValue("SVG HXT", "Unit", m_parameters.unit);
    SetRegistryBOOL("SVG HXT", "OnlyPath", m_parameters.importaspathonly);
    SetRegistryValue("SVG HXT", "Fronts", m_parameters.m_fronts);
    SetRegistryValue("SVG HXT", "Sides", m_parameters.m_sides);
    SetRegistryValue("SVG HXT", "Backs", m_parameters.m_backs);
    SetRegistryValue("SVG HXT", "BevFronts", m_parameters.m_bevfronts);
    SetRegistryValue("SVG HXT", "BevSides", m_parameters.m_bevsides);
    SetRegistryValue("SVG HXT", "BevBacks", m_parameters.m_bevbacks);
    SetRegistryValue("SVG HXT", "BevRound", m_parameters.m_bevround);
    SetRegistryValue("SVG HXT", "BevInward", m_parameters.m_bevinward);
    SetRegistryValue("SVG HXT", "BevAmount", m_parameters.m_bevamt);
    SetRegistryValue("SVG HXT", "SubdivKind", m_parameters.m_subdivkind);
    SetRegistryValue("SVG HXT", "ExtrudeDepth", m_parameters.m_depth);

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        String nameonly = filename.GetNameOnly();
        HModelCache *hmc = HModelCache::New(nameonly.Get());
        ImportSVG_Path(filename, hmc, TRUE);
    }
    DeleteStringList(namelist);

    return TRUE;
}

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
#include "Matrix34.h"

void CHxtApp::ImportSVG_Path(const String &pfilename, HModelCache *hmc, BOOL newmodel) {
    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_IMPORTTITLE);
        m_hprogressbar->SetMessage1(text);
        m_hprogressbar->SetMessage2(pfilename.GetNameOnly().Get());
    }

    String unit;
    switch (m_parameters.unit) {
        case 0:
            unit = "px";
            break;
        case 1:
            unit = "pt";
            break;
        case 2:
            unit = "pc";
            break;
        case 3:
            unit = "mm";
            break;
        case 4:
            unit = "cm";
            break;
        case 5:
            unit = "in";
            break;
        default:
            unit = "px";
            break;
    }

    if (m_hprogressbar) {
        m_hprogressbar->SetMessage2("Parsing File");
    }
    NSVGimage *g_image = nsvgParseFromFile(pfilename.Get(), unit.Get(), m_parameters.resolution);
    if (m_hprogressbar) {
        m_hprogressbar->SetProgress(33);
    }

    PFAD temppfad;
    std::vector<PFAD> pathlist;
    std::vector<HSpline *> splinelist;
    std::vector<SHAPE> shapelist;

    if (m_hprogressbar) {
        m_hprogressbar->SetMessage2("Build Splines");
    }
    int pathnumber = 0;
    for (NSVGshape *shape = g_image->shapes; shape != nullptr; shape = shape->next) {
        SHAPE tempshape;
        for (auto &i: tempshape.pfad) {
            i.path.clear();
        }
        tempshape.pfad.clear();
        for (NSVGpath *path = shape->paths; path != nullptr; path = path->next, pathnumber++) {
#ifdef _DEBUG1
            ATLTRACE2(atlTraceGeneral, 0, "Path %i Points %i\n", pathnumber, path->npts - 1);
            int j = 0;
            for (int i = 0; i < path->npts; ++i) {
                float *vwert = &path->pts[i * 2];
                switch (j) {
                    case 0:
                        ATLTRACE2(atlTraceGeneral, 0, "%i %f %f pos\n", i, vwert[0], vwert[1]);
                        j++;
                        break;
                    case 1:
//                        ATLTRACE2(atlTraceGeneral, 0, "%i %f %f out\n", i, vwert[0], vwert[1]);
                        j++;
                        break;
                    case 2:
//                        ATLTRACE2(atlTraceGeneral, 0, "%i %f %f in\n", i, vwert[0], vwert[1]);
                        j = 0;
                        break;
                    default:
                        ATLTRACE2(atlTraceGeneral, 0, "%i %f %f unknown\n", i, vwert[0], vwert[1]);
                        break;
                }
                //                ATLTRACE2(atlTraceGeneral, 0, "%i %f %f\n",i, vwert[0], vwert[1]);
            }
#endif
            pathlist.clear();
            HSpline *sphptr = nullptr;
            HCP *lastcp = nullptr;
            BOOL peaked_cps = FALSE;
            Vector pos, firstpos;
            int numpoints = path->npts - 1;
            if (path->closed) {
                if (numpoints == 12) // == 12 pure rectangle
                    peaked_cps = TRUE;
            }
            float *wert = &path->pts[0];
            temppfad.inbias.Set(0);
            temppfad.pos.Set(wert[0], wert[1], 0);
            temppfad.outbias.Set(wert[2], wert[3], 0);
            pathlist.push_back(temppfad);
            for (int i = 2; i < numpoints; i += 3) {
                wert = &path->pts[i * 2LL];
                temppfad.inbias.Set(wert[0], wert[1], 0);
                temppfad.pos.Set(wert[2], wert[3], 0);
                temppfad.outbias.Set(wert[4], wert[5], 0);
                pathlist.push_back(temppfad);
            }
            size_t path_size = pathlist.size();
            if (path->closed) {
                Vector p1, p2;
                p1 = pathlist[path_size - 2].pos;
                p2 = pathlist[path_size - 1].pos;
                if (p1 == p2) {
                    path_size--;
                }
            }
            if (!m_parameters.importaspathonly && path->closed) {
                TPFAD t1;
                for (size_t i = 0; i < path_size; ++i) {
                    t1.path.push_back(pathlist[i]);
                }
                tempshape.pfad.push_back(t1);
                continue;
            }
            firstpos = pathlist[0].pos;
            pos = pathlist[1].pos;
            sphptr = hmc->StartSpline(&firstpos, &pos);
            splinelist.push_back(sphptr);
            pathlist[0].cp = sphptr->GetHeadCP();
            lastcp = sphptr->GetHeadCP()->GetNext();
            pathlist[1].cp = lastcp;
            for (size_t i = 2; i < path_size; ++i) {
                pos = pathlist[i].pos;
                lastcp = hmc->AddCP(lastcp, &pos);
                pathlist[i].cp = lastcp;
            }
            float alpha, gamma, magnitude;
            if (path->closed) {
                hmc->AttachCPs(sphptr->GetHeadCP(), lastcp);
            }
            Vector temp = pathlist[0].outbias - pathlist[0].pos;
            lastcp = sphptr->GetHeadCP();
            if (peaked_cps) {
                lastcp->SetPeaked();
            } else {
                if (path->closed) {
                    if (temp.x != 0 || temp.y != 0) {
                        temp *= 3;
                        temp.Negate();
                        lastcp->ComputeInBias(temp, alpha, gamma, magnitude);
                        if (hash_math::abs(alpha) > .1f)
                            lastcp->SetInAlpha(alpha);
                        lastcp->SetInGamma(gamma);
                        lastcp->SetInMagnitude(magnitude);
                    }
                } else {
                    if (temp.x != 0 || temp.y != 0) {
                        temp *= 3;
                        lastcp->ComputeOutBias(temp, alpha, gamma, magnitude);
                        if (hash_math::abs(alpha) > .1f)
                            lastcp->SetOutAlpha(alpha);
                        lastcp->SetOutGamma(gamma);
                        lastcp->SetOutMagnitude(magnitude);
                    }
                }
            }
            path_size--;
            if (path->closed && !peaked_cps) {
                temp = pathlist[path_size].inbias - pathlist[path_size].pos;
                if (temp.x != 0 || temp.y != 0) {
                    temp *= 3;
                    lastcp->ComputeOutBias(temp, alpha, gamma, magnitude);
                    if (hash_math::abs(alpha) > .1f)
                        lastcp->SetOutAlpha(alpha);
                    lastcp->SetOutGamma(gamma);
                    lastcp->SetOutMagnitude(magnitude);
                }
            }
            for (size_t i = 1; i < path_size; ++i) {
                if (peaked_cps) {
                    pathlist[i].cp->SetPeaked();
                } else {
                    temp = pathlist[i].inbias - pathlist[i].pos;
                    if (temp.x != 0 || temp.y != 0) {
                        temp *= 3;
                        pathlist[i].cp->ComputeOutBias(temp, alpha, gamma, magnitude);
                        if (hash_math::abs(alpha) > .1f)
                            pathlist[i].cp->SetOutAlpha(alpha);
                        pathlist[i].cp->SetOutGamma(gamma);
                        pathlist[i].cp->SetOutMagnitude(magnitude);
                    }
                    temp = pathlist[i].outbias - pathlist[i].pos;
                    if (temp.x != 0 || temp.y != 0) {
                        temp *= 3;
                        temp.Negate();
                        pathlist[i].cp->ComputeInBias(temp, alpha, gamma, magnitude);
                        if (hash_math::abs(alpha) > .1f)
                            pathlist[i].cp->SetInAlpha(alpha);
                        pathlist[i].cp->SetInGamma(gamma);
                        pathlist[i].cp->SetInMagnitude(magnitude);
                    }
                }
            }
            if (!path->closed) {
                temp = pathlist[path_size].inbias - pathlist[path_size].pos;
                if (temp.x != 0 || temp.y != 0) {
                    temp *= 3;
                    pathlist[path_size].cp->ComputeOutBias(temp, alpha, gamma, magnitude);
                    if (hash_math::abs(alpha) > .1f)
                        pathlist[path_size].cp->SetInAlpha(alpha);
                    pathlist[path_size].cp->SetOutGamma(gamma);
                    pathlist[path_size].cp->SetOutMagnitude(magnitude);
                }
            }
            String groupname = "SVGPath_" + (String)pathnumber;
            HGroup *group = hmc->CreateGroup(groupname);
            for (lastcp = sphptr->GetHeadCP(); lastcp; lastcp = lastcp->GetNext()) {
                group->AddCP(lastcp);
                if (lastcp->IsLoop())
                    break;
            }
        }
        if (!tempshape.pfad.empty()) {
            shapelist.push_back(tempshape);
        }
    }
    nsvgDelete(g_image);

    if (!splinelist.empty()) {
        if (m_hprogressbar) {
            if (shapelist.empty())
                m_hprogressbar->SetProgress(66);
            else
                m_hprogressbar->SetProgress(50);
            m_hprogressbar->SetMessage2("Move to location");
        }
        //Need Y-Axis Flip
        String groupname = "TempGroup";
        HGroup *group = hmc->CreateGroup(groupname);
        for (auto &i: splinelist) {
            for (HCP *lastcp = i->GetHeadCP(); lastcp; lastcp = lastcp->GetNext()) {
                group->AddCP(lastcp);
                if (lastcp->IsLoop())
                    break;
            }
        }
        int groupcount = 0;
        Vector groupcenter(0.F);
        for (HGroupCP *currentgroupcp = group->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
            groupcenter += *currentgroupcp->GetCP()->GetPosition();
            groupcount++;
        }
        groupcenter /= (float)groupcount;
        Matrix34 *gmatrix = group->GetMatrix();
        Matrix34 nmatrix = TranslateV(groupcenter) * *gmatrix * ScaleV(Vector(1, -1, 1)) * gmatrix->Inverse() * TranslateV(-groupcenter);
        for (HGroupCP *currentgroupcp = group->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
            HCP *cp = currentgroupcp->GetCP();
            cp = currentgroupcp->GetCP();
            Vector pos = *cp->GetPosition();
            pos *= nmatrix;
            cp->SetPosition(&pos);
        }
        if (m_parameters.center) {
            Matrix34 nmatrix1 = TranslateV(-groupcenter) * *gmatrix;
            for (HGroupCP *currentgroupcp = group->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
                HCP *cp = currentgroupcp->GetCP();
                cp = currentgroupcp->GetCP();
                Vector pos = *cp->GetPosition();
                pos *= nmatrix1;
                cp->SetPosition(&pos);
            }
        }
        HModelCache::DeleteHandle(group);
    }
    if (!shapelist.empty()) {
        if (m_hprogressbar) {
            m_hprogressbar->SetProgress(50);
            m_hprogressbar->SetMessage2("Build Model");
        }
        HGroup *group = nullptr;
        BuildClosedModel(shapelist, hmc, &group);
        if (m_hprogressbar) {
            m_hprogressbar->SetProgress(80);
            m_hprogressbar->SetMessage2("Move to location");
        }
        if (group) {
            int groupcount = 0;
            Vector groupcenter(0.F);
            for (HGroupCP *currentgroupcp = group->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
                groupcenter += *currentgroupcp->GetCP()->GetPosition();
                groupcount++;
            }
            groupcenter /= (float)groupcount;
            Matrix34 *gmatrix = group->GetMatrix();
            Matrix34 nmatrix = TranslateV(groupcenter) * *gmatrix * ScaleV(Vector(1, -1, 1)) * gmatrix->Inverse() * TranslateV(-groupcenter);
            for (HGroupCP *currentgroupcp = group->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
                HCP *cp = currentgroupcp->GetCP();
                cp = currentgroupcp->GetCP();
                Vector pos = *cp->GetPosition();
                pos *= nmatrix;
                cp->SetPosition(&pos);
            }
            if (m_parameters.center) {
                groupcenter *= Vector(1, 1, 0);
                Matrix34 nmatrix1 = TranslateV(-groupcenter) * *gmatrix;
                for (HGroupCP *currentgroupcp = group->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
                    HCP *cp = currentgroupcp->GetCP();
                    cp = currentgroupcp->GetCP();
                    Vector pos = *cp->GetPosition();
                    pos *= nmatrix1;
                    cp->SetPosition(&pos);
                }
            }
        }
    }
    if (m_hprogressbar) {
        m_hprogressbar->SetProgress(100);
    }
    hmc->Update();
    GetHProject()->DeselectAll();
    if (newmodel)
        hmc->OpenView();
    else
        hmc->ZoomFit();

    RefreshAllTrees();
    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }
}

static void SubdivToModel(const Subdiv *subdiv, HModelCache *mch, BOOL makegroup, HGroup **newgroup);
static void SetBiases(HCP *cp, const Vector &t1, const Vector &t2);

void CHxtApp::BuildClosedModel(const std::vector<SHAPE> &shapelist, HModelCache *hmc, HGroup **group) {
    AIParser parser;
    for (auto &i: shapelist) {
        AICompoundPath *curcpath = new AICompoundPath;
        parser.objects.AddBack(curcpath);
        for (auto &j: i.pfad) {
            AIPath *curpath = new AIPath();
            curpath->close = TRUE;
            curpath->stroke = TRUE;
            curpath->fill = TRUE;
            curpath->clockwise = FALSE;
            const PFAD tpa = j.path[0];
            AIPathOp *pop = new AIPathOp(AIPMoveto, FALSE, tpa.pos.x, tpa.pos.y);
            //            gtrace("p %f %f\n", tpa.pos.x, tpa.pos.y);
            curpath->pathops.AddBack(pop);
            for (size_t k = 1; k < j.path.size(); ++k) {
                const PFAD tp = j.path[k];
                const PFAD tp1 = j.path[k - 1];
                //                gtrace("o %f %f i %f %f p %f %f\n", tp1.outbias.x, tp1.outbias.y, tp.inbias.x, tp.inbias.y, tp.pos.x, tp.pos.y);
                pop = new AIPathOp(AIPCurveto, FALSE, tp1.outbias.x, tp1.outbias.y, tp.inbias.x, tp.inbias.y, tp.pos.x, tp.pos.y);
                curpath->pathops.AddBack(pop);
            }
            curcpath->members.AddBack(curpath);
        }
    }
    //    parser.DumpObjects("d:\\test16\\svg_ob.txt");
    auto *subdiv = new Subdiv();
    PolygonalAreaArray *areas = BuildAIEdges(subdiv, &parser);
    if (areas == nullptr) {
        delete subdiv;
        return;
    }

    if (!m_parameters.m_fronts)
        m_parameters.m_bevfronts = FALSE;
    if (!m_parameters.m_sides)
        m_parameters.m_bevsides = FALSE;
    if (!m_parameters.m_backs)
        m_parameters.m_bevbacks = FALSE;

    float inset = m_parameters.m_bevamt * 0.1F;
    const BOOL anybevels = m_parameters.m_bevfronts || m_parameters.m_bevsides || m_parameters.m_bevbacks;
    const BOOL inward = m_parameters.m_bevinward;
    if (anybevels) {
        const float maxinset = areas->MaxInset(inward);
        if (inset >= maxinset) {
            const float suggest_inset = 0.9F * maxinset;
            const double o_i = inset / 0.1;
            const double n_i = suggest_inset / 0.1;
            CString msg;
            msg.Format("The specified inset (%g) will likely produce edge overlaps. Do you want to use the maximum suggested inset (%g) instead?", o_i, n_i);
            if (AfxMessageBox(msg, MB_YESNO) == IDYES) {
                inset = suggest_inset;
                SetRegistryValue("SVG HXT", "BevAmount", RoundValue(inset * 10.F, 0.1F));
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
    if (m_parameters.m_subdivkind != SVGParameters::SUB_NONE) {
        flags |= EX_SUB;
        if (m_parameters.m_subdivkind == SVGParameters::SUB_ALL)
            flags |= EX_SUB_ALL;
    }

    Extrude(subdiv, areas, flags, m_parameters.m_depth, inset);
    SubdivToModel(subdiv, hmc, TRUE, group);

    delete areas;
    delete subdiv;
}

static void UpdateVertRoots(HCP **vertroots, const int i, HCP *cp, HModelCache *mch, HGroup **pgroup, BOOL isloopback) {
    HCP *rootcp = vertroots[i];
    if (rootcp == nullptr) {
        vertroots[i] = cp;
    } else {
        isloopback = mch->AttachCPs(rootcp, cp);
    }
    // Note: if AttachCPs causes loopback, A:M deletes tail cp
    // before attaching, so can't add it to group
    if (!isloopback)
        (*pgroup)->AddCP(cp);
}

static void SubdivToModel(const Subdiv *subdiv, HModelCache *mch, BOOL makegroup, HGroup **newgroup) {
    if (mch->GetHeadInstance()) // There is at least one visible model, so lets selected the points
        makegroup = TRUE;
    GetHProject()->DeselectAll(); // deselect the current group since we're making a new one
    const int nv = subdiv->NumPoints();
    HCP **vertroots = new HCP*[nv];
    for (int j = 0; j < nv; ++j) {
        vertroots[j] = nullptr;
    }
    if (makegroup) {
        const String groupname = "SVG_Import";
        *newgroup = mch->CreateGroup(groupname);
    }

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
        if (p0 == p) {
            do {
                si.GetNext();
                if (si.Cur() == nullptr)
                    continue;
                e = si.Cur();
                i = e->Dst();
                ASSERT(0 <= i && i < nv);
                p = subdiv->Coords(i);
            } while (p0 == p);
        }
        HSpline *sh = mch->StartSpline(&p0, &p);
        HCP *firstcp = sh->GetHeadCP();
        UpdateVertRoots(vertroots, i0, firstcp, mch, newgroup, FALSE);
        HCP *cp = firstcp->GetNext();
        UpdateVertRoots(vertroots, i, cp, mch, newgroup, FALSE);
        si.GetNext();
        int nedges = 1;
        for (; si.Cur() != nullptr; si.GetNext()) {
            nedges++;
            e = si.Cur();
            i = e->Dst();
            ASSERT(0 <= i && i < nv);
            p = subdiv->Coords(i);
            cp = mch->AddCP(cp, &p);
            UpdateVertRoots(vertroots, i, cp, mch, newgroup, i == i0);
        }
#ifdef _DEBUG
        int count_cp = 0;
        for (HCP *lastcp = sh->GetHeadCP(); lastcp; lastcp = lastcp->GetNext()) {
            count_cp++;
            if (lastcp->IsLoop())
                break;
        }
        if (count_cp < 2) {
            ASSERT(false && "Invalid Spline");
        }
#endif
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

    delete[] vertroots;
}

// Compute A:M biases for cp, so that the tangent leading into t2 from
// previous cp is t1, and the tangent out of cp to next cp is t1.
static void SetBiases(HCP *cp, const Vector &t1, const Vector &t2) {

    //    Vector pos = *cp->GetPosition();
    //    gtrace("p %f %f i %f %f o %f %f\n", pos.x, pos.y, t1.x, t1.y, t2.x, t2.y);
    cp->SetSmooth();
    const Vector tin(-t1.x, -t1.y, -t1.z);
    const Vector tout(-t2.x, -t2.y, -t2.z);
    float ina, ing, inm, outa, outg, outm;

    cp->ComputeInBias(tin, ina, ing, inm);
    if (hash_math::abs(ina) > .1f)
        cp->SetInAlpha(ina);
    cp->SetInGamma(ing);
    cp->SetInMagnitude(inm);

    cp->ComputeOutBias(tout, outa, outg, outm);
    if (hash_math::abs(outa) > .1f)
        cp->SetOutAlpha(outa);
    cp->SetOutGamma(outg);
    cp->SetOutMagnitude(outm);
}
