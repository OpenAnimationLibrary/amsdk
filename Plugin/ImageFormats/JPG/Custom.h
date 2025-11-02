// YP  01/10/2005  \Plugin\Image Formats\JPG\Custom.h
#pragma once

#include "ImageIO.h"
#include "resource.h"
#include "StrClass.h"
#include "SDK/HPropert.h"

#include <csetjmp>

#define HAVE_BOOLEAN

extern "C" {
#include "jpeglib.h"
}

struct my_error_mgr {
    jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

typedef my_error_mgr *my_error_ptr;

class CustomImageIO final : public ImageIO {
public:
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
        return "Hash\\JPG";
    }

    bool GetImageIOInfo(ImageIOInfo &iioinfo) override;

    // IO
    bool CanLoadImage(const String &filename) override;
    void GetFilesStartEndFrame(const String &filename, int &start, int &end) override;
    bool SetSaveOptions(CWnd *parent, const String &extension, float fps) override;

    long OpenWriteFrame(String filename, HBitmapNode *bn, HOutputInfo *outputinfo, bool hasaudio) override {
        return 0;
    }

    long WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) override;
    void CloseWriteFrame(bool hasaudio) override {}
    long LoadFrame(HBitmapNode *bn, const String &filename, int frame = -1, UINT flags = 0) override;

    bool IsFileOpen() override {
        return false;
    }

    // CUSTOM IMAGEIO FUNCTIONS
private:
    int m_status;
    int m_width;
    int m_height;
    int m_bytesperpixel;
    int m_colorspace;
    float m_gammacorrection;
    GammaType m_gammapreset;
    bool m_ungammacorrect;

    bool OpenJpegR(const char *filename);
    bool GetJpegRow();
    bool CloseJpegR(bool loadinfoonly = FALSE);
    bool OpenJpegW(const char *filename);
    bool SetJpegRow();
    bool CloseJpegW();
    HBitmapBuffer *ReadJpeg();
    static bool IsJPG(int filenumber);
    bool WriteJpeg(HBitmapNode *bn);
    [[nodiscard]] BYTE GammaCorrect(float value) const;
    static float UnGammaCorrect(UBYTE value);

    // IJG library interface
    jpeg_decompress_struct m_dinfo;
    jpeg_compress_struct m_cinfo;
    my_error_mgr m_jerr;
    FILE *m_infile{nullptr};
    FILE *m_outfile{nullptr};
    JSAMPARRAY m_jpegbuffer;
    int m_row_stride{0};
};
