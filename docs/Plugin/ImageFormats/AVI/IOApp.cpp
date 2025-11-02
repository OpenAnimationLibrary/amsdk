// KB  12/9/2004  \Plugin\Image Formats\TGA\IOApp.cpp

#include "StdAfx.h"
#include "F_Protos.h"
#include "Custom.h"
#include "IOApp.h"
//#include "resource.h"

CImageIOApp theApp;

BOOL CImageIOApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    // New Infos here

    m_mdStuff.dwHandler = 0;
    m_mdStuff.dwKey = 15;
    m_mdStuff.dwQuality = 7500;
    m_mdStuff.dwBytes = 0;
    m_mdStuff.dwFlags = 0;

    LoadAVIOptions();
    return CPluginApp::InitInstance();
}

int CImageIOApp::ExitInstance() {
    // Delete Infos Here
    SaveAVIOptions();
    return CPluginApp::ExitInstance();
}

void CImageIOApp::LoadAVIOptions() {
    //   m_mdStuff.dwHandler = GetRegistryValue( "AVI", "Handler", 1684633187);//Cinipak by radius
    m_mdStuff.dwHandler = GetRegistryValue("AVI", "Handler", (int)mmioFOURCC('D', 'I', 'B', ' ')); //Uncompressed
    m_mdStuff.dwKey = GetRegistryValue("AVI", "Key", 15);
    m_mdStuff.dwQuality = GetRegistryValue("AVI", "Quality", 7500);
    m_mdStuff.dwBytes = GetRegistryValue("AVI", "Bytes", 0);
    m_mdStuff.dwFlags = GetRegistryValue("AVI", "Flags", 0);
}

void CImageIOApp::SaveAVIOptions() const {
    SetRegistryValue("AVI", "Handler", (int)m_mdStuff.dwHandler);
    SetRegistryValue("AVI", "Key", (int)m_mdStuff.dwKey);
    SetRegistryValue("AVI", "Quality", (int)m_mdStuff.dwQuality);
    SetRegistryValue("AVI", "Bytes", (int)m_mdStuff.dwBytes);
    SetRegistryValue("AVI", "Flags", (int)m_mdStuff.dwFlags);
}
