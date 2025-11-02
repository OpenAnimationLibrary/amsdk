// YP  01/10/2005  \Plugin\Image Formats\JPG\Save.cpp

#include "StdAfx.h"
#include "RGBByte.h"
#include "Custom.h"
#include "IOApp.h"
#include "Files.h"

#include <fcntl.h>
#define ErrorExit()           goto Error_Exit

extern CImageIOApp theApp;

static void JpegError(j_common_ptr cinfo) {
    [[maybe_unused]] auto myerr = (my_error_ptr)cinfo->err;
    (*cinfo->err->output_message)(cinfo);
    throw cinfo->err->msg_code;
}

bool CustomImageIO::OpenJpegW(const char *filename) {
    if (fopen_s(&m_outfile, filename, "wb") != 0)
        return false;

    m_cinfo.err = jpeg_std_error(&m_jerr.pub);
    m_jerr.pub.error_exit = JpegError;
    try {
        jpeg_create_compress(&m_cinfo);
        jpeg_stdio_dest(&m_cinfo, m_outfile);

        m_cinfo.image_width = m_width;
        m_cinfo.image_height = m_height;
        m_cinfo.input_components = m_bytesperpixel == 1 ? 1 : 3;
        m_cinfo.in_color_space = m_bytesperpixel == 1 ? JCS_GRAYSCALE : JCS_RGB;
        jpeg_set_defaults(&m_cinfo);
        jpeg_set_quality(&m_cinfo, theApp.m_compression, TRUE);
        m_cinfo.optimize_coding = theApp.m_optimal;
        jpeg_simple_progression(&m_cinfo);
        jpeg_start_compress(&m_cinfo, TRUE);

        m_row_stride = m_cinfo.image_width * m_cinfo.input_components;
        m_jpegbuffer = (*m_cinfo.mem->alloc_sarray)((j_common_ptr)&m_cinfo, JPOOL_IMAGE, m_row_stride, 1);
    }
    catch (int) {
        jpeg_destroy_compress(&m_cinfo);
        fclose(m_outfile);
        return false;
    }
    return true;
}

bool CustomImageIO::SetJpegRow() {
    if (m_cinfo.next_scanline >= m_cinfo.image_height)
        return false;
    try {
        jpeg_write_scanlines(&m_cinfo, m_jpegbuffer, 1);
    }
    catch (int) {
        jpeg_destroy_compress(&m_cinfo);
        fclose(m_outfile);
        return false;
    }
    return true;
}

bool CustomImageIO::CloseJpegW() {
    try {
        jpeg_finish_compress(&m_cinfo);
        jpeg_destroy_compress(&m_cinfo);
    }
    catch (int) {
        jpeg_destroy_compress(&m_cinfo);
        fclose(m_outfile);
        return false;
    }
    fclose(m_outfile);
    if (m_jerr.pub.num_warnings)
        return false;
    return true;
}

BYTE CustomImageIO::GammaCorrect(float value) const {
    if (m_gammapreset == GAMMA_NTSC)
        if (value <= 0.00304f)
            value *= 12.92f;
        else
            value = hash_math::pow(value, 1.F / 2.4f);
    else if (m_gammacorrection != 1.F)
        value = hash_math::pow(value, hash_math::rcp(m_gammacorrection));
    return FLOATTOBYTE(value);
}

bool CustomImageIO::WriteJpeg(HBitmapNode *bn) {
    auto *buffer = (UBYTE *)AllocBitmap(sizeof(RGBByte) * m_width);
    auto *rgbbuf = (RGBByte *)buffer;
    m_jpegbuffer = &buffer;

    m_status = HBitmapNode::WRITE_ERROR;
    switch (m_bytesperpixel) {
        case 1: // Grayscale
        {
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    RGBFloat color;
                    bn->ReadPixel(x, y, color);
                    // Grayscale are not gamma corrected
                    buffer[x] = FLOATTOBYTE(color.Red());
                }
                if (!SetJpegRow())
                    ErrorExit();
            }
            m_status = HBitmapNode::WRITE_OK;
            break;
        }
        case 3: // RGB
        {
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    RGBFloat color;
                    bn->ReadPixel(x, y, color);
                    rgbbuf[x].SetBlue(GammaCorrect(color.Red()));
                    rgbbuf[x].SetGreen(GammaCorrect(color.Green()));
                    rgbbuf[x].SetRed(GammaCorrect(color.Blue()));
                }
                if (!SetJpegRow())
                    ErrorExit();
            }
            m_status = HBitmapNode::WRITE_OK;
            break;
        }
        case 4: // RGBA. But jpeg does not support alpha channels
        {
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    RGBAFloat color;
                    bn->ReadPixel(x, y, color);
                    rgbbuf[x].SetBlue(GammaCorrect(color.Red()));
                    rgbbuf[x].SetGreen(GammaCorrect(color.Green()));
                    rgbbuf[x].SetRed(GammaCorrect(color.Blue()));
                }
                if (!SetJpegRow())
                    ErrorExit();
            }
            m_status = HBitmapNode::WRITE_OK;
            break;
        }
        default:
            ASSERT(false);
    }

Error_Exit:
    if (buffer) {
        FreeBitmap(buffer);
        buffer = nullptr;
    }
    m_jpegbuffer = nullptr;
    return m_status;
}

long CustomImageIO::WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) {
    if (filename.GetSuffixOnly() != "jpg" && filename.GetSuffixOnly() != "jpeg")
        return HBitmapNode::WRITE_NORESULT;
    HBitmapBuffer *bufferhead = bn->GetBufferHead();
    m_gammapreset = (GammaType)outputinfo->GetGammaPreset();
    m_gammacorrection = outputinfo->GetOutputGamma();
    m_bytesperpixel = bufferhead->GetNbrChannels();

    MakeDirPath(filename);
    [[maybe_unused]] int error = Remove(filename);

    m_width = bn->GetWidth();
    m_height = bn->GetHeight();
    if (!OpenJpegW(filename.Get()))
        return HBitmapNode::WRITE_ERROR;
    WriteJpeg(bn);
    CloseJpegW();
    return HBitmapNode::WRITE_OK;
}
