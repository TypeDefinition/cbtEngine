#pragma once

// Include CBT
#include "Game/Component/CBTComponent.h"
#include "Core/Math/CBTMathUtil.h"
#include "Rendering/Color/CBTColor.h"

NS_CBT_BEGIN

enum CBTLightMode
{
    CBT_LIGHT_POINT = 0,
    CBT_LIGHT_SPOT,
    CBT_LIGHT_DIRECTIONAL,
};

class CBTLight : public CBTComponent
{
private:
    CBTLightMode m_Mode = CBTLightMode::CBT_LIGHT_POINT;
    CBTColor m_Color = CBTColor::WHITE;
    cbtF32 m_Power = 10.0f;

    cbtF32 m_AttenuationConstant = 1.0f;
    cbtF32 m_AttenuationLinear = 1.0f;
    cbtF32 m_AttenuationQuadratic = 1.0f;

    cbtF32 m_SpotlightInnerAngle = 10.0f;
    cbtF32 m_SpotlightOuterAngle = 30.0f;

    static cbtBool s_LightingEnabled;

public:
    // Constructor(s) & Destructor
    CBTLight() {}
    virtual ~CBTLight() {}

    static cbtBool IsLightingEnabled() { return s_LightingEnabled; }

    // Interface Function(s)
    inline CBTLightMode GetMode() const { return m_Mode; }
    inline void SetMode(CBTLightMode _type) { m_Mode = _type; }

    inline CBTColor GetColor() const { return m_Color; }
    inline void SetColor(CBTColor _color) { m_Color = _color; }

    inline cbtF32 GetPower() const { return m_Power; }
    inline void SetPower(cbtF32 _power) { m_Power = CBTMathUtil::Max<cbtF32>(0.0f, _power); }

    inline cbtF32 GetAttenuationConstant() const { return m_AttenuationConstant; }
    inline void SetAttenuationConstant(cbtF32 _attenuation) { m_AttenuationConstant = CBTMathUtil::Max<cbtF32>(_attenuation, 0.0f); }

    inline cbtF32 GetAttenuationLinear() const { return m_AttenuationLinear; }
    inline void SetAttenuationLinear(cbtF32 _attenuation) { m_AttenuationLinear = CBTMathUtil::Max<cbtF32>(_attenuation, 0.0f); }

    inline cbtF32 GetAttenuationQuadratic() const { return m_AttenuationQuadratic; }
    inline void SetAttenuationQuadratic(cbtF32 _attenuation) { m_AttenuationQuadratic = CBTMathUtil::Max<cbtF32>(_attenuation, 0.0f); }

    inline cbtF32 GetSpotlightInnerConsine() const { return std::cos(CBTMathUtil::DEG2RAD * GetSpotlightInnerAngle()); }
    inline cbtF32 GetSpotlightInnerAngle() const { return CBTMathUtil::Min<cbtF32>(m_SpotlightOuterAngle, m_SpotlightInnerAngle); }
    inline void SetSpotlightInnerAngle(cbtF32 _angle) { m_SpotlightInnerAngle = CBTMathUtil::Clamp<cbtF32>(_angle, 1.0f, 89.0f); }

    inline cbtF32 GetSpotlightOuterConsine() const { return std::cos(CBTMathUtil::DEG2RAD * GetSpotlightOuterAngle()); }
    inline cbtF32 GetSpotlightOuterAngle() const { return m_SpotlightOuterAngle; }
    inline void SetSpotlightOuterAngle(cbtF32 _angle) { m_SpotlightOuterAngle = CBTMathUtil::Clamp<cbtF32>(_angle, 1.0f, 89.0f); }
};

NS_CBT_END