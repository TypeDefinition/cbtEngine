#pragma once

// Include CBT
#include "CBTMacros.h"
#include "CBTMathUtil.h"

// Include STD
#include <iostream>

NS_CBT_BEGIN

/// A CBTVector3 represents a vector with 2 components, X, Y and Z.
template <typename T>
class CBTVector3
{
public:
    /// The X component of the vector.
    T m_X;
    /// The Y component of the vector.
    T m_Y;
    /// The Z component of the vector.
    T m_Z;

    /**
        \brief Constructs a new vector with given X, Y components.
        
        \param _x The X component of the vector.
        \param _y The Y component of the vector.
        \param _z The Z component of the vector.

        \return A new CBTVector3 with given X, Y and Z components.
    */
    CBTVector3(T _x = 0.0f, T _y = 0.0f, T _z = 0.0f)
        : m_X(_x), m_Y(_y), m_Z(_z)
    {}
    /**
        \brief Constructs a new CBTVector3 which is a copy of given CBTVector3.
        
        \param _x The CBTVector3 to copy.

        \return A new CBTVector3 which is a copy of _other.
    */
    CBTVector3(const CBTVector3& _other) { *this = _other; }
    /// \brief Destructor.
    ~CBTVector3() {}

    // Interface Function(s)
    /**
        \brief Sets the X, Y and Z component of this vector.
        
        \param _x The value to set the X component to.
        \param _y The value to set the Y component to.
        \param _z The value to set the Z component to.
    */
    inline void Set(T _x, T _y, T _z) { m_X = _x; m_Y = _y; m_Z = _z; }
    /**
        \brief Sets the X component of this vector.
        
        \param _x The value to set the X component to.
    */
    inline void SetX(T _x) { m_X = _x; }
    /**
        \brief Sets the Y component of this vector.
        
        \param _y The value to set the Y component to.
    */
    inline void SetY(T _y) { m_Y = _y; }
    /**
        \brief Sets the Z component of this vector.

        \param _z The value to set the Z component to.
    */
    inline void SetZ(T _z) { m_Z = _z; }
    /**
        \brief Get the X component of this vector.

        \return The X component of this vector.
    */
    inline T GetX() const { return m_X; }
    /**
        \brief Get the Y component of this vector.

        \return The Y component of this vector.
    */
    inline T GetY() const { return m_Y; }
    /**
        \brief Get the Z component of this vector.

        \return The Z component of this vector.
    */
    inline T GetZ() const { return m_Z; }

    // Operator Overload(s)
    /**
        \brief Returns true if this vector and another vector are approximately equal.
        
        \param _rhs The vector to compare to.

        \return Returns true if this vector and another vector are approximately equal.

        \sa operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    cbtBool operator==(const CBTVector3& _rhs) const { return CBTMathUtil::IsApproxEqual(m_X, _rhs.m_X) && CBTMathUtil::IsApproxEqual(m_Y, _rhs.m_Y) && CBTMathUtil::IsApproxEqual(m_Z, _rhs.m_Z); }
    /**
        \brief Returns true if this vector and another vector are NOT approximately equal.
        
        \param _rhs The vector to compare to.

        \return Returns true if this vector and another vector are NOT approximately equal.

        \sa operator==(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    cbtBool operator!=(const CBTVector3& _rhs) const { return !(*this == _rhs); }
    /**
        \brief Set the X, Y and Z component of this vector to the X, Y and Z component of another vector.
        
        \param _rhs The vector whose X, Y and Z component to set to.

        \return Returns this vector after setting its X, Y and Z components.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3& operator=(const CBTVector3& _rhs)
    {
        Set(_rhs.m_X, _rhs.m_Y, _rhs.m_Z);
        return *this;
    }

    /**
        \brief Adds this vector and another vector. The original vectors are not changed.

        \param _rhs The vector to add.

        \return Returns the result as a new CBTVector3.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3 operator+(const CBTVector3& _rhs) const { return CBTVector3(m_X + _rhs.m_X, m_Y + _rhs.m_Y, m_Z + _rhs.m_Z); }
    /**
        \brief Adds this vector and another vector. This vector will become the resultant vector.
        
        \param _rhs The vector to add.

        \return Returns this vector as the resultant vector.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&)
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3& operator+=(const CBTVector3& _rhs)
    {
        m_X += _rhs.m_X; m_Y += _rhs.m_Y; m_Z += _rhs.m_Z;
        return *this;
    }

    /**
        \brief Returns the negative of this vector.

        \return Returns the negative of this vector as a new CBTVector3.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3 operator-() const { return CBTVector3(-m_X, -m_Y, -m_Z); }
    /**
        \brief Subtract another vector from this vector. This vector will become the resultant vector.
        
        \param _rhs The vector to subtract.

        \return Returns this vector as the resultant vector.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3 operator-(const CBTVector3& _rhs) const { return CBTVector3(m_X - _rhs.m_X, m_Y - _rhs.m_Y, m_Z - _rhs.m_Z); }
    /**
        \brief Subtracts another vector from this vector. This vector will become the resultant vector.
        
        \param _rhs The vector to subtract.

        \return Returns this vector as the resultant vector.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3& operator-=(const CBTVector3& _rhs)
    {
        m_X -= _rhs.m_X; m_Y -= _rhs.m_Y; m_Z -= _rhs.m_Z;
        return *this;
    }

    /**
        \brief Multiply this vector by another vector. This original vector is not changed.

        \param _rhs The vector to multiply.

        \return Returns the result as a new CBTVector3.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&),
            operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3 operator*(const CBTVector3& _rhs) const { return CBTVector3(m_X * _rhs.m_X, m_Y * _rhs.m_Y, m_Z * _rhs.m_Z); }

    /**
        \brief Multiply this vector by another vector. This vector will become the resultant vector.

        \param _rhs The vector to multiply.

        \return Returns the result as a new CBTVector3.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&),
            operator*(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3& operator*=(const CBTVector3& _rhs)
    {
        m_X *= _rhs.m_X; m_Y *= _rhs.m_Y; m_Z *= _rhs.m_Z;
        return *this;
    }

    /**
        \brief Multiply this vector by a scalar. This original vector is not changed.
        
        \param _scalar The scalar to multiply.

        \return Returns the result as a new CBTVector3.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3 operator*(const T _scalar) const { return CBTVector3(m_X * _scalar, m_Y * _scalar, m_Z * _scalar); }
    /**
        \brief Multiply this vector by a scalar. This vector will become the resultant vector.
        
        \param _scalar The scalar to multiply.

        \return Returns this vector as the resultant vector.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T),
            operator*(const T _scalar, const CBTVector3& _vector)
    */
    CBTVector3& operator*=(const T _scalar)
    {
        m_X *= _scalar; m_Y *= _scalar; m_Z *= _scalar;
        return *this;
    }

    // Friend Function(s)
    /**
        \brief Multiply this vector by a scalar. This original vector is not changed.
        
        \param _scalar The scalar to multiply.

        \return Returns the result as a new CBTVector3.

        \sa operator==(const CBTVector3&), operator!=(const CBTVector3&), operator=(const CBTVector3&),
            operator+(const CBTVector3&), operator+=(const CBTVector3&),
            operator(), operator-(const CBTVector3&), operator-=(const CBTVector3&),
            operator*(const CBTVector3&), operator*=(const CBTVector3&),
            operator*(const T), operator*=(const T)
    */
    friend CBTVector3 operator*(const T _scalar, const CBTVector3& _vector) { return _vector * _scalar; }

    // Static Constant Variable(s)
    /// Equivalent to CBTVector3(0, 0, 1).
    static const CBTVector3 FORWARDS;
    /// Equivalent to CBTVector3(0, 0, -1).
    static const CBTVector3 BACKWARDS;
    /// Equivalent to CBTVector3(1, 0, 0).
    static const CBTVector3 LEFT;
    /// Equivalent to CBTVector3(-1, 0, 0).
    static const CBTVector3 RIGHT;
    /// Equivalent to CBTVector3(0, 1, 0).
    static const CBTVector3 UP;
    /// Equivalent to CBTVector3(0, -1, 0).
    static const CBTVector3 DOWN;
    /// Equivalent to CBTVector3(0, 0, 0).
    static const CBTVector3 ZERO;
};

// Static Constant Variable(s)
template <typename T> const CBTVector3<T> CBTVector3<T>::FORWARDS = CBTVector3<T>(0, 0, 1);
template <typename T> const CBTVector3<T> CBTVector3<T>::BACKWARDS = -CBTVector3<T>::FORWARDS;
template <typename T> const CBTVector3<T> CBTVector3<T>::LEFT = CBTVector3<T>(1, 0, 0);
template <typename T> const CBTVector3<T> CBTVector3<T>::RIGHT = -CBTVector3<T>::LEFT;
template <typename T> const CBTVector3<T> CBTVector3<T>::UP = CBTVector3<T>(0, 1, 0);
template <typename T> const CBTVector3<T> CBTVector3<T>::DOWN = -UP;
template <typename T> const CBTVector3<T> CBTVector3<T>::ZERO = CBTVector3<T>(0, 0, 0);

// Type Definition(s)
typedef CBTVector3<cbtF32> CBTVector3F;
typedef CBTVector3<cbtU32> CBTVector3U;
typedef CBTVector3<cbtS32> CBTVector3S;

/**
    \brief Get the square of the length of this vector.
           If possible, use LengthSquared() instead of Length() as it is cheaper
           to calculate the length squared then the length.

    \return The square of the length of this vector.
*/
template <typename T>
T LengthSquared(const CBTVector3<T>& _vector) { return _vector.m_X * _vector.m_X + _vector.m_Y * _vector.m_Y + _vector.m_Z * _vector.m_Z; }
/**
    \brief Get the length of this vector.
           If possible, use LengthSquared() instead of Length() as it is cheaper
           to calculate the length squared then the length.

    \return The length of this vector.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, T) Length(const CBTVector3<T>& _vector) { return std::sqrt(LengthSquared(_vector)); }

/// \brief Normalize this vector.
template <typename T>
CBT_ENABLE_IF_FLOAT(T, void) Normalize(CBTVector3<T>& _vector)
{
    T length = Length(_vector);
    if (CBTMathUtil::IsApproxEqual<T>(0, length))
    {
        _vector = CBTVector3<T>::ZERO;
    }
    else
    {
        _vector.m_X /= length; _vector.m_Y /= length; _vector.m_Z /= length;
    }
}
/**
    \brief Returns a normalized version of this vector as a new CBTVector3.

    \return A normalized version of this vector as a new CBTVector3.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, CBTVector3<T>) Normalized(const CBTVector3<T>& _vector)
{
    T length = Length(_vector);
    if (CBTMathUtil::IsApproxEqual<T>(0, length))
    {
        return CBTVector3<T>::ZERO;
    }
    else
    {
        return CBTVector3<T>(_vector.m_X / length, _vector.m_Y / length, _vector.m_Z / length);
    }
}

/**
    \brief Returns the dot product between this vector and another CBTVector3.

    \return The dot product between this vector and another CBTVector3.
*/
template <typename T>
T Dot(const CBTVector3<T>& _vectorA, const CBTVector3<T>& _vectorB) { return _vectorA.m_X * _vectorB.m_X + _vectorA.m_Y * _vectorB.m_Y + _vectorA.m_Z * _vectorB.m_Z; }
/**
    \brief Returns the cross product between this vector and another CBTVector3.

    \return The cross product between this vector and another CBTVector3 as a new CBTVector3.
*/
template <typename T>
CBTVector3<T> Cross(const CBTVector3<T>& _vectorA, const CBTVector3<T>& _vectorB)
{
    return CBTVector3<T>((_vectorA.m_Y * _vectorB.m_Z) - (_vectorA.m_Z * _vectorB.m_Y), (_vectorA.m_Z * _vectorB.m_X) - (_vectorA.m_X * _vectorB.m_Z), (_vectorA.m_X * _vectorB.m_Y) - (_vectorA.m_Y * _vectorB.m_X));
}
/**
    \brief Returns the projection of this vector onto another CBTVector3.

    \return The projection of this vector onto another CBTVector3 as a new CBTVector3.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, CBTVector3<T>) Project(const CBTVector3<T>& _vectorA, const CBTVector3<T>& _vectorB)
{
    CBTVector3<T> vectorBNormalized = _vectorB.Normalized();
    return Dot(_vectorA, vectorBNormalized) * vectorBNormalized;
}
/**
    \brief Returns the angle between this vector and another CBTVector3 in Degrees.

    \return The angle between this vector and another CBTVector3 in Degrees.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, T) Angle(const CBTVector3<T>& _vectorA, const CBTVector3<T>& _vectorB)
{
    return std::acos(Dot(_vectorA, _vectorB) / (Length(_vectorA) * Length(_vectorB))) * CBTMathUtil::RAD2DEG;
}

NS_CBT_END