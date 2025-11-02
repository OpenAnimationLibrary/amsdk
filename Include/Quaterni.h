//Dan  2/24/2004  \DanLP110\Include\Quaterni.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "Vector.h"
#include "Exports.h"

class RotateVector;
class RotateSphere;
class RotateEuler;
class Bone;

//size 16
//class __declspec(dllexport, align(16)) Quaternion final {
class MATRIXEXPORT Quaternion final {
//protected:
    float x{0.F};
    float y{0.F};
    float z{0.F};
    float w{1.F};

public:
    constexpr Quaternion() noexcept = default;
    HASH_INLINE explicit Quaternion(const Matrix33 &) noexcept;
    HASH_INLINE explicit Quaternion(const Matrix34 &) noexcept;

    constexpr explicit Quaternion(const float scale) noexcept : w(scale) {}
    constexpr Quaternion(const Vector vec, const float scale) noexcept : x(vec.x), y(vec.y), z(vec.z), w(scale) {}
    constexpr Quaternion(const float x1, const float y1, const float z1, const float w1) noexcept : x(x1), y(y1), z(z1), w(w1) {}

    constexpr Quaternion(const float radangle, const Vector axis) noexcept {
        radangle != 0.F ? SetAngleAxis(radangle, axis) : SetIdentity();
    }

    explicit HASH_INLINE Quaternion(RotateVector rv) noexcept; //SOB STYLE ROLL
    explicit HASH_INLINE Quaternion(RotateSphere rs) noexcept;
    constexpr explicit Quaternion(RotateEuler re) noexcept;
    constexpr Quaternion(RotateEuler re, bool isyxz) noexcept;

    //STORAGE & RETRIEVAL
    [[nodiscard]] constexpr float GetX() const noexcept {
        return x;
    }

    [[nodiscard]] constexpr float GetY() const noexcept {
        return y;
    }

    [[nodiscard]] constexpr float GetZ() const noexcept {
        return z;
    }

    [[nodiscard]] constexpr float GetW() const noexcept {
        return w;
    }

    [[nodiscard]] constexpr Vector GetVector() const noexcept {
        return Vector(x, y, z);
    }

    constexpr void SetV(const Vector vec) noexcept {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    constexpr void SetV(const int index, const float value) noexcept {
        ASSERT(index < 3);
        (&x)[index] = value;
    }

    constexpr void SetW(const float scale) noexcept {
        w = scale;
    }

    constexpr void Set(const float px, const float py, const float pz, const float pw) noexcept {
        x = px;
        y = py;
        z = pz;
        w = pw;
    }

    constexpr void Set(const Vector pv, const float pw) noexcept {
        x = pv.x;
        y = pv.y;
        z = pv.z;
        w = pw;
    }

    constexpr void Set(const float fillvalue) noexcept {
        x = y = z = w = fillvalue;
    }

    constexpr void SetIdentity() noexcept {
        Set(0.F, 0.F, 0.F, 1.F);
    }

    [[nodiscard]] constexpr Vector GetXAxis() const noexcept {
        //        return *this * Vector(1.F, 0.F, 0.F);
        const Quaternion quat1(w, z, -y, -x);
        return Vector((quat1.y * -z - quat1.z * -y) + quat1.w * -x + quat1.x * w, (quat1.z * -x - quat1.x * -z) + quat1.w * -y + quat1.y * w,
                      (quat1.x * -y - quat1.y * -x) + quat1.w * -z + quat1.z * w);
    }

    [[nodiscard]] constexpr Vector GetYAxis() const noexcept {
        //        return *this * Vector(0.F, 1.F, 0.F);
        const Quaternion quat1(-z, w, x, -y);
        return Vector((quat1.y * -z - quat1.z * -y) + quat1.w * -x + quat1.x * w, (quat1.z * -x - quat1.x * -z) + quat1.w * -y + quat1.y * w,
                      (quat1.x * -y - quat1.y * -x) + quat1.w * -z + quat1.z * w);
    }

    [[nodiscard]] constexpr Vector GetZAxis() const noexcept {
        //        return *this * Vector(0.F, 0.F, 1.F);
        const Quaternion quat1(y, -x, w, -z);
        return Vector((quat1.y * -z - quat1.z * -y) + quat1.w * -x + quat1.x * w, (quat1.z * -x - quat1.x * -z) + quat1.w * -y + quat1.y * w,
                      (quat1.x * -y - quat1.y * -x) + quat1.w * -z + quat1.z * w);
    }

    constexpr float const &operator [](const int index) const noexcept {
        ASSERT(index < 4);
        return (&x)[index];
    }

    constexpr float &operator [](const int index) noexcept {
        ASSERT(index < 4);
        return (&x)[index];
    }

    [[nodiscard]] float GetAngle() const noexcept {
        if (const float fw = hash_math::abs(w); fw < 1.F)
            return hash_math::acos(fw) * 2.F;
        return 0.F;
    }

    [[nodiscard]] Vector GetAxis() const noexcept {
        const Vector v(x, y, z);
        if (hash_math::abs(w) >= 1.F)
            return v;
        if (w > 0.F)
            return v / hash_math::sin(hash_math::acos(w));
        return v / -hash_math::sin(hash_math::acos(w));
    }

    constexpr void SetAngleAxis(const float radangle, const Vector axis) noexcept {
        if (radangle == 0.F) {
            x = y = z = 0.F;
            w = 1.F;
        } else {
            const float half_angle = radangle * 0.5F;
            if (axis == Vector(0.F, 0.F, 1.F)) {
                x = 0.F;
                y = 0.F;
                z = hash_math::sin(half_angle);
            } else {
                const float angle_sin = hash_math::sin(half_angle);
                if (const float square = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z; square != 0.F) {
                    const float divisor = hash_math::rcp(hash_math::sqrt(square));
                    x = axis.x * divisor * angle_sin;
                    y = axis.y * divisor * angle_sin;
                    z = axis.z * divisor * angle_sin;
                } else {
                    x = axis.x * angle_sin;
                    y = axis.y * angle_sin;
                    z = axis.z * angle_sin;
                }
            }
            w = hash_math::cos(half_angle);
        }
    }

    //UNARY OPERATIONS
    [[nodiscard]] float Norm() const noexcept {
        if (IsIdentity())
            return 1.F;
        return hash_math::sqrt(x * x + y * y + z * z + w * w);
    }

    [[nodiscard]] float InvNorm() const noexcept {
        return hash_math::rcp(hash_math::sqrt(x * x + y * y + z * z + w * w));
    }

    [[nodiscard]] Quaternion FixQuaternion() const noexcept {
        if (w == 1.F && hash_math::abs(x) < 1e-3F && hash_math::abs(y) < 1e-3F && hash_math::abs(z) < 1e-3F) {
            return Quaternion();
        }
        return *this;
    }

    Quaternion &Normalize() noexcept {
        const float length = Norm();
        if (length < 1e-10F) {
            *this = Quaternion();
        } else {
            if (length != 1.F) {
                *this /= length;
                *this = FixQuaternion();
            }
        }
        return *this;
    }

    [[nodiscard]] Quaternion Normalized() const noexcept {
        const float length = Norm();
        if (length < 1e-10F)
            return Quaternion();
        if (length == 1.F)
            return  *this;
        const Quaternion r_quat = *this / length;
        return r_quat.FixQuaternion();
    }

    [[nodiscard]] Quaternion Inverse() const noexcept {
        Vector temp(x, y, z);
        temp.Negate();
        return Quaternion(temp, w);
    }

    constexpr Quaternion &Negate() noexcept {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
        return *this;
    }

    [[nodiscard]] bool IsIdentity() const noexcept {
        return *this == Quaternion();
    }

    //OPERATORS
    friend bool operator==(const Quaternion &li, const Quaternion &re) noexcept {
        return floatEQ(li.x, re.x) && floatEQ(li.y, re.y) && floatEQ(li.z, re.z) && floatEQ(li.w, re.w);
    }

    friend bool operator!=(const Quaternion &li, const Quaternion &re) noexcept {
        return !operator==(li, re);
    }

    friend bool operator <(const Quaternion &li, const Quaternion &re) noexcept {
        return li.Norm() < re.Norm();
    }

    constexpr Quaternion &operator *=(const Quaternion other) noexcept {
        *this = *this * other;
        return *this;
    }

    constexpr Quaternion &operator *=(const float scale) noexcept {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
        return *this;
    }

    Quaternion &operator /=(const float scale) noexcept {
        ASSERT(scale != 0.F);
        x /= scale;
        y /= scale;
        z /= scale;
        w /= scale;
        return *this;
    }

    constexpr Quaternion &operator +=(const Quaternion &q2) noexcept {
        x += q2.x;
        y += q2.y;
        z += q2.z;
        w += q2.w;
        return *this;
    }

    constexpr Quaternion &operator -=(const Quaternion &q2) noexcept {
        x -= q2.x;
        y -= q2.y;
        z -= q2.z;
        w -= q2.w;
        return *this;
    }

    constexpr Quaternion operator -() const noexcept {
        return Quaternion(*this).Negate();
    }

    constexpr Quaternion operator *(Quaternion b) const noexcept;

    constexpr Quaternion operator *(const float scale) const noexcept {
        return {x * scale, y * scale, z * scale, w * scale};
    }

    constexpr friend Quaternion operator *(const float scale, const Quaternion q) noexcept {
        return {q.x * scale, q.y * scale, q.z * scale, q.w * scale};
    }

    constexpr Quaternion operator /(const float scale) const noexcept {
        ASSERT(scale != 0.F);
        return {x / scale, y / scale, z / scale, w / scale};
    }

    constexpr Quaternion operator +(const Quaternion b) const noexcept {
        return {x + b.x, y + b.y, z + b.z, w + b.w};
    }

    constexpr Quaternion operator -(const Quaternion b) const noexcept {
        return {x - b.x, y - b.y, z - b.z, w - b.w};
    }

    friend void swap(Quaternion &lhs, Quaternion &rhs) noexcept {
        const Quaternion temp(lhs);
        lhs = rhs;
        rhs = temp;
    }

    friend Vector operator *(const Vector s_v, const Quaternion b) noexcept {
        return {b * s_v};
    }

    Vector operator *(const Vector sv) const noexcept {
        //no constexpr
        //variable in constexpr function does not have automatic storage duration
        if (static Quaternion quatzero(0.F); *this == quatzero)
            return Vector();
        const Quaternion quat1((y * sv.z - z * sv.y) + w * sv.x, (z * sv.x - x * sv.z) + w * sv.y, (x * sv.y - y * sv.x) + w * sv.z, -(x * sv.x + y * sv.y + z * sv.z));
        return Vector((quat1.y * -z - quat1.z * -y) + quat1.w * -x + quat1.x * w, (quat1.z * -x - quat1.x * -z) + quat1.w * -y + quat1.y * w,
                      (quat1.x * -y - quat1.y * -x) + quat1.w * -z + quat1.z * w);
    }

#ifdef _DEBUG
    [[nodiscard]] bool IsValid() const {
        if (!IsFinite(x))
            return false;
        if (!IsFinite(y))
            return false;
        if (!IsFinite(z))
            return false;
        if (!IsFinite(w))
            return false;
        return true;
    }
#endif

    //    friend void TransformVector(const Quaternion &q, Vector &v);
    constexpr friend float Dot(Quaternion a, Quaternion b) noexcept;
    constexpr friend Quaternion RotateVQ(float angle, Vector axis) noexcept;
    constexpr friend Quaternion XRotateRadiansQ(float anglerad) noexcept;
    constexpr friend Quaternion YRotateRadiansQ(float anglerad) noexcept;
    constexpr friend Quaternion ZRotateRadiansQ(float anglerad) noexcept;
    constexpr friend Quaternion XRotateQ(float angle) noexcept;
    constexpr friend Quaternion YRotateQ(float angle) noexcept;
    constexpr friend Quaternion ZRotateQ(float angle) noexcept;
    constexpr friend Quaternion YXZRotateRadiansQ(float y, float x, float z) noexcept;
    constexpr friend Quaternion YXRotateRadiansQ(float y, float x) noexcept;
    constexpr friend Quaternion YXZRotateQ(float y, float x, float z) noexcept;
    constexpr friend Quaternion YXRotateQ(float y, float x) noexcept;
    constexpr friend Quaternion XYZRotateQ(float x, float y, float z) noexcept;
    constexpr friend Quaternion XYRotateQ(float x, float y) noexcept;
    friend Quaternion VectorsToStandardQ(Vector zdir, Vector ydir) noexcept;
    friend MATRIXEXPORT Quaternion RotateVRadiansQ(float theta, Vector vhat) noexcept;
    friend MATRIXEXPORT Quaternion Rotate2VQ(Vector from, Vector to) noexcept;
    friend MATRIXEXPORT Quaternion Blend(Quaternion quat1, float percent1, Quaternion quat2, float percent2) noexcept;

    friend Quaternion RotateVRadiansQ_inline(float theta, Vector vhat) noexcept;
    friend Quaternion Rotate2VQ_inline(Vector from, Vector to) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &val) {
        os << val.x << " " << val.y << " " << val.z << " " << val.w;
        return os;
    }
    };

constexpr float Dot(Quaternion a, Quaternion b) noexcept;
constexpr Quaternion RotateVQ(float angle, Vector axis) noexcept;
constexpr Quaternion XRotateRadiansQ(float anglerad) noexcept;
constexpr Quaternion YRotateRadiansQ(float anglerad) noexcept;
constexpr Quaternion ZRotateRadiansQ(float anglerad) noexcept;
constexpr Quaternion XRotateQ(float angle) noexcept;
constexpr Quaternion YRotateQ(float angle) noexcept;
constexpr Quaternion ZRotateQ(float angle) noexcept;
constexpr Quaternion YXZRotateRadiansQ(float y, float x, float z) noexcept;
constexpr Quaternion YXRotateRadiansQ(float y, float x) noexcept;
constexpr Quaternion YXZRotateQ(float y, float x, float z) noexcept;
constexpr Quaternion YXRotateQ(float y, float x) noexcept;
constexpr Quaternion XYZRotateQ(float x, float y, float z) noexcept;
constexpr Quaternion XYRotateQ(float x, float y) noexcept;
Quaternion VectorsToStandardQ(Vector zdir, Vector ydir) noexcept;
MATRIXEXPORT Quaternion RotateVRadiansQ(float theta, Vector vhat) noexcept;
MATRIXEXPORT Quaternion Rotate2VQ(Vector from, Vector to) noexcept;
MATRIXEXPORT Quaternion Blend(Quaternion quat1, float percent1, Quaternion quat2, float percent2) noexcept;

HASH_INLINE Quaternion RotateVRadiansQ_inline(float theta, Vector vhat) noexcept;
HASH_INLINE Quaternion Rotate2VQ_inline(Vector from, Vector to) noexcept;

constexpr float Dot(const Quaternion a, const Quaternion b) noexcept {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

constexpr Quaternion RotateVQ(const float angle, const Vector axis) noexcept {
    return Quaternion(angle * hash_constants::inverse_radians, axis);
}

constexpr Quaternion XRotateRadiansQ(const float anglerad) noexcept {
    return Quaternion(anglerad, Vector(1.F, 0.F, 0.F));
}

constexpr Quaternion YRotateRadiansQ(const float anglerad) noexcept {
    return Quaternion(anglerad, Vector(0.F, 1.F, 0.F));
}

constexpr Quaternion ZRotateRadiansQ(const float anglerad) noexcept {
    return Quaternion(anglerad, Vector(0.F, 0.F, 1.F));
}

constexpr Quaternion XRotateQ(const float angle) noexcept {
    return XRotateRadiansQ(angle * hash_constants::inverse_radians);
}

constexpr Quaternion YRotateQ(const float angle) noexcept {
    return YRotateRadiansQ(angle * hash_constants::inverse_radians);
}

constexpr Quaternion ZRotateQ(const float angle) noexcept {
    return ZRotateRadiansQ(angle * hash_constants::inverse_radians);
}

constexpr Quaternion YXZRotateRadiansQ(const float y, const float x, const float z) noexcept {
    return YRotateRadiansQ(y) * XRotateRadiansQ(x) * ZRotateRadiansQ(z);
}

constexpr Quaternion YXRotateRadiansQ(const float y, const float x) noexcept {
    return YRotateRadiansQ(y) * XRotateRadiansQ(x);
}

constexpr Quaternion YXZRotateQ(const float y, const float x, const float z) noexcept {
    return YXZRotateRadiansQ(y * hash_constants::inverse_radians, x * hash_constants::inverse_radians, z * hash_constants::inverse_radians);
}

constexpr Quaternion YXRotateQ(const float y, const float x) noexcept {
    return YXRotateRadiansQ(y * hash_constants::inverse_radians, x * hash_constants::inverse_radians);
}

constexpr Quaternion XYZRotateQ(const float x, const float y, const float z) noexcept {
    return XRotateQ(x) * YRotateQ(y) * ZRotateQ(z);
}

constexpr Quaternion XYRotateQ(const float x, const float y) noexcept {
    return XRotateQ(x) * YRotateQ(y);
}

/*
    //original
    return { (v ^ b.v) + (w * b.v) + (v * b.w), w * b.w - (v | b.v) };

    //same as original , but without using vector functions
    return {(y * b.z - z * b.y) + w * b.x + x * b.w,
            (z * b.x - x * b.z) + w * b.y + y * b.w,
            (x * b.y - y * b.x) + w * b.z + z * b.w,
             w * b.w - (x * b.x + y * b.y + z * b.z)};

    //from Pixar USD , slightly different results
    float r1 = GetW();
    float r2 = b.GetW();
    const Vector &i1 = GetVector();
    const Vector &i2 = b.GetVector();
    float r = r1 * r2 - Dot(i1, i2);
    Vector i(r1 * i2[0] + r2 * i1[0] + (i1[1] * i2[2] - i1[2] * i2[1]), r1 * i2[1] + r2 * i1[1] + (i1[2] * i2[0] - i1[0] * i2[2]), r1 * i2[2] + r2 * i1[2] + (i1[0] * i2[1] - i1[1] * i2[0]));
    Quaternion quat1(i, r);

    //faster than originalm, needs check why not using
    const __m128 a = _mm_setr_ps(x, y, z, w);
    const __m128 ab = _mm_setr_ps(b.x, b.y, b.z, b.w);
    const __m128 wzyx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 1, 2, 3));
    const __m128 baba = _mm_shuffle_ps(ab, ab, _MM_SHUFFLE(0, 1, 0, 1));
    const __m128 dcdc = _mm_shuffle_ps(ab, ab, _MM_SHUFFLE(2, 3, 2, 3));
    const __m128 ZnXWY = _mm_hsub_ps(_mm_mul_ps(a, baba), _mm_mul_ps(wzyx, dcdc));
    const __m128 XZYnW = _mm_hadd_ps(_mm_mul_ps(a, dcdc), _mm_mul_ps(wzyx, baba));
    const __m128 XZWY = _mm_addsub_ps(_mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3, 2, 1, 0)), _mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2, 3, 0, 1)));
    __m128 res1 = _mm_shuffle_ps(XZWY, XZWY, _MM_SHUFFLE(2, 1, 3, 0));
    return {res1.m128_f32[0], res1.m128_f32[1], res1.m128_f32[2], res1.m128_f32[3]};
*/

constexpr Quaternion Quaternion::operator *(const Quaternion b) const noexcept {
    return Quaternion((y * b.z - z * b.y) + w * b.x + x * b.w, (z * b.x - x * b.z) + w * b.y + y * b.w, (x * b.y - y * b.x) + w * b.z + z * b.w, w * b.w - (x * b.x + y * b.y + z * b.z));
}

/*
original
    const Quaternion q2((q.v ^ (*this)) + (q.w * (*this)), -q.v | (*this)); //FASTER 24*, 17+
    *this = (q2.v * q.w) - (q2.w * q.v) - (q2.v ^ q.v);
    return *this;
*/

HASH_INLINE Vector &Vector::operator *=(const Quaternion &q) noexcept {
    //same as original , but without using vector functions
    const float q_x = q.GetX();
    const float q_y = q.GetY();
    const float q_z = q.GetZ();
    const float q_w = q.GetW();
    const float quat1_x = (q_y * z - q_z * y) + q_w * x;
    const float quat1_y = (q_z * x - q_x * z) + q_w * y;
    const float quat1_z = (q_x * y - q_y * x) + q_w * z;
    const float quat1_w = -(q_x * x + q_y * y + q_z * z);
    Set((quat1_y * -q_z - quat1_z * -q_y) + quat1_w * -q_x + quat1_x * q_w, (quat1_z * -q_x - quat1_x * -q_z) + quat1_w * -q_y + quat1_y * q_w,
        (quat1_x * -q_y - quat1_y * -q_x) + quat1_w * -q_z + quat1_z * q_w);
    return *this;
}

HASH_INLINE Vector Lerp(const Vector vec1, const Vector vec2, const float blendratio) noexcept {
    return ((1.F - blendratio) * vec1 + blendratio * vec2).Normalized();
}

HASH_INLINE Quaternion RotateVRadiansQ_inline(const float theta, const Vector vhat) noexcept {
    if (vhat.IsNotZero()) {
        Vector temp(vhat.x, vhat.y, vhat.z);
        temp.Normalize();
        temp *= hash_math::sin(theta * 0.5F);
        const Quaternion rvalue(temp, hash_math::cos(theta * 0.5F));
        return rvalue;
    }
    const Quaternion rvalue(vhat, hash_math::cos(theta * 0.5F));
    return rvalue;
}

HASH_INLINE Quaternion Rotate2VQ_inline(const Vector from, const Vector to) noexcept {
    const float numerator = from | to;
    const float denominator = from.Norm() * to.Norm();
    if (hash_math::abs(numerator - denominator) < 1e-6F) // SAME DIR
        return Quaternion(); //IdentityQ();
    float radangle;
    Vector axis;
    if (hash_math::abs(numerator + denominator) < 1e-6F) {
        // OPPOSITE DIR
        radangle = hash_constants::pi;
        if (from.FixedNormalized().Absolute() != Vector(1.F, 0.F, 0.F))
            axis = from ^ Vector(1.F, 0.F, 0.F);
        else
            axis = from ^ Vector(0.F, 1.F, 0.F);
    } else {
        const float ratio = numerator / denominator;
        if (ratio >= 1.F || ratio < -1.F) //otherwise infinite value for radangle
            return Quaternion(); //IdentityQ();
        radangle = hash_math::acos(ratio);
        axis = from ^ to;
    }
    return RotateVRadiansQ_inline(radangle, axis);
}

HASH_INLINE Quaternion VectorsToStandardQ(const Vector zdir, const Vector ydir) noexcept {
    Quaternion vectostandard = Rotate2VQ_inline(zdir, Vector(0.F, 0.F, 1.F));
    const Vector rollvec = vectostandard * ydir;
    if (const float roll = hash_math::atan2(-rollvec.x, rollvec.y); roll == 0.F)
        vectostandard = ZRotateRadiansQ(-roll) * vectostandard;
    return vectostandard;
}

constexpr Vector Slerp(const Vector vec1, const Vector vec2, const float blendratio) noexcept {
    if (blendratio == 0.F)
        return Quaternion() * vec1;
    Quaternion delta = Rotate2VQ_inline(vec1, vec2);
    delta.SetAngleAxis(delta.GetAngle() * blendratio, delta.GetAxis());
    Vector rcVector = delta * vec1;
    rcVector.FixedNormalize();
    return rcVector;
}
