// BakeNull.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "BakeNull.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBakeNullApp

BEGIN_MESSAGE_MAP(CBakeNullApp, CWinApp)
        //{{AFX_MSG_MAP(CBakeNullApp)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBakeNullApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CBakeNullApp-Objekt

CBakeNullApp theApp;

BOOL CBakeNullApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CBakeNullApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CBakeNullApp::CloneNull(HNullObject *hno) {

    if (HChor *hc = hno->GetChor(); hc) {
        Vector pos;
        HProject *hp = GetHProject();
        const float fps = hp->GetFPS();
        const Time totaltime = hc->GetTotalTime()->GetValue();
        const Time akt_time = hc->GetTime();

        HObject *hclone = hno->MakeCopy(TRUE);
        HRotateProperty *hrp_o = hno->GetTransform()->GetRotate();
        HTranslateProperty *htp_o = hno->GetTransform()->GetTranslate();
        const HScaleProperty *hsp_o = hno->GetTransform()->GetScale();
        HRotateProperty *hrp_c = hclone->GetTransform()->GetRotate();
        HTranslateProperty *htp_c = hclone->GetTransform()->GetTranslate();
        HScaleProperty *hsp_c = hclone->GetTransform()->GetScale();

        for (Time time; time <= totaltime; time.StepFrame(fps)) {
            Quaternion rot = hrp_o->GetValue(time);
            pos = htp_o->GetValue(time);
            Vector scale = hsp_o->GetValue();
            hsp_c->StoreValue(time, scale,FALSE);
            htp_c->StoreValue(time, pos,FALSE);
            hrp_c->StoreValue(time, rot,TRUE,TRUE);
        }

        hsp_c->Reduce(1.F);
        htp_c->Reduce(1.F);
        hrp_c->Reduce(1.F);

        hc->SetTime(akt_time);
        pos = htp_o->GetValue(akt_time);
        hclone->HilightInProjectBar();
    }
    GetHProject()->UpdateAllViews();
    return TRUE;
}
