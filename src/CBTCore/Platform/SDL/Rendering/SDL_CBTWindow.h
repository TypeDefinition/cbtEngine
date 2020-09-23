#pragma once

// Include CBT
#include "Rendering/Window/CBTWindow.h"

#ifdef CBT_SDL

// Include SDL
#include <SDL.h>
#include <SDL_image.h>

NS_CBT_BEGIN

class SDL_CBTWindow : public CBTWindow
{
protected:
    SDL_GLContext m_SDL_GLContext;
    SDL_Window* m_SDL_Window;

public:
    SDL_CBTWindow(const CBTWindowProperties& _properties);
    virtual ~SDL_CBTWindow();

    virtual void Resize(cbtU32 _width, cbtU32 _height);
    virtual void SwapBuffers();
};

NS_CBT_END

#endif // CBT_SDL