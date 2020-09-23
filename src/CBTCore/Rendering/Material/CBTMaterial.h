#pragma once

// Include CBT
#include "Debug/CBTDebug.h"
#include "Rendering/Mesh/CBTMesh.h"
#include "Rendering/Texture/CBTTexture.h"
#include "Rendering/Shader/CBTShaderProgram.h"

// Include STD
#include <vector>

NS_CBT_BEGIN

/// Render Mode dictates the rendering order.
enum CBTRenderMode
{
    CBT_RENDER_MODE_DEFERRED, /// Render 1st
    CBT_RENDER_MODE_FORWARD, /// Render 2nd
    CBT_RENDER_MODE_FORWARD_TRANSPARENT, /// Render 3rd
    CBT_NUM_RENDER_MODE,
};

class CBTMaterial : public CBTManaged
{
protected:
    /// Material Name
    const cbtStr m_Name;

    /// Ambient Color
    CBTColor m_AmbientColor = CBTColor(0.1f, 0.1f, 0.1f, 1.0f);
    CBTColor m_AlbedoColor = CBTColor::WHITE;
    CBTColor m_SpecularColor = CBTColor::WHITE;
    cbtF32 m_Gloss = 16.0f;
    cbtF32 m_DisplacementScale = 0.1f;
    cbtS32 m_MinDisplacementSamples = 1;
    cbtS32 m_MaxDisplacementSamples = 25;
    CBTVector2F m_TextureOffset;
    CBTVector2F m_TextureScale = CBTVector2F(1.0f, 1.0f);

    /// Albedo Texture
    CBTRef<CBTTexture> m_TextureAlbedo;
    /// Normal Map
    CBTRef<CBTTexture> m_TextureNormal;
    /// Specular
    CBTRef<CBTTexture> m_TextureSpecular;
    /// Gloss Map
    CBTRef<CBTTexture> m_TextureGloss;
    /// Displacement Map
    CBTRef<CBTTexture> m_TextureDisplacement;

    /// Mesh
    CBTRef<CBTMesh> m_Mesh;

    /// Forward Shader/Geometry Shader
    CBTRef<CBTShaderProgram> m_Shader;

    /// Render Mode
    CBTRenderMode m_RenderMode = CBT_RENDER_MODE_DEFERRED;

    /**
        \brief Destructor
    */
    virtual ~CBTMaterial() {}

public:
    CBTMaterial(const cbtStr& _name) : m_Name(_name) {}

    // Interface Function(s)
    inline const cbtStr& GetName() const { return m_Name; }
    inline cbtBool IsComplete() const { return (m_Mesh != nullptr) && (m_Shader != nullptr); }

    inline const CBTColor& GetAmbientColor() const { return m_AmbientColor; }
    inline void SetAmbientColor(const CBTColor& _color) { m_AmbientColor = _color; }

    inline const CBTColor& GetAlbedoColor() const { return m_AlbedoColor; }
    inline void SetAlbedoColor(const CBTColor& _color) { m_AlbedoColor = _color; }

    inline const CBTColor& GetSpecularColor() const { return m_SpecularColor; }
    inline void SetSpecularColor(const CBTColor& _color) { m_SpecularColor = _color; }

    inline cbtF32 GetGloss() const { return m_Gloss; }
    inline void SetGloss(cbtF32 _gloss) { m_Gloss = _gloss; }

    inline cbtF32 GetDisplacementScale() const { return m_DisplacementScale; }
    inline void SetDisplacementScale(cbtF32 _displacementScale) { m_DisplacementScale = _displacementScale; }

    inline cbtS32 GetMaxDisplacementSamples() const { return m_MaxDisplacementSamples; }
    inline cbtS32 GetMinDisplacementSamples() const { return m_MinDisplacementSamples; }
    inline void SetDisplacementSamples(cbtS32 _min, cbtS32 _max) { m_MinDisplacementSamples = _min; m_MaxDisplacementSamples = _max; }

    const CBTVector2F& GetTextureOffset() const { return m_TextureOffset; }
    inline void SetTextureOffset(const CBTVector2F& _textureOffset) { m_TextureOffset = _textureOffset; }

    const CBTVector2F& GetTextureScale() const { return m_TextureScale; }
    inline void SetTextureScale(const CBTVector2F& _textureScale) { m_TextureScale = _textureScale; }

    inline const CBTTexture* GetTextureAlbedo() const { return m_TextureAlbedo.GetRawPointer(); }
    inline CBTTexture* GetTextureAlbedo() { return m_TextureAlbedo.GetRawPointer(); }
    inline void SetTextureAlbedo(CBTTexture* _texture) { m_TextureAlbedo = _texture; }

    inline const CBTTexture* GetTextureNormal() const { return m_TextureNormal.GetRawPointer(); }
    inline CBTTexture* GetTextureNormal() { return m_TextureNormal.GetRawPointer(); }
    inline void SetTextureNormal(CBTTexture* _texture) { m_TextureNormal = _texture; }

    inline const CBTTexture* GetTextureSpecular() const { return m_TextureSpecular.GetRawPointer(); }
    inline CBTTexture* GetTextureSpecular() { return m_TextureSpecular.GetRawPointer(); }
    inline void SetTextureSpecular(CBTTexture* _texture) { m_TextureSpecular = _texture; }

    inline const CBTTexture* GetTextureGloss() const { return m_TextureGloss.GetRawPointer(); }
    inline CBTTexture* GetTextureGloss() { return m_TextureGloss.GetRawPointer(); }
    inline void SetTextureGloss(CBTTexture* _texture) { m_TextureGloss = _texture; }

    inline const CBTTexture* GetTextureDisplacement() const { return m_TextureDisplacement.GetRawPointer(); }
    inline CBTTexture* GetTextureDisplacement() { return m_TextureDisplacement.GetRawPointer(); }
    inline void SetTextureDisplacement(CBTTexture* _texture) { m_TextureDisplacement = _texture; }

    inline const CBTMesh* GetMesh() const { return m_Mesh.GetRawPointer(); }
    inline CBTMesh* GetMesh() { return m_Mesh.GetRawPointer(); }
    inline void SetMesh(CBTMesh* _mesh) { m_Mesh = _mesh; }

    inline const CBTShaderProgram* GetShader() const { return m_Shader.GetRawPointer(); }
    inline CBTShaderProgram* GetShader() { return m_Shader.GetRawPointer(); }
    inline void SetShader(CBTShaderProgram* _shader) { m_Shader = _shader; }

    inline CBTRenderMode GetRenderMode() const { return m_RenderMode; }
    inline void SetRenderMode(CBTRenderMode _renderMode) { m_RenderMode = _renderMode; }
};

NS_CBT_END