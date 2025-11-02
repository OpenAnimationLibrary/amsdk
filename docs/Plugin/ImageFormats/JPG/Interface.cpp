// KB  3/01/2005  \Plugin\Image Formats\JPG\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "F_Protos.h"
#include "IOApp.h"
#include "JPEGCompression.h"

extern CImageIOApp theApp;

bool CustomImageIO::GetImageIOInfo(ImageIOInfo &iioinfo) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    iioinfo.m_candomultiframes = false;
    iioinfo.m_canwrite = true;
    iioinfo.m_haswriteoptions = true;
    iioinfo.m_canstorealpha = false;
    iioinfo.m_closewrite = false;
    iioinfo.m_canstoresound = false;
    iioinfo.m_canstoremultibuffers = false;
    iioinfo.m_openfilter = "Jpeg Files (*.jpg;*.jpeg)|*.jpg;*.jpeg|JPEG|";
    iioinfo.m_savefilter = "Jpeg Files (*.jpg)|*.jpg|JPEG|";
    iioinfo.m_suffix = "jpg";
    iioinfo.m_localizedname = "Jpeg sequence";
    iioinfo.m_matchname = "Jpeg";
    iioinfo.m_documentation =
    "The Jpeg format is a 24 bit lossy compressed file format meaning that image information is permanently destroyed by the compression operation. So it should only be used for stills expressly designed for posting on the Internet. It does not support alpha channels. The Jpeg format is for still images, so a separate image file is rendered for each frame, and the frame number is appended to the filename.";
    return true;
}

bool CustomImageIO::SetSaveOptions(CWnd *parent, const String &extension, float fps) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    JPEGCompression options(parent);
    options.m_compression = theApp.m_compression;
    options.m_optimal = theApp.m_optimal;
    const INT_PTR retval = options.DoModal();
    if (retval == IDOK) {
        theApp.m_compression = options.m_compression;
        theApp.m_optimal = options.m_optimal;
        SetRegistryString("JPEG", "Compression", theApp.m_compression);
        SetRegistryBOOL("JPEG", "OptimizeTable", theApp.m_optimal);
    }
    return true;
}
