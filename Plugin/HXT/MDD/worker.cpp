#include "StdAfx.h"
#include "MDD.h"
#include <algorithm>

#define ByteSwap5(x) ByteSwap((unsigned char *) &(x),sizeof(x))

void ByteSwap(unsigned char *b, const int n) {
    int i = 0;
    int j = n - 1;
    while (i < j) {
        std::swap(b[i], b[j]);
        i++;
        j--;
    }
}

BOOL CMDDApp::CPIsAddedToArray(const HCP *cp) {
    for (int i = 0; i < allcps.GetSize(); ++i) {
        if (allcps[i].cp == cp)
            return TRUE;
    }
    return FALSE;
}

bool PointInside(const Vector testpoint, const float radius, const Vector center) {
    const Vector kDiff = testpoint - center;
    const float difference = kDiff.Norm();
    return difference <= radius;
}

int CMDDApp::FindMatchingCP(const Vector pos) {
    for (int i = 0; i < allcps.GetSize(); ++i) {
        if (!allcps[i].inuse) {
            if (pos == allcps[i].position) {
                allcps[i].inuse = true;
                return i;
            }
        }
    }
    float difference = hash_constants::max_float;
    int nearestcp = -1;
    for (int i = 0; i < allcps.GetSize(); ++i) {
        if (!allcps[i].inuse) {
            Vector kDiff = pos - allcps[i].position;
            if (const float diff = kDiff.Norm(); diff <= difference) {
                nearestcp = i;
                difference = diff;
            }
        }
    }

    if (nearestcp != -1) {
        allcps[nearestcp].inuse = true;
        return nearestcp;
    }

    return -1;
}

BOOL CMDDApp::OnImport(HModel *hm) {
//    HChor *hchor = hm->GetChor();
    auto *hmc = (HModelCache *)hm->GetCache();

    HCP *cp = nullptr;
    HPatch *hp = nullptr;
    HPatch5 *hp5 = nullptr;
    Vector position;
    W_CPPOS temprecord;
    temprecord.inuse = false;
    temprecord.cpinstance = nullptr;

    for (UINT i = 0; i < hmc->GetPatchCount(); ++i) {
        hp = hmc->GetPatch(i);
        cp = hp->GetCP1();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        cp = hp->GetCP2();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        cp = hp->GetCP3();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        if (hp->GetNumPoints() == 4) {
            cp = hp->GetCP4();
            if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
                temprecord.cp = cp;
                temprecord.position = *cp->GetModelPosition();
                allcps.Add(temprecord);
            }
        }
    }

    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        cp = hp5->GetCP1();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        cp = hp5->GetCP2();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        cp = hp5->GetCP3();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        cp = hp5->GetCP4();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
        cp = hp5->GetCP5();
        if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
            temprecord.cp = cp;
            temprecord.position = *cp->GetModelPosition();
            allcps.Add(temprecord);
        }
    }

    for (HSpline *spline = hmc->GetHeadSpline(); spline; spline = spline->GetNextSpline()) {
        for (cp = spline->GetHeadCP(); cp; cp = cp->GetNext()) {
            if (cp == cp->GetHead() && !CPIsAddedToArray(cp)) {
                temprecord.cp = cp;
                temprecord.position = *cp->GetModelPosition();
                allcps.Add(temprecord);
            }
            if (cp->IsLoop())
                break;
        }
    }

    for (int i = 0; i < allcps.GetSize(); ++i) {
        allcps[i].inuse = false;
        allcps[i].cpinstance = allcps[i].cp->GetCPInstance();
        if (!allcps[i].cpinstance) {
            allcps[i].cpinstance = allcps[i].cp->CreateCPInstance();
        }
    }

    FileStream fs;

    int totalFrames, totalPoints;
    float p1, p2, p3;
    CArray<float, float &> timecode;

    fs.Open(parameter->filename, FileMode::HS_BINARY | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS);
    fs.Seek(0, FileStream::HS_BEGINNING);
    fs >> totalFrames;
    ByteSwap5(totalFrames);
    fs >> totalPoints;
    ByteSwap5(totalPoints);
    for (int j = 0; j < totalFrames; ++j) {
        fs >> p1;
        ByteSwap5(p1);
        Round(p1, 0.001F);
        timecode.Add(p1);
    }
    CArray<int, int &> cpordered;
    int _cpordered;
    for (int i = 0; i < totalPoints; ++i) {
        fs >> p1;
        ByteSwap5(p1);
        fs >> p2;
        ByteSwap5(p2);
        fs >> p3;
        ByteSwap5(p3);
        position.Set(p1, p2, -p3); //Z-Axis always reverted
        _cpordered = FindMatchingCP(position);
        cpordered.Add(_cpordered);
    }

    Time time;
    float projectfps = GetHProject()->GetFPS();
    for (int j = 0; j < totalFrames; ++j) {
        if (!fs.Eof()) {
            float timing = timecode.GetAt(j);
            timing *= parameter->fps;
            time.SetFrame(timing, projectfps);
            if (parameter->startatcurrenttime) {
                time += parameter->start;
            }
            for (int i = 0; i < totalPoints; ++i) {
                fs >> p1;
                ByteSwap5(p1);
                fs >> p2;
                ByteSwap5(p2);
                fs >> p3;
                ByteSwap5(p3);
                position.Set(p1, p2, -p3);
                _cpordered = cpordered.GetAt(i);
                if (_cpordered >= 0) {
                    Vector diffPos = position - allcps[_cpordered].position;
                    if (parameter->scale != 1.F) {
                        diffPos *= parameter->scale;
                    }
                    allcps[_cpordered].cpinstance->GetPosition()->StoreValue(time, diffPos, false);
                }
            }
        }
    }
    fs.Close();

    if (cpordered.GetSize() != allcps.GetSize()) {
        AfxMessageBox("Possible Errors.\n Some cp's not found.", MB_ICONWARNING);
    }
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    cpordered.RemoveAll();
    allcps.RemoveAll();
    timecode.RemoveAll();
    return TRUE;
}

BOOL CMDDApp::OnExport(HModel *hm) const {
    HChor *hchor = hm->GetChor();
//    HModelCache *hmc = (HModelCache *)hm->GetCache();
    float projectfps = GetHProject()->GetFPS();

    IEPolyModelParms m_iemp;

    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = (SubType)parameter->subtype;
    m_iemp.m_ignorevisibility = TRUE;

    Time buildtime;
    FileStream fs;
    Vector p0;
    int swapint;
    float swapfloat;

    fs.Open(parameter->filename, FileMode::HS_BINARY | FileMode::HS_STORE | FileMode::HS_DONTPROGRESS);
    fs.Seek(0, FileStream::HS_BEGINNING);

    IEPolyModel *model = hm->BuildExportModel(&m_iemp, buildtime, nullptr);
    int azframes = (parameter->end - parameter->start).GetFrameInt(projectfps);
    swapint = azframes + 1;
    ByteSwap5(swapint);
    fs << swapint;
    int azpoints = model->m_vertexlist.GetSize();
    swapint = azpoints;
    ByteSwap5(swapint);
    fs << swapint;
    int startframe = parameter->start.GetFrameInt(projectfps);
    for (int i = 0; i <= azframes; ++i) {
        swapfloat = (i + startframe) / projectfps;
        ByteSwap5(swapfloat);
        fs << swapfloat;
    }
    Vector *vectorarray = model->m_vertexlist.GetArray();
    for (int j = 0; j < azpoints; ++j) {
        p0 = vectorarray[j];
        if (parameter->scale != 1.F) {
            p0 *= parameter->scale;
        }
        p0.z *= -1;
        swapfloat = p0.x;
        ByteSwap5(swapfloat);
        fs << swapfloat;
        swapfloat = p0.y;
        ByteSwap5(swapfloat);
        fs << swapfloat;
        swapfloat = p0.z;
        ByteSwap5(swapfloat);
        fs << swapfloat;
    }
    DeleteIEModel(model);
    for (int i = startframe; i <= azframes + startframe; ++i) {
        buildtime.SetFrame(i, projectfps);
        model = hm->BuildExportModel(&m_iemp, buildtime, nullptr);
        azpoints = model->m_vertexlist.GetSize();
        vectorarray = model->m_vertexlist.GetArray();
        for (int j = 0; j < azpoints; ++j) {
            p0 = vectorarray[j];
            if (parameter->scale != 1.F) {
                p0 *= parameter->scale;
            }
            p0.z *= -1;
            swapfloat = p0.x;
            ByteSwap5(swapfloat);
            fs << swapfloat;
            swapfloat = p0.y;
            ByteSwap5(swapfloat);
            fs << swapfloat;
            swapfloat = p0.z;
            ByteSwap5(swapfloat);
            fs << swapfloat;
        }
        DeleteIEModel(model);
    }
    fs.Close();
    hchor->SetTime(parameter->start);
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}

/*
BOOL CMDDApp::OnExportASCII(HModel *hm) {
   HChor *hchor = hm->GetChor();
   HModelCache *hmc = (HModelCache *)hm->GetCache();
   float projectfps = GetHProject()->GetFPS();

    IEPolyModelParms m_iemp;
    IEPolyModel *model;
   Vector *vectorarray;

    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = ST_1;
    m_iemp.m_ignorevisibility = TRUE;

   Time buildtime = 0;
   FileStream fs;
   Vector p0;
   int azframes,azpoints;

   fs.Open(parameter->filename,FileMode::HS_ASCII | FileMode::HS_STORE );

   model = hm->BuildExportModel(&m_iemp,buildtime,nullptr);
   azframes = (parameter->end - parameter->start).GetFrameInt(projectfps);
   fs << "Frames " << azframes << nl;
   azpoints = model->m_vertexlist.GetSize();
   fs << "AzPoints " << azpoints << nl;
   int startframe = parameter->start.GetFrameInt(projectfps);
   for (int i = 0; i <= azframes; ++i) {
      fs << (i+startframe)/projectfps << tab; //should be parameter->fps
   }
   fs << nl;

      fs << nl << "frame " << 0 << nl;
   vectorarray = model->m_vertexlist.GetArray();
    for (int j=0; j < azpoints; ++j) {
      p0 = vectorarray[j];
      p0.z *= -1;
      fs << p0 << nl;
   }
   DeleteIEModel(model);

   for (int i = startframe; i < (azframes+startframe); ++i ) {
      fs << "frame " << i+1 << nl;
      buildtime.SetFrame(i,projectfps);
      model = hm->BuildExportModel(&m_iemp,buildtime,nullptr);
      azpoints = model->m_vertexlist.GetSize();
      vectorarray = model->m_vertexlist.GetArray();
       for (int j=0; j < azpoints; ++j) {
         p0 = vectorarray[j];
         p0.z *= -1;
         fs << p0 << nl;
      }
      DeleteIEModel(model);
   }


   fs.Close();
   return true;
}

BOOL CMDDApp::Test() {

   int totalFrames,totalPoints;
   float p1,p2,p3;
   FileStream fs,fs_out;
   String filename;
   CArray<float, float &> timecode;
//   filename = "E:\\test_mdd\\Model.mdd";
//   filename = "E:\\test_mdd\\test.mdd";
//   filename = "E:\\test_mdd\\unscaled.mdd";
   filename = "E:\\test.mdd";
   fs_out.Open("E:\\testmdd.txt",FileMode::HS_ASCII | FileMode::HS_STORE);

   fs.Open(filename,FileMode::HS_BINARY | FileMode::HS_LOAD );
   fs >> totalFrames;
   ByteSwap5(totalFrames);
   fs >> totalPoints;
   ByteSwap5(totalPoints);
//   fs >> startframe;
//   ByteSwap5(startframe);

//   firstpos
   fs_out << "TotalPoints " << totalPoints << nl;
   fs_out << "TotalFrames " << totalFrames << nl;
   for (int j = 0;j<totalFrames;++j) {
      fs >> p1;
      ByteSwap5(p1);
      timecode.Add(p1);
      fs_out << p1 << tab;
   }
   fs_out << nl;
   //frame 0 modelcache position
   //mapping the points
   for (int i = 0;i<totalPoints;++i) {
            fs >> p1;
            ByteSwap5(p1);
            fs >> p2;
            ByteSwap5(p2);
            fs >> p3;
            ByteSwap5(p3);
            fs_out << p1 << tab  << p2 << tab << p3 << nl;
   }


   for (int j = 0;j<totalFrames;++j) {
      if (fs.Eof()) {
         fs_out << "Frame EOF " << j << nl;
      } else {
         float timing = timecode.GetAt(j);
         fs_out << "Frame " << j << nl;
         for (int i = 0;i<totalPoints;++i) {
            fs >> p1;
            ByteSwap5(p1);
            fs >> p2;
            ByteSwap5(p2);
            fs >> p3;
            ByteSwap5(p3);
            fs_out << p1 << tab  << p2 << tab << p3 << nl;
         }
         fs_out << nl;
      }
   }
   fs.Close();
   fs_out.Close();

   return TRUE;
}
*/
