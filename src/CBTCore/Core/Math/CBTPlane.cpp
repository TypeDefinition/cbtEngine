// Include CBT
#include "cbtPlane.h"

NS_CBT_BEGIN

cbtPlane::cbtPlane(const CBTVector3F& _normal, cbtF32 _constant)
    : m_Normal(_normal)
    , m_Constant(_constant)
{
}

cbtPlane::cbtPlane(const cbtPlane& _other)
    : m_Normal(_other.m_Normal)
    , m_Constant(_other.m_Constant)
{
}

cbtPlane::~cbtPlane()
{
}

void cbtPlane::Normalize()
{
    cbtF32 normalLength = Length(m_Normal);
    m_Constant /= normalLength;
    m_Normal *= (1.0f/normalLength);
}

cbtPlane cbtPlane::Normalized()
{
    cbtF32 normalLength = Length(m_Normal);
    return cbtPlane(m_Normal * (1.0f/normalLength), m_Constant / normalLength);
}

cbtF32 cbtPlane::DistanceToPoint(const CBTVector3F& _point)
{
    return (Dot(_point, m_Normal) + m_Constant) / Length(m_Normal);
}

NS_CBT_END