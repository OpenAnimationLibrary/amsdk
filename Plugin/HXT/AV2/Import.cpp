// KB  12/7/2004  \Plugin\HXT\AV2\Import.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "StringLi.h"
#include "ImportModelDialog.h"
#include "SDK/HModel.h"
#include "SDK/Misc.h"

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) const {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("AV2");
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
        IEPatchModel *patchmodel = ImportAV2(filename);
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
    const String ext("AV2");
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
            ReportImportError(filename);
            DeleteStringList(namelist);
            return TRUE;
        }
        IEPatchModel *patchmodel = ImportAV2(filename);
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

IEPatchModel *CHxtApp::ImportAV2(const String &pfilename) {
    int tint;
    int count;
    BYTE tbyte;
    char name[3];
    FileStream fs;
    String filename = pfilename;

    if (!fs.Open(filename, FileMode::HS_BINARY | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS))
        return nullptr;

    auto *model = new IEPatchModel;

    fs.Read(name, 3);

    if (name[0] != 'A' || name[1] != 'V' || name[2] != '2') {
        fs.Close();
        CString msg, title;
        msg.LoadString(IDS_INVALIDFILEFORMAT);
        String temp = msg;
        temp.Replace("%1", filename);
        msg = temp.Get();
        title.LoadString(IDS_IMPORTTITLE);
        MessageBox(GetMainApplicationWnd(), msg, title, MB_ICONEXCLAMATION);
        return nullptr;
    }

    fs >> tint; //Version
    if (tint != 2) {
        fs.Close();
        CString msg, title;
        msg.LoadString(IDS_INVALIDVERSION);
        title.LoadString(IDS_IMPORTTITLE);
        MessageBox(GetMainApplicationWnd(), msg, title, MB_ICONEXCLAMATION);
        return nullptr;
    }

    const String oldbasepath = GetBasePath();
    SetBasePath(filename);

    // Load Material Attributes List
    fs >> count; //Num Attr
    model->m_attrlist.SetSize(count);
    int i;
    for (i = 0; i < count; ++i) {
        Attr &attr = model->m_attrlist.ElementAt(i);
        BYTE red, green, blue;
        fs >> red >> green >> blue;
        attr.m_diffusecolor.m_red = (float)red / 255.0F;
        attr.m_diffusecolor.m_green = (float)green / 255.0F;
        attr.m_diffusecolor.m_blue = (float)blue / 255.0F;
        fs >> attr.m_diffusefalloff;
        fs >> red >> green >> blue;
        attr.m_specularcolor.m_red = (float)red / 255.0F;
        attr.m_specularcolor.m_green = (float)green / 255.0F;
        attr.m_specularcolor.m_blue = (float)blue / 255.0F;
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
    for (i = 0; i < count; ++i) {
        IEMap &map = model->m_maplist.ElementAt(i);
        char temp[256];
        fs.ParseToken(temp, '\0');
        String mapname = temp;
        mapname = mapname.GetAbsolutePath();

        strcpy_s(map.m_filename, 256, mapname.Get());
        fs >> map.m_width;
        fs >> map.m_height;
    }

    // Load Vertex List
    fs >> count;
    model->m_vertexlist.SetSize(count);

    for (i = 0; i < count; ++i)
        fs >> model->m_vertexlist[i];

    // Load Tangent Control Vertex List
    fs >> count;
    model->m_controlvertexlist.SetSize(count);
    for (i = 0; i < count; ++i)
        fs >> model->m_controlvertexlist[i];

    // Load Patch List
    fs >> count;
    model->m_patcharray.SetSize(count);
    for (i = 0; i < count; ++i) {
        auto *patch = new IEPatch(nullptr);
        model->m_patcharray.SetAt(i, patch);

        fs >> patch->m_attrid;
        fs >> patch->m_vertexid[0] >> patch->m_vertexid[1] >> patch->m_vertexid[2] >> patch->m_vertexid[3];
        for (int &t: patch->m_controlvertexid)
            fs >> t;

        // Load Patch Texture Maps
        int mapcount;
        fs >> mapcount;
        patch->m_mapnodearray.SetSize(mapcount);
        for (int mc = 0; mc < mapcount; ++mc) {
            auto *mapnode = new IEPatchMapNode;
            patch->m_mapnodearray.SetAt(mc, mapnode);
            fs >> mapnode->m_mapid;
            fs >> mapnode->m_percent;
            fs >> mapnode->m_repeat;
            fs >> tbyte; // kind
            mapnode->m_kind = tbyte;
            fs >> tbyte; // seamless;
            mapnode->m_isseamless = tbyte;

            int uvcount;
            for (uvcount = 0; uvcount < 4; ++uvcount)
                fs >> mapnode->m_uv[uvcount]; // UV

            for (uvcount = 0; uvcount < 8; ++uvcount)
                fs >> mapnode->m_controluv[uvcount]; // UV
        }
    }

    //Load Bones
    LoadBones(fs, &model->m_bonehead, nullptr);
    SetBasePath(oldbasepath);
    fs.Close();
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
