// VuePython.h : Hauptheaderdatei für die VuePython DLL
//

#pragma once

#ifndef __AFXWIN_H__
   #error 'StdAfx.h' muss vor dieser Datei in PCH eingeschlossen werden.
#endif

#include "resource.h"		// Hauptsymbole
#include "F_Protos.h"
#include "HashFile.h"
#include "Vector.h"
#include "Matrix34.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HDecal.h"
#include "SDK/HCamera.h"
#include "SDK/HLight.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HChor.h"
#include "StrClass.h"

class FileStream;
class HActionCache;
class HActionCacheContainer;
class HBone;
class HModelCache;

// CVuePythonApp
// Siehe VuePython.cpp für die Implementierung dieser Klasse
//

struct W_PARA {
    int mode{}; //0 cameras and lights, 1 only selected camera, 2 only selected light
    int width{};
    int height{};
    int light_type{};
    int start{}, end{};
    int fps{};
    CString filename{};
    CString path{};
    CString cameraname{};
    BOOL override_camsettings{};
};

class CVuePythonApp final : public CPluginApp {
public:
    CVuePythonApp();
    ~CVuePythonApp() override;
    BOOL OnLight(HLight *hlight);
    BOOL OnCamera(HCamera *hcam);
    BOOL OnChor(HChor *hchor);
    BOOL GetPropRecurseCamera(HProperty *akt_prop) const;
    void GetPropCamera(HHashObject *obj) const;
    void GetPropLight(HHashObject *obj) const;
    void WriteOutCamera(HCamera *hcam, FileStream &fs) const;
    void WriteOutLight(HLight *hlight, FileStream &fs) const;

    W_PARA *para{};

    // Überschreibungen
public:
    BOOL InitInstance() override;
    int ExitInstance() override;

DECLARE_MESSAGE_MAP()
};
