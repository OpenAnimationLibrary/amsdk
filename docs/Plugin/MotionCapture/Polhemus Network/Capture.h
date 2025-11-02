// WEP  4/12/2005  \will120\Plugin\MotionCapture\Polhemus Network\Capture.h

#pragma once
#include "MCDriver.h"
#include "resource.h"

class HBoolProperty;
class HStringProperty;
class HIntProperty;
class HTypeProperty;

class Driver final : public MCDriver {
public:
    HBoolProperty *m_isbinary;
    HStringProperty *m_ipaddress;
    HIntProperty *m_port;
    HIntProperty *m_timeout;
    HTypeProperty *m_scalefactortype;
    float m_scalefactor{0.F};
    SOCKET m_insock{0};
    SOCKET m_outsock{0};

    enum { SENSORSPERCARD = 2 };

#define CENTIMETERSPERINCH 2.54f

    explicit Driver(HTreeObject *Treeobject);
    ~Driver() override;

    Driver(const Driver&) = delete;
    Driver &operator= (const Driver&) = delete; 
    Driver(Driver &&) = delete; 
    Driver &operator=(Driver &&) = delete; 
    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_DRIVER;
    }

    const char *GetClassName() override {
        return "Hash\\Polhemus Network";
    }

    UINT GetNameID() noexcept override {
        return IDS_DRIVERNAME;
    }

    HProperty *GetPropertyAt(int i) override;

    // IMPLEMENTATION
    bool SupportsLiveCaptureSequence() override {
        return true;
    }

    bool SupportsLiveCaptureFrame() override {
        return true;
    }

    bool LiveCaptureInit() override;
    FrameError LiveCaptureFrame() override;
    void LiveCaptureClose() override;

    int WriteUltra(const char *text) const;
    BOOL ReadUltra(char *buffer, int limit) const;
    [[nodiscard]] int GetMaxSensorIndex() const;
    [[nodiscard]] BOOL InsertSensors() const;
    [[nodiscard]] BOOL StoreTranslate(int sensornum, float x, float y, float z) const;
//    BOOL StoreQuat(int sensornum, float x, float y, float z, float w);
    BOOL StoreData(int sensornum, const float *f, int count) const;
    static float GetSeconds();
};
