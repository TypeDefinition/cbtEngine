#pragma once

// Include CBT
#include "Core/Math/CBTVector3.h"
#include "Core/Math/CBTQuaternion.h"
#include "Game/Component/CBTComponent.h"

// Include STD
#include <list>

NS_CBT_BEGIN

class CBTTransform : public CBTComponent
{
private:
    // Scene Graph
    CBTTransform* m_Parent;
    CBTTransform* m_Child;
    CBTTransform* m_SiblingPrev;
    CBTTransform* m_SiblingNext;

    // Local Data
    CBTVector3F m_LocalPosition;
    CBTVector3F m_LocalScale;
    CBTQuaternion m_LocalRotation;

public:
    CBTTransform(); ///< Constructor(s)
    virtual ~CBTTransform(); ///< Protected Destructor. Use Ref::Release instead.

    // Hierarchy
    CBTTransform* GetParent() { return m_Parent; }
    const CBTTransform* GetParent() const { return m_Parent; }
    CBTTransform* GetSiblingPrev() { return m_SiblingPrev; }
    const CBTTransform* GetSiblingPrev() const { return m_SiblingPrev; }
    CBTTransform* GetSiblingNext() { return m_SiblingNext; }
    const CBTTransform* GetSiblingNext() const { return m_SiblingNext; }
    CBTTransform* GetChild() { return m_Child; }
    const CBTTransform* GetChild() const { return m_Child; }

    cbtBool IsAncestor(const CBTTransform* _transform) const;
    void RemoveParent();
    void SetParent(CBTTransform* _parent);

    // Local Translation
    inline const CBTVector3F& GetLocalPosition() const { return m_LocalPosition; }
    void SetLocalPosition(const CBTVector3F& _position) { m_LocalPosition = _position; }
    void LocalTranslate(const CBTVector3F& _translation) { m_LocalPosition += _translation; }

    // Rotation
    inline const CBTVector3F& GetLocalScale() const { return m_LocalScale; }
    inline const CBTQuaternion& GetLocalRotation() const { return m_LocalRotation; }
    void SetLocalRotation(cbtF32 _angle, const CBTVector3F& _rotationAxis) { m_LocalRotation.SetToRotation(_angle, _rotationAxis); }
    void LocalRotate(cbtF32 _angle, const CBTVector3F& _rotationAxis) { m_LocalRotation = (CBTQuaternion(_angle, _rotationAxis) * m_LocalRotation).Normalized(); }

    // LocalScale
    void SetLocalScale(const CBTVector3F& _scale) { m_LocalScale = _scale; }
    void LocalScale(const CBTVector3F& _scale) { m_LocalScale *= _scale; }
    void LocalScale(cbtF32 _scale) { m_LocalScale *= _scale; }

    /*
        These 3 functions only gives the matrices relative to the PARENT.
        The chances of needing this data very often is low, so we will not store it as a variable to be updated every time
        any of the translate, scale or rotate function is called, which might result in even more calculations.
        We also do not want to update it with the m_IsDirty flag as we are trying to keep getting local transformations
        be able to be done on a const Transform.
    */
    CBTMatrix4F GetLocalTranslationMatrix() const { return CBTMatrixUtil::GetTranslationMatrix(m_LocalPosition); }
    CBTMatrix4F GetLocalRotationMatrix() const { return m_LocalRotation.ToRotationMatrix(); }
    CBTMatrix4F GetLocalScaleMatrix() const { return CBTMatrixUtil::GetScaleMatrix(m_LocalScale); }
    CBTMatrix4F GetLocalModelMatrix() const { return GetLocalTranslationMatrix() * GetLocalRotationMatrix() * GetLocalScaleMatrix(); }

    // Any rotation is done relative to the object's parent orientation.
    CBTMatrix4F GetGlobalRotationMatrix() const { return m_Parent ? GetLocalRotationMatrix() * m_Parent->GetGlobalRotationMatrix() : GetLocalRotationMatrix(); }
    // This function will give the model matrix relative to the WORLD.
    CBTMatrix4F GetGlobalModelMatrix() const { return m_Parent ? GetLocalModelMatrix() * m_Parent->GetGlobalModelMatrix() : GetLocalModelMatrix(); }

    // These functions will give the vector relative to the WORLD.
    CBTVector3F GetGlobalPosition() const;
    CBTVector3F GetForward() const;
    CBTVector3F GetBackwards() const { return -GetForward(); }
    CBTVector3F GetUp() const;
    CBTVector3F GetDown() const { return -GetUp(); }
    CBTVector3F GetLeft() const;
    CBTVector3F GetRight() const { return -GetLeft(); }
};

NS_CBT_END