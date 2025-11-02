//

#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "ExportModelDialog.h"
#include "ExportModelsDialog.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"

//#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"
#include "SDK/HProgres.h"

BOOL CHxtApp::OnExportModelCache(HModelCache *hmc) {

    CExportModelDialog cdlg(hmc->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;
    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = cdlg.m_generatemodelmaps;
    m_iemp.m_minmodelmapsize = (MapLimit)cdlg.m_minsize;
    m_iemp.m_maxmodelmapsize = (MapLimit)cdlg.m_maxsize;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_isbuildweights = cdlg.m_isbuildweights;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    //m_iemp.m_maxweightcount = 4;

    const String modelmapfilename = cdlg.m_filename.GetWithoutSuffix() + ".bmp";
    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
    if (model == nullptr) {
        ReportExportError(cdlg.m_filename);
        return TRUE;
    }

    const BOOL result = ExportPLY(model, cdlg.m_filename, m_iemp.m_isbuildweights);
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
    m_iemp.m_isbuildweights = cdlg.m_isbuildweights;
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

        const BOOL result = ExportPLY(model, filename, m_iemp.m_isbuildweights);
        DeleteIEModel(model);

        if (!result) {
            ReportExportError(filename);
            hac->EndEditWithModelCache(hm);
            return TRUE;
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
    m_iemp.m_isbuildweights = cdlg.m_isbuildweights;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HModelCache *hmc = cdlg.m_selected.GetNext(pos);
        String filename = hmc->GetName();
        filename = filename.GetNameOnlyWithoutSuffix() + ".PLH";
        filename = CombineNameToPath(cdlg.m_dir, filename);
        String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }
        const BOOL result = ExportPLY(model, filename, m_iemp.m_isbuildweights);
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
    m_iemp.m_isbuildweights = cdlg.m_isbuildweights;
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

        Time totaltime = hac->GetTotalTime();
        String basefilename = hac->GetName();
        basefilename = basefilename.GetNameOnlyWithoutSuffix() + "-0000.PLH";
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

            const BOOL result = ExportPLY(model, filename, m_iemp.m_isbuildweights);
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
    m_iemp.m_isbuildweights = cdlg.m_isbuildweights;
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

        const BOOL result = ExportPLY(model, filename, m_iemp.m_isbuildweights);
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

BOOL CHxtApp::ExportPLY(IEPolyModel *model, const String &filename, const BOOL saveweights) {
    FileStream fs;
    int curritem = 0;

    if (!fs.Open(filename, FileMode::HS_BINARY | FileMode::HS_STORE | FileMode::HS_DONTPROGRESS))
        return FALSE;
    fs.SetWriteStringCounts(FALSE);

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

    // Get total items for percent bar
    int totalitems = model->m_attrlist.GetSize() + model->m_maplist.GetSize() + model->m_vertexlist.GetSize() + model->m_normallist.GetSize() + model->m_polyarray.GetSize() + CountBones(model);

    fs << "PLY" << nl;

    if (saveweights) // VERSION
        fs << 3L << nl;
    else
        fs << 2L << nl;

    SaveAttributes(fs, model, totalitems, curritem);
    SaveTextureMaps(fs, model, totalitems, curritem);
    SaveVertexList(fs, model, totalitems, curritem);
    SaveNormalList(fs, model, totalitems, curritem);
    SavePolys(fs, model, totalitems, curritem);
    SaveBones(fs, model, totalitems, curritem, saveweights);

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }
    SetBasePath(oldpath);
    return TRUE;
}

void CHxtApp::SaveAttributes(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const {
    const int count = model->m_attrlist.GetSize();
    fs << count << nl;
    const Attr *attrarray = model->m_attrlist.GetArray();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        fs << FLOATTOBYTE(attrarray[i].m_diffusecolor.m_red) << nl;
        fs << FLOATTOBYTE(attrarray[i].m_diffusecolor.m_green) << nl;
        fs << FLOATTOBYTE(attrarray[i].m_diffusecolor.m_blue) << nl;

        fs << attrarray[i].m_diffusefalloff << nl;

        fs << FLOATTOBYTE(attrarray[i].m_specularcolor.m_red) << nl;
        fs << FLOATTOBYTE(attrarray[i].m_specularcolor.m_green) << nl;
        fs << FLOATTOBYTE(attrarray[i].m_specularcolor.m_blue) << nl;

        fs << attrarray[i].m_specularsize << nl;
        fs << attrarray[i].m_specularintensity << nl;
        fs << attrarray[i].m_ambiance << nl;
        fs << attrarray[i].m_roughness << nl;
        fs << attrarray[i].m_roughnessscale << nl;
        fs << attrarray[i].m_reflectivity << nl;
        fs << attrarray[i].m_transparency << nl;
        fs << attrarray[i].m_refraction << nl;
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
    fs << count << nl;
    const Vector *vectorarray = model->m_vertexlist.GetArray();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        fs << vectorarray[i] << nl;
    }
}

void CHxtApp::SaveNormalList(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const {
    const int count = model->m_normallist.GetSize();
    fs << count << nl;
    const Vector *vectorarray = model->m_normallist.GetArray();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        fs << vectorarray[i] << nl;
    }
}

void CHxtApp::SavePolys(FileStream &fs, IEPolyModel *model, const int &totalitems, int &curritem) const {
    const int count = model->m_polyarray.GetSize();
    fs << count << nl;
    IEPoly **polyarray = model->m_polyarray.GetArray();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        fs << polyarray[i]->m_attrid << nl;
        int c;
        for (c = 0; c < 4; ++c)
            fs << polyarray[i]->m_vertexid[c] << nl;
        for (c = 0; c < 4; ++c)
            fs << polyarray[i]->m_normalid[c] << nl;
        const int mapnodecount = polyarray[i]->m_mapnodearray.GetSize();
        IEMapNode **mapnodearray = polyarray[i]->m_mapnodearray.GetArray();
        fs << mapnodecount << nl;
        for (int mi = 0; mi < mapnodecount; ++mi) {
            fs << mapnodearray[mi]->m_mapid << nl;
            fs << mapnodearray[mi]->m_percent << nl;
            fs << mapnodearray[mi]->m_repeat << nl;
            fs << mapnodearray[mi]->m_kind << nl;
            fs << mapnodearray[mi]->m_isseamless << nl;

            for (c = 0; c < 4; ++c)
                fs << mapnodearray[mi]->m_uv[c] << nl;
        }
    }
}

void CHxtApp::SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem, const BOOL saveweights) const {
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
        if (saveweights) {
            const float *weights = bone->m_weightarray.GetArray();
            for (int i = 0; i < count; ++i)
                fs << weights[i] << nl;
        }
        if (bone->m_child)
            SaveBoneBranch(fs, bone->m_child, totalitems, curritem, saveweights);
    }
}

void CHxtApp::SaveBones(FileStream &fs, const IEPolyModel *model, int &totalitems, int &curritem, const BOOL saveweights) const {
    SaveBoneBranch(fs, model->m_bonehead, totalitems, curritem, saveweights);
}
