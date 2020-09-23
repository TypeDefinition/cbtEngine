#include "Sandbox.h"
#include "Scene/GameScene.h"

USING_NS_CBT;

cbtApplication* cbtApplication::CreateInstance()
{
    return new Sandbox("Sandbox");
}

Sandbox::Sandbox(const cbtStr& _name)
    : cbtApplication(_name)
{
}

Sandbox::~Sandbox()
{
}

void Sandbox::PostInit()
{
    cbtGameEngine::GetInstance()->GetSceneManager()->RegisterScene<GameScene>("Game Scene");
    cbtGameEngine::GetInstance()->GetSceneManager()->PushScene("Game Scene");
}

void Sandbox::PreUpdate() {}

void Sandbox::PostUpdate() {}

void Sandbox::PreExit() {}