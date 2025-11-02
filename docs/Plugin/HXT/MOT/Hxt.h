// HXT.h : main header file for the HXT DLL
//
#pragma once

#include <afxwin.h>
#ifndef __STRCLASS_H
#include "StrClass.h"
#endif
#include "resource.h"		// main symbols
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See HXT.cpp for the implementation of this class
//
#define MOTVERSION  (0x12345678+1)
//X-translate, Y-translate, Z-Translate, X-scale, Y-scale, Z-scale, X-orient, Y-orient, Z-orient, W-Orient
#define NUMCHANNELITEMS 10

class FileStream;
class HActionCache;
class HActionCacheContainer;
class HBone;
class HModelCache;

class CHxtApp final : public CPluginApp {
public:
    CHxtApp();

    // Export
    BOOL OnExportActionCache(HActionCache *hac) const;
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc);
    static void ReportExportError(const String &filename);

    static BOOL ExportMOT(String &filename, HActionCache *hac, HModelCache *hmc);
    BOOL GetFileName(HActionCache *hac, String &filename) const;
    //   WORD CountSkeletalChannelHandles(HActionCache *hac);
    //   void SaveSkeletalChannelHandle(FileStream &fs, SkeletalChannelHandle *chan, BoneHandle *bone, Time totaltime, float fps);

    // Import
    HModelCache *m_hmc;
    float m_fFps{};
    float m_fErrorTol{};
    BOOL OnImportActionCache(HActionCache *hac);
    BOOL OnImportActionCacheContainer(HActionCacheContainer *hacc);
    static void ReportImportError(const String &filename);

    BOOL ImportMOT(const String &pfilename, HModelCache *hmc, HActionCache *hdstac, BOOL bMultipleActions) const;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
public:
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CHxtApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
