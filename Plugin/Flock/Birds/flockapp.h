// KB  9/25/01  \Ken90\Plugin\Flock\Birds\flockapp.h
//
#pragma once

#include "SDK/HPropert.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CFlockApp
// See Flock.cpp for the implementation of this class
//

class CFlockApp final : public CPluginApp {
public:
    HFloatPropertyInfo *m_mindistanceinfo{};
    HFloatPropertyInfo *m_maxspeedinfo{};
    HFloatPropertyInfo *m_accelerationinfo{};
    HIntPropertyInfo *m_jitterinfo{};

    CFlockApp();
    BOOL InitInstance() override;
    int ExitInstance() override;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CFlockApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CFlockApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
