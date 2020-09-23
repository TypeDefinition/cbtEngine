#pragma once

// Include CBT
#include "CBTMacros.h"

// Include STD
#include <vector>
#include <queue>

#ifdef CBT_SDL

// Include SDL
#include <SDL.h>

NS_CBT_BEGIN

struct SDLEventListener
{
public:
    cbtBool (*m_Filter)(const SDL_Event& _event) = nullptr; // Not to be confused with SDL_EventFilter.
    std::queue<SDL_Event> m_EventQueue;
};

// A very very simple event poller to allow multiple systems to poll and listen for SDL events.
class SDLEventPoller
{
private:
    static std::vector<SDLEventListener*> m_Listeners;

    SDLEventPoller();
    ~SDLEventPoller();

public:
    static void PollEvents()
    {
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent))
        {
            for (cbtU32 i = 0; i < m_Listeners.size(); ++i)
            {
                if (m_Listeners[i]->m_Filter(sdlEvent))
                {
                    m_Listeners[i]->m_EventQueue.push(sdlEvent);
                }
            }
        }
    }

    static void AddListener(SDLEventListener* _listener)
    {
        m_Listeners.push_back(_listener);
    }

    static void RemoveListener(SDLEventListener* _listener)
    {
        for (auto iter = m_Listeners.begin(); iter != m_Listeners.end(); ++iter)
        {
            if (*iter == _listener)
            {
                m_Listeners.erase(iter);
                break;
            }
        }
    }
};

NS_CBT_END

#endif // CBT_SDL