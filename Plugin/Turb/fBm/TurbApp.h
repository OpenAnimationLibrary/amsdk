// KB  9/26/01  \Ken90\Plugin\Turb\fBm\TurbApp.h
//
#pragma once

#include <afxwin.h>
#include "resource.h"		// main symbols
#include "SDK/HPropert.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CTurbApp
// See Turb.cpp for the implementation of this class
//

class CTurbApp final : public CPluginApp {
public:
    HIntPropertyInfo *m_octavesinfo{};
    float m_fractalincrement{};
    static float m_exponent[8];

    CTurbApp() noexcept = default;
    BOOL InitInstance() override;
    int ExitInstance() override;
    static void InitfBm(float h);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTurbApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CTurbApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
