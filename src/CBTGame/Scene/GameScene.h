#pragma once

// Include CBT
#include "Application/CBTApplication.h"
#include "Game/Scene/CBTScene.h"
#include "Rendering/RenderEngine/CBTRenderEngine.h"

USING_NS_CBT;

class GameScene : public NS_CBT::CBTScene
{
protected:
    cbtECS m_Light;
    cbtECS m_Floor;

    // Destructor
    virtual ~GameScene();

public:
    // Constructor(s)
    GameScene();
};