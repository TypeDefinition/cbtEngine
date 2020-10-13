#pragma once

// Include CBT
#include "Rendering/Window/cbtWindow.h"

#ifdef CBT_SDL

// Include SDL
#include <SDL.h>
#include <SDL_image.h>

NS_CBT_BEGIN

class SDL_cbtWindow : public cbtWindow
{
protected:
    SDL_GLContext m_SDL_GLContext;
    SDL_Window* m_SDL_Window;

public:
    SDL_cbtWindow(const cbtWindowProperties& _properties);
    virtual ~SDL_cbtWindow();

    virtual void Resize(cbtU32 _width, cbtU32 _height);
    virtual void SwapBuffers();
};

NS_CBT_END

#endif // CBT_SDL