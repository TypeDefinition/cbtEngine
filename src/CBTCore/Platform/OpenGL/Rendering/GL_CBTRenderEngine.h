#pragma once

// Include CBT
#include "Rendering/RenderEngine/CBTRenderEngine.h"
#include "Rendering/Window/CBTWindow.h"
#include "Rendering/Renderer/CBTRenderer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

class GL_CBTRenderEngine : public CBTRenderEngine
{
    friend class CBTRenderEngine;

protected:
    CBTWindow* m_Window = nullptr;
    CBTRenderer* m_Renderer = nullptr;

    GL_CBTRenderEngine() {}
    virtual ~GL_CBTRenderEngine() {}

public:
    virtual void Init(const CBTWindowProperties& _winProp);
    virtual void Update();
    virtual void Exit();

    virtual const CBTWindow* GetWindow() const { return m_Window; }
    virtual CBTWindow* GetWindow() { return m_Window; }
};

NS_CBT_END

#endif // CBT_OPENGL