// WEP  4/12/2005  \will120\Plugin\MotionCapture\Polhemus Network\Capture.cpp

// ReSharper disable CppAssignedValueIsNeverUsed
// ReSharper disable CppClangTidyCertErr33C
#include "StdAfx.h"
#include "Capture.h"
#include "Matrix34.h"
#include "MotionCaptureApp.h"
#include <winsock.h>
#include <ctime>

HProperty *Driver::GetPropertyAt(const int i) {
    switch (i) {
        case 0:
            return m_scalefactortype;
        case 1:
            return m_isbinary;
        case 2:
            return m_ipaddress;
        case 3:
            return m_port;
        case 4:
            return m_timeout;
        default:
            return nullptr;
    }
}

float Driver::GetSeconds() {
    return (float)clock() / CLOCKS_PER_SEC;
}

int Driver::WriteUltra(const char *text) const {
    timeval timeout{};
    ZeroMemory(&timeout, sizeof timeout);
    fd_set wrtfds;
    FD_ZERO(&wrtfds);
    int flag = 0, status = 0;

    while (!flag) {
        FD_SET(m_outsock, &wrtfds);
        flag = select(m_outsock + 1, nullptr, &wrtfds, nullptr, &timeout);
        flag = FD_ISSET(m_outsock, &wrtfds);
        if (flag)
            status = send(m_outsock, text, strlen(text), 0);
    }
    return status;
}

BOOL Driver::ReadUltra(char *buffer, const int limit) const {
    [[maybe_unused]] int count = 0;
    int framesize;
    const float starttime = GetSeconds();

    //CConnectDlg *dlg = new CConnectDlg();
    int bytes = 0;
    do {
        const int err = recv(m_insock, buffer, limit, 0);
        if (err == SOCKET_ERROR) {
            [[maybe_unused]] int temp = WSAGetLastError();
            count++;
        } else if (err)
            bytes = err;
        else
            count++;
        if (bytes) {
            buffer[bytes] = '\0';
            if (sscanf_s(buffer, "%*s %*d %*s %d", &framesize) != 1 || bytes != framesize)
                bytes = 0;
        }
    } while (bytes == 0 && GetSeconds() - starttime < m_timeout->GetValue());
    //delete dlg;

    if (bytes == 0) {
        String msg = "ERROR 9: After %1 Seconds, No full packet received. packets from ascii format with all sensors active are to large";
        msg.Replace("%1", m_timeout->GetValue());
        AfxMessageBox(msg.Get());
        //      AfxMessageBox( "ERROR 9: After %1 Seconds, No full packet received. packets from ascii format with all sensors active are to large"
    }
    return bytes != 0;
}

static char *StrToken(char *s1, const char *s2) // JUST LIKE strtok, BUT SKIPS 
{
    // 2 DELIMITERS IN A ROW ie a:\temp
    static char *p;

    if (s1)
        p = s1;
    else
        *p = s2[0];
    while (strchr(s2, *p))
        p++;

    char *start = p;
    while (!strchr(s2, *p))
        p++;

    *p = '\0';
    return start;
}

int Driver::GetMaxSensorIndex() const {
    char packet[1700];
    for (int i = 0; i < 5; ++i) {
        if (!ReadUltra(packet, sizeof packet))
            return 0;
    }
    const char *buffer = StrToken(packet, "\r\n");
    int framesize, headersize, recordsize;
    int count = sscanf_s(buffer, "%*s %*d %*s %d %*s %d %*s %d", &framesize, &headersize, &recordsize);
    if (count != 3)
        return 0;

    const int sensorcount = (framesize - headersize) / recordsize;
    int card, sensor, maxindex = 0;
    if (m_isbinary->GetValue()) {
        const char *ptr = buffer + headersize;
        for (int line = 0; line < sensorcount; line++) {
            count = sscanf_s(ptr, "%*1c%1d%*1c%1d", &card, &sensor);
            if (count != 2)
                continue;
            maxindex = MAX(maxindex, card * SENSORSPERCARD + sensor - 1);
            ptr += recordsize;
        }
    } else {
        for (int line = 0; line < sensorcount; line++) {
            buffer = StrToken(nullptr, "\r\n");
            count = sscanf_s(buffer, "%*1c%1d%*1c%1d", &card, &sensor);
            if (count != 2)
                continue;
            maxindex = MAX(maxindex, card * SENSORSPERCARD + sensor - 1);
        }
    }
    return maxindex;
}

BOOL Driver::InsertSensors() const {
    char packet[1700];
    if (!ReadUltra(packet, sizeof packet))
        return FALSE;
    char *buffer = StrToken(packet, "\r\n");
    int framesize, headersize, recordsize;
    int count = sscanf_s(buffer, "%*s %*d %*s %d %*s %d %*s %d", &framesize, &headersize, &recordsize);
    if (count != 3)
        return FALSE;
    const int sensorcount = (framesize - headersize) / recordsize;
    int sensor, card, sensornum;
    if (m_isbinary->GetValue()) {
        const char *ptr = buffer + headersize;
        for (int line = 0; line < sensorcount; line++) {
            count = sscanf_s(ptr, "%*1c%1d%*1c%1d", &card, &sensor);
            if (count != 2)
                continue;
            sensornum = card * SENSORSPERCARD + sensor - 1;
            sprintf_s(buffer, 1700, "Sensor %d-%d", card, sensor);
            InsertSensor(sensornum, buffer);
            ptr += recordsize;
        }
    } else {
        for (int line = 0; line < sensorcount; line++) {
            buffer = StrToken(nullptr, "\r\n");
            count = sscanf_s(buffer, "%*1c%1d%*1c%1d", &card, &sensor);
            if (count != 2)
                continue;
            sensornum = card * SENSORSPERCARD + sensor - 1;
            sprintf_s(buffer, 1700, "Sensor %d-%d", card, sensor);
            InsertSensor(sensornum, buffer);
        }
    }
    return TRUE;
}

bool Driver::LiveCaptureInit() {
    ULONG wopt;
    WSADATA WsaData;
    SOCKADDR_IN localaddr;
    SOCKADDR_IN remoteaddr;

    int err = WSAStartup(0x0101, &WsaData);
    if (err == SOCKET_ERROR) {
        AfxMessageBox("ERROR 3: Can't Initialize TCP/IP Sockets Library.");
        return FALSE;
    }
    m_insock = socket(PF_INET, SOCK_DGRAM, 0);
    if (m_insock == (UINT_PTR)SOCKET_ERROR) {
        AfxMessageBox("ERROR 4: Can't Create Input Socket.");
        return FALSE;
    }
    ZeroMemory(&localaddr, sizeof localaddr);
    localaddr.sin_family = PF_INET;
    localaddr.sin_port = htons(m_port->GetValue());
    err = bind(m_insock, (PSOCKADDR)&localaddr, sizeof localaddr);
    if (err == SOCKET_ERROR) {
        AfxMessageBox("ERROR 5: Can't Bind Input Socket for IP Port.");
        return FALSE;
    }
    wopt = 1;
    if (ioctlsocket(m_insock, FIONBIO, &wopt)) {
        AfxMessageBox("ERROR 6: Can't Create I/O Control Socket for Input.");
        return FALSE;
    }
    // OUT
    m_outsock = socket(PF_INET, SOCK_DGRAM, 0);
    if (m_outsock == (UINT_PTR)SOCKET_ERROR) {
        AfxMessageBox("ERROR 7: Can't Create Output Socket.");
        return FALSE;
    }
    // ReSharper disable once CppDeprecatedEntity
    remoteaddr.sin_addr.s_addr = inet_addr(m_ipaddress->GetValue());
    remoteaddr.sin_family = PF_INET;
    remoteaddr.sin_port = htons(m_port->GetValue());
    wopt = 1;
    if (ioctlsocket(m_outsock, FIONBIO, &wopt)) {
        AfxMessageBox("ERROR 8: Can't Connect to Output Control Socket for IP Address: ");
        return FALSE;
    }
    [[maybe_unused]] int rc_connect = WriteUltra("[RUN]\n");

    const int maxsensors = GetMaxSensorIndex() + 1;
    if (maxsensors == 1) {
        LiveCaptureClose();
        return FALSE;

    }
    if (!BuildSensorArray(maxsensors)) {
        LiveCaptureClose();
        return FALSE;
    }
    if (!InsertSensors()) {
        LiveCaptureClose();
        return FALSE;
    }

    if (m_scalefactortype->GetValue() == CMCApp::CENTIMETERS)
        m_scalefactor = CENTIMETERSPERINCH;
    else
        m_scalefactor = 1.F;

    return TRUE;
}

namespace {
    Matrix34 CreateQuatMatrix(const float q0, const float q1, const float q2, const float q3) // wxyz
    {
        const float sq0 = q0 * q0;
        const float sq1 = q1 * q1;
        const float sq2 = q2 * q2;
        const float sq3 = q3 * q3;
        return Matrix34(Vector4(2 * (q1 * q2 - q0 * q3), 2 * (q1 * q3 + q0 * q2), sq0 + sq1 - sq2 - sq3, 0.F), Vector4(sq0 - sq1 + sq2 - sq3, 2 * (q2 * q3 - q0 * q1), 2 * (q3 * q0 + q1 * q2), 0.F), Vector4(2 * (q1 * q0 - q3 * q2), sq0 - sq1 - sq2 + sq3, 2 * (q1 * q3 - q0 * q2), 0.F));
        // swapped xyz columns to yzx columns
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
        // swapped xyz columns to yzx columns
    }
}

BOOL Driver::StoreTranslate(const int sensornum, float x, float y, float z) const {
    x *= m_scalefactor;
    y *= m_scalefactor;
    z *= m_scalefactor;
    if (!SetValue(sensornum, XTRANS, x))
        return FALSE;
    if (!SetValue(sensornum, YTRANS, y))
        return FALSE;
    if (!SetValue(sensornum, ZTRANS, z))
        return FALSE;
    return TRUE;
}

BOOL Driver::StoreData(const int sensornum, const float *f, const int count) const {
    switch (count) {
        case 7: // TRANSLATE & QUAT
            if (!StoreTranslate(sensornum, f[0], f[1], f[2]))
                return FALSE;
            return StoreRotate(sensornum, CreateQuatMatrix(f[3], f[4], f[5], f[6]));
        case 6: // TRANSLATE, EULER
            if (!StoreTranslate(sensornum, f[0], f[1], f[2]))
                return FALSE;
            return StoreRotate(sensornum, CreatePolhemusMatrix(f[3], f[4], f[5]));
        case 4: // QUAT
            return StoreRotate(sensornum, CreateQuatMatrix(f[0], f[1], f[2], f[3]));
        case 3: // TRANSLATE
            return StoreTranslate(sensornum, f[0], f[1], f[2]);
        default: 
    return TRUE;
    }
}

Driver::FrameError Driver::LiveCaptureFrame() {

    char packet[1700];
    if (!ReadUltra(packet, sizeof packet))
        return FE_FAILED;
    char *buffer = StrToken(packet, "\r\n");
    int framesize, headersize, recordsize;
    if (sscanf_s(buffer, "%*s %*d %*s %d %*s %d %*s %d", &framesize, &headersize, &recordsize) != 3) {
        AfxMessageBox("ERROR 10: Invalid Header on Data Packet.");
        return FE_FAILED;
    }
    const int sensorcount = (framesize - headersize) / recordsize;
    char newdata;
    int card, sensor, count, sensornum;
    float f[8];
    if (m_isbinary->GetValue()) {
        char *ptr = buffer + headersize;
        for (int line = 0; line < sensorcount; line++) {
            count = sscanf_s(ptr, "%*1c%1d%*1c%1d", &card, &sensor);
            if (count != 2)
                continue;
            sensornum = card * SENSORSPERCARD + sensor - 1;
            ptr += 5;
            count = (recordsize - 5) / sizeof(float);
            for (int i = 0; i < count; ++i) {
                f[i] = *(float *)ptr;
                ptr += sizeof(float);
            }
            if (!StoreData(sensornum, f, count))
                return FE_FAILED;
        }
    } else {
        for (int line = 0; line < sensorcount; line++) {
            buffer = StrToken(nullptr, "\r\n");
             ASSERT(false && "Parameter list");
//            count = sscanf_s(buffer, "%*1c%1d%1c%1d%*1c%1d %f %f %f %f %f %f %f", &card, &newdata, &sensor, &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7]);
            count = sscanf_s(buffer, "%*1c%1d%1c%1d%*1c %f %f %f %f %f %f %f", &card, &newdata, &sensor, &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7]);
            count -= 3;
            if (count != 7 && count != 6 && count != 3 && count != 4) {
                //            AfxMessageBox( "ERROR 11: Unrecognized ASCII Data Format." );
                return FE_TRYAGAIN;
            }
            sensornum = card * SENSORSPERCARD + sensor - 1;
            if (!StoreData(sensornum, f, count))
                return FE_FAILED;
        }
    }
    return FE_SUCCESS;
}

void Driver::LiveCaptureClose() {
    if (m_outsock) {
        [[maybe_unused]] const int rc_write = WriteUltra("[STOP]\n");
        ASSERT(rc_write);
    }

    closesocket(m_insock);
    closesocket(m_outsock);
    WSACleanup();
    FreeSensorArray();
}
