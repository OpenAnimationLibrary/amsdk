// KB  01/19/2005  \Plugin\Image Formats\TGA\IOApp.h
#pragma once

//#include "SDK/HPropert.h"
#include "SDK/Misc.h"

class CImageIOApp final : public CPluginApp {
public:
    bool m_compression{};

    BOOL InitInstance() override;
    int ExitInstance() override;
};
