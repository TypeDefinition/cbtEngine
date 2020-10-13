// Include CBT
#include "cbtApplication.h"
#include "Core/General/cbtRef.h"

// SDL
#include <SDL2/SDL.h>

NS_CBT_BEGIN

void cbtApplication::Run()
{
    Init();
    PostInit();

    // Game Loop
    cbtU64 currentFrameTime = SDL_GetPerformanceCounter();
    cbtU64 lastFrameTime = 0;
    while (!m_Quit)
    {
        lastFrameTime = currentFrameTime;
        currentFrameTime = SDL_GetPerformanceCounter();
        m_DeltaTime = static_cast<cbtF32>((currentFrameTime - lastFrameTime)) / static_cast<cbtF32>(SDL_GetPerformanceFrequency());
        m_TimePassed += m_DeltaTime;

        CBT_LOG_INFO(CBT_LOG_CATEGORY_APPLICATION, "FPS: %d", static_cast<cbtS32>(1.0f/m_DeltaTime));

        PreUpdate();
        Update();
        PostUpdate();
    }

    PreExit();
    Exit();
}

void cbtApplication::Init()
{
    cbtGameEngine::GetInstance()->Init();
    cbtWindowProperties winProp;
    winProp.m_Title = cbtApplication::GetInstance()->GetName();
    winProp.m_Flags |= CBT_WINDOW_BORDERLESS;
    cbtRenderEngine::GetInstance()->Init(winProp);
    cbtInputEngine::GetInstance()->Init();
}

void cbtApplication::Update()
{
    cbtGameEngine::GetInstance()->Update();
    cbtRenderEngine::GetInstance()->Update();
    cbtInputEngine::GetInstance()->Update();
    cbtManaged::ClearReleasePool();
}

void cbtApplication::Exit()
{
    cbtGameEngine::GetInstance()->Exit(); cbtGameEngine::Destroy();
    cbtRenderEngine::GetInstance()->Exit(); cbtRenderEngine::Destroy();
    cbtInputEngine::GetInstance()->Exit(); cbtInputEngine::Destroy();

    cbtManaged::ClearReleasePool();
}

NS_CBT_END