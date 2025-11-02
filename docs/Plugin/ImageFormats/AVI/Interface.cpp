// KB  1/17/2005  \Ken120\Plugin\Image Formats\AVI\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "IOApp.h"

bool CustomImageIO::GetImageIOInfo(ImageIOInfo &iioinfo) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    iioinfo.m_candomultiframes = true;
    iioinfo.m_canwrite = true;
    iioinfo.m_haswriteoptions = true;
    iioinfo.m_canstorealpha = false;
    iioinfo.m_closewrite = true;
    iioinfo.m_canstoresound = true;
    iioinfo.m_canstoremultibuffers = false;
    iioinfo.m_openfilter = "AVI Files (*.avi)|*.avi|****|";
    iioinfo.m_savefilter = "AVI Files (*.avi)|*.avi|****|";
    iioinfo.m_suffix = "avi";
    iioinfo.m_localizedname = "AVI Movie";
    iioinfo.m_matchname = "AVI";
    iioinfo.m_documentation = "The AVI format is used for Video for Windows.  Only 24-bit depth is supported.";
    return true;
}
