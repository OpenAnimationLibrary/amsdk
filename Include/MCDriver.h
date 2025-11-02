//RC  4/24/2002  \HRandy95\Include\MCDriver.h
#pragma once

#include "Vector.h"
#include "Exports.h"
#include "DllPlugi.h"

class MCDevice;
class Matrix34;
class Time;

constexpr int MCDLLVERSION = 2;

// ReSharper disable once CppClassCanBeFinal
class PLUGINEXPORT MCDriver : public DLLPlugin {
    MCDevice *m_device{nullptr};

public:
    //RETURN VALUES FOR LiveCaptureFrame()
    enum FrameError {
        FE_FAILED,
        FE_SUCCESS,
        FE_TRYAGAIN
    };

    //CHANNEL INDEXES FOR SETVALUE
    enum {
        XTRANS,
        YTRANS,
        ZTRANS,
        XSCALE,
        YSCALE,
        ZSCALE,
        XORIENT,
        YORIENT,
        ZORIENT,
        ROLL
    };

    explicit MCDriver(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}

    void SetDevice(MCDevice *pdevice) {
        m_device = pdevice;
    }

    [[nodiscard]] MCDevice *GetDevice() const {
        return m_device;
    }

    //UTILITY FUNCTIONS FOR LIVE & STATIC CAPTURE
    [[nodiscard]] bool BuildSensorArray(int count) const;
    bool InsertSensor(int index, char *name, int parentindex = -1) const;
    bool InsertSensor(int index, char *name, Vector start, Vector end, int parentindex = -1) const;
    void DoneInsertingSensors() const;
    void FreeSensorArray() const;
    [[nodiscard]] bool SetValue(int sensorindex, int channelindex, float value) const;
    [[nodiscard]] bool StoreRotate(int sensorindex, const Matrix34 &matrix) const;
    [[nodiscard]] bool StoreRotateStandard(int sensorindex, const Matrix34 &matrix) const;
    [[nodiscard]] bool StoreTranslateStandard(int sensorindex, const Vector &translate) const;
    static bool StorePose(MCDevice *device, const char *name, float percent);

    //UTILITY FUNCTIONS FOR STATIC CAPTURE
    static Time GetTime();
    static void SetTime(Time time);
    static float GetFrame();
    static void SetFrame(float frame);
    static float GetSystemRate();
    static float GetCaptureRate();

    void Redraw() const;
    static bool EscapeKeyDown();

    //CAPABILITIES
    virtual bool SupportsLiveCaptureSequence() {
        return false;
    }

    virtual bool SupportsLiveCaptureFrame() {
        return false;
    }

    virtual bool SupportsStaticCaptureSequence() {
        return false;
    }

    //IMPLEMENTATION OF LIVE CAPTURE
    virtual bool LiveCaptureInit() {
        return false;
    }

    virtual FrameError LiveCaptureFrame() {
        return FE_FAILED;
    }

    virtual void LiveCaptureClose() {}

    //IMPLEMENTATION OF STATIC CAPTURE
    virtual bool StaticCaptureSequence() {
        return false;
    }
};
