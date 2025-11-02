// MH  6/30/2005  \Mart120\Plugin\Post\FrameBurn\Custom.h
#pragma once

#include "PostPlug.h"
#include "resource.h"
#include "SDK/HBitmap.h"
//#include "ColorBtn.h"
#include "SDK/HPropert.h"

class CustomPostPlugin final : public PostPlugin {
public:
    HPercentProperty *m_fontscale{nullptr};
    HPercentProperty *m_opacity{nullptr};
    HBoolProperty *m_displayname{nullptr};
    HBoolProperty *m_displayshadow{nullptr};

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
        return "Hash\\FrameBurn";
    }

    // PROCESSING
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time) override;
    bool Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output) override;
    int GetNumInputs() override;
    Styles GetAllowedInputBufferStyles() override;

    // CUSTOM POST FUNCTIONS
    BOOL BurnText(HRGBAFloatBuffer *inbuffer, const String &text, BOOL leftside) const;
};
