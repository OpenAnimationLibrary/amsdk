// MH  6/30/2005  \Mart120\Plugin\Post\Bloom\Custom.h
#pragma once

#include "PostPlug.h"
#include "resource.h"
#include "ColorBtn.h"
#include "SDK/HPropert.h"

class CustomPostPlugin final : public PostPlugin {
public:
    HTypeCategoryProperty *m_style;
    HPercentProperty *m_strength;
    HPercentProperty *m_threshold;
    HIntProperty *m_radius;

    BOOL m_isstylechanging;

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
        return "Hash\\Bloom";
    }

    // PROCESSING
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time = Time()) override;
    bool Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output) override;
    int GetNumInputs() override;
    Styles GetAllowedInputBufferStyles() override;
    //virtual Info              GetInfo() {return USES_ZBUFFER;} used to set bloomed z over no z to bloomed pixel's z, but for now posts happen after depth buffer is built

    // CUSTOM POST FUNCTIONS
};
