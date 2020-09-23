#pragma once

// Include CBT
#include "Debug/CBTDebug.h"
#include "CBTScene.h"

// Include STD
#include <functional>
#include <unordered_map>
#include <stack>

NS_CBT_BEGIN

class CBTSceneManager
{
private:
    typedef std::unordered_map<cbtStr, std::function<CBTScene*(void)>> SceneDictionary;

    // Variable(s)
    SceneDictionary m_RegisteredScenes;
    std::stack<CBTScene*> m_SceneStack;
    CBTScene* m_ActiveScene;
    CBTScene* m_NextScene;

    template <typename T>
    static CBTScene* CreateScene() { return new T(); }

public:
    // Constructor(s) & Destructor
    CBTSceneManager();
    ~CBTSceneManager();

    // Interface Function(s)
    CBTScene * GetActiveScene() { return m_ActiveScene; }
    const CBTScene * GetActiveScene() const { return m_ActiveScene; }

    cbtBool HasScene(const cbtStr& _sceneName) const;
    void ReplaceScene(const cbtStr& _sceneName);
    void PushScene(const cbtStr& _sceneName);
    void PopScene();

    void Update();

    template <typename T>
    void RegisterScene(const cbtStr& _sceneName)
    {
        CBT_ASSERT(!HasScene(_sceneName));
        m_RegisteredScenes.insert(std::pair<cbtStr, std::function<CBTScene*(void)>>(_sceneName, &CBTSceneManager::CreateScene<T>));
    }

    void UnregisterScene(const cbtStr& _sceneName)
    {
        CBT_ASSERT(HasScene(_sceneName));
        m_RegisteredScenes.erase(m_RegisteredScenes.find(_sceneName));
    }
};

NS_CBT_END