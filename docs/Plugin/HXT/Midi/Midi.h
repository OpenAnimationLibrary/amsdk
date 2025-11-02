// Midi.h : Haupt-Header-Datei für die DLL MIDI
//

#if !defined(AFX_MIDI_H__4841EEE0_9D7C_4525_B3D2_3C869A68C457__INCLUDED_)
#define AFX_MIDI_H__4841EEE0_9D7C_4525_B3D2_3C869A68C457__INCLUDED_

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
#include "structuren.h"
#include "midifile.h"

/////////////////////////////////////////////////////////////////////////////
// CMidiApp
// Siehe Midi.cpp für die Implementierung dieser Klasse
//
//#define QUAD(A)        ((A) * (A))
//#define S_PI           3.1415926535898
//#define SD_PI          (2*3.1415926535898)
//static double fround(const double n, const int d) {
//    return hash_math::floor(n * hash_math::pow(10., d) + .5) / hash_math::pow(10., d);
//}
//#define fround(A, B) floor((A) * pow(10., B) + .5) / pow(10., B)

class HCP;
class HModel;
class HModelCache;
class HAction;
class HGroup;
class HGroupCP;
class HProgressBar;

class CMidiApp final : public CPluginApp {
public:
    CMidiApp();
    ~CMidiApp() override;
    BOOL InitApp();
    BOOL OnModel(HModel *htreeobject);
    BOOL OnProperty(HProperty *htreeobject);
    BOOL MainWorking();
    BOOL GetMidiTiming();
    BOOL GetMidiFrameEvents();
    void SaveSettings() const;
    void GetSettings() const;

    Parameter *para{};
    FrameEvent *frameevent{};
    MidiFile_t midi_file{};
    MidiFileTrack_t track{};

    /*
    BOOL ModelWorking(HModel *hm_org);
    BOOL OnPropertyWorking(HTreeObject *htreeobject);
    */
    // Überladungen
    // Vom Klassenassistenten generierte Überladungen virtueller Funktionen
    //{{AFX_VIRTUAL(CMidiApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CMidiApp)
    // HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MIDI_H__4841EEE0_9D7C_4525_B3D2_3C869A68C457__INCLUDED_)
