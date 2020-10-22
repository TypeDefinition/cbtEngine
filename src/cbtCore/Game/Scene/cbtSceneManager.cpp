// Include CBT
#include "cbtSceneManager.h"

NS_CBT_BEGIN

// Constructor(s) & Destructor
    cbtSceneManager::cbtSceneManager()
            :m_ActiveScene(nullptr), m_NextScene(nullptr)
    {
    }

    cbtSceneManager::~cbtSceneManager()
    {
        if (m_ActiveScene)
        { m_ActiveScene->Release(); }
        while (!m_SceneStack.empty())
        { PopScene(); }
    }

// Interface Function(s)
    cbtBool cbtSceneManager::HasScene(const cbtStr& _sceneName) const
    {
        return m_RegisteredScenes.find(_sceneName) != m_RegisteredScenes.end();
    }

    void cbtSceneManager::ReplaceScene(const cbtStr& _sceneName)
    {
        CBT_ASSERT(HasScene(_sceneName));
        PopScene();
        PushScene(_sceneName);
    }

    void cbtSceneManager::PushScene(const cbtStr& _sceneName)
    {
        CBT_ASSERT(HasScene(_sceneName));

        // Create a new scene and push it onto the stack.
        cbtScene* scene = m_RegisteredScenes.find(_sceneName)->second();
        scene->Retain();
        m_SceneStack.push(scene);

        // Set the next scene.
        m_NextScene = scene;
    }

    void cbtSceneManager::PopScene()
    {
        CBT_ASSERT(!m_SceneStack.empty());

        // Pop the scene.
        m_SceneStack.top()->AutoRelease();
        m_SceneStack.pop();

        // Set the next scene.
        m_NextScene = m_SceneStack.empty() ? nullptr : m_SceneStack.top();
    }

    void cbtSceneManager::Update()
    {
        // Check if there is a scene change.
        if (m_ActiveScene == m_NextScene)
        { return; }
        if (m_ActiveScene)
        { m_ActiveScene->AutoRelease(); }
        m_ActiveScene = m_NextScene;

        // Add 1 to the active scene's reference count, so that if it is popped, it will not get deleted until the scene has changed.
        if (m_ActiveScene)
        { m_ActiveScene->Retain(); }
    }

NS_CBT_END