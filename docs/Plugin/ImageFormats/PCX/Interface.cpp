// NAP  2/28/2005  \Master120\Plugin\Image Formats\PCX\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
//#include "IOApp.h"

bool CustomImageIO::GetImageIOInfo(ImageIOInfo &iioinfo) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    iioinfo.m_candomultiframes = false;
    iioinfo.m_canwrite = false;
    iioinfo.m_haswriteoptions = false;
    iioinfo.m_canstorealpha = false;
    iioinfo.m_canstoresound = false;
    iioinfo.m_canstoremultibuffers = false;
    iioinfo.m_openfilter = "PCX Files (*.pcx)|*.pcx|PCX |";
    iioinfo.m_savefilter = "";
    iioinfo.m_suffix = "pcx";
    iioinfo.m_localizedname = "PCX sequence";
    iioinfo.m_matchname = "PCX";
    iioinfo.m_documentation =
    "The PCX format does not support alpha channels.  The PCX format is for still images, so a separate image file is rendered for each frame. The frame number is appended to the filename.";
    return true;
}
