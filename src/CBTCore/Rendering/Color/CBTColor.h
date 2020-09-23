#pragma once
// Include CBT
#include "CBTMacros.h"
#include "Core/Math/CBTMathUtil.h"

NS_CBT_BEGIN

class CBTColor
{
public:
    // Variable(s)
    cbtF32 m_R, m_G, m_B, m_A;

    // Constructor(s) & Destructor
    CBTColor(cbtF32 _r = 1.0f, cbtF32 _g = 1.0f, cbtF32 _b = 1.0f, cbtF32 _a = 1.0f) { Set(_r, _g, _b, _a); }
    CBTColor(const CBTColor& _other) { Set(_other.m_R, _other.m_G, _other.m_B, _other.m_A); }
    ~CBTColor() {}

    // Interface Function(s)
    inline void Set(cbtF32 _r, cbtF32 _g, cbtF32 _b, cbtF32 _a)
    {
        m_R = CBTMathUtil::Clamp<cbtF32>(_r, 0.0f, 1.0f);
        m_G = CBTMathUtil::Clamp<cbtF32>(_g, 0.0f, 1.0f);
        m_B = CBTMathUtil::Clamp<cbtF32>(_b, 0.0f, 1.0f);
        m_A = CBTMathUtil::Clamp<cbtF32>(_a, 0.0f, 1.0f);
    }
    inline cbtF32 GetR() const { return m_R; }
    inline cbtF32 GetG() const { return m_G; }
    inline cbtF32 GetB() const { return m_B; }
    inline cbtF32 GetA() const { return m_A; }

    // Operator Overload(s)
    inline cbtBool operator==(const CBTColor& _rhs)
    {
        return (m_R == _rhs.m_R) && (m_G == _rhs.m_G) && (m_B == _rhs.m_B) && (m_A == _rhs.m_A);
    }

    inline cbtBool operator!=(const CBTColor& _rhs)
    {
        return !(*this == _rhs);
    }

    inline CBTColor& operator=(const CBTColor& _rhs)
    {
        m_R = _rhs.m_R; m_G = _rhs.m_G; m_B = _rhs.m_B; m_A = _rhs.m_A;
        return *this;
    }

    inline CBTColor operator+(const CBTColor& _rhs)
    {
        return CBTColor(m_R + _rhs.m_R, m_G + _rhs.m_G, m_B + _rhs.m_B, m_A + _rhs.m_A);
    }
    inline CBTColor operator+=(const CBTColor& _rhs)
    {
        *this = (*this + _rhs);
        return *this;
    }

    inline CBTColor operator-(const CBTColor& _rhs)
    {
        return CBTColor(m_R - _rhs.m_R, m_G - _rhs.m_G, m_B - _rhs.m_B, m_A - _rhs.m_A);
    }
    inline CBTColor operator-=(const CBTColor& _rhs)
    {
        *this = (*this - _rhs);
        return *this;
    }

    inline CBTColor operator*(const CBTColor& _rhs)
    {
        return CBTColor(m_R * _rhs.m_R, m_G * _rhs.m_G, m_B * _rhs.m_B, m_A * _rhs.m_A);
    }
    inline CBTColor operator*=(const CBTColor& _rhs)
    {
        *this = (*this * _rhs);
        return *this;
    }

    // Pre-Defined Color(s)
    static const CBTColor WHITE;
    static const CBTColor BLACK;
    static const CBTColor GREY;

    static const CBTColor RED;
    static const CBTColor GREEN;
    static const CBTColor BLUE;

    static const CBTColor MAGENTA;
    static const CBTColor YELLOW;
    static const CBTColor CYAN;
};

NS_CBT_END