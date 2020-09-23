// Include CBT
#include "Rendering/RenderEngine/CBTRenderAPI.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

GLenum ToOpenGLCompareFunc(CBTCompareFunc _func)
{
    switch (_func)
    {
    case NS_CBT::CBTCompareFunc::NEVER: return GL_NEVER;
    case NS_CBT::CBTCompareFunc::LESS: return GL_LESS;
    case NS_CBT::CBTCompareFunc::EQUAL: return GL_EQUAL;
    case NS_CBT::CBTCompareFunc::LEQUAL: return GL_LEQUAL;
    case NS_CBT::CBTCompareFunc::GREATER: return GL_GREATER;
    case NS_CBT::CBTCompareFunc::NOTEQUAL: return GL_NOTEQUAL;
    case NS_CBT::CBTCompareFunc::GEQUAL: return GL_GEQUAL;
    case NS_CBT::CBTCompareFunc::ALWAYS: return GL_ALWAYS;
    default: return GL_INVALID_ENUM;
    }
}

GLenum ToOpenGLStencilOp(CBTStencilOp _op)
{
    switch (_op)
    {
    case NS_CBT::CBTStencilOp::KEEP: return GL_KEEP;
    case NS_CBT::CBTStencilOp::ZERO: return GL_ZERO;
    case NS_CBT::CBTStencilOp::REPLACE: return GL_REPLACE;
    case NS_CBT::CBTStencilOp::INCREASE: return GL_INCR;
    case NS_CBT::CBTStencilOp::INCREASE_WRAP: return GL_INCR_WRAP;
    case NS_CBT::CBTStencilOp::DECREASE: return GL_DECR;
    case NS_CBT::CBTStencilOp::DECREASE_WRAP: return GL_DECR_WRAP;
    case NS_CBT::CBTStencilOp::INVERT: return GL_INVERT;
    default: return GL_INVALID_ENUM;
    }
}

void CBTRenderAPI::SetCulling(cbtBool _enable)
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

void CBTRenderAPI::SetDepthFunc(CBTCompareFunc _func)
{
    glDepthFunc(ToOpenGLCompareFunc(_func));
}

void CBTRenderAPI::SetDepthWrite(cbtBool _enable)
{
    glDepthMask(_enable ? GL_TRUE : GL_FALSE);
}

void CBTRenderAPI::SetDepthTest(cbtBool _enable)
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

void CBTRenderAPI::SetBlendTest(cbtBool _enable)
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

void CBTRenderAPI::DrawElements(cbtU32 _numElements)
{
    glDrawElements(GL_TRIANGLES, _numElements, GL_UNSIGNED_INT, 0);
}

void CBTRenderAPI::DrawElementsInstanced(cbtU32 _numElements, cbtU32 _numInstances)
{
    glDrawElementsInstanced(GL_TRIANGLES, _numElements, GL_UNSIGNED_INT, 0, _numInstances);
}

void CBTRenderAPI::SetViewPort(cbtS32 _bottomX, cbtS32 _bottomY, cbtS32 _width, cbtS32 _height) { glViewport(_bottomX, _bottomY, _width, _height); }

void CBTRenderAPI::SetScissor(cbtS32 _bottomX, cbtS32 _bottomY, cbtS32 _width, cbtS32 _height) { glScissor(_bottomX, _bottomY, _width, _height); }

// If Depth Test is false, glClear(GL_STENCIL_BUFFER_BIT) does not work. But clearing a FrameBuffer directly using glClearNamedFrameBuffer* works.
void CBTRenderAPI::SetScissorTest(cbtBool _enable)
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

void CBTRenderAPI::SetStencilTest(cbtBool _enable)
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

void CBTRenderAPI::SetStencilFunc(CBTCompareFunc _func, cbtU8 _referenceValue, cbtU8 _mask)
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

void CBTRenderAPI::SetStencilOp(CBTStencilOp _stencilFail, CBTStencilOp _stencilPassDepthFail, CBTStencilOp _stencilPassDepthPass)
{
    glStencilOp(ToOpenGLStencilOp(_stencilFail), ToOpenGLStencilOp(_stencilPassDepthFail), ToOpenGLStencilOp(_stencilPassDepthPass));
}

NS_CBT_END

#endif // CBT_OPENGL