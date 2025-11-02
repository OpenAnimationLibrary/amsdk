// Dan  11/26/2001  \Dan90\Plugin\MotionCapture\BioVision BVH\Capture.h

#pragma once
#include "MCDriver.h"
#include "resource.h"
#include "SDK/HPropert.h"

class Driver final : public MCDriver {
public:
#define CENTIMETERSPERINCH 2.54f

    explicit Driver(HTreeObject *Treeobject);
    ~Driver() override = default;

    Driver(const Driver&) = delete;
    Driver &operator= (const Driver&) = delete; 
    Driver(Driver &&) = delete; 
    Driver &operator=(Driver &&) = delete; 

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_DRIVER;
    }

    const char *GetClassName() override {
        return "Hash\\BioVision BVH File";
    }

    UINT GetNameID() noexcept override {
        return IDS_DRIVERNAME;
    }

    HProperty *GetPropertyAt(int i) override;

    // IMPLEMENTATION
    bool SupportsStaticCaptureSequence() override {
        return true;
    }

    bool StaticCaptureSequence() override;
};
