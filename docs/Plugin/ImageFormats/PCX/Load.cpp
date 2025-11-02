// WEP  3/4/2005  \will120\Plugin\Image Formats\PCX\Load.cpp

#include "StdAfx.h"
#include "SDK/Misc.h"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "Matrix34.h"
#include "Files.h"
#include "Macros.h"
#include <io.h>
#include <fcntl.h>

#define ErrorExit()           goto Error_Exit

UBYTE CustomImageIO::ReadBufferByte() {
    if (m_filled == 0) {
        if ((m_filled = _read(m_filenumber, m_data, BUFFERSIZE)) == -1) {
            m_status = HBitmapNode::LOAD_FAILED;
            return 0;
        }
        m_buf = m_data;
    } else
        ++m_buf;

    --m_filled;
    return *m_buf;
}

bool CustomImageIO::ReadPCXLine(UBYTE *row) {
    int x = 0;

    do {
        UBYTE c = ReadBufferByte();
        if ((c & 0xC0) == 0xC0) {
            int i = c & 0x3F;
            c = ReadBufferByte();
            for (; i > 0 && m_status == HBitmapNode::LOAD_OK && x < m_bytes; --i, ++x) {
                row[x] = c;
            }
        } else
            row[x++] = c;
    } while (m_status == HBitmapNode::LOAD_OK && x < m_bytes);
    return m_status == HBitmapNode::LOAD_OK;
}

bool CustomImageIO::Read16PCXLine(UBYTE *planeptr) {
    int x = 0;

    do {
        UBYTE c = ReadBufferByte();
        if ((c & 0xC0) == 0xC0) {
            int i = c & 0x3F;
            c = ReadBufferByte();
            for (; i > 0 && m_status == HBitmapNode::LOAD_OK && x < m_bytes; --i, ++x) {
                *planeptr = c;
                planeptr++;
            }
        } else {
            *planeptr = c;
            planeptr++;
            ++x;
        }
    } while (m_status == HBitmapNode::LOAD_OK && x < m_bytes);
    return m_status == HBitmapNode::LOAD_OK;
}

bool CustomImageIO::Read24PCXLine(UBYTE *row, int y, const bool encoding) {
    long x = 0;
    UBYTE c;

    if (encoding) {
        do {
            c = ReadBufferByte();
            if ((c & 0xC0) == 0xC0) {
                int i = c & 0x3F;
                c = ReadBufferByte();
                while (i--) {
                    if (x < m_width3)
                        row[x] = c;
                    ++x;
                }
            } else {
                if (x < m_width3)
                    row[x] = c;
                ++x;
            }
        } while (x < m_bytes3);
    } else {
        do {
            c = ReadBufferByte();
            row[x] = c;
            ++x;
        } while (x < m_bytes3);
    }
    return m_status == HBitmapNode::LOAD_OK;
}

HBitmapBuffer *CustomImageIO::UnpackPCXFile(HBitmapNode *bn) {
    UBYTE *row = ALLOC(m_width);
    final_act _f1([&] { FREE(row) });

    HRGBBuffer *vec3buffer = HBitmapNode::CreateRGBBuffer("RGB", HBitmapBuffer::CT_UBYTE, m_width, m_height);
    if (!vec3buffer) {
        return nullptr;
    }
    vec3buffer->AllocateData();
    auto *data = (RGBByte *)vec3buffer->GetData();
    m_status = HBitmapNode::LOAD_OK;
    bn->AddBuffer(vec3buffer);
    HBitmapBuffer *buffer = vec3buffer;
    for (int y = 0; y < m_height; ++y) {
        if (!ReadPCXLine(row)) {
            delete buffer;
            return nullptr;
        }
        UBYTE *col = row;
        for (int x = 0; x < m_width; x++, col++) {
            const int pal = *col * 3;
            *data = RGBByte(m_palette[pal], m_palette[pal + 1], m_palette[pal + 2]);
            data++;
        }
    }
    m_status = HBitmapNode::LOAD_OK;
    return buffer;
}

RGBByte CustomImageIO::GetPixel(const UBYTE *ptr, const int x) const {
    UINT pal = 0;

    const int bitmask = 1 << (7 - (x & 7));
    const int fillbit = 1 << (m_depth - 1);

    for (int i = 0; i < m_depth; ++i) {
        pal = pal >> 1;
        if (*ptr & bitmask)
            pal |= fillbit;
        ptr += m_bytes;
    }
    pal *= 3;
    const RGBByte color = RGBByte(m_palette[pal], m_palette[pal + 1], m_palette[pal + 2]);
    return color;
}

HBitmapBuffer *CustomImageIO::Unpack16PCXFile(HBitmapNode *bn) {
    UBYTE *row = ALLOC(m_bytes*4);
    final_act _f1([&] { FREE(row) });

    HRGBBuffer *vec3buffer = HBitmapNode::CreateRGBBuffer("RGB", HBitmapBuffer::CT_UBYTE, m_width, m_height);
    if (!vec3buffer) {
        return nullptr;
    }
    vec3buffer->AllocateData();
    auto *data = (RGBByte *)vec3buffer->GetData();
    m_status = HBitmapNode::LOAD_OK;
    bn->AddBuffer(vec3buffer);
    HBitmapBuffer *buffer = vec3buffer;
    for (int y = 0; y < m_height; ++y) {
        UBYTE *bits = row;
        if (!Read16PCXLine(bits))
            ErrorExit();
        if (m_depth >= 2) {
            bits += m_bytes;
            if (!Read16PCXLine(bits))
                ErrorExit();
        }
        if (m_depth >= 3) {
            bits += m_bytes;
            if (!Read16PCXLine(bits))
                ErrorExit();
        }
        if (m_depth == 4) {
            bits += m_bytes;
            if (!Read16PCXLine(bits))
                ErrorExit();
        }
        bits = row;
        for (int x = 0; x < m_width; ++x) {
            *data = GetPixel(bits, x);
            data++;
            if ((x & 7) == 7)
                bits++;
        }
    }
    return buffer;

Error_Exit:
    delete buffer;
    return nullptr;
}

HBitmapBuffer *CustomImageIO::Unpack24PCXFile(HBitmapNode *bn, const bool encoding) {
    UBYTE *row = ALLOC((long)m_width * 3);
    final_act _f1([&] { FREE(row) });

    HRGBBuffer *vec3buffer = HBitmapNode::CreateRGBBuffer("RGB", HBitmapBuffer::CT_UBYTE, m_width, m_height);
    if (!vec3buffer) {
        return nullptr;
    }
    vec3buffer->AllocateData();
    auto *data = (RGBByte *)vec3buffer->GetData();
    m_status = HBitmapNode::LOAD_OK;
    bn->AddBuffer(vec3buffer);
    HBitmapBuffer *buffer = vec3buffer;
    for (int y = 0; y < m_height; ++y) {
        if (!Read24PCXLine(row, y, encoding)) {
            delete buffer;
            return nullptr;
        }
        UBYTE *col = row;
        for (int x = 0; x < m_width; x++, col++) {
            *data = RGBByte(col[0], col[m_width], col[m_width2]);
            data++;
        }
    }
    return buffer;
}

#define MANUFACTURER			0x0A

bool CustomImageIO::IsPCX(const int filenumber) {
    char type;
    const int rvalue = _lseek(filenumber, 0L, SEEK_SET);
    if (rvalue == -1)
        return false;
    if (_read(filenumber, &type, 1) == -1)
        return false;
    if (type != MANUFACTURER)
        return false;
    return true;
}

// ****************** Interface

bool CustomImageIO::CanLoadImage(const String &filename) {
    int filenumber;
    if (_sopen_s(&filenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return false;
    if (IsPCX(filenumber)) {
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
    //NAP Bitmap COME-back handle frame
    int pfilenumber;
    if (_sopen_s(&pfilenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return HBitmapNode::LOAD_FAILED;
    m_filenumber = pfilenumber;
    m_status = HBitmapNode::LOAD_FAILED;
    // YP Comeback: Remove this unnecessary protection when file type check is fixed
    m_data = nullptr;
    if (!IsPCX(m_filenumber))
        ErrorExit();

    _lseek(m_filenumber, 0L, SEEK_SET);
    if (_read(m_filenumber, &m_header, sizeof(PCXHEAD)) != sizeof(PCXHEAD))
        ErrorExit();
    if (m_header.manufacturer != 0x0A)
        ErrorExit();
    m_flags = flags;

    m_width = m_header.xmax - m_header.xmin + 1;
    m_height = m_header.ymax - m_header.ymin + 1;
    bn->SetWidth(m_width);
    bn->SetHeight(m_height);
    /*
   if (m_flags & BitmapNode::LOADBKCOLOR) {
      bn.m_background.Set(255,255,255);
      bn.m_hasbackground = false;
   }
   */
    // YP Comeback: Do that for other format too.
    if (m_flags & HBitmapNode::LOADINFOONLY) {
        m_status = HBitmapNode::LOAD_OK;
        ErrorExit();
    }
    m_data = ALLOC(BUFFERSIZE);
    m_filled = 0;
    m_bytes = m_header.bytesperline;
    m_bytes3 = m_bytes * 3;
    m_depth = (unsigned char)m_header.colorplanes;
    m_width2 = m_width * 2;
    m_width3 = m_width * 3;

    HBitmapBuffer *buffer;
    if (m_header.bitsperpixel == 8 && m_depth == 3) {
        // RGB
        m_bytesperpixel = 3;
        _lseek(m_filenumber, PCXHEADER, SEEK_SET);
        buffer = Unpack24PCXFile(bn, m_header.encoding);
        if (m_status != HBitmapNode::LOAD_OK)
            ErrorExit();
    } else {
        SBYTE id;
        m_bytesperpixel = 1;
        _lseek(m_filenumber, -(PALETTEBYTES + 1), SEEK_END);
        if (_read(m_filenumber, &id, sizeof(UBYTE)) != 1)
            ErrorExit();
        if (id == 0x0C) {
            // That's a 256 color VGA palette
            if (_read(m_filenumber, &m_palette, (size_t)PALETTEBYTES) != PALETTEBYTES)
                ErrorExit();
            _lseek(m_filenumber, PCXHEADER, SEEK_SET);
            buffer = UnpackPCXFile(bn);
            if (m_status != HBitmapNode::LOAD_OK)
                ErrorExit();
        } else {
            // We have a 16 color EGA palette
            for (int i = 0; i < 3 * 16; ++i)
                m_palette[i] = m_header.palette[i];
            _lseek(m_filenumber, PCXHEADER, SEEK_SET);
            buffer = Unpack16PCXFile(bn);
            if (m_status != HBitmapNode::LOAD_OK)
                ErrorExit();
        }
    }

    if (buffer && m_status == HBitmapNode::LOAD_OK) {
        buffer->SetIsPremultipliedAlpha(FALSE); // undid multiply when pixels were read in ReadTGA
        /*
                if (m_status == HBitmapNode::LOAD_OK) {
                    //         bn->AddBuffer(buffer);
                    // YP Comeback: What about this
                    //    UnGammaCorrect();
                    //    if (m_iscompressed) 
                    //       Compress();
                    //buffer->DetectBackground(); //NAP Bitmpa COMEBACK
                } else
                    delete buffer;
                    */
    } else {
        delete buffer;
    }

Error_Exit:
    _close(m_filenumber);
    FREE(m_data)
    return m_status;
}
