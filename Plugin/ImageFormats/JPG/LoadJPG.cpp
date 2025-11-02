// YP  01/16/2005  \Plugin\Image Formats\JPG\Load.cpp

// ReSharper disable CppClangTidyCertErr33C
#include "StdAfx.h"
#include "SDK/Misc.h"
#include "SDK/HBitmap.h"
#include "RGBByte.h"
#include "RGBHalf.h"
#include "RGBHalf.inl"
#include "Custom.h"
#include "Matrix34.h"
#include "Files.h"

#include <cstdio>
#include <io.h>
#include <fcntl.h>

#define ErrorExit()           goto Error_Exit

static void JpegError(j_common_ptr cinfo) {
    [[maybe_unused]] auto myerr = (my_error_ptr)cinfo->err;
    (*cinfo->err->output_message)(cinfo);
    throw cinfo->err->msg_code;
}

bool CustomImageIO::OpenJpegR(const char *filename) {
    if (fopen_s(&m_infile, filename, "rb") != 0)
        return false;
    m_dinfo.err = jpeg_std_error(&m_jerr.pub);
    m_jerr.pub.error_exit = JpegError;
    try {
        jpeg_create_decompress(&m_dinfo);
        jpeg_stdio_src(&m_dinfo, m_infile);
        jpeg_read_header(&m_dinfo, TRUE);
        if (m_dinfo.num_components == 4)
            m_dinfo.out_color_space = JCS_RGB;
        jpeg_start_decompress(&m_dinfo);
        m_row_stride = m_dinfo.output_width * m_dinfo.output_components;
        m_jpegbuffer = (*m_dinfo.mem->alloc_sarray)((j_common_ptr)&m_dinfo, JPOOL_IMAGE, m_row_stride, 1);
    }
    catch (int) {
        jpeg_destroy_decompress(&m_dinfo);
        fclose(m_infile);
        return false;
    }
    return true;
}

bool CustomImageIO::GetJpegRow() {
    if (m_dinfo.output_scanline >= m_dinfo.output_height)
        return false;
    try {
        jpeg_read_scanlines(&m_dinfo, m_jpegbuffer, 1);
    }
    catch (int) {
        jpeg_destroy_decompress(&m_dinfo);
        fclose(m_infile);
        return false;
    }
    return true;
}

bool CustomImageIO::CloseJpegR(const bool loadinfoonly) {
    try {
        if (!loadinfoonly)
            jpeg_finish_decompress(&m_dinfo);
        jpeg_destroy_decompress(&m_dinfo);
    }
    catch (int) {
        jpeg_destroy_decompress(&m_dinfo);
        fclose(m_infile);
        return false;
    }
    fclose(m_infile);
    if (m_jerr.pub.num_warnings)
        return false;
    return true;
}

float CustomImageIO::UnGammaCorrect(const UBYTE value) {
    const float temp = (float)value / 255.0f;
    if (temp <= 0.03928)
        return temp / 12.92f;
    return hash_math::pow((temp + 0.055f) / 1.055f, 2.4f);
}

HBitmapBuffer *CustomImageIO::ReadJpeg() {
//    int x, y;
    HBitmapBuffer *buffer = nullptr;
//    RGBByte color;
//    UBYTE *pbits;

    switch (m_bytesperpixel) {
        case 1: // Grayscale
            if (m_ungammacorrect) {
                HScalarBuffer *scalarbuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_HALF, m_width, m_height);
                buffer = scalarbuffer;
                scalarbuffer->AllocateData();
                half *data = (half *)scalarbuffer->GetData();
                for (int y = 0; y < m_height; ++y) {
                    if (!GetJpegRow())
                        ErrorExit();
                    UBYTE *pbits = m_jpegbuffer[0];
                    for (int x = 0; x < m_width; x++, pbits++)
                        *(data + y * (int64_t)m_width + x) = (half)UnGammaCorrect(*pbits);
                }
                m_status = HBitmapNode::LOAD_OK;
            } else {
                HScalarBuffer *scalarbuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_UBYTE, m_width, m_height);
                buffer = scalarbuffer;
                scalarbuffer->AllocateData();
                auto *data = (UBYTE *)scalarbuffer->GetData();
                for (int y = 0; y < m_height; ++y) {
                    if (!GetJpegRow())
                        ErrorExit();
                    UBYTE *pbits = m_jpegbuffer[0];
                    for (int x = 0; x < m_width; x++, pbits++)
                        *(data + y * (int64_t)m_width + x) = *pbits;
                }
                m_status = HBitmapNode::LOAD_OK;
            }
            break;
        case 3:
        case 4: // Jpeg doesn't have alpha channels. 4 channels are CMYK or CYYK and are converted to RGB
            if (m_ungammacorrect) {
                HRGBBuffer *vec3buffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_HALF, m_width, m_height);
                buffer = vec3buffer;
                vec3buffer->AllocateData();
                auto *data = (RGBHalf *)vec3buffer->GetData();
                RGBFloat temp;
                for (int y = 0; y < m_height; ++y) {
                    if (!GetJpegRow())
                        ErrorExit();
                    UBYTE *pbits = m_jpegbuffer[0];
                    for (int x = 0; x < m_width; x++, pbits += 3) {
                        temp.SetRed(UnGammaCorrect(*pbits));
                        temp.SetGreen(UnGammaCorrect(*(pbits + 1)));
                        temp.SetBlue(UnGammaCorrect(*(pbits + 2)));
                        *(data + y * (int64_t)m_width + x) = RGBHalf(temp);
                    }
                }
                m_status = HBitmapNode::LOAD_OK;
            } else {
                HRGBBuffer *vec3buffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_UBYTE, m_width, m_height);
                buffer = vec3buffer;
                vec3buffer->AllocateData();
                auto *data = (RGBByte *)vec3buffer->GetData();
                for (int y = 0; y < m_height; ++y) {
                    if (!GetJpegRow())
                        ErrorExit();
                    UBYTE *pbits = m_jpegbuffer[0];
                    for (int x = 0; x < m_width; x++, pbits += 3)
                        *(data + y * (int64_t)m_width + x) = RGBByte(*pbits, *(pbits + 1), *(pbits + 2));
                }
                m_status = HBitmapNode::LOAD_OK;
            }
            break;
        default:
            return buffer;
    }

Error_Exit:
    if (m_status == HBitmapNode::LOAD_FAILED && buffer) {
        delete buffer;
        buffer = nullptr;
    }
    return buffer;
}

bool CustomImageIO::IsJPG(const int filenumber) {
    char type[10];

    _lseek(filenumber, 0L, SEEK_SET);
    if (_read(filenumber, type, (size_t)10) != 10)
        return false;
    if (type[6] != 'J' || type[7] != 'F' || type[8] != 'I' || type[9] != 'F')
        if (type[6] != 'E' || type[7] != 'x' || type[8] != 'i' || type[9] != 'f')
            return false;

    return true;
}

// ****************** Interface

bool CustomImageIO::CanLoadImage(const String &filename) {
    int filenumber;
    if (_sopen_s(&filenumber, filename.Get(), _O_RDONLY | _O_BINARY, _SH_DENYNO, _S_IREAD) != 0)
        return false;
    if (IsJPG(filenumber)) {
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
        } while (FileExists(endtest));
    }
}

long CustomImageIO::LoadFrame(HBitmapNode *bn, const String &filename, int frame/*=-1*/, const UINT flags /*= 0*/) {
    m_status = HBitmapNode::LOAD_FAILED;

    // YP COMEBACK: Handle frames
    if (!OpenJpegR(filename.Get()))
        return m_status;

    bn->SetWidth(m_width = m_dinfo.image_width);
    bn->SetHeight(m_height = m_dinfo.image_height);
    if (flags & HBitmapNode::LOADINFOONLY) {
        CloseJpegR(TRUE);
        return m_status = HBitmapNode::LOAD_OK;
    }

    m_bytesperpixel = m_dinfo.num_components;
    m_colorspace = m_dinfo.jpeg_color_space;
    // YP For compatibility with legacy jpeg used in A:M projects, we don't ungammacorrect by default.
    // But we need to find a way for the user to specify if he wants to ungammacorrect or not.
    // The most probable situation when loading jpeg files is that they are in the sRGB color space with a gamma of 2.2.
    // But jpeg does not store gamma or colorspace info.
    m_ungammacorrect = false;

    /* this was to fix a memory leak when finishing rendering a frame during render to file issue 2673
       but it caused an exception so it is now handeled below issue 2816
       if (flags & HBitmapNode::LOADINFOONLY) {
          CloseJpegR();
          return m_status = HBitmapNode::LOAD_OK;
       }
    */
    HBitmapBuffer *buffer = ReadJpeg();
    if (!buffer)
        return m_status;

    buffer->SetIsPremultipliedAlpha(FALSE);
    buffer->SetIsKeyBackground(FALSE); // With JPEG compression artifacts, background is not desirable.
    if (flags & HBitmapNode::LOADINFOONLY)
        delete buffer; //a shame we have to build it just to destroy it. see commented LOADINFOONLY above
    else
        bn->AddBuffer(buffer);
    CloseJpegR();
    return m_status;
}
