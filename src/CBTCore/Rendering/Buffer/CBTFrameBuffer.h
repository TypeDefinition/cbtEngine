#pragma once

// Include CBT
#include "Core/General/CBTRef.h"
#include "Rendering/Texture/CBTTexture.h"
#include "Rendering/Color/CBTColor.h"

NS_CBT_BEGIN

class CBTFrameBuffer : public CBTManaged
{
protected:
    CBTFrameBuffer() {}
    virtual ~CBTFrameBuffer() {}

public:
    virtual void AddColorAttachment(CBTTexture* _attachment, cbtU32 _index) = 0;
    virtual CBTTexture* GetColorAttachment(cbtU32 _index) = 0;
    virtual const CBTTexture* GetColorAttachment(cbtU32 _index) const = 0;

    virtual void AddDepthAttachment(CBTTexture* _attachment) = 0;
    virtual CBTTexture* GetDepthAttachment() = 0;
    virtual const CBTTexture* GetDepthAttachment() const = 0;

    virtual void AddDepthStencilAttachment(CBTTexture* _attachment) = 0;
    virtual CBTTexture* GetDepthStencilAttachment() = 0;
    virtual const CBTTexture* GetDepthStencilAttachment() const = 0;

    virtual void AddStencilAttachment(CBTTexture* _attachment) = 0;
    virtual CBTTexture* GetStencilAttachment() = 0;
    virtual const CBTTexture* GetStencilAttachment() const = 0;

    virtual void SetReadColorBuffer(cbtU32 _index) = 0;
    virtual void SetDrawColorBuffer(cbtU32 _index) = 0;
    virtual void SetDrawColorBuffers(std::initializer_list<cbtU32> _indices) = 0;
    virtual void SetDrawColorBuffersAll() = 0;

    virtual cbtBool IsComplete() const = 0;

    // These function(s) are static so that we can pass a nullptr to represent the default framebuffer.
    static void Bind(CBTFrameBuffer* _frameBuffer);
    static void Blit(CBTFrameBuffer* _src, CBTFrameBuffer* _dest,
        cbtBool _colorBuffer, cbtBool _depthBuffer, cbtBool _stencilBuffer,
        cbtS32 _srcX0, cbtS32 _srcY0, cbtS32 _srcX1, cbtS32 _srcY1,
        cbtS32 _destX0, cbtS32 _destY0, cbtS32 _destX1, cbtS32 _destY1);

    // The default clear values follow the default values of OpenGL.
    static void ClearColorAll(CBTFrameBuffer* _frameBuffer, CBTColor _color = CBTColor::BLACK);
    static void ClearColor(CBTFrameBuffer* _frameBuffer, std::initializer_list<cbtU32> _attachmentIndices, CBTColor _color = CBTColor::BLACK);
    static void ClearDepth(CBTFrameBuffer* _frameBuffer, cbtF32 _depth = 1.0f); ///< If Depth Test is false, Clear Depth Buffer does not work.
    static void ClearDepthStencil(CBTFrameBuffer* _frameBuffer, cbtF32 _depth = 1.0f, cbtS32 _stencil = 0); ///< If Depth Test is false, Clear Depth Buffer does not work. If Stencil Test is false, Clear Stencil Buffer does not work.
    static void ClearStencil(CBTFrameBuffer* _frameBuffer, cbtS32 _stencil = 0); ///< If Stencil Test is false, Clear Stencil Buffer does not work.
    static void ClearAttachmentsAll(CBTFrameBuffer* _frameBuffer, CBTColor _color = CBTColor::BLACK, cbtF32 _depth = 1.0f, cbtS32 _stencil = 0);

    static CBTFrameBuffer* CreateFrameBuffer();
};

NS_CBT_END