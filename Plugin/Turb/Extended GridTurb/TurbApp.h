// Yves  2004/11/18  \Plugin\Turb\Extended GridTurb\TurbApp.h
//
#pragma once

#include <afxwin.h>
#include "resource.h"		// main symbols
#include "SDK/HPropert.h"
#include "SDK/Misc.h"

/////////////////////////////////////////////////////////////////////////////
// CTurbApp
// See TurbApp.cpp for the implementation of this class
//

class CTurbApp final : public CPluginApp {
public:

    TypeInfoArray m_TypeInfoArray;
    HTypePropertyInfo *m_GridTypeInfo{};

    HBoolPropertyInfo *m_UseXInfo{};
    HFloatPropertyInfo *m_XSizeInfo{};
    HFloatPropertyInfo *m_XRatioInfo{};
    HPercentPropertyInfo *m_XBlurInfo{};

    HBoolPropertyInfo *m_UseYInfo{};
    HFloatPropertyInfo *m_YSizeInfo{};
    HFloatPropertyInfo *m_YRatioInfo{};
    HPercentPropertyInfo *m_YBlurInfo{};

    HBoolPropertyInfo *m_UseZInfo{};
    HFloatPropertyInfo *m_ZSizeInfo{};
    HFloatPropertyInfo *m_ZRatioInfo{};
    HPercentPropertyInfo *m_ZBlurInfo{};

    HBoolPropertyInfo *m_UseAzimuthInfo{};
    HFloatPropertyInfo *m_AzimuthSizeInfo{};
    HFloatPropertyInfo *m_AzimuthRatioInfo{};
    HPercentPropertyInfo *m_AzimuthBlurInfo{};
    HFloatPropertyInfo *m_AzimuthStripeInfo{};

    HBoolPropertyInfo *m_UseElevationInfo{};
    HFloatPropertyInfo *m_ElevationSizeInfo{};
    HFloatPropertyInfo *m_ElevationRatioInfo{};
    HPercentPropertyInfo *m_ElevationBlurInfo{};
    HFloatPropertyInfo *m_ElevationStripeInfo{};

    HBoolPropertyInfo *m_UseRadialInfo{};
    HFloatPropertyInfo *m_RadialSizeInfo{};
    HFloatPropertyInfo *m_RadialRatioInfo{};
    HPercentPropertyInfo *m_RadialBlurInfo{};

    CTurbApp() noexcept = default;
    BOOL InitInstance() override;
    int ExitInstance() override;

    CString LoadString(int ID) const;

    static HBoolPropertyInfo *InitBool(int IDS, const char *matchname, BOOL def = TRUE);
    static HFloatPropertyInfo *InitFloat(int IDS, const char *matchname, float def, float min, float max, float fact = 1.F, UINT flags = HFloatPropertyInfo::FF_UNIT);
    static HPercentPropertyInfo *InitPercent(int IDS, const char *matchname, float def, float min = 0.F, float max = 1.F);

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
