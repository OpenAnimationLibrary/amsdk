// Yves  10/12/2004  \Yves115\Plugin\Image Formats\PNG\Load.cpp

// ReSharper disable CppClangTidyCertErr33C
// ReSharper disable CppClangTidyModernizeUseAuto
#include "StdAfx.h"
#include "SDK/HBitmap.h"
#include "RGBByte.h"
#include "RGBHalf.h"
#include "Custom.h"
#include "Matrix34.h"
#include "IOApp.h"
#include "Files.h"
#include "RGBHalf.inl"
//#include <cstdio>
#include <fcntl.h>

namespace {
    void PngError(png_structp png_ptr, png_const_charp msg) {
        throw std::exception(msg);
    }
}

bool CustomImageIO::OpenPng(const char *filename) {
    if (fopen_s(&m_infile, filename, "rb") != 0)
        return false;

    m_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, PngError, nullptr);
    if (!m_png_ptr) {
        fclose(m_infile);
        return false;
    }
    m_info_ptr = png_create_info_struct(m_png_ptr);
    if (!m_info_ptr) {
        png_destroy_read_struct(&m_png_ptr, nullptr, nullptr);
        fclose(m_infile);
        return false;
    }
    try {
        png_init_io(m_png_ptr, m_infile);
        png_read_info(m_png_ptr, m_info_ptr);
        png_get_IHDR(m_png_ptr, m_info_ptr, (png_uint_32*)&m_width, (png_uint_32*)&m_height, &m_bitdepth, &m_colortype, nullptr, nullptr, nullptr);
        if (m_colortype == PNG_COLOR_TYPE_PALETTE)
            png_set_expand(m_png_ptr);
        if (m_bitdepth < 8)
            png_set_expand(m_png_ptr);
        if (m_bitdepth == 16)
            png_set_swap(m_png_ptr);
        if (png_get_valid(m_png_ptr, m_info_ptr, PNG_INFO_tRNS))
            png_set_expand(m_png_ptr);
        m_hasbackground = false;
        m_channels = png_get_channels(m_png_ptr, m_info_ptr);
        if (m_channels == 1 || m_channels == 3) {
            //no alpha channel, needs a background 
            if (png_get_bKGD(m_png_ptr, m_info_ptr, &m_background)) {
                // YP Comeback: Handle 16 to half backgrounds.
                png_set_background(m_png_ptr, m_background, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
                if (m_bitdepth > 8)
                    m_bkgcolor = RGBFloat(m_background->red / 65535.0F, m_background->green / 65535.0F, m_background->blue / 65535.0F); //NAP Bitmap huh this is 0-1?
                else
                    m_bkgcolor = RGBFloat(m_background->red / 255.0F, m_background->green / 255.0F, m_background->blue / 255.0F); //NAP Bitmap huh this is 0-1?
                m_hasbackground = true;
            }
        }
        m_ingammapreset = GAMMA_NONE;
        m_ingamma = 1.F;
        int intent; // Actually just a dummy.
        if (png_get_sRGB(m_png_ptr, m_info_ptr, &intent)) {
            png_set_gamma(m_png_ptr, 2.2, PNG_DEFAULT_sRGB);
            m_ingammapreset = GAMMA_NTSC;
            m_ingamma = 2.2f;
        } else {
            double image_gamma;
            const double screen_gamma = GetScreenGamma();
            if (png_get_gAMA(m_png_ptr, m_info_ptr, &image_gamma) != 0)
                png_set_gamma(m_png_ptr, screen_gamma, image_gamma);
            else
                png_set_gamma(m_png_ptr, screen_gamma, 0.45455);
        }
        m_nbpasses = png_set_interlace_handling(m_png_ptr);
        png_read_update_info(m_png_ptr, m_info_ptr);
        png_get_IHDR(m_png_ptr, m_info_ptr, (png_uint_32*)&m_width, (png_uint_32*)&m_height, &m_bitdepth, &m_colortype, nullptr, nullptr, nullptr);
        m_channels = png_get_channels(m_png_ptr, m_info_ptr);
        return true;
    }
    catch (const std::exception &e) {
        const String msg = "PNG IIO\nLoad Error :\n"+ String(filename)+"\n"+(String)e.what();
        AfxMessageBox(msg.Get(),MB_ICONERROR);
        png_destroy_read_struct(&m_png_ptr, &m_info_ptr, nullptr);
        fclose(m_infile);
    }
    return false;
}

HBitmapNode::LoadStatus CustomImageIO::ClosePng(const bool loadinfoonly) {
    try {
        if (!loadinfoonly)
            png_read_end(m_png_ptr, m_info_ptr);
        png_destroy_read_struct(&m_png_ptr, &m_info_ptr, nullptr);
    }
    catch (const std::exception &e) {
        [[maybe_unused]] char const *msg = e.what();
        png_destroy_read_struct(&m_png_ptr, &m_info_ptr, nullptr);
        fclose(m_infile);
        return HBitmapNode::LOAD_FAILED;
    }
    fclose(m_infile);
    return HBitmapNode::LOAD_OK;
}

float CustomImageIO::UnGammaCorrect(const USHORT value) const {
    const float temp = (float)value / 65525.0F;
    if (!m_ingammapreset)
        return temp;
    if (m_ingammapreset == GAMMA_NTSC) {
        // This is the sRGB / ICC rec 709 way.
        if (temp <= 0.03928F)
            return temp / 12.92F;
        return hash_math::pow((temp + 0.055F) / 1.055F, 2.4F);
    }
    return hash_math::pow(temp, m_ingamma);
}

float CustomImageIO::UnGammaCorrect(const UBYTE value) const {
    const float temp = (float)value / 255.0F;
    if (!m_ingammapreset)
        return temp;
    if (m_ingammapreset == GAMMA_NTSC) {
        // This is the sRGB / ICC rec 709 way.
        if (temp <= 0.03928F)
            return temp / 12.92F;
        return hash_math::pow((temp + 0.055F) / 1.055F, 2.4F);
    }
    return hash_math::pow(temp, m_ingamma);
}

HBitmapNode::LoadStatus CustomImageIO::NReadPng(HBitmapNode *bn) const {
    try {
        png_bytep *row_pointers = new png_bytep[m_height];
        for (int row = 0; row < m_height; row++)
            row_pointers[row] = new png_byte[png_get_rowbytes(m_png_ptr, m_info_ptr)];

        png_read_image(m_png_ptr, row_pointers);

        switch (m_channels) {
        case 1: // Grayscale
        {
            HScalarBuffer *ybuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_UBYTE, m_width, m_height);
            ybuffer->AllocateData();
            auto *ydata = (UBYTE*)ybuffer->GetData();
            bn->AddBuffer(ybuffer);
            for (int y = 0; y < m_height; ++y) {
                UBYTE *yrow = ydata + y * (int64_t)m_width;
                UBYTE *pbits = row_pointers[y];
                for (int x = 0; x < m_width; ++x, ++pbits) {
                    yrow[x] = *pbits;
                }
            }
            if (m_hasbackground && m_flags & HBitmapNode::LOADBKCOLOR) {
                ybuffer->SetBackground(m_bkgcolor);
                ybuffer->SetIsKeyBackground(m_hasbackground);
            }
            break;
        }
        case 2: // Grayscale and Alpha
        {
            HYABuffer *yabuffer = HBitmapNode::CreateYABuffer("YAlpha", HBitmapBuffer::CT_UBYTE, m_width, m_height);
            yabuffer->AllocateData();
            auto *yadata = (YAByte*)yabuffer->GetData();
            bn->AddBuffer(yabuffer);
            for (int y = 0; y < m_height; ++y) {
                YAByte *yarow = yadata + y * (int64_t)m_width;
                UBYTE *pbits = row_pointers[y];
                for (int x = 0; x < m_width; ++x, pbits += 2) {
                    yarow[x].Set(*pbits, *(pbits + 1));
                }
            }
            break;
        }
        case 3: // RGB
        {
            // Add the A:M standard named "Color" buffer to the HBitmapNode
            HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_UBYTE, m_width, m_height);
            rgbbuffer->AllocateData();
            auto *rgbdata = (RGBByte*)rgbbuffer->GetData();
            bn->AddBuffer(rgbbuffer);
            for (int y = 0; y < m_height; ++y) {
                RGBByte *rgbrow = rgbdata + y * (int64_t)m_width;
                UBYTE *pbits = row_pointers[y];
                for (int x = 0; x < m_width; ++x, pbits += 3) {
                    rgbrow[x].Set(*pbits, *(pbits + 1), *(pbits + 2));
                }
            }
            if (m_hasbackground && m_flags & HBitmapNode::LOADBKCOLOR) {
                rgbbuffer->SetBackground(m_bkgcolor);
                rgbbuffer->SetIsKeyBackground(m_hasbackground);
            }
            break;
        }
        case 4: // RGBA
        {
            HRGBABuffer *rgbabuffer = HBitmapNode::CreateRGBABuffer("ColorAlpha", HBitmapBuffer::CT_UBYTE, m_width, m_height);
            rgbabuffer->AllocateData();
            auto *rgbadata = (RGBAByte*)rgbabuffer->GetData();
            bn->AddBuffer(rgbabuffer);
            for (int y = 0; y < m_height; ++y) {
                RGBAByte *rgbarow = rgbadata + y * (int64_t)m_width;
                UBYTE *pbits = row_pointers[y];
                for (int x = 0; x < m_width; ++x, pbits += 4) {
                    rgbarow[x].Set(*pbits, *(pbits + 1), *(pbits + 2), *(pbits + 3));
                }
            }
            break;
        }
        default:
            break;
        }

        for (int row = 0; row < m_height; row++)
            delete[] row_pointers[row];
        delete[] row_pointers;
    }
    catch (const std::exception &e) {
        const String msg = "PNG IIO\nLoad Error\n"+ (String)e.what();
        AfxMessageBox(msg.Get(),MB_ICONERROR);
        return HBitmapNode::LOAD_FAILED;
    }
    return HBitmapNode::LOAD_OK;
}

HBitmapNode::LoadStatus CustomImageIO::NReadPng16(HBitmapNode *bn) const {
    try {
        png_bytep *row_pointers = new png_bytep[m_height];
        for (int row = 0; row < m_height; row++)
            row_pointers[row] = new png_byte[png_get_rowbytes(m_png_ptr, m_info_ptr)];

        png_read_image(m_png_ptr, row_pointers);

        switch (m_channels) {
        case 1: // Grayscale
        {
            HScalarBuffer *ybuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_HALF, m_width, m_height);
            ybuffer->AllocateData();
            half *ydata = (half*)ybuffer->GetData();
            bn->AddBuffer(ybuffer);
            for (int y = 0; y < m_height; ++y) {
                half *yrow = ydata + y * (int64_t)m_width;
                auto *pwords = (USHORT*)row_pointers[y];
                for (int x = 0; x < m_width; ++x, ++pwords) {
                    yrow[x] = UnGammaCorrect(*pwords);
                }
            }
            if (m_hasbackground && m_flags & HBitmapNode::LOADBKCOLOR) {
                ybuffer->SetBackground(m_bkgcolor);
                ybuffer->SetIsKeyBackground(m_hasbackground);
            }
            break;
        }
        case 2: // Grayscale and Alpha
        {
            HYABuffer *yabuffer = HBitmapNode::CreateYABuffer("YAlpha", HBitmapBuffer::CT_HALF, m_width, m_height);
            yabuffer->AllocateData();
            auto *yadata = (YAHalf*)yabuffer->GetData();
            bn->AddBuffer(yabuffer); //shoud be added after you are done
            for (int y = 0; y < m_height; ++y) {
                YAHalf *yarow = yadata + y * (int64_t)m_width;
                auto *pwords = (USHORT*)row_pointers[y];
                for (int x = 0; x < m_width; ++x, pwords += 2) {
                    yarow[x].Set(UnGammaCorrect(*pwords), UnGammaCorrect(*(pwords + 1)));
                }
            }
            break;
        }
        case 3: // RGB
        {
            HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_HALF, m_width, m_height);
            rgbbuffer->AllocateData();
            auto *rgbdata = (RGBHalf*)rgbbuffer->GetData();
            bn->AddBuffer(rgbbuffer);
            for (int y = 0; y < m_height; ++y) {
                RGBHalf *rgbrow = rgbdata + y * (int64_t)m_width;
                auto *pwords = (USHORT*)row_pointers[y];
                for (int x = 0; x < m_width; ++x, pwords += 3) {
                    rgbrow[x].Set(UnGammaCorrect(*pwords), UnGammaCorrect(*(pwords + 1)), UnGammaCorrect(*(pwords + 2)));
                }
            }
            if (m_hasbackground && m_flags & HBitmapNode::LOADBKCOLOR) {
                rgbbuffer->SetBackground(m_bkgcolor);
                rgbbuffer->SetIsKeyBackground(m_hasbackground);
            }
            break;
        }
        case 4: // RGBA
        {
            HRGBABuffer *rgbabuffer = HBitmapNode::CreateRGBABuffer("ColorAlpha", HBitmapBuffer::CT_HALF, m_width, m_height);
            rgbabuffer->AllocateData();
            auto *rgbadata = (RGBAHalf*)rgbabuffer->GetData();
            bn->AddBuffer(rgbabuffer);
            for (int y = 0; y < m_height; ++y) {
                RGBAHalf *rgbarow = rgbadata + y * (int64_t)m_width;
                auto *pwords = (USHORT*)row_pointers[y];
                for (int x = 0; x < m_width; ++x, pwords += 4) {
                    rgbarow[x].Set(UnGammaCorrect(*pwords), UnGammaCorrect(*(pwords + 1)), UnGammaCorrect(*(pwords + 2)), UnGammaCorrect(*(pwords + 3)));
                }
            }
            break;
        }
        default:
            break;
        }

        for (int row = 0; row < m_height; row++)
            delete[] row_pointers[row];
        delete[] row_pointers;
    }
    catch (const std::exception &e) {
        const String msg = "PNG IIO\nLoad Error\n"+ (String)e.what();
        AfxMessageBox(msg.Get(),MB_ICONERROR);
        return HBitmapNode::LOAD_FAILED;
    }

    return HBitmapNode::LOAD_OK;
}

HBitmapNode::LoadStatus CustomImageIO::NReadPngGammaCorrect(HBitmapNode *bn) const {
    try {
        png_bytep *row_pointers = new png_bytep[m_height];
        for (int row = 0; row < m_height; row++)
            row_pointers[row] = new png_byte[png_get_rowbytes(m_png_ptr, m_info_ptr)];

        png_read_image(m_png_ptr, row_pointers);

        switch (m_channels) {
        case 1: // Grayscale
        {
            HScalarBuffer *ybuffer = HBitmapNode::CreateScalarBuffer("Y", HBitmapBuffer::CT_HALF, m_width, m_height);
            ybuffer->AllocateData();
            half *ydata = (half*)ybuffer->GetData();
            bn->AddBuffer(ybuffer);
            for (int y = 0; y < m_height; ++y) {
                half *yrow = ydata + y * (int64_t)m_width;
                UBYTE *pwords = row_pointers[y];
                for (int x = 0; x < m_width; ++x, ++pwords) {
                    yrow[x] = UnGammaCorrect(*pwords);
                }
            }
            if (m_hasbackground && m_flags & HBitmapNode::LOADBKCOLOR) {
                ybuffer->SetBackground(m_bkgcolor);
                ybuffer->SetIsKeyBackground(m_hasbackground);
            }
            break;
        }
        case 2: // Grayscale and Alpha
        {
            HYABuffer *yabuffer = HBitmapNode::CreateYABuffer("YAlpha", HBitmapBuffer::CT_HALF, m_width, m_height);
            yabuffer->AllocateData();
            auto *yadata = (YAHalf*)yabuffer->GetData();
            bn->AddBuffer(yabuffer); //shoud be added after you are done
            for (int y = 0; y < m_height; ++y) {
                YAHalf *yarow = yadata + y * (int64_t)m_width;
                UBYTE *pwords = row_pointers[y];
                for (int x = 0; x < m_width; ++x, pwords += 2) {
                    yarow[x].Set(UnGammaCorrect(*pwords), UnGammaCorrect(*(pwords + 1)));
                }
            }
            break;
        }
        case 3: // RGB
        {
            HRGBBuffer *rgbbuffer = HBitmapNode::CreateRGBBuffer("Color", HBitmapBuffer::CT_HALF, m_width, m_height);
            rgbbuffer->AllocateData();
            auto *rgbdata = (RGBHalf*)rgbbuffer->GetData();
            bn->AddBuffer(rgbbuffer);
            for (int y = 0; y < m_height; ++y) {
                RGBHalf *rgbrow = rgbdata + y * (int64_t)m_width;
                UBYTE *pwords = row_pointers[y];
                for (int x = 0; x < m_width; ++x, pwords += 3) {
                    rgbrow[x].Set(UnGammaCorrect(*pwords), UnGammaCorrect(*(pwords + 1)), UnGammaCorrect(*(pwords + 2)));
                }
            }
            if (m_hasbackground && m_flags & HBitmapNode::LOADBKCOLOR) {
                rgbbuffer->SetBackground(m_bkgcolor);
                rgbbuffer->SetIsKeyBackground(m_hasbackground);
            }
            break;
        }
        case 4: // RGBA
        {
            HRGBABuffer *rgbabuffer = HBitmapNode::CreateRGBABuffer("ColorAlpha", HBitmapBuffer::CT_HALF, m_width, m_height);
            rgbabuffer->AllocateData();
            auto *rgbadata = (RGBAHalf*)rgbabuffer->GetData();
            bn->AddBuffer(rgbabuffer);
            for (int y = 0; y < m_height; ++y) {
                RGBAHalf *rgbarow = rgbadata + y * (int64_t)m_width;
                UBYTE *pwords = row_pointers[y];
                for (int x = 0; x < m_width; ++x, pwords += 4) {
                    rgbarow[x].Set(UnGammaCorrect(*pwords), UnGammaCorrect(*(pwords + 1)), UnGammaCorrect(*(pwords + 2)), UnGammaCorrect(*(pwords + 3)));
                }
            }
            break;
        }
        default:
            break;
        }

        for (int row = 0; row < m_height; row++)
            delete[] row_pointers[row];
        delete[] row_pointers;
    }
    catch (const std::exception &e) {
        const String msg = "PNG IIO\nLoad Error\n"+ (String)e.what();
        AfxMessageBox(msg.Get(),MB_ICONERROR);
        return HBitmapNode::LOAD_FAILED;
    }

    return HBitmapNode::LOAD_OK;
}

bool CustomImageIO::IsPNG(FILE *file) {
    unsigned char sig[8];
    fseek(file, 0L, SEEK_SET);
    if (fread(sig, 1, 8, file) != 8)
        return false;
    if (!png_check_sig(sig, 8))
        return false;
    return true;
}

// ****************** Interface

bool CustomImageIO::CanLoadImage(const String &filename) {
    FILE *file;
    if (fopen_s(&file, filename.Get(), "rb") != 0)
        return false;
    if (IsPNG(file)) {
        fclose(file);
        return true;
    }
    fclose(file);
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
    int status = HBitmapNode::LOAD_FAILED;
    // YP COMEBACK: Remove this protection when the filetype check is done appropriately before calling LoadFrame
    if (!CanLoadImage(filename))
        return status;

    // YP COMEBACK: Handle frames
    if (!OpenPng(filename.Get()))
        return status;

    bn->SetWidth(m_width);
    bn->SetHeight(m_height);
    if (flags & HBitmapNode::LOADINFOONLY) {
        status = ClosePng(true);
        return status;
    }

    m_flags = flags;
    if (m_bitdepth == 16) {
        status = NReadPng16(bn);
    } else {
        if (m_ingammapreset) {
            status = NReadPngGammaCorrect(bn);
        } else {
            status = NReadPng(bn);
        }
    }
    status |= ClosePng();
    return status;
}
