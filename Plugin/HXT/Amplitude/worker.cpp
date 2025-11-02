// ReSharper disable CppClangTidyModernizeLoopConvert
#include "StdAfx.h"
#include "Amplitude.h"

float CAmplitudeApp::GetWaveValue(double samplepos) {
    double highest_left = 0;
    double highest_right = 0;
    float value = 0.F;
    if (para.m_useband) {
        double pos = samplepos + m_offset_pos; //for fitting windowsize 1024 
        if (pos < 0)
            pos = 0;
        if (pos >= para.m_wave.m_length)
            pos -= 1024 * m_step + m_offset_pos;
        for (int j = 0; j < 1024; ++j) {
            if (pos < para.m_wave.m_length) {
                const PCMSample_16bitStereo sample = para.m_wave.GetSample(pos);
                pos += m_step;
                m_outBuf_L[j] = sample.left;
                m_outBuf_R[j] = sample.right;
            } else {
                m_outBuf_L[j] = 0;
                m_outBuf_R[j] = 0;
            }
        }
        for (double j = 0; j < m_stepend;) {
            pos = j + samplepos;
            const PCMSample_16bitStereo sample = para.m_wave.GetSample(pos);
            if (hash_math::abs(highest_left) < hash_math::abs(sample.left))
                highest_left = sample.left;
            if (hash_math::abs(highest_right) < hash_math::abs(sample.right))
                highest_right = sample.right;
            j += m_step;
        }
        const float value_left = hash_math::abs(highest_left / 32767. / para.m_wave.m_peaksample);
        const float value_right = hash_math::abs(highest_right / 32767. / para.m_wave.m_peaksample);

        double fdraw[11];
        double scale;
        double fmax = -hash_constants::max_float;
        double fmin = hash_constants::max_float;
        m_fftTransformer->Transform(m_outBuf_L);
        for (int j = 0; j < 11; ++j) {
            double sfmax = -hash_constants::max_float;
            for (int z = para.m_wave.m_bands[j].start; z < para.m_wave.m_bands[j].start + para.m_wave.m_bands[j].az_freq; ++z) {
                const double temp_value = m_fftTransformer->GetIntensity(z);
                if (temp_value > sfmax)
                    sfmax = temp_value;
            }
            fdraw[j] = sfmax;
            if (fdraw[j] > fmax)
                fmax = fdraw[j];
            if (fdraw[j] < fmin)
                fmin = fdraw[j];
        }
        if (value_left < 0.001)
            scale = 0;
        else
            scale = 1.0 / fmax;
        highest_left = fdraw[para.m_band] * scale * value_left;

        fmax = -hash_constants::max_float;
        fmin = hash_constants::max_float;
        m_fftTransformer->Transform(m_outBuf_R);
        for (int j = 0; j < 11; ++j) {
            double sfmax = -hash_constants::max_float;
            for (int z = para.m_wave.m_bands[j].start; z < para.m_wave.m_bands[j].start + para.m_wave.m_bands[j].az_freq; ++z) {
                const double temp_value = m_fftTransformer->GetIntensity(z);
                if (temp_value > sfmax)
                    sfmax = temp_value;
            }
            fdraw[j] = sfmax;
            if (fdraw[j] > fmax)
                fmax = fdraw[j];
            if (fdraw[j] < fmin)
                fmin = fdraw[j];
        }
        if (value_right < 0.001)
            scale = 0;
        else
            scale = 1.0 / fmax;
        highest_right = fdraw[para.m_band] * scale * value_right;

        if (highest_left == 0 && highest_right == 0) {
            value = 0.F;
        } else {
            switch (para.m_channels) {
                case 0: //both or mono
                    value = (highest_left + highest_right) / 2.;
                    break;
                case 1: //left
                    value = highest_left;
                    break;
                case 2: //right
                    value = highest_right;
                    break;
                default:
                    ASSERT(false);
                    break;
            }
        }
    } else {
        if (samplepos >= para.m_wave.m_length)
            samplepos -= m_stepend;
        for (double j = 0; j < m_stepend;) {
            const double pos = j + samplepos;
            const PCMSample_16bitStereo sample = para.m_wave.GetSample(pos);
            if (highest_left < hash_math::abs(sample.left))
                highest_left = hash_math::abs(sample.left);
            if (highest_right < hash_math::abs(sample.right))
                highest_right = hash_math::abs(sample.right);
            j += m_step;
        }
        switch (para.m_channels) {
            case 0: //both or mono
                value = (highest_left + highest_right) / 2. / 32767.;
                break;
            case 1: //left
                value = highest_left / 32767.;
                break;
            case 2: //right
                value = highest_right / 32767.;
                break;
            default:
                ASSERT(false);
                break;
        }
        if (value < 0.0001)
            value = 0.F;
    }
    if (value < 0.F)
        value = 0.F;
    return value; //return value in the range 0 - 1
}

BOOL CAmplitudeApp::WorkFloat() {
    const HFloatProperty *hfp = (HFloatProperty *)para.m_property;
    const HFloatPropertyInfo *hfpinfo = (HFloatPropertyInfo *)hfp->GetPropertyInfo();
    const float factor_value = hfpinfo->GetFactorValue();
    const float min_val = hfpinfo->GetMinValue();
    const float max_val = hfpinfo->GetMaxValue();

    const int startframe = para.m_wave.m_startpos.GetFrameInt(para.m_fps);
    const int endframe = para.m_wave.m_endpos.GetFrameInt(para.m_fps);
    const float high_value = para.m_maxf - para.m_minf;
    Time time;
    Time time_halfframe;
    time_halfframe.SetSeconds(m_stepend);
    CArray<float, float &> add_value;
    if (para.add_tocurrentvalue) {
        for (int i = startframe; i <= endframe; ++i) {
            time.SetFrame(i, para.m_fps);
            float act_value = hfp->GetValue(time);
            add_value.Add(act_value);
        }
    }

    for (int i = startframe; i <= endframe; ++i) {
        time.SetFrame(i, para.m_fps);
        double act_second = time.GetSecondsDouble();
        float value = para.m_minf + GetWaveValue(act_second) * high_value;
        if (factor_value != 1.F)
            value /= factor_value;
        if (para.add_tocurrentvalue) {
            value += add_value.GetAt(i);
        } else {
            if (value < para.m_minf) {
                value = para.m_minf;
            }
            if (value > para.m_maxf) {
                value = para.m_maxf;
            }
        }
        if (value < min_val) {
            value = min_val;
        }
        if (value > max_val) {
            value = max_val;
        }
        hfp->StoreValue(time, value, FALSE);
        if (para.m_halfframe) {
            if (i < endframe) {
                time += time_halfframe;
                act_second = time.GetSecondsDouble();
                value = para.m_minf + GetWaveValue(act_second) * high_value;
                if (factor_value != 1.F)
                    value /= factor_value;
                if (para.add_tocurrentvalue) {
                    value += add_value.GetAt(i);
                } else {
                    if (value < para.m_minf) {
                        value = para.m_minf;
                    }
                    if (value > para.m_maxf) {
                        value = para.m_maxf;
                    }
                }
                if (value < min_val) {
                    value = min_val;
                }
                if (value > max_val) {
                    value = max_val;
                }
                hfp->StoreValue(time, value, FALSE);
            }
        }
    }
    return TRUE;
}

BOOL CAmplitudeApp::WorkPercent() {
    const HPercentProperty *hfp = (HPercentProperty *)para.m_property;
    const HPercentPropertyInfo *hfpinfo = (HPercentPropertyInfo *)hfp->GetPropertyInfo();
    const float factor_value = hfpinfo->GetFactorValue();
    const float min_val = hfpinfo->GetMinValue();
    const float max_val = hfpinfo->GetMaxValue();

    const int startframe = para.m_wave.m_startpos.GetFrameInt(para.m_fps);
    const int endframe = para.m_wave.m_endpos.GetFrameInt(para.m_fps);
    const float high_value = para.m_maxf - para.m_minf;
    Time time;
    Time time_halfframe;
    time_halfframe.SetSeconds(m_stepend);
    CArray<float, float &> add_value;
    if (para.add_tocurrentvalue) {
        for (int i = startframe; i <= endframe; ++i) {
            time.SetFrame(i, para.m_fps);
            float act_value = hfp->GetValue(time);
            add_value.Add(act_value);
        }
    }

    for (int i = startframe; i <= endframe; ++i) {
        time.SetFrame(i, para.m_fps);
        double act_second = time.GetSecondsDouble();
        float value = para.m_minf + GetWaveValue(act_second) * high_value;
        if (factor_value != 1.F)
            value /= factor_value;
        if (para.add_tocurrentvalue) {
            value += add_value.GetAt(i);
        } else {
            if (value < para.m_minf) {
                value = para.m_minf;
            }
            if (value > para.m_maxf) {
                value = para.m_maxf;
            }
        }
        if (value < min_val) {
            value = min_val;
        }
        if (value > max_val) {
            value = max_val;
        }
        hfp->StoreValue(time, value, FALSE);
        if (para.m_halfframe) {
            if (i < endframe) {
                time += time_halfframe;
                act_second = time.GetSecondsDouble();
                value = para.m_minf + GetWaveValue(act_second) * high_value;
                if (factor_value != 1.F)
                    value /= factor_value;
                if (para.add_tocurrentvalue) {
                    value += add_value.GetAt(i);
                } else {
                    if (value < para.m_minf) {
                        value = para.m_minf;
                    }
                    if (value > para.m_maxf) {
                        value = para.m_maxf;
                    }
                }
                if (value < min_val) {
                    value = min_val;
                }
                if (value > max_val) {
                    value = max_val;
                }
                hfp->StoreValue(time, value, FALSE);
            }
        }
    }
    return TRUE;
}

BOOL CAmplitudeApp::WorkColor() {
    const auto hfp = (HColorProperty *)para.m_property;
    auto *hfpinfo = (HColorPropertyInfo *)hfp->GetPropertyInfo();
    Vector factor_value;
    factor_value.x = hfpinfo->GetRed()->GetFactorValue();
    factor_value.y = hfpinfo->GetGreen()->GetFactorValue();
    factor_value.z = hfpinfo->GetBlue()->GetFactorValue();
    Vector min_col, max_col;
    min_col.x = GetRValue(para.m_minc);
    min_col.y = GetGValue(para.m_minc);
    min_col.z = GetBValue(para.m_minc);

    max_col.x = GetRValue(para.m_maxc);
    max_col.y = GetGValue(para.m_maxc);
    max_col.z = GetBValue(para.m_maxc);

    CArray<Vector, Vector &> col_array;
    constexpr double step1 = 1.0 / 65536;
    Vector test;
    const Vector m1 = max_col - min_col;
    for (int i = 0; i <= 65536; ++i) {
        test = m1 * (step1 * i);
        if (test.x < 0)
            test.x += 255;
        if (test.y < 0)
            test.y += 255;
        if (test.z < 0)
            test.z += 255;
        col_array.Add(test);
    }

    const int startframe = para.m_wave.m_startpos.GetFrameInt(para.m_fps);
    const int endframe = para.m_wave.m_endpos.GetFrameInt(para.m_fps);
//    Vector average_value = (min_col + max_col) / 2.F;
    Time time;
    double stepend = 1.0 / para.m_fps;
    stepend /= 2.0;
//    double step = 1.0 / para.m_wave.GetSampleRate();
//    int highest_left = 0;
//    int highest_right = 0;
//    int value_left;
//    int value_right;
//    Vector value;
    Time time_halfframe;
    time_halfframe.SetSeconds(stepend);
    RGBFloat color;
    for (int i = startframe; i <= endframe; ++i) {
        time.SetFrame(i, para.m_fps);
        double act_second = time.GetSecondsDouble();
        int index = RoundValue(GetWaveValue(act_second) * 65536);
        if (index > 65536)
            index = 65536;
        test = col_array.GetAt(index);
        test /= factor_value;
        color.Set(test.x, test.y, test.z);
        hfp->StoreValue(time, color, FALSE);
        if (para.m_halfframe) {
            if (i < endframe) {
                time += time_halfframe;
                act_second = time.GetSecondsDouble();
                index = RoundValue(GetWaveValue(act_second) * 65536);
                if (index > 65536)
                    index = 65536;
                test = col_array.GetAt(index);
                test /= factor_value;
                color.Set(test.x, test.y, test.z);
                hfp->StoreValue(time, color, FALSE);
            }
        }
    }

    for (HPropertyDriver *hpd = hfp->GetHeadDriver(); hpd; hpd = hpd->GetNextDriver()) {
        hpd->Reduce(1);
        if (hpd->IsSimpleDriverShortcut()) {
            if (auto *hds = (HDriverShortcut *)hpd) {
                if (const HChannelDriver *hdc = (HChannelDriver *)hds->GetDriver()) {
                    hdc->SetInterpolationMethod(CPI_LINEAR);
                }
            }
        }
    }
    return TRUE;
}

BOOL CAmplitudeApp::WorkInt() {
    const auto hfp = (HIntProperty *)para.m_property;
    const HIntPropertyInfo *hfpinfo = (HIntPropertyInfo *)hfp->GetPropertyInfo();
//    const int factor_value = 1;
    const int min_val = hfpinfo->GetMinValue();
    const int max_val = hfpinfo->GetMaxValue();

    const int startframe = para.m_wave.m_startpos.GetFrameInt(para.m_fps);
    const int endframe = para.m_wave.m_endpos.GetFrameInt(para.m_fps);
    const int high_value = para.m_maxi - para.m_mini;
    Time time;
    Time time_halfframe;
    time_halfframe.SetSeconds(m_stepend);
    CArray<int, int &> add_value;
    if (para.add_tocurrentvalue) {
        for (int i = startframe; i <= endframe; ++i) {
            time.SetFrame(i, para.m_fps);
            int act_value = hfp->GetValue(time);
            add_value.Add(act_value);
        }
    }

    for (int i = startframe; i <= endframe; ++i) {
        time.SetFrame(i, para.m_fps);
        double act_second = time.GetSecondsDouble();
        int value = RoundValue(para.m_mini + GetWaveValue(act_second) * high_value);
//        if (factor_value != 1.F)
//            value /= factor_value;
        if (para.add_tocurrentvalue) {
            value += add_value.GetAt(i);
        } else {
            if (value < para.m_mini) {
                value = para.m_mini;
            }
            if (value > para.m_maxi) {
                value = para.m_maxi;
            }
        }
        if (value < min_val) {
            value = min_val;
        }
        if (value > max_val) {
            value = max_val;
        }
        hfp->StoreValue(time, value, FALSE);
        if (para.m_halfframe) {
            if (i < endframe) {
                time += time_halfframe;
                act_second = time.GetSecondsDouble();
                value = RoundValue(para.m_mini + GetWaveValue(act_second) * high_value);
//                if (factor_value != 1.F)
//                    value /= factor_value;
                if (para.add_tocurrentvalue) {
                    value += add_value.GetAt(i);
                } else {
                    if (value < para.m_mini) {
                        value = para.m_mini;
                    }
                    if (value > para.m_maxi) {
                        value = para.m_maxi;
                    }
                }
                if (value < min_val) {
                    value = min_val;
                }
                if (value > max_val) {
                    value = max_val;
                }
                hfp->StoreValue(time, value, FALSE);
            }
        }
    }
    return TRUE;
}

#ifdef _DEBUG
BOOL CAmplitudeApp::Work() const {

    const int azframes = para.m_chorlength.GetFrameInt(para.m_fps);
    const float average_value = (para.m_minf + para.m_maxf) / 2.F;
    for (int i = 0; i < azframes; ++i) {
        Time time;
        time.SetFrame(i, para.m_fps);
        PCMSample_16bitStereo all_sample;
        all_sample.left = 0;
        all_sample.right = 0;
        int test = 0;
        for (double j = 0; j < 1.0 / para.m_fps; j += 1.0 / para.m_wave.GetSampleRate(), test++) {
            const double pos = j + time.GetSecondsDouble();
            const PCMSample_16bitStereo sample = para.m_wave.GetSample(pos);
            all_sample.left += sample.left;
            all_sample.right += sample.right;
        }
        float value = hash_math::abs((float)all_sample.left / MAX16BIT);
        value *= average_value;
        if (value < para.m_minf) {
            ASSERT(false);
        }
        if (value > para.m_maxf) {
            ASSERT(false);
        }
        if (para.m_objtype == HOT_FLOAT) {
                const HFloatProperty *hfp = (HFloatProperty *)para.m_property;
                hfp->StoreValue(time, value, FALSE);
        }
    }
    return TRUE;
}
#endif
