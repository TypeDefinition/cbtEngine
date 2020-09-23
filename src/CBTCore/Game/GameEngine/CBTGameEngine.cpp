// Include CBT
#include "cbtGameEngine.h"

NS_CBT_BEGIN

void cbtGameEngine::Init()
{
    m_SceneManager = new cbtSceneManager();
}

void cbtGameEngine::Update()
{
    m_SceneManager->Update();
}

void cbtGameEngine::Exit()
{
    delete m_SceneManager;
    m_SceneManager = nullptr;
    cbtManaged::ClearReleasePool();
}

NS_CBT_END