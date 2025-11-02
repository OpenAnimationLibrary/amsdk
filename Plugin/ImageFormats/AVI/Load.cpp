// NAP  2/25/2005  \Noel120\Plugin\Image Formats\AVI\Load.cpp

#include "StdAfx.h"
#include "MessageR.h"
#include "F_Protos.h"
#include "RGBByte.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
//#include "IOApp.h"
//#include "Files.h"
#include "resource.h"
#include <Vfw.h>
#include <io.h>
#include <fcntl.h>

#define ErrorExit()             goto Error_Exit
#define ALLOC(baz)              (UBYTE *)AllocBitmap((long)(baz) )
#define FREE(baz)               {if (baz){FreeBitmap((void *)(baz) );(baz)=nullptr;}}

static void PrintAVIFileOpenError(const long result, const String &name) {
    String stemp = GetResourceString(IDS_ERRORWITHAVIFILE);
    stemp.Replace("%1", name);
    if (result == AVIERR_BADFORMAT)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_BADFORMAT));
    else if (result == AVIERR_MEMORY)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_MEMORY));
    else if (result == AVIERR_FILEREAD)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_FILEREAD));
    else if (result == AVIERR_FILEOPEN)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_FILEOPEN));
    else if (result == REGDB_E_CLASSNOTREG)
        stemp.Replace("%2", GetResourceString(IDS_REGDB_E_CLASSNOTREG));
    else
        stemp.Replace("%2", GetResourceString(IDS_AVIUNDOCUMENTEDERROR));
    MessageRequest(stemp);
}

static void PrintAVIFileGetStreamError(const long result, const String &name) {
    String stemp = GetResourceString(IDS_ERRORWITHAVIFILE);
    stemp.Replace("%1", name);
    if (result == AVIERR_NODATA)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_NODATA));
    else if (result == AVIERR_MEMORY)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_MEMORYERROR));
    MessageRequest(stemp);
}

static bool LoadAVIInfo(long frame, int *width, int *height, int *bpp, const char *name, long *length, long *fps) {
    AVISTREAMINFO si;
    BITMAPINFO head;
    long lsize;
    PAVIFILE pfile;
    PAVISTREAM pavi;

    AVIFileInit();
    if (frame < 0)
        frame = 0;
    pfile = nullptr;
    long result = AVIFileOpen(&pfile, name, OF_READ, nullptr);
    if (result) {
        PrintAVIFileOpenError(result, name);
        return false;
    }
    result = AVIFileGetStream(pfile, &pavi, streamtypeVIDEO, (long)0);
    if (result) {
        PrintAVIFileGetStreamError(result, name);
        AVIFileRelease(pfile);
        AVIFileExit();
        return false;
    }
    AVIStreamInfo(pavi, &si, sizeof si);
    if (si.dwScale)
        *fps = si.dwRate / si.dwScale;
    else
        *fps = si.dwRate;
    *length = si.dwLength;
    if (frame > *length - 1)
        frame = *length - 1;
    //AVIStreamReadFormat( pavi, (long)frame, nullptr, (long *)&lsize );
    lsize = sizeof(BITMAPINFO); // sometimes lsize returned larger than BITMAPINFO, so it trompted memory
    result = AVIStreamReadFormat(pavi, frame, &head, &lsize);
    *width = head.bmiHeader.biWidth;
    *height = head.bmiHeader.biHeight;
    *bpp = 3; //set it always to this value , handled now in LoadAVIData
    if (head.bmiHeader.biCompression != 0) {
        //compressed format
        ICINFO icinfo{};
        if (ICInfo(ICTYPE_VIDEO, si.fccHandler, &icinfo)) {
            if (HIC hic = ICOpen(icinfo.fccType, icinfo.fccHandler, ICMODE_DECOMPRESS); hic) {
                // Find out the compressor name. 
#ifdef _DEBUG
                ICGetInfo(hic, &icinfo, sizeof(ICINFO));
                OutputDebugStringW(icinfo.szName);
                OutputDebugString(" - ");
                OutputDebugStringW(icinfo.szDescription);
                OutputDebugString("\n");
#endif
                ICClose(hic);
            } else {
                PrintAVIFileOpenError(AVIERR_BADFORMAT, name);
                AVIStreamRelease(pavi);
                AVIFileRelease(pfile);
                AVIFileExit();
                return false;
            }
        } else {
            PrintAVIFileOpenError(AVIERR_BADFORMAT, name);
            AVIStreamRelease(pavi);
            AVIFileRelease(pfile);
            AVIFileExit();
            return false;
        }
    }
    AVIStreamRelease(pavi);
    AVIFileRelease(pfile);
    AVIFileExit();
    return true;
}

static bool LoadAVIData(UINT frame, const char *name, char *databuffer, const int dwWidth, const int dwHeight) {
    AVISTREAMINFO si;
    PAVIFILE pfile;
    PAVISTREAM pavi;
    PGETFRAME pframe;

    char *buffer = databuffer;
    AVIFileInit();
    pfile = nullptr;
    long result = AVIFileOpen(&pfile, name, OF_READ, nullptr);
    if (result) {
        PrintAVIFileOpenError(result, name);
        AVIFileExit();
        return false;
    }
    result = AVIFileGetStream(pfile, &pavi, streamtypeVIDEO, (long)0);
    if (result) {
        PrintAVIFileOpenError(result, name);
        AVIFileRelease(pfile);
        AVIFileExit();
        return false;
    }
    AVIStreamInfo(pavi, &si, sizeof si);
    if (const DWORD maxframe = si.dwLength; frame > maxframe - 1)
        frame = maxframe - 1;
    BITMAPINFOHEADER bih = {};
    long lsize = sizeof(BITMAPINFO); // sometimes lsize returned larger than BITMAPINFO, so it trompted memory
    bih.biSize = sizeof(BITMAPINFOHEADER);
    AVIStreamReadFormat(pavi, (long)frame, &bih, &lsize);
    if (bih.biBitCount != 24 || bih.biSize != sizeof(BITMAPINFOHEADER)) {
        //   if (bih.biBitCount != 24 || bih.biCompression != BI_RGB || bih.biSize != sizeof(BITMAPINFOHEADER))  {
        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biBitCount = 24; //24 bit per pixel
        bih.biClrImportant = 0;
        bih.biClrUsed = 0;
        bih.biCompression = BI_RGB;
        bih.biPlanes = 1;
        bih.biXPelsPerMeter = 0;
        bih.biYPelsPerMeter = 0;
        bih.biWidth = dwWidth;
        bih.biHeight = dwHeight;
        bih.biSizeImage = (bih.biWidth * 3 + 3 & 0xFFFC) * bih.biHeight;
        pframe = AVIStreamGetFrameOpen(pavi, &bih);
    } else {
        pframe = AVIStreamGetFrameOpen(pavi, nullptr);
    }
    const BITMAPINFO *bi = (BITMAPINFO *)AVIStreamGetFrame(pframe, frame);
    if (!bi) {
        AVIStreamGetFrameClose(pframe);
        AVIStreamRelease(pavi);
        AVIFileRelease(pfile);
        AVIFileExit();
        return false;
    }

    const char *data = (char *)bi->bmiColors;
    memcpy(buffer, data, bi->bmiHeader.biSizeImage);
    AVIStreamGetFrameClose(pframe);
    AVIStreamRelease(pavi);
    AVIFileRelease(pfile);
    AVIFileExit();
    return true;
}

static bool IsAVI(const int filenumber) {
    char buffer[12];

    _lseek(filenumber, 0L, SEEK_SET);
    if (_read(filenumber, buffer, (size_t)11) != 11)
        return false;
    char *ptrriff = buffer;
    char *ptravi = buffer;
    ptravi += 8;
    ptravi[3] = '\0';
    ptrriff[4] = '\0';
    if (strcmp(ptravi, "AVI") != 0 || strcmp(ptrriff, "RIFF") != 0)
        return false;

    return true;
}

// ****************** Interface

void CustomImageIO::GetFilesStartEndFrame(const String &filename, int &start, int &end) {
    AVISTREAMINFO si;
    PAVIFILE pfile;
    PAVISTREAM pavi;

    start = 0;
    end = 0;

    AVIFileInit();
    pfile = nullptr;
    long result = AVIFileOpen(&pfile, filename.Get(), OF_READ, nullptr);
    if (result) {
        AVIFileExit();
        return;
    }
    result = AVIFileGetStream(pfile, &pavi, streamtypeVIDEO, (long)0);
    if (result) {
        AVIFileRelease(pfile);
        AVIFileExit();
        return;
    }
    AVIStreamInfo(pavi, &si, sizeof si);
    end = si.dwLength;
    AVIStreamRelease(pavi);
    AVIFileRelease(pfile);
    AVIFileExit();
}

bool CustomImageIO::CanLoadImage(const String &filename) {
    int filenumber;

    if (_sopen_s(&filenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return false;
    if (IsAVI(filenumber)) {
        _close(filenumber);
        return true;
    }
    _close(filenumber);
    return false;
}

long CustomImageIO::LoadFrame(HBitmapNode *bn, const String &filename, const int frame, const UINT flags) {
    char *original;
//    UBYTE *row = nullptr, *buffer = nullptr;
    int width, height, bpp;
    long videolength;
    bool messagealreadydisplayed;
    long fps;
    int status = HBitmapNode::LOAD_FAILED; //EXIT_ALLOCFAIL;

    const DWORD result = LoadAVIInfo(frame, &width, &height, &bpp, filename.Get(), &videolength, &fps);
    if (result) {
        bn->SetWidth(width);
        bn->SetHeight(height);
        bn->SetLength(videolength);
        if (flags & HBitmapNode::INITIALIZE)
            bn->SetFps(fps);
        if (!(flags & HBitmapNode::LOADINFOONLY)) {
            const int bufwidth = (int)hash_math::ceil((float)width * (float)bpp / 4.) * 4;
            const DWORD memsize = bufwidth * height;
            original = (char *)ALLOC(memsize);
            if (!LoadAVIData(frame, filename.Get(), original, width, height)) {
                messagealreadydisplayed = true;
                ErrorExit();
            }
            HRGBBuffer *vec3buffer = HBitmapNode::CreateRGBBuffer("RGB", HBitmapBuffer::CT_UBYTE, width, height);
            vec3buffer->AllocateData();
            auto *data = (RGBByte *)vec3buffer->GetData();
            data += width * (height - 1LL); //last row
            const char *colorptr = original;
            const int width2 = width * 2;
            const int padding = bufwidth - width * bpp;
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    *data = RGBByte(*(colorptr + 2), *(colorptr + 1), *colorptr);
                    data++;
                    colorptr += bpp;
                }
                colorptr += padding;
                data -= width2; //prev row
            }
            bn->AddBuffer(vec3buffer);
            FREE(original)
        }
    }
    if (result)
        status = HBitmapNode::LOAD_OK;
    return status;

Error_Exit:
    if (!messagealreadydisplayed) {
        String stemp = GetResourceString(IDS_AVINOTENOUGHMEMORY);
        stemp.Replace("%1", filename);
        MessageRequest(stemp);
    }
    if (original) FREE(original)

    return HBitmapNode::LOAD_FAILED;
}
