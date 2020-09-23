#pragma once

// Include CBT
#include "Application/cbtApplication.h"
#include "Game/Scene/cbtScene.h"
#include "Rendering/RenderEngine/cbtRenderEngine.h"

USING_NS_CBT;

class GameScene : public NS_CBT::cbtScene
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