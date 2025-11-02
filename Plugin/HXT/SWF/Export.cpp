// Dan  1/25/01  \Dan90\Plugin\HXT\Ply\Export.cpp
// ZPiDER 2001-11 http://www.kci-group.com/z
// ZPiDER 2002-08 http://www.kci-group.com/z

// ToDo:
// non camera views could use rinfo to get size. Use case eddie in an action.
// check filling!! (swish compatibility)
// http://www.half-serious.com/swf/format/examples-shapes/index.html

// Release notes:
// 9/19/06 camera picked from a combo now.

#include "StdAfx.h"

#include "Hxt.h"
#include "HashFile.h"
#include "HashArra.h"
#include "ExportActionDialog.h"

#include "Matrix34.h"
#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"
#include "SDK/HCamera.h"
#include "SDK/HLight.h"
#include "SDK/HProgres.h"
#include "RGBByte.inl"
#include "./Flash/F3SDK.h"

extern "C" {
#include "./gpc/gpc.h"
}

int currentFrame;

int m_style_outline_color;
int m_style_outline_thickness;

int m_frame_range;
int m_frame_from;
int m_frame_to;
int m_frame_stepping;

String m_camera_name;
int f_cameraindex;
int m_camera_perspective;
int m_camera_zero;

int offsetX;
int offsetY;
int sizeX;
int sizeY;

int m_lights_parallel;

int m_culling_occlusion;
int m_culling_mapsize;
int m_culling_minarea;
int m_culling_backface;

int m_flat;
int m_flat_spec;
float m_flat_minedgelength;

int m_safe_frame1;
int m_safe_all;

int m_preview_frame;

BOOL CHxtApp::OnExportActionCache(HActionCache *hac) {
    // get model for action
    HModelCache *hmc = hac->GetDefaultModelCache();

    // cant get model for action -> error message
    if (hmc == nullptr) {
        CString msg, title;
        msg.LoadString(IDS_ACTIONHASNOMODELASSIGNED);
        String temp = msg;
        temp.Replace("%1", hac->GetName());
        msg = temp.Get();
        title.LoadString(IDS_EXPORTTITLE);

        MessageBox(GetMainApplicationWnd(), msg, title, MB_OK);
        return FALSE;
    }

    HModel *hm = hac->EditWithModelCache(hmc);
    HChor *chor = hm->GetChor();

    const Time totaltime = hac->GetTotalTime(); // KB
    const BOOL result = ExportDialog(chor, hmc->GetName(), totaltime);

    hac->EndEditWithModelCache(hm);
    if (result == FALSE)
        return TRUE;
    GetHProject()->UpdateAllViews();
    return TRUE;
}

BOOL CHxtApp::OnExportChor(HChor *chor) {
    const Time totaltime = chor->GetTotalTime()->GetValue();
    return ExportDialog(chor, chor->GetName(), totaltime);
}

CExportActionDialog *cdlg;

BOOL CHxtApp::ExportDialog(HChor *chor, char *name, const Time &length) {
    ASSERT(false); //goto ShowDialog !
showDialog:
    cdlg = new CExportActionDialog(name, chor, this);
    const INT_PTR dlgRes = cdlg->DoModal();
    if (dlgRes != IDOK)
        return TRUE; // cancel/x pressed
    if (cdlg->m_preview) {
        Export(chor, name, length, TRUE);
        ShellExecute(nullptr, nullptr, cdlg->m_filename.Get(), nullptr, nullptr, SW_SHOWDEFAULT);
        goto showDialog;
    }
    return Export(chor, name, length, FALSE);
}

BOOL CHxtApp::Export(HChor *chor, char *name, const Time &length, const BOOL previewMode) {
    currentFrame = 0;

    // ----------------------------------------------------------------------------------------------------

    CWaitCursor wait;
    m_iemp.m_subtype = (SubType)cdlg->m_subtype;

    // get style attributes from dialog

    m_style_outline_color = cdlg->m_style_outline_color;
    m_style_outline_thickness = cdlg->m_style_outline_thickness;

    m_camera_name = cdlg->m_camera_name;
    f_cameraindex = cdlg->m_cameraindex;
    m_camera_perspective = cdlg->m_camera_perspective;
    m_camera_zero = cdlg->m_camera_zero;

    sizeX = 7000;
    sizeY = 5250;
    offsetX = offsetY = 0;
    if (!m_camera_zero) {
        offsetX = sizeX / 2;
        offsetY = sizeY / 2;
    }

    m_lights_parallel = cdlg->m_lights_parallel;

    m_culling_occlusion = cdlg->m_culling_occlusion;
    m_culling_mapsize = cdlg->m_culling_mapsize;
    m_culling_minarea = cdlg->m_culling_minarea;
    m_culling_backface = cdlg->m_culling_backface;

    m_flat = cdlg->m_flat;
    m_flat_spec = cdlg->m_flat_spec;
    m_flat_minedgelength = cdlg->m_flat_minedgelength;

    m_safe_frame1 = cdlg->m_safe_frame1;
    m_safe_all = cdlg->m_safe_all;

    m_frame_range = cdlg->m_frame_range;
    m_frame_from = cdlg->m_frame_from;
    m_frame_to = cdlg->m_frame_to;
    m_frame_stepping = cdlg->m_frame_stepping;
    if (m_frame_stepping == 0)
        m_frame_stepping = 1;

    m_preview_frame = cdlg->m_preview_frame;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    Time endtime = length;
    Time starttime;
    Time steptime;
    steptime.SetFrame(1, fps);

    if (previewMode) {
        m_frame_from = m_preview_frame;
        m_frame_to = m_preview_frame;
        m_frame_stepping = 1;
    }

    // custom frame range selected

    if (m_frame_range == 0) {
        // nice input values

        if (m_frame_to < m_frame_from)
            m_frame_stepping = -abs(m_frame_stepping);
        else
            m_frame_stepping = abs(m_frame_stepping);

        endtime.SetFrame(m_frame_to, fps);
        starttime.SetFrame(m_frame_from, fps);
        steptime.SetFrame(m_frame_stepping, fps);
    }

    const String basefilename = cdlg->m_filename;

    FObjCollection flashObjects;
    StartSWF(flashObjects);

    int steps = (endtime.GetFrame(fps) - starttime.GetFrame(fps)) / steptime.GetFrame(fps);

    if (m_safe_frame1) {
        const Time time = starttime;
        const int frame = time.GetFrameInt(fps);
        const String filename = basefilename.NumberFrame(frame);
        IEPolyModel *model = chor->BuildExportModel(&m_iemp, time, filename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }
        DeleteIEModel(model);
    }

    const int totalitems = steps;
    int currentitem = 0;

    for (Time time = starttime; steps >= 0; time += steptime, steps--) // time.StepFrame(fps))
    {
        hp->SetTime(time);
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);

        bool rebuild = true;
        int rebuildCount = 0;

        IEPolyModel *model = nullptr;

        while (rebuild && rebuildCount < 10) {
            rebuildCount++;

            model = chor->BuildExportModel(&m_iemp, time, filename.Get());

            if (model == nullptr) {
                ReportExportError(filename);
                return FALSE;
            }

            rebuild = false;

            if (m_safe_all) {
                IEPolyModel *model2 = chor->BuildExportModel(&m_iemp, time, filename.Get());

                if (model2 == nullptr || model->m_vertexlist.GetSize() != model2->m_vertexlist.GetSize()) {
                    rebuild = true;
                } else {
                    for (int i = 0; i < model->m_vertexlist.GetSize() && !rebuild; i++) {
                        Vector &v = model->m_vertexlist.ElementAt(i);
                        const Vector &v2 = model2->m_vertexlist.ElementAt(i);
                        if (v != v2)
                            rebuild = true;
                    }
                }
            }
        }

        String logfilename = filename.GetWithoutSuffix() + ".txt";
        const BOOL result = ExportSWF(flashObjects, model, chor, time, logfilename, totalitems, currentitem++);
        DeleteIEModel(model);

        if (!result) {
            ReportExportError(filename);
            return TRUE;
        }
        currentFrame++;
    }

    FinishSWF(flashObjects, cdlg->m_filename);
    hp->SetTime(starttime);
    GetHProject()->UpdateAllViews();
    return TRUE;
}

void CHxtApp::ReportExportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_EXPORTTITLE);
    CString text;
    text.LoadString(IDS_ERROREXPORTINGMODEL);
    String temp = text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

BOOL CHxtApp::ExportSWF(FObjCollection &flashObjects, IEPolyModel *model, HChor *chor, const Time time, const String &filename, const int totalitems, const int currentitem) {
    FileStream fs;

    //DD	if (!fs.Open( (String)filename, FileMode::HS_BINARY | FileMode::HS_STORE))
    //DD		return FALSE;

    m_hprogressbar = GetProgressBar();
    if (!m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        m_hprogressbar->SetMessage1(text);
    }

    SavePolys(flashObjects, fs, model, chor, time, m_hprogressbar, totalitems, currentitem);

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }

    return TRUE;
}

//////////////////////////////////////////////// SWF File Processing /////

void CHxtApp::StartSWF(FObjCollection &flashObjects) {
    const FColor bgcol = FColor(0xcc, 0xcc, 0xcc);

    auto *background = new FCTSetBackgroundColor(new FColor(bgcol));
    flashObjects.AddFObj(background);
}

void CHxtApp::FinishSWF(FObjCollection &flashObjects, const String &filename) {
    flashObjects.CreateMovie(filename.Get(), sizeX, sizeY, 12);
}

//////////////////////////////////////////////// 3D Util /////////////

float CHxtApp::PointDistance(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2) {
    const float xd = x2 - x1;
    const float yd = y2 - y1;
    const float zd = z2 - z1;
    const float d = hash_math::sqrt(xd * xd + yd * yd + zd * zd);
    //	hash_math::pow(n, exp);

    return abs(d);
}

int magnify = 100;

///////////////////////////////////////////////// Winding Check

BOOL isRightOfLine(const float x1, const float y1, const float x2, const float y2, const float px, const float py) {
    if (x1 == x2)
    //	if (hash_math::abs(x1-x2) < 1)
    {
        //		if ((y1 < y2) && (px > x1))	return true;
        //		if ((y1 > y2) && (px < x1)) return true;
        if (y1 < y2 && px < x1)
            return true;
        if (y1 > y2 && px > x1)
            return true;
        return false;
    }

    const float gy = (y2 - y1) / (x2 - x1) * px + y1 - (y2 - y1) / (x2 - x1) * x1;

    if (x2 > x1 && py > gy)
        return true;
    if (x2 < x1 && py < gy)
        return true;
    return false;
}

BOOL isRightOfLine(const Vector &v1, const Vector &v2, const Vector &p) {
    return isRightOfLine(v1.x, v1.y, v2.x, v2.y, p.x, p.y);
}

BOOL isRightOfLine(const Vector &v1, const Vector &v2, const float px, const float py) {
    return isRightOfLine(v1.x, v1.y, v2.x, v2.y, px, py);
}

///////////////////////////////////////////////// Tree Tools

HHashObject *getChildByName(HHashObject *parent, const char *name) {
    HHashObject *ho = parent->GetChild();

    int stopper = 100;
    while (stopper-- > 0 && ho != nullptr) {
        if (_stricmp(ho->GetName(), name) == 0)
            return ho;
        ho = ho->GetSibling();
    }
    return nullptr;
}

IEBone *findBone(IEBone *current, const char *name, const int maxDepth) {
    if (current == nullptr)
        return nullptr; // break if null reached
    if (_stricmp(current->m_name, name) == 0)
        return current; // break if bone found
    if (maxDepth == 0)
        return nullptr; // break if searchdepth reached

    IEBone *bone = findBone(current->m_sibling, name, maxDepth);
    if (bone != nullptr)
        return bone; // break if the child knows the wanted bone 
    bone = findBone(current->m_child, name, maxDepth - 1);
    if (bone != nullptr)
        return bone; // break if the sibling knows the wanted bone

    return nullptr; // bone not found here.
}

////////////////////////////////////////////////// Occlusion Mapping

int occMapWidth = 500;
int occMapHeight = 500;
float occMapScale = 8;

int fillTriangle(bool *occMap, const Vector *v1, const Vector *v2, const Vector *v3) {
    const float v1x = v1->x * occMapScale + occMapWidth / 2;
    const float v1y = v1->y * occMapScale + occMapHeight / 2;
    float v2x = v2->x * occMapScale + occMapWidth / 2;
    float v2y = v2->y * occMapScale + occMapHeight / 2;
    float v3x = v3->x * occMapScale + occMapWidth / 2;
    float v3y = v3->y * occMapScale + occMapHeight / 2;

    // calculate drawing bounds

    int minX = occMapWidth;
    int minY = occMapHeight;
    int maxX = 0;
    int maxY = 0;

    if (minX > v1x)
        minX = v1x;
    if (minY > v1y)
        minY = v1y;
    if (minX > v2x)
        minX = v2x;
    if (minY > v2y)
        minY = v2y;
    if (minX > v3x)
        minX = v3x;
    if (minY > v3y)
        minY = v3y;
    if (minX < 0)
        minX = 0;
    if (minY < 0)
        minY = 0;

    if (maxX < v1x)
        maxX = v1x;
    if (maxY < v1y)
        maxY = v1y;
    if (maxX < v2x)
        maxX = v2x;
    if (maxY < v2y)
        maxY = v2y;
    if (maxX < v3x)
        maxX = v3x;
    if (maxY < v3y)
        maxY = v3y;
    if (maxX > occMapWidth)
        maxX = occMapWidth;
    if (maxY > occMapHeight)
        maxY = occMapHeight;

    // tri is wrongly wound -> flip

    if (isRightOfLine(*v1, *v2, *v3)) {
        const float tx = v2x;
        const float ty = v2y;
        v2x = v3x;
        v2y = v3y;
        v3x = tx;
        v3y = ty;
    }

    int newOcc = 0;

    // the face center is on a unoccluded area (for small patches)

    const int centerx = (v1x + v2x + v3x) / 3;
    const int centery = (v1y + v2y + v3y) / 3;

    if (centerx >= minX && centerx <= maxX && centery >= minY && centery <= minY && !occMap[(int)(centerx + centery * occMapWidth)])
        newOcc += 20;

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            if (!occMap[x + y * occMapWidth] && !isRightOfLine(v1x, v1y, v2x, v2y, x, y) && !isRightOfLine(v2x, v2y, v3x, v3y, x, y) && !isRightOfLine(v3x, v3y, v1x, v1y, x, y)) {
                newOcc++;
                occMap[y * occMapWidth + x] = true;
            }
        }
    }

    return newOcc;
}

//////////////////////////////////////////////// FRAME EXPORTING /////////////

Matrix34 cameraMatrix;
BOOL perspective;

void cameraPerspective(Vector &vertex) {
    // perspective distortion

    if (perspective) {
        if (vertex.z < 0) {
            vertex.x /= vertex.z / 100;
            vertex.y /= vertex.z / 100;
        }
    } else {
        vertex.x *= -1;
        vertex.y *= -1;
    }
}

void cameraTransformationOnly(Vector &vertex) {
    vertex *= cameraMatrix;
    vertex.Negate();
    vertex.x = -vertex.x;
}

void cameraTransformation(Vector &vertex) {
    cameraTransformationOnly(vertex);
    cameraPerspective(vertex);
}

int runCount = 0;

void CHxtApp::SavePolys(FObjCollection &flashObjects, FileStream &fs, IEPolyModel *model, HChor *chor, Time time, HProgressBar *progressbar, int totalitems, int currentitem) {
    HProject *hp = GetHProject();
    float fps = hp->GetFPS();

    String message = "Preparing " + String(time.GetFrameInt(fps));
    if (totalitems == 0)
        totalitems = 1;
    float barstart = currentitem * 100.F / (totalitems + 1);
    float barspan = 100.F / totalitems;
    progressbar->SetMessage2(message.Get());
    progressbar->SetProgress(barstart);

    float nearclip = 0.5F;

    // get camera

    int cameraindex = 1; //0 is for IDS_NONE;
    HCamera *camera = chor->GetChildCamera();
    while (camera && cameraindex != f_cameraindex) {
        cameraindex++;
        camera = camera->GetNextCameraInChor();
    }

    perspective = false;

    model->BuildNormalList(2.F);

    CMap<int, int, float, float> facingMap; // poly number -> facing (cameraDir.Dot(normal))
    facingMap.InitHashTable(997);

    Vector cameraPos = Vector(0, 0, 0);
    Vector cameraDir = Vector(0, 0, -1);

    int pnum = model->m_polyarray.GetSize();
    int p;

    if (camera) {
        HTransformProperty *htransform = camera->GetTransform();

        cameraMatrix = Matrix34(TSQ(htransform->GetTranslate()->GetValue(time), htransform->GetScale()->GetValue(time), htransform->GetRotate()->GetValue(time)));
        cameraMatrix = cameraMatrix.InvertRotateTranslate();

        cameraDir *= cameraMatrix;
        cameraPos *= cameraMatrix;
        cameraDir -= cameraPos; // TODO: check if invert needed, etc.!

        cameraDir.x = -cameraDir.x;
        cameraPos.x = -cameraPos.x;
    }

    // calculate lighting -----------------------------------------------------------------------------------

    CMap<int, int, float, float> luminanceMap; // poly number -> luminance
    luminanceMap.InitHashTable(997);

    // get light

    HLightListNode *lightNode = chor->GetHeadAllLightList();

    if (!m_flat) {
        for (p = 0; p < pnum; p++) {
            IEPoly *poly = model->m_polyarray.GetAt(p);

            Vector *v1 = &model->m_vertexlist.ElementAt(poly->m_vertexid[0]);
            Vector *v2 = &model->m_vertexlist.ElementAt(poly->m_vertexid[1]);
            Vector *v3 = &model->m_vertexlist.ElementAt(poly->m_vertexid[2]);
            Vector *v4 = &model->m_vertexlist.ElementAt(poly->m_vertexid[3]);

            Vector *n1 = &model->m_normallist.ElementAt(poly->m_normalid[0]);
            Vector *n2 = &model->m_normallist.ElementAt(poly->m_normalid[1]);
            Vector *n3 = &model->m_normallist.ElementAt(poly->m_normalid[2]);
            Vector *n4 = &model->m_normallist.ElementAt(poly->m_normalid[3]);

            Vector v = (*v1 + *v2 + *v3 + *v4) / 4;
            Vector n = (*n1 + *n2 + *n3 + *n4) / 4;

            float luminance = 0;
            HLightListNode *currLightNode = lightNode;

            if (!currLightNode) // default light
            {
                luminance += (n.x + 1) / 2;
            }

            while (currLightNode) {
                Vector l;
                //                Vector ls;

                HLight *light = currLightNode->GetLight();

                HTransformProperty *htransform = light->GetTransform();
                l = htransform->GetTranslate()->GetValue(time);

                Vector vl1 = l - v; // poly->light

                if (m_lights_parallel == 1) {
                    Quaternion lr;
                    vl1 = Vector(0, 0, -1);
                    vl1 *= (Matrix34)RotateVector(lr);
                }

                vl1.Normalize();

                float lu = n.Dot(vl1);

                if (lu > 0)
                    luminance += (1 - (1 - lu) * (1 - lu)) * light->GetIntensity()->GetValue(time); // inverse quadratic diffuse falloff

                currLightNode = currLightNode->GetNextLightListNode();

                if (currLightNode == lightNode)
                    currLightNode = nullptr;
            }

            luminanceMap.SetAt(p, luminance);

            facingMap.SetAt(p, cameraDir.Dot(n));
        }
    } else {
        for (p = 0; p < pnum; p++) {
            facingMap.SetAt(p, 0);
        }
    }

    // apply camera transformation --------------------------------------------------------------------------

    int vnum = model->m_vertexlist.GetSize();
    int v;

    if (camera) {
        // viewing angle transformation

        if (m_camera_perspective == 1)
            perspective = true;

        for (v = 0; v < vnum; v++) {
            // viewing angle transformation

            cameraTransformation(model->m_vertexlist.ElementAt(v));
        }
    } else {
        //DD		fs << "WARNING: Camera not found.";
    }

    // collect polys & calculate distance to camera (depth) -------------------------------------------------

    CMap<int, int, float, float> depthMap; // poly number -> depth
    depthMap.InitHashTable(997);

    CArray<int, int> order; // stores poly numbers

    for (p = 0; p < pnum; p++) {
        IEPoly *poly = model->m_polyarray.GetAt(p);

        Vector &va1 = model->m_vertexlist.ElementAt(poly->m_vertexid[0]);
        Vector &v2 = model->m_vertexlist.ElementAt(poly->m_vertexid[1]);
        Vector &v3 = model->m_vertexlist.ElementAt(poly->m_vertexid[2]);
        Vector &v4 = model->m_vertexlist.ElementAt(poly->m_vertexid[3]);

        depthMap.SetAt(p, (va1.z + v2.z + v3.z + v4.z) / 4);
        order.Add(p);
    }

    // sort polys by depth ----------------------------------------------------------------------------------
    // TODO; implement faster sorting. currently shakersort

    BOOL sorting = true;
    int p1, p2;
    float d1, d2;
    while (sorting) {
        sorting = false;
        int i;
        for (i = 0; i < pnum - 1; i++) {
            p1 = order.GetAt(i);
            p2 = order.GetAt(i + 1);
            depthMap.Lookup(p1, d1);
            depthMap.Lookup(p2, d2);
            if (d1 < d2) // if next neighbour is smaller
            {
                order.SetAt(i, p2); // exchange with neighbour
                order.SetAt(i + 1, p1);
                sorting = true;
            }
        }
        for (i = pnum - 1; i > 0; i--) {
            p1 = order.GetAt(i - 1);
            p2 = order.GetAt(i);
            depthMap.Lookup(p1, d1);
            depthMap.Lookup(p2, d2);
            if (d1 < d2) // if next neighbour is smaller
            {
                order.SetAt(i - 1, p2); // exchange with neighbour
                order.SetAt(i, p1);
                sorting = true;
            }
        }
    }

    // occlusion culling ------------------------------------------------------------------------------------

    if (m_culling_occlusion) {
        occMapWidth = occMapHeight = m_culling_mapsize;

        bool *occMap = new bool[(occMapWidth + 1) * (occMapHeight + 1)];

        //	for (int pd1=pnum; pd1>=0; pd1--)	// draw polys front to back on occlusion map
        for (int pd1 = 0; pd1 < pnum; pd1++) // draw polys front to back on occlusion map
        // TODO: why is the order inverted ??? check if drawing oder ok ..
        {
            p = order.GetAt(pd1);
            IEPoly *poly = model->m_polyarray.GetAt(p);
            Attr &attr = model->m_attrlist.ElementAt(poly->m_attrid);

            if (attr.m_transparency == 0) {
                Vector *va1 = &model->m_vertexlist.ElementAt(poly->m_vertexid[0]);
                Vector *v2 = &model->m_vertexlist.ElementAt(poly->m_vertexid[1]);
                Vector *v3 = &model->m_vertexlist.ElementAt(poly->m_vertexid[2]);
                Vector *v4 = &model->m_vertexlist.ElementAt(poly->m_vertexid[3]);

                int visible1 = fillTriangle(occMap, va1, v2, v3);
                int visible2 = fillTriangle(occMap, va1, v4, v3);

                if (visible1 + visible2 < m_culling_minarea) {
                    facingMap.SetAt(p, 100); // impossible value in facingMap
                }
            }
        }

        delete [] occMap;
    }

    // drawing polys ----------------------------------------------------------------------------------------

    runCount++;

    // SWF init

    const FColor outline(m_style_outline_color & 255, m_style_outline_color >> 8 & 255, m_style_outline_color >> 16 & 255);

    //    FColor blue = FColor(0, 0, 0xff);
    //    FColor black = FColor(0, 0, 0);

    CMap<int, int, gpc_polygon, gpc_polygon> clipShapes; // attr number -> clipshape
    clipShapes.InitHashTable(997);

    /*	if (m_flat) // init not needed, can be done on the fly!
       {
          for (int a=0; a<model->m_attrlist.GetSize(); a++)
          {
             gpc_polygon p;
             clipShapes.SetAt(a, p);
          }
       }*/

    int startDepth = 0;
    int endDepth = pnum;
    int stepDepth = 1;

    if (m_flat) // inverse stepping order for flat shading
    {
        startDepth = pnum - 1;
        endDepth = -1;
        stepDepth = -1;
    }

    //	for (int pd=0; pd<pnum; pd++)	// for shaded
    //	for (int pd=pnum; pd>0; pd--)	// for flat

    message = "Processing Frame " + String(time.GetFrameInt(fps));
    progressbar->SetMessage2(message.Get());

    int currentpoly = 0;

    for (int pd = startDepth; pd != endDepth; pd += stepDepth) {
        if (pnum != 0) // avoid div by zero
        {
            progressbar->SetProgress(barstart + currentpoly++ * barspan / pnum);
        }

        BOOL cull = false;

        p = order.GetAt(pd);

        //		fs << String(p) << " ";

        IEPoly *poly = model->m_polyarray.GetAt(p);

        Vector *va1 = &model->m_vertexlist.ElementAt(poly->m_vertexid[0]);
        Vector *v2 = &model->m_vertexlist.ElementAt(poly->m_vertexid[1]);
        Vector *v3 = &model->m_vertexlist.ElementAt(poly->m_vertexid[2]);
        Vector *v4 = &model->m_vertexlist.ElementAt(poly->m_vertexid[3]);
        /*
                Vector *n1 = &model->m_normallist.ElementAt(poly->m_normalid[0]);
                Vector *n2 = &model->m_normallist.ElementAt(poly->m_normalid[1]);
                Vector *n3 = &model->m_normallist.ElementAt(poly->m_normalid[2]);
                Vector *n4 = &model->m_normallist.ElementAt(poly->m_normalid[3]);
        */
        // move cursor to new position & set styles

        int x1 = (int)(va1->x * magnify);
        int y1 = (int)(va1->y * magnify);

        //		fs << "- ";
        //		fs << String(x1).buf << "|" << String(y1).buf << " ";

        int coincidences = 0;

        int cursorx = x1;
        int cursory = y1;
        int x12 = (int)(v2->x * magnify) - cursorx;
        int y12 = (int)(v2->y * magnify) - cursory;
        if (x12 == 0 && y12 == 0)
            coincidences++;
        //		fs << String(x12).buf << "|" << String(y12).buf << " ";

        cursorx += x12;
        cursory += y12;
        int x23 = (int)(v3->x * magnify) - cursorx;
        int y23 = (int)(v3->y * magnify) - cursory;
        if (x23 == 0 && y23 == 0)
            coincidences++;
        //		fs << String(x23).buf << "|" << String(y23).buf << " ";

        cursorx += x23;
        cursory += y23;
        int x34 = (int)(v4->x * magnify) - cursorx;
        int y34 = (int)(v4->y * magnify) - cursory;
        if (x34 == 0 && y34 == 0)
            coincidences++;
        //		fs << String(x34).buf << "|" << String(y34).buf << " ";

        cursorx += x34;
        cursory += y34;
        int x41 = (int)(va1->x * magnify) - cursorx;
        int y41 = (int)(va1->y * magnify) - cursory;
        if (x41 == 0 && y41 == 0)
            coincidences++;
        //		fs << String(x41).buf << "|" << String(y41).buf << " ";

        // handle wrongly wound patches

        bool flip = false;

        if (coincidences < 2) // dont bother looking at polys with only 2 edges
        {
            //	if (isRightOfLine(*v1, *v2, *v3) == false) flip = true;
            if (x12 != 0 || y12 != 0) {
                if (x23 != 0 || y23 != 0) {
                    if (x34 != 0 || y34 != 0) {
                        if (x41 != 0 || y41 != 0) // this is a 4 pointer
                        {
                            if (!static_cast<bool>(isRightOfLine(*va1, *v2, *v3)))
                                flip = true;

                            /*							if ((isRightOfLine(*v1, *v2, *v3) == false)	&&	// convex poly left wound
                                                    (isRightOfLine(*v2, *v3, *v4) == false) &&
                                                    (isRightOfLine(*v3, *v4, *v1) == false) &&
                                                    (isRightOfLine(*v4, *v1, *v2) == false))	flip = true;
                            
                                                 if ((isRightOfLine(*v1, *v2, *v3) == false) &&	// 3 and 4 are on the right side of 12
                                                    (isRightOfLine(*v1, *v2, *v4) == false))	flip = true;*/
                        } else if (!static_cast<bool>(isRightOfLine(*va1, *v2, *v3)))
                            flip = true;
                    } else if (!static_cast<bool>(isRightOfLine(*va1, *v2, *v3)))
                        flip = true;
                } else if (!static_cast<bool>(isRightOfLine(*va1, *v3, *v4)))
                    flip = true;
            } else if (!static_cast<bool>(isRightOfLine(*va1, *v3, *v4)))
                flip = true;
        }

        if (!flip) {
            // invert direction of left wound polys

            /*			v1 = &model->m_vertexlist.ElementAt(poly->m_vertexid[1]);
                     v2 = &model->m_vertexlist.ElementAt(poly->m_vertexid[0]);
                     v3 = &model->m_vertexlist.ElementAt(poly->m_vertexid[3]);
                     v4 = &model->m_vertexlist.ElementAt(poly->m_vertexid[2]);
            
                     n1 = &model->m_normallist.ElementAt(poly->m_normalid[1]);
                     n2 = &model->m_normallist.ElementAt(poly->m_normalid[0]);
                     n3 = &model->m_normallist.ElementAt(poly->m_normalid[3]);
                     n4 = &model->m_normallist.ElementAt(poly->m_normalid[2]);*/

            int ox12 = x12;
            int oy12 = y12;

            int ox23 = x23;
            int oy23 = y23;

            int ox34 = x34;
            int oy34 = y34;

            int ox41 = x41;
            int oy41 = y41;

            x12 = -ox41;
            y12 = -oy41;

            x23 = -ox34;
            y23 = -oy34;

            x34 = -ox23;
            y34 = -oy23;

            x41 = -ox12;
            y41 = -oy12;
        } else {
            // back face culling

            if (m_culling_backface) {
                cull = true;
            }
        }

        //      Vector* v = &((*v1+*v2+*v3+*v4)/4); // KB: these lines cause a warning, but the variables aren't used
        //      Vector* n = &((*n1+*n2+*n3+*n4)/4);

        Attr &attr = model->m_attrlist.ElementAt(poly->m_attrid);

        float facing;
        facingMap.Lookup(p, facing);

        // calculate transparency

        int a = (1.F - attr.m_transparency) * 255;

        if (a < 255) {
            // the density property is being used as transparency falloff

            float transparencyfalloff = 1.F - hash_math::abs(facing * (1.F - attr.m_density * 10.F));

            a *= transparencyfalloff;

            // show back faces on transparent objects (just show transparent backfaces actually)
            cull = false;
        }

        // cull if closer than nearclip

        if (perspective && (va1->z > -nearclip || v2->z > -nearclip || v3->z > -nearclip || v4->z > -nearclip)) {
            cull = true;
        }

        // remove old frame	// TODO: check if this can stand BEFORE the for(...)

        if (currentFrame > 0) {
            flashObjects.AddFObj(new FCTRemoveObject2(1 + (currentFrame - 1) % 2));
        }

        // draw the poly in flash

        if (!static_cast<bool>(cull) && coincidences < 2 && facing != 100) {
            if (!m_flat) {
                auto *rectBounds = new FRect(-sizeX, -sizeY, sizeX, sizeY); // redrawing rect

                auto *swfPoly = new FDTDefineShape3(rectBounds);
                U16 swfPolyID = swfPoly->ID();

                // get luminance

                float luminance;
                luminanceMap.Lookup(p, luminance);

                // apply ambiance to luminance

                //luminance = 1 - (1 - luminance * (1.F-attr.m_ambiance));
                luminance = luminance * (1 - attr.m_ambiance) + attr.m_ambiance;

                // correct to interval 0-255

                if (luminance < 0.F)
                    luminance = 0.F;
                if (luminance > 1.F)
                    luminance = 1.F;

                // get color

                int r, g, b;
                RGBFloat fcol = attr.m_diffusecolor;

                // apply luminance
                RGBByte col = fcol * luminance;

                r = col.Red();
                g = col.Green();
                b = col.Blue();

                auto *fillcol = new FColor(r, g, b, a);
                FFillStyle *fillstyle = new FFillStyleSolid(fillcol);

                U32 fillStyleID = swfPoly->AddFillStyle(fillstyle);

                // draw outline if glow is selected
                // TODO: what color could be appropriate ? specular col ?

                BOOL doOutline = attr.m_isglow;

                U32 outlineStyleID = 0;
                if (doOutline) {
                    outlineStyleID = swfPoly->AddLineStyle(m_style_outline_thickness, new FColor(outline));
                }

                swfPoly->FinishStyleArrays();

                swfPoly->AddShapeRec(new FShapeRecChange(false, // stateNewStyles
                                                         doOutline, // stateLineStyle
                                                         true, // stateFillStyle1
                                                         false, // stateFillStyle0		// doFill
                                                         true, // stateMoveTo
                                                         x1, // moveDeltaX		not delta. this is absolute to 0/0
                                                         -y1, // moveDeltaY		not delta. this is absolute to 0/0
                                                         0, // fill0Style
                                                         fillStyleID, // fill1Style
                                                         outlineStyleID, // lineStyle
                                                         nullptr, // fillStyles
                                                         nullptr) // lineStyles
                );

                if (x12 != 0 || y12 != 0)
                    swfPoly->AddShapeRec(new FShapeRecEdgeStraight(x12, -y12));
                if (x23 != 0 || y23 != 0)
                    swfPoly->AddShapeRec(new FShapeRecEdgeStraight(x23, -y23));
                // dont draw 3-4 for a 3 - pointer
                if (x34 != 0 || y34 != 0)
                    swfPoly->AddShapeRec(new FShapeRecEdgeStraight(x34, -y34));
                if (x41 != 0 || y41 != 0)
                    swfPoly->AddShapeRec(new FShapeRecEdgeStraight(x41, -y41));

                // finish Shape and add to movie
                swfPoly->AddShapeRec(new FShapeRecEnd());
                flashObjects.AddFObj(swfPoly);

                auto *mat = new FMatrix(false, // hasScale
                                        0, // scaleX
                                        0, // scaleY
                                        false, // hasRotate
                                        0, // rotateSkew0
                                        0, // rotateSkew1
                                        offsetX, // translateX
                                        offsetY // translateY
                );

                // add new Object
                flashObjects.AddFObj(new FCTPlaceObject2(false, // ~ _hasClipDepth
                                                         false, // has ratio
                                                         true, // has Id
                                                         false, // has move
                                                         1 + currentFrame % 2, // depth
                                                         swfPolyID, // character id
                                                         mat, // matrix 
                                                         nullptr, // color transform
                                                         0, // ratio
                                                         nullptr, // name
                                                         0) // clip
                );
            } else // if (!m_flat)
            {
                try {
                    BOOL usedPoly = false;

                    for (int ac = 0; ac < model->m_attrlist.GetSize(); ac++) {
                        gpc_polygon newp;

                        int x2 = x1 + x12;
                        int y2 = y1 + y12;

                        int x3 = x2 + x23;
                        int y3 = y2 + y23;

                        int x4 = x3 + x34;
                        int y4 = y3 + y34;

                        if (x12 == 0 && y12 == 0) {
                            gpc_define_3corner(&newp, x1, y1, x3, y3, x4, y4);
                        } else if (x23 == 0 && y23 == 0) {
                            gpc_define_3corner(&newp, x1, y1, x2, y2, x4, y4);
                        } else if (x34 == 0 && y34 == 0) {
                            gpc_define_3corner(&newp, x1, y1, x2, y2, x4, y4);
                        } else if (x41 == 0 && y41 == 0) {
                            gpc_define_3corner(&newp, x1, y1, x2, y2, x3, y3);
                        } else {
                            gpc_define_4corner(&newp, x1, y1, x2, y2, x3, y3, x4, y4);
                        }

                        gpc_polygon ppp;
                        gpc_polygon result;

                        if (clipShapes.Lookup(ac, ppp)) {
                            if (ac == poly->m_attrid) {
                                // add to own attr gpc_polygon

                                gpc_polygon_clip(GPC_UNION, &ppp, &newp, &result);
                                clipShapes.SetAt(ac, result);
                                gpc_free_polygon(&ppp);
                            } else {
                                if (a == 255) {
                                    // remove from other attr gpc_polygons

                                    gpc_polygon_clip(GPC_DIFF, &ppp, &newp, &result);
                                    clipShapes.SetAt(ac, result);
                                    gpc_free_polygon(&ppp);
                                }
                            }
                        } else {
                            if (ac == poly->m_attrid) {
                                usedPoly = TRUE;
                                clipShapes.SetAt(ac, newp);
                            }
                        }

                        if (!usedPoly) {
                            gpc_free_polygon(&newp);
                        }
                    }
                }
                catch (...) {
                    //DD					fs << "\r\nFailed clip for Poly " << String(p).buf;
                }
            } // if (!m_flat) .. else ..
        }
    }

    // DEBUG crash after plugin use
    //	flashObjects.AddFObj(	new FCTShowFrame()  );
    //	return;

    message = "Writing Frame " + String(time.GetFrameInt(fps));
    progressbar->SetMessage2(message.Get());

    try {
        if (m_flat) {
            for (int ac = 0; ac < model->m_attrlist.GetSize(); ac++) {
                try {
                    gpc_polygon ppp;

                    if (clipShapes.Lookup(ac, ppp)) {
                        int shapeCount = 0;
                        int tr = 0;

                        // remove old frame	// TODO: check if this can stand BEFORE the for(...)

                        if (currentFrame > 0) {
                            flashObjects.AddFObj(new FCTRemoveObject2(1 + (currentFrame - 1) % 2));
                            flashObjects.AddFObj(new FCTRemoveObject2(1 + (currentFrame - 1) % 2 + 2)); // transparent object layer
                        }

                        auto *rectBounds = new FRect(-sizeX, -sizeY, sizeX, sizeY); // redrawing rect

                        auto *swfPoly = new FDTDefineShape3(rectBounds);
                        U16 swfPolyID = swfPoly->ID();

                        // get surface attributes

                        int r, g, b;
                        Attr &attr = model->m_attrlist.ElementAt(ac);

                        BOOL doOutline = attr.m_isglow;

                        int a = (1.F - attr.m_transparency) * 255;

                        if (a < 255)
                            tr = 2;

                        RGBByte col = attr.m_diffusecolor;

                        r = col.Red();
                        g = col.Green();
                        b = col.Blue();

                        auto *fillcol = new FColor(r, g, b, a);
                        U32 fillStyleID = 0;

                        // Gradient rendering

                        if (m_flat_spec && attr.m_specularsize > 0.F) {
                            // TODO: add feature: roughness selects light (roughness=0->first light 1->"Light1", etc.)

                            Vector lightPos;
                            Vector lightScale;
                            int lightFalloff;

                            if (!lightNode) // default light
                            {
                                lightPos = Vector(0, 0, 0);
                                lightScale = Vector(1, 1, 1);
                                lightFalloff = 100;
                            } else {
                                HLightListNode *currLightNode = lightNode;
                                HLight *light;

                                String wantedLightName = String("Shortcut to Light") + String((int)(attr.m_roughness * 100 + 1));

                                while (currLightNode && String(currLightNode->GetName()) != wantedLightName) {
                                    currLightNode = currLightNode->GetNextLightListNode();
                                    if (currLightNode == lightNode)
                                        currLightNode = nullptr;
                                }
                                if (!currLightNode) {
                                    currLightNode = lightNode;
                                }

                                light = currLightNode->GetLight();

                                HTransformProperty *ht = light->GetTransform();
                                lightPos = ht->GetTranslate()->GetValue(time);
                                lightScale = ht->GetScale()->GetValue(time);

                                lightFalloff = light->GetFalloff()->GetValue(time);
                                if (camera) {
                                    Vector lightFalloffVec = lightPos;
                                    cameraTransformationOnly(lightFalloffVec);

                                    lightFalloffVec.x = lightFalloff;
                                    cameraPerspective(lightFalloffVec);

                                    lightFalloff = lightFalloffVec.x;
                                }

                                if (camera)
                                    cameraTransformation(lightPos);
                                lightPos.y = -lightPos.y;
                            }

                            if (attr.m_specularintensity > 99)
                                attr.m_specularintensity = 99;
                            attr.m_specularsize *= 2; // double size

                            col = attr.m_specularcolor;

                            r = col.Red();
                            g = col.Green();
                            b = col.Blue();

                            auto *speccol = new FColor(r, g, b, 255);

                            auto *gmat = new FMatrix(true, // hasScale
                                                     lightFalloff * 255 * attr.m_specularsize * lightScale.x, // scaleX
                                                     lightFalloff * 255 * attr.m_specularsize * lightScale.y, // scaleY
                                                     false, // hasRotate
                                                     0, // rotateSkew0
                                                     0, // rotateSkew1
                                                     lightPos.x * magnify, // translateX
                                                     lightPos.y * magnify // translateY
                            );

                            auto *fgrad = new FGradient();
                            int ratio = attr.m_specularintensity * 255;
                            if (ratio < 0)
                                ratio = 0;
                            if (ratio > 254)
                                ratio = 254;
                            fgrad->Add(new FGradRecord(ratio, speccol));
                            fgrad->Add(new FGradRecord(255, fillcol));

                            auto *fillstyle = new FFillStyleGradient(0, gmat, fgrad);

                            fillStyleID = swfPoly->AddFillStyle(fillstyle);
                        } else {
                            FFillStyle *fillstyle = new FFillStyleSolid(fillcol);
                            fillStyleID = swfPoly->AddFillStyle(fillstyle);
                        }

                        U32 outlineStyleID = 0;
                        if (doOutline) {
                            outlineStyleID = swfPoly->AddLineStyle(m_style_outline_thickness, new FColor(outline));
                        }

                        swfPoly->FinishStyleArrays();

                        for (int c = 0; c < ppp.num_contours; c++) {
                            if (ppp.contour[c].num_vertices > 2) {
                                // first count if enough different vertices

                                int firstX = ppp.contour[c].vertex[0].x;
                                int firstY = ppp.contour[c].vertex[0].y;

                                int oldX = firstX;
                                int oldY = firstY;

                                int vertexCount = 0;
                                for (int vv1 = 1; vv1 < ppp.contour[c].num_vertices; vv1++) {
                                    int x = ppp.contour[c].vertex[vv1].x;
                                    int y = ppp.contour[c].vertex[vv1].y;

                                    if (x != oldX || y != oldY)
                                        vertexCount++;

                                    oldX = x;
                                    oldY = y;
                                }

                                // modify styles for holes

                                if (vertexCount > 2) {
                                    U32 fill = fillStyleID;
                                    BOOL doFill = TRUE;

                                    if (ppp.hole[c] == TRUE) {
                                        //                                        BOOL doFill = FALSE;
                                        fill = 0;
                                    }

                                    shapeCount++;

                                    swfPoly->AddShapeRec(new FShapeRecChange(false, // stateNewStyles
                                                                             doOutline, // stateLineStyle
                                                                             doFill, // stateFillStyle1
                                                                             false, // stateFillStyle0		// doFill
                                                                             true, // stateMoveTo
                                                                             firstX, // moveDeltaX		not delta. this is absolute to 0/0
                                                                             -firstY, // moveDeltaY		not delta. this is absolute to 0/0
                                                                             0, // fill0Style
                                                                             fill, // fill1Style
                                                                             outlineStyleID, // lineStyle
                                                                             nullptr, // fillStyles
                                                                             nullptr) // lineStyles
                                    );

                                    //	fs << "\r\n" << String(firstX).buf << "|" << String(firstY).buf << " ";

                                    int old_x = firstX;
                                    int old_y = firstY;

                                    for (int i = 1; i < ppp.contour[c].num_vertices; i++) {
                                        int x = ppp.contour[c].vertex[i].x;
                                        int y = ppp.contour[c].vertex[i].y;

                                        int xo = x - old_x;
                                        int yo = y - old_y;

                                        int length = hash_math::sqrt((float)xo * xo + yo * yo);

                                        if (length > m_flat_minedgelength) //(x != oldX) || (y != oldY))
                                        {
                                            //			fs << String(x).buf << "|" << String(y).buf << " ";
                                            swfPoly->AddShapeRec(new FShapeRecEdgeStraight(xo, -yo));
                                            vertexCount++;

                                            old_x = x;
                                            old_y = y;
                                        }
                                    }

                                    // close shape

                                    int x = firstX;
                                    int y = firstY;

                                    int xo = x - old_x;
                                    int yo = y - old_y;

                                    if (x != old_x || y != old_y) {
                                        swfPoly->AddShapeRec(new FShapeRecEdgeStraight(xo, -yo));
                                    }
                                } // if (vertexcount > 2)
                            }
                        } // for (int c=0; c<ppp.num_contours; c++)

                        if (shapeCount > 0) {
                            swfPoly->AddShapeRec(new FShapeRecEnd());

                            flashObjects.AddFObj(swfPoly);

                            auto *mat = new FMatrix(false, // hasScale
                                                    0, // scaleX
                                                    0, // scaleY
                                                    false, // hasRotate
                                                    0, // rotateSkew0
                                                    0, // rotateSkew1
                                                    offsetX, // translateX
                                                    offsetY // translateY
                            );

                            // add new Object
                            flashObjects.AddFObj(new FCTPlaceObject2(false, // ~ _hasClipDepth
                                                                     false, // has ratio
                                                                     true, // has Id
                                                                     false, // has move
                                                                     1 + currentFrame % 2 + tr, // depth
                                                                     swfPolyID, // character id
                                                                     mat, // matrix 
                                                                     nullptr, // color transform
                                                                     0, // ratio
                                                                     nullptr, // name
                                                                     0) // clip
                            );
                        } // if (shapeCount > 0)

                        gpc_free_polygon(&ppp);
                    } // if (clipShapes.Lookup(ac, ppp))
                }
                catch (...) {
                    //DD				fs << "\r\nFailed output for Attr " << String(ac).buf;
                }
            }

            clipShapes.RemoveAll();
        }
    }
    catch (...) {
        //DD		fs << "export failed!";
    }

    //	delete clipShapes;

    // finish frame
    flashObjects.AddFObj(new FCTShowFrame());
}
