#pragma once

// Include CBT
#include "Input/InputEngine/CBTInputEngine.h"
#include "Platform/SDL/SDLEventPoller/SDLEventPoller.h"
#include "Platform/SDL/Input/SDL_CBTKeycode.h"

#ifdef CBT_SDL

NS_CBT_BEGIN

class SDL_CBTInputEngine : public CBTInputEngine
{
    friend class CBTInputEngine;

protected:
    CBTKeyboardHandler* m_KeyboardHandler;
    SDLEventListener m_SDLEventListener;

    SDL_CBTInputEngine()
        : m_KeyboardHandler(nullptr)
    {}
    virtual ~SDL_CBTInputEngine() {}

public:
    virtual void Init();
    virtual void Update();
    virtual void Exit();

    virtual CBTKeyboardHandler* GetKeyboardHandler() { return m_KeyboardHandler; }
    virtual const CBTKeyboardHandler* GetKeyboardHandler() const { return m_KeyboardHandler; }
};

NS_CBT_END

#endif // CBT_SDL