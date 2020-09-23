#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTSingleton.h"
#include "Game/Scene/CBTSceneManager.h"

NS_CBT_BEGIN

class CBTGameEngine : public CBTSingleton<CBTGameEngine>
{
    friend class CBTSingleton<CBTGameEngine>;

protected:
    CBTSceneManager* m_SceneManager;

    CBTGameEngine()
    : m_SceneManager(nullptr)
    {}
    virtual ~CBTGameEngine() {}

    static CBTGameEngine* CreateInstance() { return cbtNew CBTGameEngine(); }

public:
    void Init();
    void Update();
    void Exit();

    // System(s)
    inline const CBTSceneManager* GetSceneManager() const { return m_SceneManager; }
    inline CBTSceneManager* GetSceneManager() { return m_SceneManager; }
};

NS_CBT_END