// YP  19/01/2005  \Plugin\Image Formats\BMP\Custom.h
#pragma once

#include "ImageIO.h"
#include "resource.h"
#include "StrClass.h"
#include "Vector2.h"
#include "SDK/HPropert.h"

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
        return "Hash\\BMP";
    }

    bool GetImageIOInfo(ImageIOInfo &iioinfo) override;

    // IO
    bool CanLoadImage(const String &filename) override;
    void GetFilesStartEndFrame(const String &filename, int &start, int &end) override;

    bool SetSaveOptions(CWnd *parent, const String &extension, float fps) override {
        return false;
    }

    long OpenWriteFrame(String filename, HBitmapNode *bn, HOutputInfo *outputinfo, bool hasaudio) override {
        return 0;
    }

    long WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) override;
    void CloseWriteFrame(bool audio) override {}
    long LoadFrame(HBitmapNode *bn, const String &filename, int frame = -1, UINT flags = 0) override;

    // CUSTOM IMAGEIO FUNCTIONS
private:
    int m_filenumber{0};
    String m_filename;
    UBYTE *m_data{nullptr}, *m_buf{nullptr}, *m_row{nullptr}, m_bytesperpixel{0};
    int m_width{0}, m_height{0}, m_filled{0}, m_flags{0}, m_palentries{0};
    BITMAPINFO m_bi{};
    BITMAPFILEHEADER m_header{};
    RGBQUAD m_palette[256]{};
    BOOL m_status{FALSE};
    int m_depth{0};
    int m_ncolors{0};
    int m_nplanes{0};
    int m_widthbytes{0};
    int m_pad{0};
    int m_size{0};
    float m_gamma{0.F};
    bool m_isalpha{false};

    UBYTE ReadBufferByte();
    bool GetBMPRow();
    bool ReadBMP(HBitmapNode *bn, int width, int height);
    static bool IsBMP(int filenumber);
    bool BMPOpen(const String &name);
    bool BMPWriteBitmap(HBitmapNode *bn) const;
    void BMPClose() const;
};
