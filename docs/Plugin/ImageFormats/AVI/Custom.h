// WEP  6/10/2005  \svn12.0\Plugin\Image Formats\AVI\Custom.h
#pragma once

#include "ImageIO.h"
#include "resource.h"
#include "StrClass.h"
#include "Vector2.h"
#include "SDK/HPropert.h"
#include <mmsystem.h>
#include <Digitalv.h>
#include <Vfw.h>

typedef struct tagMYDATA {
    DWORD dwHandler{0};
    DWORD dwKey{0};
    DWORD dwQuality{0};
    DWORD dwBytes{0};
    DWORD dwFlags{0};
} MYDATA;

class CustomImageIO final : public ImageIO {
public:
    AVICOMPRESSOPTIONS AVIopts, AVIaopts;
    AVISTREAMINFO AVIsvi, AVIsai;
    BITMAPINFOHEADER bmHeader;
    MYDATA FAR *pmdStuff;
    PAVIFILE pAVIFile;
    PAVISTREAM pAVIStream, pAVIStreamB, pAVIStreamA, pAVIStreamAB;
    WAVEFORMATEX waveformat;
    DWORD audioindex{0};
    UINT m_frame{0};
    bool bMakingAVI{false};

    // CONSTRUCTION/DESTRUCTION
    explicit CustomImageIO(HTreeObject *treeobject);
    ~CustomImageIO() override;

    CustomImageIO(const CustomImageIO &) = delete;
    CustomImageIO &operator=(const CustomImageIO &) = delete;
    CustomImageIO(CustomImageIO &&) = delete;
    CustomImageIO &operator=(CustomImageIO &&) = delete;

    // INTERFACE
    UINT GetIconID() noexcept override {
        return IDI_IMAGEIO;
    }

    UINT GetNameID() noexcept override {
        return IDS_IMAGEIONAME;
    }

    const char *GetClassName() override {
        return "Hash\\AVI";
    }

    bool GetImageIOInfo(ImageIOInfo &iioinfo) override;

    // IO
    bool CanLoadImage(const String &filename) override;
    void GetFilesStartEndFrame(const String &filename, int &start, int &end) override;
    bool SetSaveOptions(CWnd *parent, const String &extension, float fps) override;
    long OpenWriteFrame(String pfilename, HBitmapNode *bn, HOutputInfo *outputinfo, bool audio) override;
    long WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) override;
    void CloseWriteFrame(bool audio) override;
    long LoadFrame(HBitmapNode *bn, const String &filename, int frame = -1, UINT flags = 0) override;
    bool IsFileOpen() override;

    // CUSTOM IMAGEIO FUNCTIONS
    void MakeDIB(int width, int height);
    long WriteOneFrame(HBitmapNode *bn, int frame, int currentframe, int step, int fps, short *wavedata, bool audio);

};
