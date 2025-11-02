// NAP  3/26/2004  \noel110\Plugin\HXT\3DS\Export.cpp
// ReSharper disable CppLocalVariableWithNonTrivialDtorIsNeverUsed
#include "StdAfx.h"
#include "Hxt.h"
#include "ExportModelDialog.h"
#include "ExportModelsDialog.h"
#include "ExportActionsDialog.h"
#include "TextureMapDialog.h"
#include "F_Protos.h"
#include "Archive.h"
#include "Files.h"
#include "SDK/HCP.h"
#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/HChor.h"
#include "SDK/Misc.h"

BOOL CHxtApp::OnExportModelCache(HModelCache *hmc) {

    CExportModelDialog cdlg(hmc->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;
    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
    m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    const String modelmapfilename = cdlg.m_filename.GetWithoutSuffix() + ".bmp";
    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
    if (model == nullptr) {
        ReportExportError(cdlg.m_filename);
        return TRUE;
    }

    const BOOL result = Export3DS(model, cdlg.m_filename);
    DeleteIEModel(model);

    if (!result)
        ReportExportError(cdlg.m_filename);

    return TRUE;
}

BOOL CHxtApp::OnExportActionCache(HActionCache *hac) {
    HModelCache *hmc = hac->GetDefaultModelCache();

    if (hmc == nullptr) {
        CString msg, title;
        msg.LoadString(IDS_ACTIONHASNOMODELASSIGNED);
        String temp = msg;
        temp.Replace("%1", hac->GetName());
        msg = temp.Get();
        title.LoadString(IDS_EXPORTTITLE);

        MessageBox(GetMainApplicationWnd(), msg, title, MB_OK);
        return TRUE;
    }

    CExportModelDialog cdlg(hmc->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;

    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
    m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const Time totaltime = hac->GetTotalTime();
    const String basefilename = cdlg.m_filename;

    HModel *hm = hac->EditWithModelCache(hmc);

    for (Time time; time <= totaltime; time.StepFrame(fps)) {
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);
        String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            hac->EndEditWithModelCache(hm);
            return TRUE;
        }

        const BOOL result = Export3DS(model, filename);
        DeleteIEModel(model);

        if (!result) {
            ReportExportError(filename);
            hac->EndEditWithModelCache(hm);
            return FALSE;
        }

    }
    hac->EndEditWithModelCache(hm);
    return TRUE;
}

BOOL CHxtApp::OnExportObjectCacheContainer(HObjectCacheContainer *hocc) {
    CExportModelsDialog cdlg(hocc);
    if (cdlg.DoModal() != IDOK)
        return TRUE;

    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
    m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HModelCache *hmc = cdlg.m_selected.GetNext(pos);
        String filename = hmc->GetName();
        filename = filename.GetNameOnlyWithoutSuffix() + ".3ds";
        filename = CombineNameToPath(cdlg.m_dir, filename);
        String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }
        const BOOL result = Export3DS(model, filename);
        DeleteIEModel(model);
        if (!result) {
            ReportExportError(filename);
            return TRUE;
        }
    }
    return TRUE;
}

BOOL CHxtApp::OnExportActionCacheContainer(HActionCacheContainer *hocc) {
    CExportActionsDialog cdlg(hocc);
    if (cdlg.DoModal() != IDOK)
        return TRUE;

    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
    m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();

    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HActionCache *hac = cdlg.m_selected.GetNext(pos);
        HModelCache *hmc = hac->GetDefaultModelCache();

        if (hmc == nullptr) {
            CString msg, title;
            msg.LoadString(IDS_ACTIONHASNOMODELASSIGNED);
            String temp = msg;
            temp.Replace("%1", hac->GetName());
            msg = temp.Get();
            title.LoadString(IDS_EXPORTTITLE);
            MessageBox(GetMainApplicationWnd(), msg, title, MB_OK);
            return TRUE;
        }

        const Time totaltime = hac->GetTotalTime();
        String basefilename = hac->GetName();
        basefilename = basefilename.GetNameOnlyWithoutSuffix() + "-0000.3ds";
        basefilename = CombineNameToPath(cdlg.m_dir, basefilename);

        HModel *hm = hac->EditWithModelCache(hmc);

        for (Time time; time <= totaltime; time.StepFrame(fps)) {
            const int frame = time.GetFrameInt(fps);
            String filename = basefilename.NumberFrame(frame);
            String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
            IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
            if (model == nullptr) {
                ReportExportError(filename);
                hac->EndEditWithModelCache(hm);
                return TRUE;
            }

            const BOOL result = Export3DS(model, filename);
            DeleteIEModel(model);

            if (!result) {
                ReportExportError(filename);
                hac->EndEditWithModelCache(hm);
                return TRUE;
            }

        }
        hac->EndEditWithModelCache(hm);
    }
    return TRUE;
}

BOOL CHxtApp::OnExportChor(HChor *hchor) {

    CExportModelDialog cdlg(hchor->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;

    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
    m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const HTimeProperty *totaltime = hchor->GetTotalTime();
    const String basefilename = cdlg.m_filename;

    for (Time time; time <= totaltime->GetValue(); time.StepFrame(fps)) {
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);
        String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }

        const BOOL result = Export3DS(model, filename);
        DeleteIEModel(model);

        if (!result) {
            ReportExportError(filename);
            return TRUE;
        }
    }
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

class Chunk {
public:
    CArchive *m_ar{};
    DWORD m_startpos{};
    bool m_inside{false};

    Chunk() = default;

    Chunk(CArchive *ar, const WORD id) {
        Start(ar, id);
    }

    ~Chunk() {
        End();
    }
    Chunk(const Chunk&) = default;
    Chunk &operator=(const Chunk&) = default; 
    Chunk(Chunk &&) = default; 
    Chunk &operator=(Chunk &&) = default; 

    void End() {
        if (m_inside) {
            m_inside = false;
            const DWORD currpos = GetPosition(*m_ar);
            SetPosition(*m_ar, m_startpos + CHUNKIDSIZE);
            *m_ar << currpos - m_startpos;
            SetPosition(*m_ar, currpos);
        }
    }

    void Start(CArchive *ar, const WORD id) {
        if (!m_inside) {
            m_inside = true;
            m_ar = ar;
            m_startpos = GetPosition(*m_ar);
            *ar << id;
            *ar << DEFAULTCHUCKSIZE;
        }
    }
};

static void WriteChunk(CArchive &ar, const WORD id, const WORD value) {
    Chunk chunk(&ar, id);
    ar << value;
}

static void WriteChunk(CArchive &ar, const WORD id, const DWORD value) {
    Chunk chunk(&ar, id);
    ar << value;
}

static void WriteChunk(CArchive &ar, const WORD id, const float value) {
    Chunk chunk(&ar, id);
    ar << value;
}

static void WriteChunk(CArchive &ar, const WORD id, const CString &string) {
    Chunk chunk(&ar, id);
    WriteString(ar, string);
}

/*
static void WriteChunk(CArchive &ar, WORD id, const Matrix34 &m34) {
    Chunk chunk(&ar, id);
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 3; ++y)
            ar << m34[y][x];
}
*/
static void WriteColorChunk(CArchive &ar, const WORD id, const RGBFloat &color, const BOOL isfloat) {
    Chunk chunk(&ar, id);
    if (isfloat) {
        Chunk colorchunk(&ar, CHUNK_RGB_F);
        ar << color.m_red << color.m_green << color.m_blue;
    } else {
        Chunk colorchunk(&ar, CHUNK_RGB_B);
        const auto r = (UBYTE)MIN3DS(255, color.m_red * 255);
        const auto g = (UBYTE)MIN3DS(255, color.m_green * 255);
        const auto b = (UBYTE)MIN3DS(255, color.m_blue * 255);
        ar << r << g << b;
    }
}

static void WritePctChunk(CArchive &ar, const WORD id, const float value, const BOOL isfloat) {
    Chunk chunk(&ar, id);
    if (isfloat) {
        Chunk colorchunk(&ar, CHUNK_PERCENT_F);
        ar << value;
    } else {
        Chunk colorchunk(&ar, CHUNK_PERCENT_W);
        const WORD p = (WORD)(value * 100);
        ar << p;
    }
}

void CHxtApp::CopyMaps(const String &path, IEPolyModel *model) {
    for (int i = 0; i < model->m_maplist.GetSize(); ++i) {
        const IEMap &map = model->m_maplist[i];
        String sourcefilename = map.m_filename;
        if (String destfilename = CombineNameToPath(path, m_maplist[i]); !HashCopyFile(sourcefilename, destfilename)) {
            CString text;
            text.LoadString(IDS_UNABLETOCOPYFILE);
            String stext = text;
            stext.Replace("%1", sourcefilename);
            stext.Replace("%2", destfilename);
            AfxMessageBox(stext.Get(), MB_OK);
        }
    }
}

BOOL CHxtApp::Export3DS(IEPolyModel *model, const String &filename) {
    if (model->m_maplist.GetSize()) {
        CTextureMapDialog cdlg(this, model);
        if (cdlg.DoModal() != IDOK)
            return TRUE;
        if (cdlg.m_copymaps)
            CopyMaps(filename.GetPathOnly(), model);
    }

    if (model->m_vertexlist.GetSize() > 65535 || model->m_polyarray.GetSize() * 2 > 65535) {
        CString text;
        text.LoadString(IDS_INVALIDNUMBEROFVERTICESPOLYS);
        String stext = text;
        String vertstring = model->m_vertexlist.GetSize();
        String polystring = model->m_polyarray.GetSize() * 2;
        stext.Replace("%1", vertstring.Get());
        stext.Replace("%2", polystring.Get());
        AfxMessageBox(stext.Get(), MB_OK);
    }

    CFile file;
    CFileException fileexception;

    if (!file.Open(filename.Get(), CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &fileexception)) {
        CString text;
        text.LoadString(IDS_CANTOPENFILE);
        String stext = text;
        stext.Replace("%1", filename.Get());
        stext.Replace("%2", fileexception.m_cause);
        AfxMessageBox(stext.Get(), MB_OK);
        return FALSE;
    }

    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        m_hprogressbar->SetMessage1(text);
        m_hprogressbar->SetMessage2(filename.GetNameOnly().Get());
    }

    // Get total items for percent bar
    m_totalexportitems = MIN3DS(65535, model->m_vertexlist.GetSize()) + MIN3DS(65535, model->m_polyarray.GetSize()*2);

    m_currexportitem = 0;

    CArchive ar(&file, CArchive::store);
    TRY
        {
            Chunk chunk(&ar, CHUNK_MAIN);
            WriteChunk(ar, CHUNK_M3DVERSION, (DWORD)2);
            WriteObjMeshChunk(ar, model);
            chunk.End();
        }
    CATCH(CUserException, e)
        {
            ar.Close();
            file.Close();
            if (m_hprogressbar) {
                m_hprogressbar->Uninitialize();
                m_hprogressbar = nullptr;
            }
            return FALSE;
        }
    AND_CATCH_ALL(e)
        {
            ar.Close();
            file.Close();
            e->ReportError();
            if (m_hprogressbar) {
                m_hprogressbar->Uninitialize();
                m_hprogressbar = nullptr;
            }
            return FALSE;
        }
    END_CATCH_ALL

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }
    return TRUE;
}

void MapMaterialID::Set(IEPoly *poly) {
    const int mapcount = poly->m_mapnodearray.GetSize();
    m_materialid = poly->m_attrid;
    m_colormapid = -1;
    m_specularmapid = -1;
    m_bumpmapid = -1;
    m_opacitymapid = -1;
    m_reflectmapid = -1;

    if (mapcount) {
        Vector2 uv[4];
        BOOL filleduvs = FALSE;
        for (int k = 0; k < mapcount; ++k) {
            const IEMapNode *mapnode = poly->m_mapnodearray[k];
            if (filleduvs == FALSE) {
                filleduvs = TRUE;
                uv[0] = mapnode->m_uv[0];
                uv[1] = mapnode->m_uv[1];
                uv[2] = mapnode->m_uv[2];
                uv[3] = mapnode->m_uv[3];
            } // only put in maps that have the same UV coordinates as the first map for this poly
            else if (mapnode->m_uv[0] != uv[0] || mapnode->m_uv[1] != uv[1] || mapnode->m_uv[2] != uv[2] || mapnode->m_uv[3] != uv[3])
                continue;

            switch (mapnode->m_kind) {
                case IEMapNode::COLORMAP:
                    if (m_colormapid == -1)
                        m_colormapid = mapnode->m_mapid;
                    break;
                case IEMapNode::SPECULARINTENSITYMAP:
                    if (m_specularmapid == -1)
                        m_specularmapid = mapnode->m_mapid;
                    break;
                case IEMapNode::BUMPMAP:
                    if (m_bumpmapid == -1)
                        m_bumpmapid = mapnode->m_mapid;
                    break;
                case IEMapNode::TRANSPARENCYMAP:
                    if (m_opacitymapid == -1)
                        m_opacitymapid = mapnode->m_mapid;
                    break;
                case IEMapNode::MIRRORMAP:
                    if (m_reflectmapid == -1)
                        m_reflectmapid = mapnode->m_mapid;
                    break;
            }
        }
    }
}

void CHxtApp::WriteObjMeshChunk(CArchive &ar, IEPolyModel *model) {
    Chunk chunk(&ar, CHUNK_OBJMESH);

    WriteChunk(ar, CHUNK_MESHVERSION, (DWORD)2);

    const int matcount = model->m_attrlist.GetSize();

    int currindex;
    for (currindex = 0; currindex < matcount; ++currindex)
        WriteMaterial(ar, model->m_attrlist[currindex], currindex);

    // now make materials for all texturemaps
    MapMaterialID mapmaterialid;
    for (int i = 0; i < model->m_polyarray.GetSize(); ++i) {
        IEPoly *poly = model->m_polyarray[i];
        if (const int mapcount = poly->m_mapnodearray.GetSize(); mapcount) {
            mapmaterialid.Set(poly);
            if (int id; !m_hashtable.Lookup(mapmaterialid, id)) {
                m_hashtable.SetAt(mapmaterialid, currindex);
                WriteMapMaterial(ar, model, &mapmaterialid, currindex);
                currindex++;
            }
        }
    }
    WriteChunk(ar, CHUNK_MASTERSCALE, 2.54F);
    WriteObjChunk(ar, model);
}

void CHxtApp::WriteMaterial(CArchive &ar, const Attr &attr, const int id) {
    Chunk chunk(&ar, CHUNK_MATERIAL);
    CString name;
    name.LoadString(IDS_MATERIAL);
    String sname = name;
    sname.Replace("%1", id + 1);

    WriteChunk(ar, CHUNK_MAT_NAME, sname.Get());
    WriteColorChunk(ar, CHUNK_MAT_AMBIENT, RGBFloat(attr.m_ambiance), FALSE);
    WriteColorChunk(ar, CHUNK_MAT_DIFFUSE, attr.m_diffusecolor, FALSE);
    WriteColorChunk(ar, CHUNK_MAT_SPECULAR, attr.m_specularcolor, FALSE);
    WritePctChunk(ar, CHUNK_MAT_SHININESS, 1.F - attr.m_specularsize, FALSE);
    WritePctChunk(ar, CHUNK_MAT_SHIN2PCT, attr.m_specularintensity, FALSE);
    WritePctChunk(ar, CHUNK_MAT_TRANSPARENCY, attr.m_transparency, FALSE);
    WriteChunk(ar, CHUNK_MAT_SHADING, (WORD)3);
}

void CHxtApp::WriteMapMaterial(CArchive &ar, IEPolyModel *model, const MapMaterialID *mapmaterialid, const int i) {
    Chunk chunk(&ar, CHUNK_MATERIAL);
    CString name;
    name.LoadString(IDS_MATERIAL);
    String sname = name;
    sname.Replace("%1", i + 1);

    WriteChunk(ar, CHUNK_MAT_NAME, sname.Get());

    if (mapmaterialid->m_materialid != -1) {
        const Attr &attr = model->m_attrlist[mapmaterialid->m_materialid];
        RGBFloat ambiance(attr.m_diffusecolor);
        ambiance *= attr.m_ambiance;
        WriteColorChunk(ar, CHUNK_MAT_AMBIENT, ambiance, FALSE);
        WriteColorChunk(ar, CHUNK_MAT_DIFFUSE, attr.m_diffusecolor, FALSE);
        WriteColorChunk(ar, CHUNK_MAT_SPECULAR, attr.m_specularcolor, FALSE);
        WritePctChunk(ar, CHUNK_MAT_SHININESS, MIN(1.F, MAX(0.F, 1.F - attr.m_specularsize)), FALSE);
        WritePctChunk(ar, CHUNK_MAT_SHIN2PCT, attr.m_specularintensity, FALSE);
        WritePctChunk(ar, CHUNK_MAT_TRANSPARENCY, MIN(1.F, MAX(0.F, attr.m_transparency)), FALSE);
        WriteChunk(ar, CHUNK_MAT_SHADING, (WORD)3);
    }
    if (mapmaterialid->m_colormapid != -1) {
        Chunk mapchunk(&ar, CHUNK_MAT_TEXTUREMAP);
        WriteChunk(ar, CHUNK_PERCENT_W, (WORD)100);
        WriteChunk(ar, CHUNK_MAT_MAPNAME, m_maplist[mapmaterialid->m_colormapid]);
    }
    if (mapmaterialid->m_specularmapid != -1) {
        Chunk mapchunk(&ar, CHUNK_MAT_SPECULARMAP);
        WriteChunk(ar, CHUNK_PERCENT_W, (WORD)100);
        WriteChunk(ar, CHUNK_MAT_MAPNAME, m_maplist[mapmaterialid->m_specularmapid]);
    }
    if (mapmaterialid->m_bumpmapid != -1) {
        Chunk mapchunk(&ar, CHUNK_MAT_BUMPMAP);
        WriteChunk(ar, CHUNK_PERCENT_W, (WORD)100);
        WriteChunk(ar, CHUNK_MAT_MAPNAME, m_maplist[mapmaterialid->m_bumpmapid]);
    }
    if (mapmaterialid->m_opacitymapid != -1) {
        Chunk mapchunk(&ar, CHUNK_MAT_OPACMAP);
        WriteChunk(ar, CHUNK_PERCENT_W, (WORD)100);
        WriteChunk(ar, CHUNK_MAT_MAPNAME, m_maplist[mapmaterialid->m_opacitymapid]);
    }
    if (mapmaterialid->m_reflectmapid != -1) {
        Chunk mapchunk(&ar, CHUNK_MAT_REFLECTMAP);
        WriteChunk(ar, CHUNK_PERCENT_W, (WORD)100);
        WriteChunk(ar, CHUNK_MAT_MAPNAME, m_maplist[mapmaterialid->m_reflectmapid]);
    }
}

void CHxtApp::WriteObjChunk(CArchive &ar, IEPolyModel *model) {
    Chunk chunk(&ar, CHUNK_OBJCHUNK);

    const String tfilename = ar.GetFile()->GetFileName();
    const CString filename = tfilename.GetNameOnlyWithoutSuffix().Get();
    WriteString(ar, filename);
    WriteTriMeshChunk(ar, model);
}

void CHxtApp::WriteTriMeshChunk(CArchive &ar, IEPolyModel *model) {
    Chunk chunk(&ar, CHUNK_TRIMESH);

    WriteVertexList(ar, model);

    //   Matrix34 m34 = XRotate(-90);
    //   WriteChunk(ar, CHUNK_TRMATRIX, m34);

    WriteFaceList(ar, model);
    for (int i = 0; i < model->m_attrlist.GetSize(); ++i)
        WriteFaceMat(ar, model, i);
    BOOL hasmaps = FALSE;
    for (POSITION pos = m_hashtable.GetStartPosition(); pos;) {
        hasmaps = TRUE;
        int id;
        MapMaterialID mapmaterialid;
        m_hashtable.GetNextAssoc(pos, mapmaterialid, id);
        WriteFaceMapMat(ar, model, id);
    }
    if (hasmaps)
        WriteUVList(ar, model);
}

void CHxtApp::WriteVertexList(CArchive &ar, IEPolyModel *model) {
    Chunk chunk(&ar, CHUNK_VERTLIST);

    int count = model->m_vertexlist.GetSize();
    count = MIN3DS(count, 65535);
    ar << (WORD)count;
    for (int i = 0; i < count; ++i) {
        const Vector &p = model->m_vertexlist[i];
        //      ar << p.x << p.y << p.z;
        ar << p.x << -p.z << p.y;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)m_currexportitem++ / m_totalexportitems * 100));
    }
}

void CHxtApp::WriteFaceList(CArchive &ar, IEPolyModel *model) {
    Chunk chunk(&ar, CHUNK_FACELIST);

    int count = model->m_polyarray.GetSize();
    count = MIN3DS(count, 65535);
    const DWORD startpos = GetPosition(ar);
    ar << (WORD)(count * 2); // triangles
    int threepoints = 0;
    for (int i = 0; i < count; ++i) {
        const IEPoly *poly = model->m_polyarray[i];
        ar << (WORD)MIN3DS(65536, poly->m_vertexid[0]);
        ar << (WORD)MIN3DS(65536, poly->m_vertexid[1]);
        ar << (WORD)MIN3DS(65536, poly->m_vertexid[2]);
        ar << (WORD)6; // face flags
        if (poly->m_vertexid[0] != poly->m_vertexid[3]) {
            // Not a 3 point patch
            ar << (WORD)MIN3DS(65536, poly->m_vertexid[0]);
            ar << (WORD)MIN3DS(65536, poly->m_vertexid[2]);
            ar << (WORD)MIN3DS(65536, poly->m_vertexid[3]);
            ar << (WORD)6; // face flags
        } else
            threepoints++;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)m_currexportitem / m_totalexportitems * 100));
        m_currexportitem += 2;
    }
    if (threepoints) {
        // must go back and adjust count now
        const DWORD currpos = GetPosition(ar);
        SetPosition(ar, startpos);
        ar << (WORD)(count * 2 - threepoints);
        SetPosition(ar, currpos);
    }
}

void CHxtApp::WriteFaceMat(CArchive &ar, IEPolyModel *model, const int id) {
    Chunk chunk(&ar, CHUNK_FACEMAT);

    CString name;
    name.LoadString(IDS_MATERIAL);
    String sname = name;
    sname.Replace("%1", id + 1);

    [[maybe_unused]] DWORD temppos = GetPosition(ar);
    WriteString(ar, sname.Get());
    const DWORD oldpos = GetPosition(ar);
    ar << (WORD)0;

    int writtencount = 0;
    int faceid = 0;

    int polycount = model->m_polyarray.GetSize();
    polycount = MIN3DS(polycount, 65535);

    for (int i = 0; i < polycount; ++i) {
        if (const IEPoly *poly = model->m_polyarray[i]; poly->m_attrid == id && poly->m_mapnodearray.GetSize() == 0) {
            ar << (WORD)faceid;
            faceid++;
            writtencount++;
            if (poly->m_vertexid[0] != poly->m_vertexid[3]) {
                // Not a 3 point patch
                ar << (WORD)faceid;
                faceid++;
                writtencount++;
            }
        } else {
            faceid++;
            if (poly->m_vertexid[0] != poly->m_vertexid[3]) // Not a 3 point patch
                faceid++;
        }
    }
    if (writtencount) {
        const DWORD currpos = GetPosition(ar);
        SetPosition(ar, oldpos);
        ar << (WORD)writtencount;
        SetPosition(ar, currpos);
    }
}

void CHxtApp::WriteFaceMapMat(CArchive &ar, IEPolyModel *model, const int matchid) const {
    Chunk chunk(&ar, CHUNK_FACEMAT);

    CString name;
    name.LoadString(IDS_MATERIAL);
    String sname = name;
    sname.Replace("%1", matchid + 1);

    WriteString(ar, sname.Get());
    const DWORD oldpos = GetPosition(ar);
    ar << (WORD)0;

    int writtencount = 0;
    int faceid = 0;

    int polycount = model->m_polyarray.GetSize();
    polycount = MIN3DS(polycount, 65535);

    MapMaterialID mapmaterialid;
    for (int i = 0; i < polycount; ++i) {
        IEPoly *poly = model->m_polyarray[i];
        mapmaterialid.Set(poly);

        int id;
        if (!m_hashtable.Lookup(mapmaterialid, id))
            id = -1;

        if (id == matchid) {
            ar << (WORD)faceid;
            faceid++;
            writtencount++;
            if (poly->m_vertexid[0] != poly->m_vertexid[3]) {
                // Not a 3 point patch
                ar << (WORD)faceid;
                faceid++;
                writtencount++;
            }
        } else {
            faceid++;
            if (poly->m_vertexid[0] != poly->m_vertexid[3]) // Not a 3 point patch
                faceid++;
        }
    }
    if (writtencount) {
        const DWORD currpos = GetPosition(ar);
        SetPosition(ar, oldpos);
        ar << (WORD)writtencount;
        SetPosition(ar, currpos);
    }
}

void CHxtApp::WriteUVList(CArchive &ar, IEPolyModel *model) {
    Chunk chunk(&ar, CHUNK_UVLIST);

    HashArray<Vector2, Vector2 &> vertuv;
    int vertsize = model->m_vertexlist.GetSize();
    vertuv.SetSize(vertsize); // want array to be full size

    vertsize = MIN3DS(65536, vertsize);
    int i;
    for (i = 0; i < vertsize; ++i)
        vertuv[i] = 0.F; // init all uvs to 0;

    const int polycount = model->m_polyarray.GetSize();
    for (i = 0; i < polycount; ++i) {
        if (IEPoly *poly = model->m_polyarray[i]; poly->m_mapnodearray.GetSize()) {
            const IEMapNode *mapnode = poly->m_mapnodearray[0];
            vertuv[poly->m_vertexid[0]].x = mapnode->m_uv[0].x;
            vertuv[poly->m_vertexid[0]].y = 1.F - mapnode->m_uv[0].y;
            vertuv[poly->m_vertexid[1]].x = mapnode->m_uv[1].x;
            vertuv[poly->m_vertexid[1]].y = 1.F - mapnode->m_uv[1].y;
            vertuv[poly->m_vertexid[2]].x = mapnode->m_uv[2].x;
            vertuv[poly->m_vertexid[2]].y = 1.F - mapnode->m_uv[2].y;
            vertuv[poly->m_vertexid[3]].x = mapnode->m_uv[3].x;
            vertuv[poly->m_vertexid[3]].y = 1.F - mapnode->m_uv[3].y;
        }
    }

    ar << (WORD)vertsize;
    for (i = 0; i < vertsize; ++i) {
        ar << vertuv[i].x;
        ar << vertuv[i].y;
    }
}

template<>
UINT AFXAPI HashKey<MapMaterialID &>(MapMaterialID &key) {
    UINT hashkey = key.m_colormapid;
    hashkey <<= 16;
    hashkey |= key.m_materialid;
    return hashkey;
}
