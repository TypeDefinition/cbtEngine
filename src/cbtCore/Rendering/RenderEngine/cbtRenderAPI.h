#pragma once

// Include CBT
#include "cbtMacros.h"

NS_CBT_BEGIN

    enum class cbtCompareFunc
    {
        NEVER,
        LESS,
        EQUAL,
        LEQUAL,
        GREATER,
        NOTEQUAL,
        GEQUAL,
        ALWAYS,
    };

    enum class cbtStencilOp
    {
        KEEP,
        ZERO,
        REPLACE,
        INCREASE,
        INCREASE_WRAP,
        DECREASE,
        DECREASE_WRAP,
        INVERT,
    };

    class cbtRenderAPI
    {
    private:
        cbtRenderAPI()
        {
        }

        ~cbtRenderAPI()
        {
        }

    public:
        static void SetCulling(cbtBool _enable);

        static void SetDepthFunc(cbtCompareFunc _func);

        static void SetDepthWrite(cbtBool _enable);

        static void SetDepthTest(cbtBool _enable); // If Depth Test is false, Clear Depth Buffer does not work.

        static void SetBlendTest(cbtBool _enable);

        static void DrawElements(cbtU32 _numElements);

        static void DrawElementsInstanced(cbtU32 _numElements, cbtU32 _numInstances);

        static void SetViewPort(cbtS32 _bottomX, cbtS32 _bottomY, cbtS32 _width, cbtS32 _height);

        static void SetScissor(cbtS32 _bottomX, cbtS32 _bottomY, cbtS32 _width, cbtS32 _height);

        static void SetScissorTest(cbtBool _enable);

        static void SetStencilTest(cbtBool _enable); // If Stencil Test is false, Clear Stencil Buffer does not work.
        static void SetStencilFunc(cbtCompareFunc _func, cbtU8 _referenceValue, cbtU8 _mask = (cbtU8)0xFF);

        static void
        SetStencilOp(cbtStencilOp _stencilFail, cbtStencilOp _stencilPassDepthFail, cbtStencilOp _stencilPassDepthPass);
    };

NS_CBT_END