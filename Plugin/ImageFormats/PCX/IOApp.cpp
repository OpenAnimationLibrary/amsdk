// Yves  10/04/2004  \Yves115\Plugin\Image Formats\BMP\IOApp.cpp

#include "StdAfx.h"
#include "IOApp.h"
//#include "resource.h"

CImageIOApp theApp;

BOOL CImageIOApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");
    return CPluginApp::InitInstance();
}

int CImageIOApp::ExitInstance() {
    // Delete Infos Here

    return CPluginApp::ExitInstance();
}
