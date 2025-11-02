// Yves  01/14/2005  \Plugin\Image Formats\PNG\IOApp.h
#pragma once

#include "SDK/Misc.h"

class CImageIOApp final : public CPluginApp {
public:
    int m_compression{0};
    bool m_interlaced{false};
    bool m_8bit{false};

    BOOL InitInstance() override;
    int ExitInstance() override;
};
