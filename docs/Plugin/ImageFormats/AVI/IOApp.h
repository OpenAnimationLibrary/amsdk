// KB 12/21/2004  \Ken120\Plugin\Image Formats\AVI\IOApp.h
#pragma once

#include "SDK/HPropert.h"
#include "SDK/Misc.h"

class CImageIOApp final : public CPluginApp {
public:
    MYDATA m_mdStuff;

    void LoadAVIOptions();
    void SaveAVIOptions() const;

    BOOL InitInstance() override;
    int ExitInstance() override;
};
