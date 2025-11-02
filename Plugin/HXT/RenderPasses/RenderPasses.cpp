// passes.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "RenderPasses.h"
#include "Dialog1.h"
#include "Dialog2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CpassesApp

BEGIN_MESSAGE_MAP(CPassesApp, CWinApp)
        //{{AFX_MSG_MAP(CPassesApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassesApp Konstruktion

CPassesApp::CPassesApp() = default;

CPassesApp::~CPassesApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CPassesApp-Objekt

CPassesApp theApp;

BOOL CPassesApp::OnChor(HChor *htreeobject) {

    para = new PARAMETER;
    para->azmodel = 0;
    para->pass = 0;

    Dialog1 dlg1(para);
    if (dlg1.DoModal() != IDOK) {
        delete [] para;
        return TRUE;
    }

    Dialog2 dlg2(para);

    switch (para->pass) {
        case 0:
            DiffuseShadingPass(htreeobject);
            ChangeChorName(htreeobject, "_DiffuseShading");
            break;
        case 1:
            SpecularityPass(htreeobject);
            ChangeChorName(htreeobject, "_Specularity");
            break;
        case 2:
            ShadowPass(htreeobject);
            ChangeChorName(htreeobject, "_Shadow");
            break;
        case 3:
            DofPass(htreeobject);
            ChangeChorName(htreeobject, "_Dof");
            break;
        case 4:
            ReadChor(htreeobject);
            if (dlg2.DoModal() != IDOK) {
                FreeStruct();
                delete [] para;
                return TRUE;
            }
            Usershading(htreeobject);
            ChangeChorName(htreeobject, "_UserShading");
            break;
        default:
            break;
    }

    FreeStruct();
    delete [] para;
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;
}

BOOL CPassesApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CPassesApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
