// Include CBT
#include "CBTApplication.h"
#include "Core/General/CBTRef.h"

// SDL
#include <SDL.h>

NS_CBT_BEGIN

void CBTApplication::Run()
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

void CBTApplication::Init()
{
    CBTGameEngine::GetInstance()->Init();
    CBTWindowProperties winProp;
    winProp.m_Title = CBTApplication::GetInstance()->GetName();
    winProp.m_Flags |= CBT_WINDOW_BORDERLESS;
    CBTRenderEngine::GetInstance()->Init(winProp);
    CBTInputEngine::GetInstance()->Init();
    // CBTAudioEngine::GetInstance()->Init();
}

void CBTApplication::Update()
{
    CBTGameEngine::GetInstance()->Update();
    CBTRenderEngine::GetInstance()->Update();
    CBTInputEngine::GetInstance()->Update();
    CBTManaged::ClearReleasePool();
}

void CBTApplication::Exit()
{
    CBTGameEngine::GetInstance()->Exit(); CBTGameEngine::Destroy();
    CBTRenderEngine::GetInstance()->Exit(); CBTRenderEngine::Destroy();
    CBTInputEngine::GetInstance()->Exit(); CBTInputEngine::Destroy();
    // CBTAudioEngine::GetInstance()->Exit(); CBTAudioEngine::Destroy();

    CBTManaged::ClearReleasePool();
}

NS_CBT_END