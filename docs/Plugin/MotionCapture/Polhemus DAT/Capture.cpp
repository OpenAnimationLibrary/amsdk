// Dan  3/1/01  \Dan90\Plugin\MotionCapture\Polhemus DAT\Capture.cpp

// ReSharper disable CppAssignedValueIsNeverUsed
// ReSharper disable CppClangTidyCertErr33C
#include "StdAfx.h"
#include "Capture.h"
#include "Matrix34.h"
#include "F_Protos.h"
#include "MotionCaptureApp.h"
#include "HashMath.h"
#include <cstdio>

HProperty *Driver::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_scalefactortype;
        case 1:
            return m_filename;
        default:
            return nullptr;
    }
}

int Driver::GetSensorCount(FILE *file, int &recordsize) {
    char buffer[256];
    int framesize, headersize;

    if (fgets(buffer, 256, file) == nullptr)
        return 0;
    if (sscanf_s(buffer, "%*s %*d %*s %d %*s %d %*s %d", &framesize, &headersize, &recordsize) != 3)
        return 0;
    return (framesize - headersize) / recordsize;
}

namespace {
    Matrix34 CreateQuatMatrix(const float q0, const float q1, const float q2, const float q3) {
        const float sq0 = q0 * q0;
        const float sq1 = q1 * q1;
        const float sq2 = q2 * q2;
        const float sq3 = q3 * q3;
        return Matrix34(Vector4(2 * (q1 * q2 - q0 * q3), 2 * (q1 * q3 + q0 * q2), sq0 + sq1 - sq2 - sq3, 0.F), Vector4(sq0 - sq1 + sq2 - sq3, 2 * (q2 * q3 - q0 * q1), 2 * (q3 * q0 + q1 * q2), 0.F), Vector4(2 * (q1 * q0 - q3 * q2), sq0 - sq1 - sq2 + sq3, 2 * (q1 * q3 - q0 * q2), 0.F));
    }

    Matrix34 CreatePolhemusMatrix(const float az, const float el, const float roll) {

        const float cr = hash_math::cos(roll / hash_constants::radians);
        const float sr = hash_math::sin(roll / hash_constants::radians);
        const float ce = hash_math::cos(el / hash_constants::radians);
        const float se = hash_math::sin(el / hash_constants::radians);
        const float ca = hash_math::cos(az / hash_constants::radians);
        const float sa = hash_math::sin(az / hash_constants::radians);

        /* The composition matrix is composed in the following order:
         *           roll       x
         *           elevation  y
         *           azimuth    z
         */
        return Matrix34(Vector4(sa * cr + ca * se * sr, sa * sr - ca * se * cr, ca * ce, 0.F), Vector4(ca * cr - sa * se * sr, ca * sr + sa * se * cr, -sa * ce, 0.F), Vector4(-ce * sr, ce * cr, se, 0.F));
    }
}

BOOL Driver::ReadOneFrame(FILE *file, float frame) {
    char newdata;
    int card, sensor, count;
    float f[8];

    if (m_scalefactortype->GetValue() == CMCApp::CENTIMETERS)
        m_scalefactor = CENTIMETERSPERINCH;
    else
        m_scalefactor = 1.F;
    for (int i = 0; i < 2; ++i) {
        char buffer[256];
        int framesize, recordsize, headersize;
        if (fgets(buffer, 256, file) == nullptr)
            return FALSE;
        //      String errorstring = strerror( ferror( file ) ); 
        if (sscanf_s(buffer, "%*s %*d %*s %d %*s %d %*s %d", &framesize, &headersize, &recordsize) != 3)
            return FALSE;
        const int sensorcount = (framesize - headersize) / recordsize;

        for (int line = 0; line < sensorcount; line++) {
            if (m_isbinary) {
                const int bytesread = fread(buffer, sizeof(char), recordsize, file);
                if (bytesread != recordsize) {
                    //               int isend = feof(file);
                    //               String errorstring = strerror( ferror( file ) ); 
                    fclose(file);
                    return FALSE;
                }
                //            count = sscanf( buffer, "%*1c%1d%1*c%1d", &card, &sensor );
                count = sscanf_s(buffer, "%*1c%1d%*1c%1d", &card, &sensor);
                if (count != 2)
                    continue;
                char *ptr = buffer + 5;
                count = (recordsize - 5) / sizeof(float);
                for (int i1 = 0; i1 < count; ++i1) {
                    f[i1] = *(float *)ptr;
                    ptr += sizeof(float);
                }
            } else {
                if (fgets(buffer, 256, file) == nullptr)
                    return FALSE;
                ASSERT(false && "Parameter list");
                count = sscanf_s(buffer, "%*1c%1d%1c%1d%*1c %f %f %f %f %f %f %f", &card, &newdata, &sensor, &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7]);
//                count = sscanf_s(buffer, "%*1c%1d%1c%*1c%1d %f %f %f %f %f %f %f", &card, &newdata, &sensor, &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7]);
                count -= 3;
            }

            if (i == 1) {
                // newdata == '1' || newdata == '*' ) {
                [[maybe_unused]] BOOL rc;
                const WORD n = card * SENSORSPERCARD + sensor - 1;
                switch (count) {
                    case 7:
                    {
                        // TRANSLATE, QUAT
                        f[0] *= m_scalefactor;
                        f[1] *= m_scalefactor;
                        f[2] *= m_scalefactor;
                        rc = SetValue(n, XTRANS, f[0]);
                        rc = SetValue(n, YTRANS, f[1]);
                        rc = SetValue(n, ZTRANS, f[2]);
                        rc = StoreRotate(n, CreateQuatMatrix(f[3], f[4], f[5], f[6]));
                        break;
                    }
                    case 6: // TRANSLATE, EULER
                        f[0] *= m_scalefactor;
                        f[1] *= m_scalefactor;
                        f[2] *= m_scalefactor;
                        rc = SetValue(n, XTRANS, f[0]);
                        rc = SetValue(n, YTRANS, f[1]);
                        rc = SetValue(n, ZTRANS, f[2]);
                        rc = StoreRotate(n, CreatePolhemusMatrix(f[3], f[4], f[5]));
                        break;
                    case 4: // QUAT
                        rc = StoreRotate(n, CreateQuatMatrix(f[0], f[1], f[2], f[3]));
                        break;
                    case 3: // TRANSLATE
                        f[0] *= m_scalefactor;
                        f[1] *= m_scalefactor;
                        f[2] *= m_scalefactor;
                        rc = SetValue(n, XTRANS, f[0]);
                        rc = SetValue(n, YTRANS, f[1]);
                        rc = SetValue(n, ZTRANS, f[2]);
                        break;
                    default:
                        return FALSE;
                }
            }
        }
    }
    return TRUE;
}

BOOL Driver::SkipOneFrame(FILE *file) const {
    int recordsize;
    for (int i = 0; i < 2; ++i) {
        const int sensorcount = GetSensorCount(file, recordsize);
        for (int line = 0; line < sensorcount; line++) {
            char buffer[256];
            if (m_isbinary) {
                const int bytesread = fread(buffer, sizeof(char), recordsize, file);
                if (bytesread != recordsize)
                    return FALSE;
            } else {
                if (fgets(buffer, sizeof buffer, file) == nullptr)
                    return FALSE;
            }
        }
    }
    return TRUE;
}

bool Driver::StaticCaptureSequence() {
    String datname;
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest("Open Polhemus DAT File", "Polhemus DAT Files (*.dat)|*.dat|TEXT|All Files (*.*)|*.*|****||", datname, "dat", "DAT"))
            return TRUE;
    }
    FILE *file;
    if (fopen_s(&file, datname.Get(), "rb") != 0)
        return FALSE;

    char buffer[256];
    BOOL done = FALSE;

    //test for binary or ascii format //not perfect if it fails use a BoolProperty instead (it was that way)
    if (fgets(buffer, 256, file) == nullptr)
        return FALSE;
    if (fgets(buffer, 256, file) == nullptr)
        return FALSE;
    if (buffer[5] == ' ' || buffer[5] == '-')
        m_isbinary = FALSE;
    else
        m_isbinary = TRUE;
    if (!isdigit(buffer[6]))
        m_isbinary = TRUE;
    fseek(file, 0, SEEK_SET);

    int recordsize;
    //count and build sensors
    const int sensorcount = GetSensorCount(file, recordsize);
    if (sensorcount == 0) {
        fclose(file);
        return FALSE;
    }
    if (!BuildSensorArray(sensorcount + 1))
        return FALSE;
    int card;
    int sensor;
    for (int line = 0; line < sensorcount; line++) {
        if (m_isbinary) {
            if (fread(buffer, sizeof(byte), recordsize, file) != (UINT)recordsize) {
                fclose(file);
                return FALSE;
            }
        } else {
            if (fgets(buffer, 256, file) == nullptr) {
                fclose(file);
                return FALSE;
            }
        }
        const int count = sscanf_s(buffer, "%*1c%1x%*1c%1d", &card, &sensor);
        if (count != 2) {
            fclose(file);
            return FALSE;
        }
        const int sensornum = card * SENSORSPERCARD + sensor - 1;
        sprintf_s(buffer, 256, "Sensor %d-%d", card, sensor);
        InsertSensor(sensornum, buffer);
    }

    const float systemrate = GetSystemRate();
    const float capturerate = GetCaptureRate();
    float framestep;
    if (capturerate)
        framestep = systemrate / capturerate;
    else
        framestep = 0.F;
    float lastframe = -framestep;
    //capture frames
    fseek(file, 0, SEEK_SET);
    float frame = GetFrame();
    do {
        if (frame - lastframe >= framestep) {
            if (!ReadOneFrame(file, frame))
                done = TRUE;
            Redraw();
            lastframe = frame;
        } else {
            if (!SkipOneFrame(file))
                done = TRUE;
        }
        frame += systemrate / 30.0f;
        if (capturerate) //uses only one frame if nullptr
            SetFrame(frame);
    } while (!EscapeKeyDown() && !feof(file) && !done);
    fclose(file);

    FreeSensorArray();
    return TRUE;
}
