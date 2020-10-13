#pragma once

// Include CBT
#include "cbtMacros.h"
#include "cbtRenderBuffer.h"
#include "Core/Event/cbtEventListener.h"
#include "Rendering/Shader/cbtShaderProgram.h"
#include "Game/Component/Transform/cbtTransform.h"
#include "Rendering/Component/Graphics/cbtGraphics.h"
#include "Rendering/Component/Camera/cbtCamera.h"
#include "Rendering/Component/Light/cbtLight.h"

// Include STD
#include <unordered_map>

NS_CBT_BEGIN

// Stencil Value(s)
#define CBT_STENCIL_OPAQUE 1

class cbtRenderer
{
private:
    cbtEventListener m_EventListener;

    cbtRef<cbtMesh> m_ScreenQuad;
    cbtRef<cbtMesh> m_SkyboxMesh;

    cbtF32 m_RenderScale;
    cbtS32 m_BufferWidth, m_BufferHeight;
    cbtS32 m_WindowWidth, m_WindowHeight;
    cbtFrameBuffer* m_GBuffer;
    cbtFrameBuffer* m_LBuffer;
    cbtFrameBuffer* m_FBuffer;
    cbtFrameBuffer* m_PBuffer;

    cbtComponentGroup<cbtLight, cbtTransform> m_Lights;
    cbtComponentGroup<cbtCamera, cbtTransform> m_Cameras;
    cbtComponentGroup<cbtGraphics, cbtTransform> m_Objects;

    std::unordered_map<cbtMaterial*, std::vector<cbtU32>> m_Deferred;
    std::unordered_map<cbtMaterial*, std::vector<cbtU32>> m_Forward;
    std::vector<cbtU32> m_Transparent;

    static cbtBool InViewFrustum(const cbtMatrix4F& _viewProjectionMatrix, const cbtMatrix4F& _modelMatrix, const cbtBoundingBox& _boundingBox);
    static cbtF32 GetObjectDistanceToCamera(const cbtMatrix4F& _viewProjectionMatrix, const cbtMatrix4F& _modelMatrix, const cbtBoundingBox& _boundingBox);

    void SortRenderObjects();
    void ClearRenderObjects();

    void DistanceMergeSort(cbtF32* _distanceArray, cbtU32* _indexArray, cbtU32 _numElements);
    std::vector<cbtU32> SortTransparentObjects(const cbtMatrix4F& _viewProjectionMatrix);

    void RenderGPass(const cbtMatrix4F& _viewMatrix, const cbtMatrix4F& _projectionMatrix, const cbtMatrix4F& _viewProjectionMatrix, cbtCamera* _camCamera);
    void RenderLPass(const cbtMatrix4F& _viewMatrix, const cbtMatrix4F& _projectionMatrix, cbtCamera* _camCamera, cbtTransform* _camTransform);
    void RenderFPass(const cbtMatrix4F& _viewMatrix, const cbtMatrix4F& _projectionMatrix, const cbtMatrix4F& _viewProjectionMatrix, cbtCamera* _camCamera, cbtTransform* _camTransform);
    void RenderPPass(const cbtMatrix4F& _viewMatrix, const cbtMatrix4F& _projectionMatrix, const cbtMatrix4F& _viewProjectionMatrix, cbtCamera* _camCamera, cbtTransform* _camTransform);

    void Render();

public:
    cbtRenderer();
    ~cbtRenderer();

    inline void SetRenderScale(cbtF32 _renderScale) { m_RenderScale = _renderScale; }
    inline cbtF32 GetRenderScale() const { return m_RenderScale; }

    void Update();
};

NS_CBT_END