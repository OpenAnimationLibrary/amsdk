// KB  2/1/01  \Ken90\Plugin\MotionCapture\BioVision BVH\Capture.cpp

// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#include "StdAfx.h"
#include "Capture.h"
#include "Matrix34.h"
#include "F_Protos.h"
#include "HashFile.h"
#include <afxtempl.h>

#define ERROR    0
#define ENDBONE  1
#define ENDBONES 2

/*   enum {    XTRANS=1, YTRANS=2, ZTRANS=4,
             XROT=8, YROT=16, ZROT=32,
             XSCALE=64, YSCALE=128, ZSCALE=256};
*/

class BvSensor final {
public:
    CList<int, int> m_channels;
    String m_name;
    Vector m_start;
    Vector m_end;
    BvSensor *m_parent{nullptr};
    int m_index{0};
    bool m_notended{true};

    BvSensor() noexcept = default;

    void StoreEnd(Vector end);
    int Load(HashStream &hs, const String &name, BvSensor *parent, CList<BvSensor *, BvSensor *> *list, int *index);
    int ReadFrame(HashStream &hs, const Driver *driver);
};

HProperty *Driver::GetPropertyAt(int i) {
    return nullptr;
}

void BvSensor::StoreEnd(const Vector end) {
    if (m_notended)
        m_end = end;
    m_notended = false;
}

int BvSensor::Load(HashStream &hs, const String &name, BvSensor *parent, CList<BvSensor *, BvSensor *> *list, int *index) {
    Vector offset;
    String command;
    String nextname = "Error";
    BOOL end = FALSE;
    BOOL added = FALSE;
    m_parent = parent;
    m_name = name;
    m_index = *index;
    *index = *index + 1;
    MemoryStream ms(256);
    while (TRUE) {
        hs.ReadLine(ms);
        if (hs.IsFailed())
            return FALSE;

        ms >> command;
        if (command == "{") {
            if (!added) {
                list->AddTail(this);
                added = TRUE;
            }
            if (!end) {
                auto *sensor = new BvSensor;
                const int rvalue = sensor->Load(hs, nextname, this, list, index);
                if (rvalue == ENDBONES)
                    return rvalue;
                if (rvalue == ERROR)
                    return rvalue;
            }
        } else if (command == "ROOT" || command == "JOINT") {
            ms.ReadLine(nextname);
        } else if (command == "OFFSET") {
            ms >> offset.x >> offset.y >> offset.z;
            offset *= CENTIMETERSPERINCH;
            if (!end) {
                if (parent) {
                    m_start = parent->m_start + offset;
                    parent->StoreEnd(m_start);
                } else {
                    m_start = offset;
                }
            } else {
                StoreEnd(m_start + offset);
            }
        } else if (command == "CHANNELS") {
            int numchannels;
            String channeltype;
            ms >> numchannels;
            for (int i = 0; i < numchannels; ++i) {
                ms >> channeltype;
                if (channeltype == "Xposition")
                    m_channels.AddTail(Driver::XTRANS);
                else if (channeltype == "Yposition")
                    m_channels.AddTail(Driver::YTRANS);
                else if (channeltype == "Zposition")
                    m_channels.AddTail(Driver::ZTRANS);
                else if (channeltype == "Zrotation")
                    m_channels.AddTail(Driver::ZORIENT);
                else if (channeltype == "Xrotation")
                    m_channels.AddTail(Driver::XORIENT);
                else if (channeltype == "Yrotation")
                    m_channels.AddTail(Driver::YORIENT);
                else if (channeltype == "Xscale")
                    m_channels.AddTail(Driver::XSCALE);
                else if (channeltype == "Yscale")
                    m_channels.AddTail(Driver::YSCALE);
                else if (channeltype == "Zscale")
                    m_channels.AddTail(Driver::ZSCALE);
            }
        } else if (command == "End") {
            end = TRUE;
        } else if (command == "}") {
            if (!end)
                return ENDBONE;
            end = FALSE;
        } else if (command == "MOTION")
            return ENDBONES;
    }
}

int BvSensor::ReadFrame(HashStream &hs, const Driver *driver) {
    float value;
    Matrix34 rotate(Identity34());
    Vector translate;
    BOOL isrotated = FALSE;
    BOOL istranslated = FALSE;
    [[maybe_unused]] BOOL rc;
    for (POSITION pos = m_channels.GetHeadPosition(); pos;) {
        const int channeltype = m_channels.GetNext(pos);
        //      StoreRotate( sensornum, XYZRotate( xr, yr, zr )); 
        switch (channeltype) {
            case Driver::XTRANS:
                hs >> translate.x;
                translate.x *= CENTIMETERSPERINCH;
                //driver->SetValue( m_index, Driver::XTRANS, value*CENTIMETERSPERINCH);
                istranslated = TRUE;
                break;
            case Driver::YTRANS:
                hs >> translate.y;
                translate.y *= CENTIMETERSPERINCH;
                //driver->SetValue( m_index, Driver::YTRANS, value*CENTIMETERSPERINCH);
                istranslated = TRUE;
                break;
            case Driver::ZTRANS:
                hs >> translate.z;
                translate.z *= CENTIMETERSPERINCH;
                //driver->SetValue( m_index, Driver::ZTRANS, value*CENTIMETERSPERINCH);
                istranslated = TRUE;
                break;
            case Driver::XORIENT:
                hs >> value;
                //driver->SetValue( m_index, Driver::XORIENT, value);
                rotate *= XRotate(value); // * rotate;
                isrotated = TRUE;
                break;
            case Driver::YORIENT:
                hs >> value;
                //driver->SetValue( m_index, Driver::YORIENT, value);
                rotate *= YRotate(value); // * rotate;
                isrotated = TRUE;
                break;
            case Driver::ZORIENT:
                hs >> value;
                //driver->SetValue( m_index, Driver::ZORIENT, value);
                rotate *= ZRotate(value); // * rotate;
                isrotated = TRUE;
                break;
            case Driver::XSCALE:
                hs >> value;
                rc = driver->SetValue(m_index, Driver::XSCALE, value);
                break;
            case Driver::YSCALE:
                hs >> value;
                rc = driver->SetValue(m_index, Driver::YSCALE, value);
                break;
            case Driver::ZSCALE:
                hs >> value;
                rc = driver->SetValue(m_index, Driver::ZSCALE, value);
                break;

        }
    }
    if (hs.IsFailed())
        return FALSE;
    if (istranslated)
        rc = driver->StoreTranslateStandard(m_index, translate);
    if (isrotated)
        rc = driver->StoreRotateStandard(m_index, rotate);
    return TRUE;
}

/*
static Matrix34 XYZRotate(float x, const float y, const float z) {
    //   return XRotate( x ) * YRotate( y ) * ZRotate( z );  // below is faster version of this with -y becomes new z, and z becomes y
    const float cx = hash_math::cos(x / hash_constants::radians),
          sx = hash_math::sin(x / hash_constants::radians),
          cy = hash_math::cos(y / hash_constants::radians),
          sy = hash_math::sin(y / hash_constants::radians),
          cz = hash_math::cos(z / hash_constants::radians),
          sz = hash_math::sin(z / hash_constants::radians);

    return Matrix34(Vector4(cy * cz, sy, cy * sz, 0.F),
                    Vector4(sx * sy * cz + cx * sz, -sx * cy, sx * sy * sz - cx * cz, 0.F),
                    Vector4(-cx * sy * cz + sx * sz, cx * cy, -cx * sy * sz - sx * cz, 0.F));
}
*/
bool Driver::StaticCaptureSequence() {
    //   FILE *file;
    //   float systemrate = GetSystemRate();
    //   float frame, lastframe;
    //   Time now;//just a test to see if time will work here
    //   float framestep, capturerate = GetCaptureRate();
    //   float xt, yt, zt, xr, yr, zr;
    //   char  segname[256];

    String filename;
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest("Open BioVision BVH File", "BioVision BVH Files (*.bvh)|*.bvh|TEXT|All Files (*.*)|*.*|****||", filename, "bva", "BVA"))
            return TRUE;
    }
    MemoryStream fs;
    if (!fs.Open(filename, FileMode::HS_LOAD | FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS))
        return FALSE;

    String command;
    fs >> command;
    if (command != "HIERARCHY")
        return FALSE;

    fs >> command;
    if (command != "ROOT")
        return FALSE;
    String name;
    if (!fs.ReadLine(name))
        return FALSE;
    fs >> command;
    if (command != "{")
        return FALSE;

    CList<BvSensor *, BvSensor *> sensorlist;
    auto *firstbone = new BvSensor;
    int index = 0;
    firstbone->Load(fs, name, nullptr, &sensorlist, &index);

    const int sensors = sensorlist.GetCount();
    if (!BuildSensorArray(sensors))
        return FALSE;
    for (POSITION pos = sensorlist.GetHeadPosition(); pos;) {
        const BvSensor *sensor = sensorlist.GetNext(pos);
        if (sensor->m_parent)
            InsertSensor(sensor->m_index, sensor->m_name.Get(), sensor->m_start, sensor->m_end, sensor->m_parent->m_index);
        else
            //sensor->m_end.x = sensor->m_start.x; //should leave m_end alone and rotate root translates to global
            //sensor->m_end.y = sensor->m_start.y;
            //sensor->m_end.z = 10;
            InsertSensor(sensor->m_index, sensor->m_name.Get(), sensor->m_start, sensor->m_end, -1);
    }
    DoneInsertingSensors();

    fs >> command;
    if (command != "MOTION")
        return FALSE;

    int frames;
    fs >> command >> frames;
    if (command != "Frames:")
        return FALSE;

    String command2;
    double frametime;
    fs >> command >> command2 >> frametime;
    if (command != "Frame" && command2 != "Time:")
        return FALSE;

    const Time starttime = GetTime();
    Time time;
    MemoryStream ms(2048);
    for (int frame = 0; frame < frames; ++frame) {
        time.SetSeconds(frame * frametime + starttime.GetSeconds());
        SetTime(time);
        fs.ReadLine(ms);
        if (fs.IsFailed())
            return FALSE;
        for (POSITION pos = sensorlist.GetHeadPosition(); pos;) {
            BvSensor *sensor = sensorlist.GetNext(pos);
            if (!sensor->ReadFrame(ms, this))
                return FALSE;
        }
        if (EscapeKeyDown()) {
            break;
        }
    }
    FreeSensorArray();
    Redraw();
    return TRUE;
}
