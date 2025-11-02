// Yves  04/01/2005  \Plugin\Image Formats\PNG\Custom.h
#pragma once

#include "ImageIO.h"
#include "resource.h"
#include "StrClass.h"
#include "Vector2.h"
#include "SDK/HPropert.h"
#include "png.h"

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
        return "Hash\\PNG";
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
    int m_width{0};
    int m_height{0};
    int m_bitdepth{0};
    int m_colortype{0};
    int m_nbpasses{0};
    int m_rowbytes{0};
    int m_channels{0};
    int m_bytesperpixel{0};
    RGBFloat m_bkgcolor{0.F};
    bool m_hasbackground{false};
    png_color_16 *m_background{nullptr};
    GammaType m_ingammapreset{GAMMA_NONE};
    float m_ingamma{0.F};
    GammaType m_outgammapreset{GAMMA_NONE};
    float m_outgamma{0.F};
    int m_interlace{0};
    int m_srgbintent{0};
    int m_flags{0};

    // IJG library interface
    png_structp m_png_ptr{};
    png_infop m_info_ptr{};
    png_text m_text_ptr[3]{};
    FILE *m_infile{nullptr};
    FILE *m_outfile{nullptr};

    bool OpenPng(const char *filename);
    HBitmapNode::LoadStatus ClosePng(bool loadinfoonly = false);
    [[nodiscard]] float UnGammaCorrect(USHORT value) const;
    [[nodiscard]] float UnGammaCorrect(UBYTE value) const;
    HBitmapNode::LoadStatus NReadPng(HBitmapNode *bn) const;
    HBitmapNode::LoadStatus NReadPng16(HBitmapNode *bn) const;
    HBitmapNode::LoadStatus NReadPngGammaCorrect(HBitmapNode *bn) const;
    static bool IsPNG(FILE *file);

    bool OpenPngW(const char *filename, HOutputInfo *outputinfo);
    HBitmapNode::WriteStatus ClosePngW();
    HBitmapNode::WriteStatus WritePng(HBitmapNode *bn) const;

    [[nodiscard]] UBYTE GammaCorrectB(float value) const;
    [[nodiscard]] USHORT GammaCorrectW(float value) const;
};
