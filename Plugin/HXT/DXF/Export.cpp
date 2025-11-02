// KB  9/25/02  \Ken95\Plugin\HXT\DXF\Export.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "HashFile.h"
#include "ExportModelDialog.h"
#include "ExportModelsDialog.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"

#include "SDK/HModel.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"
#include "SDK/HChor.h"
#include "SDK/HProgres.h"

#define EOFILE       0xFF

BOOL CHxtApp::OnExportModelCache(HModelCache *hmc) {

    CExportModelDialog cdlg(hmc->GetName());
    if (cdlg.DoModal() != IDOK)
        return TRUE;
    CWaitCursor wait;
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    IEPolyModel *model = hmc->BuildExportModel(&m_iemp, nullptr);
    if (model == nullptr) {
        ReportExportError(cdlg.m_filename);
        return TRUE;
    }

    const BOOL result = ExportDXF(model, cdlg.m_filename);
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
        IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, nullptr);
        if (model == nullptr) {
            ReportExportError(filename);
            hac->EndEditWithModelCache(hm);
            return TRUE;
        }

        const BOOL result = ExportDXF(model, filename);
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
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    for (POSITION pos = cdlg.m_selected.GetHeadPosition(); pos;) {
        HModelCache *hmc = cdlg.m_selected.GetNext(pos);
        String filename = hmc->GetName();
        filename = filename.GetNameOnlyWithoutSuffix() + ".DXF";
        filename = CombineNameToPath(cdlg.m_dir, filename);
        IEPolyModel *model = hmc->BuildExportModel(&m_iemp, nullptr);
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }
        const BOOL result = ExportDXF(model, filename);
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

        Time totaltime = hac->GetTotalTime();
        String basefilename = hac->GetName();
        basefilename = basefilename.GetNameOnlyWithoutSuffix() + "-0000.DXF";
        basefilename = CombineNameToPath(cdlg.m_dir, basefilename);

        HModel *hm = hac->EditWithModelCache(hmc);

        for (Time time; time <= totaltime; time.StepFrame(fps)) {
            const int frame = time.GetFrameInt(fps);
            String filename = basefilename.NumberFrame(frame);
//            String modelmapfilename = filename.GetWithoutSuffix() + ".bmp";
            IEPolyModel *model = hm->BuildExportModel(&m_iemp, time, nullptr);
            if (model == nullptr) {
                ReportExportError(filename);
                hac->EndEditWithModelCache(hm);
                return TRUE;
            }

            const BOOL result = ExportDXF(model, filename);
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
    m_iemp.m_subtype = (SubType)cdlg.m_subtype;
    m_iemp.m_applydisplacement = cdlg.m_applybump;

    HProject *hp = GetHProject();
    const float fps = hp->GetFPS();
    const HTimeProperty *totaltime = hchor->GetTotalTime();
    const String basefilename = cdlg.m_filename;

    for (Time time; time <= totaltime->GetValue(); time.StepFrame(fps)) {
        const int frame = time.GetFrameInt(fps);
        String filename = basefilename.NumberFrame(frame);
        IEPolyModel *model = hchor->BuildExportModel(&m_iemp, time, nullptr);
        if (model == nullptr) {
            ReportExportError(filename);
            return TRUE;
        }

        const BOOL result = ExportDXF(model, filename);
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

namespace {
    void CountBoneBranch(const IEBone *bone, int *count) {
        for (; bone; bone = bone->m_sibling) {
            (*count)++;
            if (bone->m_child)
                CountBoneBranch(bone->m_child, count);
        }
    }
}

int CHxtApp::CountBones(const IEPolyModel *model) {
    int count = 0;
    CountBoneBranch(model->m_bonehead, &count);
    return count;
}

void CHxtApp::PadLine(FILE *file) {
    fprintf(file, "\x0D\x0A"); //So Mac's can load the file
}

BOOL CHxtApp::ExportDXF(IEPolyModel *model, const String &pfilename) {
    FILE *file;
    char filename[256];
    int curritem = 0;

    m_hprogressbar = GetProgressBar();
    if (m_hprogressbar) {
        m_hprogressbar->Initialize();
        CString text;
        text.LoadString(IDS_EXPORTTITLE);
        m_hprogressbar->SetMessage1(text);
        m_hprogressbar->SetMessage2(pfilename.GetNameOnly().Get());
    }

    // Get total items for percent bar
    const int totalitems = model->m_polyarray.GetSize();

    sprintf_s(filename, 256, "%s", pfilename.Get());
    if (fopen_s(&file, filename, "wb") != 0)
        return FALSE;

    fprintf(file, "0");
    PadLine(file);
    fprintf(file, "SECTION");
    PadLine(file);
    fprintf(file, "2");
    PadLine(file);
    fprintf(file, "ENTITIES");
    PadLine(file);

    const int count = model->m_polyarray.GetSize();
    for (int i = 0; i < count; ++i) {
        if (m_hprogressbar)
            m_hprogressbar->SetProgress((int)((float)curritem++ / totalitems * 100));
        const IEPoly *poly = model->m_polyarray.GetAt(i);
        const Vector &p1 = model->m_vertexlist.ElementAt(poly->m_vertexid[0]);
        const Vector &p2 = model->m_vertexlist.ElementAt(poly->m_vertexid[1]);
        const Vector &p3 = model->m_vertexlist.ElementAt(poly->m_vertexid[2]);
        const Vector &p4 = model->m_vertexlist.ElementAt(poly->m_vertexid[3]);
        fprintf(file, "0");
        PadLine(file);
        fprintf(file, "3DFACE");
        PadLine(file);
        fprintf(file, "8");
        PadLine(file);
        fprintf(file, "%d", 2);
        PadLine(file);

        fprintf(file, "10");
        PadLine(file);
        fprintf(file, "%g", p2.x);
        PadLine(file);
        fprintf(file, "20");
        PadLine(file);
        fprintf(file, "%g", p2.y);
        PadLine(file);
        fprintf(file, "30");
        PadLine(file);
        fprintf(file, "%g", p2.z);
        PadLine(file);

        fprintf(file, "11");
        PadLine(file);
        fprintf(file, "%g", p3.x);
        PadLine(file);
        fprintf(file, "21");
        PadLine(file);
        fprintf(file, "%g", p3.y);
        PadLine(file);
        fprintf(file, "31");
        PadLine(file);
        fprintf(file, "%g", p3.z);
        PadLine(file);

        fprintf(file, "12");
        PadLine(file);
        fprintf(file, "%g", p4.x);
        PadLine(file);
        fprintf(file, "22");
        PadLine(file);
        fprintf(file, "%g", p4.y);
        PadLine(file);
        fprintf(file, "32");
        PadLine(file);
        fprintf(file, "%g", p4.z);
        PadLine(file);

        fprintf(file, "13");
        PadLine(file);
        fprintf(file, "%g", p1.x);
        PadLine(file);
        fprintf(file, "23");
        PadLine(file);
        fprintf(file, "%g", p1.y);
        PadLine(file);
        fprintf(file, "33");
        PadLine(file);
        fprintf(file, "%g", p1.z);
        PadLine(file);
    }

    fprintf(file, "0");
    PadLine(file);
    fprintf(file, "ENDSEC");
    PadLine(file);
    fprintf(file, "0");
    PadLine(file);
    fprintf(file, "EOF");
    PadLine(file);

    fprintf(file, "%c", EOFILE);

    fclose(file);

    if (m_hprogressbar) {
        m_hprogressbar->Uninitialize();
        m_hprogressbar = nullptr;
    }

    return TRUE;
}

/*
void CHxtApp::SaveAttributes(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem)
{
   int count = model->m_attrlist.GetSize();
   fs << count << nl;
   Attr *attrarray = model->m_attrlist.GetArray();
   for (int i=0; i < count; ++i) {
      if (m_hprogressbar)
         m_hprogressbar->SetProgress((int)((float)curritem++/totalitems*100));
      fs << (BYTE)(attrarray[i].m_diffusecolor.red*255.0f) << nl;
      fs << (BYTE)(attrarray[i].m_diffusecolor.green*255.0f) << nl;
      fs << (BYTE)(attrarray[i].m_diffusecolor.blue*255.0f) << nl;
      
      fs << attrarray[i].m_diffusefalloff << nl;
      
      fs << (BYTE)(attrarray[i].m_specularcolor.red*255.0f) << nl;
      fs << (BYTE)(attrarray[i].m_specularcolor.green*255.0f) << nl;
      fs << (BYTE)(attrarray[i].m_specularcolor.blue*255.0f) << nl;
      
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

void CHxtApp::SaveTextureMaps(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem)
{
   int count = model->m_maplist.GetSize();
   fs << count << nl;
   IEMap *maparray = model->m_maplist.GetArray();
   for (int i=0; i < count; ++i) {
      if (m_hprogressbar)
         m_hprogressbar->SetProgress((int)((float)curritem++/totalitems*100));
      String mapname = maparray[i].m_filename;
      mapname = mapname.GetRelativePath();
      fs.Write(mapname.Get(), mapname.length());
      fs << '\0';
      fs << maparray[i].m_width << sp << maparray[i].m_height << nl;
   }
}

void CHxtApp::SaveVertexList(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem)
{
   char buf[40];
   int count = model->m_vertexlist.GetSize();
   //fs << count << nl;
   fs << "# Verticies" << NL;
   Vector *vectorarray = model->m_vertexlist.GetArray();
   for (int i=0; i < count; ++i) {
      if (m_hprogressbar)
         m_hprogressbar->SetProgress((int)((float)curritem++/totalitems*100));
      fs << "v "; 
	  _gcvt(vectorarray[i].x,8,buf); 
	  fs << buf << " ";
	  _gcvt(vectorarray[i].y,8,buf); 
	  fs << buf << " ";
	  _gcvt(vectorarray[i].z,8,buf); 
	  fs << buf << NL;
   }
}

void CHxtApp::SaveNormalList(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem)
{
   char buf[40];
   int count = model->m_normallist.GetSize();
   //fs << count << nl;
   fs << "# Normals" << NL;
   Vector *vectorarray = model->m_normallist.GetArray();
   for (int i=0; i < count; ++i) {
      if (m_hprogressbar)
         m_hprogressbar->SetProgress((int)((float)curritem++/totalitems*100));
      fs << "vn "; 
	  _gcvt(vectorarray[i].x,8,buf); 
	  fs << buf << " ";
	  _gcvt(vectorarray[i].y,8,buf); 
	  fs << buf << " ";
	  _gcvt(vectorarray[i].z,8,buf); 
	  fs << buf << NL;
   }
}

void CHxtApp::SavePolys(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem)
{
   char buf[40];
   int ival;
   int count = model->m_polyarray.GetSize();
   //fs << count << nl;
   fs << "# Faces" << NL;
   IEPoly **polyarray = model->m_polyarray.GetArray();
   for (int i=0; i < count; ++i) {
      if (m_hprogressbar)
         m_hprogressbar->SetProgress((int)((float)curritem++/totalitems*100));
      //fs << polyarray[i]->m_attrid << nl;
      int c;
	  fs << "f";
      for (c=0; c < 4; ++c) {
		ival = polyarray[i]->m_vertexid[c] + 1;
		_itoa(ival,buf,10); 
		fs << " " << buf << "//";
		ival = polyarray[i]->m_normalid[c] + 1;
		_itoa(ival,buf,10); 
		fs << buf;
	  }
	  fs << NL;
      int mapnodecount = polyarray[i]->m_mapnodearray.GetSize();
      IEMapNode **mapnodearray = polyarray[i]->m_mapnodearray.GetArray();
      fs << mapnodecount << nl;
      for (int mi=0; mi < mapnodecount; ++mi) {
         fs << mapnodearray[mi]->m_mapid << nl;
         fs << mapnodearray[mi]->m_percent << nl;
         fs << mapnodearray[mi]->m_repeat << nl;
         fs << (BYTE)mapnodearray[mi]->m_kind << nl;
         fs << (BYTE)mapnodearray[mi]->m_isseamless << nl;
         
         for (c=0; c < 4; ++c)
            fs << mapnodearray[mi]->m_uv[c] << nl;
      }
   }
}

void CHxtApp::SaveBoneBranch(FileStream &fs, IEBone *bone, int &totalitems, int &curritem)
{
   for (; bone; bone = bone->m_sibling) {
      if (m_hprogressbar)
         m_hprogressbar->SetProgress((int)((float)curritem++/totalitems*100));
      if (bone->m_child)
         fs << (BYTE)1 << nl;
      else
         fs << (BYTE)0 << nl;
      if (bone->m_sibling)
         fs << (BYTE)1 << nl;
      else
         fs << (BYTE)0 << nl;

      fs.Write( bone->m_name, strlen(bone->m_name));
      fs << '\0';
      
      fs << bone->m_pivotpos << nl;
      fs << bone->m_endpos << nl;
      fs << bone->m_rollpos << nl;
      
      int count = bone->m_vertexidarray.GetSize();
      fs << count << nl;
      int *array = bone->m_vertexidarray.GetArray();
      for (int i=0; i < count; ++i)
         fs << array[i] << nl;

      if (bone->m_child)      
         SaveBoneBranch( fs, bone->m_child, totalitems, curritem );
   }
}

void CHxtApp::SaveBones(FileStream &fs, IEPolyModel *model, int &totalitems, int &curritem)
{
   SaveBoneBranch(fs, model->m_bonehead, totalitems, curritem);
}
*/
