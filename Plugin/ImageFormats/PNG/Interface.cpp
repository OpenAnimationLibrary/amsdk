// YP  01/10/2005  \Plugin\Image Formats\PNG\Interface.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "F_Protos.h"
#include "IOApp.h"
#include "OptionsDlg.h"

extern CImageIOApp theApp;

// Macintosh file types signatures
// *.tga|TPIC|;
// *.bmp|BMPf|;
// *.pcx|PCX |;
// *.tif|TIFF|;
// *.jpg|JPEG|;
// *.iff|ILBM|;
// *.pic|PICT|;
// *.png|PiNG|;
// *.gif|GIFf|;

bool CustomImageIO::GetImageIOInfo(ImageIOInfo &iioinfo) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    iioinfo.m_candomultiframes = false;
    iioinfo.m_canwrite = true;
    iioinfo.m_haswriteoptions = true; // Not for compression because PNG always compresess. But for other save options.
    iioinfo.m_canstorealpha = true;
    iioinfo.m_closewrite = false;
    iioinfo.m_canstoresound = false;
    iioinfo.m_canstoremultibuffers = false;
    iioinfo.m_openfilter = "Portable Network Graphics Files (*.png)|*.png|PiNG|";
    iioinfo.m_savefilter = "Portable Network Graphics Files (*.png)|*.png|PiNG|";
    iioinfo.m_suffix = "png";
    iioinfo.m_localizedname = "PNG sequence";
    iioinfo.m_matchname = "PNG";
    iioinfo.m_documentation =
        "The Portable Network Graphics (PNG) format is a 24 or 32 bit (at 8 bits per channel) or a 48 or 64 bit (at 16 bits per channel for higher precision colors) lossless compressed file format.  It can support alpha channels.  The PNG format is for still images, so a separate image file is rendered for each frame, and the frame number is appended to the filename.";
    return true;
}

bool CustomImageIO::SetSaveOptions(CWnd *parent, const String &extension, float fps) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
    OptionsDlg options(parent);
    options.m_interlaced = theApp.m_interlaced;
    options.m_8bit = theApp.m_8bit ? 0 : 1;
    options.m_compression = theApp.m_compression;
    const INT_PTR retval = options.DoModal();
    if (retval == IDOK) {
        theApp.m_interlaced = options.m_interlaced;
        theApp.m_8bit = options.m_8bit ? false : true;
        theApp.m_compression = options.m_compression;
        SetRegistryString("PNG", "Interlacing", theApp.m_interlaced ? 1 : 0);
        SetRegistryString("PNG", "EightBit", theApp.m_8bit ? 1 : 0);
        SetRegistryString("PNG", "Compression", theApp.m_compression);
    }
    return true;
}
