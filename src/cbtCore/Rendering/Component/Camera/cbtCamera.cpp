// Include CBT
#include "cbtCamera.h"
#include "Debug/cbtDebug.h"

NS_CBT_BEGIN

    CBT_DEFINE_FLAGS(cbtCamera, CBT_COMPONENT_FLAG_NONE);

// Interface Function(s)
    void cbtCamera::SetProjectionMode(cbtProjectionMode _mode)
    {
        m_ProjectionMode = _mode;
        SetNearPlane(m_NearPlane);
        SetFarPlane(m_FarPlane);
    }

    void cbtCamera::SetNearPlane(cbtF32 _value)
    {
        switch (m_ProjectionMode)
        {
        case cbtProjectionMode::PERSPECTIVE:
            m_NearPlane = cbtMathUtil::Max<cbtF32>(0.01f, _value);
            break;
        case cbtProjectionMode::ORTHOGRAPHIC:
            m_NearPlane = _value;
            break;
        }
        SetFarPlane(m_FarPlane);
    }

    void cbtCamera::SetFarPlane(cbtF32 _value)
    {
        m_FarPlane = cbtMathUtil::Max<cbtF32>(m_NearPlane + 0.01f, _value);
    }

    cbtMatrix4F cbtCamera::GetProjectionMatrix() const
    {
        switch (GetProjectionMode())
        {
        case cbtProjectionMode::ORTHOGRAPHIC:
            return cbtMatrixUtil::GetOrthographicMatrix(GetAspectRatio(), GetOrthoSize(), GetNearPlane(),
                    GetFarPlane());
        case cbtProjectionMode::PERSPECTIVE:
            return cbtMatrixUtil::GetPerspectiveMatrix(GetAspectRatio(), GetFOV(), GetNearPlane(), GetFarPlane());
        default:
            CBT_ASSERT(false);
            return cbtMatrixUtil::GetIdentityMatrix<cbtF32, 4>();
        }
    }

    void cbtCamera::SetPostProcessShaders(std::initializer_list<cbtShaderProgram*> _shaders)
    {
        std::vector<cbtShaderProgram*> shaders(_shaders);
        for (cbtU32 i = 0; i < shaders.size(); ++i)
        { shaders[i]->Retain(); }
        for (cbtU32 i = 0; i < m_PostProcessShaders.size(); ++i)
        { m_PostProcessShaders[i]->AutoRelease(); }
        m_PostProcessShaders.swap(shaders);
    }

NS_CBT_END