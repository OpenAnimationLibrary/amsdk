// KB  9/25/02  \Ken95\Plugin\HXT\DXF\Import.cpp

#include "StdAfx.h"
#include "StringLi.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "ImportModelDialog.h"

#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HProgres.h"

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    const String ext("DXF");
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
        IEPolyModel *patchmodel = ImportDXF(filename);
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

BOOL CHxtApp::OnImportObjectCacheContainer(HObjectCacheContainer *hocc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    const String ext("DXF");
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
        IEPolyModel *patchmodel = ImportDXF(filename);
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

void CHxtApp::IgnoreLine(FILE *fs, const char lastchar) {
    char ch = lastchar;
    while (!feof(fs) && ch != NEWLINE_CHAR) {
        ch = fgetc(fs);
    }
}

void CHxtApp::GetToken(FILE *fs, char *buffer, char *lastchar) {
    BOOL start = FALSE;
    BOOL end = FALSE;
    buffer[0] = 0;
    int counter = 1;
    while (!feof(fs) && !end) {
        const char ch = fgetc(fs);
        if (ch != ' ' && ch != NEWLINE_CHAR) {
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
    }
    buffer[counter] = 0;
}

int CHxtApp::FindVertex(const IEPolyModel *model, const Vector vertex, const int countverticies) {
    constexpr int id = -1;

    for (int counter = countverticies - 1; counter >= 0; counter--) {
        if (const Vector vec = model->m_vertexlist.GetAt(counter); vec.x == vertex.x && vec.y == vertex.y && vec.z == vertex.z)
            return counter;
    }

    return id;
}

int CHxtApp::CreateVertex(IEPolyModel *model, const Vector vertex, int *countverticies) {
    int id = FindVertex(model, vertex, *countverticies);
    //   char msg[100];
    //   sprintf_s(msg, "FindVertex = %d", id);
    //   AfxMessageBox(msg, MB_OK);
    if (id == -1) {
        id = *countverticies;
        Vector &vec = model->m_vertexlist.ElementAt(*countverticies);
        vec.x = vertex.x;
        vec.y = vertex.y;
        vec.z = vertex.z;
        *countverticies = *countverticies + 1;
    }

    return id;
}

IEPolyModel *CHxtApp::ImportDXF(const String &pfilename, const BOOL isnewimport) {
    FILE *fs;
    char filename[256];
    int m_numverticies = 0;
    int m_numfaces = 0;
    char lastchar;
    char token[256];
    char value[256];
    int countverticies = 0;
    int countfaces = 0;

    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        m_hprogressbar->SetMessage1(text);
        m_hprogressbar->SetMessage2(pfilename.GetNameOnly().Get());
    }

    sprintf_s(filename, 256, "%s", pfilename.Get());
    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;
    auto *model = new IEPolyModel;

    while (!feof(fs)) {
        GetToken(fs, token, &lastchar);
        if (token[0] == 0)
            break;
        if (_strcmpi("0", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            if (_strcmpi("3DFACE", value) == 0) {
                m_numfaces++;
            }
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("10", token) == 0) {
            m_numverticies++;
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("11", token) == 0) {
            m_numverticies++;
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("12", token) == 0) {
            m_numverticies++;
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("13", token) == 0) {
            m_numverticies++;
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            IgnoreLine(fs, lastchar);
        } else {
            //MessageBox(nullptr,token,"Unknown Token Found and Ignored",IDOK);
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            IgnoreLine(fs, lastchar);
        }
    }

    fclose(fs);

    // Load Material Attributes List
    model->m_attrlist.SetSize(1);
    for (int i = 0; i < 1; ++i) {
        Attr &attr = model->m_attrlist.ElementAt(i);
        BYTE green, blue;
        BYTE red = green = blue = 255;
        attr.m_diffusecolor.m_red = (float)red / 255.0F;
        attr.m_diffusecolor.m_green = (float)green / 255.0F;
        attr.m_diffusecolor.m_blue = (float)blue / 255.0F;
        attr.m_diffusefalloff = 1.F;
        red = green = blue = 255;
        attr.m_specularcolor.m_red = (float)red / 255.0F;
        attr.m_specularcolor.m_green = (float)green / 255.0F;
        attr.m_specularcolor.m_blue = (float)blue / 255.0F;
        attr.m_specularsize = 0.F;
        attr.m_specularintensity = 0.F;
        attr.m_ambiance = 0.F;
        attr.m_roughness = 0.F;
        attr.m_roughnessscale = 0.F;
        attr.m_reflectivity = 0.F;
        attr.m_transparency = 0.F;
        attr.m_refraction = 0.F;
    }

    // Load Normals Vertex List
    model->m_normallist.SetSize(0);
    // Load Texture Maps List
    model->m_maplist.SetSize(0);
    // Load Vertex List
    model->m_vertexlist.SetSize(m_numverticies);
    // Load Poly List
    model->m_polyarray.SetSize(m_numfaces);

    // Load up the faces and verticies at the same time
    int vertexid1, vertexid2, vertexid3, vertexid4;
    BOOL bvertex1 = FALSE;
    BOOL bvertex2 = FALSE;
    BOOL bvertex3 = FALSE;
    BOOL bvertex4 = FALSE;
    BOOL b_started = FALSE;
    IEPoly *poly{nullptr};

    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;
    while (!feof(fs)) {
        Vector vertex4;
        Vector vertex3;
        Vector vertex2;
        Vector vertex1;
        GetToken(fs, token, &lastchar);
        //MessageBox(nullptr,token,"Token",IDOK);
        if (token[0] == 0)
            break;
        if (_strcmpi("0", token) == 0) {
            //         AfxMessageBox("token = \"0\"", MB_OK);
            if (b_started) {
                //            AfxMessageBox("b_started = TRUE", MB_OK);
                b_started = FALSE;
                if (bvertex1) {
                    vertexid1 = CreateVertex(model, vertex1, &countverticies);
                }
                if (bvertex2) {
                    vertexid2 = CreateVertex(model, vertex2, &countverticies);
                }
                if (bvertex3) {
                    vertexid3 = CreateVertex(model, vertex3, &countverticies);
                }
                if (bvertex4) {
                    vertexid4 = CreateVertex(model, vertex4, &countverticies);
                } else
                    vertexid4 = vertexid3;
                poly->m_vertexid[0] = vertexid1;
                poly->m_vertexid[1] = vertexid2;
                poly->m_vertexid[2] = vertexid3;
                poly->m_vertexid[3] = vertexid4;
                if (m_hprogressbar)
                    m_hprogressbar->SetProgress((int)((float)countfaces / m_numfaces * 100));
            }
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            //         char msg[100];
            //         sprintf_s(msg, "value = %d", value);
            //         AfxMessageBox(value, MB_OK);
            if (_strcmpi("3DFACE", value) == 0) {
                b_started = TRUE;
                poly = new IEPoly(nullptr);
                model->m_polyarray.SetAt(countfaces++, poly);
                poly->m_mapnodearray.SetSize(0);
                poly->m_attrid = 0;
                bvertex1 = FALSE;
                bvertex2 = FALSE;
                bvertex3 = FALSE;
                bvertex4 = FALSE;
            }
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("10", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex1.x = atof_replace(value);
            bvertex1 = TRUE;
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("11", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex2.x = atof_replace(value);
            bvertex2 = TRUE;
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("12", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex3.x = atof_replace(value);
            bvertex3 = TRUE;
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("13", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex4.x = atof_replace(value);
            bvertex4 = TRUE;
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("20", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex1.y = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("21", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex2.y = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("22", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex3.y = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("23", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex4.y = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("30", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex1.z = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("31", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex2.z = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("32", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex3.z = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else if (_strcmpi("33", token) == 0) {
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            vertex4.z = atof_replace(value);
            IgnoreLine(fs, lastchar);
        } else {
            //MessageBox(nullptr,token,"Unknown Token Found and Ignored",IDOK);
            IgnoreLine(fs, lastchar);
            GetToken(fs, value, &lastchar);
            IgnoreLine(fs, lastchar);
        }
    }

    fclose(fs);

    model->m_vertexlist.SetSize(countverticies);
    /*
       count = 0;
   
    if (fopen_s(&fs, filename, "r") != 0)
          return nullptr;
   
       while (!feof(fs)) {
           GetToken(fs,token,&lastchar);
           if (token[0] == 0)
               break;
           if (token[0] == '#') IgnoreLine(fs,lastchar);
           else if (_strcmpi("v",token) == 0) {
               Vector &vec = model->m_vertexlist.ElementAt(count);
               GetToken(fs,token,&lastchar);
               vec.x = atof_replace(token);
               GetToken(fs,token,&lastchar);
               vec.y = atof_replace(token);
               GetToken(fs,token,&lastchar);
               vec.z = atof_replace(token);
               IgnoreLine(fs,lastchar);
               count++;
           }
           else {
               IgnoreLine(fs,lastchar);
           }
       }
   
       fclose(fs);
   
       count = 0;
   
    if (fopen_s(&fs, filename, "r") != 0)
          return nullptr;
   
       while (!feof(fs)) {
           GetToken(fs,token,&lastchar);
           if (token[0] == 0)
               break;
           if (token[0] == '#') IgnoreLine(fs,lastchar);
           else if (_strcmpi("f",token) == 0) {
               IEPoly *poly = new IEPoly(nullptr);
               model->m_polyarray.SetAt(count, poly);
               poly->m_mapnodearray.SetSize(0);
               poly->m_attrid = 0;
   
               // first vertex
               GetToken(fs,token,&lastchar);
               IgnoreLine(fs,lastchar);
               count++;
           }
           else {
               IgnoreLine(fs,lastchar);
           }
       }
   
       fclose(fs);
    */
    /*
    String oldbasepath = GetBasePath();
    SetBasePath(filename);

 // Load Material Attributes List
    fs >> count; //Num Attr
    model->m_attrlist.SetSize(count);
    for (int i =0; i < count; ++i) {
       Attr &attr = model->m_attrlist.ElementAt(i);
       BYTE red, green, blue;
       fs >> red >> green >> blue;
       attr.m_diffusecolor.red = (float)red/255.0f;
       attr.m_diffusecolor.green = (float)green/255.0f;
       attr.m_diffusecolor.blue = (float)blue/255.0f;
       fs >> attr.m_diffusefalloff;
       fs >> red >> green >> blue;
       attr.m_specularcolor.red = (float)red/255.0f;
       attr.m_specularcolor.green = (float)green/255.0f;
       attr.m_specularcolor.blue = (float)blue/255.0f;
       fs >> attr.m_specularsize;
       fs >> attr.m_specularintensity;
       fs >> attr.m_ambiance;
       fs >> attr.m_roughness;
       fs >> attr.m_roughnessscale;
       fs >> attr.m_reflectivity;
       fs >> attr.m_transparency;
       fs >> attr.m_refraction;
    }

 // Load Texture Maps List
    fs >> count; //Num Textures
    model->m_maplist.SetSize(count);
    for (i=0; i < count; ++i) {
       IEMap &map = model->m_maplist.ElementAt(i);
       char temp[256];
       fs.ParseToken(temp, '\0');
       String mapname = temp;
       mapname = mapname.GetAbsolutePath();
       strcpy(map.m_filename, mapname.Get());
       fs >> map.m_width;
       fs >> map.m_height;
    }


    // Load Poly List
    fs >> count;
    model->m_polyarray.SetSize(count);
    for (i =0; i < count; ++i) {
       IEPoly *poly = new IEPoly(nullptr);
       model->m_polyarray.SetAt(i, poly);

       fs >> poly->m_attrid;
       fs >> poly->m_vertexid[0] >> poly->m_vertexid[1] >> poly->m_vertexid[2] >> poly->m_vertexid[3];
       for (int n = 0; n < 4; n++ )
          fs >> poly->m_normalid[n];

       // Load Poly Texture Maps
       int mapcount;
       fs >> mapcount;
       poly->m_mapnodearray.SetSize(mapcount);
       for (int mc=0; mc < mapcount; ++mc) {
          IEMapNode *mapnode = new IEMapNode;
          poly->m_mapnodearray.SetAt(mc, mapnode);
          fs >> mapnode->m_mapid;
          fs >> mapnode->m_percent;
          fs >> mapnode->m_repeat;
          BYTE tbyte;
          fs >> tbyte; // kind
          mapnode->m_kind = tbyte;
          fs >> tbyte; // seamless;
          mapnode->m_isseamless = tbyte;

          for (int uvcount = 0; uvcount < 4;  ++uvcount)
             fs >> mapnode->m_uv[uvcount]; // UV
       }
    }

    //Load Bones
    //LoadBones(fs, &model->m_bonehead, nullptr);
    SetBasePath(oldbasepath);
    */

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }

    if (isnewimport) {
        char buf[1024];
        sprintf_s(buf, 1024, "Imported:\nNum verticies: %d\nNum Faces: %d", countverticies, countfaces);
        MessageBox(nullptr, buf, "Info", IDOK);
    }

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
