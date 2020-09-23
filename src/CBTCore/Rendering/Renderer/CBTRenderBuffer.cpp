// Include CBT
#include "CBTRenderBuffer.h"

NS_CBT_BEGIN

CBTFrameBuffer* CreateGBuffer(cbtS32 _width, cbtS32 _height)
{
    CBTFrameBuffer* frameBuffer = CBTFrameBuffer::CreateFrameBuffer();

    CBTTexture* colors[(cbtU32)CBTGBuffer::NUM_COLOR_ATTACHMENTS];
    // Position Camera Space (Store the x, y and z as half floats).
    colors[(cbtU32)CBTGBuffer::POSITION_CAMERA_SPACE] = CBTTexture::CreateFrameBufferAttachment("GBuffer Position Camera Space", _width, _height, CBT_RGB16F);
    // Normal Camera Space (Store the x, y and z as half floats).
    colors[(cbtU32)CBTGBuffer::NORMAL_CAMERA_SPACE] = CBTTexture::CreateFrameBufferAttachment("GBuffer Normal Camera Space", _width, _height, CBT_RGB16F);
    // Ambient Color
    colors[(cbtU32)CBTGBuffer::AMBIENT_COLOR] = CBTTexture::CreateFrameBufferAttachment("GBuffer Ambient Color", _width, _height, CBT_RGBA8);
    // Alebedo Color
    colors[(cbtU32)CBTGBuffer::ALBEDO_COLOR] = CBTTexture::CreateFrameBufferAttachment("GBuffer Albedo Color", _width, _height, CBT_RGBA8);
    // Diffuse Color
    colors[(cbtU32)CBTGBuffer::SPECULAR_COLOR] = CBTTexture::CreateFrameBufferAttachment("GBuffer Specular Color", _width, _height, CBT_RGBA8);
    // Gloss
    colors[(cbtU32)CBTGBuffer::GLOSS] = CBTTexture::CreateFrameBufferAttachment("GBuffer Gloss", _width, _height, CBT_R32F);

    for (cbtU32 i = 0; i < sizeof(colors)/sizeof(colors[0]); ++i)
    {
        frameBuffer->AddColorAttachment(colors[i], i);
    }
    frameBuffer->SetDrawColorBuffersAll();

    CBTTexture* depthStencil = CBTTexture::CreateFrameBufferAttachment("GBuffer Depth Stencil", _width, _height, CBT_DEPTH24_STENCIL8);
    frameBuffer->AddDepthStencilAttachment(depthStencil);

    CBT_ASSERT(frameBuffer->IsComplete());
    return frameBuffer;
}

CBTFrameBuffer* CreateLBuffer(cbtS32 _width, cbtS32 _height)
{
    CBTFrameBuffer* frameBuffer = CBTFrameBuffer::CreateFrameBuffer();

    CBTTexture* colors[(cbtU32)CBTLBuffer::NUM_COLOR_ATTACHMENTS];
    // Color Output
    colors[(cbtU32)CBTLBuffer::COMPOSITE] = CBTTexture::CreateFrameBufferAttachment("LBuffer Composite", _width, _height, CBT_RGBA8);
    // Light Diffuse Color
    colors[(cbtU32)CBTLBuffer::LIGHT_DIFFUSE] = CBTTexture::CreateFrameBufferAttachment("LBuffer Light Diffuse", _width, _height, CBT_RGBA8);
    // Light Specular Color
    colors[(cbtU32)CBTLBuffer::LIGHT_SPECULAR] = CBTTexture::CreateFrameBufferAttachment("LBuffer Light Specular", _width, _height, CBT_RGBA8);

    for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
    {
        frameBuffer->AddColorAttachment(colors[i], i);
    }
    frameBuffer->SetDrawColorBuffersAll();

    CBTTexture* depthStencil = CBTTexture::CreateFrameBufferAttachment("LBuffer Depth Stencil", _width, _height, CBT_DEPTH24_STENCIL8);
    frameBuffer->AddDepthStencilAttachment(depthStencil);

    CBT_ASSERT(frameBuffer->IsComplete());
    return frameBuffer;
}

CBTFrameBuffer* CreateFBuffer(cbtS32 _width, cbtS32 _height)
{
    CBTFrameBuffer* frameBuffer = CBTFrameBuffer::CreateFrameBuffer();

    CBTTexture* colors[(cbtU32)CBTFBuffer::NUM_COLOR_ATTACHMENTS];

    // Color Output
    colors[(cbtU32)CBTFBuffer::COMPOSITE] = CBTTexture::CreateFrameBufferAttachment("FBuffer Composite", _width, _height, CBT_RGBA8);
    // Position Camera Space (Store the x, y and z as half floats).
    colors[(cbtU32)CBTFBuffer::POSITION_CAMERA_SPACE] = CBTTexture::CreateFrameBufferAttachment("FBuffer Position Camera Space", _width, _height, CBT_RGB16F);
    // Normal Camera Space (Store the x, y and z as half floats).
    colors[(cbtU32)CBTFBuffer::NORMAL_CAMERA_SPACE] = CBTTexture::CreateFrameBufferAttachment("FBuffer Normal Camera Space", _width, _height, CBT_RGB16F);

    for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
    {
        frameBuffer->AddColorAttachment(colors[i], i);
    }
    frameBuffer->SetDrawColorBuffersAll();

    CBTTexture* depthStencil = CBTTexture::CreateFrameBufferAttachment("Forward Buffer Depth Stencil", _width, _height, CBT_DEPTH24_STENCIL8);
    frameBuffer->AddDepthStencilAttachment(depthStencil);

    CBT_ASSERT(frameBuffer->IsComplete());
    return frameBuffer;
}

CBTFrameBuffer* CreatePBuffer(cbtS32 _width, cbtS32 _height)
{
    CBTFrameBuffer* frameBuffer = CBTFrameBuffer::CreateFrameBuffer();

    CBTTexture* colors[(cbtU32)CBTPBuffer::NUM_COLOR_ATTACHMENTS];

    // Color Output
    colors[(cbtU32)CBTPBuffer::COMPOSITE] = CBTTexture::CreateFrameBufferAttachment("PBuffer Composite Post", _width, _height, CBT_RGBA8);

    for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
    {
        frameBuffer->AddColorAttachment(colors[i], i);
    }
    frameBuffer->SetDrawColorBuffersAll();

    CBT_ASSERT(frameBuffer->IsComplete());
    return frameBuffer;
}

NS_CBT_END