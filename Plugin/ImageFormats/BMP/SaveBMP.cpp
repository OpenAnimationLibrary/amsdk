// KB  1/21/2005  \Plugin\Image Formats\BMP\Save.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "IOApp.h"
#include "Files.h"

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

#define ErrorExit()           goto Error_Exit
extern CImageIOApp theApp;

bool CustomImageIO::BMPOpen(const String &name) {
    if (_sopen_s(&m_filenumber, name.Get(), _O_RDWR | _O_BINARY | _O_CREAT, _SH_DENYNO, _S_IWRITE) != 0)
        return false;

    int palettesize = 0;
    if (m_depth < 24) {
        m_ncolors = 256;
        palettesize = 256 * sizeof(RGBQUAD);
    } else
        m_ncolors = 0;
    m_nplanes = m_depth / 8;
    m_widthbytes = m_width * m_nplanes;
    if (m_widthbytes % 4)
        m_widthbytes += 4 - m_widthbytes % 4;
    m_size = m_height * m_widthbytes;

    BITMAPINFOHEADER bminfo;
    bminfo.biSize = sizeof(BITMAPINFOHEADER);
    bminfo.biWidth = m_width;
    bminfo.biHeight = m_height;
    bminfo.biPlanes = 1; // This value must always be set to 1 for Win API.
    bminfo.biBitCount = m_depth;
    bminfo.biCompression = BI_RGB;
    bminfo.biSizeImage = m_size;
    bminfo.biXPelsPerMeter = 5162; // 72 DPI
    bminfo.biYPelsPerMeter = 5162;
    bminfo.biClrUsed = m_depth < 24 ? 256 : 0;
    bminfo.biClrImportant = 0;

    BITMAPFILEHEADER bmfhdr;
    bmfhdr.bfType = (WORD)('M' << 8) | 'B'; // "BM"
    bmfhdr.bfSize = m_size + bminfo.biSize + sizeof(BITMAPFILEHEADER);
    bmfhdr.bfReserved1 = 0;
    bmfhdr.bfReserved2 = 0;
    bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + bminfo.biSize + palettesize;

    RGBQUAD palette[256];
    for (int i = 0; i < m_ncolors; ++i) {
        // If 1 plane only then it is a gray scale. We don't gamma correct grayscale.
        palette[i].rgbRed = i;
        palette[i].rgbGreen = i;
        palette[i].rgbBlue = i;
        palette[i].rgbReserved = 0;
    }

    if (_write(m_filenumber, &bmfhdr, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
        ErrorExit();
    if (_write(m_filenumber, &bminfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
        ErrorExit();
    if (palettesize) {
        if (_write(m_filenumber, &palette, palettesize) != palettesize)
            ErrorExit();
    }
    return true;

Error_Exit:
    _close(m_filenumber);
    return false;
}

bool CustomImageIO::BMPWriteBitmap(HBitmapNode *bn) const {
    auto *buffer = (UBYTE *)AllocBitmap(m_widthbytes);
    if (!buffer)
        return false;
    switch (m_bytesperpixel) {
        case 4:
        {
            if (m_isalpha) {
                auto *buf = (RGBQUAD *)buffer;
                RGBAFloat color;
                for (int y = m_height - 1; y >= 0; y--) {
                    for (int x = 0; x < m_width; ++x) {
                        bn->ReadPixel(x, y, color);
                        if (m_gamma != 1.F) {
                            color.SetRed(hash_math::pow(color.Red(), m_gamma));
                            color.SetGreen(hash_math::pow(color.Green(), m_gamma));
                            color.SetBlue(hash_math::pow(color.Blue(), m_gamma));
                        }
                        buf[x].rgbRed = FLOATTOBYTE(color.Red());
                        buf[x].rgbGreen = FLOATTOBYTE(color.Green());
                        buf[x].rgbBlue = FLOATTOBYTE(color.Blue());
                        buf[x].rgbReserved = FLOATTOBYTE(color.Alpha());
                    }
                    if (_write(m_filenumber, buffer, m_widthbytes) != m_widthbytes)
                        ErrorExit();
                }
            } else {
                auto *buf = (RGBTRIPLE *)buffer;
                RGBAFloat color;
                for (int y = m_height - 1; y >= 0; y--) {
                    for (int x = 0; x < m_width; ++x) {
                        bn->ReadPixel(x, y, color);
                        if (m_gamma != 1.F) {
                            color.SetRed(hash_math::pow(color.Red(), m_gamma));
                            color.SetGreen(hash_math::pow(color.Green(), m_gamma));
                            color.SetBlue(hash_math::pow(color.Blue(), m_gamma));
                        }
                        buf[x].rgbtRed = FLOATTOBYTE(color.Red());
                        buf[x].rgbtGreen = FLOATTOBYTE(color.Green());
                        buf[x].rgbtBlue = FLOATTOBYTE(color.Blue());
                    }
                    if (_write(m_filenumber, buffer, m_widthbytes) != m_widthbytes)
                        ErrorExit();
                }
            }
        }
        break;
        case 3:
        {
            auto *buf = (RGBTRIPLE *)buffer;
            RGBFloat color;
            for (int y = m_height - 1; y >= 0; y--) {
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    if (m_gamma != 1.F) {
                        color.SetRed(hash_math::pow(color.Red(), m_gamma));
                        color.SetGreen(hash_math::pow(color.Green(), m_gamma));
                        color.SetBlue(hash_math::pow(color.Blue(), m_gamma));
                    }
                    buf[x].rgbtRed = FLOATTOBYTE(color.Red());
                    buf[x].rgbtGreen = FLOATTOBYTE(color.Green());
                    buf[x].rgbtBlue = FLOATTOBYTE(color.Blue());
                }
                if (_write(m_filenumber, buffer, m_widthbytes) != m_widthbytes)
                    ErrorExit();
            }
        }
        break;
        case 2:
        case 1:
        {
            // grey scale image
            UBYTE *buf = buffer;
            for (int y = m_height - 1; y >= 0; y--) {
                for (int x = 0; x < m_width; ++x) {
                    RGBFloat color;
                    bn->ReadPixel(x, y, color);
                    buf[x] = FLOATTOBYTE(color.Red());
                }
                if (_write(m_filenumber, buffer, m_widthbytes) != m_widthbytes)
                    ErrorExit();
            }
        }
        default:
   break;
    }
    FreeBitmap(buffer);
    return true;

Error_Exit:
    FreeBitmap(buffer);
    return false;
}

void CustomImageIO::BMPClose() const {
    _close(m_filenumber);
    //   SetFileType( m_filename, FALSE, 'BMP ' );
}

long CustomImageIO::WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) {
    if (filename.GetSuffixOnly() != "bmp")
        return HBitmapNode::WRITE_NORESULT;

    HBitmapBuffer *bufferhead = bn->GetBufferHead();
    m_bytesperpixel = bufferhead->GetNbrChannels();
    m_isalpha = outputinfo->GetIsAlpha();
    m_depth = m_bytesperpixel * 8;
    if (!m_isalpha) {
        if (m_bytesperpixel == 4) {
            m_depth = 24;
        } else {
            if (m_bytesperpixel == 2) {
                m_depth = 8;
            }
        }
    }

    MakeDirPath(filename);
    [[maybe_unused]] int error = Remove(filename);

    m_width = bn->GetWidth();
    m_height = bn->GetHeight();
    m_gamma = hash_math::rcp(outputinfo->GetOutputGamma());
    if (!BMPOpen(filename))
        return HBitmapNode::WRITE_ERROR;
    m_filename = filename;

    if (!BMPWriteBitmap(bn))
        return HBitmapNode::WRITE_ERROR;

    BMPClose();
    return HBitmapNode::WRITE_OK;
}
