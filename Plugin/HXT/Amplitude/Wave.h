#ifndef __PCM_Wave_H
#define __PCM_Wave_H 
#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __STRCLASS_H
#include "StrClass.h"
#endif
#ifndef __HASHTIME_H
#include "HashTime.h"
#endif
#include <mmsystem.h>
// Error results
#define PCM_Wave_ERR_OPEN_DEV		1
#define PCM_Wave_ERR_WRITE_DATA		2
#define PCM_Wave_ERR_NO_WAVE_BUFFER	3

// Typedefs to make it easier to interpret sample buffer.
// NOTE: Intel only!  PCM data is little-endian.  Other platforms may need
// to convert.

// Also:
// 8-bit mono is just 1 BYTE per sample
// 16-bit mono is just 1 short per sample (see Intel note above!)

// 8-bit values:	Min = 0			Max = 255		Zero = 128
// 16-bit values:	Min = -32768	Max = 32767		Zero = 0	

#define MAX32BIT  2147483648
#define MIN32BIT (-2147483648)
#define MAX16BIT  32767
#define MIN16BIT (-32768)
#define MAX8BIT     255
#define MIN8BIT       0

typedef struct {
    BYTE left;
    BYTE right;
} PCMSample_8bitStereo;

typedef struct {
    short left;
    short right;
} PCMSample_16bitStereo;

typedef struct {
    int left;
    int right;
} PCMSample_32bitStereo;

typedef struct {
    int start_freq;
    int end_freq;
    int start;
    int end;
    int az_freq;
} FrequenzBand;

class PCM_Wave final {
protected:
    // Number of *samples*, not bytes, allocated in sample buffer
    unsigned long m_ulDataSize;

    // Wave buffer
    HANDLE m_hData;
    LPSTR m_lpData;

public:
    // Wave format (shoudl be protected)
    WAVEFORMATEX m_pcmWF{};

    float m_peaksample{};
    float m_length{};
    FrequenzBand m_bands[11]{}; //Frequenzbaender fuer eq

    Time m_startpos;
    Time m_endpos;

    CArray<CPoint, CPoint &> Points_Left;
    CArray<CPoint, CPoint &> Points_Right;
    BOOL waveform_ready{};

    PCM_Wave();
    ~PCM_Wave();
    void FreeWave();

    [[nodiscard]] unsigned long GetNumSamples() const;
    [[nodiscard]] int GetSampleSize() const;

    [[nodiscard]] int GetSampleRate() const;
    void SetSampleRate(int new_rate);

    [[nodiscard]] int GetNumChannels() const;
    void SetNumChannels(int chans);

    [[nodiscard]] WORD GetBitsPerSample() const;
    void SetBitsPerSample(WORD bps);

    [[nodiscard]] LPSTR GetBuffer() const;
    void SetBuffer(LPSTR buffer);
    [[nodiscard]] DWORD GetBufferSizeBytes() const;

    void CalculateLength();

    void FreeSampleBuffer();

    BOOL IsSound(const String &name);
    BOOL LoadWAV(const String &name);
    [[nodiscard]] BOOL IsBufferReady() const;

    [[nodiscard]] PCMSample_16bitStereo GetSample(double t) const;

    [[nodiscard]] String GetSoundDescription(double fps = 30, TimeUnit timemode = TimeUnit::SMPTE) const;

    void RemovePop() const;
    void SetPeakSample();

    void DrawWaveform(CRect bounds, float in, float out, double samplesperpixel);
    void Draw8BitMono(const BYTE *sample, UINT numsamples, float in, float out, CRect bounds, double samplesperpixel);
    void Draw16BitMono(const short *sample, UINT numsamples, float in, float out, CRect bounds, double samplesperpixel);
    void Draw8BitStereo(const PCMSample_8bitStereo *sample, UINT numsamples, float in, float out, CRect bounds, double samplesperpixel);
    void Draw16BitStereo(const PCMSample_16bitStereo *sample, UINT numsamples, float in, float out, CRect bounds, double samplesperpixel);
    void Draw32BitStereo(const PCMSample_32bitStereo *sample, UINT numsamples, float in, float out, CRect bounds, double samplesperpixel);

};

inline unsigned long PCM_Wave::GetBufferSizeBytes() const {
    return m_ulDataSize * m_pcmWF.nBlockAlign;
}

inline unsigned long PCM_Wave::GetNumSamples() const {
    return m_ulDataSize;
}

inline int PCM_Wave::GetSampleSize() const {
    return m_pcmWF.nBlockAlign;
}

inline int PCM_Wave::GetSampleRate() const {
    return m_pcmWF.nSamplesPerSec;
}

inline void PCM_Wave::SetSampleRate(const int new_rate) {
    m_pcmWF.nSamplesPerSec = new_rate;
    // Take care of nBlockAlign so we don't have to worry about it
    m_pcmWF.nAvgBytesPerSec = new_rate * m_pcmWF.nBlockAlign;
}

inline int PCM_Wave::GetNumChannels() const {
    return m_pcmWF.nChannels;
}

inline void PCM_Wave::SetNumChannels(const int chans) {
    m_pcmWF.nChannels = chans;
    // Take care of nBlockAlign so we don't have to worry about it
    m_pcmWF.nBlockAlign = chans * m_pcmWF.wBitsPerSample / 8;
    // ...and fix up nAvgBytesPerSec...
    m_pcmWF.nAvgBytesPerSec = m_pcmWF.nSamplesPerSec * m_pcmWF.nBlockAlign;
}

inline WORD PCM_Wave::GetBitsPerSample() const {
    return m_pcmWF.wBitsPerSample;
}

inline void PCM_Wave::SetBitsPerSample(const WORD bps) {
    m_pcmWF.wBitsPerSample = bps;
    // Take care of nBlockAlign so we don't have to worry about it
    m_pcmWF.nBlockAlign = m_pcmWF.nChannels * bps / 8;
    // ...and fix up nAvgBytesPerSec...
    m_pcmWF.nAvgBytesPerSec = m_pcmWF.nSamplesPerSec * m_pcmWF.nBlockAlign;
}

inline void PCM_Wave::CalculateLength() {
    m_length = (float)GetNumSamples() / GetSampleRate();
}

inline LPSTR PCM_Wave::GetBuffer() const {
    return m_lpData;
}

inline void PCM_Wave::SetBuffer(const LPSTR buffer) {
    m_lpData = buffer;
}

inline BOOL PCM_Wave::IsBufferReady() const {
    return m_lpData != nullptr;
}

inline PCMSample_16bitStereo PCM_Wave::GetSample(const double t) const {
    PCMSample_16bitStereo s{};
    if (!m_lpData || t > m_length) {
        s.left = 0;
        s.right = 0;
        return s;
    }
    PCMSample_32bitStereo s32;
    const short *ptr16 = (short*)m_lpData;
    const int *ptr32 = (int*)m_lpData;
    UINT index = (UINT)fast_round(t * m_pcmWF.nSamplesPerSec * m_pcmWF.nChannels);

    if (m_pcmWF.nChannels == 2) {
        if (index & 1) //fix left/right boundary
            index--;
    }

    if (m_pcmWF.wBitsPerSample == 16) {
        s.left = ptr16[index];
    } else {
        if (m_pcmWF.wBitsPerSample == 32) {
            s32.left = ptr32[index];
            s.left = (short)(s32.left / MAX32BIT * MAX16BIT);
        } else {
            s.left = (short)(((UBYTE)m_lpData[index] + 1) / 256.0 * 65535 - 32768);
        }
    }

    if (m_pcmWF.nChannels == 2) {
        if (m_pcmWF.wBitsPerSample == 16) {
            s.right = ptr16[index + 1];
        } else {
            if (m_pcmWF.wBitsPerSample == 32) {
                s32.left = ptr32[index + 1];
                s.left = (short)(s32.left / MAX32BIT * MAX16BIT);
            } else {
                s.right = (short)(((UBYTE)m_lpData[index + 1] + 1) / 256.0 * 65535 - 32768);
            }
        }
    } else {
        s.right = s.left; //mirror mono on both channels
    }
    return s;
}

#endif
