#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "ExportModelDialog.h"
#include "ExportModelsDialog.h"
#include "ExportActionsDialog.h"
#include "ExportChorDialog.h"
#include "TextureMapDialog.h"
#include "F_Protos.h"
#include "Files.h"

#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"
#include "SDK/HProgres.h"
#ifdef _DEBUG
#include "SDK/HPatch.h"
#endif

BOOL CHxtApp::OnExportModelCache(HModelCache *hmc) {

    CExportModelDialog cdlg(hmc->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;
    m_exportnormals = TRUE;
    CWaitCursor wait;
    String modelmapfilename = "";
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    if (m_iemp.m_isbuildmodelmap) {
        m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
        m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
        modelmapfilename = cdlg.m_filename.GetWithoutSuffix() + ".bmp";
    }
    m_iemp.m_isbuildmaparray = (BITFIELDS16)TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    m_iemp.m_ignorevisibility = !cdlg.m_visibility;
    m_bexporttriangles = cdlg.m_btriangles;
    m_discarddegenerated = cdlg.m_discardfaces;
    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
    if (model == nullptr) {
        ReportExportError(cdlg.m_filename);
        return TRUE;
    }
    m_exportnormals = cdlg.m_exportnormals;
    const BOOL result = ExportOBJ(model, cdlg.m_filename);
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
        String temp = (LPCTSTR)msg;
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
    m_exportnormals = TRUE;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    if (m_iemp.m_isbuildmodelmap) {
        m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
        m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    }
    m_iemp.m_isbuildmaparray = (BITFIELDS16)TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    m_bexporttriangles = cdlg.m_btriangles;
    m_discarddegenerated = cdlg.m_discardfaces;
    m_exportnormals = cdlg.m_exportnormals;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const Time totaltime = hac->GetTotalTime();
    const String basefilename = cdlg.m_filename;

    HModel *hm = hac->EditWithModelCache(hmc);
    needsmapdlg = TRUE;
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

        const BOOL result = ExportOBJ(model, filename, FALSE);
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
    m_exportnormals = TRUE;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    if (m_iemp.m_isbuildmodelmap) {
        m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
        m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    }
    m_iemp.m_isbuildmaparray = (BITFIELDS16)TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    m_discarddegenerated = cdlg.m_discardfaces;
    m_exportnormals = cdlg.m_exportnormals;

    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HModelCache *hmc = cdlg.m_selected.GetNext(pos);
        String filename = hmc->GetName();
        filename = filename.GetNameOnlyWithoutSuffix() + ".OBJ";
        filename = CombineNameToPath(cdlg.m_dir, filename);
        String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }
        const BOOL result = ExportOBJ(model, filename);
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
    m_exportnormals = TRUE;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    if (m_iemp.m_isbuildmodelmap) {
        m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
        m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    }
    m_iemp.m_isbuildmaparray = (BITFIELDS16)TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    m_discarddegenerated = FALSE;
    m_exportnormals = cdlg.m_exportnormals;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();

    needsmapdlg = TRUE;
    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HActionCache *hac = cdlg.m_selected.GetNext(pos);
        HModelCache *hmc = hac->GetDefaultModelCache();

        if (hmc == nullptr) {
            CString msg, title;
            msg.LoadString(IDS_ACTIONHASNOMODELASSIGNED);
            String temp = (LPCTSTR)msg;
            temp.Replace("%1", hac->GetName());
            msg = temp.Get();
            title.LoadString(IDS_EXPORTTITLE);
            MessageBox(GetMainApplicationWnd(), msg, title, MB_OK);
            return TRUE;
        }

        const Time totaltime = hac->GetTotalTime();
        String basefilename = hac->GetName();
        basefilename = basefilename.GetNameOnlyWithoutSuffix() + "-0000.OBJ";
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

            const BOOL result = ExportOBJ(model, filename, FALSE);
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
    CExportChorDialog cdlg(hchor->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;

    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    if (m_iemp.m_isbuildmodelmap) {
        m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
        m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    }
    m_iemp.m_isbuildmaparray = (BITFIELDS16)TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    m_discarddegenerated = cdlg.m_discardfaces;
    m_exportnormals = cdlg.m_exportnormals;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    HTimeProperty *totaltime = hchor->GetTotalTime();
    String basefilename = cdlg.m_filename;
    String filename;
    String modelmapfilename;
    String modelname;

    if (cdlg.m_allframes) {
        needsmapdlg = TRUE;
        for (Time time = Time(); time <= totaltime->GetValue(); time.StepFrame(fps)) {
            const int frame = time.GetFrameInt(fps);
            if (cdlg.m_exportmethod == 0) {
                filename = basefilename.NumberFrame(frame);
                modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
                IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
                if (model == nullptr) {
                    ReportExportError(filename);
                    return TRUE;
                }

                const BOOL result = ExportOBJ(model, filename);
                DeleteIEModel(model);

                if (!result) {
                    ReportExportError(filename);
                    return TRUE;
                }
            } else {
                if (cdlg.m_exportmethod == 1) {
                    for (HModel *hmodel = hchor->GetChildModel(); hmodel; hmodel = hmodel->GetNextModelInChor()) {
                        modelname = hmodel->GetMatchName();
                        filename = basefilename.GetPathOnly() + NATIVESEPARATOR + modelname + "_.obj";
                        filename = filename.NumberFrame(frame);
                        modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
                        IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get(), hmodel);
                        if (model == nullptr) {
                            ReportExportError(filename);
                            return TRUE;
                        }

                        const BOOL result = ExportOBJ(model, filename, TRUE);
                        DeleteIEModel(model);

                        if (!result) {
                            ReportExportError(filename);
                            return TRUE;
                        }
                    }
                } else {
                    IEPolyModel *model = nullptr;
                    filename = basefilename.NumberFrame(frame);
                    modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
                    for (HModel *hmodel = hchor->GetChildModel(); hmodel; hmodel = hmodel->GetNextModelInChor()) {
                        model = hchor->BuildExportModel(model, &m_iemp, Time(), modelmapfilename.Get(), hmodel);
                        if (model == nullptr) {
                            ReportExportError(filename);
                            return TRUE;
                        }
                    }
                    if (!model) {
                        ReportExportError(filename);
                        return TRUE;
                    }
                    if (m_exportnormals)
                        model->BuildNormalList();
                    const BOOL result = ExportOBJ(model, filename, FALSE);
                    DeleteIEModel(model);
                    if (!result) {
                        ReportExportError(filename);
                        return TRUE;
                    }
                }
            }
        }
    } else {
        constexpr Time time;
        hchor->SetTime(time);
        if (cdlg.m_exportmethod == 0) {
            filename = basefilename;
            modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
            IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
            if (model == nullptr) {
                ReportExportError(filename);
                return TRUE;
            }
            const BOOL result = ExportOBJ(model, filename);
            DeleteIEModel(model);
            if (!result) {
                ReportExportError(filename);
                return TRUE;
            }
        } else {
            if (cdlg.m_exportmethod == 1) {
                for (HModel *hmodel = hchor->GetChildModel(); hmodel; hmodel = hmodel->GetNextModelInChor()) {
                    modelname = hmodel->GetMatchName();
                    filename = basefilename.GetPathOnly() + NATIVESEPARATOR + modelname + "_.obj";
                    //                    filename = filename;
                    modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
                    IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get(), hmodel);
                    if (model == nullptr) {
                        ReportExportError(filename);
                        return TRUE;
                    }
                    const BOOL result = ExportOBJ(model, filename, TRUE);
                    DeleteIEModel(model);
                    if (!result) {
                        ReportExportError(filename);
                        return TRUE;
                    }
                }
            } else {
                IEPolyModel *model = nullptr;
                filename = basefilename;
                modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
                for (HModel *hmodel = hchor->GetChildModel(); hmodel; hmodel = hmodel->GetNextModelInChor()) {
                    model = hchor->BuildExportModel(model, &m_iemp, time, modelmapfilename.Get(), hmodel);
                    if (model == nullptr) {
                        ReportExportError(filename);
                        return TRUE;
                    }
                }
                if (!model) {
                    ReportExportError(filename);
                    return TRUE;
                }
                if (cdlg.m_rebuildnormals && m_exportnormals)
                    model->BuildNormalList();
                const BOOL result = ExportOBJ(model, filename);
                DeleteIEModel(model);
                if (!result) {
                    ReportExportError(filename);
                    return TRUE;
                }
            }
        }
    }
    return TRUE;
}

/*
BOOL CHxtApp::OnExportChor(HChor *hchor)
{
CExportModelDialog cdlg(hchor->GetName());
if (cdlg.DoModal()!=IDOK)
return TRUE;

CWaitCursor wait;
m_iemp.m_isbuildmodelmap = TRUE;
m_iemp.m_isbuildmaparray = TRUE;
m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
m_iemp.m_subtype = (SubType)cdlg.m_subtype;
m_bexporttriangles = cdlg.m_btriangles;

HProject *hp = GetHProject();
float fps = hp->GetFPS();
HTimeProperty *totaltime = hchor->GetTotalTime();
String basefilename = cdlg.m_filename;

for (Time time; time<=totaltime->GetValue(); time.StepFrame(fps)) {
int frame = time.GetFrameInt(fps);
String filename = basefilename.NumberFrame(frame);
String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
if (model==nullptr) {
ReportExportError(filename);
return FALSE;
}

BOOL result = ExportOBJ(model, filename);
DeleteIEModel(model);

if (!result) {
ReportExportError(filename);
return FALSE;
}
}
return TRUE;
}
*/
void CHxtApp::ReportExportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_EXPORTTITLE);
    CString text;
    text.LoadString(IDS_ERROREXPORTINGMODEL);
    String temp = (LPCTSTR)text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

static void CountBoneBranch(const IEBone *bone, int *count) {
    for (; bone; bone = bone->m_sibling) {
        (*count)++;
        if (bone->m_child)
            CountBoneBranch(bone->m_child, count);
    }
}

int CHxtApp::CountBones(const IEPolyModel *model) {
    int count = 0;
    CountBoneBranch(model->m_bonehead, &count);
    return count;
}

void CHxtApp::CopyMaps(const String &path, IEPolyModel *model) {
    for (int i = 0; i < model->m_maplist.GetSize(); ++i) {
        const IEMap &map = model->m_maplist[i];
        String sourcefilename = map.m_filename;
        String destfilename = CombineNameToPath(path, m_maplist[i]);
        if (!HashCopyFile(sourcefilename, destfilename)) {
            CString text;
            text.LoadString(IDS_UNABLETOCOPYFILE);
            String stext = (LPCTSTR)text;
            stext.Replace("%1", sourcefilename);
            stext.Replace("%2", destfilename);
            AfxMessageBox(stext.Get(), MB_OK);
        }
    }
}

void CHxtApp::MakeUniqueName(String &filename, const int count) {
    const int digits = (int)log10((float)count) + 1;

    filename = filename.Left(7 - digits) + "_" + (String)count;
    for (int i = 0; i < m_maplist.GetSize(); ++i) {
        if (m_maplist[i] == (CString)filename.Get()) {
            MakeUniqueName(filename, count + 1);
            return;
        }
    }
}

BOOL CHxtApp::ExportOBJ(IEPolyModel *model, const String &filename, const BOOL savename) {
    FileStream fs;
    int totalitems, curritem = 0;
    //    char buf[256];

    if (model->m_maplist.GetSize()) {
        BOOL need_dlg = FALSE;
        for (int i = 0; i < model->m_maplist.GetSize(); ++i) {
            IEMap &map = model->m_maplist[i];
            String filename1 = map.m_filename;
//            String suffix = filename1.GetSuffixOnly();
            filename1 = filename1.GetNameOnlyWithoutSuffix();
            const String &origfilename = filename;

            filename1 = filename1.Left(8);
            if (filename1 != origfilename) {
                need_dlg = TRUE;
            }
        }
        if (need_dlg) {
            if (needsmapdlg) {
                CTextureMapDialog cdlg(this, model);
                if (cdlg.DoModal() != IDOK)
                    return TRUE;
                needsmapdlg = FALSE;
                if (cdlg.m_copymaps)
                    CopyMaps(filename.GetPathOnly(), model);
            } else {
                m_maplist.SetSize(model->m_maplist.GetSize());
                for (int i = 0; i < model->m_maplist.GetSize(); ++i) {
                    IEMap &map = model->m_maplist[i];
                    String filename1 = map.m_filename;
                    String suffix = filename1.GetSuffixOnly();
                    filename1 = filename1.GetNameOnlyWithoutSuffix();
                    MakeUniqueName(filename1);
                    filename1 += "." + suffix;
                    m_maplist[i] = (CString)filename1.Get();
                }
                CopyMaps(filename.GetPathOnly(), model);
            }
        } else {
            m_maplist.SetSize(model->m_maplist.GetSize());
            for (int i = 0; i < model->m_maplist.GetSize(); ++i) {
                IEMap &map = model->m_maplist[i];
                String filename1 = map.m_filename;
                String suffix = filename1.GetSuffixOnly();
                filename1 = filename1.GetNameOnlyWithoutSuffix();
                filename1 += "." + suffix;
                m_maplist[i] = (CString)filename1.Get();
            }
            CopyMaps(filename.GetPathOnly(), model);
        }
    }

    if (!fs.Open(filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS))
        return FALSE;

    const String oldpath = GetBasePath();
    SetBasePath(filename); // used to make texturemap filenames relative to model exported location
    // used in conjuction with String::GetRelativePath

    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        m_hprogressbar->SetMessage1(text);
        m_hprogressbar->SetMessage2(filename.GetNameOnly().Get());
    }

    fs << "# OBJ - Exported from Animation Master" << nl;
    fs << VERSION << nl;
    fs << nl;
    String mtlfilename = filename.GetWithoutSuffix() + ".mtl";
    //   sprintf_s(buf,"mtllib %s",mtlfilename.GetNameOnly().Get()); 
    //   fs << buf << nl;
    fs << "mtllib " << mtlfilename.GetNameOnly() << nl;
    fs << "o " << filename.GetNameOnly() << nl;

    AddAttributesFromTexture(model);
    totalitems = model->m_attrlist.GetSize() + model->m_vertexlist.GetSize() + model->m_polyarray.GetSize();
    if (m_exportnormals) {
        totalitems += model->m_normallist.GetSize();
    }
    SaveAttributes(mtlfilename, model, totalitems, curritem);
    SaveVertexList(fs, model, totalitems, curritem);
    fs << nl;
    SaveUVs(fs, model, totalitems, curritem);
    fs << nl;
    if (m_exportnormals) {
        SaveNormalList(fs, model, totalitems, curritem);
        fs << nl;
    }
    String groupname;
    if (savename) {
        groupname = filename.GetNameOnlyWithoutSuffix();
    }
    SavePolys(fs, model, totalitems, curritem, groupname);
    fs << nl;

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }

    SetBasePath(oldpath);
    return TRUE;
}

String CHxtApp::FindTextureFilename(IEPolyModel *model, const String &tofind) {
    const int mapcount = model->m_maplist.GetSize();
    const IEMap *maparray = model->m_maplist.GetArray();
    for (int j = 0; j < mapcount; ++j) {
        String mapname = maparray[j].m_filename;
        mapname = mapname.GetNameOnlyWithoutSuffix();
        if (strcmp(mapname.Get(), tofind.Get()) == 0) {
            return m_maplist[j];
        }
    }
    return "";
}

void CHxtApp::SaveAttributes(const String &filename, IEPolyModel *model, int &totalitems, int &curritem) {
    FileStream fs;

    if (!fs.Open(filename, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS))
        return;

    const int count = model->m_attrlist.GetSize();
    BOOL istexture;
    //fs << count << nl;
    Attr *attrarray = model->m_attrlist.GetArray();
    IEMap *maparray = model->m_maplist.GetArray();
    const int mapcount = model->m_maplist.GetSize();
    char buf[256]{};
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        if (strcmp("UnKnown", attrarray[i].m_name) == 0) {
            sprintf_s(buf, 256, "newmtl %s%d", attrarray[i].m_name, i);
            istexture = FALSE;
        } else {
            sprintf_s(buf, 256, "newmtl %s", attrarray[i].m_name);
            istexture = TRUE;
        }
        fs << buf << nl;
        sprintf_s(buf, 256, "Ns %d", (int)(attrarray[i].m_specularintensity * 200));
        fs << buf << nl;
        sprintf_s(buf, 256, "Ka %f %f %f", attrarray[i].m_ambiancecolor.m_red, attrarray[i].m_ambiancecolor.m_green, attrarray[i].m_ambiancecolor.m_blue);
        fs << buf << nl;
        sprintf_s(buf, 256, "Kd %f %f %f", attrarray[i].m_diffusecolor.m_red, attrarray[i].m_diffusecolor.m_green, attrarray[i].m_diffusecolor.m_blue);
        fs << buf << nl;
        sprintf_s(buf, 256, "Ks %f %f %f", attrarray[i].m_specularcolor.m_red, attrarray[i].m_specularcolor.m_green, attrarray[i].m_specularcolor.m_blue);
        fs << buf << nl;
        sprintf_s(buf, 256, "d %f", (float)1.0 - attrarray[i].m_transparency);
        fs << buf << nl;
        sprintf_s(buf, 256, "Ni %f", attrarray[i].m_refraction);
        fs << buf << nl;
        sprintf_s(buf, 256, "sharpness %f", (float)1.0 - attrarray[i].m_roughness);
        fs << buf << nl;
        if (istexture) {
            for (int j = 0; j < mapcount; ++j) {
                String mapname = maparray[j].m_filename;
                mapname = mapname.GetNameOnlyWithoutSuffix();
                if (strcmp(mapname.Get(), attrarray[i].m_name) == 0) {
                    String sname_map;
                    for (int h = 0; h < m_attrmap.GetSize(); ++h) {
                        if (m_attrmap[h].m_bmapKd) {
                            sname_map = (String)m_attrmap[h].m_mapKd;
                            if (strcmp(sname_map.Get(), attrarray[i].m_name) == 0) {
                                if (m_attrmap[h].m_hasadditionalmaps) {
                                    if (m_attrmap[h].m_bmapKd) {
                                        sname_map = (String)m_attrmap[h].m_mapKd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Kd %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKa) {
                                        sname_map = (String)m_attrmap[h].m_mapKa;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ka %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKs) {
                                        sname_map = (String)m_attrmap[h].m_mapKs;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ks %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapd) {
                                        sname_map = (String)m_attrmap[h].m_mapd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_d %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapBump) {
                                        sname_map = (String)m_attrmap[h].m_mapBump;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_bump %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                } else {
                                    sprintf_s(buf, 256, "map_Kd %s", ((String)m_maplist[j]).Get());
                                    fs << buf << nl;
                                }
                                break;
                            }
                        }
                        if (m_attrmap[h].m_bmapKa) {
                            sname_map = (String)m_attrmap[h].m_mapKa;
                            if (strcmp(sname_map.Get(), attrarray[i].m_name) == 0) {
                                if (m_attrmap[h].m_hasadditionalmaps) {
                                    if (m_attrmap[h].m_bmapKd) {
                                        sname_map = (String)m_attrmap[h].m_mapKd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Kd %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKa) {
                                        sname_map = (String)m_attrmap[h].m_mapKa;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ka %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKs) {
                                        sname_map = (String)m_attrmap[h].m_mapKs;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ks %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapd) {
                                        sname_map = (String)m_attrmap[h].m_mapd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_d %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapBump) {
                                        sname_map = (String)m_attrmap[h].m_mapBump;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_bump %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                } else {
                                    sprintf_s(buf, 256, "map_Ka %s", ((String)m_maplist[j]).Get());
                                    fs << buf << nl;
                                }
                                break;
                            }
                        }
                        if (m_attrmap[h].m_bmapKs) {
                            sname_map = (String)m_attrmap[h].m_mapKs;
                            if (strcmp(sname_map.Get(), attrarray[i].m_name) == 0) {
                                if (m_attrmap[h].m_hasadditionalmaps) {
                                    if (m_attrmap[h].m_bmapKd) {
                                        sname_map = (String)m_attrmap[h].m_mapKd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Kd %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKa) {
                                        sname_map = (String)m_attrmap[h].m_mapKa;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ka %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKs) {
                                        sname_map = (String)m_attrmap[h].m_mapKs;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ks %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapd) {
                                        sname_map = (String)m_attrmap[h].m_mapd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_d %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapBump) {
                                        sname_map = (String)m_attrmap[h].m_mapBump;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_bump %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                } else {
                                    sprintf_s(buf, 256, "map_Ks %s", ((String)m_maplist[j]).Get());
                                    fs << buf << nl;
                                }
                                break;
                            }
                        }
                        if (m_attrmap[h].m_bmapd) {
                            sname_map = (String)m_attrmap[h].m_mapd;
                            if (strcmp(sname_map.Get(), attrarray[i].m_name) == 0) {
                                if (m_attrmap[h].m_hasadditionalmaps) {
                                    if (m_attrmap[h].m_bmapKd) {
                                        sname_map = (String)m_attrmap[h].m_mapKd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Kd %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKa) {
                                        sname_map = (String)m_attrmap[h].m_mapKa;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ka %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKs) {
                                        sname_map = (String)m_attrmap[h].m_mapKs;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ks %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapd) {
                                        sname_map = (String)m_attrmap[h].m_mapd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_d %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapBump) {
                                        sname_map = (String)m_attrmap[h].m_mapBump;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_bump %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                } else {
                                    sprintf_s(buf, 256, "map_d %s", ((String)m_maplist[j]).Get());
                                    fs << buf << nl;
                                }
                                break;
                            }
                        }
                        if (m_attrmap[h].m_bmapBump) {
                            sname_map = (String)m_attrmap[h].m_mapBump;
                            if (strcmp(sname_map.Get(), attrarray[i].m_name) == 0) {
                                if (m_attrmap[h].m_hasadditionalmaps) {
                                    if (m_attrmap[h].m_bmapKd) {
                                        sname_map = (String)m_attrmap[h].m_mapKd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Kd %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKa) {
                                        sname_map = (String)m_attrmap[h].m_mapKa;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ka %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapKs) {
                                        sname_map = (String)m_attrmap[h].m_mapKs;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_Ks %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapd) {
                                        sname_map = (String)m_attrmap[h].m_mapd;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_d %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                    if (m_attrmap[h].m_bmapBump) {
                                        sname_map = (String)m_attrmap[h].m_mapBump;
                                        String texturename = FindTextureFilename(model, sname_map);
                                        sprintf_s(buf, 256, "map_bump %s", texturename.Get());
                                        fs << buf << nl;
                                    }
                                } else {
                                    sprintf_s(buf, 256, "map_bump %s", ((String)m_maplist[j]).Get());
                                    fs << buf << nl;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        fs << nl;
    }
    fs.Close();
}

int CHxtApp::FindAttributesFromName(IEPolyModel *model, const String &name) {
    const int attrcount = model->m_attrlist.GetSize();
    const Attr *attrarray = model->m_attrlist.GetArray();
    for (int i = 0; i < attrcount; ++i) {
        if (strcmp(attrarray[i].m_name, name.Get()) == 0) {
            return i;
        }
    }
    return -1;
}

void CHxtApp::AddAttributesFromTexture(IEPolyModel *model) {
    //    Attr *attrarray = model->m_attrlist.GetArray();
    IEMap *maparray = model->m_maplist.GetArray();
    const int mapcount = model->m_maplist.GetSize();
    m_attrmap.SetSize(mapcount + 1);
    const int polycount = model->m_polyarray.GetSize();
    IEPoly **polyarray = model->m_polyarray.GetArray();
    int attrmapcount = 0;
    //    int lastadded = 0;
    for (int i = 0; i < polycount; ++i) {
        const int mapnodecount = polyarray[i]->m_mapnodearray.GetSize();
        IEMapNode **mapnodearray = polyarray[i]->m_mapnodearray.GetArray();
        for (int mi = 0; mi < mapnodecount; ++mi) {
            if (mapnodearray[mi]->m_kind == IEMapNode::COLORMAP || mapnodearray[mi]->m_kind == IEMapNode::BUMPMAP || mapnodearray[mi]->m_kind == IEMapNode::AMBIANCEMAP || mapnodearray[mi]->m_kind == IEMapNode::SPECULARINTENSITYMAP || mapnodearray[mi]->m_kind == IEMapNode::TRANSPARENCYMAP) {
                String name = maparray[mapnodearray[mi]->m_mapid].m_filename;
                String suffix = name.GetSuffixOnly();
                const BOOL ismodelmap = m_iemp.m_isbuildmodelmap && suffix == "bmp";
                name = name.GetNameOnlyWithoutSuffix();
                int rc = FindAttributesFromName(model, name);
                if (rc == -1) {
                    if (m_iemp.m_isbuildmodelmap) {
                        if (ismodelmap) {
                            Attr oldattr;
                            rc = model->m_attrlist.Add(oldattr);
                            Attr &attr = model->m_attrlist.ElementAt(rc);
                            strncpy_s(attr.m_name, 256, name.Get(), 256);
                            attr.m_name[255] = '\0';
                            attr.m_diffusecolor.Set(1.F);
                            polyarray[i]->m_attrid = rc;
                            AttrMap &attrmap = m_attrmap.ElementAt(attrmapcount);
                            attrmap.m_bmapKs = false;
                            attrmap.m_bmapKa = false;
                            attrmap.m_bmapBump = false;
                            attrmap.m_bmapd = false;
                            attrmap.m_bmapKd = true;
                            attrmap.m_mapKd = attr.m_name;
                            attrmapcount++;
                        }
                    } else {
                        if (mapnodearray[mi]->m_mapid_parent != -1) {
                            //                     Attr &attr = model->m_attrlist.ElementAt((lastadded));
//                            AttrMap attrmap;
                            int i1;
                            BOOL found = FALSE;
                            for (i1 = 0; i1 < m_attrmap.GetSize(); ++i1) {
                                AttrMap &attrmap1 = m_attrmap.ElementAt(i1);
                                if (attrmap1.m_mapid == mapnodearray[mi]->m_mapid_parent) {
                                    found = TRUE;
                                    break;
                                }
                            }
                            if (found) {
                                AttrMap &attrmap1 = m_attrmap.ElementAt(i1);
                                switch (mapnodearray[mi]->m_kind) {
                                    case IEMapNode::COLORMAP:
                                        attrmap1.m_hasadditionalmaps = true;
                                        attrmap1.m_bmapKd = true;
                                        attrmap1.m_mapKd = name.Get();
                                        break;
                                    case IEMapNode::AMBIANCEMAP:
                                        attrmap1.m_hasadditionalmaps = true;
                                        attrmap1.m_bmapKa = true;
                                        attrmap1.m_mapKa = name.Get();
                                        break;
                                    case IEMapNode::BUMPMAP:
                                        attrmap1.m_hasadditionalmaps = true;
                                        attrmap1.m_bmapBump = true;
                                        attrmap1.m_mapBump = name.Get();
                                        break;
                                    case IEMapNode::SPECULARINTENSITYMAP:
                                        attrmap1.m_hasadditionalmaps = true;
                                        attrmap1.m_bmapKs = true;
                                        attrmap1.m_mapKs = name.Get();
                                        break;
                                    case IEMapNode::TRANSPARENCYMAP:
                                        attrmap1.m_hasadditionalmaps = true;
                                        attrmap1.m_bmapd = true;
                                        attrmap1.m_mapd = name.Get();
                                        break;
                                    default:
                                        break;
                                }
                            }
                        } else {
                            Attr oldattr;
                            rc = model->m_attrlist.Add(oldattr);
                            Attr &attr = model->m_attrlist.ElementAt(rc);
                            strncpy_s(attr.m_name, 256, name.Get(), 256);
                            attr.m_name[255] = '\0';
                            attr.m_diffusecolor.Set(1.F);
                            polyarray[i]->m_attrid = rc;
                            AttrMap &attrmap = m_attrmap.ElementAt(attrmapcount);
                            attrmap.m_hasadditionalmaps = false;
                            attrmap.m_bmapKd = false;
                            attrmap.m_bmapKs = false;
                            attrmap.m_bmapKa = false;
                            attrmap.m_bmapBump = false;
                            attrmap.m_bmapd = false;
                            attrmap.m_mapid = mapnodearray[mi]->m_mapid;
                            switch (mapnodearray[mi]->m_kind) {
                                case IEMapNode::COLORMAP:
                                    attrmap.m_bmapKd = true;
                                    attrmap.m_mapKd = attr.m_name;
                                    break;
                                case IEMapNode::AMBIANCEMAP:
                                    attrmap.m_bmapKa = true;
                                    attrmap.m_mapKa = attr.m_name;
                                    break;
                                case IEMapNode::BUMPMAP:
                                    attrmap.m_bmapBump = true;
                                    attrmap.m_mapBump = attr.m_name;
                                    break;
                                case IEMapNode::SPECULARINTENSITYMAP:
                                    attrmap.m_bmapKs = true;
                                    attrmap.m_mapKs = attr.m_name;
                                    break;
                                case IEMapNode::TRANSPARENCYMAP:
                                    attrmap.m_bmapd = true;
                                    attrmap.m_mapd = attr.m_name;
                                    break;
                                default:
                                    break;
                            }
                            attrmapcount++;
                        }
                    }
                } else {
                    polyarray[i]->m_attrid = rc;
                }
            }
        }
    }
}

void CHxtApp::SaveTextureMaps(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const {
    const int count = model->m_maplist.GetSize();
    fs << count << nl;
    const IEMap *maparray = model->m_maplist.GetArray();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        String mapname = maparray[i].m_filename;
        mapname = mapname.GetRelativePath();
        fs.Write(mapname.Get(), mapname.GetLength());
        fs << '\0';
        fs << maparray[i].m_width << sp << maparray[i].m_height << nl;
    }
}

void CHxtApp::SaveVertexList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const {
    const int count = model->m_vertexlist.GetSize();
    const float exportscale = GetRegistryValue("OBJ Plugin", "ExportScale", 1.F);
    Vector *vectorarray = model->m_vertexlist.GetArray();
    if (exportscale != 1.F) {
        for (int i = 0; i < count; ++i) {
            if (m_hprogressbar)
                m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
            vectorarray[i] *= exportscale;
            fs << "v " << vectorarray[i].x << " " << vectorarray[i].y << " " << vectorarray[i].z << nl;
        }
    } else {
        for (int i = 0; i < count; ++i) {
            if (m_hprogressbar)
                m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
            fs << "v " << vectorarray[i].x << " " << vectorarray[i].y << " " << vectorarray[i].z << nl;
        }
    }
    fs << "# " << count << " verticies" << nl;
}

typedef struct structUV {
    float u{0.F};
    float v{0.F};
} typeUV;

#include <vector>

void CHxtApp::SaveUVs(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem) {
    //    char buf[40];
    m_buvcount = false;
    const int count = model->m_polyarray.GetSize();
    typeUV tempUV{};
    std::vector<typeUV> uvcoord;
    int uvnum = 0;
    IEPoly **polyarray = model->m_polyarray.GetArray();
    for (int i = 0; i < count; ++i) {
        const int mapnodecount = polyarray[i]->m_mapnodearray.GetSize();
        if (mapnodecount > 0) {
            IEMapNode **mapnodearray = polyarray[i]->m_mapnodearray.GetArray();
            for (int mi = 0; mi < mapnodecount; ++mi) {
                if (mapnodearray[mi]->m_mapid_parent == -1) {
                    m_buvcount = true;
                    if (mapnodearray[mi]->m_kind == IEMapNode::COLORMAP || mapnodearray[mi]->m_kind == IEMapNode::BUMPMAP || mapnodearray[mi]->m_kind == IEMapNode::AMBIANCEMAP || mapnodearray[mi]->m_kind == IEMapNode::SPECULARINTENSITYMAP || mapnodearray[mi]->m_kind == IEMapNode::TRANSPARENCYMAP) {
                        for (int c = 0; c < 4; ++c) {
                            tempUV.u = mapnodearray[mi]->m_uv[c].x;
                            tempUV.v = 1.F - mapnodearray[mi]->m_uv[c].y;
                            if (tempUV.u > 1.F && mapnodearray[mi]->m_repeat.x == 1)
                                tempUV.u = 1.F;
                            if (tempUV.v > 1.F && mapnodearray[mi]->m_repeat.y == 1)
                                tempUV.v = 1.F;
                            uvcoord.push_back(tempUV);
                            uvnum++;
                            polyarray[i]->m_uvid[c] = uvnum;
                        }
                    }
                }
            }
        }
    }
    if (m_buvcount) {
        int uvcount = 0;
        std::vector<typeUV>::const_iterator c1_Iter = uvcoord.cbegin();
        for (; c1_Iter != uvcoord.cend(); ++c1_Iter, ++uvcount) {
            tempUV = *c1_Iter;
            fs << "vt " << tempUV.u << " " << tempUV.v << nl;
        }
        fs << "# " << uvcount << " texture coordinates" << nl;
    } else {
        fs << "# Dummy Texture Coordinate" << nl;
        fs << "vt 0.00000 1.00000" << nl;
        fs << "# 1 texture coordinates" << nl;
    }
    fs << nl;
}

void CHxtApp::SaveNormalList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const {
    const int count = model->m_normallist.GetSize();
    const Vector *vectorarray = model->m_normallist.GetArray();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        fs << "vn " << vectorarray[i].x << " " << vectorarray[i].y << " " << vectorarray[i].z << nl;
    }
    fs << "# " << count << " normals" << nl;
}

BOOL IsDegeneratedFace(const int id0, const int id1, const int id2) {
    int same = 0;
    if (id0 == id1 || id0 == id2) {
        same++;
    }
    if (id1 == id2) {
        same++;
    }
    //   ATLTRACE2(atlTraceGeneral, 0, "%i %i %i %i s%i\n",id0,id1,id2,id3,same);
    if (same) //3 vertices same coordinates, completly degenerated
        return TRUE;
    return FALSE;
}

BOOL IsDegeneratedFace(const int id0, const int id1, const int id2, const int id3) {
    int same = 0;
    if (id0 == id1 || id0 == id2 || id0 == id3) {
        same++;
    }
    if (id1 == id2 || id1 == id3) {
        same++;
    }
    if (id2 == id3) {
        same++;
    }
    //   ATLTRACE2(atlTraceGeneral, 0, "%i %i %i %i s%i\n",id0,id1,id2,id3,same);
    if (same) //2 vertices same coordinates, completly degenerated
        return TRUE;
    return FALSE;
}

BOOL IsDegeneratedFace(const int id0, const int id1, const int id2, const int idd0, const int idd1, const int idd2) {
    int same = 0;
    if (id0 == idd0 || id0 == idd1 || id0 == idd2) {
        same++;
    }
    if (id1 == idd0 || id1 == idd1 || id1 == idd2) {
        same++;
    }
    if (id2 == idd0 || id2 == idd1 || id2 == idd2) {
        same++;
    }
    if (same >= 3) //2 vertices same coordinates, 1 triangle on the same coords
        return TRUE;
    return FALSE;
}

void CHxtApp::SavePolys(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem, const String &groupname) const {
    char buf[80]{};
    char buf2[80]{};
    char mtlbuf[256]{};
    char lastmtl[256]{};

/*
    for (int ix = 0; ix < 256; ++ix) {
        lastmtl[ix] = 0;
        mtlbuf[ix] = 0;
    }
*/
    const int count = model->m_polyarray.GetSize();
    if (groupname.IsEmpty()) {
        fs << "g default" << nl;
    } else {
        fs << "g " << groupname.Get() << nl;
    }
    fs << "s 1" << nl;
    IEPoly **polyarray = model->m_polyarray.GetArray();
    Attr *attrarray = model->m_attrlist.GetArray();
    int countpoly = 0;
    int counttri = 0;
    int ival;
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        const int attrid = polyarray[i]->m_attrid;
        if (strcmp("UnKnown", attrarray[attrid].m_name) == 0) {
            sprintf_s(mtlbuf, 256, "usemtl %s%d", attrarray[attrid].m_name, attrid);
        } else {
            sprintf_s(mtlbuf, 256, "usemtl %s", attrarray[attrid].m_name);
        }
        if (strcmp(lastmtl, mtlbuf) != 0) {
            fs << mtlbuf << nl;
/*
            for (int iy = 0; iy < 256; ++iy) {
                lastmtl[iy] = mtlbuf[iy];                
            }
            */
            sprintf_s(lastmtl, 256, "%s", mtlbuf);
        }
        int c;
        if (!m_bexporttriangles) {
            if (m_discarddegenerated) {
                if (!IsDegeneratedFace(polyarray[i]->m_vertexid[0], polyarray[i]->m_vertexid[1], polyarray[i]->m_vertexid[2], polyarray[i]->m_vertexid[3])) {
                    if (!polyarray[i]->m_istriangle) {
                        //Quad
                        fs << "f";
                        for (c = 0; c < 4; ++c) {
                            ival = polyarray[i]->m_vertexid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            if (!m_buvcount)
                                fs << " " << buf << "/1/";
                            else {
                                sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                                fs << " " << buf << "/" << buf2 << "/";
                            }
                            ival = polyarray[i]->m_normalid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            fs << buf;
                        }
                        fs << nl;
                        countpoly++;
                    } else {
                        //Triangle only
                        fs << "f";
                        for (c = 0; c < 3; ++c) {
                            ival = polyarray[i]->m_vertexid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            if (!m_buvcount)
                                fs << " " << buf << "/1/";
                            else {
                                sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                                fs << " " << buf << "/" << buf2 << "/";
                            }
                            ival = polyarray[i]->m_normalid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            fs << buf;
                        }
                        fs << nl;
                        counttri++;
                    }
                } else {
                    //fallback to triangle only
                    if (!IsDegeneratedFace(polyarray[i]->m_vertexid[0], polyarray[i]->m_vertexid[1], polyarray[i]->m_vertexid[2])) {
                        //Tri
                        fs << "f";
                        for (c = 0; c < 3; ++c) {
                            ival = polyarray[i]->m_vertexid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            if (!m_buvcount)
                                fs << " " << buf << "/1/";
                            else {
                                sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                                fs << " " << buf << "/" << buf2 << "/";
                            }
                            ival = polyarray[i]->m_normalid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            fs << buf;
                        }
                        fs << nl;
                        counttri++;
                    }
                    if (!polyarray[i]->m_istriangle) {
                        if (!IsDegeneratedFace(polyarray[i]->m_vertexid[2], polyarray[i]->m_vertexid[3], polyarray[i]->m_vertexid[0])) {
                            //Tri
                            fs << "f";
                            for (c = 2; c < 4; ++c) {
                                ival = polyarray[i]->m_vertexid[c] + 1;
                                sprintf_s(buf, 80, "%d", ival);
                                if (!m_buvcount)
                                    fs << " " << buf << "/1/";
                                else {
                                    sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                                    fs << " " << buf << "/" << buf2 << "/";
                                }
                                ival = polyarray[i]->m_normalid[c] + 1;
                                sprintf_s(buf, 80, "%d", ival);
                                fs << buf;
                            }
                            ival = polyarray[i]->m_vertexid[0] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            if (!m_buvcount)
                                fs << " " << buf << "/1/";
                            else {
                                sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[0]);
                                fs << " " << buf << "/" << buf2 << "/";
                            }
                            ival = polyarray[i]->m_normalid[0] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            fs << buf;
                            fs << nl;
                            counttri++;
                        }
                    }
#ifdef _DEBUG
                    //degenerated face !
                    [[maybe_unused]] PatchID id = polyarray[i]->m_origpatch->GetPatchID();
#endif
                }
            } else {
                if (!polyarray[i]->m_istriangle) {
                    //Quad
                    fs << "f";
                    for (c = 0; c < 4; ++c) {
                        ival = polyarray[i]->m_vertexid[c] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        if (!m_buvcount)
                            fs << " " << buf << "/1/";
                        else {
                            sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                            fs << " " << buf << "/" << buf2 << "/";
                        }
                        ival = polyarray[i]->m_normalid[c] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        fs << buf;
                    }
                    fs << nl;
                    countpoly++;
                } else {
                    //Tri
                    fs << "f";
                    for (c = 0; c < 3; ++c) {
                        ival = polyarray[i]->m_vertexid[c] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        if (!m_buvcount)
                            fs << " " << buf << "/1/";
                        else {
                            sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                            fs << " " << buf << "/" << buf2 << "/";
                        }
                        ival = polyarray[i]->m_normalid[c] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        fs << buf;
                    }
                    fs << nl;
                    counttri++;
                }
            }
        } else {
            if (m_discarddegenerated) {
                if (!IsDegeneratedFace(polyarray[i]->m_vertexid[0], polyarray[i]->m_vertexid[1], polyarray[i]->m_vertexid[2])) {
                    //Tri
                    fs << "f";
                    for (c = 0; c < 3; ++c) {
                        ival = polyarray[i]->m_vertexid[c] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        if (!m_buvcount)
                            fs << " " << buf << "/1/";
                        else {
                            sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                            fs << " " << buf << "/" << buf2 << "/";
                        }
                        ival = polyarray[i]->m_normalid[c] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        fs << buf;
                    }
                    fs << nl;
                    counttri++;
                }
                if (!polyarray[i]->m_istriangle) {
                    if (!IsDegeneratedFace(polyarray[i]->m_vertexid[2], polyarray[i]->m_vertexid[3], polyarray[i]->m_vertexid[0])) {
                        //Tri
                        fs << "f";
                        for (c = 2; c < 4; ++c) {
                            ival = polyarray[i]->m_vertexid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            if (!m_buvcount)
                                fs << " " << buf << "/1/";
                            else {
                                sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                                fs << " " << buf << "/" << buf2 << "/";
                            }
                            ival = polyarray[i]->m_normalid[c] + 1;
                            sprintf_s(buf, 80, "%d", ival);
                            fs << buf;
                        }
                        ival = polyarray[i]->m_vertexid[0] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        if (!m_buvcount)
                            fs << " " << buf << "/1/";
                        else {
                            sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[0]);
                            fs << " " << buf << "/" << buf2 << "/";
                        }
                        ival = polyarray[i]->m_normalid[0] + 1;
                        sprintf_s(buf, 80, "%d", ival);
                        fs << buf;
                        fs << nl;
                        counttri++;
                    }
                }
            } else {
                //Tri
                fs << "f";
                for (c = 0; c < 3; ++c) {
                    ival = polyarray[i]->m_vertexid[c] + 1;
                    sprintf_s(buf, 80, "%d", ival);
                    if (!m_buvcount)
                        fs << " " << buf << "/1/";
                    else {
                        sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                        fs << " " << buf << "/" << buf2 << "/";
                    }
                    ival = polyarray[i]->m_normalid[c] + 1;
                    sprintf_s(buf, 80, "%d", ival);
                    fs << buf;
                }
                fs << nl;
                counttri++;
                //Tri
                fs << "f";
                for (c = 2; c < 4; ++c) {
                    ival = polyarray[i]->m_vertexid[c] + 1;
                    sprintf_s(buf, 80, "%d", ival);
                    if (!m_buvcount)
                        fs << " " << buf << "/1/";
                    else {
                        sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[c]);
                        fs << " " << buf << "/" << buf2 << "/";
                    }
                    ival = polyarray[i]->m_normalid[c] + 1;
                    sprintf_s(buf, 80, "%d", ival);
                    fs << buf;
                }
                ival = polyarray[i]->m_vertexid[0] + 1;
                sprintf_s(buf, 80, "%d", ival);
                if (!m_buvcount)
                    fs << " " << buf << "/1/";
                else {
                    sprintf_s(buf2, 80, "%d", polyarray[i]->m_uvid[0]);
                    fs << " " << buf << "/" << buf2 << "/";
                }
                ival = polyarray[i]->m_normalid[0] + 1;
                sprintf_s(buf, 80, "%d", ival);
                fs << buf;
                fs << nl;
                counttri++;
            }
        }
    }
    if (!m_bexporttriangles) {
        if (countpoly > 0 && counttri > 0) {
            sprintf_s(buf, 80, "# %d polygons\n# %d triangles", countpoly, counttri);
        } else {
            if (countpoly > 0) {
                sprintf_s(buf, 80, "# %d polygons", countpoly);
            } else {
                sprintf_s(buf, 80, "# %d triangles", counttri);
            }
        }
    } else {
        sprintf_s(buf, 80, "# %d triangles", counttri);
    }
    fs << buf << nl;
    /*
    #ifdef _DEBUG
        if (!m_bexporttriangles && counttri > 0) {
            String message = (String)counttri + " Triangles exported.\nPossible cause 5 Point Patches / 3 Point Patches / Hooks in the model";
            AfxMessageBox(message.Get(), MB_OK | MB_ICONINFORMATION);
        }
    #endif
        */
}

void CHxtApp::SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem) const {
    for (; bone; bone = bone->m_sibling) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        if (bone->m_child)
            fs << (BYTE)1 << nl;
        else
            fs << (BYTE)0 << nl;
        if (bone->m_sibling)
            fs << (BYTE)1 << nl;
        else
            fs << (BYTE)0 << nl;

        fs.Write(bone->m_name, strlen(bone->m_name));
        fs << '\0';

        fs << bone->m_pivotpos << nl;
        fs << bone->m_endpos << nl;
        fs << bone->m_rollpos << nl;

        const int count = bone->m_vertexidarray.GetSize();
        fs << count << nl;
        const int *array = bone->m_vertexidarray.GetArray();
        for (int i = 0; i < count; ++i)
            fs << array[i] << nl;

        if (bone->m_child)
            SaveBoneBranch(fs, bone->m_child, totalitems, curritem);
    }
}

void CHxtApp::SaveBones(FileStream &fs, const IEPolyModel *model, int &totalitems, int &curritem) const {
    SaveBoneBranch(fs, model->m_bonehead, totalitems, curritem);
}
