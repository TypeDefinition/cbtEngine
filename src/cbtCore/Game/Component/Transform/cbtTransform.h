#pragma once

// Include CBT
#include "Core/Math/cbtVector3.h"
#include "Core/Math/cbtQuaternion.h"
#include "Game/Component/cbtComponent.h"

// Include STD
#include <list>

NS_CBT_BEGIN

    class cbtTransform : public cbtComponent
    {
    private:
        // Scene Graph
        cbtTransform* m_Parent;
        cbtTransform* m_Child;
        cbtTransform* m_SiblingPrev;
        cbtTransform* m_SiblingNext;

        // Local Data
        cbtVector3F m_LocalPosition;
        cbtVector3F m_LocalScale;
        cbtQuaternion m_LocalRotation;

    public:
        cbtTransform(); ///< Constructor(s)
        virtual ~cbtTransform(); ///< Protected Destructor. Use Ref::Release instead.

        // Hierarchy
        cbtTransform* GetParent()
        {
            return m_Parent;
        }

        const cbtTransform* GetParent() const
        {
            return m_Parent;
        }

        cbtTransform* GetSiblingPrev()
        {
            return m_SiblingPrev;
        }

        const cbtTransform* GetSiblingPrev() const
        {
            return m_SiblingPrev;
        }

        cbtTransform* GetSiblingNext()
        {
            return m_SiblingNext;
        }

        const cbtTransform* GetSiblingNext() const
        {
            return m_SiblingNext;
        }

        cbtTransform* GetChild()
        {
            return m_Child;
        }

        const cbtTransform* GetChild() const
        {
            return m_Child;
        }

        cbtBool IsAncestor(const cbtTransform* _transform) const;

        void RemoveParent();

        void SetParent(cbtTransform* _parent);

        // Local Translation
        inline const cbtVector3F& GetLocalPosition() const
        {
            return m_LocalPosition;
        }

        void SetLocalPosition(const cbtVector3F& _position)
        {
            m_LocalPosition = _position;
        }

        void LocalTranslate(const cbtVector3F& _translation)
        {
            m_LocalPosition += _translation;
        }

        // Rotation
        inline const cbtVector3F& GetLocalScale() const
        {
            return m_LocalScale;
        }

        inline const cbtQuaternion& GetLocalRotation() const
        {
            return m_LocalRotation;
        }

        void SetLocalRotation(cbtF32 _angle, const cbtVector3F& _rotationAxis)
        {
            m_LocalRotation.SetToRotation(_angle, _rotationAxis);
        }

        void LocalRotate(cbtF32 _angle, const cbtVector3F& _rotationAxis)
        {
            m_LocalRotation = (cbtQuaternion(_angle, _rotationAxis) * m_LocalRotation).Normalized();
        }

        // LocalScale
        void SetLocalScale(const cbtVector3F& _scale)
        {
            m_LocalScale = _scale;
        }

        void LocalScale(const cbtVector3F& _scale)
        {
            m_LocalScale *= _scale;
        }

        void LocalScale(cbtF32 _scale)
        {
            m_LocalScale *= _scale;
        }

        /*
            These 3 functions only gives the matrices relative to the PARENT.
            The chances of needing this data very often is low, so we will not store it as a variable to be updated every time
            any of the translate, scale or rotate function is called, which might result in even more calculations.
            We also do not want to update it with the m_IsDirty flag as we are trying to keep getting local transformations
            be able to be done on a const Transform.
        */
        cbtMatrix4F GetLocalTranslationMatrix() const
        {
            return cbtMatrixUtil::GetTranslationMatrix(m_LocalPosition);
        }

        cbtMatrix4F GetLocalRotationMatrix() const
        {
            return m_LocalRotation.ToRotationMatrix();
        }

        cbtMatrix4F GetLocalScaleMatrix() const
        {
            return cbtMatrixUtil::GetScaleMatrix(m_LocalScale);
        }

        cbtMatrix4F GetLocalModelMatrix() const
        {
            return GetLocalTranslationMatrix() * GetLocalRotationMatrix() * GetLocalScaleMatrix();
        }

        // Any rotation is done relative to the object's parent orientation.
        cbtMatrix4F GetGlobalRotationMatrix() const
        {
            return m_Parent ? GetLocalRotationMatrix() * m_Parent->GetGlobalRotationMatrix() : GetLocalRotationMatrix();
        }

        // This function will give the model matrix relative to the WORLD.
        cbtMatrix4F GetGlobalModelMatrix() const
        {
            return m_Parent ? GetLocalModelMatrix() * m_Parent->GetGlobalModelMatrix() : GetLocalModelMatrix();
        }

        // These functions will give the vector relative to the WORLD.
        cbtVector3F GetGlobalPosition() const;

        cbtVector3F GetForward() const;

        cbtVector3F GetBackwards() const
        {
            return -GetForward();
        }

        cbtVector3F GetUp() const;

        cbtVector3F GetDown() const
        {
            return -GetUp();
        }

        cbtVector3F GetLeft() const;

        cbtVector3F GetRight() const
        {
            return -GetLeft();
        }
    };

NS_CBT_END