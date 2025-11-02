// NAP  1/12/2005  \Noel120\Plugin\Post\Multiply\Custom.h
#pragma once

#include "PostPlug.h"
#include "resource.h"
#include "ColorBtn.h"
#include "SDK/HPropert.h"

class CustomPostPlugin final : public PostPlugin {
public:
    HPercentProperty *m_percent;

    // CONSTRUCTION/DESTRUCTION
    explicit CustomPostPlugin(HTreeObject *treeobject);
    ~CustomPostPlugin() override;
    CustomPostPlugin(const CustomPostPlugin&) = delete;
    CustomPostPlugin &operator= (const CustomPostPlugin&) = delete; 
    CustomPostPlugin(CustomPostPlugin &&) = delete; 
    CustomPostPlugin &operator=(CustomPostPlugin &&) = delete; 

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_POST;
    }

    UINT GetNameID() noexcept override {
        return IDS_POSTNAME;
    }

    const char *GetClassName() override {
        return "Hash\\Divide";
    }

    // PROCESSING
    HProperty *GetPropertyAt(int i) override;
    bool Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output) override;
    int GetNumInputs() override;
    Styles GetAllowedInputBufferStyles() override;

    // CUSTOM POST FUNCTIONS
};
