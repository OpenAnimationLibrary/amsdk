// Yves  2005/03/03  \Plugin\Turb\Extended GridTurb\TurbApp.cpp
//

#include "StdAfx.h"
#include "TurbApp.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurbApp

BEGIN_MESSAGE_MAP(CTurbApp, CWinApp)
    //{{AFX_MSG_MAP(CTurbApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurbApp construction

BOOL CTurbApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here
    m_TypeInfoArray.SetArraySize(3);
    m_TypeInfoArray[0]->SetMatchName("GridCubical");
    string.LoadString(IDS_CUBICAL);
    m_TypeInfoArray[0]->SetLocalizedName(string.GetBuffer());

    m_TypeInfoArray[1]->SetMatchName("GridSpherical");
    string.LoadString(IDS_SPHERICAL);
    m_TypeInfoArray[1]->SetLocalizedName(string.GetBuffer());

    m_TypeInfoArray[2]->SetMatchName("GridCylindrical");
    string.LoadString(IDS_CYLINDRICAL);
    m_TypeInfoArray[2]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_GRIDTYPE);
    m_GridTypeInfo = HTypePropertyInfo::New(string, "GridType", &m_TypeInfoArray);
    m_GridTypeInfo->SetDefaultIndex(0);
    // Ensure that the material preview window will update if this value is changed.
    m_GridTypeInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Cubical grid properties
    m_UseXInfo = InitBool(IDS_XGRIDS, "GridUseX");
    m_XSizeInfo = InitFloat(IDS_SIZE, "GridXSize", 1.F, 0.F, 1000000.0F);
    m_XRatioInfo = InitPercent(IDS_RATIO, "GridXRatio", 0.1F);
    m_XBlurInfo = InitPercent(IDS_BLUR, "GridXBlur", 0.1F);

    m_UseYInfo = InitBool(IDS_YGRIDS, "GridUseY");
    m_YSizeInfo = InitFloat(IDS_SIZE, "GridYSize", 1.F, 0.F, 1000000.0F);
    m_YRatioInfo = InitPercent(IDS_RATIO, "GridYRatio", 0.1F);
    m_YBlurInfo = InitPercent(IDS_BLUR, "GridYBlur", 0.1F);

    // Cubical, Spherical and Cylindrical grids property
    m_UseZInfo = InitBool(IDS_ZGRIDS, "GridUseZ");
    m_ZSizeInfo = InitFloat(IDS_SIZE, "GridZSize", 1.F, 0.F, 1000000.0F);
    m_ZRatioInfo = InitPercent(IDS_RATIO, "GridZRatio", 0.1F);
    m_ZBlurInfo = InitPercent(IDS_BLUR, "GridZBlur", 0.1F);

    // Spherical and Cylindrical grids property
    m_UseAzimuthInfo = InitBool(IDS_AGRIDS, "GridUseAzimuth");
    m_AzimuthSizeInfo = InitFloat(IDS_FREQUENCY, "GridAzimuthFrequency", 1.F, 0.F, 1000000.0F);
    m_AzimuthRatioInfo = InitPercent(IDS_RATIO, "GridAzimuthRatio", 0.1F);
    m_AzimuthBlurInfo = InitPercent(IDS_BLUR, "GridAzimuthBlur", 0.1F);
    m_AzimuthStripeInfo = InitFloat(IDS_STRIPESIZE, "GridAzimuthStripeSize", 0.F, 0.F, 1000.0F);

    // Spherical grid property
    m_UseElevationInfo = InitBool(IDS_EGRIDS, "GridUseElevation");
    m_ElevationSizeInfo = InitFloat(IDS_SIZE, "GridElevationSize", 1.F, 0.F, 1000000.0F);
    m_ElevationRatioInfo = InitPercent(IDS_RATIO, "GridElevationRatio", 0.1F);
    m_ElevationBlurInfo = InitPercent(IDS_BLUR, "GridElevationBlur", 0.1F);
    m_ElevationStripeInfo = InitFloat(IDS_STRIPESIZE, "GridElevationStripeSize", 0.F, 0.F, 1000.0F);

    // Cylindrical grid property
    m_UseRadialInfo = InitBool(IDS_RGRIDS, "GridUseRadial");
    m_RadialSizeInfo = InitFloat(IDS_SIZE, "GridRadialSize", 1.F, 0.F, 1000000.0F);
    m_RadialRatioInfo = InitPercent(IDS_RATIO, "GridRadialRatio", 0.1F);
    m_RadialBlurInfo = InitPercent(IDS_BLUR, "GridRadialBlur", 0.1F);

    return CPluginApp::InitInstance();
}

HBoolPropertyInfo *CTurbApp::InitBool(const int IDS, const char *matchname, const BOOL def) {
    CString string;
    string.LoadString(IDS);
    HBoolPropertyInfo *Info = HBoolPropertyInfo::New(string, matchname);
    if (Info) {
        Info->SetDefaultValue(def);
        // This property can be hidden as needed.
        Info->SetVisibleWhen(HPropertyInfo::VISIBLESOMETIMES);
        // Update material preview window when this value is changed.
        Info->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
    }
    return Info;
}

HFloatPropertyInfo *CTurbApp::InitFloat(const int IDS, const char *matchname, const float def, const float min, const float max, const float fact, const UINT flags) {
    CString string;
    string.LoadString(IDS);
    HFloatPropertyInfo *Info = HFloatPropertyInfo::New(string, matchname);
    if (Info) {
        Info->SetFlags(flags);
        Info->SetDefaultValue(def);
        Info->SetMinValue(min);
        Info->SetMaxValue(max);
        Info->SetFactorValue(fact);
        // This property can be hidden as needed.
        Info->SetVisibleWhen(HPropertyInfo::VISIBLESOMETIMES);
        // Update material preview window when this value is changed.
        Info->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
    }
    return Info;
}

HPercentPropertyInfo *CTurbApp::InitPercent(const int IDS, const char *matchname, const float def, const float min, const float max) {
    CString string;
    string.LoadString(IDS);
    HPercentPropertyInfo *Info = HPercentPropertyInfo::New(string, matchname);
    if (Info) {
        Info->SetDefaultValue(def);
        Info->SetMinValue(min);
        Info->SetMaxValue(max);
        // This property can be hidden as needed.
        Info->SetVisibleWhen(HPropertyInfo::VISIBLESOMETIMES);
        // Update material preview window when this value is changed.
        Info->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
    }
    return Info;
}

int CTurbApp::ExitInstance() {
    // Delete Infos Here
    delete m_GridTypeInfo;

    delete m_UseXInfo;
    delete m_XSizeInfo;
    delete m_XRatioInfo;
    delete m_XBlurInfo;

    delete m_UseYInfo;
    delete m_YSizeInfo;
    delete m_YRatioInfo;
    delete m_YBlurInfo;

    delete m_UseZInfo;
    delete m_ZSizeInfo;
    delete m_ZRatioInfo;
    delete m_ZBlurInfo;

    delete m_UseAzimuthInfo;
    delete m_AzimuthSizeInfo;
    delete m_AzimuthRatioInfo;
    delete m_AzimuthBlurInfo;
    delete m_AzimuthStripeInfo;

    delete m_UseElevationInfo;
    delete m_ElevationSizeInfo;
    delete m_ElevationRatioInfo;
    delete m_ElevationBlurInfo;
    delete m_ElevationStripeInfo;

    delete m_UseRadialInfo;
    delete m_RadialSizeInfo;
    delete m_RadialRatioInfo;
    delete m_RadialBlurInfo;

    return CPluginApp::ExitInstance();
}

// The one and only CTurbApp object

CTurbApp theApp;

CString CTurbApp::LoadString(const int ID) const {
    char buffer[128];
    ::LoadString(m_hInstance, ID, buffer, 127);
    CString string(buffer);
    return string;
}
