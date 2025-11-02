//BC  12/24/2003  \Bob110\Include\Matrix34.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "StdAfx.h"
#include "Exports.h"
#include "Matrix44.h"
#include "Matrix33.h"
#include "Rotate.h"

//size 48
class MATRIXEXPORT Matrix34 final {
    Vector4 v[3];

public:
    constexpr Matrix34() noexcept = default;
    constexpr Matrix34(const Vector4 &, const Vector4 &, const Vector4 &) noexcept;
    constexpr explicit Matrix34(float fillvalue) noexcept;
    explicit HASH_INLINE Matrix34(RotateVector rv) noexcept;
    explicit HASH_INLINE Matrix34(RotateEuler re) noexcept;
    explicit HASH_INLINE Matrix34(const Quaternion &) noexcept;
    explicit Matrix34(const TSQ &tsq) noexcept;

    Matrix34(const Matrix34 &other) = default;
    Matrix34 &operator=(const Matrix34 &other) = default;
    Matrix34(Matrix34 &&other) = default;
    Matrix34 &operator=(Matrix34 &&other) = default;
    ~Matrix34() = default;

    constexpr Matrix34 &operator *=(const Matrix34 &other) noexcept {
        *this = *this * other;
        return *this;
    }

    const Vector4 &operator [](const int row) const noexcept {
        ASSERT(row < 3);
        return v[row];
    }

    constexpr Vector4 &operator [](const int row) noexcept {
        ASSERT(row < 3);
        return v[row];
    }

    constexpr void Set(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2) noexcept;

    constexpr void SetIdentity() noexcept {
        v[0].Set(1.F, 0.F, 0.F, 0.F);
        v[1].Set(0.F, 1.F, 0.F, 0.F);
        v[2].Set(0.F, 0.F, 1.F, 0.F);
    }

    [[nodiscard]] constexpr Matrix34 Transpose() const noexcept;
    [[nodiscard]] HASH_INLINE Matrix34 Inverse() const noexcept;
    constexpr void SetTranslate(Vector translate) noexcept;
    [[nodiscard]] constexpr Vector GetTranslate() const noexcept;
    [[nodiscard]] constexpr Matrix34 NoTranslate() const noexcept;
    [[nodiscard]] HASH_INLINE Matrix34 GetScaleMatrix() const noexcept;
    [[nodiscard]] HASH_INLINE Vector GetScaleVector() const noexcept;

    bool operator==(const Matrix34 &other) const = default;
    bool operator!=(const Matrix34 &other) const = default;

    [[nodiscard]] constexpr Vector GetXAxis() const noexcept {
        return Vector(v[0][0], v[1][0], v[2][0]);
    }

    [[nodiscard]] constexpr Vector GetYAxis() const noexcept {
        return Vector(v[0][1], v[1][1], v[2][1]);
    }

    [[nodiscard]] constexpr Vector GetZAxis() const noexcept {
        return Vector(v[0][2], v[1][2], v[2][2]);
    }

    constexpr Matrix34 operator *(const Matrix34 &) const noexcept;

    [[nodiscard]] constexpr Matrix34 InvertRotateTranslate() const noexcept {
        //THE MATRIX MUST HAVE NO SCALE
        Matrix34 rotate = Transpose();
        rotate.SetTranslate(rotate * -GetTranslate());
        return rotate;
    }

    [[nodiscard]] bool IsUpDir() const noexcept {
        const Vector updir = ToMatrix33(*this) * Vector(0.F, 1.F, 0.F);
        return hash_math::abs(updir.z) > 1.e-6F;
    }

    friend void swap(Matrix34 &a, Matrix34 &b) noexcept {
        const Matrix34 tmp(a);
        a = b;
        b = tmp;
    }

    friend Vector operator *(Vector v, const Matrix34 &m) noexcept;
    friend Vector operator *(const Matrix34 &m, Vector v) noexcept;
    constexpr friend MATRIXEXPORT Matrix34 Identity34() noexcept;

    //GL MATRIX CREATION FUNCTIONS
    friend MATRIXEXPORT Matrix34 Translatef(float x, float y, float z) noexcept;
    friend MATRIXEXPORT Matrix34 TranslateV(Vector v) noexcept;
    friend MATRIXEXPORT Matrix34 Scalef(float x, float y, float z) noexcept;
    friend MATRIXEXPORT Matrix34 ScaleV(Vector v) noexcept;
    friend MATRIXEXPORT Matrix34 RotateVRadians(float anglerad, Vector axis) noexcept;
    friend MATRIXEXPORT Matrix34 Rotatef(float angle, float x, float y, float z) noexcept;
    friend MATRIXEXPORT Matrix34 Rotate2V(Vector from, Vector to) noexcept;
    friend MATRIXEXPORT HASH_INLINE Matrix34 XRotateRadians(float anglerad) noexcept;
    friend MATRIXEXPORT HASH_INLINE Matrix34 YRotateRadians(float anglerad) noexcept;
    friend MATRIXEXPORT HASH_INLINE Matrix34 ZRotateRadians(float anglerad) noexcept;
    friend MATRIXEXPORT Matrix34 YXRotateRadians(float yangle, float xangle) noexcept;
    friend MATRIXEXPORT Matrix34 YXZRotateRadians(float yangle, float xangle, float zangle) noexcept;
    friend MATRIXEXPORT Matrix34 XZYRotate(float xangle, float zangle, float yangle) noexcept;
    friend MATRIXEXPORT Matrix34 VectorsToStandard(Vector zdir, Vector ydir) noexcept;
    friend MATRIXEXPORT Matrix34 StandardToVectors(Vector zdir, Vector ydir) noexcept;
    friend MATRIXEXPORT void TwoVectorsToAxisAngle(Vector from, Vector to, Vector &axis, float &radangle) noexcept;

    friend Matrix34 YXZRotate(float yangle, float xangle, float zangle) noexcept;
    friend Matrix34 RotateV(float angle, const Vector &axis) noexcept;
    friend Matrix34 XRotate(float angle) noexcept;
    friend Matrix34 YRotate(float angle) noexcept;
    friend Matrix34 ZRotate(float angle) noexcept;

    //CONVERSION FUNCTIONS
    friend MATRIXEXPORT Matrix44 ToMatrix44(const Matrix33 &m) noexcept;
    friend MATRIXEXPORT Matrix44 ToMatrix44(const Matrix34 &m) noexcept;
    friend MATRIXEXPORT Matrix33 ToMatrix33(const Matrix34 &m) noexcept;
    friend MATRIXEXPORT Matrix33 ToMatrix33(const Matrix44 &m) noexcept;
    friend MATRIXEXPORT Matrix34 ToMatrix34(const Matrix44 &m) noexcept;
    friend MATRIXEXPORT Matrix34 ToMatrix34(const Matrix33 &m) noexcept;

    friend MATRIXEXPORT void MatrixTimesScale(Matrix34 &a, const Vector &s) noexcept {
        if (s != Vector(1.F))
            a.Set(Vector4(a[0][0] * s.x, a[0][1] * s.y, a[0][2] * s.z, a[0][3]), Vector4(a[1][0] * s.x, a[1][1] * s.y, a[1][2] * s.z, a[1][3]),
                  Vector4(a[2][0] * s.x, a[2][1] * s.y, a[2][2] * s.z, a[2][3]));
    }

    friend MATRIXEXPORT void ScaleTimesMatrix(const Vector &s, Matrix34 &a) noexcept {
        if (s != Vector(1.F))
            a.Set(Vector4(a[0][0] * s.x, a[0][1] * s.x, a[0][2] * s.x, a[0][3] * s.x), Vector4(a[1][0] * s.y, a[1][1] * s.y, a[1][2] * s.y, a[1][3] * s.y),
                  Vector4(a[2][0] * s.z, a[2][1] * s.z, a[2][2] * s.z, a[2][3] * s.z));
    }

    friend MATRIXEXPORT void TransformVectorNoTranslate(const Matrix34 &m, Vector &vv) noexcept {
        vv.Set(m[0][0] * vv.x + m[0][1] * vv.y + m[0][2] * vv.z, m[1][0] * vv.x + m[1][1] * vv.y + m[1][2] * vv.z, m[2][0] * vv.x + m[2][1] * vv.y + m[2][2] * vv.z);
    }

    friend Matrix34 CreateEulerMatrix(const Rotate &rotate) noexcept;
    friend void TransformVector(const Matrix34 &matrix, Vector &p) noexcept;

    friend Matrix34 Rotate2V_inline(const Vector &from, const Vector &to) noexcept;
    friend Matrix34 RotateVRadians_inline(float anglerad, const Vector &axis) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Matrix34 &val) {
        os << val[0] << " " << val[1] << " " << val[2] << " " << val[3];
        return os;
    }

};

//friends need a declaration outside the class

constexpr MATRIXEXPORT Matrix34 Identity34() noexcept;
MATRIXEXPORT Matrix34 Translatef(float x, float y, float z) noexcept;
MATRIXEXPORT Matrix34 TranslateV(Vector v) noexcept;
MATRIXEXPORT Matrix34 Scalef(float x, float y, float z) noexcept;
MATRIXEXPORT Matrix34 ScaleV(Vector v) noexcept;
MATRIXEXPORT Matrix34 RotateVRadians(float anglerad, Vector axis) noexcept;
MATRIXEXPORT Matrix34 Rotatef(float angle, float x, float y, float z) noexcept;
MATRIXEXPORT Matrix34 Rotate2V(Vector from, Vector to) noexcept;
MATRIXEXPORT HASH_INLINE Matrix34 XRotateRadians(float anglerad) noexcept;
MATRIXEXPORT HASH_INLINE Matrix34 YRotateRadians(float anglerad) noexcept;
MATRIXEXPORT HASH_INLINE Matrix34 ZRotateRadians(float anglerad) noexcept;
MATRIXEXPORT Matrix34 YXRotateRadians(float yangle, float xangle) noexcept;
MATRIXEXPORT Matrix34 YXZRotateRadians(float yangle, float xangle, float zangle) noexcept;
MATRIXEXPORT Matrix34 XZYRotate(float xangle, float zangle, float yangle) noexcept;
MATRIXEXPORT Matrix34 VectorsToStandard(Vector zdir, Vector ydir) noexcept;
MATRIXEXPORT Matrix34 StandardToVectors(Vector zdir, Vector ydir) noexcept;
MATRIXEXPORT Matrix44 ToMatrix44(const Matrix33 &m) noexcept;
MATRIXEXPORT Matrix44 ToMatrix44(const Matrix34 &m) noexcept;
MATRIXEXPORT Matrix33 ToMatrix33(const Matrix34 &m) noexcept;
MATRIXEXPORT Matrix33 ToMatrix33(const Matrix44 &m) noexcept;
MATRIXEXPORT Matrix34 ToMatrix34(const Matrix44 &m) noexcept;
MATRIXEXPORT Matrix34 ToMatrix34(const Matrix33 &m) noexcept;
MATRIXEXPORT void TwoVectorsToAxisAngle(Vector from, Vector to, Vector &axis, float &radangle) noexcept;

void TransformVector(const Matrix34 &matrix, Vector &p) noexcept;
Matrix34 Rotate2V_inline(Vector from, Vector to) noexcept;
Matrix34 RotateVRadians_inline(float anglerad, Vector axis) noexcept;

constexpr Matrix34 Matrix34::operator *(const Matrix34 &b) const noexcept {
#define ROWCOL(i,j) v[i][0]*b[0][j] + v[i][1]*b[1][j] + v[i][2]*b[2][j]
    return Matrix34(Vector4(ROWCOL(0, 0), ROWCOL(0, 1), ROWCOL(0, 2), ROWCOL(0, 3) + v[0][3]), Vector4(ROWCOL(1, 0), ROWCOL(1, 1), ROWCOL(1, 2), ROWCOL(1, 3) + v[1][3]),
                    Vector4(ROWCOL(2, 0), ROWCOL(2, 1), ROWCOL(2, 2), ROWCOL(2, 3) + v[2][3]));
}

HASH_INLINE Matrix34::Matrix34(const Quaternion &q) noexcept {
    const float nq = q.Norm();
    const float s = (nq > 0.F) ? (2.F / nq) : 0.F;
    const float qx = q.GetX();
    const float qy = q.GetY();
    const float xs = qx * s, ys = qy * s, zs = q.GetZ() * s;
    const float qw = -q.GetW();
    const float wx = qw * xs, wy = qw * ys, wz = qw * zs;
    const float xx = qx * xs, xy = qx * ys, xz = qx * zs;
    const float zz = q.GetZ() * zs, yy = qy * ys, yz = qy * zs;

    v[0].Set(1.F - (yy + zz), xy + wz, xz - wy, 0.F);
    v[1].Set(xy - wz, 1.F - (xx + zz), yz + wx, 0.F);
    v[2].Set(xz + wy, yz - wx, 1.F - (xx + yy), 0.F);
}

HASH_INLINE void TwoVectorsToAxisAngle(const Vector from, const Vector to, Vector &axis, float &radangle) noexcept {
    const float numerator = from.Dot(to);

    if (const float denominator = from.Norm() * to.Norm(); hash_math::abs(denominator - numerator) < 1e-6F) {
        //SAME DIR
        radangle = 0.F;
        axis = Vector(1.F, 0.F, 0.F);
    } else if (hash_math::abs(denominator + numerator) < 1e-6F) {
        //OPPOSITE DIR
        radangle = hash_constants::pi;
        if (from.Normalized().Absolute() != Vector(1.F, 0.F, 0.F)) {
            axis = from ^ Vector(1.F, 0.F, 0.F);
        } else {
            axis = from ^ Vector(0.F, 1.F, 0.F);
        }
    } else {
        if (const float ratio = numerator / denominator; ratio >= 1.F) {
            radangle = 0.F;
            axis = Vector(1.F, 0.F, 0.F);
        } else {
            radangle = hash_math::acos(ratio);
            axis = from ^ to;
        }
    }
}

HASH_INLINE Matrix34 YXZRotate(const float yangle, const float xangle, const float zangle) noexcept {
    return YXZRotateRadians(yangle * hash_constants::inverse_radians, xangle * hash_constants::inverse_radians, zangle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix34 RotateV(const float angle, const Vector axis) noexcept {
    return RotateVRadians(angle * hash_constants::inverse_radians, axis);
}

HASH_INLINE Matrix34 Rotatef(const float angle, const float x, const float y, const float z) noexcept {
    return RotateV(angle, Vector(x, y, z));
}

HASH_INLINE Matrix34 XRotate(const float angle) noexcept {
    return XRotateRadians(angle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix34 YRotate(const float angle) noexcept {
    return YRotateRadians(angle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix34 ZRotate(const float angle) noexcept {
    return ZRotateRadians(angle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix34::Matrix34(const RotateVector rv) noexcept {
    const float y = hash_math::atan2(rv.end.x, rv.end.z);
    if (const float x = hash_math::atan2(-rv.end.y, hash_math::sqrt(rv.end.x * rv.end.x + rv.end.z * rv.end.z)); rv.roll != 0.F) {
        *this = YXZRotateRadians(y, x, rv.roll * hash_constants::inverse_radians);
    } else {
        *this = YXRotateRadians(y, x);
    }
}

HASH_INLINE Matrix34 CreateEulerMatrix(const Rotate rotate) noexcept {
    if (rotate.IsZero()) {
        return Matrix34(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(0.F, 0.F, 1.F, 0.F));
    }
    const Matrix34 mat34 = YXZRotate(-rotate.roll, -rotate.swivel, -rotate.tilt);
    return mat34.Transpose();
}

HASH_INLINE Matrix34::Matrix34(const RotateEuler re) noexcept {
    if (re.IsZero()) {
        Set(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(0.F, 0.F, 1.F, 0.F));
    } else {
        *this = YXZRotate(re.y, re.x, re.z);
    }
}

//HASH_INLINE friend functions
//Vector operator *(const Vector &v, const Matrix34 &m);
//Vector operator *(const Matrix34 &m, const Vector &v);

HASH_INLINE Vector operator *(const Vector v, const Matrix34 &m) noexcept {
    return Vector(m.v[0].Dot(v), m.v[1].Dot(v), m.v[2].Dot(v));
}

HASH_INLINE Vector operator *(const Matrix34 &m, const Vector v) noexcept {
    return Vector(m.v[0].Dot(v), m.v[1].Dot(v), m.v[2].Dot(v));
}

HASH_INLINE void TransformVector(const Matrix34 &matrix, Vector &p) noexcept {
    p = matrix * p;
}

//regular inlined functions
constexpr void Matrix34::Set(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2) noexcept {
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}

constexpr Matrix34::Matrix34(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2) noexcept {
    Set(v0, v1, v2);
}

constexpr Matrix34::Matrix34(const float fillvalue) noexcept {
    v[0] = Vector4(fillvalue);
    v[1] = Vector4(fillvalue);
    v[2] = Vector4(fillvalue);
}

constexpr Matrix34 Identity34() noexcept {
    return Matrix34(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(0.F, 0.F, 1.F, 0.F));
}

constexpr void Matrix34::SetTranslate(const Vector translate) noexcept {
    v[0][3] = translate.x;
    v[1][3] = translate.y;
    v[2][3] = translate.z;
}

constexpr Vector Matrix34::GetTranslate() const noexcept {
    return Vector(v[0][3], v[1][3], v[2][3]);
}

constexpr Matrix34 Matrix34::NoTranslate() const noexcept {
    return Matrix34(Vector4(v[0][0], v[0][1], v[0][2], 0.F), Vector4(v[1][0], v[1][1], v[1][2], 0.F), Vector4(v[2][0], v[2][1], v[2][2], 0.F));
}

HASH_INLINE Matrix34 Matrix34::GetScaleMatrix() const noexcept {
    return Matrix34((Quaternion(*this).Inverse())) * NoTranslate();
}

HASH_INLINE Vector Matrix34::GetScaleVector() const noexcept {
    Matrix34 scalem = GetScaleMatrix();
    return Vector(scalem[0][0], scalem[1][1], scalem[2][2]);
}

HASH_INLINE Vector &Vector::operator *=(const Matrix34 &m) noexcept {
    *this = m * *this;
    return *this;
}

//------------ CONVERSION TO AND FROM OTHER TYPES -------------------

HASH_INLINE Matrix44 ToMatrix44(const Matrix34 &m) noexcept {
    return Matrix44(m[0], m[1], m[2], Vector4(0.F, 0.F, 0.F, 1.F));
}

HASH_INLINE Matrix44 ToMatrix44(const Matrix33 &m) noexcept {
    return Matrix44(Vector4(m[0][0], m[0][1], m[0][2], 0.F), Vector4(m[1][0], m[1][1], m[1][2], 0.F), Vector4(m[2][0], m[2][1], m[2][2], 0.F), Vector4(0.F, 0.F, 0.F, 1.F));
}

HASH_INLINE Matrix33 ToMatrix33(const Matrix34 &m) noexcept {
    return Matrix33(Vector(m[0][0], m[0][1], m[0][2]), Vector(m[1][0], m[1][1], m[1][2]), Vector(m[2][0], m[2][1], m[2][2]));
}

HASH_INLINE Matrix33 ToMatrix33(const Matrix44 &m) noexcept {
    return Matrix33(Vector(m[0][0], m[0][1], m[0][2]), Vector(m[1][0], m[1][1], m[1][2]), Vector(m[2][0], m[2][1], m[2][2]));
}

HASH_INLINE Matrix34 ToMatrix34(const Matrix44 &m) noexcept {
    return Matrix34(m[0], m[1], m[2]);
}

HASH_INLINE Matrix34 ToMatrix34(const Matrix33 &m) noexcept {
    return Matrix34(Vector4(m[0][0], m[0][1], m[0][2], 0.F), Vector4(m[1][0], m[1][1], m[1][2], 0.F), Vector4(m[2][0], m[2][1], m[2][2], 0.F));
}

HASH_INLINE Matrix34 StandardToVectors(const Vector zdir, const Vector ydir) noexcept {
    Vector ydir_normalized = ydir.Normalized();
    Vector zdir_normalized = zdir.Normalized();
    Vector xdir = Cross(ydir_normalized, zdir_normalized);
    if (const float xlength = xdir.Norm(); xlength != 1.F) {
        xdir /= xlength;
        ydir_normalized = Cross(zdir_normalized, xdir);
    }
    return Matrix34(Vector4(xdir[0], ydir_normalized[0], zdir_normalized[0], 0), Vector4(xdir[0], ydir_normalized[0], zdir_normalized[0], 0), Vector4(xdir[0], ydir_normalized[0], zdir_normalized[0], 0));
}

//-------------------- GL STYLE CREATION FUNCTIONS ----------------------

HASH_INLINE Matrix34 Translatef(const float x, const float y, const float z) noexcept {
    return Matrix34(Vector4(1.F, 0.F, 0.F, x), Vector4(0.F, 1.F, 0.F, y), Vector4(0.F, 0.F, 1.F, z));
}

HASH_INLINE Matrix34 TranslateV(const Vector v) noexcept {
    return Translatef(v[0], v[1], v[2]);
}

HASH_INLINE Matrix34 Scalef(const float x, const float y, const float z) noexcept {
    return Matrix34(Vector4(x, 0.F, 0.F, 0.F), Vector4(0.F, y, 0.F, 0.F), Vector4(0.F, 0.F, z, 0.F));
}

HASH_INLINE Matrix34 ScaleV(const Vector v) noexcept {
    return Scalef(v[0], v[1], v[2]);
}

HASH_INLINE Matrix34 XRotateRadians(const float anglerad) noexcept {
    const float ca = hash_math::cos(anglerad);
    const float sa = hash_math::sin(anglerad);
    constexpr Vector4 v1 = Vector4(1.F, 0.F, 0.F, 0.F);
    const Vector4 v2 = Vector4(0.F, ca, -sa, 0.F);
    const Vector4 v3 = Vector4(0.F, sa, ca, 0.F);
    return Matrix34(v1, v2, v3);
}

HASH_INLINE Matrix34 YRotateRadians(const float anglerad) noexcept {
    const float ca = hash_math::cos(anglerad);
    const float sa = hash_math::sin(anglerad);
    const Vector4 v1 = Vector4(ca, 0.F, sa, 0.F);
    constexpr Vector4 v2 = Vector4(0.F, 1.F, 0.F, 0.F);
    const Vector4 v3 = Vector4(-sa, 0.F, ca, 0.F);
    return Matrix34(v1, v2, v3);
}

HASH_INLINE Matrix34 ZRotateRadians(const float anglerad) noexcept {
    const float ca = hash_math::cos(anglerad);
    const float sa = hash_math::sin(anglerad);
    const Vector4 v1 = Vector4(ca, -sa, 0.F, 0.F);
    const Vector4 v2 = Vector4(sa, ca, 0.F, 0.F);
    constexpr Vector4 v3 = Vector4(0.F, 0.F, 1.F, 0.F);
    return Matrix34(v1, v2, v3);
}

//ROTATION CONVERSIONS THAT REQUIRE MATRIX34

HASH_INLINE RotateVector::RotateVector(const Matrix34 &matrix) noexcept {
    end = matrix.GetZAxis();
    const float y = hash_math::atan2(end.x, end.z);
    const float x = hash_math::atan2(-end.y, hash_math::sqrt(end.x * end.x + end.z * end.z));
    Vector rolldir = matrix.GetYAxis();
    rolldir *= YXRotateRadians(y, x).Transpose();
    roll = hash_math::atan2(-rolldir.x, rolldir.y) * hash_constants::radians;
}

HASH_INLINE RotateEuler::RotateEuler(const Matrix34 &matrix) noexcept {
    const Vector end = matrix.GetZAxis();
    y = hash_math::atan2(end.x, end.z);
    x = hash_math::atan2(-end.y, hash_math::sqrt(end.x * end.x + end.z * end.z));
    Vector rolldir = matrix.GetYAxis();
    rolldir *= YXRotateRadians(y, x).Transpose();
    z = hash_math::atan2(-rolldir.x, rolldir.y) * hash_constants::radians;
    x *= hash_constants::radians;
    y *= hash_constants::radians;
}

constexpr Matrix34 Matrix34::Transpose() const noexcept {
    return Matrix34(Vector4(v[0][0], v[1][0], v[2][0], 0.F), Vector4(v[0][1], v[1][1], v[2][1], 0.F), Vector4(v[0][2], v[1][2], v[2][2], 0.F));
}

HASH_INLINE Matrix34 Matrix34::Inverse() const noexcept {
    // ReSharper disable once CppLocalVariableMayBeConst
    Matrix44 a = ToMatrix44(*this);
    return ToMatrix34(a.Inverse());
}

HASH_INLINE Matrix34 RotateVRadians_inline(const float anglerad, const Vector axis) noexcept {
    const float c = hash_math::cos(anglerad);
    const float s = hash_math::sin(anglerad);
    const float t = 1.F - c;
    const Vector v = axis.Normalized();
    const Vector4 v1 = Vector4(t * v[0] * v[0] + c, t * v[0] * v[1] - s * v[2], t * v[0] * v[2] + s * v[1], 0.F);
    const Vector4 v2 = Vector4(t * v[0] * v[1] + s * v[2], t * v[1] * v[1] + c, t * v[1] * v[2] - s * v[0], 0.F);
    const Vector4 v3 = Vector4(t * v[0] * v[2] - s * v[1], t * v[1] * v[2] + s * v[0], t * v[2] * v[2] + c, 0.F);
    return Matrix34(v1, v2, v3);
/*
    return Matrix34(Vector4(t * v[0] * v[0] + c, t * v[0] * v[1] - s * v[2], t * v[0] * v[2] + s * v[1], 0.F),
                    Vector4(t * v[0] * v[1] + s * v[2], t * v[1] * v[1] + c, t * v[1] * v[2] - s * v[0], 0.F),
                    Vector4(t * v[0] * v[2] - s * v[1], t * v[1] * v[2] + s * v[0], t * v[2] * v[2] + c, 0.F));
                    */
}

HASH_INLINE Matrix34 Rotate2V_inline(const Vector from, const Vector to) noexcept {
    const float numerator = from | to;
    const float denominator = from.Norm() * to.Norm();

    if (hash_math::abs(numerator - denominator) < 1e-6F) //.00001f SAME DIR
        return Identity34();
    float radangle;
    Vector axis;
    if (hash_math::abs(numerator + denominator) < 1e-6F) {
        // OPPOSITE DIR
        radangle = hash_constants::pi;
        if (from.Normalized().Absolute() != Vector(1.F, 0.F, 0.F))
            axis = from ^ Vector(1.F, 0.F, 0.F);
        else
            axis = from ^ Vector(0.F, 1.F, 0.F);
    } else {
        const float ratio = numerator / denominator;
        if (ratio >= 1.F)
            return Identity34();
        radangle = hash_math::acos(ratio);
        axis = from ^ to;
    }
    return RotateVRadians_inline(radangle, axis);
}

HASH_INLINE Matrix34 VectorsToStandard(const Vector zdir, const Vector ydir) noexcept {
    Matrix34 vectostandard = Rotate2V_inline(zdir, Vector(0.F, 0.F, 1.F));
    const Vector rollvec = vectostandard * ydir;

    if (const float roll = hash_math::atan2(-rollvec.x, rollvec.y); roll != 0.F)
        vectostandard = ZRotateRadians(-roll) * vectostandard;
    return vectostandard; //may be faster to just compute like below, but the transpose
}

HASH_INLINE Quaternion::Quaternion(const Matrix34 &pm) noexcept {
    Vector xa = pm.GetXAxis();
    xa.Normalize();
    Vector ya = pm.GetYAxis();
    ya.Normalize();
    Vector za = pm.GetZAxis();
    za.Normalize();
    Matrix33 m(Vector(xa.x, ya.x, za.x), Vector(xa.y, ya.y, za.y), Vector(xa.z, ya.z, za.z));

    if (const float tr = m[0][0] + m[1][1] + m[2][2]; tr >= 0) {
        float s = hash_math::sqrt(tr + 1.F);
        w = 0.5F * s;
        s = 0.5F / s;
        x = (m[2][1] - m[1][2]) * s;
        y = (m[0][2] - m[2][0]) * s;
        z = (m[1][0] - m[0][1]) * s;
    } else {
        int i = 0;
        if (m[1][1] > m[0][0])
            i = 1;
        if (m[2][2] > m[i][i])
            i = 2;
        switch (i) {
            case 0:
                {
                    float s = hash_math::sqrt((m[0][0] - (m[1][1] + m[2][2])) + 1.F);
                    x = 0.5F * s;
                    s = 0.5F / s;
                    y = (m[0][1] + m[1][0]) * s;
                    z = (m[2][0] + m[0][2]) * s;
                    w = (m[2][1] - m[1][2]) * s;
                }
                break;
            case 1:
                {
                    float s = hash_math::sqrt((m[1][1] - (m[2][2] + m[0][0])) + 1.F);
                    y = 0.5F * s;
                    s = 0.5F / s;
                    z = (m[1][2] + m[2][1]) * s;
                    x = (m[0][1] + m[1][0]) * s;
                    w = (m[0][2] - m[2][0]) * s;
                }
                break;
            case 2:
                {
                    float s = hash_math::sqrt((m[2][2] - (m[0][0] + m[1][1])) + 1.F);
                    z = 0.5F * s;
                    s = 0.5F / s;
                    x = (m[2][0] + m[0][2]) * s;
                    y = (m[1][2] + m[2][1]) * s;
                    w = (m[1][0] - m[0][1]) * s;
                }
                break;
            default:
                break;
        }
    }
}
