// Include CBT
#include "CBTRenderer.h"
#include "Core/Math/CBTPlane.h"
#include "Game/GameEngine/CBTGameEngine.h"
#include "Rendering/RenderEngine/CBTRenderEngine.h"
#include "Rendering/Mesh/CBTMeshBuilder.h"

NS_CBT_BEGIN

// http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/
cbtBool CBTRenderer::InViewFrustum(const CBTMatrix4F& _viewProjectionMatrix, const CBTMatrix4F& _modelMatrix, const CBTBoundingBox& _boundingBox)
{
    // The planes of the frustum.
    CBTPlane frustumPlanes[6];
    // Left Plane
    frustumPlanes[0].Set(CBTVector3F(_viewProjectionMatrix[0][3] + _viewProjectionMatrix[0][0], _viewProjectionMatrix[1][3] + _viewProjectionMatrix[1][0], _viewProjectionMatrix[2][3] + _viewProjectionMatrix[2][0]), _viewProjectionMatrix[3][3] + _viewProjectionMatrix[3][0]);
    // Right Plane
    frustumPlanes[1].Set(CBTVector3F(_viewProjectionMatrix[0][3] - _viewProjectionMatrix[0][0], _viewProjectionMatrix[1][3] - _viewProjectionMatrix[1][0], _viewProjectionMatrix[2][3] - _viewProjectionMatrix[2][0]), _viewProjectionMatrix[3][3] - _viewProjectionMatrix[3][0]);
    // Bottom Plane
    frustumPlanes[2].Set(CBTVector3F(_viewProjectionMatrix[0][3] + _viewProjectionMatrix[0][1], _viewProjectionMatrix[1][3] + _viewProjectionMatrix[1][1], _viewProjectionMatrix[2][3] + _viewProjectionMatrix[2][1]), _viewProjectionMatrix[3][3] + _viewProjectionMatrix[3][1]);
    // Top Plane
    frustumPlanes[3].Set(CBTVector3F(_viewProjectionMatrix[0][3] - _viewProjectionMatrix[0][1], _viewProjectionMatrix[1][3] - _viewProjectionMatrix[1][1], _viewProjectionMatrix[2][3] - _viewProjectionMatrix[2][1]), _viewProjectionMatrix[3][3] - _viewProjectionMatrix[3][1]);
    // Far Plane
    frustumPlanes[4].Set(CBTVector3F(_viewProjectionMatrix[0][3] + _viewProjectionMatrix[0][2], _viewProjectionMatrix[1][3] + _viewProjectionMatrix[1][2], _viewProjectionMatrix[2][3] + _viewProjectionMatrix[2][2]), _viewProjectionMatrix[3][3] + _viewProjectionMatrix[3][2]);
    // Near Plane
    frustumPlanes[5].Set(CBTVector3F(_viewProjectionMatrix[0][3] - _viewProjectionMatrix[0][2], _viewProjectionMatrix[1][3] - _viewProjectionMatrix[1][2], _viewProjectionMatrix[2][3] - _viewProjectionMatrix[2][2]), _viewProjectionMatrix[3][3] - _viewProjectionMatrix[3][2]);

    // For each plane, check if the points of the bounding box are on the "inner" side of the frustum plane.
    for (cbtU32 i = 0; i < 6; ++i)
    {
        cbtBool inside = false;
        for (cbtU32 j = 0; j < CBTBoundingBox::NUM_POINTS; ++j)
        {
            CBTMatrix<cbtF32, 1, 4> pointModelSpace;
            pointModelSpace[0][0] = _boundingBox[j].m_X;
            pointModelSpace[0][1] = _boundingBox[j].m_Y;
            pointModelSpace[0][2] = _boundingBox[j].m_Z;
            pointModelSpace[0][3] = 1.0f;

            CBTMatrix<cbtF32, 1, 4> pointWorldSpace = _modelMatrix * pointModelSpace;
            CBTVector3F testPoint(pointWorldSpace[0][0], pointWorldSpace[0][1], pointWorldSpace[0][2]);

            cbtF32 distance = frustumPlanes[i].DistanceToPoint(testPoint);
            if (distance > 0.0f)
            {
                inside = true;
                break;
            }
        }

        // If all 8 points of the bounding box is on the "outer" side of one of the planes, then the object is *highly likely* to not be in the view frustum.
        if (!inside)
        {
            return false;
        }
    }

    // If every plane has at least 1 point of the bounding box in the "inner" side, then the object is in the view frustum.
    return true;
}

cbtF32 CBTRenderer::GetObjectDistanceToCamera(const CBTMatrix4F& _viewProjectionMatrix, const CBTMatrix4F& _modelMatrix, const CBTBoundingBox& _boundingBox)
{
    // Near Plane
    CBTPlane nearPlane;
    nearPlane.Set(CBTVector3F(_viewProjectionMatrix[0][3] + _viewProjectionMatrix[0][2], _viewProjectionMatrix[1][3] + _viewProjectionMatrix[1][2], _viewProjectionMatrix[2][3] + _viewProjectionMatrix[2][2]), _viewProjectionMatrix[3][3] + _viewProjectionMatrix[3][2]);

    cbtF32 longestDistance = CBTMathUtil::F32_LOWEST;
    for (cbtU32 i = 0; i < CBTBoundingBox::NUM_POINTS; ++i)
    {
        CBTMatrix<cbtF32, 1, 4> pointModelSpace;
        pointModelSpace[0][0] = _boundingBox[i].m_X;
        pointModelSpace[0][1] = _boundingBox[i].m_Y;
        pointModelSpace[0][2] = _boundingBox[i].m_Z;
        pointModelSpace[0][3] = 1.0f;

        CBTMatrix<cbtF32, 1, 4> pointWorldSpace = _modelMatrix * pointModelSpace;
        CBTVector3F testPoint(pointWorldSpace[0][0], pointWorldSpace[0][1], pointWorldSpace[0][2]);

        cbtF32 distance = nearPlane.DistanceToPoint(testPoint);
        longestDistance = (distance > longestDistance) ? distance : longestDistance;
    }

    return longestDistance;
}

CBTRenderer::CBTRenderer()
{
    m_RenderScale = 1.0f;
    m_WindowWidth = CBTRenderEngine::GetInstance()->GetWindow()->GetProperties().m_Width;
    m_WindowHeight = CBTRenderEngine::GetInstance()->GetWindow()->GetProperties().m_Height;
    m_BufferWidth = (cbtS32)(m_RenderScale * (cbtF32)m_WindowWidth);
    m_BufferHeight = (cbtS32)(m_RenderScale * (cbtF32)m_WindowHeight);

    // Face Culling
    CBTRenderAPI::SetCulling(true);
    // Depth Test
    CBTRenderAPI::SetDepthTest(true);
    CBTRenderAPI::SetDepthFunc(CBTCompareFunc::LESS);
    CBTRenderAPI::SetDepthWrite(true);
    // Alpha Blending
    CBTRenderAPI::SetBlendTest(false);
    // Viewport
    CBTRenderAPI::SetViewPort(0, 0, m_BufferWidth, m_BufferHeight);
    // Scissor does not affect NDC, but acts like a mask preventing writes to the framebuffer outside of the specified area. Does not affect the textures passed in as uniforms.
    // CBTRenderAPI::SetScissor(0, 0, m_WindowWidth, m_WindowHeight);
    // CBTRenderAPI::SetScissorTest(false);
    // Alpha Blending
    CBTRenderAPI::SetBlendTest(true);
    // Stencil Test
    CBTRenderAPI::SetStencilTest(false);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::ALWAYS, 0, 0xFF);
    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::KEEP);

    m_ScreenQuad = CBTMeshBuilder::CreateScreenQuad("Screen Quad"); m_ScreenQuad->Retain();
    m_SkyboxMesh = CBTMeshBuilder::CreateSkybox("Skybox"); m_SkyboxMesh->Retain();

    m_GBuffer = CreateGBuffer(m_BufferWidth, m_BufferHeight); m_GBuffer->Retain();
    m_LBuffer = CreateLBuffer(m_BufferWidth, m_BufferHeight); m_LBuffer->Retain();
    m_FBuffer = CreateFBuffer(m_BufferWidth, m_BufferHeight); m_FBuffer->Retain();
    m_PBuffer = CreatePBuffer(m_BufferWidth, m_BufferHeight); m_PBuffer->Retain();
}

CBTRenderer::~CBTRenderer()
{
    m_ScreenQuad->Release();
    m_SkyboxMesh->Release();

    m_GBuffer->Release();
    m_LBuffer->Release();
    m_FBuffer->Release();
    m_PBuffer->Release();
}

void CBTRenderer::Update()
{
    CBTFrameBuffer::ClearAttachmentsAll(m_GBuffer);
    CBTFrameBuffer::ClearAttachmentsAll(m_LBuffer);
    CBTFrameBuffer::ClearAttachmentsAll(m_FBuffer);
    CBTFrameBuffer::ClearAttachmentsAll(m_PBuffer);
    CBTFrameBuffer::ClearAttachmentsAll(nullptr);

    CBTScene* activeScene = CBTGameEngine::GetInstance()->GetSceneManager()->GetActiveScene();
    if (activeScene == nullptr) { return; }
    activeScene->GetComponentGroup<CBTLight, CBTTransform>(m_Lights);
    activeScene->GetComponentGroup<CBTCamera, CBTTransform>(m_Cameras);
    activeScene->GetComponentGroup<CBTGraphics, CBTTransform>(m_Objects);

    Render();
}

void CBTRenderer::SortRenderObjects()
{
    // Sort the entities into 3 sorting orders, CBT_RENDER_MODE_DEFERRED, CBT_RENDER_MODE_FORWARD and CBT_RENDER_MODE_FORWARD_TRANSPARENT.
    CBTGraphics** graphicArray = m_Objects.GetArray<CBTGraphics>();
    for (cbtU32 i = 0; i < m_Objects.GetArraySize(); ++i)
    {
        CBTMaterial* material = graphicArray[i]->GetMaterial();
        if (!material->IsComplete()) { continue; }

        /* Further sort them according to their materials to reduce the number of times we need to swap out the shader and textures and uniforms.
        After sorting, we are using i, the index of the entity in the array to access it later for rendering. */
        switch (material->GetRenderMode())
        {
        case CBT_RENDER_MODE_DEFERRED:
            m_Deferred[material].push_back(i);
            break;
        case CBT_RENDER_MODE_FORWARD:
            m_Forward[material].push_back(i);
            break;
        case CBT_RENDER_MODE_FORWARD_TRANSPARENT:
            m_Transparent.push_back(i);
            break;
        default:
            break;
        }
    }
}

void CBTRenderer::ClearRenderObjects()
{
    m_Deferred.clear();
    m_Forward.clear();
    m_Transparent.clear();
}

void CBTRenderer::DistanceMergeSort(cbtF32* _distanceArray, cbtU32* _indexArray, cbtU32 _numElements)
{
    if (_numElements <= 1)
    {
        return;
    }

    cbtF32* tempDistanceBuffer = cbtNew cbtF32[_numElements];
    cbtU32* tempIndexBuffer = cbtNew cbtU32[_numElements];

    cbtU32 index = 0;
    cbtU32 mid = (_numElements >> 1);

    cbtU32 left = 0;
    cbtU32 right = mid;
    DistanceMergeSort(_distanceArray, _indexArray, mid);
    DistanceMergeSort(_distanceArray + mid, _indexArray + mid, _numElements - mid);
    while (left < mid || right < _numElements)
    {
        if (left == mid)
        {
            tempDistanceBuffer[index] = _distanceArray[right];
            tempIndexBuffer[index] = _indexArray[right];
            ++right;
        }
        else if (right == _numElements)
        {
            tempDistanceBuffer[index] = _distanceArray[left];
            tempIndexBuffer[index] = _indexArray[left];
            ++left;
        }
        else if (_distanceArray[left] > _distanceArray[right])
        {
            tempDistanceBuffer[index] = _distanceArray[left];
            tempIndexBuffer[index] = _indexArray[left];
            ++left;
        }
        else
        {
            tempDistanceBuffer[index] = _distanceArray[right];
            tempIndexBuffer[index] = _indexArray[right];
            ++right;
        }

        ++index;
    }

    std::memcpy(_distanceArray, tempDistanceBuffer, _numElements * sizeof(cbtF32));
    std::memcpy(_indexArray, tempIndexBuffer, _numElements * sizeof(cbtU32));

    delete[] tempDistanceBuffer;
    delete[] tempIndexBuffer;
}

std::vector<cbtU32> CBTRenderer::SortTransparentObjects(const CBTMatrix4F& _viewProjectionMatrix)
{
    CBTTransform** objectTransformArray = m_Objects.GetArray<CBTTransform>();
    CBTGraphics** objectGraphicsArray = m_Objects.GetArray<CBTGraphics>();

    std::vector<cbtF32> distance;
    std::vector<cbtU32> objects;
    for (cbtU32 i = 0; i < m_Transparent.size(); ++i)
    {
        CBTTransform* transform = objectTransformArray[m_Transparent[i]];
        CBTGraphics* graphics = objectGraphicsArray[m_Transparent[i]];
        CBTMatrix4F modelMatrix = transform->GetGlobalModelMatrix();
        const CBTBoundingBox& boundingBox = graphics->GetMaterial()->GetMesh()->GetBoundingBox();

        if (InViewFrustum(_viewProjectionMatrix, modelMatrix, boundingBox))
        {
            distance.push_back(GetObjectDistanceToCamera(_viewProjectionMatrix, modelMatrix, boundingBox));
            objects.push_back(m_Transparent[i]);
        }
    }
    DistanceMergeSort(&distance[0], &objects[0], (cbtU32)objects.size());

    return objects;
}

void CBTRenderer::RenderGPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, const CBTMatrix4F& _viewProjectionMatrix, CBTCamera* _camCamera)
{
    CBTFrameBuffer::Bind(m_GBuffer);

    CBTRenderAPI::SetStencilTest(true);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::ALWAYS, CBT_STENCIL_OPAQUE);
    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::REPLACE);

    CBTTransform** transformArray = m_Objects.GetArray<CBTTransform>();
    for (std::unordered_map<CBTMaterial*, std::vector<cbtU32>>::iterator iter = m_Deferred.begin(); iter != m_Deferred.end(); ++iter)
    {
        CBTMaterial* material = iter->first;
        std::vector<cbtU32>& arrayIndices = iter->second;

        // Use the shader.
        CBTShaderProgram* shader = material->GetShader();
        shader->UseProgram();

        // Set textures
        shader->SetTexture(CBT_TEXTURE_ALBEDO, material->GetTextureAlbedo());
        shader->SetTexture(CBT_TEXTURE_NORMAL, material->GetTextureNormal());
        shader->SetTexture(CBT_TEXTURE_SPECULAR, material->GetTextureSpecular());
        shader->SetTexture(CBT_TEXTURE_GLOSS, material->GetTextureGloss());
        shader->SetTexture(CBT_TEXTURE_DISPLACEMENT, material->GetTextureDisplacement());

        // Set the shader uniforms.
        shader->SetUniform(CBT_U_TEXTURE_ALBEDO_ENABLED, material->GetTextureAlbedo() != nullptr);
        shader->SetUniform(CBT_U_TEXTURE_NORMAL_ENABLED, material->GetTextureNormal() != nullptr);
        shader->SetUniform(CBT_U_TEXTURE_SPECULAR_ENABLED, material->GetTextureSpecular() != nullptr);
        shader->SetUniform(CBT_U_TEXTURE_GLOSS_ENABLED, material->GetTextureGloss() != nullptr);
        shader->SetUniform(CBT_U_TEXTURE_DISPLACEMENT_ENABLED, material->GetTextureDisplacement() != nullptr);

        shader->SetUniform(CBT_U_MATRIX_PROJECTION, false, _projectionMatrix);
        shader->SetUniform(CBT_U_TEXTURE_OFFSET, material->GetTextureOffset());
        shader->SetUniform(CBT_U_TEXTURE_SCALE, material->GetTextureScale());

        shader->SetUniform(CBT_U_AMBIENT_COLOR, material->GetAmbientColor());
        shader->SetUniform(CBT_U_ALBEDO_COLOR, material->GetAlbedoColor());
        shader->SetUniform(CBT_U_SPECULAR_COLOR, material->GetSpecularColor());
        shader->SetUniform(CBT_U_GLOSS, material->GetGloss());

        shader->SetUniform(CBT_U_DISPLACEMENT_SCALE, material->GetDisplacementScale());
        shader->SetUniform(CBT_U_MIN_DISPLACEMENT_SAMPLE, material->GetMinDisplacementSamples());
        shader->SetUniform(CBT_U_MAX_DISPLACEMENT_SAMPLE, material->GetMaxDisplacementSamples());

        shader->SetUniform(CBT_U_BUFFER_WIDTH, m_BufferWidth); // Ensure that this is a signed int, same as in the shader.
        shader->SetUniform(CBT_U_BUFFER_HEIGHT, m_BufferHeight); // Ensure that this is a signed int, same as in the shader.
        shader->SetUniform(CBT_U_NEAR_PLANE, _camCamera->GetNearPlane());
        shader->SetUniform(CBT_U_FAR_PLANE, _camCamera->GetFarPlane());

        // Bind the mesh.
        CBTMesh* mesh = material->GetMesh();
        mesh->Bind();

        // Set the mesh instance data.
        CBTMeshInstance* meshInstances = cbtNew CBTMeshInstance[arrayIndices.size()];
        cbtU32 numVisible = 0;
        for (cbtU32 n = 0; n < (cbtU32)arrayIndices.size(); ++n)
        {
            CBTTransform* transform = transformArray[arrayIndices[n]];
            CBTMatrix4F modelMatrix = transform->GetGlobalModelMatrix();
            CBTMatrix4F modelViewMatrix = _viewMatrix * modelMatrix;
            CBTMatrix3F normalMatrix = CBTMatrixUtil::GetTransposeMatrix(CBTMatrixUtil::GetInverseMatrix(CBTMatrixUtil::GetMinorMatrix(modelViewMatrix, 3, 3)));

            // Frustum Culling
            if (InViewFrustum(_viewProjectionMatrix, modelMatrix, mesh->GetBoundingBox()))
            {
                meshInstances[numVisible].SetModelViewMatrix(modelViewMatrix);
                meshInstances[numVisible].SetNormalMatrix(normalMatrix);
                ++numVisible;
            }
        }
        mesh->SetInstanceData(numVisible, meshInstances);
        delete[] meshInstances;

        // Draw Mesh
        CBTRenderAPI::DrawElementsInstanced(mesh->GetIndexCount(), numVisible);
    }

    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::KEEP);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::ALWAYS, 0, 0xFF);
    CBTRenderAPI::SetStencilTest(false);
}

void CBTRenderer::RenderLPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, CBTCamera* _camCamera, CBTTransform* _camTransform)
{
    CBTFrameBuffer::Bind(m_LBuffer);

    CBTRenderAPI::SetDepthTest(false);
    CBTRenderAPI::SetDepthWrite(false);

    // Render Lights
    CBTShaderProgram* shader = _camCamera->GetLightingShader();
    shader->UseProgram();

    // Set Texture(s)
    shader->SetTexture(CBT_GBUFFER_POSITION_CAMERA_SPACE, m_GBuffer->GetColorAttachment((cbtU32)CBTGBuffer::POSITION_CAMERA_SPACE));
    shader->SetTexture(CBT_GBUFFER_NORMAL_CAMERA_SPACE, m_GBuffer->GetColorAttachment((cbtU32)CBTGBuffer::NORMAL_CAMERA_SPACE));
    shader->SetTexture(CBT_GBUFFER_AMBIENT_COLOR, m_GBuffer->GetColorAttachment((cbtU32)CBTGBuffer::AMBIENT_COLOR));
    shader->SetTexture(CBT_GBUFFER_ALBEDO_COLOR, m_GBuffer->GetColorAttachment((cbtU32)CBTGBuffer::ALBEDO_COLOR));
    shader->SetTexture(CBT_GBUFFER_SPECULAR_COLOR, m_GBuffer->GetColorAttachment((cbtU32)CBTGBuffer::SPECULAR_COLOR));
    shader->SetTexture(CBT_GBUFFER_GLOSS, m_GBuffer->GetColorAttachment((cbtU32)CBTGBuffer::GLOSS));

    // Set Uniform(s)
    shader->SetUniform(CBT_U_LIGHTING_ENABLED, CBTLight::IsLightingEnabled());

    shader->SetUniform(CBT_U_BUFFER_WIDTH, m_BufferWidth); // Ensure that this is a signed int, same as in the shader.
    shader->SetUniform(CBT_U_BUFFER_HEIGHT, m_BufferHeight); // Ensure that this is a signed int, same as in the shader.
    shader->SetUniform(CBT_U_NEAR_PLANE, _camCamera->GetNearPlane());
    shader->SetUniform(CBT_U_FAR_PLANE, _camCamera->GetFarPlane());

    CBTVector3F camRight = _camTransform->GetRight();
    CBTVector3F camUp = _camTransform->GetUp();
    CBTVector3F camForward = _camTransform->GetForward();
    cbtU32 numLights = m_Lights.GetArraySize();
    cbtU32 numPasses = numLights / CBT_MAX_LIGHTS + 1;
    CBTLight** lightLightArray = m_Lights.GetArray<CBTLight>();
    CBTTransform** lightTransformArray = m_Lights.GetArray<CBTTransform>();
    for (cbtU32 i = 0; i < numPasses; ++i)
    {
        cbtS32 activeLights = 0; // Make sure that is an int and not an unsigned int since in the shader it is an int.
        for (cbtU32 j = 0; j < CBT_MAX_LIGHTS; ++j)
        {
            cbtU32 k = i * CBT_MAX_LIGHTS + j;
            if (k == numLights) { break; }

            CBTLight* light = lightLightArray[k];
            CBTTransform* transform = lightTransformArray[k];
            CBTMatrix4F positionMatrix = _viewMatrix * transform->GetGlobalModelMatrix();;
            CBTVector3F directionVector;
            directionVector.m_X = Dot(camRight, transform->GetForward());
            directionVector.m_Y = Dot(camUp, transform->GetForward());
            directionVector.m_Z = Dot(camForward, transform->GetForward());
            Normalize(directionVector);
            
            shader->SetUniform(j + CBT_U_LIGHT_MODE0, light->GetMode());
            shader->SetUniform(j + CBT_U_LIGHT_POWER0, light->GetPower());
            shader->SetUniform(j + CBT_U_LIGHT_COLOR0, light->GetColor());
            shader->SetUniform(j + CBT_U_LIGHT_ATTENUATION_CONSTANT0, light->GetAttenuationConstant());
            shader->SetUniform(j + CBT_U_LIGHT_ATTENUATION_LINEAR0, light->GetAttenuationLinear());
            shader->SetUniform(j + CBT_U_LIGHT_ATTENUATION_QUADRATIC0, light->GetAttenuationQuadratic());
            shader->SetUniform(j + CBT_U_LIGHT_SPOTLIGHT_INNER_COSINE0, light->GetSpotlightInnerConsine());
            shader->SetUniform(j + CBT_U_LIGHT_SPOTLIGHT_OUTER_COSINE0, light->GetSpotlightOuterConsine());
            shader->SetUniform(j + CBT_U_LIGHT_POSITION_CAMERA_SPACE0, CBTVector3F(positionMatrix[3][0], positionMatrix[3][1], positionMatrix[3][2]));
            shader->SetUniform(j + CBT_U_LIGHT_DIRECTION_CAMERA_SPACE0, directionVector);
            
            ++activeLights;
        }

        shader->SetTexture(CBT_LBUFFER_LIGHT_DIFFUSE, m_LBuffer->GetColorAttachment((cbtU32)CBTLBuffer::LIGHT_DIFFUSE));
        shader->SetTexture(CBT_LBUFFER_LIGHT_SPECULAR, m_LBuffer->GetColorAttachment((cbtU32)CBTLBuffer::LIGHT_SPECULAR));
        shader->SetUniform(CBT_U_ACTIVE_LIGHTS, activeLights);

        m_ScreenQuad->Bind();
        m_ScreenQuad->SetInstanceData(0, nullptr);

        // Draw Mesh
        CBTRenderAPI::DrawElementsInstanced(m_ScreenQuad->GetIndexCount(), 1);
    }

    CBTRenderAPI::SetDepthTest(true);
    CBTRenderAPI::SetDepthWrite(true);
}

void CBTRenderer::RenderFPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, const CBTMatrix4F& _viewProjectionMatrix, CBTCamera* _camCamera, CBTTransform* _camTransform)
{
    CBTFrameBuffer::Bind(m_FBuffer);

    CBTVector3F camRight = _camTransform->GetRight();
    CBTVector3F camUp = _camTransform->GetUp();
    CBTVector3F camForward = _camTransform->GetForward();
    CBTTransform** lightTransformArray = m_Lights.GetArray<CBTTransform>();
    CBTLight** lightLightArray = m_Lights.GetArray<CBTLight>();
    CBTTransform** objectTransformArray = m_Objects.GetArray<CBTTransform>();
    CBTGraphics** objectGraphicsArray = m_Objects.GetArray<CBTGraphics>();

CBT_REGION(RENDER_OPAQUE)
    // Opaque
    CBTRenderAPI::SetStencilTest(true);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::ALWAYS, CBT_STENCIL_OPAQUE);
    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::REPLACE);

    CBTMaterial* previousMaterial = nullptr;
    for (std::unordered_map<CBTMaterial*, std::vector<cbtU32>>::iterator iter = m_Forward.begin(); iter != m_Forward.end(); ++iter)
    {
        CBTMaterial* material = iter->first;
        CBTShaderProgram* shader = material->GetShader();

        if (previousMaterial != material)
        {
            previousMaterial = material;
            shader->UseProgram();

            // Set textures
            shader->SetTexture(CBT_TEXTURE_ALBEDO, material->GetTextureAlbedo());
            shader->SetTexture(CBT_TEXTURE_NORMAL, material->GetTextureNormal());
            shader->SetTexture(CBT_TEXTURE_SPECULAR, material->GetTextureSpecular());
            shader->SetTexture(CBT_TEXTURE_GLOSS, material->GetTextureGloss());
            shader->SetTexture(CBT_TEXTURE_DISPLACEMENT, material->GetTextureDisplacement());

            // Set the shader uniforms.
            shader->SetUniform(CBT_U_TEXTURE_ALBEDO_ENABLED, material->GetTextureAlbedo() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_NORMAL_ENABLED, material->GetTextureNormal() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_SPECULAR_ENABLED, material->GetTextureSpecular() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_GLOSS_ENABLED, material->GetTextureGloss() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_DISPLACEMENT_ENABLED, material->GetTextureDisplacement() != nullptr);

            shader->SetUniform(CBT_U_MATRIX_PROJECTION, false, _projectionMatrix);
            shader->SetUniform(CBT_U_TEXTURE_OFFSET, material->GetTextureOffset());
            shader->SetUniform(CBT_U_TEXTURE_SCALE, material->GetTextureScale());

            shader->SetUniform(CBT_U_AMBIENT_COLOR, material->GetAmbientColor());
            shader->SetUniform(CBT_U_ALBEDO_COLOR, material->GetAlbedoColor());
            shader->SetUniform(CBT_U_SPECULAR_COLOR, material->GetSpecularColor());
            shader->SetUniform(CBT_U_GLOSS, material->GetGloss());

            shader->SetUniform(CBT_U_DISPLACEMENT_SCALE, material->GetDisplacementScale());
            shader->SetUniform(CBT_U_MIN_DISPLACEMENT_SAMPLE, material->GetMinDisplacementSamples());
            shader->SetUniform(CBT_U_MAX_DISPLACEMENT_SAMPLE, material->GetMaxDisplacementSamples());

            shader->SetUniform(CBT_U_LIGHTING_ENABLED, CBTLight::IsLightingEnabled());

            shader->SetUniform(CBT_U_BUFFER_WIDTH, m_BufferWidth); // Ensure that this is a signed int, same as in the shader.
            shader->SetUniform(CBT_U_BUFFER_HEIGHT, m_BufferHeight); // Ensure that this is a signed int, same as in the shader.
            shader->SetUniform(CBT_U_NEAR_PLANE, _camCamera->GetNearPlane());
            shader->SetUniform(CBT_U_FAR_PLANE, _camCamera->GetFarPlane());

            cbtS32 activeLights = 0; // Make sure that is an int and not an unsigned int since in the shader it is an int.
            for (cbtU32 i = 0; i < CBT_MAX_LIGHTS; ++i)
            {
                if (i == m_Lights.GetArraySize()) { break; }

                CBTLight* light = lightLightArray[i];
                CBTTransform* transform = lightTransformArray[i];
                CBTMatrix4F positionMatrix = _viewMatrix * transform->GetGlobalModelMatrix();;
                CBTVector3F directionVector;
                directionVector.m_X = Dot(camRight, transform->GetForward());
                directionVector.m_Y = Dot(camUp, transform->GetForward());
                directionVector.m_Z = Dot(camForward, transform->GetForward());
                Normalize(directionVector);

                shader->SetUniform(i + CBT_U_LIGHT_MODE0, light->GetMode());
                shader->SetUniform(i + CBT_U_LIGHT_POWER0, light->GetPower());
                shader->SetUniform(i + CBT_U_LIGHT_COLOR0, light->GetColor());
                shader->SetUniform(i + CBT_U_LIGHT_ATTENUATION_CONSTANT0, light->GetAttenuationConstant());
                shader->SetUniform(i + CBT_U_LIGHT_ATTENUATION_LINEAR0, light->GetAttenuationLinear());
                shader->SetUniform(i + CBT_U_LIGHT_ATTENUATION_QUADRATIC0, light->GetAttenuationQuadratic());
                shader->SetUniform(i + CBT_U_LIGHT_SPOTLIGHT_INNER_COSINE0, light->GetSpotlightInnerConsine());
                shader->SetUniform(i + CBT_U_LIGHT_SPOTLIGHT_OUTER_COSINE0, light->GetSpotlightOuterConsine());
                shader->SetUniform(i + CBT_U_LIGHT_POSITION_CAMERA_SPACE0, CBTVector3F(positionMatrix[3][0], positionMatrix[3][1], positionMatrix[3][2]));
                shader->SetUniform(i + CBT_U_LIGHT_DIRECTION_CAMERA_SPACE0, directionVector);

                ++activeLights;
            }
            shader->SetUniform(CBT_U_ACTIVE_LIGHTS, activeLights);
        }

        // Bind the mesh.
        CBTMesh* mesh = material->GetMesh();
        mesh->Bind();

        // Set the mesh instance data.
        std::vector<cbtU32>& arrayIndices = iter->second;
        CBTMeshInstance* meshInstances = cbtNew CBTMeshInstance[arrayIndices.size()];
        cbtU32 numVisible = 0;
        for (cbtU32 n = 0; n < (cbtU32)arrayIndices.size(); ++n)
        {
            CBTTransform* transform = objectTransformArray[arrayIndices[n]];
            CBTMatrix4F modelMatrix = transform->GetGlobalModelMatrix();
            CBTMatrix4F modelViewMatrix = _viewMatrix * modelMatrix;
            CBTMatrix3F normalMatrix = CBTMatrixUtil::GetTransposeMatrix(CBTMatrixUtil::GetInverseMatrix(CBTMatrixUtil::GetMinorMatrix(modelViewMatrix, 3, 3)));

            if (InViewFrustum(_viewProjectionMatrix, modelMatrix, mesh->GetBoundingBox()))
            {
                meshInstances[numVisible].SetModelViewMatrix(modelViewMatrix);
                meshInstances[numVisible].SetNormalMatrix(normalMatrix);
                ++numVisible;
            }
        }
        mesh->SetInstanceData(numVisible, meshInstances);
        delete[] meshInstances;

        // Draw Mesh
        CBTRenderAPI::DrawElementsInstanced(mesh->GetIndexCount(), numVisible);
    }

    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::KEEP);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::ALWAYS, 0, 0xFF);
    CBTRenderAPI::SetStencilTest(false);
CBT_END_REGION(RENDER_OPAQUE)

CBT_REGION(RENDER_SKYBOX)
    CBTRenderAPI::SetDepthTest(false);
    CBTRenderAPI::SetDepthWrite(false);

    CBTRenderAPI::SetStencilTest(true);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::NOTEQUAL, CBT_STENCIL_OPAQUE);
    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::KEEP);

    // Render Skybox
    CBTShaderProgram* skyboxShader = _camCamera->GetSkyboxShader();
    skyboxShader->UseProgram();
    skyboxShader->SetTexture(CBT_TEXTURE_SKYBOX, _camCamera->GetSkyboxTexture());
    skyboxShader->SetUniform(CBT_U_MATRIX_PROJECTION, false, _projectionMatrix);
    skyboxShader->SetUniform(CBT_U_SKYBOX_COLOR, _camCamera->GetSkyboxColor());
    skyboxShader->SetUniform(CBT_U_TEXTURE_SKYBOX_ENABLED, _camCamera->GetSkyboxTexture() != nullptr);

    CBTMatrix4F modelMatrix = CBTMatrixUtil::GetTranslationMatrix(_camTransform->GetGlobalPosition());
    CBTMatrix4F modelViewMatrix = _viewMatrix * modelMatrix;
    CBTMatrix3F normalMatrix = CBTMatrixUtil::GetTransposeMatrix(CBTMatrixUtil::GetInverseMatrix(CBTMatrixUtil::GetMinorMatrix(modelViewMatrix, 3, 3)));

    m_SkyboxMesh->Bind();
    CBTMeshInstance meshInstance;
    meshInstance.SetModelViewMatrix(modelViewMatrix);
    meshInstance.SetNormalMatrix(normalMatrix);
    m_SkyboxMesh->SetInstanceData(1, &meshInstance);

    // Draw Mesh
    CBTRenderAPI::DrawElementsInstanced(m_SkyboxMesh->GetIndexCount(), 1);

    CBTRenderAPI::SetStencilOp(CBTStencilOp::KEEP, CBTStencilOp::KEEP, CBTStencilOp::KEEP);
    CBTRenderAPI::SetStencilFunc(CBTCompareFunc::ALWAYS, 0, 0xFF);
    CBTRenderAPI::SetStencilTest(false);

    CBTRenderAPI::SetDepthTest(true);
    CBTRenderAPI::SetDepthWrite(true);
CBT_END_REGION(RENDER_SKYBOX)

CBT_REGION(RENDER_TRANSPARENT)
    CBTRenderAPI::SetBlendTest(true);

    std::vector<cbtU32> sorted = SortTransparentObjects(_viewProjectionMatrix);
    CBTMaterial* previousMaterial = nullptr;
    for (cbtU32 i = 0; i < sorted.size(); ++i)
    {
        CBTTransform* transform = objectTransformArray[sorted[i]];
        CBTGraphics* graphics = objectGraphicsArray[sorted[i]];
        CBTMaterial* material = graphics->GetMaterial();
        CBTShaderProgram* shader = material->GetShader();

        if (previousMaterial != material)
        {
            previousMaterial = material;
            shader->UseProgram();

            // Set textures
            shader->SetTexture(CBT_TEXTURE_ALBEDO, material->GetTextureAlbedo());
            shader->SetTexture(CBT_TEXTURE_NORMAL, material->GetTextureNormal());
            shader->SetTexture(CBT_TEXTURE_SPECULAR, material->GetTextureSpecular());
            shader->SetTexture(CBT_TEXTURE_GLOSS, material->GetTextureGloss());
            shader->SetTexture(CBT_TEXTURE_DISPLACEMENT, material->GetTextureDisplacement());

            // Set the shader uniforms.
            shader->SetUniform(CBT_U_TEXTURE_ALBEDO_ENABLED, material->GetTextureAlbedo() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_NORMAL_ENABLED, material->GetTextureNormal() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_SPECULAR_ENABLED, material->GetTextureSpecular() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_GLOSS_ENABLED, material->GetTextureGloss() != nullptr);
            shader->SetUniform(CBT_U_TEXTURE_DISPLACEMENT_ENABLED, material->GetTextureDisplacement() != nullptr);

            shader->SetUniform(CBT_U_MATRIX_PROJECTION, false, _projectionMatrix);
            shader->SetUniform(CBT_U_TEXTURE_OFFSET, material->GetTextureOffset());
            shader->SetUniform(CBT_U_TEXTURE_SCALE, material->GetTextureScale());

            shader->SetUniform(CBT_U_AMBIENT_COLOR, material->GetAmbientColor());
            shader->SetUniform(CBT_U_ALBEDO_COLOR, material->GetAlbedoColor());
            shader->SetUniform(CBT_U_SPECULAR_COLOR, material->GetSpecularColor());
            shader->SetUniform(CBT_U_GLOSS, material->GetGloss());

            shader->SetUniform(CBT_U_DISPLACEMENT_SCALE, material->GetDisplacementScale());
            shader->SetUniform(CBT_U_MIN_DISPLACEMENT_SAMPLE, material->GetMinDisplacementSamples());
            shader->SetUniform(CBT_U_MAX_DISPLACEMENT_SAMPLE, material->GetMaxDisplacementSamples());

            shader->SetUniform(CBT_U_LIGHTING_ENABLED, CBTLight::IsLightingEnabled());

            shader->SetUniform(CBT_U_BUFFER_WIDTH, m_BufferWidth); // Ensure that this is a signed int, same as in the shader.
            shader->SetUniform(CBT_U_BUFFER_HEIGHT, m_BufferHeight); // Ensure that this is a signed int, same as in the shader.
            shader->SetUniform(CBT_U_NEAR_PLANE, _camCamera->GetNearPlane());
            shader->SetUniform(CBT_U_FAR_PLANE, _camCamera->GetFarPlane());

            cbtS32 activeLights = 0; // Make sure that is an int and not an unsigned int since in the shader it is an int.
            for (cbtU32 i = 0; i < CBT_MAX_LIGHTS; ++i)
            {
                if (i == m_Lights.GetArraySize()) { break; }

                CBTLight* light = lightLightArray[i];
                CBTTransform* transform = lightTransformArray[i];
                CBTMatrix4F positionMatrix = _viewMatrix * transform->GetGlobalModelMatrix();;
                CBTVector3F directionVector;
                directionVector.m_X = Dot(camRight, transform->GetForward());
                directionVector.m_Y = Dot(camUp, transform->GetForward());
                directionVector.m_Z = Dot(camForward, transform->GetForward());
                Normalize(directionVector);

                shader->SetUniform(i + CBT_U_LIGHT_MODE0, light->GetMode());
                shader->SetUniform(i + CBT_U_LIGHT_POWER0, light->GetPower());
                shader->SetUniform(i + CBT_U_LIGHT_COLOR0, light->GetColor());
                shader->SetUniform(i + CBT_U_LIGHT_ATTENUATION_CONSTANT0, light->GetAttenuationConstant());
                shader->SetUniform(i + CBT_U_LIGHT_ATTENUATION_LINEAR0, light->GetAttenuationLinear());
                shader->SetUniform(i + CBT_U_LIGHT_ATTENUATION_QUADRATIC0, light->GetAttenuationQuadratic());
                shader->SetUniform(i + CBT_U_LIGHT_SPOTLIGHT_INNER_COSINE0, light->GetSpotlightInnerConsine());
                shader->SetUniform(i + CBT_U_LIGHT_SPOTLIGHT_OUTER_COSINE0, light->GetSpotlightOuterConsine());
                shader->SetUniform(i + CBT_U_LIGHT_POSITION_CAMERA_SPACE0, CBTVector3F(positionMatrix[3][0], positionMatrix[3][1], positionMatrix[3][2]));
                shader->SetUniform(i + CBT_U_LIGHT_DIRECTION_CAMERA_SPACE0, directionVector);

                ++activeLights;
            }
            shader->SetUniform(CBT_U_ACTIVE_LIGHTS, activeLights);
        }

        // Bind the mesh.
        CBTMesh* mesh = material->GetMesh();
        mesh->Bind();

        CBTMatrix4F modelViewMatrix = _viewMatrix * transform->GetGlobalModelMatrix();
        CBTMatrix3F normalMatrix = CBTMatrixUtil::GetTransposeMatrix(CBTMatrixUtil::GetInverseMatrix(CBTMatrixUtil::GetMinorMatrix(modelViewMatrix, 3, 3)));
        CBTMeshInstance meshInstance;
        meshInstance.SetModelViewMatrix(modelViewMatrix);
        meshInstance.SetNormalMatrix(normalMatrix);
        mesh->SetInstanceData(1, &meshInstance);

        // Draw Mesh
        CBTRenderAPI::DrawElementsInstanced(mesh->GetIndexCount(), 1);
    }

    CBTRenderAPI::SetBlendTest(false);
CBT_END_REGION(RENDER_TRANSPARENT)
}

void CBTRenderer::RenderPPass(const CBTMatrix4F& _viewMatrix, const CBTMatrix4F& _projectionMatrix, const CBTMatrix4F& _viewProjectionMatrix, CBTCamera* _camCamera, CBTTransform* _camTransform)
{
    CBTFrameBuffer::Bind(m_PBuffer);

    CBTRenderAPI::SetDepthTest(false);
    CBTRenderAPI::SetDepthWrite(false);

    // Render Lights
    CBTShaderProgram** shaders = _camCamera->GetPostProcessShaders();
    cbtU32 numShaders = _camCamera->GetPostProcessShaderCount();
    for (cbtU32 i = 0; i < numShaders; ++i)
    {
        CBTShaderProgram* shader = shaders[i];
        shader->UseProgram();

        // Set Texture(s)
        shader->SetTexture(CBT_FBUFFER_POSITION_CAMERA_SPACE, m_FBuffer->GetColorAttachment((cbtU32)CBTFBuffer::POSITION_CAMERA_SPACE));
        shader->SetTexture(CBT_FBUFFER_NORMAL_CAMERA_SPACE, m_FBuffer->GetColorAttachment((cbtU32)CBTFBuffer::NORMAL_CAMERA_SPACE));
        shader->SetTexture(CBT_FBUFFER_DEPTH_STENCIL, m_FBuffer->GetDepthStencilAttachment());
        shader->SetTexture(CBT_PBUFFER_COMPOSITE, m_PBuffer->GetColorAttachment((cbtU32)CBTPBuffer::COMPOSITE));

        // Set Uniform(s)
        shader->SetUniform(CBT_U_BUFFER_WIDTH, m_BufferWidth); // Ensure that this is a signed int, same as in the shader.
        shader->SetUniform(CBT_U_BUFFER_HEIGHT, m_BufferHeight); // Ensure that this is a signed int, same as in the shader.
        shader->SetUniform(CBT_U_NEAR_PLANE, _camCamera->GetNearPlane());
        shader->SetUniform(CBT_U_FAR_PLANE, _camCamera->GetFarPlane());

        m_ScreenQuad->Bind();
        m_ScreenQuad->SetInstanceData(0, nullptr);

        // Draw Mesh
        CBTRenderAPI::DrawElementsInstanced(m_ScreenQuad->GetIndexCount(), 1);
    }

    CBTRenderAPI::SetDepthTest(true);
    CBTRenderAPI::SetDepthWrite(true);
}

void CBTRenderer::Render()
{
    SortRenderObjects();

    CBTCamera** cameraArray = m_Cameras.GetArray<CBTCamera>();
    CBTTransform** transformArray = m_Cameras.GetArray<CBTTransform>();
    for (cbtU32 i = 0; i < m_Cameras.GetArraySize(); ++i)
    {
        CBTCamera* camCamera = cameraArray[i];
        CBTTransform* camTransform = transformArray[i];

        CBTMatrix4F viewMatrix = CBTMatrixUtil::GetViewMatrix(camTransform->GetForward(), camTransform->GetUp(), camTransform->GetGlobalPosition());
        CBTMatrix4F projectionMatrix = camCamera->GetProjectionMatrix();
        CBTMatrix4F viewProjectionMatrix = projectionMatrix * viewMatrix;
        const CBTViewport& viewport = camCamera->GetViewport();

        cbtS32 bufferBottomX = (cbtS32)(viewport.m_BottomX * (cbtF32)m_BufferWidth);
        cbtS32 bufferBottomY = (cbtS32)(viewport.m_BottomY * (cbtF32)m_BufferHeight);
        cbtS32 bufferTopX = (cbtS32)(viewport.m_TopX * (cbtF32)m_BufferWidth);
        cbtS32 bufferTopY = (cbtS32)(viewport.m_TopY * (cbtF32)m_BufferHeight);

        cbtS32 windowBottomX = (cbtS32)(viewport.m_BottomX * (cbtF32)m_WindowWidth);
        cbtS32 windowBottomY = (cbtS32)(viewport.m_BottomY * (cbtF32)m_WindowHeight);
        cbtS32 windowTopX = (cbtS32)(viewport.m_TopX * (cbtF32)m_WindowWidth);
        cbtS32 windowTopY = (cbtS32)(viewport.m_TopY * (cbtF32)m_WindowHeight);

        CBTRenderAPI::SetScissorTest(true);
        CBTRenderAPI::SetScissor(bufferBottomX, bufferBottomY, bufferTopX - bufferBottomX, bufferTopY - bufferBottomY);
        CBTFrameBuffer::ClearAttachmentsAll(m_GBuffer);
        CBTFrameBuffer::ClearAttachmentsAll(m_LBuffer);
        CBTFrameBuffer::ClearAttachmentsAll(m_FBuffer);
        CBTFrameBuffer::ClearAttachmentsAll(m_PBuffer);
        CBTRenderAPI::SetScissorTest(false);

        // Geometry Pass
        CBTRenderAPI::SetViewPort(bufferBottomX, bufferBottomY, bufferTopX - bufferBottomX, bufferTopY - bufferBottomY);
        m_GBuffer->SetDrawColorBuffersAll();
        RenderGPass(viewMatrix, projectionMatrix, viewProjectionMatrix, camCamera);

        // Light Pass
        CBTRenderAPI::SetViewPort(0, 0, m_BufferWidth, m_BufferHeight);
        CBTFrameBuffer::Blit(m_GBuffer, m_LBuffer, false, true, true, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY); // Copy GBuffer DEPTH_STENCIL
        m_LBuffer->SetDrawColorBuffersAll();
        RenderLPass(viewMatrix, projectionMatrix, camCamera, camTransform);

        // Forward Pass
        CBTRenderAPI::SetViewPort(bufferBottomX, bufferBottomY, bufferTopX - bufferBottomX, bufferTopY - bufferBottomY);

        CBTFrameBuffer::Blit(m_GBuffer, m_FBuffer, false, true, true, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY); // Copy GBuffer DEPTH_STENCIL

        m_GBuffer->SetReadColorBuffer((cbtU32)CBTGBuffer::POSITION_CAMERA_SPACE);
        m_FBuffer->SetDrawColorBuffer((cbtU32)CBTFBuffer::POSITION_CAMERA_SPACE);
        CBTFrameBuffer::Blit(m_GBuffer, m_FBuffer, true, false, false, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY); // Copy GBuffer POSITION_CAMERA_SPACE

        m_GBuffer->SetReadColorBuffer((cbtU32)CBTGBuffer::NORMAL_CAMERA_SPACE);
        m_FBuffer->SetDrawColorBuffer((cbtU32)CBTFBuffer::NORMAL_CAMERA_SPACE);
        CBTFrameBuffer::Blit(m_GBuffer, m_FBuffer, true, false, false, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY); // Copy GBuffer NORMAL_CAMERA_SPACE

        m_LBuffer->SetReadColorBuffer((cbtU32)CBTLBuffer::COMPOSITE);
        m_FBuffer->SetDrawColorBuffer((cbtU32)CBTFBuffer::COMPOSITE);
        CBTFrameBuffer::Blit(m_LBuffer, m_FBuffer, true, false, false, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY); // Copy LBuffer COMPOSITE

        m_FBuffer->SetDrawColorBuffersAll();
        RenderFPass(viewMatrix, projectionMatrix, viewProjectionMatrix, camCamera, camTransform);

        // Post Process Pass
        CBTRenderAPI::SetViewPort(0, 0, m_BufferWidth, m_BufferHeight);

        m_FBuffer->SetReadColorBuffer((cbtU32)CBTFBuffer::COMPOSITE);
        m_PBuffer->SetDrawColorBuffer((cbtU32)CBTPBuffer::COMPOSITE);
        CBTFrameBuffer::Blit(m_FBuffer, m_PBuffer, true, false, false, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY, bufferBottomX, bufferBottomY, bufferTopX, bufferTopY); // Copy LBuffer COMPOSITE

        m_PBuffer->SetDrawColorBuffersAll();
        RenderPPass(viewMatrix, projectionMatrix, viewProjectionMatrix, camCamera, camTransform);
    }

    // Render To Screen
    m_PBuffer->SetReadColorBuffer((cbtU32)CBTPBuffer::COMPOSITE);
    CBTFrameBuffer::Blit(m_PBuffer, nullptr, true, false, false, 0, 0, m_BufferWidth, m_BufferHeight, 0, 0, m_WindowWidth, m_WindowHeight);

    ClearRenderObjects();

    CBTRenderEngine::GetInstance()->GetWindow()->SwapBuffers();

    CBTRenderAPI::SetScissorTest(false);
}

NS_CBT_END