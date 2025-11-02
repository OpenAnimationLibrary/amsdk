// Yves  10/05/2004  \Yves115\Plugin\Image Formats\JPG\IOApp.cpp

#include "StdAfx.h"
#include "IOApp.h"
#include "resource.h"
#include "F_Protos.h"

CImageIOApp theApp;

BOOL CImageIOApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    m_compression = GetRegistryValue("JPEG", "Compression", 75); // 75% quality is the standard default for Jpeg
    m_optimal = GetRegistryBOOL("JPEG", "OptimizeTable", FALSE);
    return CPluginApp::InitInstance();
}

int CImageIOApp::ExitInstance() {
    // Delete Infos Here

    return CPluginApp::ExitInstance();
}
