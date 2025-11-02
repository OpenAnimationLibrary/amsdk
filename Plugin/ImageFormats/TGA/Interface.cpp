// KB  12/23/2004  \Ken120\Plugin\Image Formats\TGA\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "F_Protos.h"
#include "IOApp.h"
#include "CompressionDlg.h"

extern CImageIOApp theApp;

bool CustomImageIO::GetImageIOInfo(ImageIOInfo &iioinfo) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    iioinfo.m_candomultiframes = false;
    iioinfo.m_canwrite = true;
    iioinfo.m_haswriteoptions = true;
    iioinfo.m_canstorealpha = true;
    iioinfo.m_closewrite = false;
    iioinfo.m_canstoresound = false;
    iioinfo.m_canstoremultibuffers = false;
    iioinfo.m_openfilter = "Targa Files (*.tga)|*.tga|TPIC|";
    iioinfo.m_savefilter = "Targa Files (*.tga)|*.tga|TPIC|";
    iioinfo.m_suffix = "tga";
    iioinfo.m_localizedname = "Targa sequence";
    iioinfo.m_matchname = "Targa";
    iioinfo.m_documentation =
    "The TrueVision Targa format is a 24 or 32 bit lossless compressed file format.  It can support alpha channels.  The Targa format is for still images, so a separate image file is rendered for each frame, and the frame number is appended to the filename.";
    return true;
}

bool CustomImageIO::SetSaveOptions(CWnd *parent, const String &extension, float fps) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    CCompressionDlg options(parent);
    options.m_compression = theApp.m_compression;
    const INT_PTR retval = options.DoModal();
    if (retval == IDOK) {
        theApp.m_compression = options.m_compression;
        SetRegistryString("TGA", "Compression", theApp.m_compression ? 1 : 0);
    }
    return true;
}
