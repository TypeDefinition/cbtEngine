#include "Sandbox.h"
#include "Scene/GameScene.h"

USING_NS_CBT;

CBTApplication* CBTApplication::CreateInstance()
{
    return new Sandbox("Sandbox");
}

Sandbox::Sandbox(const cbtStr& _name)
    : CBTApplication(_name)
{
}

Sandbox::~Sandbox()
{
}

void Sandbox::PostInit()
{
    CBTGameEngine::GetInstance()->GetSceneManager()->RegisterScene<GameScene>("Game Scene");
    CBTGameEngine::GetInstance()->GetSceneManager()->PushScene("Game Scene");
}

void Sandbox::PreUpdate() {}

void Sandbox::PostUpdate() {}

void Sandbox::PreExit() {}