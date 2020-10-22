#pragma once

// Include CBT
#include "Debug/cbtDebug.h"
#include "cbtScene.h"

// Include STD
#include <functional>
#include <unordered_map>
#include <stack>

NS_CBT_BEGIN

    class cbtSceneManager
    {
    private:
        typedef std::unordered_map<cbtStr, std::function<cbtScene*(void)>> SceneDictionary;

        // Variable(s)
        SceneDictionary m_RegisteredScenes;
        std::stack<cbtScene*> m_SceneStack;
        cbtScene* m_ActiveScene;
        cbtScene* m_NextScene;

        template<typename T>
        static cbtScene* CreateScene()
        {
            return new T();
        }

    public:
        // Constructor(s) & Destructor
        cbtSceneManager();

        ~cbtSceneManager();

        // Interface Function(s)
        cbtScene* GetActiveScene()
        {
            return m_ActiveScene;
        }

        const cbtScene* GetActiveScene() const
        {
            return m_ActiveScene;
        }

        cbtBool HasScene(const cbtStr& _sceneName) const;

        void ReplaceScene(const cbtStr& _sceneName);

        void PushScene(const cbtStr& _sceneName);

        void PopScene();

        void Update();

        template<typename T>
        void RegisterScene(const cbtStr& _sceneName)
        {
            CBT_ASSERT(!HasScene(_sceneName));
            m_RegisteredScenes.insert(
                    std::pair<cbtStr, std::function<cbtScene*(void)>>(_sceneName, &cbtSceneManager::CreateScene<T>));
        }

        void UnregisterScene(const cbtStr& _sceneName)
        {
            CBT_ASSERT(HasScene(_sceneName));
            m_RegisteredScenes.erase(m_RegisteredScenes.find(_sceneName));
        }
    };

NS_CBT_END