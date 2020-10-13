#pragma once

// Include CBT
#include "cbtMathUtil.h"

NS_CBT_BEGIN

/// A cbtVector2 represents a vector with 2 components, X and Y.
template <typename T>
class cbtVector2
{
public:
    // Variable(s)
    /// The X component of the vector.
    T m_X;
    /// The Y component of the vector.
    T m_Y;

    // Constructor(s) & Destructor
    /**
        \brief Constructs a new vector with given X, Y components.
        
        \param _x The X component of the vector.
        \param _y The Y component of the vector.

        \return A new cbtVector2 with given X and Y components.
    */
    cbtVector2(T _x = 0.0f, T _y = 0.0f)
        : m_X(_x), m_Y(_y)
    {}
    /**
        \brief Constructs a new cbtVector2 which is a copy of given cbtVector2.
        
        \param _x The cbtVector2 to copy.

        \return A new cbtVector2 which is a copy of _other.
    */
    cbtVector2(const cbtVector2& _other) { *this = _other; }
    /// \brief Destructor.
    ~cbtVector2() {}

    // Interface Function(s)
    /**
        \brief Sets the X and Y component of this vector.
        
        \param _x The value to set the X component to.
        \param _y The value to set the Y component to.
    */
    inline void Set(T _x, T _y) { m_X = _x; m_Y = _y; }
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
        \brief Get the X component of this vector.
        
        \return The X component of this vector.
    */
    inline T GetX() const { return m_X; }
    /**
        \brief Get the Y component of this vector.

        \return The Y component of this vector.
    */
    inline T GetY() const { return m_Y; }

    // Operator Overload(s)
    /**
        \brief Returns true if this vector and another vector are approximately equal.
        
        \param _rhs The vector to compare to.

        \return Returns true if this vector and another vector are approximately equal.

        \sa operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtBool operator==(const cbtVector2& _rhs) const { return cbtMathUtil::IsApproxEqual(m_X, _rhs.m_X) && cbtMathUtil::IsApproxEqual(m_Y, _rhs.m_Y); }
    /**
        \brief Returns true if this vector and another vector are NOT approximately equal.
        
        \param _rhs The vector to compare to.

        \return Returns true if this vector and another vector are NOT approximately equal.

        \sa operator==(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtBool operator!=(const cbtVector2& _rhs) const { return !(*this == _rhs); }
    /**
        \brief Set the X and Y component of this vector to the X and Y component of another vector.
        
        \param _rhs The vector whose X and Y component to set to.

        \return Returns this vector after setting its X and Y components.
        
        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&)
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)

    */
    cbtVector2& operator=(const cbtVector2& _rhs)
    {
        Set(_rhs.m_X, _rhs.m_Y);
        return *this;
    }

    /**
        \brief Adds this vector and another vector. The original vectors are not changed.
        
        \param _rhs The vector to add.

        \return Returns the result as a new cbtVector2.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2 operator+(const cbtVector2& _rhs) const { return cbtVector2(m_X + _rhs.m_X, m_Y + _rhs.m_Y); }
    /**
        \brief Adds this vector and another vector. This vector will become the resultant vector.
        
        \param _rhs The vector to add.

        \return Returns this vector as the resultant vector.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2& operator+=(const cbtVector2& _rhs)
    {
        m_X += _rhs.m_X; m_Y += _rhs.m_Y;
        return *this;
    }

    /**
        \brief Returns the negative of this vector.

        \return Returns the negative of this vector as a new Vector3.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2 operator-() const { return cbtVector2(-m_X, -m_Y); }
    /**
        \brief Subtract another vector from this vector. This vector will become the resultant vector.
        
        \param _rhs The vector to subtract.

        \return Returns this vector as the resultant vector.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2 operator-(const cbtVector2& _rhs) const { return cbtVector2(m_X - _rhs.m_X, m_Y - _rhs.m_Y); }
    /**
        \brief Subtracts another vector from this vector. The original vectors are not changed.
        
        \param _rhs The vector to subtract.

        \return Returns this vector as the resultant vector.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2& operator-=(const cbtVector2& _rhs)
    {
        m_X -= _rhs.m_X; m_Y -= _rhs.m_Y;
        return *this;
    }

    /**
        \brief Multiply this vector by a vector. This original vector is not changed.

        \param _rhs The vector to multiply.

        \return Returns the result as a new cbtVector2.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*=(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2 operator*(const cbtVector2& _rhs) const { return cbtVector2(m_X * _rhs.m_X, m_Y * _rhs.m_Y); }
    /**
        \brief Multiply this vector by a vector. This original vector is not changed.

        \param _rhs The vector to multiply.

        \return Returns this vector as the resultant vector.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const cbtVector2&),
            operator*(const T), operator*=(const T),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2& operator*=(const cbtVector2& _rhs)
    {
        m_X *= _rhs.m_X; m_Y *= _rhs.m_Y;
        return *this;
    }

    /**
        \brief Multiply this vector and a scalar. This original vector is not changed.
        
        \param _scalar The scalar to multiply.

        \return Returns the result as a new cbtVector2.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*=(const T),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2 operator*(const T _scalar) const { return cbtVector2(m_X * _scalar, m_Y * _scalar); }
    /**
        \brief Multiply this vector and a scalar. This original vector is not changed.
        
        \param _scalar The scalar to multiply.

        \return Returns this vector as the resultant vector.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T),
            operator*(const T _scalar, const cbtVector2& _vector)
    */
    cbtVector2& operator*=(const T _scalar)
    {
        m_X *= _scalar; m_Y *= _scalar;
        return *this;
    }

    // Friend Function(s)
    /**
        \brief Multiply this vector and a scalar. This original vector is not changed.
        
        \param _scalar The scalar to multiply.

        \return Returns the result as a new cbtVector2.

        \sa operator==(const cbtVector2&), operator!=(const cbtVector2&), operator=(const cbtVector2&),
            operator+(const cbtVector2&), operator+=(const cbtVector2&),
            operator(), operator-(const cbtVector2&), operator-=(const cbtVector2&),
            operator*(const cbtVector2&), operator*=(const cbtVector2&),
            operator*(const T), operator*=(const T)
    */
    friend cbtVector2 operator*(const T _scalar, const cbtVector2& _vector) { return _vector * _scalar; }

    // Static Constant Variable(s)
    /// Equivalent to cbtVector2(0, 1).
    static const cbtVector2 UP;
    /// Equivalent to cbtVector2(0, -1).
    static const cbtVector2 DOWN;
    /// Equivalent to cbtVector2(-1, 0).
    static const cbtVector2 LEFT;
    /// Equivalent to cbtVector2(1, 0).
    static const cbtVector2 RIGHT;
    /// Equivalent to cbtVector2(0, 0).
    static const cbtVector2 ZERO;
};

// Static Constant Variable(s)
template <typename T> const cbtVector2<T> cbtVector2<T>::UP = cbtVector2<T>(0, 1);
template <typename T> const cbtVector2<T> cbtVector2<T>::DOWN = -cbtVector2<T>::UP;
template <typename T> const cbtVector2<T> cbtVector2<T>::LEFT = cbtVector2<T>(1, 0);
template <typename T> const cbtVector2<T> cbtVector2<T>::RIGHT = -cbtVector2<T>::LEFT;
template <typename T> const cbtVector2<T> cbtVector2<T>::ZERO = cbtVector2<T>(0, 0);

// Type Definition(s)
typedef cbtVector2<cbtF32> CBTVector2F;
typedef cbtVector2<cbtU32> CBTVector2U;
typedef cbtVector2<cbtS32> CBTVector2S;

/**
    \brief Get the square of the length of this vector.
           If possible, use LengthSquared() instead of Length() as it is cheaper
           to calculate the length squared then the length.

    \return The square of the length of this vector.
*/
template <typename T>
T LengthSquared(const cbtVector2<T>& _vector) { return _vector.m_X * _vector.m_X + _vector.m_Y * _vector.m_Y; }
/**
    \brief Get the length of this vector.
           If possible, use LengthSquared() instead of Length() as it is cheaper
           to calculate the length squared then the length.

    \return The length of this vector.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, T) Length(const cbtVector2<T>& _vector) { return sqrt(LengthSquared(_vector)); }

/// \brief Normalize this vector.
template <typename T>
CBT_ENABLE_IF_FLOAT(T, void) Normalize(cbtVector2<T>& _vector)
{
    T length = Length(_vector);
    if (cbtMathUtil::IsApproxEqual<T>(0, length))
    {
        _vector = cbtVector2<T>::ZERO;
    }
    else
    {
        _vector.m_X /= length; _vector.m_Y /= length;
    }
}
/**
    \brief Returns a normalized version of this vector as a new cbtVector2.

    \return A normalized version of this vector as a new cbtVector2.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, cbtVector2<T>) Normalized(const cbtVector2<T>& _vector)
{
    T length = Length(_vector);
    if (cbtMathUtil::IsApproxEqual<T>(0, length))
    {
        return cbtVector2<T>::ZERO;
    }
    else
    {
        return cbtVector2<T>(_vector.m_X / length, _vector.m_Y / length);
    }
}

/**
    \brief Returns the dot product between this vector and another cbtVector2.

    \return The dot product between this vector and another cbtVector2.
*/
template <typename T>
T Dot(const cbtVector2<T>& _vectorA, const cbtVector2<T>& _vectorB) { return _vectorA.m_X * _vectorB.m_X + _vectorA.m_Y * _vectorB.m_Y; }
/**
    \brief Returns the angle between this vector and another cbtVector2 in Degrees.

    \return The angle between this vector and another cbtVector2 in Degrees.
*/
template <typename T>
CBT_ENABLE_IF_FLOAT(T, T) Angle(const cbtVector2<T>& _vectorA, const cbtVector2<T>& _vectorB)
{
    return std::acos(Dot(_vectorA, _vectorB) / (Length(_vectorA) * Length(_vectorB))) * cbtMathUtil::RAD2DEG;
}

NS_CBT_END