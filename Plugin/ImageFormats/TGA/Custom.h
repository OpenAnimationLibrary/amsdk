// NAP  2/25/2005  \Noel120\Plugin\Image Formats\TGA\Custom.h
#pragma once

#include "ImageIO.h"
#include "resource.h"
#include "StrClass.h"
#include "Vector2.h"
#include "SDK/HPropert.h"
#include "TGA.h"

class CustomImageIO final : public ImageIO {
public:
    RGBFloat m_background;
    bool m_hasbackground{false};
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
        return "Hash\\TGA";
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
    void CloseWriteFrame(bool audio) override {}
    long LoadFrame(HBitmapNode *bn, const String &filename, int frame = -1, UINT flags = 0) override;

    bool IsFileOpen() override {
        return false;
    }

private:
    // CUSTOM IMAGEIO FUNCTIONS
    // Load image
    int m_infilenumber{0};
    bool m_readstatus{false};
    UBYTE *m_buffer{nullptr}, *m_data{nullptr}, *m_buf{nullptr}, *m_row{nullptr}, *m_colormap{nullptr};
    UBYTE m_inbytesperpixel{0}, m_mode{0};
    int m_inheight{0}, m_inwidth{0}, m_width2{0}, m_width3{0}, m_sbflags{0}, m_filled{0}, m_colorsize{0};
    TGA_ImageHeader m_header{};
    TGA_ImageFooter m_footer{};
    int m_status{0};
    bool m_ispremultipliedalpha{false};
    float m_embeddedgamma{0.F};

    UBYTE ReadBufferByte();
    bool GetMapEntry(UBYTE *red, UBYTE *grn, UBYTE *blu, UBYTE bytesperpixel);
    bool GetTGARow();
    bool OpenReadTGA(HBitmapNode *bn, const String &filename);
    bool PrepareReadTGA();
    bool ReadTGAGamma(HBitmapNode *bn);
    bool ReadTGA(HBitmapNode *bn);
    static bool IsTGA(int filenumber);
    static bool IsOldTGA(int filenumber);

    // Save Image
    int m_outfilenumber{0};
    int m_outbytesperpixel{0};
    GammaType m_gammapreset{GAMMA_NONE};
    float m_targetgamma{0.F};
    bool m_compress{false};
    int m_outwidth{0}, m_outheight{0}, m_outdepth{0};
    String m_user, m_org;

    [[nodiscard]] bool WriteByte(UBYTE value) const;
    [[nodiscard]] bool WriteShort(SHORT value) const;
    [[nodiscard]] bool WriteLong(long value) const;
    [[nodiscard]] bool WriteFloat(float value) const;
    static SSHORT CountDiffPixels8(const UBYTE *linebuf, SSHORT width, SSHORT x);
    static SSHORT CountDiffPixels(const TGABuf *linebuf, SSHORT width, SSHORT x);
    static SSHORT CountSamePixels8(const UBYTE *linebuf, SSHORT width, SSHORT x);
    static SSHORT CountSamePixels(const TGABuf *linebuf, SSHORT width, SSHORT x);
    static SSHORT RLEncodeRow8(UBYTE *buffer, const UBYTE *linebuf, SSHORT width);
    static SSHORT RLEncodeRow(const TGABuf *linebuf, UBYTE *buffer, SSHORT width);
    static SSHORT RLEncodeAlphaRow(const TGABuf *linebuf, UBYTE *buffer, SSHORT width);
    int TGAOpenWrite(const String &name);
    bool TGACloseWrite(const Vector *background, float aspect, bool premultipliedalpha) const;
    bool TGAWriteLine(const TGABuf *linebuf) const;
};
