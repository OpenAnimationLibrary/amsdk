//Dan  2/24/2004  \DanLP110\Include\Matrix44.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "Vector4.h"

class Quaternion;

//************************** MATRIX44 ********************************
//size 64
class MATRIXEXPORT Matrix44 final {
//protected:
    Vector4 v[4];

public:
    constexpr Matrix44() noexcept = default;
    constexpr explicit Matrix44(const float fill) noexcept {
        v[0].Set(fill);
        v[1].Set(fill);
        v[2].Set(fill);
        v[3].Set(fill);
    }
    constexpr Matrix44(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2, const Vector4 &v3) noexcept {
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
    }
    explicit HASH_INLINE Matrix44(const Quaternion &q) noexcept;

    Matrix44(const Matrix44 &other) = default;
    Matrix44 &operator=(const Matrix44 &other) = default; 
    Matrix44(Matrix44 &&other) = default; 
    Matrix44 &operator=(Matrix44 &&other) = default; 
    ~Matrix44 () = default; 

    const Vector4 &operator [](const int row) const noexcept {
        ASSERT(row < 4);
        return v[row];
    }

    constexpr Vector4 &operator [](const int row) noexcept {
        ASSERT(row < 4);
        return v[row];
    }

    constexpr void SetIdentity() noexcept {
        v[0].Set(1.F, 0.F, 0.F, 0.F);
        v[1].Set(0.F, 1.F, 0.F, 0.F);
        v[2].Set(0.F, 0.F, 1.F, 0.F);
        v[3].Set(0.F, 0.F, 0.F, 1.F);
    }

    [[nodiscard]] constexpr Matrix44 Transpose() const noexcept;
    [[nodiscard]] constexpr Matrix44 Inverse() const noexcept;

    bool Solve(Vector4 &x, const Vector4 &b) const noexcept; //Solve (*this)x=b, Gaussian elimination method


    constexpr Matrix44 operator *(const Matrix44 &b) const noexcept;
    constexpr Matrix44 &operator *=(const Matrix44 &other) noexcept {
        *this = *this * other;
        return *this;
    }

    constexpr Vector operator *(Vector vec) const noexcept;
    constexpr Vector4 operator *(Vector4 vec) const noexcept;

    bool operator==(const Matrix44 &other) const = default;
    bool operator!=(const Matrix44 &other) const = default;

    friend void swap(Matrix44 &a, Matrix44 &b) noexcept {
        const Matrix44 tmp(a);
        a = b;
        b = tmp;
    }

    constexpr friend MATRIXEXPORT Matrix44 Identity44() noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Matrix44 &val) {
        os << val[0] << " " << val[1] << " " << val[2] << " " << val[3];
        return os;
    }
};

constexpr MATRIXEXPORT Matrix44 Identity44() noexcept;

constexpr Matrix44 Matrix44::operator *(const Matrix44 &b) const noexcept {
    Matrix44 result;//(0);
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int k = 0; k < 4; ++k) {
                result[r][c] = result.v[r][c] + v[r][k] * b.v[k][c];
            }
        }
    }
    return result;
}

constexpr Matrix44 Matrix44::Inverse() const noexcept {
// Gauss-Jordan elimination with partial pivoting (See GEMS IV)
    Matrix44 a(*this);
    Matrix44 b(Identity44());

    for (int j = 0; j < 4; ++j) {
        int i1 = j;
        for (int i = j + 1; i < 4; ++i) {
            if (hash_math::abs(a.v[i][j]) > hash_math::abs(a.v[i1][j]))
                i1 = i;
        }
        swap(a.v[i1], a.v[j]);
        swap(b.v[i1], b.v[j]);

        if (a.v[j][j] == 0.F)
            return b; // ERROR SINGULAR

        if (a.v[j][j] != 1.F) {
            //saves 8 divisions 
            b.v[j] /= a.v[j][j];
            a.v[j] /= a.v[j][j];
        }

        for (int i = 0; i < 4; ++i) {
            if (i != j) {
                b.v[i] -= a.v[i][j] * b.v[j];
                a.v[i] -= a.v[i][j] * a.v[j];
            }
        }
    }
    return b;
}

constexpr Matrix44 Matrix44::Transpose() const noexcept {
    return Matrix44(Vector4(v[0][0], v[1][0], v[2][0], v[3][0]), Vector4(v[0][1], v[1][1], v[2][1], v[3][1]), Vector4(v[0][2], v[1][2], v[2][2], v[3][2]), Vector4(v[0][3], v[1][3], v[2][3], v[3][3]));
}

constexpr Vector Matrix44::operator *(const Vector vec) const noexcept {
    const Vector4 vec4(vec.x, vec.y, vec.z, 1.F);
    return Vector(v[0].Dot(vec4), v[1].Dot(vec4), v[2].Dot(vec4));
}

constexpr Vector4 Matrix44::operator *(const Vector4 vec) const noexcept {
    return Vector4(v[0].Dot(vec), v[1].Dot(vec), v[2].Dot(vec), v[3].Dot(vec));
}

constexpr MATRIXEXPORT Matrix44 Identity44() noexcept {
    return Matrix44(Vector4(1.F, 0.F, 0.F, 0.F), Vector4(0.F, 1.F, 0.F, 0.F), Vector4(0.F, 0.F, 1.F, 0.F), Vector4(0.F, 0.F, 0.F, 1.F));
}
