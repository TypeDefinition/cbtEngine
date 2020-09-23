// Include CBT
#include "CBTCamera.h"
#include "Debug/CBTDebug.h"

NS_CBT_BEGIN

CBT_DEFINE_FLAGS(CBTCamera, CBT_COMPONENT_FLAG_NONE);

// Interface Function(s)
void CBTCamera::SetProjectionMode(CBTProjectionMode _mode)
{
    m_ProjectionMode = _mode;
    SetNearPlane(m_NearPlane);
    SetFarPlane(m_FarPlane);
}

void CBTCamera::SetNearPlane(cbtF32 _value)
{
    switch (m_ProjectionMode)
    {
    case CBTProjectionMode::PERSPECTIVE:
        m_NearPlane = CBTMathUtil::Max<cbtF32>(0.01f, _value);
        break;
    case CBTProjectionMode::ORTHOGRAPHIC:
        m_NearPlane = _value;
        break;
    }
    SetFarPlane(m_FarPlane);
}

void CBTCamera::SetFarPlane(cbtF32 _value)
{
    m_FarPlane = CBTMathUtil::Max<cbtF32>(m_NearPlane + 0.01f, _value);
}

CBTMatrix4F CBTCamera::GetProjectionMatrix() const
{
    switch (GetProjectionMode())
    {
    case CBTProjectionMode::ORTHOGRAPHIC:
        return CBTMatrixUtil::GetOrthographicMatrix(GetAspectRatio(), GetOrthoSize(), GetNearPlane(), GetFarPlane());
    case CBTProjectionMode::PERSPECTIVE:
        return CBTMatrixUtil::GetPerspectiveMatrix(GetAspectRatio(), GetFOV(), GetNearPlane(), GetFarPlane());
    default:
        CBT_ASSERT(false);
        return CBTMatrixUtil::GetIdentityMatrix<cbtF32, 4>();
    }
}

void CBTCamera::SetPostProcessShaders(std::initializer_list<CBTShaderProgram*> _shaders)
{
    std::vector<CBTShaderProgram*> shaders(_shaders);
    for (cbtU32 i = 0; i < shaders.size(); ++i) { shaders[i]->Retain(); }
    for (cbtU32 i = 0; i < m_PostProcessShaders.size(); ++i) { m_PostProcessShaders[i]->AutoRelease(); }
    m_PostProcessShaders.swap(shaders);
}

NS_CBT_END