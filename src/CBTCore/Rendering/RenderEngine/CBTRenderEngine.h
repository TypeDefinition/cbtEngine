#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTSingleton.h"
#include "Core/General/CBTLibrary.h"
#include "Rendering/Color/CBTColor.h"
#include "Rendering/Window/CBTWindow.h"
#include "CBTRenderAPI.h"
#include "Rendering/Renderer/CBTRenderer.h"

NS_CBT_BEGIN

class CBTRenderEngine : public CBTSingleton<CBTRenderEngine>
{
    friend class CBTSingleton<CBTRenderEngine>;

protected:
    CBTLibrary<CBTMaterial>* m_MaterialLibrary = nullptr;
    CBTLibrary<CBTShaderProgram>* m_ShaderLibrary = nullptr;
    CBTLibrary<CBTMesh>* m_MeshLibrary = nullptr;
    CBTLibrary<CBTTexture>* m_TextureLibrary = nullptr;

    CBTRenderEngine() {}
    virtual ~CBTRenderEngine() {}

    static CBTRenderEngine* CreateInstance();

public:
    inline const CBTLibrary<CBTMaterial>* GetMaterialLibrary() const { return m_MaterialLibrary; }
    inline CBTLibrary<CBTMaterial>* GetMaterialLibrary() { return m_MaterialLibrary; }

    inline const CBTLibrary<CBTShaderProgram>* GetShaderLibrary() const { return m_ShaderLibrary; }
    inline CBTLibrary<CBTShaderProgram>* GetShaderLibrary() { return m_ShaderLibrary; }

    inline const CBTLibrary<CBTMesh>* GetMeshLibrary() const { return m_MeshLibrary; }
    inline CBTLibrary<CBTMesh>* GetMeshLibrary() { return m_MeshLibrary; }

    inline const CBTLibrary<CBTTexture>* GetTextureLibrary() const { return m_TextureLibrary; }
    inline CBTLibrary<CBTTexture>* GetTextureLibrary() { return m_TextureLibrary; }

    virtual const CBTWindow* GetWindow() const = 0;
    virtual CBTWindow* GetWindow() = 0;

    virtual void Init(const CBTWindowProperties& _winProp) = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
};

NS_CBT_END