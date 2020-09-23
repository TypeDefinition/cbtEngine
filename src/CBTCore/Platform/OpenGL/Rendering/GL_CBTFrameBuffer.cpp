// Include CBT
#include "GL_CBTFrameBuffer.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

/************************************************************Frame Buffer************************************************************/
void CBTFrameBuffer::Bind(CBTFrameBuffer* _frameBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer ? static_cast<GL_CBTFrameBuffer*>(_frameBuffer)->GetBufferName() : 0);
}

void CBTFrameBuffer::Blit(CBTFrameBuffer* _src, CBTFrameBuffer* _dest,
    cbtBool _colorBuffer, cbtBool _depthBuffer, cbtBool _stencilBuffer,
    cbtS32 _srcX0, cbtS32 _srcY0, cbtS32 _srcX1, cbtS32 _srcY1,
    cbtS32 _destX0, cbtS32 _destY0, cbtS32 _destX1, cbtS32 _destY1)
{
    GL_CBTFrameBuffer* source = static_cast<GL_CBTFrameBuffer*>(_src);
    GL_CBTFrameBuffer* destination = static_cast<GL_CBTFrameBuffer*>(_dest);

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

void CBTFrameBuffer::ClearColorAll(CBTFrameBuffer* _frameBuffer, CBTColor _color)
{
    GL_CBTFrameBuffer* frameBuffer = static_cast<GL_CBTFrameBuffer*>(_frameBuffer);

    // Default FrameBuffer
    if (frameBuffer == nullptr)
    {
        glClearNamedFramebufferfv(0, GL_COLOR, 0, &_color.m_R);
        return;
    }

    // Custom FrameBuffer
    for (cbtU32 i = 0; i < GL_MAX_COLOR_ATTACHMENTS; ++i)
    {
        if (frameBuffer->GetColorAttachment(i) == nullptr) { continue; }
        glClearNamedFramebufferfv(frameBuffer->GetBufferName(), GL_COLOR, i, &_color.m_R);
    }
}

void CBTFrameBuffer::ClearColor(CBTFrameBuffer* _frameBuffer, std::initializer_list<cbtU32> _attachmentIndices, CBTColor _color)
{
    GL_CBTFrameBuffer* frameBuffer = static_cast<GL_CBTFrameBuffer*>(_frameBuffer);

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

void CBTFrameBuffer::ClearDepth(CBTFrameBuffer* _frameBuffer, cbtF32 _depth)
{
    GL_CBTFrameBuffer* frameBuffer = static_cast<GL_CBTFrameBuffer*>(_frameBuffer);
    glClearNamedFramebufferfv(frameBuffer ? frameBuffer->GetBufferName() : 0, GL_DEPTH, 0, &_depth);
}

void CBTFrameBuffer::ClearDepthStencil(CBTFrameBuffer* _frameBuffer, cbtF32 _depth, cbtS32 _stencil)
{
    GL_CBTFrameBuffer* frameBuffer = static_cast<GL_CBTFrameBuffer*>(_frameBuffer);
    glClearNamedFramebufferfi(frameBuffer ? frameBuffer->GetBufferName() : 0, GL_DEPTH_STENCIL, 0, _depth, _stencil);
}

void CBTFrameBuffer::ClearStencil(CBTFrameBuffer* _frameBuffer, cbtS32 _stencil)
{
    GL_CBTFrameBuffer* frameBuffer = static_cast<GL_CBTFrameBuffer*>(_frameBuffer);
    glClearNamedFramebufferiv(frameBuffer ? frameBuffer->GetBufferName() : 0, GL_STENCIL, 0, &_stencil);
}

void CBTFrameBuffer::ClearAttachmentsAll(CBTFrameBuffer* _frameBuffer, CBTColor _color, cbtF32 _depth, cbtS32 _stencil)
{
    ClearColorAll(_frameBuffer, _color);
    ClearDepth(_frameBuffer, _depth);
    ClearDepthStencil(_frameBuffer, _depth, _stencil);
    ClearStencil(_frameBuffer, _stencil);
}

CBTFrameBuffer* CBTFrameBuffer::CreateFrameBuffer() { return cbtNew GL_CBTFrameBuffer(); }

GL_CBTFrameBuffer::GL_CBTFrameBuffer()
    : m_DepthAttachment(nullptr)
    , m_StencilAttachment(nullptr)
    , m_DepthStencilAttachment(nullptr)
{
    std::memset(&m_ColorAttachments[0], 0, GL_MAX_COLOR_ATTACHMENTS * sizeof(m_ColorAttachments[0]));
    glCreateFramebuffers(1, &m_BufferName);
}

GL_CBTFrameBuffer::~GL_CBTFrameBuffer()
{
    for (cbtU32 i = 0; i < GL_MAX_COLOR_ATTACHMENTS; ++i) { if (m_ColorAttachments[i]) { m_ColorAttachments[i]->Release(); } }
    if (m_DepthAttachment) { m_DepthAttachment->Release(); }
    if (m_DepthStencilAttachment) { m_DepthStencilAttachment->Release(); }
    if (m_StencilAttachment) { m_StencilAttachment->Release(); }
    glDeleteFramebuffers(1, &m_BufferName);
}

void GL_CBTFrameBuffer::AddColorAttachment(CBTTexture* _attachment, cbtU32 _index)
{
    CBT_ASSERT(m_ColorAttachments[_index] == nullptr);

    GL_CBTTexture* attachment = static_cast<GL_CBTTexture*>(_attachment);
    glNamedFramebufferTexture(m_BufferName, GL_COLOR_ATTACHMENT0 + _index, attachment->GetGLTextureName(), 0);
    _attachment->Retain();
    m_ColorAttachments[_index] = attachment;
}

void GL_CBTFrameBuffer::AddDepthAttachment(CBTTexture* _attachment)
{
    CBT_ASSERT(m_DepthAttachment == nullptr);
    CBT_ASSERT(m_DepthStencilAttachment == nullptr);

    m_DepthAttachment = static_cast<GL_CBTTexture*>(_attachment);
    m_DepthAttachment->Retain();
    glNamedFramebufferTexture(m_BufferName, GL_DEPTH_ATTACHMENT, m_DepthAttachment->GetGLTextureName(), 0);
}

void GL_CBTFrameBuffer::AddStencilAttachment(CBTTexture* _attachment)
{
    CBT_ASSERT(m_StencilAttachment == nullptr);
    CBT_ASSERT(m_DepthStencilAttachment == nullptr);

    m_StencilAttachment = static_cast<GL_CBTTexture*>(_attachment);
    m_StencilAttachment->Retain();
    glNamedFramebufferTexture(m_BufferName, GL_STENCIL_ATTACHMENT, m_StencilAttachment->GetGLTextureName(), 0);
}

void GL_CBTFrameBuffer::AddDepthStencilAttachment(CBTTexture* _attachment)
{
    CBT_ASSERT(m_DepthAttachment == nullptr);
    CBT_ASSERT(m_StencilAttachment == nullptr);
    CBT_ASSERT(m_DepthStencilAttachment == nullptr);

    m_DepthStencilAttachment = static_cast<GL_CBTTexture*>(_attachment);
    m_DepthStencilAttachment->Retain();
    glNamedFramebufferTexture(m_BufferName, GL_DEPTH_STENCIL_ATTACHMENT, m_DepthStencilAttachment->GetGLTextureName(), 0);
}

void GL_CBTFrameBuffer::SetDrawColorBuffers(std::initializer_list<cbtU32> _indices)
{
    std::vector<cbtU32> colorAttachments(_indices);
    for (cbtU32 i = 0; i < colorAttachments.size(); ++i) { colorAttachments[i] += GL_COLOR_ATTACHMENT0; }
    glNamedFramebufferDrawBuffers(m_BufferName, (GLsizei)colorAttachments.size(), &colorAttachments[0]);
}

void GL_CBTFrameBuffer::SetDrawColorBuffersAll()
{
    std::vector<cbtU32> colorAttachments;
    for (cbtU32 i = 0; i < GL_MAX_COLOR_ATTACHMENTS; ++i)
    {
        if (m_ColorAttachments[i]) { colorAttachments.push_back(GL_COLOR_ATTACHMENT0 + i); }
    }
    glNamedFramebufferDrawBuffers(m_BufferName, (GLsizei)colorAttachments.size(), &colorAttachments[0]);
}

NS_CBT_END

#endif // CBT_OPENGL