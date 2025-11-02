// RC  4/29/2002  \Randy95\Plugin\HXT\3DS\Archive.h
#pragma once

#include "StdAfx.h"
#ifndef __VECTOR4_H
#include "Vector4.h"
#endif
#ifndef __MATRIX34_H
#include "Matrix34.h"
#endif

inline CArchive &operator >>(CArchive &ar, Vector2 &v) {
    return ar >> v.x >> v.y;
}

inline CArchive &operator >>(CArchive &ar, Vector &v) {
    return ar >> v.x >> v.y >> v.z;
}

inline CArchive &operator >>(CArchive &ar, Vector4 &v) {
    float x, y, z, w;
    ar >> x >> y >> z >> w;
    v.Set(x, y, z, w);
    return ar;
}

inline CArchive &operator >>(CArchive &ar, Matrix34 &m) {
    Vector4 v0, v1, v2;
    ar >> v0 >> v1 >> v2;
    m.Set(v0, v1, v2);
    return ar;
}

inline CString ReadString(CArchive &ar) {
    char c;
    CString string;

    while (ar.Read(&c, 1)) {
        if (c == '\0')
            break;
        string += c;
    }
    return string;
}

inline void WriteString(CArchive &ar, const CString &string) {
    ar.Write(string, string.GetLength());
    ar << '\0';
}

static DWORD GetPosition(CArchive &ar) {
    ar.Flush();
    return ar.GetFile()->GetPosition();
}

static DWORD SetPosition(CArchive &ar, const DWORD pos) {
    ar.Flush();
    return ar.GetFile()->Seek(pos, CFile::begin);
}
