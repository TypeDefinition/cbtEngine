#pragma once

// Include CBT
#include "Rendering/Buffer/cbtFrameBuffer.h"
#include "GL_cbtTexture.h"

#ifdef CBT_OPENGL

// Include GL
#include <GL/glew.h>
// #include <gl/GL.h>

NS_CBT_BEGIN

    class GL_cbtFrameBuffer : public cbtFrameBuffer
    {
    protected:
        GL_cbtTexture* m_ColorAttachments[GL_MAX_COLOR_ATTACHMENTS];
        GL_cbtTexture* m_DepthAttachment;
        GL_cbtTexture* m_StencilAttachment;
        GL_cbtTexture* m_DepthStencilAttachment;
        GLuint m_BufferName;

        virtual ~GL_cbtFrameBuffer();

    public:
        GL_cbtFrameBuffer();

        GLuint GetBufferName()
        {
            return m_BufferName;
        }

        virtual void AddColorAttachment(cbtTexture* _attachment, cbtU32 _index);

        virtual cbtTexture* GetColorAttachment(cbtU32 _index)
        {
            return m_ColorAttachments[_index];
        }

        virtual const cbtTexture* GetColorAttachment(cbtU32 _index) const
        {
            return m_ColorAttachments[_index];
        }

        virtual void AddDepthAttachment(cbtTexture* _attachment);

        virtual cbtTexture* GetDepthAttachment()
        {
            return m_DepthAttachment;
        }

        virtual const cbtTexture* GetDepthAttachment() const
        {
            return m_DepthAttachment;
        }

        virtual void AddStencilAttachment(cbtTexture* _attachment);

        virtual cbtTexture* GetStencilAttachment()
        {
            return m_StencilAttachment;
        }

        virtual const cbtTexture* GetStencilAttachment() const
        {
            return m_StencilAttachment;
        }

        virtual void AddDepthStencilAttachment(cbtTexture* _attachment);

        virtual cbtTexture* GetDepthStencilAttachment()
        {
            return m_DepthStencilAttachment;
        }

        virtual const cbtTexture* GetDepthStencilAttachment() const
        {
            return m_DepthStencilAttachment;
        }

        virtual void SetReadColorBuffer(cbtU32 _index)
        {
            glNamedFramebufferReadBuffer(m_BufferName, GL_COLOR_ATTACHMENT0 + _index);
        }

        virtual void SetDrawColorBuffer(cbtU32 _index)
        {
            glNamedFramebufferDrawBuffer(m_BufferName, GL_COLOR_ATTACHMENT0 + _index);
        }

        virtual void SetDrawColorBuffers(std::initializer_list<cbtU32> _indices);

        virtual void SetDrawColorBuffersAll();

        virtual cbtBool IsComplete() const
        {
            return (GL_FRAMEBUFFER_COMPLETE == glCheckNamedFramebufferStatus(m_BufferName, GL_FRAMEBUFFER));
        }
    };

NS_CBT_END

#endif // CBT_OPENGL