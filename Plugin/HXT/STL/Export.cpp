#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "ExportModelDialog.h"
//#include "F_Protos.h"
//#include "Files.h"

#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"
//#include "SDK/HProgres.h"

BOOL CHxtApp::OnExportModelCache(HModelCache *hmc) {

    CExportModelDialog cdlg(hmc->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;
    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = FALSE;
    m_iemp.m_isbuildmaparray = FALSE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;
    const String modelname = hmc->GetName();
    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, nullptr);
    if (model == nullptr) {
        ReportExportError(cdlg.m_filename);
        return TRUE;
    }

    const BOOL result = ExportStl(model, cdlg.m_filename, modelname, cdlg.m_binary);
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
    m_iemp.m_isbuildmodelmap = FALSE;
    m_iemp.m_isbuildmaparray = FALSE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const Time totaltime = hac->GetTotalTime();
    const String basefilename = cdlg.m_filename;
    const String modelname = hmc->GetName();

    HModel *hm = hac->EditWithModelCache(hmc);

    for (Time time; time <= totaltime; time.StepFrame(fps)) {
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);
        IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, nullptr);
        if (model == nullptr) {
            ReportExportError(filename);
            hac->EndEditWithModelCache(hm);
            return TRUE;
        }

        const BOOL result = ExportStl(model, filename, modelname, cdlg.m_binary);
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

BOOL CHxtApp::OnExportChor(HChor *hchor) {
    CExportModelDialog cdlg(hchor->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;

    CWaitCursor wait;
    m_iemp.m_isbuildmodelmap = FALSE;
    m_iemp.m_isbuildmaparray = FALSE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
//    HTimeProperty *totaltime = hchor->GetTotalTime();
    const Time time = hchor->GetTime();
    const String basefilename = cdlg.m_filename;
    const String modelname = hchor->GetName();

    const int frame = time.GetFrameInt(fps);
    const String filename = basefilename.NumberFrame(frame);
    IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, nullptr);
    if (model == nullptr) {
        ReportExportError(filename);
        return TRUE;
    }

    const BOOL result = ExportStl(model, filename, modelname, cdlg.m_binary);
    DeleteIEModel(model);

    if (!result)
        ReportExportError(filename);

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

BOOL CHxtApp::ExportStl(IEPolyModel *model, const String &filename, const String &modelname, BOOL binary_format) {
    if (model->m_normallist.GetSize() == 0)
        return FALSE;
    FILE *fp;
    const errno_t err = fopen_s(&fp, filename.Get_const_char(), "wb");
    if (err != 0)
        return FALSE;
    const int count = model->m_polyarray.GetSize();
    Vector *vectorarray = model->m_vertexlist.GetArray();
    Vector *normalarray = model->m_normallist.GetArray();
    IEPoly **polyarray = model->m_polyarray.GetArray();

    Vector temp;
    short attributes = 0;
    if (binary_format) {
        char header[80] = "Animation:Master";
        memset(header, 0, 80);
        if (!modelname.IsEmpty()) {
            strncpy_s(header, _countof(header), modelname.Get(), _countof(header));
        } else {
            strcpy_s(header, _countof(header), "Animation:Master");
        }
        fwrite(header, 80, 1, fp);
        // write number of facets
        int count_faces = count * 2;
        fwrite(&count_faces, 1, sizeof(int), fp);
        for (int i = 0; i < count; i++) {
            /*
                     if (polyarray[i]->m_istriangle) {
                        temp = normalarray[polyarray[i]->m_normalid[0]];
                        temp += normalarray[polyarray[i]->m_normalid[1]];
                        temp += normalarray[polyarray[i]->m_normalid[2]];
                        temp /= 3.F;
                        temp.Normalize();
                        fwrite(&temp,3,sizeof(float),fp);
                        temp = vectorarray[polyarray[i]->m_vertexid[0]];
                        fwrite(&temp,3,sizeof(float),fp);
                        temp = vectorarray[polyarray[i]->m_vertexid[1]];
                        fwrite(&temp,3,sizeof(float),fp);
                        temp = vectorarray[polyarray[i]->m_vertexid[2]];
                        fwrite(&temp,3,sizeof(float),fp);
                        fwrite(&attributes,1,sizeof(short),fp);
                     } else {*/
            temp = normalarray[polyarray[i]->m_normalid[0]];
            temp += normalarray[polyarray[i]->m_normalid[1]];
            temp += normalarray[polyarray[i]->m_normalid[2]];
            temp *= 1.F / 3.F;
            temp.Normalize();
            fwrite(&temp, 3, sizeof(float), fp);
            temp = vectorarray[polyarray[i]->m_vertexid[0]];
            fwrite(&temp, 3, sizeof(float), fp);
            temp = vectorarray[polyarray[i]->m_vertexid[1]];
            fwrite(&temp, 3, sizeof(float), fp);
            temp = vectorarray[polyarray[i]->m_vertexid[2]];
            fwrite(&temp, 3, sizeof(float), fp);
            fwrite(&attributes, 1, sizeof(short), fp);

            temp = normalarray[polyarray[i]->m_normalid[0]];
            temp += normalarray[polyarray[i]->m_normalid[2]];
            temp += normalarray[polyarray[i]->m_normalid[3]];
            temp *= 1.F / 3.F;
            temp.Normalize();
            fwrite(&temp, 3, sizeof(float), fp);
            temp = vectorarray[polyarray[i]->m_vertexid[0]];
            fwrite(&temp, 3, sizeof(float), fp);
            temp = vectorarray[polyarray[i]->m_vertexid[2]];
            fwrite(&temp, 3, sizeof(float), fp);
            temp = vectorarray[polyarray[i]->m_vertexid[3]];
            fwrite(&temp, 3, sizeof(float), fp);
            fwrite(&attributes, 1, sizeof(short), fp);
            //         }
        }
    } else {
        if (!modelname.IsEmpty()) {
            fprintf(fp, "solid %s\n", modelname.Get());
        } else {
            fprintf(fp, "solid Animation:Master\n");
        }
        for (int i = 0; i < count; i++) {
            /*         if (polyarray[i]->m_istriangle) {
                        temp = normalarray[polyarray[i]->m_normalid[0]];
                        temp += normalarray[polyarray[i]->m_normalid[1]];
                        temp += normalarray[polyarray[i]->m_normalid[2]];
                        temp *= 1.F/3.F;
                        temp.Normalize();
                        fprintf(fp,"  facet normal %13e %13e %13e\n",temp.x,temp.y,temp.z);
                        fprintf(fp,"    outer loop\n");
                        temp = vectorarray[polyarray[i]->m_vertexid[0]];
                        fprintf(fp,"      vertex  %13e %13e %13e\n",temp.x,temp.y,temp.z);			
                        temp = vectorarray[polyarray[i]->m_vertexid[1]];
                        fprintf(fp,"      vertex  %13e %13e %13e\n",temp.x,temp.y,temp.z);			
                        temp = vectorarray[polyarray[i]->m_vertexid[2]];
                        fprintf(fp,"      vertex  %13e %13e %13e\n",temp.x,temp.y,temp.z);			
                        fprintf(fp,"    endloop\n");
                        fprintf(fp,"  endfacet\n");
                     } else {*/
            temp = normalarray[polyarray[i]->m_normalid[0]];
            temp += normalarray[polyarray[i]->m_normalid[1]];
            temp += normalarray[polyarray[i]->m_normalid[2]];
            temp *= 1.F / 3.F;
            temp.Normalize();
            fprintf(fp, "  facet normal %13e %13e %13e\n", temp.x, temp.y, temp.z);
            fprintf(fp, "    outer loop\n");
            temp = vectorarray[polyarray[i]->m_vertexid[0]];
            fprintf(fp, "      vertex  %13e %13e %13e\n", temp.x, temp.y, temp.z);
            temp = vectorarray[polyarray[i]->m_vertexid[1]];
            fprintf(fp, "      vertex  %13e %13e %13e\n", temp.x, temp.y, temp.z);
            temp = vectorarray[polyarray[i]->m_vertexid[2]];
            fprintf(fp, "      vertex  %13e %13e %13e\n", temp.x, temp.y, temp.z);
            fprintf(fp, "    endloop\n");
            fprintf(fp, "  endfacet\n");

            temp = normalarray[polyarray[i]->m_normalid[0]];
            temp += normalarray[polyarray[i]->m_normalid[2]];
            temp += normalarray[polyarray[i]->m_normalid[3]];
            temp *= 1.F / 3.F;
            temp.Normalize();
            fprintf(fp, "  facet normal %13e %13e %13e\n", temp.x, temp.y, temp.z);
            fprintf(fp, "    outer loop\n");
            temp = vectorarray[polyarray[i]->m_vertexid[0]];
            fprintf(fp, "      vertex  %13e %13e %13e\n", temp.x, temp.y, temp.z);
            temp = vectorarray[polyarray[i]->m_vertexid[2]];
            fprintf(fp, "      vertex  %13e %13e %13e\n", temp.x, temp.y, temp.z);
            temp = vectorarray[polyarray[i]->m_vertexid[3]];
            fprintf(fp, "      vertex  %13e %13e %13e\n", temp.x, temp.y, temp.z);
            fprintf(fp, "    endloop\n");
            fprintf(fp, "  endfacet\n");
            //         }
        }
        if (!modelname.IsEmpty()) {
            fprintf(fp, "endsolid %s\n", modelname.Get());
        } else {
            fprintf(fp, "endsolid Animation:Master\n");
        }
    }
    fclose(fp);
    return TRUE;
}
