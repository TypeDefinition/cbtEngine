// Include CBT
#include "CBTQuaternion.h"

NS_CBT_BEGIN

// Static Constant Variable(s)
const CBTQuaternion CBTQuaternion::IDENTITY = CBTQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
const CBTQuaternion CBTQuaternion::ZERO = CBTQuaternion(0.0f, 0.0f, 0.0f, 0.0f);

// Constructor(s) & Destructor
CBTQuaternion::CBTQuaternion(cbtF32 _w, cbtF32 _x, cbtF32 _y, cbtF32 _z)
{
    Set(_w, _x, _y, _z);
}

CBTQuaternion::CBTQuaternion(const CBTQuaternion& _other)
{
    *this = _other;
}

CBTQuaternion::CBTQuaternion(cbtF32 _angle, const CBTVector3F& _rotationAxis)
{
    SetToRotation(_angle, _rotationAxis);
}

CBTQuaternion::~CBTQuaternion()
{
}

// Interface Function(s)
cbtF32 CBTQuaternion::Length() const
{
    return std::sqrt(LengthSquared());
}

cbtF32 CBTQuaternion::LengthSquared() const
{
    return GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ();
}

// Normalizes the quaternion. If the length of the quaternion is 0, it will become a zero quaternion.
void CBTQuaternion::Normalize()
{
    if (CBTMathUtil::IsApproxEqual(0.0f, LengthSquared()))
    {
        m_W = 0.0f;
        m_XYZ = CBTVector3F::ZERO;
    }
    else
    {
        cbtF32 length = Length();
        m_W /= length;
        m_XYZ.Set(GetX() / length, GetY() / length, GetZ() / length);
    }
}

// Normalizes the quaternion. If the length of the quaternion is 0, it will return a zero quaternion.
CBTQuaternion CBTQuaternion::Normalized()
{
    if (CBTMathUtil::IsApproxEqual(0.0f, LengthSquared()))
    {
        return CBTQuaternion::ZERO;
    }
    else
    {
        cbtF32 length = Length();
        return CBTQuaternion(GetW() / length, GetX() / length, GetY() / length, GetZ() / length);
    }
}

void CBTQuaternion::Inverse()
{
    m_XYZ = -m_XYZ;
}

CBTQuaternion CBTQuaternion::Inversed() const
{
    return CBTQuaternion(GetW(), -GetX(), -GetY(), -GetZ());
}

cbtF32 CBTQuaternion::Dot(const CBTQuaternion& _other) const
{
    return GetW() * _other.GetW() + GetX() * _other.GetX() + GetY() * _other.GetY() + GetZ() * _other.GetZ();
}

// Rotation Function(s)
void CBTQuaternion::ToAxisAngle(cbtF32& _angle, CBTVector3F& _rotationAxis) const
{
    // A rotational quaternion must be a unit quaternion.
    CBT_ASSERT(CBTMathUtil::IsApproxEqual(1.0f, LengthSquared()));

    _angle = std::acos(m_W) * 2.0f * CBTMathUtil::RAD2DEG;
    // We simply normalize m_XYZ since the direction of m_XYZ is the same as the rotation axis.
    _rotationAxis = NS_CBT::Normalized(m_XYZ);
}

CBTMatrix4F CBTQuaternion::ToRotationMatrix() const
{
    CBTMatrix4F matrixA;

    matrixA[0][0] = GetW();
    matrixA[1][1] = GetW();
    matrixA[2][2] = GetW();
    matrixA[3][3] = GetW();

    matrixA[0][3] = GetX();
    matrixA[1][2] = GetX();
    matrixA[2][1] = -GetX();
    matrixA[3][0] = -GetX();

    matrixA[0][2] = -GetY();
    matrixA[1][3] = GetY();
    matrixA[2][0] = GetY();
    matrixA[3][1] = -GetY();

    matrixA[0][1] = GetZ();
    matrixA[1][0] = -GetZ();
    matrixA[2][3] = GetZ();
    matrixA[3][2] = -GetZ();

    CBTMatrix4F matrixB;

    matrixB[0][0] = GetW();
    matrixB[1][1] = GetW();
    matrixB[2][2] = GetW();
    matrixB[3][3] = GetW();

    matrixB[0][3] = -GetX();
    matrixB[1][2] = GetX();
    matrixB[2][1] = -GetX();
    matrixB[3][0] = GetX();

    matrixB[0][2] = -GetY();
    matrixB[1][3] = -GetY();
    matrixB[2][0] = GetY();
    matrixB[3][1] = GetY();

    matrixB[0][1] = GetZ();
    matrixB[1][0] = -GetZ();
    matrixB[2][3] = -GetZ();
    matrixB[3][2] = GetZ();

    return matrixA * matrixB;
}

void CBTQuaternion::SetToRotation(cbtF32 _angle, const CBTVector3F& _rotationAxis)
{
    // If the rotation axis is invalid, set this to a identity quaternion.
    if (CBTMathUtil::IsApproxEqual(NS_CBT::LengthSquared(_rotationAxis), 0.0f))
    {
        *this = CBTQuaternion::IDENTITY;
    }
    else
    {
        m_W = std::cos(_angle * 0.5f * CBTMathUtil::DEG2RAD);
        m_XYZ = std::sin(_angle * 0.5f * CBTMathUtil::DEG2RAD) * NS_CBT::Normalized(_rotationAxis);
    }
}

// Operator Overload(s)
CBTQuaternion& CBTQuaternion::operator=(const CBTQuaternion& _rhs)
{
    Set(_rhs.GetW(), _rhs.GetX(), _rhs.GetY(), _rhs.GetZ());

    return *this;
}

cbtBool CBTQuaternion::operator==(const CBTQuaternion& _rhs) const
{
    return CBTMathUtil::IsApproxEqual(m_W, _rhs.m_W) && (m_XYZ == _rhs.m_XYZ);
}

cbtBool CBTQuaternion::operator!=(const CBTQuaternion& _rhs) const
{
    return !(*this == _rhs);
}

CBTQuaternion CBTQuaternion::operator*(const CBTQuaternion& _rhs) const
{
    cbtF32 w = m_W * _rhs.m_W - NS_CBT::Dot(m_XYZ, _rhs.m_XYZ);
    CBTVector3F xyz = m_W * _rhs.m_XYZ + _rhs.m_W * m_XYZ + NS_CBT::Cross(m_XYZ, _rhs.m_XYZ);

    return CBTQuaternion(w, xyz.GetX(), xyz.GetY(), xyz.GetZ());
}

CBTQuaternion& CBTQuaternion::operator*=(const CBTQuaternion& _rhs)
{
    *this = *this * _rhs;

    return *this;
}

// Static Function(s)
CBTVector3F CBTQuaternion::Rotate(const CBTVector3F& _point, cbtF32 _angle, const CBTVector3F& _rotationAxis)
{
    CBTQuaternion rotation(_angle, _rotationAxis);
    CBTQuaternion point(0.0f, _point.GetX(), _point.GetY(), _point.GetZ());
    CBTQuaternion result = rotation * point * rotation.Inversed();
    
    return CBTVector3F(result.GetX(), result.GetY(), result.GetZ());
}

// This function assumes that _start & _end are unit quaternions.
CBTQuaternion CBTQuaternion::Slerp(const CBTQuaternion& _start, const CBTQuaternion& _end, cbtF32 _ratio, cbtBool _clampRatio)
{
    CBT_ASSERT(CBTMathUtil::IsApproxEqual(_start.LengthSquared(), 1.0f));
    CBT_ASSERT(CBTMathUtil::IsApproxEqual(_end.LengthSquared(), 1.0f));

    if (_clampRatio)
    {
        _ratio = CBTMathUtil::Clamp<cbtF32>(_ratio, 0.0f, 1.0f);
    }

    /*
    Let start quaternion be s.
    Let end quaternion be e.
    Let the quaternion needed to transform s to e be d (difference).

    We need to find what is d.
    d * s = e
    Therefore,
    d * s * s.Inversed = e * s.Inversed [s * s.Inversed cancels each other out.]
    d = e * s.Inversed
    */
    CBTQuaternion d = _end * _start.Inversed();

    /*
    Since s * d = e, if we want for example to only turn halfway, then we need to half the angle that d turns.
    For example, d could represent a rotation of 90 degrees around the Vector::UP axis.
    So to do a half rotation, we need to do a rotation of 45 degress around the Vector::UP axis.
    To do that, we must first figure out what the angle and axis of d is.
    */
    cbtF32 dAngle;
    CBTVector3F dAxis;
    d.ToAxisAngle(dAngle, dAxis);

    // Now that we have the angle and axis to rotate around, we have our result.
    return CBTQuaternion(dAngle * _ratio, dAxis) * _start;
}

NS_CBT_END