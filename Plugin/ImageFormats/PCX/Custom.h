// NAP  2/28/2005  \Master120\Plugin\Image Formats\PCX\Custom.h
#pragma once

#include "ImageIO.h"
#include "resource.h"

#define ALLOC(baz) (UBYTE *)AllocBitmap((int)(baz) )
#define FREE(baz) {if (baz){FreeBitmap((void *)(baz) );(baz)=nullptr;}}

typedef struct {
    SBYTE manufacturer, version, encoding, bitsperpixel;
    SSHORT xmin, ymin, xmax, ymax, hres, vres;
    SBYTE palette[48], reserved, colorplanes;
    SSHORT bytesperline, palettetype;
    SBYTE filler[58];
} PCXHEAD;

#define PCXHEADER               128L
#define BUFFERSIZE              512
#define PALETTEBYTES            768L

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
        return "Hash\\PCX";
    }

    bool GetImageIOInfo(ImageIOInfo &iioinfo) override;

    // IO
    bool CanLoadImage(const String &filename) override;
    void GetFilesStartEndFrame(const String &filename, int &start, int &end) override;

    bool SetSaveOptions(CWnd *parent, const String &extension, float fps) override {
        return false;
    }

    //virtual int  OpenWriteFrame( String filename, HBitmapNode *bn, HOutputInfo *outputinfo, bool hasaudio ) { return 0; }
    //virtual int  WriteFrame( HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio);
    //virtual void CloseWriteFrame( bool hasaudio) {}
    long LoadFrame(HBitmapNode *bn, const String &filename, int frame = -1, UINT flags = 0) override;

    // CUSTOM IMAGEIO FUNCTIONS
private:
    int m_filenumber;
    UBYTE *m_data, *m_buf, *m_row;
    UBYTE m_bytesperpixel, m_palette[PALETTEBYTES];
    int m_width, m_height, m_depth, m_width2, m_width3;
    int m_bytes3, m_bytes;
    int m_filled, m_flags;
    int m_palentries;
    int m_status;
    PCXHEAD m_header;

    UBYTE ReadBufferByte();
    bool ReadPCXLine(UBYTE *row);
    bool Read16PCXLine(UBYTE *planeptr);
    bool Read24PCXLine(UBYTE *row, int y, bool encoding);
    HBitmapBuffer *UnpackPCXFile(HBitmapNode *bn);
    RGBByte GetPixel(const UBYTE *ptr, int x) const;
    HBitmapBuffer *Unpack16PCXFile(HBitmapNode *bn);
    HBitmapBuffer *Unpack24PCXFile(HBitmapNode *bn, bool encoding);
    static bool IsPCX(int filenumber);
};
