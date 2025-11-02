// YP  01/05/2005  \Plugin\Image Formats\TGA\Save.cpp

#include "StdAfx.h"
#include "RGBByte.h"
#include "Custom.h"
#include "IOApp.h"
#include "Files.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#define EXT_SIZE_20        495
#define NAMELENGTH         16
#define VERSION            5

#define ErrorExit()        {_close( m_outfilenumber ); return -1;}
#define ErrorExit1()       {status=false; goto Exit;}

extern CImageIOApp theApp;

static const char *programname = _T("Animation Master");

bool CustomImageIO::WriteByte(const UBYTE value) const {
    if (_write(m_outfilenumber, &value, 1) != 1)
        return false;
    return true;
}

bool CustomImageIO::WriteShort(const SHORT value) const {
    if (_write(m_outfilenumber, &value, 2) != 2)
        return false;
    return true;
}

bool CustomImageIO::WriteLong(const long value) const {
    if (_write(m_outfilenumber, &value, 4) != 4)
        return false;
    return true;
}

bool CustomImageIO::WriteFloat(const float value) const {
    if (_write(m_outfilenumber, &value, 4) != 4)
        return false;
    return true;
}

SSHORT CustomImageIO::CountDiffPixels8(const UBYTE *linebuf, SSHORT width, SSHORT x) {
    UBYTE nextpixel = 0;
    SSHORT n = 0;

    if (width == 1)
        return 1;
    UBYTE pixel = linebuf[x];
    while (width > 1) {
        if ((nextpixel = linebuf[++x]) == pixel)
            break;
        pixel = nextpixel;
        ++n;
        --width;
    }
    if (nextpixel == pixel)
        return n;

    return n + 1;
}

SSHORT CustomImageIO::CountDiffPixels(const TGABuf *linebuf, SSHORT width, SSHORT x) {
    UINT nextpixel = 0;
    SSHORT n = 0;

    if (width == 1)
        return 1;
    UINT pixel = linebuf[x].Color();
    while (width > 1) {
        if ((nextpixel = linebuf[++x].Color()) == pixel)
            break;
        pixel = nextpixel;
        ++n;
        --width;
    }
    if (nextpixel == pixel)
        return n;

    return n + 1;
}

SSHORT CustomImageIO::CountSamePixels8(const UBYTE *linebuf, SSHORT width, SSHORT x) {
    SSHORT n = 1;

    const UBYTE pixel = linebuf[x];
    while (--width > 0) {
        if (UBYTE nextpixel; (nextpixel = linebuf[++x]) != pixel)
            break;
        ++n;
    }

    return n;
}

SSHORT CustomImageIO::CountSamePixels(const TGABuf *linebuf, SSHORT width, SSHORT x) {
    SSHORT n = 1;

    const UINT pixel = linebuf[x].Color();
    while (--width > 0) {
        if (UINT nextpixel; (nextpixel = linebuf[++x].Color()) != pixel)
            break;
        ++n;
    }

    return n;
}

SSHORT CustomImageIO::RLEncodeRow8(UBYTE *buffer, const UBYTE *linebuf, SSHORT width) {
    SSHORT x = 0;

    if (!theApp.m_compression) {
        for (x = 0; x < width; ++x)
            *buffer++ = linebuf[x];
        return width;
    }

    SSHORT rlebufsize = 0;
    while (width > 0) {
        SSHORT diffcount = CountDiffPixels8(linebuf, width, x);
        SSHORT samecount = CountSamePixels8(linebuf, width, x);
        if (diffcount > 128)
            diffcount = 128;
        if (samecount > 128)
            samecount = 128;
        if (diffcount > 0) {
            // create a raw packet 
            *buffer++ = diffcount - 1;
            width -= diffcount;
            rlebufsize += diffcount + 1;
            while (diffcount-- > 0)
                *buffer++ = linebuf[x++];
        } else if (samecount > 1) {
            // create a RLE packet
            *buffer++ = samecount - 1 | 0x80;
            width -= samecount;
            rlebufsize += 2;
            *buffer++ = linebuf[x];
            x += samecount;
        }
    }
    return rlebufsize;
}

SSHORT CustomImageIO::RLEncodeRow(const TGABuf *linebuf, UBYTE *buffer, SSHORT width) {
    TGABuf color{};
    SSHORT x = 0, rlebufsize = 0;

    if (!theApp.m_compression) {
        for (x = 0; x < width; ++x) {
            color.SetColor(linebuf[x].Color());
            *buffer++ = color.Blue();
            *buffer++ = color.Green();
            *buffer++ = color.Red();
        }
        return width * 3;
    }

    while (width > 0) {
        SSHORT diffcount = CountDiffPixels(linebuf, width, x);
        SSHORT samecount = CountSamePixels(linebuf, width, x);
        if (diffcount > 128)
            diffcount = 128;
        if (samecount > 128)
            samecount = 128;
        if (diffcount > 0) {
            // create a raw packet 
            *buffer++ = diffcount - 1;
            width -= diffcount;
            rlebufsize += diffcount * 3 + 1;
            while (diffcount-- > 0) {
                color.SetColor(linebuf[x++].Color());
                *buffer++ = color.Blue();
                *buffer++ = color.Green();
                *buffer++ = color.Red();
            }
        } else if (samecount > 1) {
            // create a RLE packet
            *buffer++ = samecount - 1 | 0x80;
            width -= samecount;
            rlebufsize += 4;
            color.SetColor(linebuf[x].Color());
            *buffer++ = color.Blue();
            *buffer++ = color.Green();
            *buffer++ = color.Red();
            x += samecount;
        }
    }
    return rlebufsize;
}

SSHORT CustomImageIO::RLEncodeAlphaRow(const TGABuf *linebuf, UBYTE *buffer, SSHORT width) {
    TGABuf color{};
    SSHORT x = 0, rlebufsize = 0;

    if (!theApp.m_compression) {
        for (x = 0; x < width; ++x) {
            color.SetColor(linebuf[x].Color());
            *buffer++ = color.Blue();
            *buffer++ = color.Green();
            *buffer++ = color.Red();
            *buffer++ = color.Alpha();
        }
        return width * 4;
    }

    while (width > 0) {
        SSHORT diffcount = CountDiffPixels(linebuf, width, x);
        SSHORT samecount = CountSamePixels(linebuf, width, x);
        if (diffcount > 128)
            diffcount = 128;
        if (samecount > 128)
            samecount = 128;
        if (diffcount > 0) {
            // create a raw packet
            *buffer++ = diffcount - 1;
            width -= diffcount;
            rlebufsize += diffcount * 4 + 1;
            while (diffcount-- > 0) {
                color.SetColor(linebuf[x++].Color());
                *buffer++ = color.Blue();
                *buffer++ = color.Green();
                *buffer++ = color.Red();
                *buffer++ = color.Alpha();
            }
        } else if (samecount > 1) {
            /* create a RLE packet */
            *buffer++ = samecount - 1 | 0x80;
            width -= samecount;
            rlebufsize += 5;
            color.SetColor(linebuf[x].Color());
            *buffer++ = color.Blue();
            *buffer++ = color.Green();
            *buffer++ = color.Red();
            *buffer++ = color.Alpha();
            x += samecount;
        }
    }
    return rlebufsize;
}

int CustomImageIO::TGAOpenWrite(const String &name) {
    if (_sopen_s(&m_outfilenumber, name.Get(), _O_RDWR | _O_BINARY | _O_CREAT, _SH_DENYNO, _S_IWRITE) != 0)
        return -1;
    if (!WriteByte(0)) // ID Length
        ErrorExit()
    if (!WriteByte(0)) // Color Map Type
        ErrorExit()
    if (m_compress) {
        if (m_outdepth == 8) {
            if (!WriteByte(11)) // Compressed B/W Image Type 
                ErrorExit()
        } else if (!WriteByte(10)) // Compressed Color Image Type 
            ErrorExit()
    } else if (m_outdepth >= 24) {
        if (!WriteByte(2)) // Uncompressed, True-color Image Type
            ErrorExit()
    } else if (!WriteByte(3)) // Uncompressed, B&W Image Type
        ErrorExit()

    if (!WriteShort(0)) // Color Map Index 
        ErrorExit()
    if (!WriteShort(0)) // Color Map Length
        ErrorExit()
    if (!WriteByte(0)) // Color Map Entry Size
        ErrorExit()
    if (!WriteShort(0)) // X Origin
        ErrorExit()
    if (!WriteShort(0)) // Y Origin
        ErrorExit()
    if (!WriteShort(m_outwidth)) ErrorExit()
    if (!WriteShort(m_outheight)) // height
        ErrorExit()
    if (!WriteByte((SBYTE)m_outdepth)) ErrorExit()
    if (m_outdepth > 24) {
        // Image Descriptor
        if (!WriteByte(0x28)) // 8 Bit Alpha Channel
            ErrorExit()
    } else if (!WriteByte(0x20)) ErrorExit()

    return m_outfilenumber;
}

bool CustomImageIO::TGACloseWrite(const Vector *background, const float aspect, const bool premultipliedalpha) const {
    long extensionoffset;
    bool status = true;
    // ReSharper disable once CppJoinDeclarationAndAssignment
    int length;
    if ((extensionoffset = _lseek(m_outfilenumber, 0L, SEEK_CUR)) == -1) {
//        [[maybe_unused]] String err = strerror(0);
        ErrorExit1()
    }

    if (_lseek(m_outfilenumber, DEPTHOFFSET, SEEK_SET) != DEPTHOFFSET) ErrorExit1()
    if (!WriteByte((SBYTE)m_outdepth)) ErrorExit1()
    if (_lseek(m_outfilenumber, extensionoffset, SEEK_SET) != extensionoffset) ErrorExit1()

    /* Extension Area */
    if (!WriteShort(EXT_SIZE_20)) ErrorExit1()
    length = m_user.GetLength();
    if (_write(m_outfilenumber, m_user.Get(), length) != length) ErrorExit1()
    for (int i = 0; i < 41 - length; ++i) /* Author Name */
        if (!WriteByte(0)) ErrorExit1()
    for (int i = 0; i < 324; ++i) /* Author Comments */
        if (!WriteByte(0)) ErrorExit1()
    for (int i = 0; i < 12; ++i) /* Date/Time Stamp */
        if (!WriteByte(0)) ErrorExit1()
    length = m_org.GetLength();
    if (_write(m_outfilenumber, m_org.Get(), length) != length) ErrorExit1()
    for (int i = 0; i < 41 - length; ++i) /* Job Name/ID */
        if (!WriteByte(0)) ErrorExit1()
    for (int i = 0; i < 6; ++i) /* Job Time */
        if (!WriteByte(0)) ErrorExit1()
    if (_write(m_outfilenumber, programname, NAMELENGTH) != NAMELENGTH) ErrorExit1()
    for (int i = 0; i < 41 - NAMELENGTH; ++i) /* pad rest of Software ID */
        if (!WriteByte(0)) ErrorExit1()
    if (!WriteShort(VERSION * 100)) ErrorExit1()
    if (!WriteByte(' ')) ErrorExit1()
    if (!WriteByte(0)) /* Alpha Field */
        ErrorExit1()
    if (!WriteByte((UBYTE)background->z)) /* Red Field */
        ErrorExit1()
    if (!WriteByte((UBYTE)background->y)) /* Green Field */
        ErrorExit1()
    if (!WriteByte((UBYTE)background->x)) /* Blue Field */
        ErrorExit1()
    if (!WriteShort((SHORT)(aspect * 100))) ErrorExit1()
    if (!WriteShort(100)) ErrorExit1()
    if (!WriteShort((SHORT)(m_targetgamma * 100.F))) // Gamma Value numerator
        ErrorExit1()
    if (!WriteShort(100)) // Gamma Value denominator
        ErrorExit1()
    if (!WriteLong(0L)) // Color Correction Offset
        ErrorExit1()
    if (!WriteLong(0L)) // Postage Stamp Offset
        ErrorExit1()
    if (!WriteLong(0L)) // Scan Line Offset
        ErrorExit1()
    if (m_outdepth > 24) {
        if (premultipliedalpha) {
            if (!WriteByte(4)) /* Attributes - alpha channel */
                ErrorExit1()
        } else {
            if (!WriteByte(3)) /* Attributes - alpha channel */
                ErrorExit1()
        }
    } else if (!WriteByte(0)) /* Attributes - no alpha channel */
        ErrorExit1()

    /* TGA File Footer */
    if (!WriteLong(extensionoffset)) ErrorExit1()
    if (!WriteLong(0)) // dev offset
        ErrorExit1()
    if (_write(m_outfilenumber, "TRUEVISION-XFILE", 16) != 16) ErrorExit1()
    if (!WriteByte('.')) /* Reserved Character */
        ErrorExit1()
    if (!WriteByte(0)) /* Binary Zero String Terminator */
        ErrorExit1()

Exit: _close(m_outfilenumber);

    return status;
}

bool CustomImageIO::TGAWriteLine(const TGABuf *linebuf) const {
    SSHORT rlecount;
    UBYTE *buffer;
    bool status = true;

    if (m_outfilenumber == -1)
        return true;

    if ((buffer = (UBYTE *)AllocBitmap(m_outwidth * 5LL)) == nullptr)
        return false;

    if (m_outdepth > 24)
        rlecount = RLEncodeAlphaRow(linebuf, buffer, m_outwidth);
    else
        rlecount = RLEncodeRow(linebuf, buffer, m_outwidth);
    if (_write(m_outfilenumber, buffer, (size_t)rlecount) != rlecount) ErrorExit1()

Exit:
    FreeBitmap(buffer);
    return status;
}

long CustomImageIO::WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) {
    if (filename.GetSuffixOnly() != "tga")
        return HBitmapNode::WRITE_NORESULT;
    m_gammapreset = (GammaType)outputinfo->GetGammaPreset(); // TGA does not store colorspace info. Just gamma so if sRGB, just use the gamma value.
    m_targetgamma = outputinfo->GetOutputGamma();
    if (m_targetgamma == 1.F)
        m_gammapreset = GAMMA_NONE;
    const float gamma = hash_math::rcp(m_targetgamma);
    TGABuf tgacolor;
    Vector bgcolor;
    UBYTE *buffer;

    HBitmapBuffer *bufferhead = bn->GetBufferHead();
    if (bufferhead == nullptr)
        return HBitmapNode::WRITE_NORESULT;
    const int nbrchannels = bufferhead->GetNbrChannels();
    switch (nbrchannels) {
        case 1:
        case 3:
            m_outbytesperpixel = nbrchannels;
            break;
        case 2:
            m_outbytesperpixel = 1; // TGA can't store gray + alpha so store only gray.
            break;
        case 4:
            if (outputinfo->GetIsAlpha())
                m_outbytesperpixel = 4;
            else
                m_outbytesperpixel = 3;
            break;
        default:
            return HBitmapNode::WRITE_NORESULT; // Shouldn't happen and Wouldn't know what to do with that here anyway
    }
    m_outdepth = m_outbytesperpixel * 8;

    MakeDirPath(filename);
    [[maybe_unused]] int error = Remove(filename);

    m_user = outputinfo->GetUser();
    if (m_user.GetLength() > 40) {
        m_user = m_user.Left(40);
    }
    m_org = outputinfo->GetOrganization();
    if (m_org.GetLength() > 40) {
        m_org = m_org.Left(40);
    }
    m_compress = theApp.m_compression;
    m_outwidth = bn->GetWidth();
    m_outheight = bn->GetHeight();
    if ((m_outfilenumber = TGAOpenWrite(filename)) == -1)
        return HBitmapNode::WRITE_ERROR;

    if (m_outbytesperpixel != 1)
        buffer = (UBYTE *)AllocBitmap(sizeof(TGABuf) * m_outwidth);
    else
        buffer = (UBYTE *)AllocBitmap(m_outwidth);
    if (!buffer)
        return HBitmapNode::WRITE_ERROR;

    switch (nbrchannels) {
        case 4:
        {
            auto *tgabuf = (TGABuf *)buffer;
            RGBAFloat color;
            for (int y = 0; y < m_outheight; ++y) {
                for (int x = 0; x < m_outwidth; ++x) {
                    bn->ReadPixel(x, y, color);
                    if (m_gammapreset) {
                        color.SetRed(hash_math::pow(color.Red(), gamma));
                        color.SetGreen(hash_math::pow(color.Green(), gamma));
                        color.SetBlue(hash_math::pow(color.Blue(), gamma));
                    }
                    tgabuf[x].SetRed(FLOATTOBYTE(color.Red()));
                    tgabuf[x].SetGreen(FLOATTOBYTE(color.Green()));
                    tgabuf[x].SetBlue(FLOATTOBYTE(color.Blue()));
                    if (outputinfo->GetIsAlpha())
                        tgabuf[x].SetAlpha(FLOATTOBYTE(color.Alpha()));
                    else
                        tgabuf[x].SetAlpha(255);
                }
                TGAWriteLine(tgabuf);
            }
        }
        break;
        case 3:
        {
            auto *tgabuf = (TGABuf *)buffer;
            RGBFloat color;
            for (int y = 0; y < m_outheight; ++y) {
                for (int x = 0; x < m_outwidth; ++x) {
                    bn->ReadPixel(x, y, color);
                    if (m_gammapreset) {
                        color.SetRed(hash_math::pow(color.Red(), gamma));
                        color.SetGreen(hash_math::pow(color.Green(), gamma));
                        color.SetBlue(hash_math::pow(color.Blue(), gamma));
                    }
                    tgabuf[x].SetRed(FLOATTOBYTE(color.Red()));
                    tgabuf[x].SetGreen(FLOATTOBYTE(color.Green()));
                    tgabuf[x].SetBlue(FLOATTOBYTE(color.Blue()));
                    tgabuf[x].SetAlpha(255);
                }
                TGAWriteLine(tgabuf);
            }
        }
        break;
        case 2:
        {
            auto *temp = (UBYTE *)AllocExt(2LL * m_outwidth);
            YAFloat color;
            for (int y = 0; y < m_outheight; ++y) {
                for (int x = 0; x < m_outwidth; ++x) {
                    bn->ReadPixel(x, y, color);
                    if (m_gammapreset)
                        color.SetLuminance(hash_math::pow(color.Luminance(), gamma));
                    buffer[x] = FLOATTOBYTE(color.Luminance());
                }
                const int rlecount = RLEncodeRow8(temp, buffer, m_outwidth);
                _write(m_outfilenumber, temp, (size_t)rlecount);
            }
        }
        break;
        case 1:
        {
            auto *temp = (UBYTE *)AllocExt(2LL * m_outwidth);
            RGBFloat color;
            for (int y = 0; y < m_outheight; ++y) {
                for (int x = 0; x < m_outwidth; ++x) {
                    bn->ReadPixel(x, y, color);
                    if (m_gammapreset)
                        color.SetRed(hash_math::pow(color.Red(), gamma));
                    buffer[x] = FLOATTOBYTE(color.Red());
                }
                const int rlecount = RLEncodeRow8(temp, buffer, m_outwidth);
                _write(m_outfilenumber, temp, (size_t)rlecount);
            }
            FreeExt(temp);
        }
    }

    const RGBFloat background = bn->GetBufferHead()->GetBackground();
    tgacolor.SetRed((UBYTE)background.Red());
    tgacolor.SetGreen((UBYTE)background.Green());
    tgacolor.SetBlue((UBYTE)background.Blue());
    //tgacolor.SetAlpha(background.Alpha()); //NAP Bitmap used to call SetColor but I'm not sure alpha makes sense here
    tgacolor.SetAlpha(255); //NAP Bitmap used to call SetColor but I'm not sure alpha makes sense here

    bgcolor.Set(tgacolor.Red(), tgacolor.Green(), tgacolor.Blue());
    TGACloseWrite(&bgcolor, 1.F, bn->GetBufferHead()->GetIsPremultipliedAlpha());
    if (buffer)
        FreeBitmap(buffer);
    //   SetFileType( filename, FALSE, 'TPIC' );
    return HBitmapNode::WRITE_OK;
}
