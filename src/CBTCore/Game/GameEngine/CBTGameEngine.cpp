// Include CBT
#include "CBTGameEngine.h"

NS_CBT_BEGIN

void CBTGameEngine::Init()
{
    m_SceneManager = new CBTSceneManager();
}

void CBTGameEngine::Update()
{
    m_SceneManager->Update();
}

void CBTGameEngine::Exit()
{
    delete m_SceneManager;
    m_SceneManager = nullptr;
    CBTManaged::ClearReleasePool();
}

NS_CBT_END