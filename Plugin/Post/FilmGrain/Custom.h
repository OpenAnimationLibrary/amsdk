// MH  6/30/2005  \Mart120\Plugin\Post\FilmGrain\Custom.h
#pragma once

#include "resource.h"
#include "PostPlug.h"
#include "SDK/HPropert.h"

class CustomPostPlugin final : public PostPlugin {
public:
    HTypeCategoryProperty *m_style;
    HPercentProperty *m_size;
    HPercentProperty *m_amount;

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
        return "Hash\\FilmGrain";
    }

    // PROCESSING
    HProperty *GetPropertyAt(int i) override;
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time) override;
    bool Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output) override;
    int GetNumInputs() override;
    Styles GetAllowedInputBufferStyles() override;

    // CUSTOM POST FUNCTIONS
};
