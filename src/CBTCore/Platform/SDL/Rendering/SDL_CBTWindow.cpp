// Include CBT
#include "SDL_CBTWindow.h"
#include "Debug/CBTDebug.h"
#include "Rendering/Window/CBTWindowEvent.h"

#ifdef CBT_SDL

NS_CBT_BEGIN

CBTWindow* CBTWindow::CreateCBTWindow(const CBTWindowProperties& _properties) { return cbtNew SDL_CBTWindow(_properties); }

SDL_CBTWindow::SDL_CBTWindow(const CBTWindowProperties& _properties)
    : CBTWindow(_properties)
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        CBT_LOG_ERROR(CBT_LOG_CATEGORY_RENDER, "SDL Window's Initialisation Failed!");
        CBT_ASSERT(false);
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        CBT_LOG_ERROR(CBT_LOG_CATEGORY_RENDER, "IMG_Init: Failed to init required jpg and png support!");
        CBT_ASSERT(false);
    }

    // Set OpenGL Version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // Set Double Buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int majorVersion;
    int minorVersion;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion);
    cbtStr glVersionMsg = "OpenGL Version: " + CBT_TO_STRING(majorVersion) + "." + CBT_TO_STRING(minorVersion);
    CBT_LOG_INFO(CBT_LOG_CATEGORY_RENDER, glVersionMsg.c_str());

    // Enable Multisampling
    // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // glEnable(GL_MULTISAMPLE);

    // Create Window
    m_SDL_Window = SDL_CreateWindow(m_Properties.m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Properties.m_Width, m_Properties.m_Height, SDL_WINDOW_OPENGL /* | SDL_WINDOW_INPUT_GRABBED */);
    SDL_SetWindowFullscreen(m_SDL_Window, m_Properties.IsFullscreen() ? SDL_TRUE : SDL_FALSE);
    SDL_SetWindowBordered(m_SDL_Window, m_Properties.IsBorderless() ? SDL_FALSE : SDL_TRUE);

    // Query Actual Window Size
    cbtS32 winddowWidth, windowHeight;
    SDL_GetWindowSize(m_SDL_Window, &winddowWidth, &windowHeight);
    m_Properties.m_Width = (cbtU32)winddowWidth;
    m_Properties.m_Height = (cbtU32)windowHeight;

    // Create OpenGL Context
    m_SDL_GLContext = SDL_GL_CreateContext(m_SDL_Window);
}

SDL_CBTWindow::~SDL_CBTWindow()
{
    SDL_DestroyWindow(m_SDL_Window);
    SDL_GL_DeleteContext(m_SDL_GLContext);
    IMG_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void SDL_CBTWindow::Resize(cbtU32 _width, cbtU32 _height)
{
    // Set Window Size
    SDL_SetWindowSize(m_SDL_Window, _width, _height);

    // Query Actual Window Size
    int winddowWidth, windowHeight;
    SDL_GetWindowSize(m_SDL_Window, &winddowWidth, &windowHeight);
    m_Properties.m_Width = (cbtU32)winddowWidth;
    m_Properties.m_Height = (cbtU32)windowHeight;

    // Send Event
    CBTEvent* windowEvent = new CBTResizeWindowEvent(m_Properties);
    m_EventDispatcher.DispatchEvent<CBTResizeWindowEvent>(windowEvent, true);
}

void SDL_CBTWindow::SwapBuffers() { SDL_GL_SwapWindow(m_SDL_Window); }

NS_CBT_END

#endif // CBT_SDL