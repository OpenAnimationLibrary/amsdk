// KB  3/01/2005  \Plugin\Image Formats\BMP\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "IOApp.h"

bool CustomImageIO::GetImageIOInfo(ImageIOInfo &iioinfo) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    iioinfo.m_candomultiframes = false;
    iioinfo.m_canwrite = true;
    iioinfo.m_haswriteoptions = false;
    iioinfo.m_canstorealpha = true;
    iioinfo.m_canstoresound = false;
    iioinfo.m_canstoremultibuffers = false;
    iioinfo.m_openfilter = "Windows bitmap Files (*.bmp, *.dib)|*.bmp;*.dib|BMP |";
    iioinfo.m_savefilter = "Windows bitmap Files (*.bmp)|*.bmp|BMP |";
    iioinfo.m_suffix = "bmp";
    iioinfo.m_localizedname = "BMP sequence";
    iioinfo.m_matchname = "WinBmp";
    iioinfo.m_documentation =
    "The Windows Bitmap format is a 24 bit non compressed file format.  It does not support alpha channels.  The Windows Bitmap format is for still images, so a separate image file is rendered for each frame, and the frame number is appended to the filename.";
    return true;
}
