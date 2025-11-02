// Amplitude.h

#if !defined(AFX_Amplitude_H__4841EEE0_9D7C_4525_B3D2_3C869A68C457__INCLUDED_)
#define AFX_Amplitude_H__4841EEE0_9D7C_4525_B3D2_3C869A68C457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif
#ifndef __cplusplus
#define __cplusplus
#endif

#include "resource.h"		// Hauptsymbole
#include "HashFile.h"
#include "F_Protos.h"
#include "Matrix34.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HPropert.h"
#include "SDK/HPropDri.h"
#include "SDK/HPatch.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HProgres.h"
#include "SDK/HChor.h"
#include "SDK/HCamera.h"
#include "SDK/HAction.h"
#include "SDK/HMaterial.h"
#include "Fft.h"
#include "Wave.h"
#include "struct.h"
#include <memory>

/////////////////////////////////////////////////////////////////////////////
// CAmplitudeApp

class HCP;
class HModel;
class HModelCache;
class HAction;
class HGroup;
class HGroupCP;
class HProgressBar;

class CAmplitudeApp final : public CPluginApp {
public:
    CAmplitudeApp() noexcept = default;
    ~CAmplitudeApp() override = default;

    CAmplitudeApp(const CAmplitudeApp&) = delete;
    CAmplitudeApp &operator= (const CAmplitudeApp&) = delete; 
    CAmplitudeApp(CAmplitudeApp &&) = delete; 
    CAmplitudeApp &operator=(CAmplitudeApp &&) = delete; 
    BOOL OnProperty(HProperty *htreeobject);
#ifdef _DEBUG
    [[nodiscard]] BOOL Work() const;
#endif
    BOOL WorkFloat(); //Euler
    BOOL WorkPercent();
    BOOL WorkInt();
    BOOL WorkColor();
    float GetWaveValue(double samplepos);
    Parameter para;

    //   std::auto_ptr<Fft> m_fftTransformer;
    std::unique_ptr<Fft> m_fftTransformer{};
    double m_step{0};
    double m_stepend{0};
    double m_offset_pos{0};
    std::vector<int> m_outBuf_L{};
    std::vector<int> m_outBuf_R{};

    //{{AFX_VIRTUAL(CAmplitudeApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CAmplitudeApp)
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_Amplitude_H__4841EEE0_9D7C_4525_B3D2_3C869A68C457__INCLUDED_)
