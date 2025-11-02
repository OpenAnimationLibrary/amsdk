// YP  01/20/2005  \Plugin\Image Formats\PNG\Save.cpp

// ReSharper disable CppClangTidyBugproneImplicitWideningOfMultiplicationResult
// ReSharper disable CppClangTidyModernizeUseAuto
#include "StdAfx.h"
#include "RGBByte.h"
#include "Custom.h"
#include "IOApp.h"
#include "Files.h"
#include "zlib.h"
#include <fcntl.h>

extern CImageIOApp theApp;

namespace {
    void PngError(png_structp png_ptr, png_const_charp msg) {
        throw std::exception(msg);
    }
}

bool CustomImageIO::OpenPngW(const char *filename, HOutputInfo *outputinfo) {
    if (fopen_s(&m_outfile, filename, "wb") != 0)
        return false;

    m_png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, PngError, nullptr);
    if (m_png_ptr == nullptr) {
        [[maybe_unused]] int rcv = fclose(m_outfile);
        return false;
    }
    m_info_ptr = png_create_info_struct(m_png_ptr);
    if (m_info_ptr == nullptr) {
        [[maybe_unused]] int rcv = fclose(m_outfile);
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
        return false;
    }
    try {
        png_init_io(m_png_ptr, m_outfile);
        png_set_IHDR(m_png_ptr, m_info_ptr, m_width, m_height, m_bitdepth, m_colortype, m_interlace, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        switch (theApp.m_compression) {
        case 1:
            png_set_compression_level(m_png_ptr, Z_BEST_SPEED);
            break;
        case 2:
            png_set_compression_level(m_png_ptr, Z_BEST_COMPRESSION);
            break;
        default:
            png_set_compression_level(m_png_ptr, Z_NO_COMPRESSION);
            break;
        }
        if (m_outgammapreset != GAMMA_NONE) {
            if (m_outgammapreset == GAMMA_NTSC)
                png_set_sRGB_gAMA_and_cHRM(m_png_ptr, m_info_ptr, m_srgbintent);
            else
                png_set_gAMA(m_png_ptr, m_info_ptr, m_outgamma);
        }
        {
            char key0[] = "Author";
            m_text_ptr[0].key = key0;
            String user = outputinfo->GetUser();
            if (user.IsEmpty())
                user = "author";
            m_text_ptr[0].text = (png_charp)user.Get_const_char();
            m_text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
            char key1[] = "Organisation";
            m_text_ptr[1].key = key1;
            String organization = outputinfo->GetOrganization();
            if (organization.IsEmpty())
                organization = "organisation";
            m_text_ptr[1].text = (png_charp)organization.Get_const_char();
            m_text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
            char key2_0[] = "Application";
            m_text_ptr[2].key = key2_0;
            char key2_1[] = "Animation:Master";
            m_text_ptr[2].text = key2_1;
            m_text_ptr[2].compression = PNG_TEXT_COMPRESSION_NONE;
            png_set_text(m_png_ptr, m_info_ptr, m_text_ptr, 3);
        }
        png_write_info(m_png_ptr, m_info_ptr);
        if (m_interlace == PNG_INTERLACE_NONE)
            m_nbpasses = 1;
        else
            m_nbpasses = png_set_interlace_handling(m_png_ptr);
        if (m_bitdepth == 16)
            png_set_swap(m_png_ptr);
        return true;
    }
    catch (const std::exception &e) {
        const String msg = "PNG IIO\nSave Error :\n"+ String(filename)+"\n"+(String)e.what();
        AfxMessageBox(msg.Get(),MB_ICONERROR);
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
        [[maybe_unused]] int rcv = fclose(m_outfile);
        [[maybe_unused]] int rcv1 = remove(filename);
    }
    return false;
}

HBitmapNode::WriteStatus CustomImageIO::ClosePngW() {
    HBitmapNode::WriteStatus status = HBitmapNode::WRITE_OK;
    try {
        png_write_end(m_png_ptr, m_info_ptr);
        png_destroy_write_struct(&m_png_ptr, &m_info_ptr);
    }
    catch (const std::exception &e) {
        [[maybe_unused]] char const *msg = e.what();
        status = HBitmapNode::WRITE_ERROR;
    }
    if (fclose(m_outfile))
        status = HBitmapNode::WRITE_ERROR;
    return status;
}

/*
 DON'T swap , is done now in the lib
inline USHORT FloatToWord(const float value) {
    // Beware. This swaps the bytes to big-endian for PNG
    USHORT temp = MAX(0, MIN(65535, fast_ftol_unsigned(value * 65535.0f + .5f)));
    temp = ((temp & 0xFF) << 8) + ((temp & 0xFF00) >> 8);
    return temp;
}
*/

__forceinline USHORT FloatToWord(const float value) {
    const USHORT temp = MAX(0, MIN(65535, fast_ftol_unsigned(value * 65535.0F + .5F)));
    return temp;
}

USHORT CustomImageIO::GammaCorrectW(float value) const {
    if (m_outgammapreset == GAMMA_NTSC) {
        if (value <= 0.00304F)
            value *= 12.92F;
        else
            value = hash_math::pow(value, 1.F / 2.4F);
    } else {
        if (m_outgamma != 1.F)
            value = hash_math::pow(value, hash_math::rcp(m_outgamma));
    }
    return FloatToWord(value);
}

UBYTE CustomImageIO::GammaCorrectB(float value) const {
    if (m_outgammapreset == GAMMA_NTSC) {
        if (value <= 0.00304F)
            value *= 12.92F;
        else
            value = hash_math::pow(value, 1.F / 2.4F);
    } else {
        if (m_outgamma != 1.F)
            value = hash_math::pow(value, hash_math::rcp(m_outgamma));
    }
    return FLOATTOBYTE(value);
}

HBitmapNode::WriteStatus CustomImageIO::WritePng(HBitmapNode *bn) const {
    HBitmapNode::WriteStatus status = HBitmapNode::WRITE_ERROR;
    if (m_bitdepth == 8) {
        png_byte *image = new png_byte[m_height * m_width * m_bytesperpixel];
        png_bytep *row_pointers = new png_bytep[m_height];
        switch (m_bytesperpixel) {
        case 1:
        {
            for (int y = 0; y < m_height; ++y) {
                RGBFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectB(color.Red());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        case 2:
        {
            for (int y = 0; y < m_height; ++y) {
                YAFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectB(color.Luminance());
                    if (m_colortype == PNG_COLOR_TYPE_GRAY_ALPHA)
                        image[pos + 1] = FLOATTOBYTE(color.Alpha());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        case 3:
        {
            for (int y = 0; y < m_height; ++y) {
                RGBFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectB(color.Red());
                    image[pos + 1] = GammaCorrectB(color.Green());
                    image[pos + 2] = GammaCorrectB(color.Blue());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        case 4:
        {
            for (int y = 0; y < m_height; ++y) {
                RGBAFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectB(color.Red());
                    image[pos + 1] = GammaCorrectB(color.Green());
                    image[pos + 2] = GammaCorrectB(color.Blue());
                    image[pos + 3] = FLOATTOBYTE(color.Alpha());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        default: 
            ASSERT(false);
            break;
        }

        try {
            for (int k = 0; k < m_height; k++)
                row_pointers[k] = k * m_width * m_bytesperpixel + image;
            png_write_image(m_png_ptr, row_pointers);
        }
        catch (const std::exception &e) {
            const String msg = "PNG IIO\nSave Error :\n" + (String)e.what();
            AfxMessageBox(msg.Get(), MB_ICONERROR);
            status = HBitmapNode::WRITE_ERROR;
        }
        delete [] row_pointers;
        delete [] image;
    } else {
        png_uint_16 *image = new png_uint_16[m_height * m_width * m_bytesperpixel];
        png_uint_16p *row_pointers = new png_uint_16p[m_height];
        switch (m_bytesperpixel) {
        case 1:
        {
            for (int y = 0; y < m_height; ++y) {
                RGBFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectW(color.Red());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        case 2:
        {
            for (int y = 0; y < m_height; ++y) {
                YAFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectW(color.Luminance());
                    if (m_colortype == PNG_COLOR_TYPE_GRAY_ALPHA)
                        image[pos + 1] = FloatToWord(color.Alpha());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        case 3:
        {
            for (int y = 0; y < m_height; ++y) {
                RGBFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectW(color.Red());
                    image[pos + 1] = GammaCorrectW(color.Green());
                    image[pos + 2] = GammaCorrectW(color.Blue());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        case 4:
        {
            for (int y = 0; y < m_height; ++y) {
                RGBAFloat color;
                const int current_y = y * m_width * m_bytesperpixel;
                for (int x = 0; x < m_width; ++x) {
                    bn->ReadPixel(x, y, color);
                    const int pos = current_y + x * m_bytesperpixel;
                    image[pos] = GammaCorrectW(color.Red());
                    image[pos + 1] = GammaCorrectW(color.Green());
                    image[pos + 2] = GammaCorrectW(color.Blue());
                    image[pos + 3] = FloatToWord(color.Alpha());
                }
            }
            status = HBitmapNode::WRITE_OK;
            break;
        }
        default: 
            ASSERT(false);
            break;
        }
        try {
            for (int k = 0; k < m_height; k++)
                row_pointers[k] = k * m_width * m_bytesperpixel + image;
            png_write_image(m_png_ptr, (png_bytepp)row_pointers);
        }
        catch (const std::exception &e) {
            const String msg = "PNG IIO\nSave Error :\n" + (String)e.what();
            AfxMessageBox(msg.Get(), MB_ICONERROR);
            status = HBitmapNode::WRITE_ERROR;
        }

        delete [] row_pointers;
        delete [] image;
    }
    return status;
}

long CustomImageIO::WriteFrame(HBitmapNode *bn, HOutputInfo *outputinfo, const String &filename, short *wavedata, bool hasaudio) {
    if (filename.GetSuffixOnly() != "png")
        return HBitmapNode::WRITE_NORESULT;
    MakeDirPath(filename);
    [[maybe_unused]] int error = Remove(filename);

    HBitmapBuffer *bufferhead = bn->GetBufferHead();
    m_outgammapreset = (GammaType)outputinfo->GetGammaPreset();
    m_outgamma = outputinfo->GetOutputGamma();
    m_bytesperpixel = bufferhead->GetNbrChannels();
    switch (m_bytesperpixel) {
    case 1:
        m_colortype = PNG_COLOR_TYPE_GRAY;
        break;
    case 2:
        if (outputinfo->GetIsAlpha())
            m_colortype = PNG_COLOR_TYPE_GRAY_ALPHA;
        else
            m_colortype = PNG_COLOR_TYPE_GRAY;
        break;
    case 3:
        m_colortype = PNG_COLOR_TYPE_RGB;
        break;
    case 4:
        if (outputinfo->GetIsAlpha())
            m_colortype = PNG_COLOR_TYPE_RGB_ALPHA;
        else {
            m_colortype = PNG_COLOR_TYPE_RGB;
            m_bytesperpixel = 3;
        }
        break;
    default: 
        break;
    }
    m_srgbintent = PNG_sRGB_INTENT_PERCEPTUAL; // PNG_sRGB_INTENT_SATURATION, PNG_sRGB_INTENT_ABSOLUTE, PNG_sRGB_INTENT_RELATIVE;
    m_width = bn->GetWidth();
    m_height = bn->GetHeight();
    m_bitdepth = theApp.m_8bit ? 8 : 16; // selected from the compression dialog
    m_interlace = theApp.m_interlaced ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE; // Selected from the compression dialog.
    if (!OpenPngW(filename.Get(), outputinfo))
        return HBitmapNode::WRITE_ERROR;
    int status = WritePng(bn);
    status |= ClosePngW();
    if (status == HBitmapNode::WRITE_ERROR)
        [[maybe_unused]] int rcv1 = remove(filename.Get());
    return status;
}
