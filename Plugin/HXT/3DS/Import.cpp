// RC  5/3/2002  \Randy95\Plugin\HXT\3DS\Import.cpp

#include "StdAfx.h"
#include "MessageR.h"
#include "StringLi.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "ImportModelDialog.h"
#include "Archive.h"
#include "SDK/HModel.h"
#include "SDK/HProgres.h"
#include "SDK/Misc.h"

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    const String ext("3DS");
    StringList *namelist;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (String defdir; !OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
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

    CImportModelDialog cdlg;
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }
    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        //        String nameonly = filename.GetNameOnly();
        IEPolyModel *patchmodel = Import3DS(filename);
        if (patchmodel == nullptr) {
            ReportImportError(filename);
            continue;
        }
        if (!hmc->MergeIEModel(patchmodel, filename.Get(), cdlg.m_peaktolerance, TRUE, TRUE))
            ReportImportError(filename);

        delete patchmodel;
    }
    DeleteStringList(namelist);
    return TRUE;
}

BOOL CHxtApp::OnImportObjectCacheContainer([[maybe_unused]] HObjectCacheContainer *hocc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    const String ext("3DS");
    StringList *namelist;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (String defdir; !OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
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

    CImportModelDialog cdlg;
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        String nameonly = filename.GetNameOnly();
        HModelCache *hmc = HModelCache::New(nameonly.Get());
        if (hmc == nullptr) {
            ReportImportError(filename);
            DeleteStringList(namelist);
            return TRUE;
        }
        IEPolyModel *patchmodel = Import3DS(filename);
        if (patchmodel == nullptr) {
            ReportImportError(filename);
            continue;
        }
        if (!hmc->MergeIEModel(patchmodel, filename.Get(), cdlg.m_peaktolerance, FALSE, TRUE))
            ReportImportError(filename);

        delete patchmodel;
    }

    DeleteStringList(namelist);
    return TRUE;
}

void CHxtApp::ReportImportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_IMPORTTITLE);
    CString text;
    text.LoadString(IDS_ERRORIMPORTINGMODEL);
    String temp = text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

IEPolyModel *CHxtApp::Import3DS(const String &pfilename) {
    CFile file;
    CFileException fileexception;

    if (!file.Open(pfilename.Get(), CFile::modeRead, &fileexception)) {
        CString text;
        text.LoadString(IDS_CANTOPENFILE);
        String stext = text;
        stext.Replace("%1", pfilename);
        stext.Replace("%2", fileexception.m_cause);
        AfxMessageBox(stext.Get(), MB_OK);
        return nullptr;
    }

    const String &filename = pfilename;
    auto *model = new IEPolyModel;

    const String oldbasepath = GetBasePath();
    SetBasePath(pfilename);

    CArchive ar(&file, CArchive::load);
    TRY
        {
            DWORD len = 0;
            WORD id;

            DWORD endpos = GetPosition(ar);

            ar >> id;
            ar >> len;

            if (id != CHUNK_MAIN) {
                ReportImportError(filename);
                AfxThrowUserException();
            }

            endpos += len;
            m_importfilelength = endpos;

            m_hprogressbar = GetProgressBar();
            if (m_hprogressbar) {
                m_hprogressbar->Initialize();
                CString text;
                text.LoadString(IDS_IMPORT3DS);
                m_hprogressbar->SetMessage1(text);
                m_hprogressbar->SetMessage2(filename.GetNameOnly().Get());
            }
            DWORD currpos;
            while ((currpos = GetPosition(ar)) < endpos) {
                ar >> id;
                ar >> len;
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)currpos / m_importfilelength * 100));
                switch (id) {
                case CHUNK_M3DVERSION:
                {
                    DWORD version;
                    ar >> version;
                    break;
                }
                case CHUNK_OBJMESH:
                    ReadObjMeshChunk(ar, currpos + len, model);
                    break;
                default:
                    SetPosition(ar, currpos + len);
                    break;
                }
            }
        }
    CATCH(CUserException, e) // NOLINT(misc-throw-by-value-catch-by-reference)
        {
            ar.Close();
            file.Close();
            delete model;
            SetBasePath(oldbasepath);
            if (m_hprogressbar) {
                m_hprogressbar->Uninitialize();
                m_hprogressbar = nullptr;
            }
            return nullptr;
        }
    AND_CATCH_ALL(e)
        {
            ar.Close();
            file.Close();
            delete model;
            e->ReportError();
            SetBasePath(oldbasepath);
            if (m_hprogressbar) {
                m_hprogressbar->Uninitialize();
                m_hprogressbar = nullptr;
            }
            return nullptr;
        }
    END_CATCH_ALL
    SetBasePath(oldbasepath);
    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }
    return model;
}

void CHxtApp::ReadObjMeshChunk(CArchive &ar, const DWORD endpos, IEPolyModel *model) {
    WORD id;
    DWORD len, currpos;

    while ((currpos = GetPosition(ar)) < endpos) {
        ar >> id;
        ar >> len;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)currpos / m_importfilelength * 100));
        switch (id) {
        case CHUNK_OBJCHUNK:
            ReadObjChunk(ar, currpos + len, model);
            break;
        case CHUNK_MESHVERSION:
        {
            DWORD meshversion;
            ar >> meshversion;
            break;
        }
        case CHUNK_MASTERSCALE:
            ar >> m_masterscale; // inches
            m_masterscale /= 2.54F; // convert to cm
            break;
        case CHUNK_MATERIAL:
            ReadMaterial(ar, currpos + len, model);
            break;
        default:
            SetPosition(ar, currpos + len);
            break;
        }
    }
}

namespace {
    BOOL ReadColorChunk(CArchive &ar, RGBFloat &color) {
        WORD id;
        DWORD len;

        const DWORD currpos = GetPosition(ar);
        ar >> id;
        ar >> len;

        switch (id) {
        case CHUNK_RGB_F:
        {
            float r, g, b;
            ar >> r >> g >> b;
            color.Set(r, g, b);
            break;
        }
        case CHUNK_RGB_B:
        {
            BYTE r, g, b;
            ar >> r >> g >> b;
            color.Set((float)r / 255, (float)g / 255, (float)b / 255);
            break;
        }
        case CHUNK_LIN_RBG_B:
        {
            BYTE r, g, b;
            ar >> r >> g >> b;
            color.Set((float)r / 255, (float)g / 255, (float)b / 255);
            break;
        }
        case CHUNK_LIN_RBG_F:
        {
            float r, g, b;
            ar >> r >> g >> b;
            color.Set(r, g, b);
            break;
        }
        default:
            SetPosition(ar, currpos + len);
            return FALSE;
        }
        return TRUE;
    }

    BOOL ReadPercentChunk(CArchive &ar, float &percent) {
        WORD id;
        DWORD len;

        const DWORD currpos = GetPosition(ar);
        ar >> id;
        ar >> len;

        switch (id) {
        case CHUNK_PERCENT_F:
            ar >> percent;
            break;
        case CHUNK_PERCENT_W:
        {
            WORD p;
            ar >> p;
            percent = (float)p / 100;
            break;
        }
        default:
            SetPosition(ar, currpos + len);
            return FALSE;
        }
        return TRUE;
    }

    float MakeLuminance(const RGBFloat &color) {
        return 0.3F * color.m_red + 0.59F * color.m_green + 0.11F * color.m_blue;
    }
}

void CHxtApp::ReadMaterial(CArchive &ar, const DWORD endpos, IEPolyModel *model) {
    WORD id;
    DWORD len, currpos;
    Attr attr;
    RGBFloat color;
    float percent;

    auto *attrext = new AttrExt;
    while ((currpos = GetPosition(ar)) < endpos) {
        ar >> id;
        ar >> len;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)currpos / m_importfilelength * 100));
        switch (id) {
        case CHUNK_MAT_NAME:
            attrext->m_matname = ReadString(ar);
            strncpy_s(attr.m_name, 256, attrext->m_matname, 256);
            break;
        case CHUNK_MAT_AMBIENT:
            if (ReadColorChunk(ar, color))
                attr.m_ambiance = MakeLuminance(color);
            break;
        case CHUNK_MAT_DIFFUSE:
            if (ReadColorChunk(ar, color))
                attr.m_diffusecolor = color;
            break;
        case CHUNK_MAT_SPECULAR:
            if (ReadColorChunk(ar, color))
                attr.m_specularcolor = color;
            break;
        case CHUNK_MAT_SHININESS:
            if (ReadPercentChunk(ar, percent))
                attr.m_specularsize = 1.F - percent;
            break;
        case CHUNK_MAT_SHIN2PCT:
            if (ReadPercentChunk(ar, percent))
                attr.m_specularintensity = percent;
            break;
        /*
                 case CHUNK_MAT_SHIN3PCT:
                    if (ReadPercentChunk(ar, percent))
                       attr.SetSpecularIntensity(percent);
                    break;
        */
        case CHUNK_MAT_TRANSPARENCY:
            if (ReadPercentChunk(ar, percent))
                attr.m_transparency = percent;
            break;
        case CHUNK_MAT_TEXTUREMAP:
        {
            IEMapNodeExt *iemapnode = ReadTextureMap(ar, currpos + len, attrext);
            iemapnode->m_kind = IEMapNode::COLORMAP;
            break;
        }
        case CHUNK_MAT_SPECULARMAP:
        {
            IEMapNodeExt *iemapnode = ReadTextureMap(ar, currpos + len, attrext);
            iemapnode->m_kind = IEMapNode::SPECULARINTENSITYMAP;
            break;
        }
        case CHUNK_MAT_OPACMAP:
        {
            IEMapNodeExt *iemapnode = ReadTextureMap(ar, currpos + len, attrext);
            iemapnode->m_kind = IEMapNode::TRANSPARENCYMAP;
            break;
        }
        case CHUNK_MAT_REFLECTMAP:
        {
            IEMapNodeExt *iemapnode = ReadTextureMap(ar, currpos + len, attrext);
            iemapnode->m_kind = IEMapNode::MIRRORMAP;
            break;
        }
        case CHUNK_MAT_BUMPMAP:
        {
            IEMapNodeExt *iemapnode = ReadTextureMap(ar, currpos + len, attrext);
            iemapnode->m_kind = IEMapNode::BUMPMAP;
            break;
        }
        default:
            SetPosition(ar, currpos + len);
            break;
        }
    }
    m_attrextlist.SetAtGrow(model->m_attrlist.AddForce(attr), attrext);
}

IEMapNodeExt *CHxtApp::ReadTextureMap(CArchive &ar, const DWORD endpos, AttrExt *attrext) const {
    WORD id;
    DWORD len, currpos;
    auto *mapnodeext = new IEMapNodeExt;

    while ((currpos = GetPosition(ar)) < endpos) {
        ar >> id;
        ar >> len;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)currpos / m_importfilelength * 100));
        switch (id) {
        case CHUNK_PERCENT_F:
            ar >> mapnodeext->m_percent;
            break;
        case CHUNK_PERCENT_W:
        {
            WORD p;
            ar >> p;
            mapnodeext->m_percent = (float)p / 100;
            break;
        }
        case CHUNK_MAT_MAPNAME:
        {
            mapnodeext->m_filename = ReadString(ar);
            String filename = mapnodeext->m_filename;
            mapnodeext->m_filename = filename.GetAbsolutePath().Get();
            break;
        }
        //         case CHUNK_MAP_TILING:
        default:
            SetPosition(ar, currpos + len);
            break;
        }
    }

    attrext->m_mapnodeextlist.AddTail(mapnodeext);
    return mapnodeext;
}

void CHxtApp::ReadObjChunk(CArchive &ar, const DWORD endpos, IEPolyModel *model) {
    WORD id;
    DWORD len, currpos;

    const CString name = ReadString(ar);

    while ((currpos = GetPosition(ar)) < endpos) {
        ar >> id;
        ar >> len;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)currpos / m_importfilelength * 100));
        if (id == CHUNK_TRIMESH) {
            ReadTriMeshChunk(ar, currpos + len, model, name);
        } else {
            SetPosition(ar, currpos + len);
        }
        /*
                switch (id) {
                    case CHUNK_TRIMESH:
                        ReadTriMeshChunk(ar, currpos + len, model, name);
                        break;
                    default:
                        SetPosition(ar, currpos + len);
                        break;
                }
               */
    }
}

void CHxtApp::ReadTriMeshChunk(CArchive &ar, const DWORD endpos, IEPolyModel *model, const CString &name) {
    WORD id;
    DWORD len, currpos;
    MeshObject meshobj;

    meshobj.m_name = name;
    while ((currpos = GetPosition(ar)) < endpos) {
        ar >> id;
        ar >> len;
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)currpos / m_importfilelength * 100));
        switch (id) {
        case CHUNK_VERTLIST:
            ReadVertexList(ar, currpos + len, meshobj);
            break;
        case CHUNK_TRMATRIX:
        {
            for (int x = 0; x < 4; ++x)
                for (int y = 0; y < 3; ++y)
                    ar >> meshobj.m_matrix[y][x];
            // Apply MasterScale now.
            //            meshobj.m_matrix = ScaleV(Vector(m_masterscale)) * meshobj.m_matrix;
            break;
        }
        case CHUNK_FACELIST:
            ReadFaceList(ar, currpos + len, meshobj);
            break;
        case CHUNK_FACEMAT:
            ReadFaceMat(ar, currpos + len, meshobj, model);
            break;
        case CHUNK_UVLIST:
            ReadUVList(ar, currpos + len, meshobj);
            break;
        default:
            SetPosition(ar, currpos + len);
            break;
        }
    }
    AddMeshObjectToModel(meshobj, model);
}

void CHxtApp::ReadVertexList(CArchive &ar, [[maybe_unused]] DWORD endpos, MeshObject &meshobj) {
    WORD numverts;
    ar >> numverts;
    meshobj.m_vertexlist.SetSize(numverts);
    for (int i = 0; i < numverts; ++i) {
        Vector p;
        ar >> p.x >> p.z >> p.y;
        p.z = -p.z;
        meshobj.m_vertexlist[i] = p;
    }
}

void CHxtApp::ReadFaceList(CArchive &ar, [[maybe_unused]] DWORD endpos, MeshObject &meshobj) {
    WORD numfaces;
    ar >> numfaces;
    meshobj.m_facelist.SetSize(numfaces);
    for (int i = 0; i < numfaces; ++i) {
        ar >> meshobj.m_facelist[i].m_vertexid[0];
        ar >> meshobj.m_facelist[i].m_vertexid[1];
        ar >> meshobj.m_facelist[i].m_vertexid[2];
        ar >> meshobj.m_facelist[i].m_flags;
    }
}

void CHxtApp::ReadFaceMat(CArchive &ar, [[maybe_unused]] DWORD endpos, MeshObject &meshobj, IEPolyModel *model) {
    const CString matname = ReadString(ar);

    int matid = -1, i;
    for (i = 0; i < m_attrextlist.GetSize(); ++i)
        if (matname == m_attrextlist[i]->m_matname) {
            matid = i;
            break;
        }

    AttrExt *attrext = nullptr;
    // walk all maps for this face and make sure they have all been added them models maplist.  
    // maplist.Add will return indices for already existent maps
    if (matid != -1) {
        attrext = m_attrextlist[matid];
        for (POSITION pos = attrext->m_mapnodeextlist.GetHeadPosition(); pos;) {
            IEMapNodeExt *mapnodeext = attrext->m_mapnodeextlist.GetNext(pos);
            IEMap iemap;
            strcpy_s(iemap.m_filename, 256, mapnodeext->m_filename);
            mapnodeext->m_mapid = model->m_maplist.Add(iemap);
        }
    }

    WORD numfaces;
    ar >> numfaces;

    // now walk faces and build IEMapNodes list
    WORD faceid;
    for (i = 0; i < numfaces; ++i) {
        ar >> faceid;
        MeshObject::Face &face = meshobj.m_facelist[faceid];
        face.m_attrid = matid;
        if (attrext) {
            face.m_mapnodes.SetSize(attrext->m_mapnodeextlist.GetCount());
            int index = 0;
            for (POSITION pos = attrext->m_mapnodeextlist.GetHeadPosition(); pos; ++index) {
                const IEMapNodeExt *mapnodeext = attrext->m_mapnodeextlist.GetNext(pos);
                IEMapNode *mapnode = face.m_mapnodes[index] = new IEMapNode; // now make a unique mapnode for this face and copy the material attr extension attributes
                *mapnode = IEMapNode(*mapnodeext);
            }
        }
    }
}

void CHxtApp::ReadUVList(CArchive &ar, [[maybe_unused]] DWORD endpos, MeshObject &meshobj) {
    WORD numuvs;
    ar >> numuvs;
    meshobj.m_mapuvlist.SetSize(numuvs);
    for (int i = 0; i < numuvs; ++i) {
        Vector2 p;
        ar >> p;
        p.y = 1.F - p.y;
        meshobj.m_mapuvlist[i] = p;
    }
}

void CHxtApp::AddMeshObjectToModel(MeshObject &meshobj, IEPolyModel *model) {
    const int facecount = meshobj.m_facelist.GetSize();
    const int origsize = model->m_polyarray.GetSize();
    model->m_polyarray.SetSize(facecount + origsize);

    for (int i = 0; i < facecount; ++i) {
        MeshObject::Face &face = meshobj.m_facelist[i];
        IEPoly *poly = model->m_polyarray[i + origsize] = new IEPoly(nullptr);
        poly->m_vertexid[0] = model->m_vertexlist.Add(meshobj.m_vertexlist[face.m_vertexid[0]]);
        poly->m_vertexid[1] = model->m_vertexlist.Add(meshobj.m_vertexlist[face.m_vertexid[1]]);
        poly->m_vertexid[2] = model->m_vertexlist.Add(meshobj.m_vertexlist[face.m_vertexid[2]]);
        poly->m_vertexid[3] = poly->m_vertexid[0];
        poly->m_attrid = face.m_attrid;
        const int count = face.m_mapnodes.GetSize();
        poly->m_mapnodearray.SetSize(count);
        for (int k = 0; k < count; ++k) {
            // Rob the map nodes out of the faces now;
            IEMapNode *mapnode = poly->m_mapnodearray[k] = face.m_mapnodes[k];
            if (meshobj.m_mapuvlist.GetSize() == meshobj.m_vertexlist.GetSize()) {
                mapnode->m_uv[0] = meshobj.m_mapuvlist[face.m_vertexid[0]];
                mapnode->m_uv[1] = meshobj.m_mapuvlist[face.m_vertexid[1]];
                mapnode->m_uv[2] = meshobj.m_mapuvlist[face.m_vertexid[2]];
                mapnode->m_uv[3] = mapnode->m_uv[0];
            } else {
                // Bogus UV's, just pick arbitrary numbers
                mapnode->m_uv[0].Set(0.F, 1.F);
                mapnode->m_uv[1].Set(0.F, 0.F);
                mapnode->m_uv[2].Set(1.F, 0.F);
                mapnode->m_uv[3] = mapnode->m_uv[0];
            }
            face.m_mapnodes[k] = nullptr;
        }
    }
}
