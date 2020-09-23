// Include CBT
#include "CBTPlane.h"

NS_CBT_BEGIN

CBTPlane::CBTPlane(const CBTVector3F& _normal, cbtF32 _constant)
    : m_Normal(_normal)
    , m_Constant(_constant)
{
}

CBTPlane::CBTPlane(const CBTPlane& _other)
    : m_Normal(_other.m_Normal)
    , m_Constant(_other.m_Constant)
{
}

CBTPlane::~CBTPlane()
{
}

void CBTPlane::Normalize()
{
    cbtF32 normalLength = Length(m_Normal);
    m_Constant /= normalLength;
    m_Normal *= (1.0f/normalLength);
}

CBTPlane CBTPlane::Normalized()
{
    cbtF32 normalLength = Length(m_Normal);
    return CBTPlane(m_Normal * (1.0f/normalLength), m_Constant / normalLength);
}

cbtF32 CBTPlane::DistanceToPoint(const CBTVector3F& _point)
{
    return (Dot(_point, m_Normal) + m_Constant) / Length(m_Normal);
}

NS_CBT_END