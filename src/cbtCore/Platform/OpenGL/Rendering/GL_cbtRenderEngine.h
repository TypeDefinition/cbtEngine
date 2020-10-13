#pragma once

// Include CBT
#include "Rendering/RenderEngine/cbtRenderEngine.h"
#include "Rendering/Window/cbtWindow.h"
#include "Rendering/Renderer/cbtRenderer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

class GL_cbtRenderEngine : public cbtRenderEngine
{
    friend class cbtRenderEngine;

protected:
    cbtWindow* m_Window = nullptr;
    cbtRenderer* m_Renderer = nullptr;

    GL_cbtRenderEngine() {}
    virtual ~GL_cbtRenderEngine() {}

public:
    virtual void Init(const cbtWindowProperties& _winProp);
    virtual void Update();
    virtual void Exit();

    virtual const cbtWindow* GetWindow() const { return m_Window; }
    virtual cbtWindow* GetWindow() { return m_Window; }
};

NS_CBT_END

#endif // CBT_OPENGL