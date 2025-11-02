// Align.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Align.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlignApp

BEGIN_MESSAGE_MAP(CAlignApp, CWinApp)
        //{{AFX_MSG_MAP(CAlignApp)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlignApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CAlignApp-Objekt

CAlignApp theApp;

BOOL CAlignApp::InitInstance() {
    return CPluginApp::InitInstance();
}

int CAlignApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CAlignApp::OnModel(HModel *hm) {
    IEPoly **polyarray;
    IEPolyModelParms m_iemp;
    IEPolyModel *model;
    HChor *chor;
    HModelCache *hmc;
#ifdef _DEBUG
    FileStream fs;
#endif
    int i, j, count;
    CArray<Vector, Vector &> pointlist;
    CArray<ALIGN_POINT, ALIGN_POINT &> worklist;
    ALIGN_POINT worktemp;
    Vector min_y, move_y, needed_y, min, max;
    Vector direction, hitp, hitn;
    bool found;

    min_y.Set(hash_constants::max_float);
    min.Set(hash_constants::max_float);
    max.Set(-hash_constants::max_float);
    move_y.Set(0.F);
    direction.Set(0, -1, 0);
    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_ignorevisibility = TRUE;
    chor = hm->GetChor();
    chor->OpenView(0);
    Time akt_time = chor->GetTime();
    hmc = (HModelCache *)hm->GetCache();
    Matrix34 pqs = hm->GetModelToWorldMatrix();

#ifdef _DEBUG
    fs.Open("e://area.txt", FileMode::HS_ASCII);
#endif
    m_iemp.m_subtype = ST_VARIABLE;
    model = hmc->BuildExportModel(&m_iemp, nullptr);
    count = model->m_polyarray.GetSize();
    polyarray = model->m_polyarray.GetArray();
    for (i = 0; i < count; ++i) {
        pointlist.Add(model->m_vertexlist[polyarray[i]->m_vertexid[0]]);
        pointlist.Add(model->m_vertexlist[polyarray[i]->m_vertexid[1]]);
        pointlist.Add(model->m_vertexlist[polyarray[i]->m_vertexid[2]]);
        pointlist.Add(model->m_vertexlist[polyarray[i]->m_vertexid[3]]);
    }
    DeleteIEModel(model);
    count = pointlist.GetSize();
    for (i = 0; i < count; ++i) {
        if (pointlist[i].y < min_y.y)
            min_y = pointlist[i];
    }
    for (i = 0; i < count; ++i) {
        if (pointlist[i].y < min_y.y + 0.1F) {
            found = false;
            for (j = 0; j < worklist.GetSize(); ++j) {
                if (pointlist[i] == worklist[j].pos) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                worktemp.pos = pointlist[i];
                worktemp.hitp.Set(0.F);
                worklist.Add(worktemp);
            }
        }
    }

#ifdef _DEBUG
    fs << "AZ Point org " << count << nl;
    fs << "Az worklist  " << worklist.GetSize() << nl;
    fs << "bottom       " << min_y << nl << nl;
#endif
    count = worklist.GetSize();
    for (i = 0; i < count; ++i) {
        worklist[i].pos *= pqs;
    }
    if (Vector a1 = min_y * pqs; !chor->Intersect(a1, direction, hitp, hitn, 2000.F, 0.0016F)) {
        a1 = min_y * pqs;
        move_y.y += 1000.F;
        //need set the model to the new position , otherwise self intersect
        hm->SetLocalMatrix(akt_time, pqs * TranslateV(move_y));
        GetHProject()->UpdateAllViews();
    }
    for (i = 0; i < count; ++i) {
        Vector a2 = worklist[i].pos + move_y;
        chor->Intersect(a2, direction, hitp, hitn, 2000.F, 0.0016F);
        hitp.x = worklist[i].pos.x;
        hitp.z = worklist[i].pos.z;
        worklist[i].hitp = hitp;
        worklist[i].neededmove = worklist[i].hitp - worklist[i].pos;
        worklist[i].quat = Rotate2VQ(worklist[i].hitp, worklist[i].pos);
    }
    if (move_y.y != 0)
        hm->SetLocalMatrix(akt_time, pqs);

    Quaternion quat;
    quat.SetIdentity();
    needed_y.Set(hash_constants::max_float);
    for (i = 0; i < count; ++i) {
        if (worklist[i].neededmove.y < needed_y.y)
            needed_y = worklist[i].neededmove;
#ifdef _DEBUG
        fs << "pos         " << worklist[i].pos << nl;
        fs << "hitp        " << worklist[i].hitp << nl;
        fs << "needed move " << worklist[i].neededmove << nl;
        RotateEuler re(worklist[i].quat);
        fs << re.x << " " << re.y << " " << re.z << nl << nl;
        fs << nl;
#endif
    }

    /*   Vector axis;
       float radangle;
       t1.Set(241.268f,74.4443f,422.195f);
       t2.Set(241.268f,95.6035f,542.195f);

       float dotp = Dot(t1,t2)/(t1.Norm()*t2.Norm());
       fs << acos(dotp)*hash_constants::radians << nl << nl;

       axis.Set(0.F);
       TwoVectorsToAxisAngle (t1, t2, axis, radangle);
       fs << axis << nl;
       fs << axis.Normalized() << nl;
       fs << radangle*hash_constants::radians << nl << nl;

       quat = Rotate2VQ(t1,t2);
       fs << quat.GetAxis() << nl;
       fs << quat.GetAngle()*hash_constants::radians << nl << nl;
    */
#ifdef _DEBUG
    Vector t1;
    for (i = 0; i < count; ++i) {
        t1 += worklist[i].hitp;
    }

    fs << "t1 " << t1 / (float)count << nl;
    float y, z;
    float x = y = z = 0;
    for (i = 0; i < count - 1; ++i) {
        for (j = i + 1; j < count; ++j) {
            quat = Rotate2VQ(worklist[i].hitp, worklist[j].hitp);
            RotateEuler re(quat);
            fs << "euler " << re.x << " " << re.y << " " << re.z << nl;
            x += re.x;
            y += re.y;
            z += re.z;
        }
    }
    fs << "x " << x << nl;
    fs << "y " << y << nl;
    fs << "z " << z << nl;
    fs << "needed y      " << needed_y << nl;
#endif
    pqs *= TranslateV(needed_y);

#ifdef _DEBUG
    fs << pqs << nl;
#endif
    for (i = 0; i < count; ++i) {
        pqs *= Matrix34(worklist[i].quat);
    }
#ifdef _DEBUG
    fs << pqs << nl;
    fs.Close();
#endif
    //	hm->SetLocalMatrix(akt_time,pqs);
    GetHProject()->UpdateAllViews();
    worklist.RemoveAll();
    pointlist.RemoveAll();
    return true;
}
