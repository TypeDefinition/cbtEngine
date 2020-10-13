// Include CBT
#include "SDL_cbtInputEngine.h"
#include "Debug/cbtDebug.h"

#ifdef CBT_SDL

NS_CBT_BEGIN

cbtInputEngine* cbtInputEngine::CreateInstance() { return cbtNew SDL_cbtInputEngine(); }

void SDL_cbtInputEngine::Init()
{
    if (SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) != 0)
    {
        CBT_LOG_ERROR(CBT_LOG_CATEGORY_INPUT, "SDL Input Initialisation Failed!");
        CBT_ASSERT(false);
    }

    m_SDLEventListener.m_Filter = [](const SDL_Event& _event) -> cbtBool
    {
        switch (_event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            return true;
        default:
            return false;
        }
    };
    SDLEventPoller::AddListener(&m_SDLEventListener);
    m_KeyboardHandler = cbtNew cbtKeyboardHandler();
}

void SDL_cbtInputEngine::Update()
{
    SDLEventPoller::PollEvents();
    while (!m_SDLEventListener.m_EventQueue.empty())
    {
        SDL_Event& sdlEvent = m_SDLEventListener.m_EventQueue.front();

        switch (sdlEvent.type)
        {
        case SDL_KEYDOWN:
            m_KeyboardHandler->OnKeyPress(m_InputContext, ToCBTKeycode(sdlEvent.key.keysym.sym));
            break;
        case SDL_KEYUP:
            m_KeyboardHandler->OnKeyRelease(m_InputContext, ToCBTKeycode(sdlEvent.key.keysym.sym));
            break;
        default:
            break;
        }

        m_SDLEventListener.m_EventQueue.pop();
    }

    m_KeyboardHandler->DispatchEvents(m_EventDispatcher);
}

void SDL_cbtInputEngine::Exit()
{
    SDLEventPoller::RemoveListener(&m_SDLEventListener);
    delete m_KeyboardHandler;
    SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC);
}

NS_CBT_END

#endif // CBT_SDL