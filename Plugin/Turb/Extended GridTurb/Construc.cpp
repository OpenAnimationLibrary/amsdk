// Yves  2005/03/03  \Plugin\Turb\Extended GridTurb\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"
//#include "Perlin.h"
//#include "Rnd.h"

extern CTurbApp theApp;

extern "C" __declspec(dllexport) Turbulence *CreateTurbulence(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomTurbulence(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return TURBULENCEDLLVERSION;
}

CustomTurbulence::CustomTurbulence(HTreeObject *treeobject) : Turbulence(treeobject) {
    m_GridType = nullptr;
    m_UseX = nullptr;
    m_XSize = nullptr;
    m_XRatio = nullptr;
    m_XBlur = nullptr;
    m_UseY = nullptr;
    m_YSize = nullptr;
    m_YRatio = nullptr;
    m_YBlur = nullptr;
    m_UseZ = nullptr;
    m_ZSize = nullptr;
    m_ZRatio = nullptr;
    m_ZBlur = nullptr;
    m_UseAzimuth = nullptr;
    m_AzimuthSize = nullptr;
    m_AzimuthRatio = nullptr;
    m_AzimuthBlur = nullptr;
    m_AzimuthStripe = nullptr;
    m_UseElevation = nullptr;
    m_ElevationSize = nullptr;
    m_ElevationRatio = nullptr;
    m_ElevationBlur = nullptr;
    m_ElevationStripe = nullptr;
    m_UseRadial = nullptr;
    m_RadialSize = nullptr;
    m_RadialRatio = nullptr;
    m_RadialBlur = nullptr;
    m_CopyOf = nullptr;

    if (!treeobject)
        return;

    m_UIDirty = m_TypeDirty = m_UseXDirty = FALSE;

    m_GridType = HTypeProperty::New(theApp.m_GridTypeInfo);

    m_UseX = HBoolCategoryProperty::New(theApp.m_UseXInfo);
    if (!m_UseX)
        return;
    m_XSize = HFloatProperty::New(theApp.m_XSizeInfo);
    m_UseX->AddProperty(m_XSize);
    m_XRatio = HFloatProperty::New(theApp.m_XRatioInfo);
    m_UseX->AddProperty(m_XRatio);
    m_XBlur = HPercentProperty::New(theApp.m_XBlurInfo);
    m_UseX->AddProperty(m_XBlur);

    m_UseY = HBoolCategoryProperty::New(theApp.m_UseYInfo);
    if (!m_UseY)
        return;
    m_YSize = HFloatProperty::New(theApp.m_YSizeInfo);
    m_UseY->AddProperty(m_YSize);
    m_YRatio = HFloatProperty::New(theApp.m_YRatioInfo);
    m_UseY->AddProperty(m_YRatio);
    m_YBlur = HPercentProperty::New(theApp.m_YBlurInfo);
    m_UseY->AddProperty(m_YBlur);

    m_UseZ = HBoolCategoryProperty::New(theApp.m_UseZInfo);
    if (!m_UseZ)
        return;
    m_ZSize = HFloatProperty::New(theApp.m_ZSizeInfo);
    m_UseZ->AddProperty(m_ZSize);
    m_ZRatio = HFloatProperty::New(theApp.m_ZRatioInfo);
    m_UseZ->AddProperty(m_ZRatio);
    m_ZBlur = HPercentProperty::New(theApp.m_ZBlurInfo);
    m_UseZ->AddProperty(m_ZBlur);

    m_UseAzimuth = HBoolCategoryProperty::New(theApp.m_UseAzimuthInfo);
    if (!m_UseAzimuth)
        return;
    m_AzimuthSize = HFloatProperty::New(theApp.m_AzimuthSizeInfo);
    m_UseAzimuth->AddProperty(m_AzimuthSize);
    m_AzimuthRatio = HFloatProperty::New(theApp.m_AzimuthRatioInfo);
    m_UseAzimuth->AddProperty(m_AzimuthRatio);
    m_AzimuthBlur = HPercentProperty::New(theApp.m_AzimuthBlurInfo);
    m_UseAzimuth->AddProperty(m_AzimuthBlur);
    m_AzimuthStripe = HFloatProperty::New(theApp.m_AzimuthStripeInfo);
    m_UseAzimuth->AddProperty(m_AzimuthStripe);

    m_UseElevation = HBoolCategoryProperty::New(theApp.m_UseElevationInfo);
    if (!m_UseElevation)
        return;
    m_ElevationSize = HFloatProperty::New(theApp.m_ElevationSizeInfo);
    m_UseElevation->AddProperty(m_ElevationSize);
    m_ElevationRatio = HFloatProperty::New(theApp.m_ElevationRatioInfo);
    m_UseElevation->AddProperty(m_ElevationRatio);
    m_ElevationBlur = HPercentProperty::New(theApp.m_ElevationBlurInfo);
    m_UseElevation->AddProperty(m_ElevationBlur);
    m_ElevationStripe = HFloatProperty::New(theApp.m_ElevationStripeInfo);
    m_UseElevation->AddProperty(m_ElevationStripe);

    m_UseRadial = HBoolCategoryProperty::New(theApp.m_UseRadialInfo);
    if (!m_UseRadial)
        return;
    m_RadialSize = HFloatProperty::New(theApp.m_RadialSizeInfo);
    m_UseRadial->AddProperty(m_RadialSize);
    m_RadialRatio = HFloatProperty::New(theApp.m_RadialRatioInfo);
    m_UseRadial->AddProperty(m_RadialRatio);
    m_RadialBlur = HPercentProperty::New(theApp.m_RadialBlurInfo);
    m_UseRadial->AddProperty(m_RadialBlur);

    // By default, grid type is cubical so those shouldn't be visible
    m_UseAzimuth->Show(FALSE);
    m_UseElevation->Show(FALSE);
    m_UseRadial->Show(FALSE);
}

CustomTurbulence::~CustomTurbulence() {
    if (m_GridType) {
        delete m_GridType;
        m_GridType = nullptr;
    }
    if (!m_UseX)
        return;
    if (m_XSize) {
        m_UseX->RemoveProperty(m_XSize);
        delete m_XSize;
        m_XSize = nullptr;
    }
    if (m_XRatio) {
        m_UseX->RemoveProperty(m_XRatio);
        delete m_XRatio;
        m_XRatio = nullptr;
    }
    if (m_XBlur) {
        m_UseX->RemoveProperty(m_XBlur);
        delete m_XBlur;
        m_XBlur = nullptr;
    }
    delete m_UseX;
    m_UseX = nullptr;

    if (!m_UseY)
        return;
    if (m_YSize) {
        m_UseY->RemoveProperty(m_YSize);
        delete m_YSize;
        m_YSize = nullptr;
    }
    if (m_YRatio) {
        m_UseY->RemoveProperty(m_YRatio);
        delete m_YRatio;
        m_YRatio = nullptr;
    }
    if (m_YBlur) {
        m_UseY->RemoveProperty(m_YBlur);
        delete m_YBlur;
        m_YBlur = nullptr;
    }
    delete m_UseY;
    m_UseY = nullptr;

    if (!m_UseZ)
        return;
    if (m_ZSize) {
        m_UseZ->RemoveProperty(m_ZSize);
        delete m_ZSize;
        m_ZSize = nullptr;
    }
    if (m_ZRatio) {
        m_UseZ->RemoveProperty(m_ZRatio);
        delete m_ZRatio;
        m_ZRatio = nullptr;
    }
    if (m_ZBlur) {
        m_UseZ->RemoveProperty(m_ZBlur);
        delete m_ZBlur;
        m_ZBlur = nullptr;
    }
    delete m_UseZ;
    m_UseZ = nullptr;

    if (!m_UseAzimuth)
        return;
    if (m_AzimuthSize) {
        m_UseAzimuth->RemoveProperty(m_AzimuthSize);
        delete m_AzimuthSize;
        m_AzimuthSize = nullptr;
    }
    if (m_AzimuthRatio) {
        m_UseAzimuth->RemoveProperty(m_AzimuthRatio);
        delete m_AzimuthRatio;
        m_AzimuthRatio = nullptr;
    }
    if (m_AzimuthBlur) {
        m_UseAzimuth->RemoveProperty(m_AzimuthBlur);
        delete m_AzimuthBlur;
        m_AzimuthBlur = nullptr;
    }
    if (m_AzimuthStripe) {
        m_UseAzimuth->RemoveProperty(m_AzimuthStripe);
        delete m_AzimuthStripe;
        m_AzimuthStripe = nullptr;
    }
    delete m_UseAzimuth;
    m_UseAzimuth = nullptr;

    if (!m_UseElevation)
        return;
    if (m_ElevationSize) {
        m_UseElevation->RemoveProperty(m_ElevationSize);
        delete m_ElevationSize;
        m_ElevationSize = nullptr;
    }
    if (m_ElevationRatio) {
        m_UseElevation->RemoveProperty(m_ElevationRatio);
        delete m_ElevationRatio;
        m_ElevationRatio = nullptr;
    }
    if (m_ElevationBlur) {
        m_UseElevation->RemoveProperty(m_ElevationBlur);
        delete m_ElevationBlur;
        m_ElevationBlur = nullptr;
    }
    if (m_ElevationStripe) {
        m_UseElevation->RemoveProperty(m_ElevationStripe);
        delete m_ElevationStripe;
        m_ElevationStripe = nullptr;
    }
    delete m_UseElevation;
    m_UseElevation = nullptr;

    if (!m_UseRadial)
        return;
    if (m_RadialSize) {
        m_UseRadial->RemoveProperty(m_RadialSize);
        delete m_RadialSize;
        m_RadialSize = nullptr;
    }
    if (m_RadialRatio) {
        m_UseRadial->RemoveProperty(m_RadialRatio);
        delete m_RadialRatio;
        m_RadialRatio = nullptr;
    }
    if (m_RadialBlur) {
        m_UseRadial->RemoveProperty(m_RadialBlur);
        delete m_RadialBlur;
        m_RadialBlur = nullptr;
    }
    delete m_UseRadial;
    m_UseRadial = nullptr;
}
