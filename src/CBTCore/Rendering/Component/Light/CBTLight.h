#pragma once

// Include CBT
#include "Game/Component/cbtComponent.h"
#include "Core/Math/cbtMathUtil.h"
#include "Rendering/Color/cbtColor.h"

NS_CBT_BEGIN

enum cbtLightMode
{
    CBT_LIGHT_POINT = 0,
    CBT_LIGHT_SPOT,
    CBT_LIGHT_DIRECTIONAL,
};

class cbtLight : public cbtComponent
{
private:
    cbtLightMode m_Mode = cbtLightMode::CBT_LIGHT_POINT;
    cbtColor m_Color = cbtColor::WHITE;
    cbtF32 m_Power = 10.0f;

    cbtF32 m_AttenuationConstant = 1.0f;
    cbtF32 m_AttenuationLinear = 1.0f;
    cbtF32 m_AttenuationQuadratic = 1.0f;

    cbtF32 m_SpotlightInnerAngle = 10.0f;
    cbtF32 m_SpotlightOuterAngle = 30.0f;

    static cbtBool s_LightingEnabled;

public:
    // Constructor(s) & Destructor
    cbtLight() {}
    virtual ~cbtLight() {}

    static cbtBool IsLightingEnabled() { return s_LightingEnabled; }

    // Interface Function(s)
    inline cbtLightMode GetMode() const { return m_Mode; }
    inline void SetMode(cbtLightMode _type) { m_Mode = _type; }

    inline cbtColor GetColor() const { return m_Color; }
    inline void SetColor(cbtColor _color) { m_Color = _color; }

    inline cbtF32 GetPower() const { return m_Power; }
    inline void SetPower(cbtF32 _power) { m_Power = cbtMathUtil::Max<cbtF32>(0.0f, _power); }

    inline cbtF32 GetAttenuationConstant() const { return m_AttenuationConstant; }
    inline void SetAttenuationConstant(cbtF32 _attenuation) { m_AttenuationConstant = cbtMathUtil::Max<cbtF32>(_attenuation, 0.0f); }

    inline cbtF32 GetAttenuationLinear() const { return m_AttenuationLinear; }
    inline void SetAttenuationLinear(cbtF32 _attenuation) { m_AttenuationLinear = cbtMathUtil::Max<cbtF32>(_attenuation, 0.0f); }

    inline cbtF32 GetAttenuationQuadratic() const { return m_AttenuationQuadratic; }
    inline void SetAttenuationQuadratic(cbtF32 _attenuation) { m_AttenuationQuadratic = cbtMathUtil::Max<cbtF32>(_attenuation, 0.0f); }

    inline cbtF32 GetSpotlightInnerConsine() const { return std::cos(cbtMathUtil::DEG2RAD * GetSpotlightInnerAngle()); }
    inline cbtF32 GetSpotlightInnerAngle() const { return cbtMathUtil::Min<cbtF32>(m_SpotlightOuterAngle, m_SpotlightInnerAngle); }
    inline void SetSpotlightInnerAngle(cbtF32 _angle) { m_SpotlightInnerAngle = cbtMathUtil::Clamp<cbtF32>(_angle, 1.0f, 89.0f); }

    inline cbtF32 GetSpotlightOuterConsine() const { return std::cos(cbtMathUtil::DEG2RAD * GetSpotlightOuterAngle()); }
    inline cbtF32 GetSpotlightOuterAngle() const { return m_SpotlightOuterAngle; }
    inline void SetSpotlightOuterAngle(cbtF32 _angle) { m_SpotlightOuterAngle = cbtMathUtil::Clamp<cbtF32>(_angle, 1.0f, 89.0f); }
};

NS_CBT_END