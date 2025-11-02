#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "ExportModelDialog.h"
#include "ExportModelsDialog.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"
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
    const String modelmapfilename = "";
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
    if (model == nullptr) {
        ReportExportError(cdlg.m_filename);
        return TRUE;
    }

    const BOOL result = ExportLWO(model, cdlg.m_filename);
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
    String modelmapfilename = "";
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const Time totaltime = hac->GetTotalTime();
    const String basefilename = cdlg.m_filename;

    HModel *hm = hac->EditWithModelCache(hmc);

    for (Time time; time <= totaltime; time.StepFrame(fps)) {
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);
        if (m_iemp.m_isbuildmodelmap) {
            modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        }
        IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            hac->EndEditWithModelCache(hm);
            return TRUE;
        }

        const BOOL result = ExportLWO(model, filename);
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
    m_iemp.m_isbuildmodelmap = FALSE;
    String modelmapfilename = "";
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HModelCache *hmc = cdlg.m_selected.GetNext(pos);
        String filename = hmc->GetName();
        filename = filename.GetNameOnlyWithoutSuffix() + ".LWO";
        filename = CombineNameToPath(cdlg.m_dir, filename);
        if (m_iemp.m_isbuildmodelmap) {
            modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        }
        IEPolyModel *model = hmc->BuildExportModel(&m_iemp, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }
        const BOOL result = ExportLWO(model, filename);
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
    m_iemp.m_isbuildmodelmap = FALSE;
    String modelmapfilename = "";
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
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
        basefilename = basefilename.GetNameOnlyWithoutSuffix() + "-0000.LWO";
        basefilename = CombineNameToPath(cdlg.m_dir, basefilename);

        HModel *hm = hac->EditWithModelCache(hmc);

        for (Time time; time <= totaltime; time.StepFrame(fps)) {
            const int frame = time.GetFrameInt(fps);
            String filename = basefilename.NumberFrame(frame);
            if (m_iemp.m_isbuildmodelmap) {
                modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
            }
            IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
            if (model == nullptr) {
                ReportExportError(filename);
                hac->EndEditWithModelCache(hm);
                return TRUE;
            }

            const BOOL result = ExportLWO(model, filename);
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
    m_iemp.m_isbuildmodelmap = FALSE;
    String modelmapfilename = "";
    m_iemp.m_isbuildmaparray = TRUE;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_bexporttriangles = cdlg.m_btriangles;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const HTimeProperty *totaltime = hchor->GetTotalTime();
    const String basefilename = cdlg.m_filename;

    for (Time time; time <= totaltime->GetValue(); time.StepFrame(fps)) {
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);
        if (m_iemp.m_isbuildmodelmap) {
            modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
        }
        IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, modelmapfilename.Get());
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }

        const BOOL result = ExportLWO(model, filename);
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

BOOL CHxtApp::ExportLWO(IEPolyModel *model, const String &filename) {

    FILE *fp;
    if (fopen_s(&fp, filename.Get(), "wb") != 0)
        return FALSE;
    char baseName[256];
    getBasename(filename.Get(), baseName);

    writeTag(fp, "FORM");
    writeLong(fp, 0);
    writeTag(fp, "LWOB");

    int totalitems = 0;
    int curritem = 0;
    SaveVertexList(fp, model, totalitems, curritem);

    SaveAttributeNames(fp, model, totalitems, curritem, baseName);

    SavePolys(fp, model, totalitems, curritem);

    SaveAttributes(fp, model, totalitems, curritem, baseName);

    const long pos2 = ftell(fp);
    fseek(fp, 4L,SEEK_SET);
    writeLong(fp, (unsigned long)(pos2 - 8));

    fclose(fp);

    return TRUE;
}

void CHxtApp::SaveAttributeNames(FILE *fp, const IEPolyModel *model, int &totalitems, int &curritem, char *baseName) {
    writeTag(fp, "SRFS");
    const long pos1 = ftell(fp);
    writeLong(fp, 0);

    const int count = model->m_attrlist.GetSize();
    for (int i = 0; i < count; ++i) {
        char buf[256];
        sprintf_s(buf, 256, "%s-%d", baseName, i);
        writeName(fp, buf);
    }
    if (count == 0) {
        writeName(fp, baseName);
    }
    const long pos2 = ftell(fp);
    fseek(fp, pos1,SEEK_SET);
    writeLong(fp, (unsigned long)(pos2 - (pos1 + 4)));
    fseek(fp, 0,SEEK_END);
}

void CHxtApp::SaveAttributes(FILE *fp, IEPolyModel *model, int &totalitems, int &curritem, char *baseName) {
    const int count = model->m_attrlist.GetSize();
    const Attr *attrarray = model->m_attrlist.GetArray();
    for (int i = 0; i < count; ++i) {

        writeTag(fp, "SURF");
        const long pos1 = ftell(fp);
        writeLong(fp, 0L);

        char name[256];
        sprintf_s(name, 256, "%s-%d", baseName, i);
        writeName(fp, name);

        writeTag(fp, "COLR");
        writeShort(fp, 4);
        writeChar(fp, FLOATTOBYTE(attrarray[i].m_diffusecolor.m_red));
        writeChar(fp, FLOATTOBYTE(attrarray[i].m_diffusecolor.m_green));
        writeChar(fp, FLOATTOBYTE(attrarray[i].m_diffusecolor.m_blue));
        writeChar(fp, (unsigned char)0);

        writeTag(fp, "VDIF");
        writeShort(fp, 4);
        writeFloat(fp, 1.F);

        writeTag(fp, "FLAG");
        writeShort(fp, 2);
        writeShort(fp, 1U << 2U);

        const long pos2 = ftell(fp);
        fseek(fp, pos1,SEEK_SET);
        writeLong(fp, (unsigned long)(pos2 - (pos1 + 4)));
        fseek(fp, 0,SEEK_END);
    }

    if (count == 0) {
        writeTag(fp, "SURF");
        const long pos1 = ftell(fp);
        writeLong(fp, 0L);

        writeName(fp, baseName);

        writeTag(fp, "COLR");
        writeShort(fp, 4);
        writeChar(fp, (unsigned char)128);
        writeChar(fp, (unsigned char)128);
        writeChar(fp, (unsigned char)128);
        writeChar(fp, (unsigned char)0);

        writeTag(fp, "VDIF");
        writeShort(fp, 4);
        writeFloat(fp, 1.F);

        writeTag(fp, "FLAG");
        writeShort(fp, 2);
        writeShort(fp, 1U << 2U);

        const long pos2 = ftell(fp);
        fseek(fp, pos1,SEEK_SET);
        writeLong(fp, (unsigned long)(pos2 - (pos1 + 4)));
        fseek(fp, 0,SEEK_END);
    }
}

void CHxtApp::SaveVertexList(FILE *fp, IEPolyModel *model, int &totalitems, int &curritem) {
    writeTag(fp, "PNTS");
    const int count = model->m_vertexlist.GetSize();
    writeLong(fp, (unsigned long)(3ULL * count * sizeof(float)));

    const Vector *vectorarray = model->m_vertexlist.GetArray();
    for (int i = 0; i < count; ++i) {
        writeFloat(fp, vectorarray[i].x);
        writeFloat(fp, vectorarray[i].y);
        writeFloat(fp, vectorarray[i].z);
    }
}

void CHxtApp::SavePolys(FILE *fp, IEPolyModel *model, int &totalitems, int &curritem) {
    writeTag(fp, "POLS");
    const long pos1 = ftell(fp);
    writeLong(fp, 0L);

    const int att_count = model->m_attrlist.GetSize();
    const int count = model->m_polyarray.GetSize();
    IEPoly **polyarray = model->m_polyarray.GetArray();
    for (int i = 0; i < count; ++i) {
        writeShort(fp, 4);
        for (const int c: polyarray[i]->m_vertexid)
            writeShort(fp, (unsigned short)c);
        writeShort(fp, (unsigned short)(att_count ? polyarray[i]->m_attrid + 1 : 1)); //1 origin
    }

    const long pos2 = ftell(fp);
    fseek(fp, pos1,SEEK_SET);
    writeLong(fp, (unsigned long)(pos2 - (pos1 + 4)));
    fseek(fp, 0,SEEK_END);
}

unsigned short CHxtApp::swapShort(const unsigned short w) {
    return (unsigned)(w >> 8U) | (unsigned)(w << 8U);
}

unsigned long CHxtApp::swapLong(const unsigned long w) {
    unsigned long tmp = w;
    auto *p = (unsigned char *)&tmp;
    unsigned char c = p[0];
    p[0] = p[3];
    p[3] = c;
    c = p[1];
    p[1] = p[2];
    p[2] = c;
    return tmp;
}

void CHxtApp::writeTag(FILE *fp, const char *tag) {
    fwrite(tag, 1, 4, fp);
}

void CHxtApp::writeChar(FILE *fp, const unsigned char dat) {
    fwrite(&dat, sizeof(unsigned char), 1, fp);
}

void CHxtApp::writeShort(FILE *fp, unsigned short dat) {
    dat = swapShort(dat);
    fwrite(&dat, sizeof(unsigned short), 1, fp);
}

void CHxtApp::writeLong(FILE *fp, unsigned long dat) {
    dat = swapLong(dat);
    fwrite(&dat, sizeof(unsigned long), 1, fp);
}

void CHxtApp::writeFloat(FILE *fp, float dat) {
    const unsigned long ld = ((unsigned long *)&dat)[0];
    writeLong(fp, ld);
}

void CHxtApp::writeName(FILE *fp, const char *name) {
    const size_t len = strlen(name) + 1;
    fwrite(name, len, 1, fp);

    if ((unsigned)len & 0x01U) {
        fwrite("\0", 1, 1, fp);
    }
}

const char *CHxtApp::getFilename(const char *name) {
    if (!name)
        return nullptr;
    const char *p = strrchr(name, '/');
    if (p)
        return p + 1;
    p = strrchr(name, '\\');
    if (p)
        return p + 1;
    return name;
}

char *CHxtApp::getBasename(const char *name, char *dest) {
    const char *filep = getFilename(name);
    if (!filep)
        return nullptr;
    // ReSharper disable once CppDeprecatedEntity
    strcpy_s(dest,256, filep);
    char *p = strrchr(dest, '.');
    if (p)
        *p = (char)NULL;
    return dest;
}
