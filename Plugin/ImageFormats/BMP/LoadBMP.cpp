// WEP  3/4/2005  \will120\Plugin\Image Formats\BMP\Load.cpp

#include "StdAfx.h"
#include "RGBByte.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "Matrix34.h"
#include "IOApp.h"
#include "Files.h"

#include <io.h>
#include <fcntl.h>
#define ErrorExit()           goto Error_Exit
#define ALLOC( baz )          (UBYTE *)AllocBitmap((long)(baz) )
#define FREE( baz )           {if (baz){FreeBitmap( baz );(baz)=nullptr;}}

#define BUFFERSIZE            1024

extern CImageIOApp theApp;

inline UBYTE CustomImageIO::ReadBufferByte() {
    if (m_filled == 0) {
        if ((m_filled = _read(m_filenumber, m_data, (size_t)BUFFERSIZE)) == -1 || m_filled == 0) {
            m_status = HBitmapNode::LOAD_FAILED;
            return 0;
        }
        m_buf = m_data;
    } else
        ++m_buf;

    --m_filled;
    return *m_buf;
}

bool CustomImageIO::GetBMPRow() {
    //    SSHORT rlecount = 0;
    int indx;

    UBYTE *row = m_row;
    for (SSHORT x = 0; m_status && x < m_width; ++x) {
        switch (m_bytesperpixel) {
            case 1:
                indx = (int)ReadBufferByte();
                row[0] = m_palette[indx].rgbBlue;
                row[1] = m_palette[indx].rgbGreen;
                row[2] = m_palette[indx].rgbRed;
                row[3] = 0xFF;
                break;
            case 2: // YP COMEBACK: 5 bits each of red, green, blue. Check the order
                row[0] = ReadBufferByte();
                row[1] = ReadBufferByte();
                row[2] = (row[1] & 0x1F) << 3;
                row[1] >>= 2;
                row[1] |= (row[0] & 0x03) << 6;
                row[0] <<= 1;
                row[3] = 0xFF;
                break;
            case 3: // 8 bits each of red, green, blue
                row[0] = ReadBufferByte();
                row[1] = ReadBufferByte();
                row[2] = ReadBufferByte();
                row[3] = 0xFF;
                break;
            case 4: // 8 bits each of red, green, blue, alpha
                row[0] = ReadBufferByte();
                row[1] = ReadBufferByte();
                row[2] = ReadBufferByte();
                row[3] = ReadBufferByte();
                break;
            default:
                return false;
        }
        row += 4;
    }
    for (int p = 0; p < m_pad; p++) //bmps are padded to an even 4 bytes
        ReadBufferByte();
    return m_status = - HBitmapNode::LOAD_OK;
}

bool CustomImageIO::ReadBMP(HBitmapNode *bn, const int width, const int height) {

    try {
        HBitmapBuffer *buffer = nullptr;
        bool grey = false;
        UBYTE *row = nullptr;
        m_row = ALLOC((long)m_width * 4);
        if (m_bytesperpixel == 1) {
            if (m_bi.bmiHeader.biClrUsed)
                m_palentries = m_bi.bmiHeader.biClrUsed;
            else
                m_palentries = 256;
            const int palettesize = m_palentries * sizeof(RGBQUAD);
            if (_read(m_filenumber, &m_palette, palettesize) != palettesize)
                ErrorExit();
            grey = true;
            for (int i = 0; i < m_palentries; ++i)
                if (m_palette[i].rgbRed != m_palette[i].rgbGreen || m_palette[i].rgbGreen != m_palette[i].rgbBlue) {
                    grey = false;
                    break;
                }
        }
        if (m_bytesperpixel < 4) {
            if (grey) {
                // Paletted-greyscale values
                HScalarBuffer *scalarbuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_UBYTE, width, height);
                buffer = scalarbuffer;
                scalarbuffer->AllocateData();
                auto *data = (UBYTE *)scalarbuffer->GetData();
                bn->AddBuffer(scalarbuffer);
                m_status = HBitmapNode::LOAD_OK;
                for (int y = 0; y < height; ++y) {
                    if (!GetBMPRow())
                        ErrorExit();
                    row = m_row;
                    for (int x = 0; x < m_width; x++, row += 4) // GetBMPRow always fill 4 bytes rows.
                        *(data + (m_height - 1LL - y) * m_width + x) = row[0];
                }
            } else {
                // RGB values or Paletted-color values
                HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("RGB", HBitmapBuffer::CT_UBYTE, width, height);
                buffer = rgbbuffer;
                rgbbuffer->AllocateData();
                auto *data = (RGBByte *)rgbbuffer->GetData();
                bn->AddBuffer(rgbbuffer);
                m_status = HBitmapNode::LOAD_OK;
                for (int y = 0; y < m_height; ++y) {
                    if (!GetBMPRow())
                        ErrorExit();
                    row = m_row;
                    for (int x = 0; x < m_width; x++, row += 4) // GetBMPRow always fill 4 bytes rows.
                        *(data + (m_height - 1LL - y) * m_width + x) = RGBByte(row[2], row[1], row[0]);
                }
            }
        } else {
            HRGBABuffer *rgbabuffer = HBitmapNode::CreateRGBABuffer("RGBA", HBitmapBuffer::CT_UBYTE, width, height);
            buffer = rgbabuffer;
            rgbabuffer->AllocateData();
            auto *data = (RGBAByte *)rgbabuffer->GetData();
            bn->AddBuffer(rgbabuffer);
            m_status = HBitmapNode::LOAD_OK;
            for (int y = 0; y < m_height; ++y) {
                if (!GetBMPRow())
                    ErrorExit();
                row = m_row;
                for (int x = 0; x < m_width; x++, row += 4)
                    *(data + (m_height - 1LL - y) * m_width + x) = RGBAByte(row[2], row[1], row[0], row[4]);
            }
        }
        buffer->SetIsPremultipliedAlpha(FALSE);
        m_status = HBitmapNode::LOAD_OK;
        FREE(m_row)
        return true;
    }
    catch (CMemoryException &pMemEx) {
        pMemEx.Delete();
        TRACE(_T("Failed to allocate size of BMP\n"));
        //ASSERT->If this ASSERT fires, you have run out of memory
        ASSERT(FALSE);
    }

Error_Exit:
    FREE(m_row)
    return false;
}

bool CustomImageIO::IsBMP(const int filenumber) {
    _lseek(filenumber, 0L, SEEK_SET);

    BITMAPFILEHEADER header;
    if (_read(filenumber, &header, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
        return false;

    if (header.bfType != 0x4d42) // BM
        return false;
    return true;
}

// ****************** Interface

bool CustomImageIO::CanLoadImage(const String &filename) {
    int filenumber;
    if (_sopen_s(&filenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return false;
    if (IsBMP(filenumber)) {
        _close(filenumber);
        return true;
    }
    _close(filenumber);
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
    int pfilenumber; //NAP Bitmap COME-back handle frame
    m_status = HBitmapNode::LOAD_FAILED;
    if (_sopen_s(&pfilenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return m_status;

    m_filenumber = pfilenumber;
    m_flags = flags;
    _lseek(m_filenumber, 0L, SEEK_SET);
    if (_read(m_filenumber, &m_header, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER)) {
        // YP COMEBACK: Question! I've added _close(file) everywhere. There was none originally. Was this normal?
        _close(m_filenumber);
        return m_status;
    }
    if (_read(m_filenumber, &m_bi.bmiHeader, sizeof m_bi.bmiHeader) != sizeof m_bi.bmiHeader) {
        _close(m_filenumber);
        return m_status;
    }

    m_width = m_bi.bmiHeader.biWidth;
    bn->SetWidth(m_width);
    m_height = m_bi.bmiHeader.biHeight;
    bn->SetHeight(m_height);
    if ((m_bytesperpixel = m_bi.bmiHeader.biBitCount / 8) == 0) {
        _close(m_filenumber);
        return m_status;
    }
    m_pad = 4 - m_bytesperpixel * m_width % 4 & 3;
    //bn->SetBackground( RGBFloat(1.F,1.F,1.F) ); //now on the buffer, defaults to false, and why set color if its false
    //bn->SetHasBackground( false ); //default, and now on the buffer

    if (m_flags & HBitmapNode::LOADINFOONLY) {
        _close(m_filenumber);
        return HBitmapNode::LOAD_OK;
    }
    if ((m_data = ALLOC(BUFFERSIZE)) == nullptr) {
        _close(m_filenumber);
        return m_status;
    }
    m_filled = 0;
    if (!ReadBMP(bn, bn->GetWidth(), bn->GetHeight()))
        bn->DeleteAllBuffers();
    _close(m_filenumber);
    FREE(m_data)
    return m_status;
}
