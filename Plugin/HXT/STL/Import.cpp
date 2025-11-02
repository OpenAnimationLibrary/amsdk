// ReSharper disable CppClangTidyCertErr33C
#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "ImportModelDialog.h"
#include "StringLi.h"

#include "SDK/Misc.h"
#include "SDK/HModel.h"

#pragma warning(disable : 4996) //warning C4996: 'strcmpi': The POSIX name for this item is deprecated.


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

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) const {

    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("STL");
    StringList *namelist;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }

    if (namelist == nullptr) {
        CString cption1;
        cption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTINGMODEL);
        MessageBox(GetMainApplicationWnd(), text, cption1, MB_OK);
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
        IEPolyModel *patchmodel = ImportSTL(filename);
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

BOOL CHxtApp::OnImportObjectCacheContainer(HObjectCacheContainer *hocc) const {

    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("STL");
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
        text.LoadString(IDS_ERRORIMPORTINGMODEL);
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
        IEPolyModel *patchmodel = ImportSTL(filename);
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

int TokenizeSTL(const String &in, String &out) {
    if (in.Find("vertex") == 0) {
        out = in.Right(in.GetLength() - 6);
        out.TrimLeft();
        return 4; //vertex
    }
    if (in.Find("facet normal") == 0) {
        out = in.Right(in.GetLength() - 12);
        out.TrimLeft();
        return 2; //facet start 
    }
    if (in.Find("outer loop") == 0) {
        return 3; //vertex start
    }
    if (in.Find("endloop") == 0) {
        return 5; //vertex end
    }
    if (in.Find("endfacet") == 0) {
        return 6; //facet end
    }
    if (in.Find("solid") == 0) {
        out = in.Right(in.GetLength() - in.Find(' '));
        return 1; //modelstart name
    }
    if (in.Find("endsolid") == 0) {
        return 7; //modelend
    }
    return -1;
}

/*
solid Vase_neu
  facet normal 1.995854e-001 -9.798540e-001 7.202197e-003
    outer loop
      vertex  2.461380e+001 -2.437020e-001 0.000000e+000
      vertex  2.943235e+001 5.784500e-001 0.000000e+000
      vertex  2.927782e+001 5.663130e-001 2.836386e+000
    endloop
  endfacet
endsolid Vase_neu
*/

IEPolyModel *CHxtApp::ImportSTL(const String &pfilename, BOOL isnewimport, BOOL isprop) {
    FILE *fs;
    char filename[256];
    sprintf_s(filename, 256, "%s", pfilename.Get());
    if (fopen_s(&fs, filename, "r") != 0)
        return nullptr;
    char line[7];
    if (fgets(line, 6, fs) == nullptr) {
        fclose(fs);
        return nullptr;
    }

    fclose(fs);
    bool is_ascii = false;
    if (_stricmp(line, "solid") == 0) {
        is_ascii = true;
    }
    STL_FACET import_element;
    CArray<STL_FACET, STL_FACET> import_array;
    if (!is_ascii) {
        FILE *fp;
        fopen_s(&fp, filename, "rb");
        if (fp == nullptr) {
            return nullptr;
        }

        int facenum;
        fseek(fp, 80, SEEK_SET);
        fread(&facenum, sizeof(int), 1, fp);
        for (int i = 0; i < facenum; ++i) {
            short attr;
            Vector norm;
            Vector tri[3];
            fread(&norm, sizeof(Vector), 1, fp);
            fread(&tri, sizeof(Vector), 3, fp);
            fread(&attr, sizeof(short), 1, fp);
            import_element.normal = norm.Normalized();
            import_element.vertex[0] = tri[0];
            import_element.vertex[1] = tri[1];
            import_element.vertex[2] = tri[2];
            import_array.Add(import_element);
        }
        fclose(fp);

    } else {
        FileStream fsa;
        if (!fsa.Open(pfilename, FileMode::HS_ASCII | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS)) {
            return nullptr;
        }
        String temp, rtemp;
        int vertexnum = 0;
        float x, y, z;
        while (fsa.ReadLine(temp)) {
            temp.TrimLeft();
            const int rc = TokenizeSTL(temp, rtemp);
#ifdef _DEBUG
            if (rc == 1) {
                //Todo 
                const String name = rtemp;
            }
#endif
            if (rc == 2) {
                //normal
                sscanf_s(rtemp.Get_const_char(), "%f %f %f", &x, &y, &z);
                import_element.normal.Set(x, y, z);
                import_element.normal.Normalize();
                vertexnum = 0;
            }
            if (rc == 4) {
                //vertex
                sscanf_s(rtemp.Get_const_char(), "%f %f %f", &x, &y, &z);
                import_element.vertex[vertexnum].Set(x, y, z);
                vertexnum++;
            }
            if (rc == 6) {
                if (vertexnum == 3) {
                    import_array.Add(import_element);
                }
            }
        }
        fsa.Close();

    }

    auto *model = new IEPolyModel;
    model->m_attrlist.SetSize(1);
    Attr &attr = model->m_attrlist.ElementAt(0);
    BYTE green, blue;
    BYTE red = green = blue = 255;
    attr.m_diffusecolor.m_red = (float)red / 255.0F;
    attr.m_diffusecolor.m_green = (float)green / 255.0F;
    attr.m_diffusecolor.m_blue = (float)blue / 255.0F;
    attr.m_diffusefalloff = 1.0F;
    red = green = blue = 255;
    attr.m_specularcolor.m_red = (float)red / 255.0F;
    attr.m_specularcolor.m_green = (float)green / 255.0F;
    attr.m_specularcolor.m_blue = (float)blue / 255.0F;
    attr.m_specularsize = 0.0F;
    attr.m_specularintensity = 0.0F;
    attr.m_ambiance = 0.0F;
    attr.m_roughness = 0.0F;
    attr.m_roughnessscale = 0.0F;
    attr.m_reflectivity = 0.0F;
    attr.m_transparency = 0.0F;
    attr.m_refraction = 0.0F;

    const int numpoly = import_array.GetSize();
    if (!isprop) {
        const float scale = GetRegistryValue("STL Plugin", "Scale", 1.0F);
        if (scale != 1.F) {
            for (int i = 0; i < numpoly; ++i) {
                import_array[i].vertex[0] *= scale;
                import_array[i].vertex[1] *= scale;
                import_array[i].vertex[2] *= scale;
            }
        }
    }
    model->m_polyarray.SetSize(numpoly);
    for (int i = 0; i < numpoly; ++i) {
        //      IEPoly *poly = model->m_polyarray[i] = new IEPoly(nullptr);
        auto *poly = new IEPoly(nullptr);
        model->m_polyarray.SetAt(i, poly);

        poly->m_mapnodearray.SetSize(0);
        poly->m_attrid = 0;
        poly->m_vertexid[0] = model->m_vertexlist.Add(import_array[i].vertex[0]);
        poly->m_vertexid[1] = model->m_vertexlist.Add(import_array[i].vertex[1]);
        poly->m_vertexid[2] = model->m_vertexlist.Add(import_array[i].vertex[2]);
        poly->m_vertexid[3] = poly->m_vertexid[0];
        const int id_added = model->m_normallist.AddWithoutKey(import_array[i].normal);
        poly->m_normalid[0] = id_added;
        poly->m_normalid[1] = id_added;
        poly->m_normalid[2] = id_added;
        poly->m_normalid[3] = id_added;
    }

    if (isprop) {
        //for some vertices no normals are saved 
        model->BuildNormalList();
    }

    if (isnewimport) {
        const int numnormals = model->GetNumNormals();
        char buf[1024];
        sprintf_s(buf, 1024, "Imported:\nNum triangles: %d\nNum normals: %d\n", numpoly, numnormals);
        MessageBox(nullptr, buf, "Info", IDOK);
    }

    return model;
}
