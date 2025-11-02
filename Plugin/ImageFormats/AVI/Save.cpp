// KB  12/23/2004  \Ken120\Plugin\Image Formats\AVI\SaveAVI.cpp

#include "StdAfx.h"
#include "MessageR.h"
#include "F_Protos.h"
#include "RGBByte.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "IOApp.h"
#include "Files.h"
#include "resource.h"

#include <memory.h>
#include <fcntl.h>

extern CImageIOApp theApp;

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

static void PrintAVIFileSaveStreamError(const long result, const String &name) {
    String stemp = GetResourceString(IDS_AVIFILECREATESTREAMERROR);
    stemp.Replace("%1", name);
    if (result == AVIERR_CANTCOMPRESS)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_CANTCOMPRESS));
    if (result == AVIERR_BUFFERTOOSMALL)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_BUFFERTOOSMALL));
    if (result == AVIERR_READONLY)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_READONLY));
    if (result == AVIERR_NODATA)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_NODATA));
    if (result == AVIERR_NOCOMPRESSOR)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_NOCOMPRESSOR));
    if (result == AVIERR_COMPRESSOR)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_COMPRESSOR));
    else if (result == AVIERR_MEMORY)
        stemp.Replace("%2", GetResourceString(IDS_AVIERR_MEMORYERROR));
    else
        stemp.Replace("%2", GetResourceString(IDS_AVIUNDOCUMENTEDERROR));
    MessageRequest(stemp);
}

static void PrintAVISTREAMWRITEError(const long result) {
    String stemp = GetResourceString(IDS_AVIWRITESTREAMERROR);
    if (result == AVIERR_BUFFERTOOSMALL)
        stemp.Replace("%1", GetResourceString(IDS_AVIERR_BUFFERTOOSMALL));
    if (result == AVIERR_NODATA)
        stemp.Replace("%1", GetResourceString(IDS_AVIERR_NODATA));
    else if (result == AVIERR_MEMORY)
        stemp.Replace("%1", GetResourceString(IDS_AVIERR_MEMORYERROR));
    else if (result == AVIERR_INTERNAL)
        stemp.Replace("%1", GetResourceString(IDS_AVIERR_INTERNAL));
    else
        stemp.Replace("%1", GetResourceString(IDS_AVIUNDOCUMENTEDERROR));
    MessageRequest(stemp);
}

void CustomImageIO::MakeDIB(const int width, const int height) {
    bmHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmHeader.biWidth = width;
    bmHeader.biHeight = height;
    bmHeader.biPlanes = 1;
    bmHeader.biBitCount = 24;
    bmHeader.biCompression = BI_RGB;
    bmHeader.biSizeImage = 0; // Docs said it was valid to set this to 0.
    bmHeader.biXPelsPerMeter = 0;
    bmHeader.biYPelsPerMeter = 0;
    bmHeader.biClrUsed = 0; // I think. ???
    bmHeader.biClrImportant = 0;
}

void CustomImageIO::CloseWriteFrame(bool audio) {
    [[maybe_unused]] long lError;

    if (pAVIStream) {
        lError = AVIStreamRelease(pAVIStream);
        pAVIStream = nullptr;
    }

    if (pAVIStreamB) {
        lError = AVIStreamRelease(pAVIStreamB);
        pAVIStreamB = nullptr;
    }

    if (pAVIStreamA) {
        lError = AVIStreamRelease(pAVIStreamA);
        pAVIStream = nullptr;
    }

    if (pAVIFile) {
        lError = AVIFileRelease(pAVIFile);
        pAVIFile = nullptr;
    }

    AVIFileExit();

    bMakingAVI = false;
}

//static long OpenAVI(char *filename, BITMAPINFO *biNode, SSHORT fps, bool audio, bool audiostereo, int audiofrequency)
long CustomImageIO::OpenWriteFrame(const String pfilename, HBitmapNode *bn, HOutputInfo *outputinfo, const bool audio) {

    if (const SSHORT wVersion = HIWORD(VideoForWindowsVersion ()); wVersion < 0x010a) {
        MessageRequest(IDS_OLDAVIDRIVER); // Bad for threads
        return 1L;
    }

    const char *filename = pfilename.Get();

    if (!MakeDirPath(filename))
        return 1;
    Remove(filename);

    m_frame = 0;
    const SSHORT width = bn->GetWidth();
    const SSHORT height = bn->GetHeight();
    pmdStuff = &theApp.m_mdStuff;

    AVIopts.fccType = streamtypeVIDEO;
    AVIopts.fccHandler = pmdStuff->dwHandler;
    AVIopts.dwKeyFrameEvery = pmdStuff->dwKey;
    AVIopts.dwQuality = pmdStuff->dwQuality;
    AVIopts.dwBytesPerSecond = pmdStuff->dwBytes;
    AVIopts.lpFormat = nullptr;
    AVIopts.cbFormat = 0;
    AVIopts.lpParms = nullptr;
    AVIopts.cbParms = 0;
    AVIopts.dwInterleaveEvery = 0;
    AVIopts.dwFlags = 0;
    if (pmdStuff->dwKey != 0)
        AVIopts.dwFlags |= AVICOMPRESSF_KEYFRAMES;
    if (pmdStuff->dwBytes != 0)
        AVIopts.dwFlags |= AVICOMPRESSF_DATARATE;

    // Hold the important information
    pAVIFile = nullptr;
    pAVIStream = nullptr;
    pAVIStreamA = nullptr;

    // Initialize the AVI DLL.
    AVIFileInit();

    // Open an AVI file for create.
    long lError = AVIFileOpen(&pAVIFile, filename, OF_WRITE | OF_CREATE, nullptr);
    if (lError) {
        PrintAVIFileOpenError(lError, filename);
        CloseWriteFrame(FALSE);
        return lError;
    }

    // Set up stream config info.
    //Video
    memset(&AVIsvi, 0, sizeof(AVISTREAMINFO));
    AVIsvi.fccType = streamtypeVIDEO;
    AVIsvi.fccHandler = pmdStuff->dwHandler;
    AVIsvi.dwScale = 1;
    AVIsvi.dwRate = outputinfo->GetFPS();
    AVIsvi.dwSuggestedBufferSize = 0;
    SetRect(&AVIsvi.rcFrame, 0, 0, width, height);

    MakeDIB(width, height);

    //Audio
    memset(&waveformat, 0, sizeof(WAVEFORMATEX));
    waveformat.wFormatTag = WAVE_FORMAT_PCM;
    if (outputinfo->GetIsAudioStereo())
        waveformat.nChannels = 2;
    else
        waveformat.nChannels = 1;
    switch (outputinfo->GetAudioFrequency()) {
        case 0:
            waveformat.nSamplesPerSec = 44100;
            break;
        case 1:
            waveformat.nSamplesPerSec = 22050;
            break;
        case 2:
            waveformat.nSamplesPerSec = 11025;
            break;
        case 3:
            waveformat.nSamplesPerSec = 8000;
            break;
    }
    waveformat.nSamplesPerSec = 44100; //hard coded for now
    waveformat.nChannels = 2; //hard coded for now
    waveformat.wBitsPerSample = 16; //hard coded for now
    waveformat.nBlockAlign = waveformat.nChannels * waveformat.wBitsPerSample / 8;
    waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec * waveformat.nBlockAlign;
    waveformat.cbSize = 0;

    memset(&AVIsai, 0, sizeof(AVISTREAMINFO));
    AVIsai.fccType = streamtypeAUDIO;
    AVIsai.fccHandler = waveformat.wFormatTag;
    AVIsai.dwScale = waveformat.nBlockAlign;
    AVIsai.dwRate = waveformat.nSamplesPerSec /**waveformat.nChannels*/ * waveformat.nBlockAlign;
    AVIsai.dwSuggestedBufferSize = 0;
    AVIsai.dwQuality = (DWORD)-1;
    AVIsai.dwSampleSize = waveformat.nBlockAlign;
    SetRect(&AVIsai.rcFrame, 0, 0, 0, 0);

    if (AVIopts.fccHandler != 0) {
        // Create the stream. (video)
        lError = AVIFileCreateStream(pAVIFile, &pAVIStreamB, &AVIsvi);
        if (lError) {
            PrintAVIFileSaveStreamError(lError, filename);
            CloseWriteFrame(audio);
            return lError;
        }

        AVIopts.dwFlags |= AVICOMPRESSF_VALID;
        // Create the compressed stream. (video)
        lError = AVIMakeCompressedStream(&pAVIStream, pAVIStreamB, &AVIopts, nullptr);
        if (lError) {
            PrintAVIFileSaveStreamError(lError, filename);
            CloseWriteFrame(audio);
            return lError;
        }

    } else {
        OutputDebugString("No compression handler specified.  Creating uncompressed.\n");
        // Create the stream. (video)
        lError = AVIFileCreateStream(pAVIFile, &pAVIStream, &AVIsvi);
        if (lError) {
            String stemp = GetResourceString(IDS_AVIFILECREATESTREAMERROR);
            stemp.Replace("%1", lError);
            MessageRequest(stemp);
            CloseWriteFrame(audio);
            return lError;
        }
    }
    // Set the stream format. (video)  
    lError = AVIStreamSetFormat(pAVIStream, 0, &bmHeader, sizeof(BITMAPINFOHEADER));
    if (lError) {
        String stemp = GetResourceString(IDS_AVISTREAMSETFORMATERROR);
        stemp.Replace("%1", lError);
        MessageRequest(stemp);
        CloseWriteFrame(audio);
        return lError;
    }

    // Create the stream. (audio) //handle only uncomppressed for now
    if (audio) {
        lError = AVIFileCreateStream(pAVIFile, &pAVIStreamA, &AVIsai);
        audioindex = 0;
        if (lError) {
            PrintAVIFileSaveStreamError(lError, filename);
            CloseWriteFrame(audio);
            return lError;
        }
    }

    // Set the stream format. (audio)  
    if (audio) {
        lError = AVIStreamSetFormat(pAVIStreamA, 0, &waveformat, sizeof(WAVEFORMATEX));
        if (lError) {
            String stemp = GetResourceString(IDS_AVISTREAMSETFORMATERROR);
            stemp.Replace("%1", lError);
            MessageRequest(stemp);
            CloseWriteFrame(audio);
            return lError;
        }
    }

    bMakingAVI = true;
    return 0;
}

long CustomImageIO::WriteOneFrame(HBitmapNode *bn, const int frame, int currentframe, const int step, const int fps, short *wavedata, const bool audio) {

    HBitmapBuffer *bufferhead = bn->GetBufferHead();
    //COMEBACK could create a (BITMAPINFO *)  on OpenWriteFrame() and pass it to CreateBITMAPINFO(biNode), and free it on CloseWriteFrame()
    const BITMAPINFO *biNode = bufferhead->CreateBITMAPINFO(); // expose this function

    auto *lpB = (SBYTE *)biNode->bmiColors;
    const DWORD dwSizeOfBytes = biNode->bmiHeader.biSizeImage;

    long lError = AVIStreamWrite(pAVIStream, frame - 1, 1, lpB, dwSizeOfBytes, 0L, nullptr, nullptr);

    if (lError) {
        PrintAVISTREAMWRITEError(lError);
        CloseWrite(audio);
        delete biNode;
        return lError;
    }

    if (audio) {
        const float stepsec = (float)step / fps;
        const int numsamples = (int)(stepsec * waveformat.nSamplesPerSec);
        lError = AVIStreamWrite(pAVIStreamA, audioindex, numsamples, wavedata, numsamples * waveformat.nBlockAlign, 0L, nullptr, nullptr);
        audioindex += numsamples;
    }

    if (lError) {
        char buf[255];
        sprintf_s(buf, 255, "AVIAudioStreamWrite error %ld.", lError);
        MessageBox(nullptr, buf, "VFW Error", MB_OK | MB_ICONSTOP);
        CloseWrite(audio);
        delete biNode;
        return lError;
    }
    delete biNode;
    return 0L;
}

//bool WriteAVIFrame(int currentframe, int startframe, int endframe, int step,
// int fps, const String &filename, BITMAPINFO *biNode, short *wavedata, bool audio, bool audiostereo, int audiofrequency)
long CustomImageIO::WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, const bool hasaudio) {

    if (filename.GetSuffixOnly() != "avi")
        return HBitmapNode::WRITE_NORESULT;

    /*remove- hack now handled on masters side
       if (time == starttime) {
          frame = 0;
          error = OpenWriteFrame(filename, bn, fps, hasaudio, isaudiostereo, audiofrequency);
          if (error)
             return HBitmapNode::WRITE_ERROR;
       }
    */
    const long error = WriteOneFrame(bn, ++m_frame, outputinfo->GetTime(), outputinfo->GetStep(), outputinfo->GetFPS(), wavedata, hasaudio);
    if (error) {
        CloseWrite(hasaudio);
        return HBitmapNode::WRITE_ERROR;
    }
    return HBitmapNode::WRITE_OK | HBitmapNode::WRITE_NEEDCLOSE;
}

bool CustomImageIO::IsFileOpen() {
    return bMakingAVI;
}

bool CustomImageIO::SetSaveOptions(CWnd *parent, const String &extension, float fps) {
    static COMPVARS cv;
    static COMPVARS FAR *cvp;

    pmdStuff = &theApp.m_mdStuff;
    const HWND hwnd = parent->GetSafeHwnd();

    cvp = &cv;
    memset(cvp, 0, sizeof(COMPVARS));
    cv.cbSize = sizeof(COMPVARS);
    cv.fccHandler = pmdStuff->dwHandler;
    cv.lKey = pmdStuff->dwKey;
    cv.lQ = pmdStuff->dwQuality;
    cv.lDataRate = pmdStuff->dwBytes;
    cv.dwFlags = ICMF_COMPVARS_VALID;
    if (cv.fccHandler == 0)
        cv.fccHandler = mmioFOURCC('D', 'I', 'B', ' ');

    BITMAPINFOHEADER head = {};
    head.biSize = sizeof(BITMAPINFOHEADER);
    head.biWidth = 20;
    head.biHeight = 20;
    head.biPlanes = 1;
    head.biBitCount = 24;
    head.biCompression = BI_RGB;

    ICCompressorChoose(hwnd,
                       ICMF_CHOOSE_KEYFRAME | ICMF_CHOOSE_DATARATE,
                       //             ICMF_CHOOSE_KEYFRAME | ICMF_CHOOSE_DATARATE | ICMF_CHOOSE_ALLCOMPRESSORS,
                       //             ICMF_CHOOSE_KEYFRAME | ICMF_CHOOSE_DATARATE | ICMF_CHOOSE_PREVIEW | ICMF_CHOOSE_ALLCOMPRESSORS,
                       &head,
                       nullptr,
                       cvp,
                       (LPSTR)"Compression Options");

    if (cv.hic) {
        // Find out the compressor name. 
#ifdef _DEBUG
        ICINFO icinfo{};
        ICGetInfo(cv.hic, &icinfo, sizeof(ICINFO));
        OutputDebugStringW(icinfo.szName);
        OutputDebugString(" - ");
        OutputDebugStringW(icinfo.szDescription);
        OutputDebugString("\n");
#endif
        ICClose(cv.hic);
    }

    pmdStuff->dwHandler = cv.fccHandler;
    pmdStuff->dwKey = cv.lKey;
    pmdStuff->dwQuality = cv.lQ;
    pmdStuff->dwBytes = cv.lDataRate;
    pmdStuff->dwFlags = cv.dwFlags;
    return true;
}
