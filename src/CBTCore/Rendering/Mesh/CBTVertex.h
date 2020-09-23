#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/Math/CBTMathUtil.h"
#include "Core/Math/CBTVector2.h"
#include "Core/Math/CBTVector3.h"

NS_CBT_BEGIN

struct CBTVertex
{
    // Variable(s)
    CBTVector3F m_Position;
    CBTVector3F m_Normal;
    CBTVector2F m_TexCoord;
    CBTVector3F m_Tangent;

    // Constructor(s) & Destructor
    CBTVertex() {}
    ~CBTVertex() {}

    // Operator Overload(s)
    CBTVertex& operator=(const CBTVertex& _rhs)
    {
        m_Position = _rhs.m_Position;
        m_Normal = _rhs.m_Normal;
        m_TexCoord = _rhs.m_TexCoord;
        m_Tangent = _rhs.m_Tangent;

        return *this;
    }

    cbtBool operator==(const CBTVertex& _rhs) const
    {
        return (m_Position == _rhs.m_Position) && (m_Normal == _rhs.m_Normal) && (m_TexCoord == _rhs.m_TexCoord) && (m_Tangent == _rhs.m_Tangent);
    }

    cbtBool operator!=(const CBTVertex& _rhs) const
    {
        return !(*this == _rhs);
    }
};

NS_CBT_END