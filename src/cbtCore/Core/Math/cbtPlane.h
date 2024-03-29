#pragma once

// Include CBT
#include "cbtMacros.h"
#include "cbtMathUtil.h"
#include "cbtVector3.h"

NS_CBT_BEGIN

/**
    \brief Represents the equation of a plane.
*/
    class cbtPlane
    {
    public:
        /// \brief The normal of the plane.
        cbtVector3F m_Normal;
        /// \brief The constant of the plane.
        cbtF32 m_Constant;

        /**
            \brief Constructs a new plane with given normal and constant.

            \param _normal The normal of the plane.
            \param _constant The constant of the plane.

            \return A new plane with given normal and constant.
        */
        cbtPlane(const cbtVector3F& _normal = cbtVector3F::ZERO, cbtF32 _constant = 0.0f);

        /**
            \brief Constructs a new Plane which is a copy of given Plane.

            \param _x The Plane to copy.

            \return A new Plane which is a copy of _other.
        */
        cbtPlane(const cbtPlane& _other);

        /**
            \brief Destructor
        */
        ~cbtPlane();

        /**
            \brief Sets the normal and constant of this plane.

            \param _normal The value to set the normal to.
            \param _constant The value to set the constant to.
        */
        inline void Set(const cbtVector3F& _normal, cbtF32 _constant)
        {
            m_Normal = _normal;
            m_Constant = _constant;
        }

        /**
            \brief Sets the normal of this plane.

            \param _normal The value to set the normal to.
        */
        inline void SetNormal(const cbtVector3F& _normal)
        {
            m_Normal = _normal;
        }

        /**
            \brief Sets the constant of this plane.

            \param _constant The value to set the constant to.
        */
        inline void SetConstant(cbtF32 _constant)
        {
            m_Constant = _constant;
        }

        /**
            \brief Get the normal of this plane.

            \return The normal of this plane.
        */
        inline cbtVector3F GetNormal() const
        {
            return m_Normal;
        }

        /**
            \brief Get the constant of this plane.

            \return The constant of this plane.
        */
        inline cbtF32 GetConstant() const
        {
            return m_Constant;
        }

        /**
            \brief Normalize this plane.
        */
        void Normalize();

        /**
            \brief Returns a normalized version of this plane as a new Plane.

            \return A normalized version of this plane as a new Plane.
        */
        cbtPlane Normalized();

        /**
            \brief Get the distance from this plane to the given point.

            \param The point to find the distance.

            \return The distance from this plane to the given point.
        */
        cbtF32 DistanceToPoint(const cbtVector3F& _point);

        /**
            \brief Sets the values of this plane to be the same as another plane.

            \param _other The plane whose values to take.

            \return This plane after setting its values.
        */
        cbtPlane& operator=(const cbtPlane& _other)
        {
            m_Normal = _other.m_Normal;
            m_Constant = _other.m_Constant;
            return *this;
        }
    };

NS_CBT_END