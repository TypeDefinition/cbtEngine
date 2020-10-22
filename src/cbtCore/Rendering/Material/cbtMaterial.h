#pragma once

// Include CBT
#include "Debug/cbtDebug.h"
#include "Rendering/Mesh/cbtMesh.h"
#include "Rendering/Texture/cbtTexture.h"
#include "Rendering/Shader/cbtShaderProgram.h"

// Include STD
#include <vector>

NS_CBT_BEGIN

/// Render Mode dictates the rendering order.
    enum cbtRenderMode
    {
        CBT_RENDER_MODE_DEFERRED, /// Render 1st
        CBT_RENDER_MODE_FORWARD, /// Render 2nd
        CBT_RENDER_MODE_FORWARD_TRANSPARENT, /// Render 3rd
        CBT_NUM_RENDER_MODE,
    };

    class cbtMaterial : public cbtManaged
    {
    protected:
        /// Material Name
        const cbtStr m_Name;

        /// Ambient Color
        cbtColor m_AmbientColor = cbtColor(0.1f, 0.1f, 0.1f, 1.0f);
        cbtColor m_AlbedoColor = cbtColor::WHITE;
        cbtColor m_SpecularColor = cbtColor::WHITE;
        cbtF32 m_Gloss = 16.0f;
        cbtF32 m_DisplacementScale = 0.1f;
        cbtS32 m_MinDisplacementSamples = 1;
        cbtS32 m_MaxDisplacementSamples = 25;
        cbtVector2F m_TextureOffset;
        cbtVector2F m_TextureScale = cbtVector2F(1.0f, 1.0f);

        /// Albedo Texture
        cbtRef<cbtTexture> m_TextureAlbedo;
        /// Normal Map
        cbtRef<cbtTexture> m_TextureNormal;
        /// Specular
        cbtRef<cbtTexture> m_TextureSpecular;
        /// Gloss Map
        cbtRef<cbtTexture> m_TextureGloss;
        /// Displacement Map
        cbtRef<cbtTexture> m_TextureDisplacement;

        /// Mesh
        cbtRef<cbtMesh> m_Mesh;

        /// Forward Shader/Geometry Shader
        cbtRef<cbtShaderProgram> m_Shader;

        /// Render Mode
        cbtRenderMode m_RenderMode = CBT_RENDER_MODE_DEFERRED;

        /**
            \brief Destructor
        */
        virtual ~cbtMaterial()
        {
        }

    public:
        cbtMaterial(const cbtStr& _name)
                :m_Name(_name)
        {
        }

        // Interface Function(s)
        inline const cbtStr& GetName() const
        {
            return m_Name;
        }

        inline cbtBool IsComplete() const
        {
            return (m_Mesh != nullptr) && (m_Shader != nullptr);
        }

        inline const cbtColor& GetAmbientColor() const
        {
            return m_AmbientColor;
        }

        inline void SetAmbientColor(const cbtColor& _color)
        {
            m_AmbientColor = _color;
        }

        inline const cbtColor& GetAlbedoColor() const
        {
            return m_AlbedoColor;
        }

        inline void SetAlbedoColor(const cbtColor& _color)
        {
            m_AlbedoColor = _color;
        }

        inline const cbtColor& GetSpecularColor() const
        {
            return m_SpecularColor;
        }

        inline void SetSpecularColor(const cbtColor& _color)
        {
            m_SpecularColor = _color;
        }

        inline cbtF32 GetGloss() const
        {
            return m_Gloss;
        }

        inline void SetGloss(cbtF32 _gloss)
        {
            m_Gloss = _gloss;
        }

        inline cbtF32 GetDisplacementScale() const
        {
            return m_DisplacementScale;
        }

        inline void SetDisplacementScale(cbtF32 _displacementScale)
        {
            m_DisplacementScale = _displacementScale;
        }

        inline cbtS32 GetMaxDisplacementSamples() const
        {
            return m_MaxDisplacementSamples;
        }

        inline cbtS32 GetMinDisplacementSamples() const
        {
            return m_MinDisplacementSamples;
        }

        inline void SetDisplacementSamples(cbtS32 _min, cbtS32 _max)
        {
            m_MinDisplacementSamples = _min;
            m_MaxDisplacementSamples = _max;
        }

        const cbtVector2F& GetTextureOffset() const
        {
            return m_TextureOffset;
        }

        inline void SetTextureOffset(const cbtVector2F& _textureOffset)
        {
            m_TextureOffset = _textureOffset;
        }

        const cbtVector2F& GetTextureScale() const
        {
            return m_TextureScale;
        }

        inline void SetTextureScale(const cbtVector2F& _textureScale)
        {
            m_TextureScale = _textureScale;
        }

        inline const cbtTexture* GetTextureAlbedo() const
        {
            return m_TextureAlbedo.GetRawPointer();
        }

        inline cbtTexture* GetTextureAlbedo()
        {
            return m_TextureAlbedo.GetRawPointer();
        }

        inline void SetTextureAlbedo(cbtTexture* _texture)
        {
            m_TextureAlbedo = _texture;
        }

        inline const cbtTexture* GetTextureNormal() const
        {
            return m_TextureNormal.GetRawPointer();
        }

        inline cbtTexture* GetTextureNormal()
        {
            return m_TextureNormal.GetRawPointer();
        }

        inline void SetTextureNormal(cbtTexture* _texture)
        {
            m_TextureNormal = _texture;
        }

        inline const cbtTexture* GetTextureSpecular() const
        {
            return m_TextureSpecular.GetRawPointer();
        }

        inline cbtTexture* GetTextureSpecular()
        {
            return m_TextureSpecular.GetRawPointer();
        }

        inline void SetTextureSpecular(cbtTexture* _texture)
        {
            m_TextureSpecular = _texture;
        }

        inline const cbtTexture* GetTextureGloss() const
        {
            return m_TextureGloss.GetRawPointer();
        }

        inline cbtTexture* GetTextureGloss()
        {
            return m_TextureGloss.GetRawPointer();
        }

        inline void SetTextureGloss(cbtTexture* _texture)
        {
            m_TextureGloss = _texture;
        }

        inline const cbtTexture* GetTextureDisplacement() const
        {
            return m_TextureDisplacement.GetRawPointer();
        }

        inline cbtTexture* GetTextureDisplacement()
        {
            return m_TextureDisplacement.GetRawPointer();
        }

        inline void SetTextureDisplacement(cbtTexture* _texture)
        {
            m_TextureDisplacement = _texture;
        }

        inline const cbtMesh* GetMesh() const
        {
            return m_Mesh.GetRawPointer();
        }

        inline cbtMesh* GetMesh()
        {
            return m_Mesh.GetRawPointer();
        }

        inline void SetMesh(cbtMesh* _mesh)
        {
            m_Mesh = _mesh;
        }

        inline const cbtShaderProgram* GetShader() const
        {
            return m_Shader.GetRawPointer();
        }

        inline cbtShaderProgram* GetShader()
        {
            return m_Shader.GetRawPointer();
        }

        inline void SetShader(cbtShaderProgram* _shader)
        {
            m_Shader = _shader;
        }

        inline cbtRenderMode GetRenderMode() const
        {
            return m_RenderMode;
        }

        inline void SetRenderMode(cbtRenderMode _renderMode)
        {
            m_RenderMode = _renderMode;
        }
    };

NS_CBT_END