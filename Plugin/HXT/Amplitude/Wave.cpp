// BC  1/14/2002  \Bob90\Sound\PCM_Wave.cpp
#include "StdAfx.h"
#include "Wave.h"
#include "HashFile.h"

#define FORMAT 0x20746D66 // 'fmt' tag
#define DATA   0x61746164 // 'data' tag
#define RIFF   0x46464952 // 'RIFF' tag
#define WAVE   0x45564157 // 'WAVE' tag
#define PCM    1          // 'PCM' tag

PCM_Wave::PCM_Wave() : m_startpos(0), m_endpos(0) {
    m_hData = nullptr;
    m_lpData = nullptr;

    // 1 sec at 11,025 samps/sec
    m_ulDataSize = 11025L;

    // Set up wave format structure
    // Default: 8-bit mono
    m_pcmWF.wFormatTag = WAVE_FORMAT_PCM;
    m_pcmWF.nChannels = 1;
    m_pcmWF.nSamplesPerSec = 11025L;
    m_pcmWF.nAvgBytesPerSec = 11025L;
    m_pcmWF.nBlockAlign = 1;
    m_pcmWF.wBitsPerSample = 8;
    m_pcmWF.cbSize = 0;
}

PCM_Wave::~PCM_Wave() {
    Points_Left.RemoveAll();
    Points_Right.RemoveAll();
    waveform_ready = FALSE;
}

void PCM_Wave::FreeWave() {
    FreeSampleBuffer();
}

void PCM_Wave::FreeSampleBuffer() {
    if (m_hData) {
        free(m_hData);
        m_ulDataSize = 0;
    }
    if (m_lpData) {
        free(m_lpData);
    }
    m_hData = nullptr;
    m_lpData = nullptr;
    Points_Left.RemoveAll();
    Points_Right.RemoveAll();
    waveform_ready = FALSE;
    //   m_startpos = 0;
    //   m_endpos = 0;
}

String PCM_Wave::GetSoundDescription(const double fps, const TimeUnit timemode) const {

    String desc = (String)GetSampleRate() + " Hz, " + GetBitsPerSample() + "bit, ";
    if (GetNumChannels() == 1)
        desc += "Mono, Wave file length ";
    else
        desc += "Stereo, Wave file length ";

    const auto length = Time(m_length);
    desc += length.ToString(fps, timemode);
    return desc;
}

BOOL PCM_Wave::IsSound(const String &name) {

    String filename = name;
    FreeWave();

    if (filename.GetSuffixOnly() == "mp3") {
        //simple test need to check the actual file header
        return TRUE;
    }
    FileStream hs;

    if (!hs.Open(filename, FileMode::HS_BINARY | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS))
        return FALSE;

    UINT tag, chunk, junk, size;
    SSHORT nNumChannels, format;
    USHORT wBitsPerSample;
    int nSampleRate;

    hs >> chunk >> junk >> tag;
    if (chunk != RIFF || tag != WAVE) {
        hs.Close();
        return FALSE;
    }

    while (!hs.Eof()) {
        hs >> tag;
        hs >> size;

        if (tag == FORMAT) {
            hs >> format;
            if (format != PCM) {
                hs.Close();
                return FALSE;
            }
            hs >> nNumChannels;
            if (nNumChannels < 1 || nNumChannels > 2) {
                hs.Close();
                return FALSE;
            }
            hs >> nSampleRate;
            if (nSampleRate <= 0) {
                hs.Close();
                return FALSE;
            }
            hs.Seek(6, HashStream::HS_OFFSET); //Skip Avg Bytes/Sec
            hs >> wBitsPerSample;
            if (size > 16)
                hs.Seek(size - 16, HashStream::HS_OFFSET);
            hs.Close();
            return TRUE;
        }
        hs.Seek(size, HashStream::HS_OFFSET); //unknown tag so skip
    }
    hs.Close();
    return FALSE;
}

float convert(const unsigned char *src) {
    const int i = (src[2] << 24 | src[1] << 16 | src[0] << 8) >> 8;
    return (i + .5F) / 8388607.5F;
}

BOOL PCM_Wave::LoadWAV(const String &name) {

    String filename = name;
    SSHORT nNumChannels, format;
    USHORT wBitsPerSample;
    int nSampleRate;
    FileStream hs;
    FreeWave();

    if (!hs.Open(filename, FileMode::HS_BINARY | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS))
        return FALSE;

    if (filename.GetSuffixOnly() == "mp3") {
        //need to load actual data for info and display
        return TRUE;
    }

    hs.Seek(12, HashStream::HS_OFFSET); //Skip RIFF & WAVE TAGS
    UINT tag, size;
    while (!hs.Eof()) {
        hs >> tag;
        hs >> size;

        if (tag == FORMAT) {
            hs >> format;
            hs >> nNumChannels;
            hs >> nSampleRate;

            hs.Seek(6, HashStream::HS_OFFSET); //Skip Avg Bytes/Sec
            hs >> wBitsPerSample;
            if (size > 16)
                hs.Seek(size - 16, HashStream::HS_OFFSET);
        } else if (tag == DATA) {
            // NOTE: If this is NOT an 8-bit sample, the sample
            // NOTE: data will have to be swapped on the Mac
            m_ulDataSize = size / (nNumChannels * wBitsPerSample / 8);
            if (wBitsPerSample == 24) {
                m_lpData = (char *)malloc(sizeof(char) * m_ulDataSize * 8);
                auto *temp = (unsigned char *)malloc(sizeof(unsigned char) * size);
                unsigned char *ptr = temp;
                UINT left = size;
                while (left > 0) {
                    const UINT amount = MIN(left, size / 100);
                    hs.Read(ptr, amount);
                    left -= amount;
                    ptr += amount;
                    hs.SetStatusMeter();
                }
                auto *sample = (PCMSample_32bitStereo*)GetBuffer();
                ptr = temp;
                unsigned char t_buffer[3];
                for (unsigned long i = 0; i < m_ulDataSize - 1; ++i) {
                    t_buffer[0] = *ptr++;
                    t_buffer[1] = *ptr++;
                    t_buffer[2] = *ptr++;
                    sample[i].left = (int)(convert(t_buffer) * MAX32BIT);
                    t_buffer[0] = *ptr++;
                    t_buffer[1] = *ptr++;
                    t_buffer[2] = *ptr++;
                    sample[i].right = (int)(convert(t_buffer) * MAX32BIT);
                }
                free(temp);
            } else {
                m_lpData = (char *)malloc(sizeof(char) * size);
                char *ptr = m_lpData;
                UINT left = size;
                while (left > 0) {
                    const UINT amount = MIN(left, size / 100);
                    hs.Read(ptr, amount);
                    left -= amount;
                    ptr += amount;
                    hs.SetStatusMeter();
                }
            }
            SetSampleRate(nSampleRate);
            SetNumChannels(nNumChannels);
            SetBitsPerSample(wBitsPerSample);
            break;
        } else
            hs.Seek(size, HashStream::HS_OFFSET); //unknown tag so skip
    }
    hs.Close();
    RemovePop();
    SetPeakSample();
    CalculateLength();
    return TRUE;
}

void PCM_Wave::RemovePop() const {
    //last sample bad.  Should write a real pop filter that scans the whole file with threshhold and window etc.
    switch (GetNumChannels()) {
        case 1: // Mono
            switch (GetBitsPerSample()) {
                case 8:
                {
                    auto *const sample = (BYTE*)GetBuffer();
                    if (sample[GetNumSamples() - 1] == 0)
                        sample[GetNumSamples() - 1] = 127;
                    break;
                }
                case 16:
                {
                    auto *sample = (short*)GetBuffer();
                    if (sample[GetNumSamples() - 1] == 0)
                        sample[GetNumSamples() - 1] = 0;
                    break;
                }
            }
            break;
        case 2: // Stereo
            switch (GetBitsPerSample()) {
                case 8:
                {
                    auto *sample = (PCMSample_8bitStereo*)GetBuffer(); // Get the sample
                    if (sample[GetNumSamples() - 1].left == 0 || sample[GetNumSamples() - 1].right == 0) {
                        sample[GetNumSamples() - 1].left = 127;
                        sample[GetNumSamples() - 1].right = 127;
                    }
                    break;
                }
                case 16:
                {
                    auto *sample = (PCMSample_16bitStereo*)GetBuffer(); // Get the sample
                    if (sample[GetNumSamples() - 1].left == 0 || sample[GetNumSamples() - 1].right == 0) {
                        sample[GetNumSamples() - 1].left = 0;
                        sample[GetNumSamples() - 1].right = 0;
                    }
                    break;
                }
            }
            break;
    }

}

void PCM_Wave::SetPeakSample() {
    m_peaksample = 0.F;

    switch (GetNumChannels()) {
        case 1: // Mono
            switch (GetBitsPerSample()) {
                case 8:
                {
                    const BYTE *sample = (BYTE*)GetBuffer();
                    for (unsigned long i = 0; i < GetNumSamples(); ++i) {
                        const float normsample = (float)abs(sample[i] - 127) / 128.0F;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;
                    }
                    break;
                }
                case 16:
                {
                    const short *sample = (short*)GetBuffer();
                    for (unsigned long i = 0; i < GetNumSamples(); ++i) {
                        const float normsample = (float)abs(sample[i]) / MAX16BIT;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;
                    }
                    break;
                }
            }
            break;
        case 2: // Stereo
            switch (GetBitsPerSample()) {
                case 8:
                {
                    const PCMSample_8bitStereo *sample = (PCMSample_8bitStereo*)GetBuffer(); // Get the sample
                    for (unsigned long i = 0; i < GetNumSamples(); ++i) {
                        float normsample = (float)abs(sample[i].left - 127) / 128.0F;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;

                        normsample = (float)abs(sample[i].right - 127) / 128.0F;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;
                    }
                    break;
                }
                case 16:
                {
                    const PCMSample_16bitStereo *sample = (PCMSample_16bitStereo*)GetBuffer(); // Get the sample
                    for (unsigned long i = 0; i < GetNumSamples(); ++i) {
                        float normsample = (float)abs(sample[i].left) / MAX16BIT;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;

                        normsample = (float)abs(sample[i].right) / MAX16BIT;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;
                    }
                    break;
                }
                case 24:
                case 32:
                {
                    const PCMSample_32bitStereo *sample = (PCMSample_32bitStereo*)GetBuffer(); // Get the sample
                    for (unsigned long i = 0; i < GetNumSamples(); ++i) {
                        float normsample = (float)abs(sample[i].left) / MAX32BIT;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;

                        normsample = (float)abs(sample[i].right) / MAX32BIT;
                        if (normsample > m_peaksample)
                            m_peaksample = normsample;
                    }
                    break;
                }
            }
            break;
    }
}

void PCM_Wave::DrawWaveform(const CRect bounds, const float in, const float out, const double samplesperpixel) {
    if (!IsBufferReady())
        return;

    switch (GetNumChannels()) {
        case 1: // Mono
            switch (GetBitsPerSample()) {
                case 8:
                {
                    const BYTE *sample = (BYTE*)GetBuffer();
                    Draw8BitMono(sample, GetNumSamples(), in, out, bounds, samplesperpixel);
                    break;
                }
                case 16:
                {
                    const short *sample = (short*)GetBuffer();
                    Draw16BitMono(sample, GetNumSamples(), in, out, bounds, samplesperpixel);
                    break;
                }
                default:
                    break;
            }
            break;
        case 2: // Stereo
            switch (GetBitsPerSample()) {
                case 8:
                {
                    const PCMSample_8bitStereo *sample = (PCMSample_8bitStereo*)GetBuffer(); // Get the sample
                    Draw8BitStereo(sample, GetNumSamples(), in, out, bounds, samplesperpixel);
                    break;
                }
                case 16:
                {
                    const PCMSample_16bitStereo *sample = (PCMSample_16bitStereo*)GetBuffer(); // Get the sample
                    Draw16BitStereo(sample, GetNumSamples(), in, out, bounds, samplesperpixel); // and draw it
                    break;
                }
                case 24:
                case 32:
                {
                    const PCMSample_32bitStereo *sample = (PCMSample_32bitStereo*)GetBuffer(); // Get the sample
                    Draw32BitStereo(sample, GetNumSamples(), in, out, bounds, samplesperpixel); // and draw it
                    break;
                }
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void PCM_Wave::Draw8BitMono(const BYTE *sample, const UINT numsamples, const float in, const float out, const CRect bounds, const double samplesperpixel) {
    // we are drawing the waveform for the region bounded by bounds
    const unsigned long startSample = fast_ftol_unsigned(in * GetSampleRate()); //* SamplesPerPixel);
    const unsigned long endSample = fast_ftol_unsigned(out * GetSampleRate()); //* SamplesPerPixel);

    const int center = (bounds.top + bounds.bottom) * 0.5F;
    const int halfheight = fast_ftol_signed(bounds.Height() / 2.0);

    const UINT step = fast_ftol_unsigned(MAX<float>(1, samplesperpixel / 10.));
    int pixel = bounds.left;
    CPoint temp_point;
    temp_point.SetPoint(pixel, center);
    Points_Left.Add(temp_point);
    for (double majorSample = startSample; majorSample < endSample - samplesperpixel && pixel <= bounds.right; majorSample += samplesperpixel) {
        float value_left = 0.F;
        for (double minorSample = majorSample; minorSample < majorSample + samplesperpixel; minorSample += step) {
            const UINT index = minorSample;
            if (index >= numsamples)
                break;
            const float normsample = (float)abs(sample[index] - 127) / 128.0F / m_peaksample;
            if (normsample > value_left)
                value_left = normsample;
        }
        temp_point.SetPoint(pixel, fast_ftol_signed(center + value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center - value_left * halfheight));
        Points_Left.Add(temp_point);
        pixel++;
    }
    waveform_ready = TRUE;
}

void PCM_Wave::Draw16BitMono(const short *sample, const UINT numsamples, const float in, const float out, const CRect bounds, const double samplesperpixel) {
    const unsigned long startSample = fast_ftol_unsigned(in * GetSampleRate()); //* SamplesPerPixel);
    const unsigned long endSample = fast_ftol_unsigned(MIN<float>(GetNumSamples(), out * GetSampleRate()));

    const int center = (bounds.top + bounds.bottom) * 0.5F;
    const int halfheight = fast_ftol_signed(bounds.Height() / 2.0);

    const UINT step = fast_ftol_unsigned(MAX<float>(1, samplesperpixel / 10.));
    int pixel = bounds.left;
    CPoint temp_point;
    temp_point.SetPoint(pixel, center);
    Points_Left.Add(temp_point);
    for (double majorSample = startSample; majorSample < endSample - samplesperpixel && pixel <= bounds.right; majorSample += samplesperpixel) {
        float value_left = 0.F;
        for (double minorSample = majorSample; minorSample < majorSample + samplesperpixel; minorSample += step) {
            const UINT index = minorSample;
            if (index >= numsamples)
                break;
            const float normsample = (float)abs(sample[index]) / MAX16BIT / m_peaksample;
            if (normsample > value_left)
                value_left = normsample;
        }
        temp_point.SetPoint(pixel, fast_ftol_signed(center + value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center - value_left * halfheight));
        Points_Left.Add(temp_point);
        pixel++;
    }
    waveform_ready = TRUE;
}

void PCM_Wave::Draw8BitStereo(const PCMSample_8bitStereo *sample, const UINT numsamples, const float in, const float out, const CRect bounds, const double samplesperpixel) {
    const unsigned long startSample = fast_ftol_unsigned(in * GetSampleRate()); //* SamplesPerPixel);
    const unsigned long endSample = fast_ftol_unsigned(MIN<float>(GetNumSamples(), out * GetSampleRate()));

    const int center = (bounds.top + bounds.bottom) * 0.5F;
    const int test = center * 0.5F;
    const int center_left = bounds.top + test;
    const int center_right = bounds.bottom - test;
    const int halfheight = fast_ftol_signed(bounds.Height() / 4.0);

    const UINT step = fast_ftol_unsigned(MIN<float>(1, samplesperpixel / 10.));
    int pixel = bounds.left;
    CPoint temp_point;
    temp_point.SetPoint(pixel, center_left);
    Points_Left.Add(temp_point);
    temp_point.SetPoint(pixel, center_right);
    Points_Right.Add(temp_point);
    for (double majorSample = startSample; majorSample < endSample - samplesperpixel && pixel <= bounds.right; majorSample += samplesperpixel) {
        float value_left = 0.F;
        float value_right = 0.F;
        for (double minorSample = majorSample; minorSample < majorSample + samplesperpixel; minorSample += step) {
            const UINT index = minorSample;
            if (index >= numsamples)
                break;
            const PCMSample_8bitStereo thesample = sample[index];
            float normsample = (float)abs(thesample.left - 127) / 128.0F / m_peaksample;
            if (normsample > value_left)
                value_left = normsample;
            normsample = (float)abs(thesample.right - 127) / 128.0F / m_peaksample;
            if (normsample > value_right)
                value_right = normsample;
        }
        temp_point.SetPoint(pixel, fast_ftol_signed(center_left + value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_left - value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_right + value_right * halfheight));
        Points_Right.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_right - value_right * halfheight));
        Points_Right.Add(temp_point);
        pixel++;
    }
    waveform_ready = TRUE;
}

void PCM_Wave::Draw16BitStereo(const PCMSample_16bitStereo *sample, const UINT numsamples, const float in, const float out, const CRect bounds, const double samplesperpixel) {
    const unsigned long startSample = fast_ftol_unsigned(in * GetSampleRate());
    const unsigned long endSample = fast_ftol_unsigned(MIN<float>(GetNumSamples(), out * GetSampleRate()));

    const int center = (bounds.top + bounds.bottom) * 0.5F;
    const int test = center * 0.5F;
    const int center_left = bounds.top + test;
    const int center_right = bounds.bottom - test;
    const int halfheight = fast_ftol_signed(bounds.Height() / 4.0);

    const UINT step = fast_ftol_unsigned(MAX<float>(1, samplesperpixel / 10.));
    int pixel = bounds.left;
    CPoint temp_point;
    temp_point.SetPoint(pixel, center_left);
    Points_Left.Add(temp_point);
    temp_point.SetPoint(pixel, center_right);
    Points_Right.Add(temp_point);
    for (double majorSample = startSample; majorSample < endSample - samplesperpixel && pixel <= bounds.right; majorSample += samplesperpixel) {
        float value_left = 0.F;
        float value_right = 0.F;
        for (double minorSample = majorSample; minorSample < majorSample + samplesperpixel; minorSample += step) {
            const UINT index = minorSample;
            if (index >= numsamples)
                break;
            const PCMSample_16bitStereo thesample = sample[index];
            float normsample = (float)abs(thesample.left) / MAX16BIT / m_peaksample;
            if (normsample > value_left)
                value_left = normsample;
            normsample = (float)abs(thesample.right) / MAX16BIT / m_peaksample;
            if (normsample > value_right)
                value_right = normsample;
        }
        temp_point.SetPoint(pixel, fast_ftol_signed(center_left + value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_left - value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_right + value_right * halfheight));
        Points_Right.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_right - value_right * halfheight));
        Points_Right.Add(temp_point);
        pixel++;
    }
    waveform_ready = TRUE;
}

void PCM_Wave::Draw32BitStereo(const PCMSample_32bitStereo *sample, const UINT numsamples, const float in, const float out, const CRect bounds, const double samplesperpixel) {
    const unsigned long startSample = fast_ftol_unsigned(in * GetSampleRate());
    const unsigned long endSample = fast_ftol_unsigned(MIN<float>(GetNumSamples(), out * GetSampleRate()));

    const int center = (bounds.top + bounds.bottom) * 0.5F;
    const int test = center * 0.5F;
    const int center_left = bounds.top + test;
    const int center_right = bounds.bottom - test;
    const int halfheight = fast_ftol_signed(bounds.Height() / 4.0);

    const UINT step = fast_ftol_unsigned(MAX<float>(1, samplesperpixel / 10.));
    int pixel = bounds.left;
    CPoint temp_point;
    temp_point.SetPoint(pixel, center_left);
    Points_Left.Add(temp_point);
    temp_point.SetPoint(pixel, center_right);
    Points_Right.Add(temp_point);
    for (double majorSample = startSample; majorSample < endSample - samplesperpixel && pixel <= bounds.right; majorSample += samplesperpixel) {
        float value_left = 0.F;
        float value_right = 0.F;
        for (double minorSample = majorSample; minorSample < majorSample + samplesperpixel; minorSample += step) {
            const UINT index = minorSample;
            if (index >= numsamples)
                break;
            const PCMSample_32bitStereo thesample = sample[index];
            float normsample = (float)abs(thesample.left) / MAX32BIT / m_peaksample;
            if (normsample > value_left)
                value_left = normsample;
            normsample = (float)abs(thesample.right) / MAX32BIT / m_peaksample;
            if (normsample > value_right)
                value_right = normsample;
        }
        temp_point.SetPoint(pixel, fast_ftol_signed(center_left + value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_left - value_left * halfheight));
        Points_Left.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_right + value_right * halfheight));
        Points_Right.Add(temp_point);
        temp_point.SetPoint(pixel, fast_ftol_signed(center_right - value_right * halfheight));
        Points_Right.Add(temp_point);
        pixel++;
    }
    waveform_ready = TRUE;
}
