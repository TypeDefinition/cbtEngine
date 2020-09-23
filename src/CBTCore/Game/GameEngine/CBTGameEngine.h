#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/General/cbtSingleton.h"
#include "Game/Scene/cbtSceneManager.h"

NS_CBT_BEGIN

class cbtGameEngine : public cbtSingleton<cbtGameEngine>
{
    friend class cbtSingleton<cbtGameEngine>;

protected:
    cbtSceneManager* m_SceneManager;

    cbtGameEngine()
    : m_SceneManager(nullptr)
    {}
    virtual ~cbtGameEngine() {}

    static cbtGameEngine* CreateInstance() { return cbtNew cbtGameEngine(); }

public:
    void Init();
    void Update();
    void Exit();

    // System(s)
    inline const cbtSceneManager* GetSceneManager() const { return m_SceneManager; }
    inline cbtSceneManager* GetSceneManager() { return m_SceneManager; }
};

NS_CBT_END