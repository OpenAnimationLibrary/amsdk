#pragma once

#include "StdAfx.h"
#include "Amplitude.h"

struct Parameter {
    HChor *m_hchor;
    HModel *m_hmodel; // HModel fuer Posen
    HProperty *m_property; // property
    ObjectType m_objtype; // Propertytype
    double m_fps; // Projectfps
    float m_minf; // Property MinValue
    float m_maxf; // Property MaxValue
    int m_mini; // Property MinValue
    int m_maxi; // Property MaxValue
    int m_timemode;
    int m_timing;
    int m_channels;
    int add_tocurrentvalue;
    int m_band; // which frequenzband should be used (0-9 fest; 10 userdefined band)
    int m_halfframe; //keyframe generation
    Time m_chorlength;
    COLORREF m_minc; // ColorValue min
    COLORREF m_maxc; // ColorValue max
    String m_name; // Propertyname 
    String m_fullname; // Propertyfullname
    String m_wavefilename; // filename
    PCM_Wave m_wave; // wavedata
    BOOL m_useband; // use band or loudness
    BOOL m_iscolor; // ColorValue
};
