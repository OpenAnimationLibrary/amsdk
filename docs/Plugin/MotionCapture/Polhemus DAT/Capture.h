// Dan  11/26/2001  \Dan90\Plugin\MotionCapture\Polhemus DAT\Capture.h

#pragma once
#include "MCDriver.h"
#include "resource.h"

class HBoolProperty;
class HTypeProperty;
class HFilenameProperty;

class Driver final : public MCDriver {
public:
    //HBoolProperty         *m_isbinary;
    HTypeProperty *m_scalefactortype;
    HFilenameProperty *m_filename;
    float m_scalefactor{0.F};
    BOOL m_isbinary{FALSE};

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
        return "Hash\\Polhemus DAT File";
    }

    UINT GetNameID() noexcept override {
        return IDS_DRIVERNAME;
    }

    HProperty *GetPropertyAt(int i) override;

    // IMPLEMENTATION
    bool SupportsStaticCaptureSequence() override {
        return TRUE;
    }

    bool StaticCaptureSequence() override;

    static int GetSensorCount(FILE *file, int &recordsize);
    BOOL ReadOneFrame(FILE *file, float frame);
    BOOL SkipOneFrame(FILE *file) const;

};
