// ReSharper disable CppCStyleCast
#include "StdAfx.h"
#include "StringLi.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "ImportModelDialog.h"
#include "HashMath.h"
#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HProgres.h"

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir;//not used for multiselect dlg
    const String ext("obj");
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

    CImportModelDialog cdlg;
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
//        String nameonly = filename.GetNameOnly();
        IEPolyModel *patchmodel = ImportOBJ(filename);
        if (patchmodel == nullptr) {
            ReportImportError(filename);
            continue;
        }
        if (!hmc->MergeIEModel(patchmodel, filename.Get(), cdlg.m_peaktolerance, TRUE, TRUE))
            ReportImportError(filename);

        delete patchmodel;
    }
    DeleteStringList(namelist);
    if (cdlg.m_openview)
        hmc->OpenView();

    return TRUE;
}

BOOL CHxtApp::OnImportObjectCacheContainer(HObjectCacheContainer *hocc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir;//not used for multiselect dlg
    const String ext("obj");
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
            DeleteStringList(namelist);
            ReportImportError(filename);
            return TRUE;
        }
        IEPolyModel *patchmodel = ImportOBJ(filename);
        if (patchmodel == nullptr) {
            ReportImportError(filename);
            continue;
        }
        if (!hmc->MergeIEModel(patchmodel, filename.Get(), cdlg.m_peaktolerance, FALSE, TRUE))
            ReportImportError(filename);

        delete patchmodel;
        if (cdlg.m_openview)
            hmc->OpenView();
    }

    DeleteStringList(namelist);
    return TRUE;
}

void CHxtApp::ReportImportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_IMPORTTITLE);
    CString text;
    text.LoadString(IDS_ERRORIMPORTINGMODEL);
    String temp = (LPCTSTR)text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

char *CHxtApp::BreakUp(char *str, IEPoly *poly, const int idx) {
    char buf[256]{};
    int count = 0;

    const int nummaps = poly->m_mapnodearray.GetSize();
    IEMapNode **mapnodearray = poly->m_mapnodearray.GetArray();

    char *chptr = str;
    while (*chptr == ' ') {
        chptr++;
    }

    if (*chptr == 0) {
        if (idx > 0) {
            poly->m_vertexid[idx] = poly->m_vertexid[idx - 1];
            poly->m_normalid[idx] = poly->m_normalid[idx - 1];
            if (nummaps > 0) {
                for (int i = 0; i < nummaps; ++i) {
                    const Vector2 lastvec = mapnodearray[i]->m_uv[idx - 1];
                    mapnodearray[i]->m_uv[idx].Set(lastvec.x, lastvec.y);
                }
            }
        }
        return chptr;
    }
    while (*chptr != 0 && *chptr != '/' && *chptr != ' ' && *chptr != 9) {
        buf[count++] = *chptr;
        chptr++;
    }
    buf[count] = 0;
    if (count > 0) {
        poly->m_vertexid[idx] = hash_math::abs(atoi_replace(buf)) - 1;
        //MessageBox(nullptr,buf,"Vertex",IDOK);
    }

    if (*chptr == 0 || *chptr == ' ') // && *chptr != 9)
        return chptr;
    chptr++;
    count = 0;
    while (*chptr != 0 && *chptr != '/' && *chptr != ' ' && *chptr != 9) {
        buf[count++] = *chptr;
        chptr++;
    }
    buf[count] = 0;
    if (count > 0) {
        if (nummaps > 0) {
            const int uvid = hash_math::abs(atoi_replace(buf)) - 1;
            const Vector uvvect = m_texturevertexlist.GetAt(uvid);
            for (int i = 0; i < nummaps; ++i) {
                mapnodearray[i]->m_uv[idx].Set(uvvect.x, uvvect.y);
            }
        }
        //MessageBox(nullptr,buf,"Texture",IDOK);
    }

    if (*chptr == 0 || *chptr == ' ') // && *chptr != 9)
        return chptr;
    chptr++;
    count = 0;
    while (*chptr != 0 && *chptr != '/' && *chptr != ' ' && *chptr != 9) {
        buf[count++] = *chptr;
        chptr++;
    }
    buf[count] = 0;
    if (count > 0) {
        poly->m_normalid[idx] = hash_math::abs(atoi_replace(buf)) - 1;
        //MessageBox(nullptr,buf,"Normal",IDOK);
    } else {
        m_normalsneedrebuild = TRUE;
    }

    return chptr;
}

void CHxtApp::IgnoreLine(FILE *fs, const char lastchar) {
    char ch = lastchar;
    while (!feof(fs) && ch != NEWLINE_CHAR) {
        ch = fgetc(fs);
    }
}

void CHxtApp::GetLine(FILE *fs, char *buffer, char *lastchar, const int maxsize) {
    BOOL start = FALSE;
    BOOL end = FALSE;
    buffer[0] = 0;
    int counter = 1;
    while (!feof(fs) && !end && counter < maxsize) {
        const char ch = fgetc(fs);
        if (ch != NEWLINE_CHAR) {
            if (!start) {
                buffer[0] = ch;
                start = TRUE;
            } else
                buffer[counter++] = ch;
        } else {
            *lastchar = ch;
            if (start) {
                end = TRUE;
                buffer[counter] = 0;
            }
        }
        ASSERT(counter < maxsize);
    }
    buffer[counter] = 0;
}

void CHxtApp::GetToken(FILE *fs, char *buffer, char *lastchar, const int maxsize) {
    BOOL start = FALSE;
    BOOL end = FALSE;
    buffer[0] = 0;
    int counter = 1;
    while (!feof(fs) && !end && counter < maxsize) {
        const char ch = fgetc(fs);
        if (ch != ' ' && ch != NEWLINE_CHAR && ch != 9) {
            if (!start) {
                buffer[0] = ch;
                start = TRUE;
            } else
                buffer[counter++] = ch;
        } else {
            *lastchar = ch;
            if (start) {
                end = TRUE;
                buffer[counter] = 0;
            }
        }
        ASSERT(counter < maxsize);
    }
    buffer[counter] = 0;
}

int CHxtApp::CountMaterials(const char *filename, const String &path) {
    FILE *fs;
    if (fopen_s(&fs, filename, "r") != 0) {
        //try to open with path
        const String filenamewithpath = path + filename;
        if (fopen_s(&fs, filenamewithpath.Get(), "r") != 0) {
            m_materialfile_found = false;
            return 0;
        }
    }

    int count = 0;
    char token[256]{};
    char lastchar{};
    while (!feof(fs)) {
        GetToken(fs, token, &lastchar, 256);
        //MessageBox(nullptr,token,"Token",IDOK);
        if (token[0] == 0)
            break;
        if (token[0] == '#') {
            IgnoreLine(fs, lastchar);
        } else {
            if (_strcmpi("newmtl", token) == 0) {
                count++;
                IgnoreLine(fs, lastchar);
            } else {
                IgnoreLine(fs, lastchar);
            }
        }
    }

    fclose(fs);

    return count;
}

int CHxtApp::FindMtlName(char list[256][256], const char *name) {
    for (int i = 0; i < 256; ++i) {
        if (!strcmp(list[i], name))
            return i;
    }
    return -1;
}

int CHxtApp::CountMaps(const int index) {
    int rv = 0;
    const AttrMap &attrmap = m_attrmap.ElementAt(index);
    if (attrmap.m_bmapKd)
        rv++;
    if (attrmap.m_bmapKs)
        rv++;
    if (attrmap.m_bmapKa)
        rv++;
    if (attrmap.m_bmapBump)
        rv++;
    if (attrmap.m_bmapd)
        rv++;

    return rv;
}

int CHxtApp::FindMapIndex(CString mapname) {
    return m_texturemaps.LookUp(mapname);
}

int CHxtApp::GetNextMap(const int mtlindex, int *lastmap) {
    const AttrMap &attrmap = m_attrmap.ElementAt(mtlindex);
    const int start = *lastmap + 1;
    for (int i = start; i <= 5; ++i) {
        if (i == 1 && attrmap.m_bmapKd) {
            *lastmap = i;
            return FindMapIndex(attrmap.m_mapKd);
        }
        if (i == 2 && attrmap.m_bmapKs) {
            *lastmap = i;
            return FindMapIndex(attrmap.m_mapKs);
        }
        if (i == 3 && attrmap.m_bmapKa) {
            *lastmap = i;
            return FindMapIndex(attrmap.m_mapKa);
        }
        if (i == 4 && attrmap.m_bmapBump) {
            *lastmap = i;
            return FindMapIndex(attrmap.m_mapBump);
        }
        if (i == 5 && attrmap.m_bmapd) {
            *lastmap = i;
            return FindMapIndex(attrmap.m_mapd);
        }
    }
    return -1;
}

int CHxtApp::GetMapType(const int index) {
    if (index == 1)
        return IEMapNode::COLORMAP;
    if (index == 2)
        return IEMapNode::DIFFUSEMAP;
    if (index == 3)
        return IEMapNode::AMBIANCEMAP;
    if (index == 4)
        return IEMapNode::BUMPMAP;
    if (index == 5)
        return IEMapNode::TRANSPARENCYMAP;
    return IEMapNode::COLORMAP;
}

IEPolyModel *CHxtApp::ImportOBJ(const String &pfilename, const BOOL isnewimport, const BOOL isprop, const float scaling) {
    float importscale = 1.F;
    if (isprop) {
        importscale = scaling;
    } else {
        importscale = GetRegistryValue("OBJ Plugin", "ImportScale", 1.F);
    }
    m_normalsneedrebuild = FALSE;
    char mtllist[256][256]{};
    for (auto &i: mtllist) {
        i[0] = 0;
    }

    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_IMPORTTITLE);
        m_hprogressbar->SetMessage1(text);
        m_hprogressbar->SetMessage2(pfilename.GetNameOnly().Get());
    }

    char filename[256]{};
    sprintf_s(filename, 256, "%s", pfilename.Get());
    FILE *fs;
    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;

    const String oldbasepath = GetBasePath();
    SetBasePath(filename);

    String pathonly;
    pathonly = pfilename.GetPathOnly() + "\\";
    auto *model = new IEPolyModel;

    int m_numnormals = 0;
    int m_numverticies = 0;
    int m_numfaces = 0;
    int m_nummaterials = 0;
    int m_numuvs = 0;
    char mtlfile[256]{};
    char token[256]{};
    char lastchar{};
    while (!feof(fs)) {
        GetToken(fs, token, &lastchar, 256);
        //MessageBox(nullptr,token,"Token",IDOK);
        if (token[0] == 0)
            break;
        if (token[0] == '#') {
            IgnoreLine(fs, lastchar);
        } else {
            if (_strcmpi("v", token) == 0) {
                m_numverticies++;
                IgnoreLine(fs, lastchar);
            } else if (_strcmpi("vn", token) == 0) {
                m_numnormals++;
                IgnoreLine(fs, lastchar);
            } else if (_strcmpi("vt", token) == 0) {
                m_numuvs++;
                IgnoreLine(fs, lastchar);
            } else if (_strcmpi("f", token) == 0) {
                m_numfaces++;
                IgnoreLine(fs, lastchar);
            } else if (_strcmpi("mtllib", token) == 0) {
                GetToken(fs, mtlfile, &lastchar, 256);
                m_nummaterials += CountMaterials(mtlfile, pathonly);
                IgnoreLine(fs, lastchar);
            } else {
                //MessageBox(nullptr,token,"Unknown Token Found and Ignored",IDOK);
                IgnoreLine(fs, lastchar);
            }
        }
    }

    fclose(fs);

    int totalitems = m_numverticies + m_numnormals + m_numfaces + m_numuvs;

    // Load Material Attributes List
    int count;
    if (m_nummaterials == 0) {
        model->m_attrlist.SetSize(1);
        m_attrmap.SetSize(1);
        count = 0;

        // Load a dummy material
        Attr &attr = model->m_attrlist.ElementAt(count);
        strcpy_s(attr.m_name, 256,"Surface OBJ dummy material");
        attr.m_diffusecolor.Set(1.F);
        attr.m_specularcolor.Set(1.F);
        attr.m_diffusefalloff = 1.F;
        attr.m_specularsize = 0.F;
        attr.m_specularintensity = 0.F;
        attr.m_ambiance = 0.F;
        attr.m_roughness = 0.F;
        attr.m_roughnessscale = 0.F;
        attr.m_reflectivity = 0.F;
        attr.m_transparency = 0.F;
        attr.m_refraction = 0.F;
    }
    if (m_nummaterials > 0) {
        model->m_attrlist.SetSize(m_nummaterials);
        m_attrmap.SetSize(m_nummaterials);
        count = -1;
        if (fopen_s(&fs, mtlfile, "r") != 0) {
            //try to open with path
            String filenamewithpath = pathonly + mtlfile;
            if (fopen_s(&fs, filenamewithpath.Get(), "r") != 0) {
                return nullptr;
            }
        }

        while (!feof(fs)) {
            GetToken(fs, token, &lastchar, 256);
            //MessageBox(nullptr,token,"Token",IDOK);
            if (token[0] == 0)
                break;
            if (token[0] == '#') {
                IgnoreLine(fs, lastchar);
            } else {
                if (_strcmpi("newmtl", token) == 0) {
                    count++;
                    GetToken(fs, token, &lastchar, 256);
                    strcpy_s(mtllist[count],256, token);
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    //initialize with default values
                    attr.m_diffusecolor.Set(1.F);
                    attr.m_specularcolor.Set(1.F);
                    attr.m_diffusefalloff = 1.F;
                    attr.m_specularsize = 0.F;
                    attr.m_specularintensity = 0.F;
                    attr.m_ambiance = 0.F;
                    attr.m_roughness = 0.F;
                    attr.m_roughnessscale = 0.F;
                    attr.m_reflectivity = 0.F;
                    attr.m_transparency = 0.F;
                    attr.m_refraction = 0.F;
                    sprintf_s(attr.m_name, 256, "Surface %s", token);
                    AttrMap &attrmap = m_attrmap.ElementAt(count);
                    attrmap.m_bmapKd = false;
                    attrmap.m_bmapKs = false;
                    attrmap.m_bmapKa = false;
                    attrmap.m_bmapBump = false;
                    attrmap.m_bmapd = false;
                    IgnoreLine(fs, lastchar);
                } else if (_strcmpi("Ns", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_specularintensity = atof_replace(token) / 200.0F;
                } else if (_strcmpi("Kd", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_diffusecolor.m_red = atof_replace(token);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_diffusecolor.m_green = atof_replace(token);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_diffusecolor.m_blue = atof_replace(token);
                } else if (_strcmpi("Ka", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_ambiancecolor.m_red = atof_replace(token);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_ambiancecolor.m_green = atof_replace(token);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_ambiancecolor.m_blue = atof_replace(token);
                } else if (_strcmpi("Ks", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_specularcolor.m_red = atof_replace(token);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_specularcolor.m_green = atof_replace(token);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_specularcolor.m_blue = atof_replace(token);
                } else if (_strcmpi("d", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_transparency = 1.F - atof_replace(token);
                } else if (_strcmpi("Ni", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_refraction = atof_replace(token);
                } else if (_strcmpi("illum", token) == 0) {
                    //                ASSERT(FALSE);
                } else if (_strcmpi("sharpness", token) == 0) {
                    Attr &attr = model->m_attrlist.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attr.m_roughness = 1.F - atof_replace(token);
                    attr.m_roughnessscale = 0.4F;
                } else if (_strcmpi("map_Kd", token) == 0) {
                    AttrMap &attrmap = m_attrmap.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attrmap.m_mapKd = token;
                    CString cst = token;
                    m_texturemaps.Add(cst);
                    attrmap.m_bmapKd = true;
                } else if (_strcmpi("map_Ks", token) == 0) {
                    AttrMap &attrmap = m_attrmap.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attrmap.m_mapKs = token;
                    CString cst = token;
                    m_texturemaps.Add(cst);
                    attrmap.m_bmapKs = true;
                } else if (_strcmpi("map_Ka", token) == 0) {
                    AttrMap &attrmap = m_attrmap.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attrmap.m_mapKa = token;
                    CString cst = token;
                    m_texturemaps.Add(cst);
                    attrmap.m_bmapKa = true;
                } else if (_strcmpi("map_Bump", token) == 0) {
                    AttrMap &attrmap = m_attrmap.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attrmap.m_mapBump = token;
                    CString cst = token;
                    m_texturemaps.Add(cst);
                    attrmap.m_bmapBump = true;
                } else if (_strcmpi("map_d", token) == 0) {
                    AttrMap &attrmap = m_attrmap.ElementAt(count);
                    GetToken(fs, token, &lastchar, 256);
                    attrmap.m_mapd = token;
                    CString cst = token;
                    m_texturemaps.Add(cst);
                    attrmap.m_bmapd = true;
                } else if (_strcmpi("refl", token) == 0) {
                    ASSERT(FALSE);
                } else {
                    IgnoreLine(fs, lastchar);
                }
            }
        }
        fclose(fs);
    }

    // Load Map List
    count = m_texturemaps.GetSize();
    model->m_maplist.SetSize(count);
    for (int i = 0; i < count; ++i) {
        IEMap &map = model->m_maplist.ElementAt(i);
        strcpy_s(map.m_filename, 256, m_texturemaps.GetAt(i));
        map.m_width = -1;
        map.m_height = -1;
    }

    // Load Vertex List
    model->m_vertexlist.SetSize(m_numverticies);
    count = 0;

    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;

    int curritem = 0;
    while (!feof(fs)) {
        GetToken(fs, token, &lastchar, 256);
        if (token[0] == 0)
            break;
        if (token[0] == '#') {
            IgnoreLine(fs, lastchar);
        } else {
            if (_strcmpi("v", token) == 0) {
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
                Vector &vec = model->m_vertexlist.ElementAt(count);
                GetToken(fs, token, &lastchar, 256);
                vec.x = atof_replace(token);
                GetToken(fs, token, &lastchar, 256);
                vec.y = atof_replace(token);
                GetToken(fs, token, &lastchar, 256);
                vec.z = atof_replace(token);
                vec *= importscale;
                IgnoreLine(fs, lastchar);
                count++;
            } else {
                IgnoreLine(fs, lastchar);
            }
        }
    }

    fclose(fs);

    // Load Normals Vertex List
    model->m_normallist.SetSize(m_numnormals);
    count = 0;

    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;

    while (!feof(fs)) {
        GetToken(fs, token, &lastchar, 256);
        if (token[0] == 0)
            break;
        if (token[0] == '#') {
            IgnoreLine(fs, lastchar);
        } else {
            if (_strcmpi("vn", token) == 0) {
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
                Vector &vec = model->m_normallist.ElementAt(count);
                GetToken(fs, token, &lastchar, 256);
                vec.x = atof_replace(token);
                GetToken(fs, token, &lastchar, 256);
                vec.y = atof_replace(token);
                GetToken(fs, token, &lastchar, 256);
                vec.z = atof_replace(token);
                vec.Normalize();
                IgnoreLine(fs, lastchar);
                count++;
            } else {
                IgnoreLine(fs, lastchar);
            }
        }
    }

    fclose(fs);

    // Load Texture Vertex List
    m_texturevertexlist.SetSize(m_numuvs);
    count = 0;

    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;

    while (!feof(fs)) {
        GetToken(fs, token, &lastchar, 256);
        if (token[0] == 0)
            break;
        if (token[0] == '#') {
            IgnoreLine(fs, lastchar);
        } else {
            if (_strcmpi("vt", token) == 0) {
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
                Vector &vec = m_texturevertexlist.ElementAt(count);
                GetToken(fs, token, &lastchar, 256);
                vec.x = atof_replace(token);
                if (vec.x > 1.F)
                    vec.x = 1.F;
                //vec.x = 1.f - vec.x;
                GetToken(fs, token, &lastchar, 256);
                vec.y = atof_replace(token);
                if (vec.y > 1.F)
                    vec.y = 1.F;
                vec.y = 1.F - vec.y;
                /*
                GetToken(fs,token,&lastchar);
                vec.z = atof_replace(token);
                if (vec.z > 1.f)
                    vec.z = 1.f;
                    */
                IgnoreLine(fs, lastchar);
                count++;
            } else {
                IgnoreLine(fs, lastchar);
            }
        }
    }

    fclose(fs);

    // Load Poly List
    model->m_polyarray.SetSize(m_numfaces);
    count = 0;
    int mtlindex = 0;
    int mapcount = 0;

    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;

    char line[8192]{};//blender may create such monster for face, maybe needs a dynamic array
    while (!feof(fs)) {
        GetToken(fs, token, &lastchar, 256);
        if (token[0] == 0)
            break;
        if (token[0] == '#') {
            IgnoreLine(fs, lastchar);
        } else {
            if (_strcmpi("usemtl", token) == 0) {
                GetToken(fs, token, &lastchar, 256);
                mtlindex = FindMtlName(mtllist, token);// + 1;
                if (mtlindex == -1) {
                    //Material not found !
                    mtlindex = 0;
                }
                mapcount = CountMaps(mtlindex);
            } else if (_strcmpi("f", token) == 0) {
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
                auto *poly = new IEPoly(nullptr);
                model->m_polyarray.SetAt(count, poly);
                poly->m_attrid = mtlindex;
                poly->m_mapnodearray.SetSize(mapcount);
                int mc = 0;
                int lastmap = 0;
                while (mc < mapcount) {
                    auto *mapnode = new IEMapNode;
                    poly->m_mapnodearray.SetAt(mc, mapnode);
                    const int mapid = GetNextMap(mtlindex, &lastmap);
                    mapnode->m_mapid = mapid;
                    mapnode->m_percent = 1.F;
                    mapnode->m_repeat.Set(1.F, 1.F);
                    mapnode->m_kind = GetMapType(lastmap);
                    mapnode->m_isseamless = TRUE;
                    mapnode->m_isgroupdecal = TRUE;
                    //sprintf_s(buf,"MapId: %d  MapType: %d",mapid,mapnode->m_kind);
                    //MessageBox(nullptr,buf,"Map",IDOK);
                    /*
                    for (int uvcount = 0; uvcount < 4;  ++uvcount)
                    fs >> mapnode->m_uv[uvcount]; // UV
                    */
                    mc++;
                }

                GetLine(fs, line, &lastchar, 8192);
                char *lineptr = line;
                // first vertex
                lineptr = BreakUp(lineptr, poly, 0);
                // second vertex
                lineptr = BreakUp(lineptr, poly, 1);
                // third vertex
                lineptr = BreakUp(lineptr, poly, 2);
                // fourth vertex
                BreakUp(lineptr, poly, 3);

                count++;
            } else {
                IgnoreLine(fs, lastchar);
            }
        }
    }

    fclose(fs);

    SetBasePath(oldbasepath);

    if (isprop && m_normalsneedrebuild) {
        //for some vertices no normals are saved 
        model->BuildNormalListForProp();
    }

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }

    if (isnewimport && GetRegistryBOOL("OBJ Plugin", "DisplayInfo", TRUE)) {
        m_numnormals = model->GetNumNormals();
        char buf[1024]{};
        if (m_materialfile_found) {
            sprintf_s(buf, 1024, "Imported:\nNum verticies: %d\nNum normals: %d\nNum Faces: %d\nNum Materials: %d\nNum UVs: %d", m_numverticies, m_numnormals, m_numfaces, m_nummaterials, m_numuvs);
        } else {
            sprintf_s(buf, 1024, "Imported:\nNum verticies: %d\nNum normals: %d\nNum Faces: %d\nNum UVs: %d\nNum Materials: %d\n\nWarning Materialfile\n\"%s\"\nnot found !\nUsing default material", m_numverticies, m_numnormals, m_numfaces, m_numuvs, m_nummaterials, mtlfile);
        }
        MessageBox(nullptr, buf, "Info", IDOK);
    }

    m_maplist.RemoveAll();
    m_texturevertexlist.Empty();
    m_attrmap.RemoveAll();
    m_texturemaps.Empty();

    return model;
}

void CHxtApp::LoadBones(FileStream &fs, IEBone **parentuplink, IEBone *parent) {
    BYTE child, sibling = TRUE;
    IEBone **siblinguplink = nullptr;

    while (sibling && !fs.Eof()) {
        fs.Read(&child, 1);
        fs >> sibling;
        auto *bone = new IEBone;

        if (parentuplink) {
            *parentuplink = bone;
            parentuplink = nullptr;
        }

        if (siblinguplink)
            *siblinguplink = bone;
        fs.ParseToken(bone->m_name, '\0');

        fs >> bone->m_pivotpos;
        fs >> bone->m_endpos;
        fs >> bone->m_rollpos;

        int count;
        fs >> count;
        bone->m_vertexidarray.SetSize(count);
        for (int i = 0; i < count; ++i) {
            fs >> bone->m_vertexidarray[i];
        }

        if (child)
            LoadBones(fs, &bone->m_child, bone);

        siblinguplink = sibling ? &bone->m_sibling : nullptr;
    }
}
