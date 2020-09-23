#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/Math/cbtMathUtil.h"
#include "Core/Math/cbtVector2.h"
#include "Core/Math/cbtVector3.h"

NS_CBT_BEGIN

struct cbtVertex
{
    // Variable(s)
    CBTVector3F m_Position;
    CBTVector3F m_Normal;
    CBTVector2F m_TexCoord;
    CBTVector3F m_Tangent;

    // Constructor(s) & Destructor
    cbtVertex() {}
    ~cbtVertex() {}

    // Operator Overload(s)
    cbtVertex& operator=(const cbtVertex& _rhs)
    {
        m_Position = _rhs.m_Position;
        m_Normal = _rhs.m_Normal;
        m_TexCoord = _rhs.m_TexCoord;
        m_Tangent = _rhs.m_Tangent;

        return *this;
    }

    cbtBool operator==(const cbtVertex& _rhs) const
    {
        return (m_Position == _rhs.m_Position) && (m_Normal == _rhs.m_Normal) && (m_TexCoord == _rhs.m_TexCoord) && (m_Tangent == _rhs.m_Tangent);
    }

    cbtBool operator!=(const cbtVertex& _rhs) const
    {
        return !(*this == _rhs);
    }
};

NS_CBT_END