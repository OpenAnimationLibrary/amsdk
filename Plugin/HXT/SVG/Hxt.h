// \Plugin\HXT\SVG\Hxt.h

#pragma once

#ifndef __AFXWIN_H__
#error include 'StdAfx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SDK/HPropert.h"
#include "SDK/Misc.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "F_Protos.h"
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CHxtApp
// See IE.cpp for the implementation of this class
//

class HModelCache;
class HObjectCacheContainer;
class FileStream;
class String;
class HProgressBar;
class HActionCache;
class HActionCacheContainer;
class HChor;

class SVGParameters {
public:
    enum { SUB_NONE, SUB_ALL, SUB_AUTO } SubdivKind;

    int unit;
    int resolution;
    BOOL center;
    BOOL importaspathonly;
    BOOL m_fronts;
    BOOL m_sides;
    BOOL m_backs;
    BOOL m_bevfronts;
    BOOL m_bevbacks;
    BOOL m_bevsides;
    BOOL m_bevround;
    BOOL m_bevinward;
    int m_subdivkind;
    float m_bevamt;
    float m_depth;
};

struct PFAD {
    Vector pos;
    Vector inbias;
    Vector outbias;
    HCP *cp{nullptr};
};

struct TPFAD {
    std::vector<PFAD> path{};
};

struct SHAPE {
    std::vector<TPFAD> pfad{};
};

class CHxtApp final : public CPluginApp
{
public:
    SVGParameters m_parameters{};
    HProgressBar *m_hprogressbar{nullptr};
    CHxtApp() = default;

    BOOL OnImportModelCache(HModelCache *hmc);
    BOOL OnImportObjectCacheContainer(HObjectCacheContainer *hocc);
    void ImportSVG_Path(const String &pfilename, HModelCache *hmc, BOOL newmodel = FALSE);
    void BuildClosedModel(const std::vector<SHAPE> &shapelist, HModelCache *hmc, HGroup **group);
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHxtApp)
    BOOL InitInstance() override;
    int ExitInstance() override; // AM SDK
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CHxtApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
