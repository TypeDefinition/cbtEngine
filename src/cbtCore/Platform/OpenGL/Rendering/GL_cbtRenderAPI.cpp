// Include CBT
#include "Rendering/RenderEngine/cbtRenderAPI.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <GL/glew.h>

NS_CBT_BEGIN

    GLenum ToOpenGLCompareFunc(cbtCompareFunc _func)
    {
        switch (_func)
        {
        case NS_CBT::cbtCompareFunc::NEVER:
            return GL_NEVER;
        case NS_CBT::cbtCompareFunc::LESS:
            return GL_LESS;
        case NS_CBT::cbtCompareFunc::EQUAL:
            return GL_EQUAL;
        case NS_CBT::cbtCompareFunc::LEQUAL:
            return GL_LEQUAL;
        case NS_CBT::cbtCompareFunc::GREATER:
            return GL_GREATER;
        case NS_CBT::cbtCompareFunc::NOTEQUAL:
            return GL_NOTEQUAL;
        case NS_CBT::cbtCompareFunc::GEQUAL:
            return GL_GEQUAL;
        case NS_CBT::cbtCompareFunc::ALWAYS:
            return GL_ALWAYS;
        default:
            return GL_INVALID_ENUM;
        }
    }

    GLenum ToOpenGLStencilOp(cbtStencilOp _op)
    {
        switch (_op)
        {
        case NS_CBT::cbtStencilOp::KEEP:
            return GL_KEEP;
        case NS_CBT::cbtStencilOp::ZERO:
            return GL_ZERO;
        case NS_CBT::cbtStencilOp::REPLACE:
            return GL_REPLACE;
        case NS_CBT::cbtStencilOp::INCREASE:
            return GL_INCR;
        case NS_CBT::cbtStencilOp::INCREASE_WRAP:
            return GL_INCR_WRAP;
        case NS_CBT::cbtStencilOp::DECREASE:
            return GL_DECR;
        case NS_CBT::cbtStencilOp::DECREASE_WRAP:
            return GL_DECR_WRAP;
        case NS_CBT::cbtStencilOp::INVERT:
            return GL_INVERT;
        default:
            return GL_INVALID_ENUM;
        }
    }

    void cbtRenderAPI::SetCulling(cbtBool _enable)
    {
        if (_enable)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
    }

    void cbtRenderAPI::SetDepthFunc(cbtCompareFunc _func)
    {
        glDepthFunc(ToOpenGLCompareFunc(_func));
    }

    void cbtRenderAPI::SetDepthWrite(cbtBool _enable)
    {
        glDepthMask(_enable ? GL_TRUE : GL_FALSE);
    }

    void cbtRenderAPI::SetDepthTest(cbtBool _enable)
    {
        if (_enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void cbtRenderAPI::SetBlendTest(cbtBool _enable)
    {
        if (_enable)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }

    void cbtRenderAPI::DrawElements(cbtU32 _numElements)
    {
        glDrawElements(GL_TRIANGLES, _numElements, GL_UNSIGNED_INT, 0);
    }

    void cbtRenderAPI::DrawElementsInstanced(cbtU32 _numElements, cbtU32 _numInstances)
    {
        glDrawElementsInstanced(GL_TRIANGLES, _numElements, GL_UNSIGNED_INT, 0, _numInstances);
    }

    void cbtRenderAPI::SetViewPort(cbtS32 _bottomX, cbtS32 _bottomY, cbtS32 _width, cbtS32 _height)
    {
        glViewport(_bottomX, _bottomY, _width, _height);
    }

    void cbtRenderAPI::SetScissor(cbtS32 _bottomX, cbtS32 _bottomY, cbtS32 _width, cbtS32 _height)
    {
        glScissor(_bottomX, _bottomY, _width, _height);
    }

// If Depth Test is false, glClear(GL_STENCIL_BUFFER_BIT) does not work. But clearing a FrameBuffer directly using glClearNamedFrameBuffer* works.
    void cbtRenderAPI::SetScissorTest(cbtBool _enable)
    {
        if (_enable)
        {
            glEnable(GL_SCISSOR_TEST);
        }
        else
        {
            glDisable(GL_SCISSOR_TEST);
        }
    }

    void cbtRenderAPI::SetStencilTest(cbtBool _enable)
    {
        /* The function glStencilMask allows us to set a bitmask that is
        ANDed with the stencil value about to be written to the buffer.
        By default this is set to a bitmask of all 1s unaffecting the output,
        but if we were to set this to 0x00 all the stencil values written to the buffer
        end up as 0s. This is equivalent to depth testing's glDepthMask(GL_FALSE). */

        if (_enable)
        {
            glEnable(GL_STENCIL_TEST);
            glStencilMask(0xFF); // Each bit is written to the stencil buffer as is.
        }
        else
        {
            glDisable(GL_STENCIL_TEST);
            glStencilMask(0x00); // Each bit ends up as 0 in the stencil buffer (disabling writes).
        }
    }

    void cbtRenderAPI::SetStencilFunc(cbtCompareFunc _func, cbtU8 _referenceValue, cbtU8 _mask)
    {
        /* _func: sets the stencil test function that determines whether a fragment passes or is discarded.
        This test function is applied to the stored stencil value and the glStencilFunc's ref value.
        Possible options are: GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL and GL_ALWAYS.
        The semantic meaning of these is similar to the depth buffer's functions.

        _referenceValue: specifies the reference value for the stencil test.
        The stencil buffer's content is compared to this value.

        _mask: specifies a mask that is ANDed with both the reference value and the stored stencil
        value before the test compares them. Initially set to all 1s. */
        glStencilFunc(ToOpenGLCompareFunc(_func), _referenceValue, _mask);
    }

    void cbtRenderAPI::SetStencilOp(cbtStencilOp _stencilFail, cbtStencilOp _stencilPassDepthFail,
            cbtStencilOp _stencilPassDepthPass)
    {
        glStencilOp(ToOpenGLStencilOp(_stencilFail), ToOpenGLStencilOp(_stencilPassDepthFail),
                ToOpenGLStencilOp(_stencilPassDepthPass));
    }

NS_CBT_END

#endif // CBT_OPENGL