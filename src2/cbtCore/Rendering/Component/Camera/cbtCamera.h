#pragma once

// Include CBT
#include "Game/Component/cbtComponent.h"
#include "Core/Math/cbtMatrixUtil.h"
#include "Core/Math/cbtMathUtil.h"
#include "Rendering/Shader/cbtShaderProgram.h"
#include "Rendering/Texture/cbtTexture.h"
#include "Rendering/Mesh/cbtMesh.h"

NS_CBT_BEGIN

struct cbtViewport
{
public:
    // (0, 0) represents the bottom of the screen and (1, 1) represents the top of the screen.
    cbtF32 m_BottomX, m_BottomY;
    cbtF32 m_TopX, m_TopY;

    cbtViewport(cbtF32 _bottomX = 0.0f, cbtF32 _bottomY = 0.0f, cbtF32 _topX = 1.0f, cbtF32 _topY = 1.0f)
        : m_BottomX(_bottomX)
        , m_BottomY(_bottomY)
        , m_TopX(_topX)
        , m_TopY(_topY)
    {}
    ~cbtViewport() {}
};

/// Camera Projection Mode
enum class cbtProjectionMode
{
    PERSPECTIVE,
    ORTHOGRAPHIC,
};

class cbtCamera : public cbtComponent
{
private:
    /// Projection Mode
    cbtProjectionMode m_ProjectionMode = cbtProjectionMode::PERSPECTIVE;
    /// Near Plane
    cbtF32 m_NearPlane = 0.3f;
    /// Far Plane
    cbtF32 m_FarPlane = 500.0f;
    /// Aspect Ratio
    cbtF32 m_AspectRatio = 16.0f/9.0f;
    /// Camera Depth
    cbtU8 m_Depth = 0;
    /// Perspective Field of View
    cbtF32 m_FOV = 45.0F;
    /// Orthographic Size
    cbtF32 m_OrthoSize = 5.0F;
    /// Viewport
    cbtViewport m_ViewPort;

    /// Deferred Lighting Shader
    cbtRef<cbtShaderProgram> m_LightingShader;
    /// Post Processing Shaders
    std::vector<cbtShaderProgram*> m_PostProcessShaders;

    /// Skybox Color
    cbtColor m_SkyboxColor = cbtColor::WHITE;
    /// Skybox Texture
    cbtRef<cbtTexture> m_SkyboxTexture;
    /// Skybox Shader
    cbtRef<cbtShaderProgram> m_SkyboxShader;

public:
    // Constructor(s) & Destructor
    cbtCamera() {}
    virtual ~cbtCamera() { for (cbtU32 i = 0; i < m_PostProcessShaders.size(); ++i) { m_PostProcessShaders[i]->AutoRelease(); } }

    // Interface Function(s)
    inline cbtProjectionMode GetProjectionMode() const { return m_ProjectionMode; }
    void SetProjectionMode(cbtProjectionMode _mode);

    inline cbtF32 GetNearPlane() const { return m_NearPlane; }
    void SetNearPlane(cbtF32 _value);
    inline cbtF32 GetFarPlane() const { return m_FarPlane; }
    void SetFarPlane(cbtF32 _value);
    inline cbtF32 GetAspectRatio() const { return m_AspectRatio; }
    inline void SetAspectRatio(cbtF32 _aspectRatio) { m_AspectRatio = _aspectRatio; }

    inline cbtU8 GetDepth() const { return m_Depth; }
    inline void SetDepth(cbtU8 _depth) { m_Depth = cbtMathUtil::Min<cbtU8>(_depth, 15); }

    cbtMatrix4F GetProjectionMatrix() const;

    // Perspective
    inline cbtF32 GetFOV() const { return m_FOV; }
    inline void SetFOV(cbtF32 _fov) { m_FOV = cbtMathUtil::Clamp<cbtF32>(_fov, 1.0f, 89.0f); }

    // Orthographic
    inline cbtF32 GetOrthoSize() const { return m_OrthoSize; }
    inline void SetOrthoSize(cbtF32 _orthoSize) { m_OrthoSize = _orthoSize; }

    // Viewport
    inline const cbtViewport& GetViewport() const { return m_ViewPort; }
    inline void SetViewport(const cbtViewport& _viewport) { m_ViewPort = _viewport; }

    // Deferred Lighting Shader
    cbtShaderProgram* GetLightingShader() { return m_LightingShader.GetRawPointer(); }
    const cbtShaderProgram* GetLightingShader() const { return m_LightingShader.GetRawPointer(); }
    void SetLightingShader(cbtShaderProgram* _shader) { m_LightingShader = _shader; }

    // Post Processing Shaders
    void SetPostProcessShaders(std::initializer_list<cbtShaderProgram*> _shaders);
    cbtShaderProgram** GetPostProcessShaders() { return m_PostProcessShaders.empty() ? nullptr : &m_PostProcessShaders[0]; }
    cbtU32 GetPostProcessShaderCount() const { return (cbtU32)m_PostProcessShaders.size(); }

    // Skybox
    inline const cbtColor& GetSkyboxColor() const { return m_SkyboxColor; }
    inline void SetSkyboxColor(const cbtColor& _color) { m_SkyboxColor = _color; }

    inline const cbtTexture* GetSkyboxTexture() const { return m_SkyboxTexture.GetRawPointer(); }
    inline cbtTexture* GetSkyboxTexture() { return m_SkyboxTexture.GetRawPointer(); }
    inline void SetSkyboxTexture(cbtTexture* _texture) { m_SkyboxTexture = _texture; }

    cbtShaderProgram* GetSkyboxShader() { return m_SkyboxShader.GetRawPointer(); }
    const cbtShaderProgram* GetSkyboxShader() const { return m_SkyboxShader.GetRawPointer(); }
    void SetSkyboxShader(cbtShaderProgram* _shader) { m_SkyboxShader = _shader; }
};

NS_CBT_END