// Include CBT
#include "cbtRenderBuffer.h"

NS_CBT_BEGIN

    cbtFrameBuffer* CreateGBuffer(cbtS32 _width, cbtS32 _height)
    {
        cbtFrameBuffer* frameBuffer = cbtFrameBuffer::CreateFrameBuffer();

        cbtTexture* colors[(cbtU32)cbtGBuffer::NUM_COLOR_ATTACHMENTS];
        // Position Camera Space (Store the x, y and z as half floats).
        colors[(cbtU32)cbtGBuffer::POSITION_CAMERA_SPACE] = cbtTexture::CreateFrameBufferAttachment(
                "GBuffer Position Camera Space", _width, _height, CBT_RGB16F);
        // Normal Camera Space (Store the x, y and z as half floats).
        colors[(cbtU32)cbtGBuffer::NORMAL_CAMERA_SPACE] = cbtTexture::CreateFrameBufferAttachment(
                "GBuffer Normal Camera Space", _width, _height, CBT_RGB16F);
        // Ambient Color
        colors[(cbtU32)cbtGBuffer::AMBIENT_COLOR] = cbtTexture::CreateFrameBufferAttachment("GBuffer Ambient Color",
                _width, _height,
                CBT_RGBA8);
        // Alebedo Color
        colors[(cbtU32)cbtGBuffer::ALBEDO_COLOR] = cbtTexture::CreateFrameBufferAttachment("GBuffer Albedo Color",
                _width, _height, CBT_RGBA8);
        // Diffuse Color
        colors[(cbtU32)cbtGBuffer::SPECULAR_COLOR] = cbtTexture::CreateFrameBufferAttachment("GBuffer Specular Color",
                _width, _height,
                CBT_RGBA8);
        // Gloss
        colors[(cbtU32)cbtGBuffer::GLOSS] = cbtTexture::CreateFrameBufferAttachment("GBuffer Gloss", _width, _height,
                CBT_R32F);

        for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
        {
            frameBuffer->AddColorAttachment(colors[i], i);
        }
        frameBuffer->SetDrawColorBuffersAll();

        cbtTexture* depthStencil = cbtTexture::CreateFrameBufferAttachment("GBuffer Depth Stencil", _width, _height,
                CBT_DEPTH24_STENCIL8);
        frameBuffer->AddDepthStencilAttachment(depthStencil);

        CBT_ASSERT(frameBuffer->IsComplete());
        return frameBuffer;
    }

    cbtFrameBuffer* CreateLBuffer(cbtS32 _width, cbtS32 _height)
    {
        cbtFrameBuffer* frameBuffer = cbtFrameBuffer::CreateFrameBuffer();

        cbtTexture* colors[(cbtU32)cbtLBuffer::NUM_COLOR_ATTACHMENTS];
        // Color Output
        colors[(cbtU32)cbtLBuffer::COMPOSITE] = cbtTexture::CreateFrameBufferAttachment("LBuffer Composite", _width,
                _height, CBT_RGBA8);
        // Light Diffuse Color
        colors[(cbtU32)cbtLBuffer::LIGHT_DIFFUSE] = cbtTexture::CreateFrameBufferAttachment("LBuffer Light Diffuse",
                _width, _height,
                CBT_RGBA8);
        // Light Specular Color
        colors[(cbtU32)cbtLBuffer::LIGHT_SPECULAR] = cbtTexture::CreateFrameBufferAttachment("LBuffer Light Specular",
                _width, _height,
                CBT_RGBA8);

        for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
        {
            frameBuffer->AddColorAttachment(colors[i], i);
        }
        frameBuffer->SetDrawColorBuffersAll();

        cbtTexture* depthStencil = cbtTexture::CreateFrameBufferAttachment("LBuffer Depth Stencil", _width, _height,
                CBT_DEPTH24_STENCIL8);
        frameBuffer->AddDepthStencilAttachment(depthStencil);

        CBT_ASSERT(frameBuffer->IsComplete());
        return frameBuffer;
    }

    cbtFrameBuffer* CreateFBuffer(cbtS32 _width, cbtS32 _height)
    {
        cbtFrameBuffer* frameBuffer = cbtFrameBuffer::CreateFrameBuffer();

        cbtTexture* colors[(cbtU32)cbtFBuffer::NUM_COLOR_ATTACHMENTS];

        // Color Output
        colors[(cbtU32)cbtFBuffer::COMPOSITE] = cbtTexture::CreateFrameBufferAttachment("FBuffer Composite", _width,
                _height, CBT_RGBA8);
        // Position Camera Space (Store the x, y and z as half floats).
        colors[(cbtU32)cbtFBuffer::POSITION_CAMERA_SPACE] = cbtTexture::CreateFrameBufferAttachment(
                "FBuffer Position Camera Space", _width, _height, CBT_RGB16F);
        // Normal Camera Space (Store the x, y and z as half floats).
        colors[(cbtU32)cbtFBuffer::NORMAL_CAMERA_SPACE] = cbtTexture::CreateFrameBufferAttachment(
                "FBuffer Normal Camera Space", _width, _height, CBT_RGB16F);

        for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
        {
            frameBuffer->AddColorAttachment(colors[i], i);
        }
        frameBuffer->SetDrawColorBuffersAll();

        cbtTexture* depthStencil = cbtTexture::CreateFrameBufferAttachment("Forward Buffer Depth Stencil", _width,
                _height, CBT_DEPTH24_STENCIL8);
        frameBuffer->AddDepthStencilAttachment(depthStencil);

        CBT_ASSERT(frameBuffer->IsComplete());
        return frameBuffer;
    }

    cbtFrameBuffer* CreatePBuffer(cbtS32 _width, cbtS32 _height)
    {
        cbtFrameBuffer* frameBuffer = cbtFrameBuffer::CreateFrameBuffer();

        cbtTexture* colors[(cbtU32)cbtPBuffer::NUM_COLOR_ATTACHMENTS];

        // Color Output
        colors[(cbtU32)cbtPBuffer::COMPOSITE] = cbtTexture::CreateFrameBufferAttachment("PBuffer Composite Post",
                _width, _height, CBT_RGBA8);

        for (cbtU32 i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i)
        {
            frameBuffer->AddColorAttachment(colors[i], i);
        }
        frameBuffer->SetDrawColorBuffersAll();

        CBT_ASSERT(frameBuffer->IsComplete());
        return frameBuffer;
    }

NS_CBT_END