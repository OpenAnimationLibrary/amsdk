// MotCam.h : Hauptheaderdatei für die MotCam DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error 'StdAfx.h' muss vor dieser Datei in PCH eingeschlossen werden.
#endif

#include "resource.h"		// Hauptsymbole
#include "F_Protos.h"
#include "HashFile.h"

#include "Matrix34.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HDecal.h"
#include "SDK/HCamera.h"
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

// CMotCamApp
// Siehe MotCam.cpp für die Implementierung dieser Klasse
//
#define MOTVERSION  (0x12345678+1)

struct W_PARA {
    int width{}, height{};
    int start{}, end{};
    int fps{};
    CString filename{};
    CString path{};
    CString cameraname{};
    BOOL override_camsettings{};
};

class CMotCamApp final : public CPluginApp {
public:
    CMotCamApp();
    ~CMotCamApp() override;
    BOOL OnCamera(HCamera *hcam);
    BOOL GetPropRecurseCamera(HProperty *akt_prop) const;
    void GetPropCamera(HHashObject *obj) const;

    W_PARA *para{};
    int cam_width{}, cam_height{};

    // Überschreibungen
public:
    BOOL InitInstance() override;
    int ExitInstance() override;

DECLARE_MESSAGE_MAP()
};
