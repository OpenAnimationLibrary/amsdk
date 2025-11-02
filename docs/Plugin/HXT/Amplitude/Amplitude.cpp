// Amplitude.cpp : Legt die Initialisierungsroutinen für die DLL fest.
#include "StdAfx.h"
#include "Amplitude.h"
#include "ImportDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmplitudeApp

BEGIN_MESSAGE_MAP(CAmplitudeApp, CWinApp)
        //{{AFX_MSG_MAP(CAmplitudeApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmplitudeApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CAmplitudeApp-Objekt

CAmplitudeApp theApp;

BOOL CAmplitudeApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CAmplitudeApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CAmplitudeApp::OnProperty(HProperty *htreeobject) {
    para.m_hmodel = (HModel *)htreeobject->GetParentOfType(HOT_MODEL);
    para.m_fps = GetHProject()->GetFPS();
    para.m_timemode = GetTimeMode();
    para.m_property = htreeobject;
    para.m_name = htreeobject->GetName();
    para.m_fullname = htreeobject->GetFullName();
    para.m_objtype = htreeobject->GetObjectType();

    para.m_wavefilename = GetRegistryString("Amplitude HXT", "filename", "");
    para.m_mini = GetRegistryValue("Amplitude HXT", "min_i", 0);
    para.m_maxi = GetRegistryValue("Amplitude HXT", "max_i", 100);
    para.m_minf = GetRegistryValue("Amplitude HXT", "min_f", 0);
    para.m_maxf = GetRegistryValue("Amplitude HXT", "max_f", 100);
    BYTE r_min = GetRegistryValue("Amplitude HXT", "min_color_r", 0);
    BYTE g_min = GetRegistryValue("Amplitude HXT", "min_color_g", 0);
    BYTE b_min = GetRegistryValue("Amplitude HXT", "min_color_b", 0);
    BYTE r_max = GetRegistryValue("Amplitude HXT", "max_color_r", 255);
    BYTE g_max = GetRegistryValue("Amplitude HXT", "max_color_g", 255);
    BYTE b_max = GetRegistryValue("Amplitude HXT", "max_color_b", 255);
    RGBFloat color(r_min, g_min, b_min);
    para.m_minc = color.GetCOLORREF();
    color.Set(r_max, g_max, b_max);
    para.m_maxc = color.GetCOLORREF();
    para.m_channels = GetRegistryValue("Amplitude HXT", "channels", 0);
    para.m_halfframe = GetRegistryValue("Amplitude HXT", "halfframe", 0);

    para.m_band = GetRegistryValue("Amplitude HXT", "frequencyband", 5);
    para.m_useband = GetRegistryValue("Amplitude HXT", "usefrequencyband", FALSE);
    para.m_wave.m_bands[0].start_freq = 0;
    para.m_wave.m_bands[0].end_freq = 44;
    para.m_wave.m_bands[1].start_freq = 44;
    para.m_wave.m_bands[1].end_freq = 88;
    para.m_wave.m_bands[2].start_freq = 88;
    para.m_wave.m_bands[2].end_freq = 177;
    para.m_wave.m_bands[3].start_freq = 177;
    para.m_wave.m_bands[3].end_freq = 355;
    para.m_wave.m_bands[4].start_freq = 355;
    para.m_wave.m_bands[4].end_freq = 710;
    para.m_wave.m_bands[5].start_freq = 710;
    para.m_wave.m_bands[5].end_freq = 1420;
    para.m_wave.m_bands[6].start_freq = 1420;
    para.m_wave.m_bands[6].end_freq = 2840;
    para.m_wave.m_bands[7].start_freq = 2840;
    para.m_wave.m_bands[7].end_freq = 5680;
    para.m_wave.m_bands[8].start_freq = 5680;
    para.m_wave.m_bands[8].end_freq = 11360;
    para.m_wave.m_bands[9].start_freq = 11360;
    para.m_wave.m_bands[9].end_freq = 22720;
    para.m_wave.m_bands[10].start_freq = GetRegistryValue("Amplitude HXT", "userfrequencyband_low", 4392); //userdefined
    para.m_wave.m_bands[10].end_freq = GetRegistryValue("Amplitude HXT", "userfrequencyband_high", 4435); //userdefined

    if (para.m_name == "Intensity") {
        if (para.m_property->GetParentOfType(HOT_LIGHT))
            para.m_objtype = HOT_PERCENT;
    }
    if (para.m_fullname.Find("Surface.Reflectivity") > 0)
        para.m_objtype = HOT_PERCENT;

    if (para.m_objtype == HOT_COLOR) {
        para.m_iscolor = true;
        const HColorProperty *hcp = (HColorProperty *)para.m_property;
        para.m_minc = para.m_maxc = hcp->GetCOLORREF();
    } else {
        para.m_iscolor = false;
        switch (para.m_objtype) {
            case HOT_INTEGER:
            {
                const HIntProperty *hip = (HIntProperty *)para.m_property;
                para.m_mini = para.m_maxi = hip->GetValue();
            }
            break;
            case HOT_PERCENT:
            {
                const HPercentProperty *hip = (HPercentProperty *)para.m_property;
                const HPercentPropertyInfo *hpi = (HPercentPropertyInfo *)hip->GetPropertyInfo();
                para.m_minf = para.m_maxf = hip->GetValue() * hpi->GetFactorValue();
            }
            break;
            default:
            {
                const HFloatProperty *hip = (HFloatProperty *)para.m_property;
                const HFloatPropertyInfo *hpi = (HFloatPropertyInfo *)hip->GetPropertyInfo();
                para.m_minf = para.m_maxf = hip->GetValue() * hpi->GetFactorValue();
            }
                break;
        }
    }

    para.m_hchor = (HChor *)htreeobject->GetParentOfType(HOT_CHOR);
    para.m_chorlength = para.m_hchor->GetTotalTime()->GetValue();

    if (para.m_objtype == HOT_CATEGORYPROPERTY) {
#ifdef _DEBUG
        const String temp = "HOT_CATEGORYPROPERTY " + para.m_name + "  " + para.m_fullname;
        AfxMessageBox(temp.Get());
#endif
        return TRUE;
    }
#ifdef _DEBUG
    //   para.m_wavefilename = "";
    //    para.m_wavefilename = "E://bugs//Amplitude//wavfiles//test_440_10000_44k.wav";
    para.m_wavefilename = "E://bugs//Amplitude//wavfiles//Kalimba2_small.wav";
#endif

    ImportDlg cdlg(para);
    if (cdlg.DoModal() != IDOK) {
        para.m_wave.FreeWave();
        return TRUE;
    }
    SetRegistryString("Amplitude HXT", "filename", para.m_wavefilename);
    SetRegistryValue("Amplitude HXT", "min_i", para.m_mini);
    SetRegistryValue("Amplitude HXT", "max_i", para.m_maxi);
    SetRegistryValue("Amplitude HXT", "min_f", para.m_minf);
    SetRegistryValue("Amplitude HXT", "max_f", para.m_maxf);
    r_min = GetRValue(para.m_minc);
    g_min = GetGValue(para.m_minc);
    b_min = GetBValue(para.m_minc);
    r_max = GetRValue(para.m_maxc);
    g_max = GetGValue(para.m_maxc);
    b_max = GetBValue(para.m_maxc);
    SetRegistryValue("Amplitude HXT", "min_color_r", r_min);
    SetRegistryValue("Amplitude HXT", "min_color_g", g_min);
    SetRegistryValue("Amplitude HXT", "min_color_b", b_min);
    SetRegistryValue("Amplitude HXT", "max_color_r", r_max);
    SetRegistryValue("Amplitude HXT", "max_color_g", g_max);
    SetRegistryValue("Amplitude HXT", "max_color_b", b_max);
    SetRegistryValue("Amplitude HXT", "channels", para.m_channels);
    SetRegistryValue("Amplitude HXT", "halfframe", para.m_halfframe);
    SetRegistryValue("Amplitude HXT", "frequencyband", para.m_band);
    SetRegistryValue("Amplitude HXT", "usefrequencyband", para.m_useband);
    SetRegistryValue("Amplitude HXT", "userfrequencyband_low", para.m_wave.m_bands[10].start_freq); //userdefined
    SetRegistryValue("Amplitude HXT", "userfrequencyband_high", para.m_wave.m_bands[10].end_freq); //userdefined

    if (para.m_hchor) {
        {
            AFX_MANAGE_STATE(AfxGetAppModuleState())
            para.m_hchor->SaveAllToUndo();
        }
    }

    m_stepend = 1.0 / para.m_fps;
    if (para.m_halfframe)
        m_stepend *= 0.5;
    m_step = 1.0 / para.m_wave.GetSampleRate();
    const double step_length = m_stepend / m_step; //in samples
    m_offset_pos = m_step * ((step_length - 1024) / 2); //for fitting windowsize fft
    //   m_fftTransformer = std::auto_ptr<Fft>(new Fft(1024, para.m_wave.GetSampleRate()));
    m_fftTransformer = std::make_unique<Fft>(1024, para.m_wave.GetSampleRate());
    m_outBuf_L.resize(1024);
    m_outBuf_R.resize(1024);
    //Calculate the bands
    for (auto &m_band: para.m_wave.m_bands) {
        m_band.start = m_fftTransformer->HzToNearestPoint(m_band.start_freq);
        m_band.end = m_fftTransformer->HzToNearestPoint(m_band.end_freq);
        m_band.az_freq = m_band.end - m_band.start;
        m_band.az_freq += 1;
    }

    switch (para.m_objtype) {
        case HOT_COLOR:
            WorkColor();
            break;
        case HOT_INTEGER:
            WorkInt();
            break;
        case HOT_PERCENT:
            WorkPercent();
            break;
        default:
            WorkFloat();
            break;
    }
    para.m_wave.FreeWave();

    if (para.m_hchor) {
        para.m_hchor->SetTime(Time());
        para.m_hchor->Dirty();
    }
    para.m_property->OnModified();
    GetHProject()->UpdateAllViews(TRUE);
    return TRUE;
}
