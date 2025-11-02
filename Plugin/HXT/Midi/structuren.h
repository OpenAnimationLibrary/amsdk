//Structuren
#pragma once

#include "midifile.h"

struct Tempo {
    //Start diese Tempos
    long beginn_tick{};
    //Ende diese Tempos
    long end_tick{};
    // Midi Tickspersecond
    double m_ticksPerSecond{};
    // Midi TickSize
    double m_tickSize{};
};

struct Parameter {
    // HModel fuer Posen
    HModel *hm_org{};
    // FPS
    double fps{};
    // Property
    HProperty *p_property{};
    // Propertyname
    String p_name;
    // Propertyfullname
    String p_fullname;
    // Propertytype
    ObjectType p_type;
    // Property MinValue
    float p_min{};
    // Property MaxValue
    float p_max{};
    // ColorValue Sonderbehandlung
    bool p_iscolor{};
    // Property Farbe min
    COLORREF p_min_f{};
    // Property Farbe max
    COLORREF p_max_f{};
    // Midifile
    CString m_name{};
    // Tracknamen
    CString *m_trackname{};
    // gewaehlter MidiTrack
    int m_track{};
    // Anzahl MidiTrack
    int m_aztrack{};
    // Midi Control
    // 0 Note, 1 highest Note, 2 Lautstaerke
    int m_control{};
    // Midi MinValue
    int m_min{};
    // Midi MaxValue
    int m_max{};
    // Midi Frames zwischen Wechsel p_min -> p_max
    int m_frame_vor{};
    // Midi Frames zwischen Wechsel p_max -> p_min
    int m_frame_nach{};
    // Midi Tempo (Anzahl Tempowechsel max 20)
    int m_Tempo_az{};
    // Midi Tempo
    Tempo m_Tempo[5000]{};
    // Midifile Gesamtlaenge in Sekunden
    double m_length{};
    // Midifile
    MidiFile_t m_midi{};
    // HoldNote 0 nein, 1 ja
    int m_hold{};
    // HoldForce 0 nein, 1 ja
    int m_hold_force{};
    // HoldNote Laenge in Frames
    int m_hold_az{};
    // Anzahl der zu erzeugenden Frames
    int az_frames{};
    // Alten Wert addieren
    int add_old{};
    // BoolProperty zwischen Werten on oder off
    int bool_prop{};
    // Cp-Reduzieren 0 nein, 1 Variante 1 (Spline),2 Variante2 (linear)
    int reduce{};
    // IsAction
    int isaction{};
    // HAction
    HAction *haction{};
    //Cakewalk
    int cakewalk{};
};

struct FrameEvent {
    // Feld 0 - 127 Noten
    // Feld	128 Gesamtlautstaerke
    // Feld 129 Note mit der hoechsten Lautstaerke
    int velo[130];
};

struct Store_float {
    float wert{};
    bool setzen{};
};

struct Store_int {
    int wert{};
    bool setzen{};
};

struct Store_color {
    ColorBuf wert{};
    bool setzen{};
};

struct Store_bool {
    bool wert{};
    bool setzen{};
};
