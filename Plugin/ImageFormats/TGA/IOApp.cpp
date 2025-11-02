// YP  01/05/2005  \Plugin\Image Formats\TGA\IOApp.cpp

#include "StdAfx.h"
#include "IOApp.h"
#include "F_Protos.h"

CImageIOApp theApp;

BOOL CImageIOApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    m_compression = GetRegistryValue("TGA", "Compression", 1) == 1; // Compress by default
    return CPluginApp::InitInstance();
}

int CImageIOApp::ExitInstance() {
    // Delete Infos Here

    return CPluginApp::ExitInstance();
}
