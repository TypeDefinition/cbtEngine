#pragma once

// Include CBT
#include "Rendering/Buffer/CBTFrameBuffer.h"
#include "GL_CBTTexture.h"

#ifdef CBT_OPENGL

// Include GL
#include <glew.h>
#include <gl/GL.h>

NS_CBT_BEGIN

class GL_CBTFrameBuffer : public CBTFrameBuffer
{
protected:
    GL_CBTTexture* m_ColorAttachments[GL_MAX_COLOR_ATTACHMENTS];
    GL_CBTTexture* m_DepthAttachment;
    GL_CBTTexture* m_StencilAttachment;
    GL_CBTTexture* m_DepthStencilAttachment;
    GLuint m_BufferName;

    virtual ~GL_CBTFrameBuffer();

public:
    GL_CBTFrameBuffer();

    GLuint GetBufferName() { return m_BufferName; }

    virtual void AddColorAttachment(CBTTexture* _attachment, cbtU32 _index);
    virtual CBTTexture* GetColorAttachment(cbtU32 _index) { return m_ColorAttachments[_index]; }
    virtual const CBTTexture* GetColorAttachment(cbtU32 _index) const { return m_ColorAttachments[_index]; }

    virtual void AddDepthAttachment(CBTTexture* _attachment);
    virtual CBTTexture* GetDepthAttachment() { return m_DepthAttachment; }
    virtual const CBTTexture* GetDepthAttachment() const { return m_DepthAttachment; }

    virtual void AddStencilAttachment(CBTTexture* _attachment);
    virtual CBTTexture* GetStencilAttachment() { return m_StencilAttachment; }
    virtual const CBTTexture* GetStencilAttachment() const { return m_StencilAttachment; }

    virtual void AddDepthStencilAttachment(CBTTexture* _attachment);
    virtual CBTTexture* GetDepthStencilAttachment() { return m_DepthStencilAttachment; }
    virtual const CBTTexture* GetDepthStencilAttachment() const { return m_DepthStencilAttachment; }

    virtual void SetReadColorBuffer(cbtU32 _index) { glNamedFramebufferReadBuffer(m_BufferName, GL_COLOR_ATTACHMENT0 + _index); }
    virtual void SetDrawColorBuffer(cbtU32 _index) { glNamedFramebufferDrawBuffer(m_BufferName, GL_COLOR_ATTACHMENT0 + _index); }
    virtual void SetDrawColorBuffers(std::initializer_list<cbtU32> _indices);
    virtual void SetDrawColorBuffersAll();

    virtual cbtBool IsComplete() const { return (GL_FRAMEBUFFER_COMPLETE == glCheckNamedFramebufferStatus(m_BufferName, GL_FRAMEBUFFER)); }
};

NS_CBT_END

#endif // CBT_OPENGL