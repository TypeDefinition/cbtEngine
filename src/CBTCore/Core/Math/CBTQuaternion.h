#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Debug/CBTDebug.h"
#include "CBTMatrixUtil.h"
#include "CBTVector3.h"

NS_CBT_BEGIN

/** 
    \brief
        Quaternion Class

        After reading a metric fuck ton of materials, here is HOW to use Quaternions.
        I do not understand and cannot explain WHY these things work they way the do.
        I can only memorize the formulas and plug them in when necessary.
        
        Disclaimer:\n
        Anything I write below is what I THINK I understand about Quaternions.
        That means that it could all be wrong and I'm full of shit.
        But hey, I tried.
        
        To Future Me:\n
        Hopefully you've (I've? we've?) figured it out eventually.
        
        If for some reason someone other than me is reading:\n
        If you actually know this shit please teach me.
        
        Quaternions may seem like a Vector, but with 4 elements.
        However, when I try to make sense of it, it simply does not make sense.
        Such as why when using a rotation Quaternion we need to multiply W by cos(Angle)
        and XYZ by sin(Angle).
        
        How I understand Quaternions is that they are like Matrices.
        Unlike a Vectors, which are an actual thing, such
        as a direction or position, Matrices aren't. Matrices are like a tool
        that we plug numbers into in order to do multiplication and shit and
        get a result. So like the matrix that REPRESENTS a position may be |x|
                                                                           |y|
                                                                           |z|
                                                                           |1|,
        but it isn't a position. It is simply a matrix with the numbers of a position plugged in.
        So quaternions are kinda similar-ish. It looks like it is a rotation, but it is
        more of a tool that plug numbers into to REPRESENT a rotation.
        
        Multiplication of Basis Elements:
        i^2 = j^2 = k^2 = ijk = -1
        ij = k
        ji = -k
        jk = i
        kj = -i
        ki = j
        ik = -j
        
        All rotation Quaternions are Unit Quaternions.
        Thus, m_W = cos(angle/2) and m_XYZ = sin(angle/2) * rotationAxis only applies to Unit Quaterions.
        
        Maintaining Rotation During Quaternion Normalization:
        
        Math answer:\n
        A unit quaternion represents a rotation in 3D space.
        Any other (i.e.: non-unit) quaternion does not represent a rotation,
        so the formula angle = 2 * acos(q0) does not apply to these quaternions.
        So there is no change of angle when normalizing,
        because the quaternions that you would normalize do not represent rotations in the first place.
        
        Programming answer:\n
        Floating point operations have accuracy issues.
        These issues result in small errors, which if accumulated may become large errors.
        When multiplying two unit quaternions, the mathematical result is another unit quaternion.
        However the floating point implementation of unit quaternions multiplication may result in
        a quaternion with a norm close to 1 but not equal 1. In this case we shall normalize the quaternion
        to correct the error. When we normalize we divide q0 by the norm which is very close to 1, so there
        is no major change in the value of q0. Because we normalize early the norm is always very close
        to 1 and we don't need to worry about the precision.
        
        Converting Quaternion To Matrix:\n
        When Quaternion = (w, x, y, z),\n
        <pre>
        Matrix =  | w  -x  -y  -z |\n
                  | x   w  -z   y |\n
                  | y   z   w  -x |\n
                  | z  -y   x   w |\n
        </pre>
*/
class CBTQuaternion
{
private:
    /// The scalar component of the quaternion, represented by W.
    cbtF32 m_W;
    /// The vector3 component of the quaternion, represented by X, Y and Z.
    CBTVector3F m_XYZ;

public:
    // Constructor(s) & Destructor
    CBTQuaternion(cbtF32 _w = 1.0f, cbtF32 _x = 0.0f, cbtF32 _y = 0.0f, cbtF32 _z = 0.0f);
    CBTQuaternion(const CBTQuaternion& _other);
    CBTQuaternion(cbtF32 _angle, const CBTVector3F& _rotationAxis);
    ~CBTQuaternion();

    // Interface Function(s)
    /**
        \brief Set the components of this quaternion.

        \param _w The W component.
        \param _x The X component.
        \param _y The Y component.
        \param _z The Z component.
    */
    inline void Set(cbtF32 _w, cbtF32 _x, cbtF32 _y, cbtF32 _z) { m_W = _w; m_XYZ = CBTVector3F(_x, _y, _z); }
    /**
        \brief Set the components of this quaternion.

        \param _w The scalar component, represented by W.
        \param _xyz The vector3 component, represented by XYZ.
    */
    inline void Set(cbtF32 _w, const CBTVector3F& _xyz) { m_W = _w; m_XYZ = _xyz; }
    /**
        \brief Set the W component of this quaternion.

        \param _w The W component.
    */
    inline void SetW(cbtF32 _w) { m_W = _w; }
    /**
        \brief Set the X component of this quaternion.

        \param _x The X component.
    */
    inline void SetX(cbtF32 _x) { m_XYZ.SetX(_x); }
    /**
        \brief Set the Y component of this quaternion.

        \param _y The Y component.
    */
    inline void SetY(cbtF32 _y) { m_XYZ.SetY(_y); }
    /**
        \brief Set the Z component of this quaternion.

        \param _z The Z component.
    */
    inline void SetZ(cbtF32 _z) { m_XYZ.SetZ(_z); }
    /**
        \brief Get the W component of this quaternion.

        \return The W component of this quaternion.
    */
    inline cbtF32 GetW() const { return m_W; }
    /**
        \brief Get the X component of this quaternion.

        \return The X component of this quaternion.
    */
    inline cbtF32 GetX() const { return m_XYZ.GetX(); }
    /**
        \brief Get the Y component of this quaternion.

        \return The Y component of this quaternion.
    */
    inline cbtF32 GetY() const { return m_XYZ.GetY(); }
    /**
        \brief Get the Z component of this quaternion.

        \return The Z component of this quaternion.
    */
    inline cbtF32 GetZ() const { return m_XYZ.GetZ(); }
    /**
        \brief Get the XYZ component of this quaternion.

        \return The XYZ component of this quaternion.
    */
    inline const CBTVector3F& GetXYZ() const { return m_XYZ; }

    /**
        \brief Get the length of the quaternion. If possible, use LengthSquared() instead of Length() as it is more expensive to compute the length then the length squared.

        \return The length of the quaternion.
    */
    cbtF32 Length() const;
    /**
        \brief Get the length squared of the quaternion. If possible, use LengthSquared() instead of Length() as it is more expensive to compute the length then the length squared.

        \return The length squared of the quaternion.
    */
    cbtF32 LengthSquared() const;

    /**
        \brief Normalise this quaternion.
    */
    void Normalize();
    /**
        \brief Get the normalised version of this quaternion.

        \return The normalised version of this quaternion.
    */
    CBTQuaternion Normalized();

    /**
        \brief Inverse this quaternion.
    */
    void Inverse();
    /**
        \brief Get the inversed version of this quaternion.

        \return The inverse version of this quaternion.
    */
    CBTQuaternion Inversed() const;

    /**
        \brief Get the dot product of this quaternion and another quaternion.

        \param _other The other quaterion to calculate the dot product with.

        \return The dot product of this quaternion and the other quaternion.
    */
    cbtF32 Dot(const CBTQuaternion& _other) const;

    // Rotation Function(s)
    /**
        \brief Get this quaterion as a rotation in degrees, around an axis.

        \param _angle The resultant angle of rotation in degrees.
        \param _rotationAxis The resultant axis of rotation.
    */
    void ToAxisAngle(cbtF32& _angle, CBTVector3F& _rotationAxis) const;
    /**
        \brief Get this quaternion as a CBTMatrix4F rotation matrix.

        \return This quaternion as a CBTMatrix4F rotation matrix.

        \warning A rotation quaternion must be a unit quaternion.
    */
    CBTMatrix4F ToRotationMatrix() const;
    /**
        \brief Set this quaternion to a rotation given an angle in degrees and an axis.

        \param _angle The angle rotation in degrees.
        \param _rotationAxis The axis of rotation.
    */
    void SetToRotation(cbtF32 _angle, const CBTVector3F& _rotationAxis);

    // Operator Overload(s)
    /**
        \brief Set the W, X, Y and Z component of this quaternion to the W, X, Y and Z component of another quaternion.

        \param _rhs The quaternion whose W, X, Y and Z component to set to.

        \return Returns this quaternion after setting its W, X, Y and Z components.
    */
    CBTQuaternion& operator=(const CBTQuaternion& _rhs);
    /**
        \brief Returns true if this quaternion and another quaternion are approximately equal.

        \param _rhs The quaternion to compare to.

        \return Returns true if this quaternion and another quaternion are approximately equal. Otherwise, return false.
    */
    cbtBool operator==(const CBTQuaternion& _rhs) const;
    /**
        \brief Returns true if this quaternion and another quaternion are NOT approximately equal.

        \param _rhs The quaternion to compare to.

        \return Returns true if this quaternion and another quaternion are NOT approximately equal. Otherwise, return false.
    */
    cbtBool operator!=(const CBTQuaternion& _rhs) const;

    /**
        \brief Multiply this quaternion with another quaternion. This original quaternion is not changed.

        \param _rhs The quaternion to multiply.

        \return Returns the result as a new CBTQuaternion.
    */
    CBTQuaternion operator*(const CBTQuaternion& _rhs) const;
    /**
        \brief Multiply this quaternion with another quaternion. This vector will become the resultant vector.

        \param _rhs The quaternion to multiply.

        \return Returns the result as a new CBTQuaternion.
    */
    CBTQuaternion& operator*=(const CBTQuaternion& _rhs);

    // Static Function(s)
    /**
        \brief Rotate a point around an axis by an angle in degrees.

        \param _point The point to rotate.
        \param _angle The angle of rotation in degrees.
        \param _rotationAxis The axis of rotation.

        \return The result of the point after the rotation.
    */
    static CBTVector3F Rotate(const CBTVector3F& _point, cbtF32 _angle, const CBTVector3F& _rotationAxis);

    /**
        \brief Spherical Linear Interpolation betwen 2 quaternions.

        \_param _start The starting quaternion.
        \_param _end The ending quaternion
        \_param _ratio The ratio to interpolate between _start and _end. A value of 0 will return _start, and a value of 1 will return _end.
        \_param _clampRatio If set to true, the _ratio is clamped to between 0 and 1. The default value is false.
    */
    static CBTQuaternion Slerp(const CBTQuaternion& _start, const CBTQuaternion& _end, cbtF32 _ratio, cbtBool _clampRatio = false);

    // Static Constant Variable(s)
    /// Equivalent to CBTQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
    static const CBTQuaternion IDENTITY;
    /// Equivalent to CBTQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
    static const CBTQuaternion ZERO;
};

NS_CBT_END