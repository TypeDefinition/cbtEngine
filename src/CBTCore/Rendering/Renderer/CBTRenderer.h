#pragma once

// Include CBT
#include "CBTMacros.h"
#include "CBTRenderBuffer.h"
#include "Core/Event/CBTEventListener.h"
#include "Rendering/Shader/CBTShaderProgram.h"
#include "Game/Component/Transform/CBTTransform.h"
#include "Rendering/Component/Graphics/CBTGraphics.h"
#include "Rendering/Component/Camera/CBTCamera.h"
#include "Rendering/Component/Light/CBTLight.h"

// Include STD
#include <unordered_map>

NS_CBT_BEGIN

// Stencil Value(s)
#define CBT_STENCIL_OPAQUE 1

class CBTRenderer
{
private:
    CBTEventListener m_EventListener;

    CBTRef<CBTMesh> m_ScreenQuad;
    CBTRef<CBTMesh> m_SkyboxMesh;

    cbtF32 m_RenderScale;
    cbtS32 m_BufferWidth, m_BufferHeight;
    cbtS32 m_WindowWidth, m_WindowHeight;
    CBTFrameBuffer* m_GBuffer;
    CBTFrameBuffer* m_LBuffer;
    CBTFrameBuffer* m_FBuffer;
    CBTFrameBuffer* m_PBuffer;

    CBTComponentGroup<CBTLight, CBTTransform> m_Lights;
    CBTComponentGroup<CBTCamera, CBTTransform> m_Cameras;
    CBTComponentGroup<CBTGraphics, CBTTransform> m_Objects;

    std::unordered_map<CBTMaterial*, std::vector<cbtU32>> m_Deferred;
    std::unordered_map<CBTMaterial*, std::vector<cbtU32>> m_Forward;
    std::vector<cbtU32> m_Transparent;

    static cbtBool InViewFrustum(const CBTMatrix4F& _viewProjectionMatrix, const CBTMatrix4F& _modelMatrix, const CBTBoundingBox& _boundingBox);
    static cbtF32 GetObjectDistanceToCamera(const CBTMatrix4F& _viewProjectionMatrix, const CBTMatrix4F& _modelMatrix, const CBTBoundingBox& _boundingBox);

    void SortRenderObjects();
    void ClearRenderObjects();

    void DistanceMergeSort(cbtF32* _distanceArray, cbtU32* _indexArray, cbtU32 _numElements);
    std::vector<cbtU32> SortTransparentObjects(const CBTMatrix4F& _viewProjectionMatrix);

    void RenderGPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, const CBTMatrix4F& _viewProjectionMatrix, CBTCamera* _camCamera);
    void RenderLPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, CBTCamera* _camCamera, CBTTransform* _camTransform);
    void RenderFPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, const CBTMatrix4F& _viewProjectionMatrix, CBTCamera* _camCamera, CBTTransform* _camTransform);
    void RenderPPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, const CBTMatrix4F& _viewProjectionMatrix, CBTCamera* _camCamera, CBTTransform* _camTransform);

    void Render();

public:
    CBTRenderer();
    ~CBTRenderer();

    inline void SetRenderScale(cbtF32 _renderScale) { m_RenderScale = _renderScale; }
    inline cbtF32 GetRenderScale() const { return m_RenderScale; }

    void Update();
};

NS_CBT_END