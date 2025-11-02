#pragma once

#include "Midicontrol.h"

struct PROPERTIE2 {
    //Property selbst
    HProperty *prop;
    HFloatProperty *hfp;
    HColorProperty *hcp;
    //Type (Percent,Float etc)
    ObjectType objt;
    // 0 eventtype, 1 channel, 2 number
    COLORREF driven_value;
    //Werttabelle
    float value[128];
    //Werttabelle
    ColorBuf value_color[128];
    // aktueller Wert
    int akt_value;
    // Value bei Frame0
    int value_beginn;
    // changed
    int changed;
    //Pose ?
    int ispose;
    // FirstFrameValue
    float First_value;
    ColorVector First_value_c;
    int First_is;
};

struct PROPERTIE {
    //Property selbst
    HProperty *prop{};
    //Name fuer Listbox
    CString name{};
    //Fullname
    String Fullname;
    //Type (Percent,Float etc)
    ObjectType objt;
    //Type 0 other, 1 Transform, 2 Color, 3 Surface, 4 Pose
    int matchtype{};
    // gesteuert durch 0 nichts, 1 selectet controller
    int driven{};
    // 0 eventtype, 1 channel, 2 number
    int driven_value[3]{};
    //Wert der Pose zum Zeitpunkt vor bearbeitung, fuer Prozent,Euler,Float
    float org_value{};
    //Wert der Pose zum Zeitpunkt vor bearbeitung, fuer Color
    COLORREF org_value_color{};
    // min Value
    double min_value{};
    // max Value
    double max_value{};
    // min Value Color
    COLORREF min_value_color{};
    // max Value Color
    COLORREF max_value_color{};
    //Pose ?
    int ispose{};
};

struct OBJECT {
    //Object selbst
    HHashObject *hobj{};
    //Name fuer Listbox
    CString name{};
    //Filter fuer Listbox  0 other, 1 Transform, 2 Color, 3 Surface, 4 Pose
    int Filter{};
    //Matchname
    String matchname;
    //Anzahl Properties
    int azprop{};
    //Propertie structur
    PROPERTIE *prop{};
};

struct midi_in_list_node {
    int midi_in_number;
    HMIDIIN midi_in;
    midi_in_list_node *next_midi_in_list_node;
};

struct PARAMETER {
    //Project
    HProject *hproject{};
    // FPS
    double fps{};
    //Wartezeit
    unsigned int waittime{};
    //aktueller Frame
    Time time;
    //Zeitteiler
    unsigned int teiler{};
    //Aktueller Frame
    unsigned int frame{};
    //Anzahl Frames
    float end_frame{};
    //Chor
    HChor *chor{};
    //Anzahl Objecte , wenn 1 dann von Object gestartet
    int azobject{};
    //selektiertes Object fuer Listbox1 Assign
    int obj_selectet{};
    //Object structur
    OBJECT *obj{};
    // Midiinputdevice
    int midi_device{};
    // MidiDevice open ?
    int midi_device_run{};
    // MidiDevice record
    int midi_record_run{};
    // Playback
    int midi_play_run{};
    // SingleStep
    int midi_single_run{};
    int midi_single_run_changed{};
    // MidiStructur
    midi_in_list_node *first_midi_in_list_node{};
    // aktueller Midicontroller
    COLORREF aktcontroller{};
    // Controller Single Step forward
    COLORREF ssforward{};
    //anzahl controller note
    int az_note{};
    //note controller 
    PROPERTIE2 *p_note{};
    //anzahl controller key
    int az_key{};
    //key controller 
    PROPERTIE2 *p_key{};
    //anzahl controller control
    int az_control{};
    //control controller 
    PROPERTIE2 *p_control{};
    //override fuer keys
    int override{};
    //Start von Action ?
    int isaction{};
    //Save settings
    int embed{};
};
