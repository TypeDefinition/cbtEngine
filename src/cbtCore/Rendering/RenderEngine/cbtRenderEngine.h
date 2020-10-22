#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/General/cbtSingleton.h"
#include "Core/General/cbtLibrary.h"
#include "Rendering/Color/cbtColor.h"
#include "Rendering/Window/cbtWindow.h"
#include "cbtRenderAPI.h"
#include "Rendering/Renderer/cbtRenderer.h"

NS_CBT_BEGIN

    class cbtRenderEngine : public cbtSingleton<cbtRenderEngine>
    {
        friend class cbtSingleton<cbtRenderEngine>;

    protected:
        cbtLibrary<cbtMaterial>* m_MaterialLibrary = nullptr;
        cbtLibrary<cbtShaderProgram>* m_ShaderLibrary = nullptr;
        cbtLibrary<cbtMesh>* m_MeshLibrary = nullptr;
        cbtLibrary<cbtTexture>* m_TextureLibrary = nullptr;

        cbtRenderEngine()
        {
        }

        virtual ~cbtRenderEngine()
        {
        }

        static cbtRenderEngine* CreateInstance();

    public:
        inline const cbtLibrary<cbtMaterial>* GetMaterialLibrary() const
        {
            return m_MaterialLibrary;
        }

        inline cbtLibrary<cbtMaterial>* GetMaterialLibrary()
        {
            return m_MaterialLibrary;
        }

        inline const cbtLibrary<cbtShaderProgram>* GetShaderLibrary() const
        {
            return m_ShaderLibrary;
        }

        inline cbtLibrary<cbtShaderProgram>* GetShaderLibrary()
        {
            return m_ShaderLibrary;
        }

        inline const cbtLibrary<cbtMesh>* GetMeshLibrary() const
        {
            return m_MeshLibrary;
        }

        inline cbtLibrary<cbtMesh>* GetMeshLibrary()
        {
            return m_MeshLibrary;
        }

        inline const cbtLibrary<cbtTexture>* GetTextureLibrary() const
        {
            return m_TextureLibrary;
        }

        inline cbtLibrary<cbtTexture>* GetTextureLibrary()
        {
            return m_TextureLibrary;
        }

        virtual const cbtWindow* GetWindow() const = 0;

        virtual cbtWindow* GetWindow() = 0;

        virtual void Init(const cbtWindowProperties& _winProp) = 0;

        virtual void Update() = 0;

        virtual void Exit() = 0;
    };

NS_CBT_END