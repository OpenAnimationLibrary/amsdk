//BC  10/14/2004  \BobL115\Include\Matrix33.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "StdAfx.h"
#include "Vector2.h"
#include "Exports.h"

class Quaternion;
class Matrix44;

//size 36
class MATRIXEXPORT Matrix33 final {
    //protected:
    Vector v[3];

public:
    constexpr Matrix33() noexcept = default;
    explicit HASH_INLINE Matrix33(const Quaternion &q) noexcept;

    constexpr explicit Matrix33(const float fill) noexcept {
        Set(fill);
    }

    constexpr Matrix33(const Vector v0, const Vector v1, const Vector v2) noexcept {
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
    }

    Matrix33(const Matrix33 &other) = default;
    Matrix33 &operator=(const Matrix33 &other) = default;
    Matrix33(Matrix33 &&other) = default;
    Matrix33 &operator=(Matrix33 &&other) = default;
    ~Matrix33() = default;

    bool operator==(const Matrix33 &other) const = default;
    bool operator!=(const Matrix33 &other) const = default;

    constexpr Matrix33 operator *(const Matrix33 &b) const noexcept {
        Matrix33 result; //implicit (0);
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                for (int k = 0; k < 3; ++k) {
                    result[r][c] = result.v[r][c] + v[r][k] * b.v[k][c];
                }
            }
        }
        return result;
    }

    constexpr Matrix33 &operator *=(const Matrix33 &other) noexcept {
        return (*this = *this * other);
    }

    const Vector &operator [](const int row) const noexcept {
        ASSERT(row < 3);
        return v[row];
    }

    constexpr Vector &operator [](const int row) noexcept {
        ASSERT(row < 3);
        return v[row];
    }

    [[nodiscard]] constexpr Matrix33 Inverse() const noexcept;

    [[nodiscard]] constexpr Vector GetXAxis() const noexcept {
        return Vector(v[0][0], v[1][0], v[2][0]);
    }

    [[nodiscard]] constexpr Vector GetYAxis() const noexcept {
        return Vector(v[0][1], v[1][1], v[2][1]);
    }

    [[nodiscard]] constexpr Vector GetZAxis() const noexcept {
        return Vector(v[0][2], v[1][2], v[2][2]);
    }

    constexpr void SetIdentity() noexcept;
    [[nodiscard]] constexpr Matrix33 Transpose() const noexcept;
    constexpr void TransposeSelf() noexcept;
    constexpr Vector operator *(const Vector &vec) const noexcept;
    HASH_INLINE bool Solve(Vector &x, Vector b) const noexcept; //Solve (*this)x=b, Gaussian elimination method

    //    friend MATRIXEXPORT Vector2 operator *(const Matrix33 &m, const Vector2 &v);
    constexpr void Set(const float fill) noexcept {
        v[0].Set(fill);
        v[1].Set(fill);
        v[2].Set(fill);
    }

    constexpr void SetTranslate(const Vector2 &t) noexcept {
        v[0][3] = t.x;
        v[1][3] = t.y;
        v[2][3] = 1.F;
    }

    void MakeOrthogonal() noexcept {
        Matrix33 a = Transpose(); //move the column vectors to the rows
        Matrix33 b;

        b[0] = a[0];
        b[0].Normalize();
        b[1] = a[2] ^ a[0];
        b[1].Normalize();
        b[2] = b[0] ^ b[1];

        b[0] = a[0];
        b[1] *= a[1].Norm();
        b[2] *= a[2].Norm();

        *this = b.Transpose();
    }

    constexpr friend MATRIXEXPORT Matrix33 Identity33() noexcept;
    friend MATRIXEXPORT Matrix33 RotateVRadians33(float anglerad, Vector axis) noexcept;
    friend MATRIXEXPORT Matrix33 XYRotateRadians33(float xangle, float yangle) noexcept;
    friend MATRIXEXPORT Matrix33 YXRotateRadians33(float yangle, float xangle) noexcept;
    friend MATRIXEXPORT Matrix33 ZXRotateRadians33(float zangle, float xangle) noexcept;
    friend MATRIXEXPORT Matrix33 YXZRotateRadians33(float yangle, float xangle, float zangle) noexcept;
    friend MATRIXEXPORT Matrix33 ZXZRotateRadians33(float zangle1, float xangle, float zangle2) noexcept;
    friend MATRIXEXPORT Matrix33 Rotate2V33(Vector from, Vector to) noexcept;

    friend Matrix33 XRotate33(float angle) noexcept;
    friend Matrix33 YRotate33(float angle) noexcept;
    friend Matrix33 ZRotate33(float angle) noexcept;
    friend Matrix33 YXRotate33(float yangle, float xangle) noexcept;
    friend Matrix33 ZXRotate33(float zangle, float xangle) noexcept;
    friend Matrix33 YXZRotate33(float yangle, float xangle, float zangle) noexcept;
    friend Matrix33 ZXZRotate33(float zangl1, float xangle, float zangl2) noexcept;
    friend Matrix33 RotateV33(float angle, Vector axis) noexcept;
    friend HASH_INLINE Matrix33 XRotateRadians33(float anglerad) noexcept;
    friend HASH_INLINE Matrix33 YRotateRadians33(float anglerad) noexcept;
    friend HASH_INLINE Matrix33 ZRotateRadians33(float anglerad) noexcept;
    friend Matrix33 VectorsToStandard33(Vector zdir, Vector ydir) noexcept;

    friend void swap(Matrix33 &a, Matrix33 &b) noexcept {
        const Matrix33 tmp(a);
        a = b;
        b = tmp;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix33 &val) {
        os << val[0] << " " << val[1] << " " << val[2];
        return os;
    }
};

constexpr MATRIXEXPORT Matrix33 Identity33() noexcept;
MATRIXEXPORT Matrix33 RotateVRadians33(float anglerad, Vector axis) noexcept;
MATRIXEXPORT Matrix33 XYRotateRadians33(float xangle, float yangle) noexcept;
MATRIXEXPORT Matrix33 YXRotateRadians33(float yangle, float xangle) noexcept;
MATRIXEXPORT Matrix33 ZXRotateRadians33(float zangle, float xangle) noexcept;
MATRIXEXPORT Matrix33 YXZRotateRadians33(float yangle, float xangle, float zangle) noexcept;
MATRIXEXPORT Matrix33 ZXZRotateRadians33(float zangle1, float xangle, float zangle2) noexcept;
MATRIXEXPORT Matrix33 Rotate2V33(Vector from, Vector to) noexcept;

Matrix33 XRotate33(float angle) noexcept;
Matrix33 YRotate33(float angle) noexcept;
Matrix33 ZRotate33(float angle) noexcept;
Matrix33 YXRotate33(float yangle, float xangle) noexcept;
Matrix33 ZXRotate33(float zangle, float xangle) noexcept;
Matrix33 YXZRotate33(float yangle, float xangle, float zangle) noexcept;
Matrix33 ZXZRotate33(float zangl1, float xangle, float zangl2) noexcept;
Matrix33 RotateV33(float angle, Vector axis) noexcept;
HASH_INLINE Matrix33 XRotateRadians33(float anglerad) noexcept;
HASH_INLINE Matrix33 YRotateRadians33(float anglerad) noexcept;
HASH_INLINE Matrix33 ZRotateRadians33(float anglerad) noexcept;
Matrix33 VectorsToStandard33(Vector zdir, Vector ydir) noexcept;

HASH_INLINE Matrix33 XRotate33(const float angle) noexcept {
    return XRotateRadians33(angle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 YRotate33(const float angle) noexcept {
    return YRotateRadians33(angle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 ZRotate33(const float angle) noexcept {
    return ZRotateRadians33(angle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 YXRotate33(const float yangle, const float xangle) noexcept {
    return YXRotateRadians33(yangle * hash_constants::inverse_radians, xangle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 ZXRotate33(const float zangle, const float xangle) noexcept {
    return ZXRotateRadians33(zangle * hash_constants::inverse_radians, xangle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 YXZRotate33(const float yangle, const float xangle, const float zangle) noexcept {
    return YXZRotateRadians33(yangle * hash_constants::inverse_radians, xangle * hash_constants::inverse_radians, zangle * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 ZXZRotate33(const float zangl1, const float xangle, const float zangl2) noexcept {
    return ZXZRotateRadians33(zangl1 * hash_constants::inverse_radians, xangle * hash_constants::inverse_radians, zangl2 * hash_constants::inverse_radians);
}

HASH_INLINE Matrix33 RotateV33(const float angle, const Vector axis) noexcept {
    return RotateVRadians33(angle * hash_constants::inverse_radians, axis);
}

HASH_INLINE Matrix33 XRotateRadians33(const float anglerad) noexcept {
    const float ca = hash_math::cos(anglerad);
    const float sa = hash_math::sin(anglerad);
    constexpr Vector v1 = Vector(1.F, 0.F, 0.F);
    const Vector v2 = Vector(0.F, ca, -sa);
    const Vector v3 = Vector(0.F, sa, ca);
    return Matrix33(v1, v2, v3);
}

HASH_INLINE Matrix33 YRotateRadians33(const float anglerad) noexcept {
    const float ca = hash_math::cos(anglerad);
    const float sa = hash_math::sin(anglerad);
    const Vector v1 = Vector(ca, 0.F, sa);
    constexpr Vector v2 = Vector(0.F, 1.F, 0.F);
    const Vector v3 = Vector(-sa, 0.F, ca);
    return Matrix33(v1, v2, v3);
}

HASH_INLINE Matrix33 ZRotateRadians33(const float anglerad) noexcept {
    const float ca = hash_math::cos(anglerad);
    const float sa = hash_math::sin(anglerad);
    const Vector v1 = Vector(ca, -sa, 0.F);
    const Vector v2 = Vector(sa, ca, 0.F);
    constexpr Vector v3 = Vector(0.F, 0.F, 1.F);
    return Matrix33(v1, v2, v3);
}

HASH_INLINE Matrix33 VectorsToStandard33(const Vector zdir, const Vector ydir) noexcept {
    Matrix33 vectostandard = Rotate2V33(zdir, Vector(0.F, 0.F, 1.F));
    const Vector rollvec = vectostandard * ydir;
    if (const float roll = hash_math::atan2(-rollvec.x, rollvec.y); roll != 0.F)
        vectostandard = ZRotateRadians33(-roll) * vectostandard;
    return vectostandard;
}

HASH_INLINE Vector &Vector::operator *=(const Matrix33 &m) noexcept {
    *this = m * (*this); //same as above
    return *this;
}

constexpr void Matrix33::SetIdentity() noexcept {
    v[0].Set(1.F, 0.F, 0.F);
    v[1].Set(0.F, 1.F, 0.F);
    v[2].Set(0.F, 0.F, 1.F);
}

constexpr Matrix33 Matrix33::Transpose() const noexcept {
    return {Vector(v[0][0], v[1][0], v[2][0]), Vector(v[0][1], v[1][1], v[2][1]), Vector(v[0][2], v[1][2], v[2][2])};
}

constexpr void Matrix33::TransposeSelf() noexcept {
    *this = Transpose();
}

constexpr Vector Matrix33::operator *(const Vector &vec) const noexcept {
    return Vector(v[0].Dot(vec), v[1].Dot(vec), v[2].Dot(vec));
}

constexpr MATRIXEXPORT Matrix33 Identity33() noexcept {
    return Matrix33(Vector(1.F, 0.F, 0.F), Vector(0.F, 1.F, 0.F), Vector(0.F, 0.F, 1.F));
}

constexpr Matrix33 Matrix33::Inverse() const noexcept {
    // Gauss-Jordan elimination with partial pivoting (See GEMS IV)
    // ReSharper disable once CppLocalVariableMayBeConst
    Matrix33 a(*this);
    // ReSharper disable once CppLocalVariableMayBeConst
    Matrix33 b(Identity33());

    for (int j = 0; j < 3; ++j) {
        int i1 = j;
        for (int i = j + 1; i < 3; ++i) {
            if (hash_math::abs(a.v[i][j]) > hash_math::abs(a.v[i1][j]))
                i1 = i;
        }
        swap(a.v[i1], a.v[j]);
        swap(b.v[i1], b.v[j]);

        if (a.v[j][j] == 0.F)
            return b; // ERROR SINGULAR

        b.v[j] /= a.v[j][j];
        a.v[j] /= a.v[j][j];

        for (int i = 0; i < 3; ++i) {
            if (i != j) {
                b.v[i] -= a.v[i][j] * b.v[j];
                a.v[i] -= a.v[i][j] * a.v[j];
            }
        }
    }
    return b;
}

#include "Quaterni.h"

HASH_INLINE Quaternion::Quaternion(const Matrix33 &pm) noexcept {
    Vector xa = pm.GetXAxis();
    xa.Normalize();
    Vector ya = pm.GetYAxis();
    ya.Normalize();
    Vector za = pm.GetZAxis();
    za.Normalize();
    Matrix33 m(Vector(xa.x, ya.x, za.x), Vector(xa.y, ya.y, za.y), Vector(xa.z, ya.z, za.z));

    if (const float tr = m[0][0] + m[1][1] + m[2][2]; tr >= 0.F) {
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

HASH_INLINE Matrix33::Matrix33(const Quaternion &q) noexcept {
    const float nq = q.Norm();
    const float s = (nq > 0.F) ? (2.F / nq) : 0.F;
    const float qx = q.GetX();
    const float qy = q.GetY();
    const float xs = qx * s, ys = qy * s, zs = q.GetZ() * s;
    const float qw = -q.GetW();
    const float wx = qw * xs, wy = qw * ys, wz = qw * zs;
    const float xx = qx * xs, xy = qx * ys, xz = qx * zs;
    const float zz = q.GetZ() * zs, yy = qy * ys, yz = qy * zs;

    v[0].Set(1.F - (yy + zz), xy + wz, xz - wy);
    v[1].Set(xy - wz, 1.F - (xx + zz), yz + wx);
    v[2].Set(xz + wy, yz - wx, 1.F - (xx + yy));
}
