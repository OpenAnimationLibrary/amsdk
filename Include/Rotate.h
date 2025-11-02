//RC  6/11/2002  \Randy95\Include\Rotate.h
// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppRedundantParentheses
#pragma once

#include "Vector.h"
#include "Quaterni.h"

class Rotate final {
public:
    float swivel{0.F}; //x
    float tilt{0.F}; //y
    float roll{0.F}; //z

    constexpr Rotate() noexcept = default;
    constexpr explicit Rotate(const Vector r) : swivel(r.x), tilt(r.y), roll(r.z) {}
    // ReSharper disable once CppNonExplicitConvertingConstructor
    constexpr Rotate(const float scale) : swivel(scale), tilt(scale), roll(scale) {}
    constexpr Rotate(const float pswivel, const float ptilt, const float proll) : swivel(pswivel), tilt(ptilt), roll(proll) {}

    [[nodiscard]] bool IsZero() const noexcept {
        return !IsNotZero();
    }

    [[nodiscard]] bool IsNotZero() const noexcept {
        if (swivel != 0.F)
            return true;
        if (tilt != 0.F)
            return true;
        if (roll != 0.F)
            return true;
        return false;
    }

    constexpr Rotate &Negate() noexcept {
        swivel = -swivel;
        tilt = -tilt;
        roll = -roll;
        return *this;
    }

    void CheckNearZero(const float min_value = 1e-6F) noexcept {
        if (hash_math::abs(swivel) < min_value)
            swivel = 0.F;
        if (hash_math::abs(tilt) < min_value)
            tilt = 0.F;
        if (hash_math::abs(roll) < min_value)
            roll = 0.F;
    }

    constexpr Rotate &operator *=(const float scale) noexcept {
        swivel *= scale;
        roll *= scale;
        tilt *= scale;
        return *this;
    }

    friend std::ostream &operator <<(std::ostream &os, const Rotate &val) {
        os << val.swivel << " " << val.tilt << " " << val.roll;
        return os;
    }
};

HASH_INLINE bool operator ==(const Rotate &lhs, const Rotate &rhs) noexcept {
    return floatEQ(lhs.swivel, rhs.swivel) && floatEQ(lhs.tilt, rhs.tilt) && floatEQ(lhs.roll, rhs.roll);
}

HASH_INLINE bool operator !=(const Rotate &lhs, const Rotate &rhs) noexcept {
    return !operator==(lhs, rhs);
}

class RotateSphere;
class RotateEuler;

class RotateVector final {
public:
    Vector end;
    float roll{0.F};

    constexpr RotateVector() noexcept = default;
    constexpr RotateVector(const Vector pend, const float proll) : end(pend), roll(proll) {}
    HASH_INLINE explicit RotateVector(RotateSphere sphere) noexcept;
    HASH_INLINE explicit RotateVector(RotateEuler euler) noexcept;
    HASH_INLINE explicit RotateVector(const Matrix34 &matrix) noexcept;
    HASH_INLINE explicit RotateVector(const Quaternion &quat) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const RotateVector &val) {
        os << val.end << " " << val.roll;
        return os;
    }
};

HASH_INLINE bool operator==(const RotateVector &lhs, const RotateVector &rhs) noexcept {
    return lhs.end == rhs.end && floatEQ(lhs.roll, rhs.roll);
}

HASH_INLINE bool operator!=(const RotateVector &lhs, const RotateVector &rhs) noexcept {
    return !operator==(lhs, rhs);
}

class RotateSphere final {
public:
    float latitude{0.F};
    float longitude{0.F};
    float roll{0.F};

    constexpr RotateSphere() noexcept = default;
    HASH_INLINE explicit RotateSphere(Vector vec) noexcept;
    HASH_INLINE explicit RotateSphere(RotateVector rotate) noexcept;
    HASH_INLINE explicit RotateSphere(const Quaternion &quat) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const RotateSphere &val) {
        os << val.latitude << " " << val.longitude << " " << val.roll;
        return os;
    }
};

class RotateEuler final {
public:
    float x{0.F};
    float y{0.F};
    float z{0.F};

    constexpr RotateEuler() noexcept = default;
    constexpr RotateEuler(const float px, const float py, const float pz) : x(px), y(py), z(pz) {}
    HASH_INLINE explicit RotateEuler(const Matrix34 &matrix) noexcept;
    HASH_INLINE explicit RotateEuler(RotateVector rotatev) noexcept;
    HASH_INLINE explicit RotateEuler(const Quaternion &quat) noexcept;

    constexpr RotateEuler operator *(const float scale) const noexcept {
        const RotateEuler other(x * scale, y * scale, z * scale);
        return other;
    }

    [[nodiscard]] bool IsZero() const noexcept {
        return !IsNotZero();
    }

    [[nodiscard]] bool IsNotZero() const noexcept {
        if (x != 0.F)
            return true;
        if (y != 0.F)
            return true;
        if (z != 0.F)
            return true;
        return false;
    }

    //    const float &operator [](const int index) const {
    constexpr float const &operator [](const int index) const noexcept {
        ASSERT(index < 3);
        return (&x)[index];
    }

    constexpr float &operator [](const int index) noexcept {
        ASSERT(index < 3);
        return (&x)[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const RotateEuler &val) {
        os << val.x << " " << val.y << " " << val.z;
        return os;
    }
};

class TSR final {
public:
    Vector translate;
    Vector scale;
    RotateVector rotate;

    constexpr void SetDefault() noexcept {
        translate.SetZero();
        scale.Set(1.F);
        rotate.end.Set(0.F, 0.F, 1.F);
        rotate.roll = 0.F;
    }

    [[nodiscard]] bool IsDefault() const noexcept {
        if (translate.IsZero() && scale == Vector(1.F) && rotate.roll == 0.F && rotate.end == Vector(0.F, 0.F, 1.F))
            return true;
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const TSR &val) {
        os << val.translate << " " << val.scale << " " << val.rotate;
        return os;
    }
};

HASH_INLINE bool operator==(const TSR &lhs, const TSR &rhs) noexcept {
    return lhs.rotate == rhs.rotate && lhs.translate == rhs.translate && lhs.scale == rhs.scale;
}

HASH_INLINE bool operator!=(const TSR &lhs, const TSR &rhs) noexcept {
    return !operator==(lhs, rhs);
}

class MATRIXEXPORT TSQ final {
public:
    Quaternion quat;
    Vector translate;
    Vector scale;
    float roll{0.F}; //used in flock plugins

    constexpr TSQ() noexcept = default;
    constexpr TSQ(const Vector ptranslate, const Vector pscale, const Quaternion &pquat) : quat(pquat), translate(ptranslate), scale(pscale) {}
    explicit TSQ(const Matrix34 &actionmatrix) noexcept;

    constexpr void SetDefault() noexcept {
        translate.SetZero();
        scale.Set(1.F);
        quat.SetIdentity();
    }

    [[nodiscard]] bool IsDefault() const noexcept {
        return (translate.IsZero() && scale == Vector(1.F) && quat.IsIdentity() && roll == 0.F);
    }

    constexpr TSQ &operator +=(const TSQ &other) noexcept {
        translate += other.translate;
        scale += other.scale;
        quat += other.quat;
        return *this;
    }

    constexpr TSQ &operator *=(const float lscale) noexcept {
        translate *= lscale;
        scale *= lscale;
        quat *= lscale;
        return *this;
    }

    void PostBlend() noexcept {
        quat.Normalize();
    }

    void FillMatrices(Matrix34 &matrix, Matrix34 &inverse) const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const TSQ &val) {
        os << val.quat << " " << val.translate << " " << val.scale << " " << val.roll;
        return os;
    }
};

HASH_INLINE bool operator==(const TSQ &lhs, const TSQ &rhs) noexcept {
    return lhs.quat == rhs.quat && lhs.translate == rhs.translate && lhs.scale == rhs.scale;
}

HASH_INLINE bool operator!=(const TSQ &lhs, const TSQ &rhs) noexcept {
    return !operator==(lhs, rhs);
}

//ANY ROTATION TYPE TO AND FROM QUATERNION

HASH_INLINE RotateEuler::RotateEuler(const Quaternion &quat) noexcept {
    const Vector end(quat.GetZAxis());
    y = hash_math::atan2(end.x, end.z) * hash_constants::radians;
    x = hash_math::atan2(-end.y, hash_math::sqrt(end.x * end.x + end.z * end.z)) * hash_constants::radians;
    Vector rolldir(quat.GetYAxis());
    rolldir *= YXRotateQ(y, x).Inverse();
    z = hash_math::atan2(-rolldir.x, rolldir.y) * hash_constants::radians;
}

HASH_INLINE RotateVector::RotateVector(const Quaternion &quat) noexcept {
    //SOB STYLE ROLL
    end = quat.GetZAxis();
    const float y1 = hash_math::atan2(end.x, end.z);
    const float x1 = hash_math::atan2(-end.y, hash_math::sqrt(end.x * end.x + end.z * end.z));
    Vector rolldir = quat.GetYAxis();
    rolldir *= YXRotateRadiansQ(y1, x1).Inverse();
    roll = hash_math::atan2(-rolldir.x, rolldir.y) * hash_constants::radians;
}

HASH_INLINE Quaternion::Quaternion(const RotateVector rv) noexcept {
    //SOB STYLE ROLL
    const float y1 = hash_math::atan2(rv.end.x, rv.end.z);
    if (const float x1 = hash_math::atan2(-rv.end.y, hash_math::sqrt(rv.end.x * rv.end.x + rv.end.z * rv.end.z)); rv.roll != 0.F) {
        *this = YXZRotateRadiansQ(y1, x1, rv.roll * hash_constants::inverse_radians);
    } else {
        *this = YXRotateRadiansQ(y1, x1);
    }
}

HASH_INLINE RotateSphere::RotateSphere(const Quaternion &quat) noexcept {
    *this = RotateSphere(RotateVector(quat));
}

HASH_INLINE Quaternion::Quaternion(const RotateSphere rs) noexcept {
    *this = Quaternion(RotateVector(rs));
}

constexpr Quaternion::Quaternion(const RotateEuler re) noexcept {
    if (re.z != 0.F) {
        *this = YXZRotateQ(re.y, re.x, re.z);
    } else {
        *this = YXRotateQ(re.y, re.x);
    }
}

constexpr Quaternion::Quaternion(const RotateEuler re, const bool isyxz) noexcept {
    if (isyxz) {
        if (re.z != 0.F) {
            *this = YXZRotateQ(re.y, re.x, re.z);
        } else {
            *this = YXRotateQ(re.y, re.x);
        }
    } else {
        if (re.z != 0.F) {
            *this = XYZRotateQ(re.x, re.y, re.z);
        } else {
            *this = XYRotateQ(re.x, re.y);
        }
    }
}

//CONVERSIONS BETWEEN ROTATE TYPES

HASH_INLINE RotateSphere::RotateSphere(const Vector vec) noexcept {
    longitude = hash_math::atan2(-vec.x, vec.y) * hash_constants::radians;
    latitude = hash_math::atan2(hash_math::sqrt(vec.x * vec.x + vec.y * vec.y), vec.z) * hash_constants::radians;
}

HASH_INLINE RotateSphere::RotateSphere(const RotateVector rotate) noexcept {
    longitude = hash_math::atan2(-rotate.end.x, rotate.end.y) * hash_constants::radians;
    latitude = hash_math::atan2(hash_math::sqrt(rotate.end.x * rotate.end.x + rotate.end.y * rotate.end.y), rotate.end.z) * hash_constants::radians;
    roll = rotate.roll;
}

HASH_INLINE RotateVector::RotateVector(const RotateSphere sphere) noexcept {
    const float r = hash_math::sin(sphere.latitude * hash_constants::inverse_radians);
    end.z = hash_math::cos(sphere.latitude * hash_constants::inverse_radians);
    end.y = r * hash_math::cos(sphere.longitude * hash_constants::inverse_radians);
    end.x = -r * hash_math::sin(sphere.longitude * hash_constants::inverse_radians);
    roll = sphere.roll;
}

HASH_INLINE RotateVector::RotateVector(const RotateEuler euler) noexcept {
    const float cy = hash_math::cos(euler.y * hash_constants::inverse_radians);
    const float sy = hash_math::sin(euler.y * hash_constants::inverse_radians);
    const float cx = hash_math::cos(euler.x * hash_constants::inverse_radians);
    const float sx = hash_math::sin(euler.x * hash_constants::inverse_radians);

    end.Set(sy * cx, -sx, cy * cx); //SPEED UP: THESE ARE THE Z COLUMN OUT OF YXROTATE, WHICH IS THE SAME AS BUILDING THAT MATRIX, THEN TRANSFORMING (0,0,1) BY IT
    roll = euler.z;
}

HASH_INLINE RotateEuler::RotateEuler(const RotateVector rotatev) noexcept {
    y = hash_math::atan2(rotatev.end.x, rotatev.end.z) * hash_constants::radians;
    x = hash_math::atan2(-rotatev.end.y, hash_math::sqrt(rotatev.end.x * rotatev.end.x + rotatev.end.z * rotatev.end.z)) * hash_constants::radians;
    z = rotatev.roll;
}

//THE 4 FUNCTIONS BELOW WORK ONLY 0 TO 90 DEGREES

HASH_INLINE float VectorsToLinear(const Vector v0, const Vector v1) noexcept {
    const float cosa = Dot(v0.Normalized(), v1.Normalized());
    if (cosa == 0.F)
        return 0.F;
    const float sina = hash_math::sqrt(1.F - cosa * cosa);
    const float slope = sina / cosa;
    const float percent = slope / (slope + 1.F) * 90.F;
    return percent;
}

HASH_INLINE float VectorsToAngle(const Vector v0, const Vector v1) noexcept {
    return hash_math::acos(Dot(v0.Normalized(), v1.Normalized())) * hash_constants::radians;
}

HASH_INLINE float LinearToAngle(const float linear) noexcept {
    return hash_math::atan(linear / (90.F - linear)) * hash_constants::radians;
}

constexpr float LinearToAngle360(const float linear) noexcept {
    if (linear < 0.F)
        return -LinearToAngle360(-linear);
    if (linear <= 90.F)
        return LinearToAngle(linear);
    const float remainder = hash_math::fmod(linear, 90.F);
    const float excess = linear - remainder;
    return excess + LinearToAngle(remainder);
}
