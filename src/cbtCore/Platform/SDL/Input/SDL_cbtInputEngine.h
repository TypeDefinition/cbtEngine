#pragma once

// Include CBT
#include "Input/InputEngine/cbtInputEngine.h"
#include "Platform/SDL/SDLEventPoller/SDLEventPoller.h"
#include "Platform/SDL/Input/SDL_cbtKeycode.h"

#ifdef CBT_SDL

NS_CBT_BEGIN

    class SDL_cbtInputEngine : public cbtInputEngine
    {
        friend class cbtInputEngine;

    protected:
        cbtKeyboardHandler* m_KeyboardHandler;
        SDLEventListener m_SDLEventListener;

        SDL_cbtInputEngine()
                :m_KeyboardHandler(nullptr)
        {
        }

        virtual ~SDL_cbtInputEngine()
        {
        }

    public:
        virtual void Init();

        virtual void Update();

        virtual void Exit();

        virtual cbtKeyboardHandler* GetKeyboardHandler()
        {
            return m_KeyboardHandler;
        }

        virtual const cbtKeyboardHandler* GetKeyboardHandler() const
        {
            return m_KeyboardHandler;
        }
    };

NS_CBT_END

#endif // CBT_SDL