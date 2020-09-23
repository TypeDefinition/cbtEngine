#pragma once

// Include CBT
#include "Core/General/cbtRef.h"
#include "Rendering/Texture/cbtTexture.h"
#include "Rendering/Color/cbtColor.h"

NS_CBT_BEGIN

class cbtFrameBuffer : public cbtManaged
{
protected:
    cbtFrameBuffer() {}
    virtual ~cbtFrameBuffer() {}

public:
    virtual void AddColorAttachment(cbtTexture* _attachment, cbtU32 _index) = 0;
    virtual cbtTexture* GetColorAttachment(cbtU32 _index) = 0;
    virtual const cbtTexture* GetColorAttachment(cbtU32 _index) const = 0;

    virtual void AddDepthAttachment(cbtTexture* _attachment) = 0;
    virtual cbtTexture* GetDepthAttachment() = 0;
    virtual const cbtTexture* GetDepthAttachment() const = 0;

    virtual void AddDepthStencilAttachment(cbtTexture* _attachment) = 0;
    virtual cbtTexture* GetDepthStencilAttachment() = 0;
    virtual const cbtTexture* GetDepthStencilAttachment() const = 0;

    virtual void AddStencilAttachment(cbtTexture* _attachment) = 0;
    virtual cbtTexture* GetStencilAttachment() = 0;
    virtual const cbtTexture* GetStencilAttachment() const = 0;

    virtual void SetReadColorBuffer(cbtU32 _index) = 0;
    virtual void SetDrawColorBuffer(cbtU32 _index) = 0;
    virtual void SetDrawColorBuffers(std::initializer_list<cbtU32> _indices) = 0;
    virtual void SetDrawColorBuffersAll() = 0;

    virtual cbtBool IsComplete() const = 0;

    // These function(s) are static so that we can pass a nullptr to represent the default framebuffer.
    static void Bind(cbtFrameBuffer* _frameBuffer);
    static void Blit(cbtFrameBuffer* _src, cbtFrameBuffer* _dest,
        cbtBool _colorBuffer, cbtBool _depthBuffer, cbtBool _stencilBuffer,
        cbtS32 _srcX0, cbtS32 _srcY0, cbtS32 _srcX1, cbtS32 _srcY1,
        cbtS32 _destX0, cbtS32 _destY0, cbtS32 _destX1, cbtS32 _destY1);

    // The default clear values follow the default values of OpenGL.
    static void ClearColorAll(cbtFrameBuffer* _frameBuffer, cbtColor _color = cbtColor::BLACK);
    static void ClearColor(cbtFrameBuffer* _frameBuffer, std::initializer_list<cbtU32> _attachmentIndices, cbtColor _color = cbtColor::BLACK);
    static void ClearDepth(cbtFrameBuffer* _frameBuffer, cbtF32 _depth = 1.0f); ///< If Depth Test is false, Clear Depth Buffer does not work.
    static void ClearDepthStencil(cbtFrameBuffer* _frameBuffer, cbtF32 _depth = 1.0f, cbtS32 _stencil = 0); ///< If Depth Test is false, Clear Depth Buffer does not work. If Stencil Test is false, Clear Stencil Buffer does not work.
    static void ClearStencil(cbtFrameBuffer* _frameBuffer, cbtS32 _stencil = 0); ///< If Stencil Test is false, Clear Stencil Buffer does not work.
    static void ClearAttachmentsAll(cbtFrameBuffer* _frameBuffer, cbtColor _color = cbtColor::BLACK, cbtF32 _depth = 1.0f, cbtS32 _stencil = 0);

    static cbtFrameBuffer* CreateFrameBuffer();
};

NS_CBT_END