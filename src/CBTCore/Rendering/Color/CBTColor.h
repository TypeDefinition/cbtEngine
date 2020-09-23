#pragma once
// Include CBT
#include "cbtMacros.h"
#include "Core/Math/cbtMathUtil.h"

NS_CBT_BEGIN

class cbtColor
{
public:
    // Variable(s)
    cbtF32 m_R, m_G, m_B, m_A;

    // Constructor(s) & Destructor
    cbtColor(cbtF32 _r = 1.0f, cbtF32 _g = 1.0f, cbtF32 _b = 1.0f, cbtF32 _a = 1.0f) { Set(_r, _g, _b, _a); }
    cbtColor(const cbtColor& _other) { Set(_other.m_R, _other.m_G, _other.m_B, _other.m_A); }
    ~cbtColor() {}

    // Interface Function(s)
    inline void Set(cbtF32 _r, cbtF32 _g, cbtF32 _b, cbtF32 _a)
    {
        m_R = cbtMathUtil::Clamp<cbtF32>(_r, 0.0f, 1.0f);
        m_G = cbtMathUtil::Clamp<cbtF32>(_g, 0.0f, 1.0f);
        m_B = cbtMathUtil::Clamp<cbtF32>(_b, 0.0f, 1.0f);
        m_A = cbtMathUtil::Clamp<cbtF32>(_a, 0.0f, 1.0f);
    }
    inline cbtF32 GetR() const { return m_R; }
    inline cbtF32 GetG() const { return m_G; }
    inline cbtF32 GetB() const { return m_B; }
    inline cbtF32 GetA() const { return m_A; }

    // Operator Overload(s)
    inline cbtBool operator==(const cbtColor& _rhs)
    {
        return (m_R == _rhs.m_R) && (m_G == _rhs.m_G) && (m_B == _rhs.m_B) && (m_A == _rhs.m_A);
    }

    inline cbtBool operator!=(const cbtColor& _rhs)
    {
        return !(*this == _rhs);
    }

    inline cbtColor& operator=(const cbtColor& _rhs)
    {
        m_R = _rhs.m_R; m_G = _rhs.m_G; m_B = _rhs.m_B; m_A = _rhs.m_A;
        return *this;
    }

    inline cbtColor operator+(const cbtColor& _rhs)
    {
        return cbtColor(m_R + _rhs.m_R, m_G + _rhs.m_G, m_B + _rhs.m_B, m_A + _rhs.m_A);
    }
    inline cbtColor operator+=(const cbtColor& _rhs)
    {
        *this = (*this + _rhs);
        return *this;
    }

    inline cbtColor operator-(const cbtColor& _rhs)
    {
        return cbtColor(m_R - _rhs.m_R, m_G - _rhs.m_G, m_B - _rhs.m_B, m_A - _rhs.m_A);
    }
    inline cbtColor operator-=(const cbtColor& _rhs)
    {
        *this = (*this - _rhs);
        return *this;
    }

    inline cbtColor operator*(const cbtColor& _rhs)
    {
        return cbtColor(m_R * _rhs.m_R, m_G * _rhs.m_G, m_B * _rhs.m_B, m_A * _rhs.m_A);
    }
    inline cbtColor operator*=(const cbtColor& _rhs)
    {
        *this = (*this * _rhs);
        return *this;
    }

    // Pre-Defined Color(s)
    static const cbtColor WHITE;
    static const cbtColor BLACK;
    static const cbtColor GREY;

    static const cbtColor RED;
    static const cbtColor GREEN;
    static const cbtColor BLUE;

    static const cbtColor MAGENTA;
    static const cbtColor YELLOW;
    static const cbtColor CYAN;
};

NS_CBT_END