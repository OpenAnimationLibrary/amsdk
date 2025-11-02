// NAP  2/21/2005  \Noel120\Plugin\Image Formats\TGA\Load.cpp

// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
#include "StdAfx.h"
#include "RGBByte.h"
#include "RGBHalf.h"
#include "SDK/HBitmap.h"
#include "3rdParty/OpenEXR3/Imath/half.h"
#include "Custom.h"
#include "Matrix34.h"
#include "IOApp.h"
#include "Files.h"

#include <io.h>
#include <fcntl.h>

#define ErrorExit()           goto Error_Exit
#define ALLOC( baz )          (UBYTE *)AllocBitmap((long)(baz) )
#define FREE( baz )           {if (baz){FreeBitmap( baz );(baz)=nullptr;}}

#define BUFFERSIZE            512

extern CImageIOApp theApp;

UBYTE CustomImageIO::ReadBufferByte() {
    if (m_filled == 0) {
        if ((m_filled = _read(m_infilenumber, m_data, BUFFERSIZE)) == -1 || m_filled == 0) {
            m_readstatus = false;
            return 0;
        }
        m_buf = m_data;
    } else
        ++m_buf;

    --m_filled;
    return *m_buf;
}

bool CustomImageIO::GetMapEntry(UBYTE *red, UBYTE *grn, UBYTE *blu, const UBYTE bytesperpixel) {

    switch (bytesperpixel) {
        case 8: // grey scale already, read and triplicate
            *red = *grn = *blu = ReadBufferByte();
            break;
        case 16: // 5 bits each of red, green, and blue
        case 15: // watch for byte order
        {
            const int j = ReadBufferByte();
            int l = ReadBufferByte();
            l = (l << 8) + j;
            *red = (l >> 10 & 31) << 3;
            *grn = (l >> 5 & 31) << 3;
            *blu = (l & 31) << 3;
        }
        break;
        case 24: // 8 bits each of red, green, and blue
            *blu = ReadBufferByte();
            *grn = ReadBufferByte();
            *red = ReadBufferByte();
            break;
        case 32: // 8 bits each of red, green, blue, throw away alpha
            *blu = ReadBufferByte();
            *grn = ReadBufferByte();
            *red = ReadBufferByte();
            ReadBufferByte();
            break;
        default:
            return false;
    }
    return m_readstatus;
}

bool CustomImageIO::GetTGARow() {
    int rlecount = 0;
    bool rleflag = false;

    for (int x = 0; m_readstatus && x < m_inwidth; ++x) {
        if (m_mode & RLENCD) {
            if (rlecount == 0) {
                const UBYTE temp = ReadBufferByte();
                rleflag = (temp & 0x80) >> 7;
                if (!rleflag)
                    rlecount = temp;
                else
                    rlecount = temp - 128;
            } else {
                --rlecount;
                if (rleflag) {
                    switch (m_inbytesperpixel) {
                        case 1:
                            m_row[x] = m_row[x - 1];
                            break;
                        case 2:
                            m_row[x] = m_row[x - 1];
                            m_row[x + m_inwidth] = m_row[x + m_inwidth - 1];
                            break;
                        case 3:
                            m_row[x] = m_row[x - 1];
                            m_row[x + m_inwidth] = m_row[x + m_inwidth - 1];
                            m_row[x + m_width2] = m_row[x + m_width2 - 1];
                            break;
                        case 4:
                            m_row[x] = m_row[x - 1];
                            m_row[x + m_inwidth] = m_row[x + m_inwidth - 1];
                            m_row[x + m_width2] = m_row[x + m_width2 - 1];
                            m_row[x + m_width3] = m_row[x + m_width3 - 1];
                            break;
                    }
                    continue;
                }
            }
        }

        switch (m_inbytesperpixel) {
            case 1:
                m_row[x] = ReadBufferByte();
                break;
            case 2: // 5 bits each of red, green, blue
                m_row[x] = ReadBufferByte();
                m_row[x + m_inwidth] = ReadBufferByte();
                break;
            case 3: // 8 bits each of red, green, blue
                m_row[x + m_width2] = ReadBufferByte();
                m_row[x + m_inwidth] = ReadBufferByte();
                m_row[x] = ReadBufferByte();
                break;
            case 4: // 8 bits each of red, green, blue, alpha
                m_row[x + m_width2] = ReadBufferByte();
                m_row[x + m_inwidth] = ReadBufferByte();
                m_row[x] = ReadBufferByte();
                m_row[x + m_width3] = ReadBufferByte();
                break;
            default:
                return false;
        }
    }
    return m_readstatus;
}

bool CustomImageIO::OpenReadTGA(HBitmapNode *bn, const String &filename) {
    int pfilenumber; //NAP Bitmap COME-back handle frame

    if (_sopen_s(&pfilenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return false;

    UBYTE alpha, red, green, blue, attrtype;

    m_readstatus = true;
    m_filled = 0;
    m_embeddedgamma = 1.F;
    m_infilenumber = pfilenumber;
    _lseek(m_infilenumber, -26L, SEEK_END);
    if (_read(m_infilenumber, &m_footer, SIZEOFFOOTER) != SIZEOFFOOTER) {
        _close(m_infilenumber);
        m_infilenumber = 0;
        return false;
    }
    m_ispremultipliedalpha = false;

    if (strcmp(m_footer.signature, "TRUEVISION-XFILE.") == 0) {
        if (m_footer.extoffset) {
            _lseek(m_infilenumber, m_footer.extoffset + KEYCOLOR, SEEK_SET);
            if (_read(m_infilenumber, &alpha, sizeof(UBYTE)) != sizeof(UBYTE)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            if (_read(m_infilenumber, &red, sizeof(UBYTE)) != sizeof(UBYTE)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            if (_read(m_infilenumber, &green, sizeof(UBYTE)) != sizeof(UBYTE)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            if (_read(m_infilenumber, &blue, sizeof(UBYTE)) != sizeof(UBYTE)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            m_background = RGBFloat(red / 255.0f, green / 255.0f, blue / 255.0f); //NAP Bitmap huh this is 0-1?
            m_hasbackground = true;
            /* now part of buffer
            if (m_sbflags & HBitmapNode::LOADBKCOLOR) {
               bn->SetBackground(RGBFloat(red/255.0f, green/255.0f, blue/255.0f)); //NAP Bitmap
               bn->SetHasBackground(TRUE);
            }
            */
            USHORT gammanumerator;
            _lseek(m_infilenumber, m_footer.extoffset + GAMMA, SEEK_SET);
            if (_read(m_infilenumber, &gammanumerator, sizeof(USHORT)) != sizeof(USHORT)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            USHORT gammadenominator;
            if (_read(m_infilenumber, &gammadenominator, sizeof(USHORT)) != sizeof(USHORT)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            m_embeddedgamma = 1.F;
            if (m_sbflags & HBitmapNode::LOADBKCOLOR && gammadenominator) {
                // use this flags for gamma also
                m_embeddedgamma = (float)gammanumerator / gammadenominator;
                if (m_embeddedgamma <= 0.F || m_embeddedgamma > 10.F)
                    m_embeddedgamma = 1.F;
            }
            //bn->SetGamma( m_embeddedgamma ); now part of buffer
            _lseek(m_infilenumber, m_footer.extoffset + ATTRTYPE, SEEK_SET);
            if (_read(m_infilenumber, &attrtype, sizeof(UBYTE)) != sizeof(UBYTE)) {
                _close(m_infilenumber);
                m_infilenumber = 0;
                return false;
            }
            if (attrtype == 0x04)
                m_ispremultipliedalpha = true;
        }
    } else
        m_hasbackground = false;
    /* now part of buffer and these are the defaults
    } else if (m_sbflags & HBitmapNode::LOADBKCOLOR) {
       bn->SetBackground(RGBFloat(1.F,1.F,1.F));
       bn->SetHasBackground(FALSE);
    }*/
    _lseek(m_infilenumber, 0L, SEEK_SET);
    if (_read(m_infilenumber, &m_header, SIZEOFHEADER) != SIZEOFHEADER) {
        _close(m_infilenumber);
        m_infilenumber = 0;
        return false;
    }
    m_inwidth = (int)m_header.width_hi * 256 + m_header.width_lo;
    m_inheight = (int)m_header.height_hi * 256 + m_header.height_lo;
    bn->SetWidth(m_inwidth);
    bn->SetHeight(m_inheight);
    m_inbytesperpixel = (m_header.pixelsize - 1) / 8 + 1;
    return true;
}

bool CustomImageIO::PrepareReadTGA() {
    m_data = m_colormap = m_buffer = m_row = nullptr;
    try {
        m_data = ALLOC(BUFFERSIZE);
        switch (m_header.imgtype) {
            case TGA_MAPRGBTYPE:
            case TGA_RAWRGBTYPE:
            case TGA_MAPENCODETYPE:
            case TGA_RAWENCODETYPE:
                m_mode = COLOR;
                break;
            case TGA_RAWMONOTYPE:
            case TGA_MONOENCODETYPE:
                m_mode = GREYSC;
                break;
            default:
                ErrorExit();
        }

        if (m_header.idlength)
            _lseek(m_infilenumber, m_header.idlength, SEEK_CUR);
        if (m_header.comaptype) {
            const int temp1 = m_header.index_lo + ((SSHORT)m_header.index_hi << 8);
            const int temp2 = m_header.length_lo + ((SSHORT)m_header.length_hi << 8);
            if ((m_colorsize = 3 * (temp1 + temp2)) > 3 * 256)
                m_colorsize = 3 * 256;
            m_colormap = ALLOC(m_colorsize);
            for (int i = temp1; i < m_colorsize; i += 3)
                if (!GetMapEntry(&m_colormap[i], &m_colormap[i + 1], &m_colormap[i + 2], m_header.cosize))
                    ErrorExit();
            switch (m_header.imgtype) {
                case TGA_MAPRGBTYPE:
                case TGA_MAPENCODETYPE:
                    m_mode |= MAPPED;
            }
        }
        switch (m_header.imgtype) {
            case TGA_MAPENCODETYPE:
            case TGA_MONOENCODETYPE:
            case TGA_RAWENCODETYPE:
                m_mode |= RLENCD;
        }
        switch (m_header.intrlve) {
            case 2:
                m_mode |= FOURWY;
            case 1:
                m_mode |= INTERL;
        }
        m_width2 = m_inwidth << 1;
        m_width3 = m_inwidth * 3;
        m_buffer = ALLOC(2L * m_inwidth);
        m_row = ALLOC((long) m_inwidth * m_inbytesperpixel);
        return true;
    }
    catch (CMemoryException &pMemEx) {
        pMemEx.Delete();
        TRACE(_T("Failed to allocate size of TGA\n"));
        //ASSERT->If this ASSERT fires, you have run out of memory
        ASSERT(FALSE);
    }
Error_Exit:
    _close(m_infilenumber);
    FREE(m_data)
    FREE(m_colormap)
    FREE(m_buffer)
    FREE(m_row)
    return false;
}

bool CustomImageIO::ReadTGAGamma(HBitmapNode *bn) {
//    int y;
//    float R, G, B;
    try {
        int ystart;
        int yend;
        int ydelta;
        if (m_header.orgbit == 0) {
            ystart = m_inheight - 1;
            yend = -1;
            ydelta = -1;
        } else {
            ystart = 0;
            yend = m_inheight;
            ydelta = 1;
        }
        const UBYTE *row = m_row;
        HBitmapBuffer *buffer = nullptr;
        switch (m_inbytesperpixel) {
            case 1:
            {
                if (m_mode | COLOR) {
                    HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_HALF, m_inwidth, m_inheight);
                    rgbbuffer->AllocateData();
                    auto *data = (RGBHalf *)rgbbuffer->GetData();
                    bn->AddBuffer(rgbbuffer);
                    for (int y = ystart; y != yend; y += ydelta) {
                        if (!GetTGARow())
                            ErrorExit();
                        for (int x = 0; x < m_inwidth; ++x) {
                            const int i = row[x] * 3;
                            const float R = m_colormap[i] / 255.0f;
                            const float G = m_colormap[i + 1] / 255.0f;
                            const float B = m_colormap[i + 2] / 255.0f;
                            *(data + y * (int64_t)m_inwidth + x) = RGBHalf(hash_math::pow(R, m_embeddedgamma), hash_math::pow(G, m_embeddedgamma), hash_math::pow(B, m_embeddedgamma));
                        }
                        buffer = rgbbuffer;
                        buffer->SetIsKeyBackground(m_hasbackground);
                    }
                } else {
                    HScalarBuffer *scalarbuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_HALF, m_inwidth, m_inheight);
                    scalarbuffer->AllocateData();
                    half *data = (half *)scalarbuffer->GetData();
                    bn->AddBuffer(scalarbuffer);
                    for (int y = ystart; y != yend; y += ydelta) {
                        if (!GetTGARow())
                            ErrorExit();
                        for (int x = 0; x < m_inwidth; ++x)
                            *(data + y * (int64_t)m_inwidth + x) = (half)hash_math::pow((float)row[x] / 255.0f, m_embeddedgamma);
                    }
                    buffer = scalarbuffer;
                    buffer->SetIsKeyBackground(m_hasbackground);
                }
                break;
            }
            case 2:
            {
                // 16 bits with 5 bits per RGB component.
                HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_HALF, m_inwidth, m_inheight);
                rgbbuffer->AllocateData();
                auto *data = (RGBHalf *)rgbbuffer->GetData();
//                USHORT *wrow = (WORD *)m_row;
                bn->AddBuffer(rgbbuffer);
                for (int y = ystart; y != yend; y += ydelta) {
                    if (!GetTGARow())
                        ErrorExit();
                    for (int x = 0; x < m_inwidth; ++x) {
                        const float R = (float)((UBYTE)((row[x + m_inwidth] & 0x7C) << 1) & 0xF8) / 255.0f;
                        const float G = (float)((UBYTE)(((row[x] & 0xE0) >> 2) + ((row[x + m_inwidth] & 0x03) << 6)) & 0xF8) / 255.0f;
                        const float B = (float)((UBYTE)(row[x] & 0x1F) << 3) / 255.0f;
                        *(data + y * (int64_t)m_inwidth + x) = RGBHalf(hash_math::pow(R, m_embeddedgamma), hash_math::pow(G, m_embeddedgamma), hash_math::pow(B, m_embeddedgamma));
                    }
                }
                buffer = rgbbuffer;
                buffer->SetIsKeyBackground(m_hasbackground);
                break;
            }
            case 3:
            {
                HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_HALF, m_inwidth, m_inheight);
                rgbbuffer->AllocateData();
                auto *data = (RGBHalf *)rgbbuffer->GetData();
                bn->AddBuffer(rgbbuffer);
                for (int y = ystart; y != yend; y += ydelta) {
                    if (!GetTGARow())
                        ErrorExit();
                    for (int x = 0; x < m_inwidth; ++x) {
                        const float R = (float)row[x] / 255.0f;
                        const float G = (float)(row + m_inwidth)[x] / 255.0f;
                        const float B = (float)(row + m_width2)[x] / 255.0f;
                        *(data + y * (int64_t)m_inwidth + x) = RGBHalf(hash_math::pow(R, m_embeddedgamma), hash_math::pow(G, m_embeddedgamma), hash_math::pow(B, m_embeddedgamma));
                    }
                }
                buffer = rgbbuffer;
                buffer->SetIsKeyBackground(m_hasbackground);
                break;
            }
            case 4:
            {
                HRGBABuffer *rgbabuffer = HBitmapNode::CreateRGBABuffer("ColorAlpha", HBitmapBuffer::CT_HALF, m_inwidth, m_inheight);
                rgbabuffer->AllocateData();
                auto *data = (RGBAHalf *)rgbabuffer->GetData();
                bn->AddBuffer(rgbabuffer);
                for (int y = ystart; y != yend; y += ydelta) {
                    if (!GetTGARow())
                        ErrorExit();
                    for (int x = 0; x < m_inwidth; ++x) {
                        const float R = hash_math::pow((float)row[x] / 255.0f, m_embeddedgamma);
                        const float G = hash_math::pow((float)(row + m_inwidth)[x] / 255.0f, m_embeddedgamma);
                        const float B = hash_math::pow((float)(row + m_width2)[x] / 255.0f, m_embeddedgamma);
                        const float A = (float)(row + m_width3)[x] / 255.0f;
                        if (m_ispremultipliedalpha && A != 0.F) // makes it unpremultiplied
                            *(data + y * (int64_t)m_inwidth + x) = RGBAHalf(MIN(R / A, 1.F), MIN(G / A, 1.F), MIN(B / A, 1.F), A);
                        else
                            *(data + y * (int64_t)m_inwidth + x) = RGBAHalf(R, G, B, A);
                    }
                }
                buffer = rgbabuffer;
                break;
            }
            default:
   break;
        }
        buffer->SetIsPremultipliedAlpha(FALSE); // undid multiply when pixels were read in ReadTGA
        buffer->SetGamma(m_embeddedgamma);
        if (m_hasbackground) {
            //buffer->SetIsKeyBackground(TRUE); //done above since background doesn't make sense with alpha
            buffer->SetBackground(m_background);
        }
        m_status = HBitmapNode::LOAD_OK;
        return true;
    }
    catch (CMemoryException &pMemEx) {
        pMemEx.Delete();
        TRACE(_T("Failed to allocate size of TGA\n"));
        //ASSERT->If this ASSERT fires, you have run out of memory
        ASSERT(FALSE);
    }

Error_Exit:
    _close(m_infilenumber);
    FREE(m_data)
    FREE(m_colormap)
    FREE(m_buffer)
    FREE(m_row)
    bn->DeleteAllBuffers();
    return false;
}

bool CustomImageIO::ReadTGA(HBitmapNode *bn) {
//    int y;
    try {
        int ydelta;
        int yend;
        int ystart;
        if (m_header.orgbit == 0) {
            // lower left
            ystart = m_inheight - 1;
            yend = -1;
            ydelta = -1;
        } else {
            // upper left
            ystart = 0;
            yend = m_inheight;
            ydelta = 1;
        }
        UBYTE *row = m_row;
        HBitmapBuffer *buffer = nullptr;
        switch (m_inbytesperpixel) {
            case 1:
            {
                if (m_mode & COLOR) {
                    HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_UBYTE, m_inwidth, m_inheight);
                    rgbbuffer->AllocateData();
                    auto *data = (RGBByte *)rgbbuffer->GetData();
                    bn->AddBuffer(rgbbuffer);
                    for (int y = ystart; y != yend; y += ydelta) {
                        if (!GetTGARow())
                            ErrorExit();
                        for (int x = 0; x < m_inwidth; ++x) {
                            const int i = row[x] * 3;
                            *(data + y * (int64_t)m_inwidth + x) = RGBByte(m_colormap[i], m_colormap[i + 1], m_colormap[i + 2]);
                        }
                    }
                    buffer = rgbbuffer;
                } else {
                    HScalarBuffer *scalarbuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_UBYTE, m_inwidth, m_inheight);
                    scalarbuffer->AllocateData();
                    auto *data = (UBYTE *)scalarbuffer->GetData();
                    bn->AddBuffer(scalarbuffer);
                    for (int y = ystart; y != yend; y += ydelta) {
                        if (!GetTGARow())
                            ErrorExit();
                        for (int x = 0; x < m_inwidth; ++x)
                            *(data + y * (int64_t)m_inwidth + x) = row[x];
                    }
                    buffer = scalarbuffer;
                }
                break;
            }
            case 2:
            {
                // 16 bits with 5 bits per RGB component.
                HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_UBYTE, m_inwidth, m_inheight);
                rgbbuffer->AllocateData();
                auto *data = (RGBByte *)rgbbuffer->GetData();
                bn->AddBuffer(rgbbuffer);
                for (int y = ystart; y != yend; y += ydelta) {
                    if (!GetTGARow())
                        ErrorExit();
                    for (int x = 0; x < m_inwidth; ++x)
                        *(data + y * (int64_t)m_inwidth + x) = RGBByte((UBYTE)((row[x + m_inwidth] & 0x7C) << 1) & 0xF8,
                                                              (UBYTE)(((row[x] & 0xE0) >> 2) + ((row[x + m_inwidth] & 0x03) << 6)) & 0xF8,
                                                              (UBYTE)(row[x] & 0x1F) << 3);
                }
                buffer = rgbbuffer;
                break;
            }
            case 3:
            {
                //NAP Bitmap COMEBACK is it "R" "G" "B" or this dito case 4
                HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_UBYTE, m_inwidth, m_inheight);
                rgbbuffer->AllocateData();
                auto *data = (RGBByte *)rgbbuffer->GetData();
                bn->AddBuffer(rgbbuffer);
                for (int y = ystart; y != yend; y += ydelta) {
                    if (!GetTGARow())
                        ErrorExit();
                    for (int x = 0; x < m_inwidth; ++x)
                        *(data + y * (int64_t)m_inwidth + x) = RGBByte(row[x], (row + m_inwidth)[x], (row + m_width2)[x]);
                }
                buffer = rgbbuffer;
                break;
            }
            case 4:
            {
                float alpha;
                HRGBABuffer *rgbabuffer = HBitmapNode::CreateRGBABuffer("ColorAlpha", HBitmapBuffer::CT_UBYTE, m_inwidth, m_inheight);
                rgbabuffer->AllocateData();
                auto *data = (RGBAByte *)rgbabuffer->GetData();
                bn->AddBuffer(rgbabuffer);
                for (int y = ystart; y != yend; y += ydelta) {
                    if (!GetTGARow())
                        ErrorExit();
                    if (m_ispremultipliedalpha) {
                        // makes it unpremultiplied
                        for (int x = 0; x < m_inwidth; ++x) {
                            if ((alpha = (float)(row + m_width3)[x] / 255) != 0) {
                                row[x] = fast_ftol_unsigned(MIN(255.F, row[x] / alpha));
                                (row + m_inwidth)[x] = fast_ftol_unsigned(MIN(255.F, (row + m_inwidth)[x] / alpha));
                                (row + m_width2)[x] = fast_ftol_unsigned(MIN(255.F, (row + m_width2)[x] / alpha));
                            }
                        }
                    }
                    for (int x1 = 0; x1 < m_inwidth; ++x1) {
#ifdef _DEBUG
                        const RGBAByte test = RGBAByte(row[x1], (row + m_inwidth)[x1], (row + m_width2)[x1], (row + m_width3)[x1]);
                        (data + y * (int64_t)m_inwidth)[x1] = test;
#else
                        (data + y * (int64_t)m_inwidth)[x1] = RGBAByte(row[x1], (row + m_inwidth)[x1], (row + m_width2)[x1], (row + m_width3)[x1]);
#endif
                    }
                }
                buffer = rgbabuffer;
                break;
            }
            default:
   break;
        }
        buffer->SetIsPremultipliedAlpha(FALSE); // undid multiply when pixels were read in ReadTGA
        m_status = HBitmapNode::LOAD_OK;
        return true;
    }
    catch (CMemoryException &pMemEx) {
        pMemEx.Delete();
        TRACE(_T("Failed to allocate size of TGA\n"));
        //ASSERT->If this ASSERT fires, you have run out of memory
        ASSERT(FALSE);
    }

Error_Exit:
    _close(m_infilenumber);
    FREE(m_data)
    FREE(m_colormap)
    FREE(m_buffer)
    FREE(m_row)
    bn->DeleteAllBuffers();
    return false;
}

    // ReSharper disable CppEntityAssignedButNoRead
bool CustomImageIO::IsTGA(const int filenumber) {
    TGA_ImageHeader header{};
    char buf[17];

    [[maybe_unused]] int value = _lseek(filenumber, 0L, SEEK_SET);
    if ((value = _read(filenumber, &header, 18)) != 18 || header.imgtype < TGA_MAPRGBTYPE || header.imgtype > TGA_MONOENCODETYPE) {
        return false;
    }
    // ReSharper disable once CppAssignedValueIsNeverUsed
    value = _lseek(filenumber, -18L, SEEK_END);
    if (_read(filenumber, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        return false;

    buf[16] = 0;

    if (!strcmp(buf, "TRUEVISION-XFILE"))
        return true;

    return false;
}
    // ReSharper restore CppEntityAssignedButNoRead

bool CustomImageIO::IsOldTGA(const int filenumber) {
    TGA_ImageHeader header{};

    _lseek(filenumber, 0L, SEEK_SET);
    if (_read(filenumber, &header, 18) != 18)
        return false;
    if (header.imgtype != 1 && header.imgtype != 2 && header.imgtype != 3 && header.imgtype != 9 && header.imgtype != 10 && header.imgtype != 11)
        return false;
    if (header.comaptype != 0 && header.comaptype != 1)
        return false;
    if (header.pixelsize != 8 && header.pixelsize != 16 && header.pixelsize != 24 && header.pixelsize != 32)
        return false;
    return true;
}

// ****************** Interface

bool CustomImageIO::CanLoadImage(const String &filename) {
    int pfilenumber;
    if (_sopen_s(&pfilenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return false;

    if (IsTGA(pfilenumber) || IsOldTGA(pfilenumber)) {
        _close(pfilenumber);
        return true;
    }
    _close(pfilenumber);
    return false;
}

void CustomImageIO::GetFilesStartEndFrame(const String &filename, int &start, int &end) {
    start = 0;
    end = 0;
    const String path = filename.GetWithoutSuffix();
    String digitstring;
    for (int i = path.GetLength() - 1; i >= 0; i--) {
        if (isdigit(path[i]))
            digitstring = path[i] + digitstring;
        else
            break;
    }
    if (!digitstring.IsEmpty()) {
        start = atoi_replace(digitstring.Get());
        int endtest = start;
        String endname = filename;
        do {
            end = endtest;
            endtest++;
            endname = endname.NumberFrame(endtest);
        } while (FileExists(endname));
    }
}

long CustomImageIO::LoadFrame(HBitmapNode *bn, const String &filename, int frame/*=-1*/, const UINT flags /*= 0*/) {
    m_sbflags = flags;
    m_status = HBitmapNode::LOAD_FAILED;
    if (!OpenReadTGA(bn, filename))
        return m_status;
    if (m_sbflags & HBitmapNode::LOADINFOONLY) {
        _close(m_infilenumber);
        return HBitmapNode::LOAD_OK;
    }
    if (!PrepareReadTGA())
        return m_status;
    if (m_embeddedgamma == 1.F)
        ReadTGA(bn);
    else
        ReadTGAGamma(bn);
    if (m_status == HBitmapNode::LOAD_FAILED)
        return m_status;
    FREE(m_data)
    FREE(m_colormap)
    FREE(m_buffer)
    FREE(m_row)
    _close(m_infilenumber);
    return m_status;
}
