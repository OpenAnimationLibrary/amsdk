// MMoP.h : Hauptheaderdatei für die MMoP DLL
//
#pragma once

#ifndef __AFXWIN_H__
	#error 'StdAfx.h' muss vor dieser Datei in PCH eingeschlossen werden.
#endif

#ifndef WINVER
#define WINVER 0x0400
#endif

#include "resource.h"		// Hauptsymbole
#include "HashFile.h"
#include "F_Protos.h"
#include "Matrix34.h"
#include "Rnd.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/HChor.h"
#include "SDK/HAction.h"
#include "SDK/HConstra.h"

// CMMoPApp
// Siehe MMoP.cpp für die Implementierung dieser Klasse
//

class HCP;
class HModel;
class HCamera;
class HModelCache;
class HGroupCP;
class HGroup;
class HLight;
class HPropertyInfo;
class HActionCache;

struct PParameter {
    HProject *hproject{};
    HModelCache *hmc{};
    HModel *hm_target{};
    HChor *chor{};
    float spline_length{};
    float distance{};
    Vector offset;
    BOOL store_rotate{};
    BOOL align{};
    HProperty *props[20]{};
    int azprop{};
    HActionCache *hac[20]{};
    int azaction{};
    BOOL action_random{};
    int random{}; //0 normal, 1 Random along path, 2 Random beside path
    int max_az{};
    BOOL use_offset{};
    BOOL allow_overlap{};
};

struct MMOP_POSITION {
    Vector pos;
    Vector dir;
    Quaternion quat;
};

//class CMMoPApp final : public CPluginApp
class CMMoPApp final : public CPluginApp {
public:
    PParameter *para = nullptr;
    CArray<int, int> rnd;
    int rndnumber = -1;
    CArray<int, int> rnd1;
    int rndnumber1 = -1;

    CMMoPApp();
    ~CMMoPApp() override;
    BOOL OnPath(HPathModel *hpm);
    BOOL OnGroup(HGroup *hg);
    void SetPoses(HModel *hm);
    void SetAction(HModel *hm);
    void GetSettings();
    void SaveSettings() const;
    bool Work(HSpline *hsp);

    // Überschreibungen
    BOOL InitInstance() override;
    int ExitInstance() override;
#ifdef _DEBUG
    FileStream fsd;
#endif

DECLARE_MESSAGE_MAP()
};
