// Include CBT
#include "cbtTransform.h"

NS_CBT_BEGIN

    CBT_DEFINE_FLAGS(cbtTransform, CBT_COMPONENT_FLAG_NONE);

// Constructor(s) & Destructor
    cbtTransform::cbtTransform()
            :m_Parent(nullptr), m_Child(nullptr), m_SiblingPrev(nullptr), m_SiblingNext(nullptr),
             m_LocalPosition(cbtVector3F::ZERO), m_LocalScale(1.0f, 1.0f, 1.0f),
             m_LocalRotation(cbtQuaternion::IDENTITY)
    {
    }

    cbtTransform::~cbtTransform()
    {
    }

// Scene Graph
    cbtBool cbtTransform::IsAncestor(const cbtTransform* _transform) const
    {
        if (_transform == nullptr)
        { return false; }

        const cbtTransform* ancestor = this;
        while (ancestor != nullptr)
        {
            if (_transform == ancestor)
            { return true; }
            ancestor = ancestor->m_Parent;
        }

        return false;
    }

    void cbtTransform::RemoveParent()
    {
        // Check if this node has a parent.
        if (!m_Parent)
        { return; }

        // Pass everything to the next sibling.
        // If we do not have a previous sibling, we are the first child.
        if (m_SiblingPrev)
        {
            m_SiblingPrev->m_SiblingNext = m_SiblingNext;
        }
        else
        {
            m_Parent->m_Child = m_SiblingNext;
        }

        if (m_SiblingNext)
        {
            m_SiblingNext->m_SiblingPrev = m_SiblingPrev;
        }

        m_Parent = m_SiblingNext = m_SiblingPrev = nullptr;
    }

    void cbtTransform::SetParent(cbtTransform* _parent)
    {
        // Check that _parent is not a descendant of this node.
        CBT_ASSERT(_parent && !IsAncestor(_parent));

        // Remove Current Parent
        RemoveParent();

        // Set our new parent and add ourselves to its children.
        m_Parent = _parent;

        // We become the first child.
        if (m_Parent->m_Child)
        {
            m_SiblingNext = m_Parent->m_Child;
            m_SiblingNext->m_SiblingPrev = this;
        }
        m_Parent->m_Child = this;
    }

// These functions will give the vector relative to the WORLD.
    cbtVector3F cbtTransform::GetGlobalPosition() const
    {
        cbtMatrix4F globalModelMatrix = GetGlobalModelMatrix();
        return cbtVector3F(globalModelMatrix[3][0], globalModelMatrix[3][1], globalModelMatrix[3][2]);
    }

    cbtVector3F cbtTransform::GetForward() const
    {
        cbtMatrix4F matrix = GetGlobalRotationMatrix() * cbtMatrixUtil::GetTranslationMatrix(cbtVector3F::FORWARDS);
        return cbtVector3F(matrix[3][0], matrix[3][1], matrix[3][2]);
    }

    cbtVector3F cbtTransform::GetUp() const
    {
        cbtMatrix4F matrix = GetGlobalRotationMatrix() * cbtMatrixUtil::GetTranslationMatrix(cbtVector3F::UP);
        return cbtVector3F(matrix[3][0], matrix[3][1], matrix[3][2]);
    }

    cbtVector3F cbtTransform::GetLeft() const
    {
        cbtMatrix4F matrix = GetGlobalRotationMatrix() * cbtMatrixUtil::GetTranslationMatrix(cbtVector3F::LEFT);
        return cbtVector3F(matrix[3][0], matrix[3][1], matrix[3][2]);
    }

NS_CBT_END