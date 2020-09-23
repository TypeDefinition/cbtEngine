#pragma once

// Include CBT
#include "Game/Component/CBTComponent.h"
#include "Core/Math/CBTMatrixUtil.h"
#include "Core/Math/CBTMathUtil.h"
#include "Rendering/Shader/CBTShaderProgram.h"
#include "Rendering/Texture/CBTTexture.h"
#include "Rendering/Mesh/CBTMesh.h"

NS_CBT_BEGIN

struct CBTViewport
{
public:
    // (0, 0) represents the bottom of the screen and (1, 1) represents the top of the screen.
    cbtF32 m_BottomX, m_BottomY;
    cbtF32 m_TopX, m_TopY;

    CBTViewport(cbtF32 _bottomX = 0.0f, cbtF32 _bottomY = 0.0f, cbtF32 _topX = 1.0f, cbtF32 _topY = 1.0f)
        : m_BottomX(_bottomX)
        , m_BottomY(_bottomY)
        , m_TopX(_topX)
        , m_TopY(_topY)
    {}
    ~CBTViewport() {}
};

/// Camera Projection Mode
enum class CBTProjectionMode
{
    PERSPECTIVE,
    ORTHOGRAPHIC,
};

class CBTCamera : public CBTComponent
{
private:
    /// Projection Mode
    CBTProjectionMode m_ProjectionMode = CBTProjectionMode::PERSPECTIVE;
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
    CBTViewport m_ViewPort;

    /// Deferred Lighting Shader
    CBTRef<CBTShaderProgram> m_LightingShader;
    /// Post Processing Shaders
    std::vector<CBTShaderProgram*> m_PostProcessShaders;

    /// Skybox Color
    CBTColor m_SkyboxColor = CBTColor::WHITE;
    /// Skybox Texture
    CBTRef<CBTTexture> m_SkyboxTexture;
    /// Skybox Shader
    CBTRef<CBTShaderProgram> m_SkyboxShader;

public:
    // Constructor(s) & Destructor
    CBTCamera() {}
    virtual ~CBTCamera() { for (cbtU32 i = 0; i < m_PostProcessShaders.size(); ++i) { m_PostProcessShaders[i]->AutoRelease(); } }

    // Interface Function(s)
    inline CBTProjectionMode GetProjectionMode() const { return m_ProjectionMode; }
    void SetProjectionMode(CBTProjectionMode _mode);

    inline cbtF32 GetNearPlane() const { return m_NearPlane; }
    void SetNearPlane(cbtF32 _value);
    inline cbtF32 GetFarPlane() const { return m_FarPlane; }
    void SetFarPlane(cbtF32 _value);
    inline cbtF32 GetAspectRatio() const { return m_AspectRatio; }
    inline void SetAspectRatio(cbtF32 _aspectRatio) { m_AspectRatio = _aspectRatio; }

    inline cbtU8 GetDepth() const { return m_Depth; }
    inline void SetDepth(cbtU8 _depth) { m_Depth = CBTMathUtil::Min<cbtU8>(_depth, 15); }

    CBTMatrix4F GetProjectionMatrix() const;

    // Perspective
    inline cbtF32 GetFOV() const { return m_FOV; }
    inline void SetFOV(cbtF32 _fov) { m_FOV = CBTMathUtil::Clamp<cbtF32>(_fov, 1.0f, 89.0f); }

    // Orthographic
    inline cbtF32 GetOrthoSize() const { return m_OrthoSize; }
    inline void SetOrthoSize(cbtF32 _orthoSize) { m_OrthoSize = _orthoSize; }

    // Viewport
    inline const CBTViewport& GetViewport() const { return m_ViewPort; }
    inline void SetViewport(const CBTViewport& _viewport) { m_ViewPort = _viewport; }

    // Deferred Lighting Shader
    CBTShaderProgram* GetLightingShader() { return m_LightingShader.GetRawPointer(); }
    const CBTShaderProgram* GetLightingShader() const { return m_LightingShader.GetRawPointer(); }
    void SetLightingShader(CBTShaderProgram* _shader) { m_LightingShader = _shader; }

    // Post Processing Shaders
    void SetPostProcessShaders(std::initializer_list<CBTShaderProgram*> _shaders);
    CBTShaderProgram** GetPostProcessShaders() { return m_PostProcessShaders.empty() ? nullptr : &m_PostProcessShaders[0]; }
    cbtU32 GetPostProcessShaderCount() const { return (cbtU32)m_PostProcessShaders.size(); }

    // Skybox
    inline const CBTColor& GetSkyboxColor() const { return m_SkyboxColor; }
    inline void SetSkyboxColor(const CBTColor& _color) { m_SkyboxColor = _color; }

    inline const CBTTexture* GetSkyboxTexture() const { return m_SkyboxTexture.GetRawPointer(); }
    inline CBTTexture* GetSkyboxTexture() { return m_SkyboxTexture.GetRawPointer(); }
    inline void SetSkyboxTexture(CBTTexture* _texture) { m_SkyboxTexture = _texture; }

    CBTShaderProgram* GetSkyboxShader() { return m_SkyboxShader.GetRawPointer(); }
    const CBTShaderProgram* GetSkyboxShader() const { return m_SkyboxShader.GetRawPointer(); }
    void SetSkyboxShader(CBTShaderProgram* _shader) { m_SkyboxShader = _shader; }
};

NS_CBT_END