// HXT.h : main header file for the IE DLL
//
#pragma once

#include <afxwin.h>
#include "StrClass.h"
#include "SDK/Misc.h"
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See Hxt.cpp for the implementation of this class
//
#define MOTVERSION  (0x12345678+1)
//X-translate, Y-translate, Z-Translate, X-scale, Y-scale, Z-scale, X-orient, Y-orient, Z-orient, W-Orient
#define NUMCHANNELITEMS 10
#define CENTIMETERSPERINCH 2.54f

class FileStream;

class HActionCache;
class HActionCacheContainer;
class HAction;
class HBone;
class HModelCache;

class CHxtApp final : public CPluginApp {
public:
    CHxtApp();

    // Export
    BOOL OnExportActionCache(HActionCache *hac) const;
    BOOL OnExportActionCacheContainer(HActionCacheContainer *hocc) const;
    static void ReportExportError(const String &filename);

    //   BOOL ExportBVH(String &filename, float errortolerance, HActionCache *hac, HModelCache *hmc, BOOL ispadmotion, BOOL isassignedonly);
    static BOOL ExportBVH(String &filename, float errortolerance, HActionCache *hac, HModelCache *hmc, BOOL nomotiondata, BOOL ispadmotion, BOOL export_all, BOOL geometry_only, BOOL motion_only);
//    BOOL GetFileName(HActionCache *hac, String &filename);

    // Import
    //   HModelCache *m_hmc;
    //   float m_fFps;
    //   float m_fErrorTol;
    BOOL OnImportActionCache(HActionCache *hac) const;
    BOOL OnImportActionCacheContainer(HActionCacheContainer *hacc) const;
    static void ReportImportError(const String &filename);

    static BOOL ImportBVH(const String &pfilename, HModelCache *hmc, HActionCache *hac, BOOL bMultipleActions);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
public:
    BOOL InitInstance() override;
    BOOL ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CHxtApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
