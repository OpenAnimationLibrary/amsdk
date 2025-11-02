// Yves  10/04/2004  \Yves115\Plugin\Image Formats\BMP\IOApp.cpp

#include "StdAfx.h"
#include "IOApp.h"
//#include "resource.h"
#include "F_Protos.h"

CImageIOApp theApp;

BOOL CImageIOApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    m_interlaced = GetRegistryValue("PNG", "interlacing", 0) == 1; // Non interlaced by default
    m_8bit = GetRegistryValue("PNG", "EightBit", 1) == 1; // 8 bit planes  by default
    m_compression = GetRegistryValue("PNG", "Compression", 0);
    return CPluginApp::InitInstance();
}

int CImageIOApp::ExitInstance() {
    // Delete Infos Here

    return CPluginApp::ExitInstance();
}
