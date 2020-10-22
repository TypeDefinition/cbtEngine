// Include CBT
#include "GL_cbtFrameBuffer.h"

// Include STL
#include <cstring>

#ifdef CBT_OPENGL

NS_CBT_BEGIN

/************************************************************Frame Buffer************************************************************/
    void cbtFrameBuffer::Bind(cbtFrameBuffer* _frameBuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER,
                _frameBuffer ? static_cast<GL_cbtFrameBuffer*>(_frameBuffer)->GetBufferName() : 0);
    }

    void cbtFrameBuffer::Blit(cbtFrameBuffer* _src, cbtFrameBuffer* _dest,
            cbtBool _colorBuffer, cbtBool _depthBuffer, cbtBool _stencilBuffer,
            cbtS32 _srcX0, cbtS32 _srcY0, cbtS32 _srcX1, cbtS32 _srcY1,
            cbtS32 _destX0, cbtS32 _destY0, cbtS32 _destX1, cbtS32 _destY1)
    {
        GL_cbtFrameBuffer* source = static_cast<GL_cbtFrameBuffer*>(_src);
        GL_cbtFrameBuffer* destination = static_cast<GL_cbtFrameBuffer*>(_dest);

        GLbitfield mask = 0;
        mask |= (_colorBuffer ? GL_COLOR_BUFFER_BIT : 0);
        mask |= (_depthBuffer ? GL_DEPTH_BUFFER_BIT : 0);
        mask |= (_stencilBuffer ? GL_STENCIL_BUFFER_BIT : 0);

        /* If filter is not GL_NEAREST and mask includes GL_DEPTH_BUFFER_BIT or GL_STENCIL_BUFFER_BIT, no data is transferred and a GL_INVALID_OPERATION error is generated.
        So for simplicity let's just use GL_NEAREST. Don't act smart use GL_LINEAR. */
        glBlitNamedFramebuffer(source ? source->GetBufferName() : 0, destination ? destination->GetBufferName() : 0,
                _srcX0, _srcY0, _srcX1, _srcY1,
                _destX0, _destY0, _destX1, _destY1,
                mask, GL_NEAREST);
    }

    void cbtFrameBuffer::ClearColorAll(cbtFrameBuffer* _frameBuffer, cbtColor _color)
    {
        GL_cbtFrameBuffer* frameBuffer = static_cast<GL_cbtFrameBuffer*>(_frameBuffer);

        // Default FrameBuffer
        if (frameBuffer == nullptr)
        {
            glClearNamedFramebufferfv(0, GL_COLOR, 0, &_color.m_R);
            return;
        }

        // Custom FrameBuffer
        for (cbtU32 i = 0; i < GL_MAX_COLOR_ATTACHMENTS; ++i)
        {
            if (frameBuffer->GetColorAttachment(i) == nullptr)
            { continue; }
            glClearNamedFramebufferfv(frameBuffer->GetBufferName(), GL_COLOR, i, &_color.m_R);
        }
    }

    void cbtFrameBuffer::ClearColor(cbtFrameBuffer* _frameBuffer, std::initializer_list<cbtU32> _attachmentIndices,
            cbtColor _color)
    {
        GL_cbtFrameBuffer* frameBuffer = static_cast<GL_cbtFrameBuffer*>(_frameBuffer);

        // Default FrameBuffer
        if (frameBuffer == nullptr)
        {
            glClearNamedFramebufferfv(0, GL_COLOR, 0, &_color.m_R);
            return;
        }

        // Custom FrameBuffer
        std::vector<cbtU32> attachmentIndices(_attachmentIndices);
        for (cbtU32 i = 0; i < attachmentIndices.size(); ++i)
        {
            glClearNamedFramebufferfv(frameBuffer->GetBufferName(), GL_COLOR, attachmentIndices[i], &_color.m_R);
        }
    }

    void cbtFrameBuffer::ClearDepth(cbtFrameBuffer* _frameBuffer, cbtF32 _depth)
    {
        GL_cbtFrameBuffer* frameBuffer = static_cast<GL_cbtFrameBuffer*>(_frameBuffer);
        glClearNamedFramebufferfv(frameBuffer ? frameBuffer->GetBufferName() : 0, GL_DEPTH, 0, &_depth);
    }

    void cbtFrameBuffer::ClearDepthStencil(cbtFrameBuffer* _frameBuffer, cbtF32 _depth, cbtS32 _stencil)
    {
        GL_cbtFrameBuffer* frameBuffer = static_cast<GL_cbtFrameBuffer*>(_frameBuffer);
        glClearNamedFramebufferfi(frameBuffer ? frameBuffer->GetBufferName() : 0, GL_DEPTH_STENCIL, 0, _depth,
                _stencil);
    }

    void cbtFrameBuffer::ClearStencil(cbtFrameBuffer* _frameBuffer, cbtS32 _stencil)
    {
        GL_cbtFrameBuffer* frameBuffer = static_cast<GL_cbtFrameBuffer*>(_frameBuffer);
        glClearNamedFramebufferiv(frameBuffer ? frameBuffer->GetBufferName() : 0, GL_STENCIL, 0, &_stencil);
    }

    void
    cbtFrameBuffer::ClearAttachmentsAll(cbtFrameBuffer* _frameBuffer, cbtColor _color, cbtF32 _depth, cbtS32 _stencil)
    {
        ClearColorAll(_frameBuffer, _color);
        ClearDepth(_frameBuffer, _depth);
        ClearDepthStencil(_frameBuffer, _depth, _stencil);
        ClearStencil(_frameBuffer, _stencil);
    }

    cbtFrameBuffer* cbtFrameBuffer::CreateFrameBuffer()
    {
        return cbtNew GL_cbtFrameBuffer();
    }

    GL_cbtFrameBuffer::GL_cbtFrameBuffer()
            :m_DepthAttachment(nullptr), m_StencilAttachment(nullptr), m_DepthStencilAttachment(nullptr)
    {
        std::memset(&m_ColorAttachments[0], 0, GL_MAX_COLOR_ATTACHMENTS * sizeof(m_ColorAttachments[0]));
        glCreateFramebuffers(1, &m_BufferName);
    }

    GL_cbtFrameBuffer::~GL_cbtFrameBuffer()
    {
        for (cbtU32 i = 0;
             i < GL_MAX_COLOR_ATTACHMENTS; ++i)
        {
            if (m_ColorAttachments[i])
            { m_ColorAttachments[i]->Release(); }
        }
        if (m_DepthAttachment)
        { m_DepthAttachment->Release(); }
        if (m_DepthStencilAttachment)
        { m_DepthStencilAttachment->Release(); }
        if (m_StencilAttachment)
        { m_StencilAttachment->Release(); }
        glDeleteFramebuffers(1, &m_BufferName);
    }

    void GL_cbtFrameBuffer::AddColorAttachment(cbtTexture* _attachment, cbtU32 _index)
    {
        CBT_ASSERT(m_ColorAttachments[_index] == nullptr);

        GL_cbtTexture* attachment = static_cast<GL_cbtTexture*>(_attachment);
        glNamedFramebufferTexture(m_BufferName, GL_COLOR_ATTACHMENT0 + _index, attachment->GetGLTextureName(), 0);
        _attachment->Retain();
        m_ColorAttachments[_index] = attachment;
    }

    void GL_cbtFrameBuffer::AddDepthAttachment(cbtTexture* _attachment)
    {
        CBT_ASSERT(m_DepthAttachment == nullptr);
        CBT_ASSERT(m_DepthStencilAttachment == nullptr);

        m_DepthAttachment = static_cast<GL_cbtTexture*>(_attachment);
        m_DepthAttachment->Retain();
        glNamedFramebufferTexture(m_BufferName, GL_DEPTH_ATTACHMENT, m_DepthAttachment->GetGLTextureName(), 0);
    }

    void GL_cbtFrameBuffer::AddStencilAttachment(cbtTexture* _attachment)
    {
        CBT_ASSERT(m_StencilAttachment == nullptr);
        CBT_ASSERT(m_DepthStencilAttachment == nullptr);

        m_StencilAttachment = static_cast<GL_cbtTexture*>(_attachment);
        m_StencilAttachment->Retain();
        glNamedFramebufferTexture(m_BufferName, GL_STENCIL_ATTACHMENT, m_StencilAttachment->GetGLTextureName(), 0);
    }

    void GL_cbtFrameBuffer::AddDepthStencilAttachment(cbtTexture* _attachment)
    {
        CBT_ASSERT(m_DepthAttachment == nullptr);
        CBT_ASSERT(m_StencilAttachment == nullptr);
        CBT_ASSERT(m_DepthStencilAttachment == nullptr);

        m_DepthStencilAttachment = static_cast<GL_cbtTexture*>(_attachment);
        m_DepthStencilAttachment->Retain();
        glNamedFramebufferTexture(m_BufferName, GL_DEPTH_STENCIL_ATTACHMENT,
                m_DepthStencilAttachment->GetGLTextureName(), 0);
    }

    void GL_cbtFrameBuffer::SetDrawColorBuffers(std::initializer_list<cbtU32> _indices)
    {
        std::vector<cbtU32> colorAttachments(_indices);
        for (cbtU32 i = 0; i < colorAttachments.size(); ++i)
        { colorAttachments[i] += GL_COLOR_ATTACHMENT0; }
        glNamedFramebufferDrawBuffers(m_BufferName, (GLsizei)colorAttachments.size(), &colorAttachments[0]);
    }

    void GL_cbtFrameBuffer::SetDrawColorBuffersAll()
    {
        std::vector<cbtU32> colorAttachments;
        for (cbtU32 i = 0; i < GL_MAX_COLOR_ATTACHMENTS; ++i)
        {
            if (m_ColorAttachments[i])
            { colorAttachments.push_back(GL_COLOR_ATTACHMENT0 + i); }
        }
        glNamedFramebufferDrawBuffers(m_BufferName, (GLsizei)colorAttachments.size(), &colorAttachments[0]);
    }

NS_CBT_END

#endif // CBT_OPENGL