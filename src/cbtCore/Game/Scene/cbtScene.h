#pragma once

// Include CBT
#include "Core/General/cbtRef.h"
#include "Core/General/cbtSparseSet.h"
#include "Core/General/cbtFamily.h"
#include "Core/General/cbtHandleSet.h"
#include "Core/Event/cbtEventDispatcher.h"
#include "Game/Component/cbtComponent.h"

// Include STD
#include <unordered_map>
#include <utility>

NS_CBT_BEGIN

    class cbtScene : public cbtManaged
    {
    private:
        cbtEntityPool m_EntityPool;
        std::unordered_map<cbtS32, cbtComponentPool*> m_ComponentPools;

    protected:
        virtual ~cbtScene()
        {
            for (std::unordered_map<cbtS32, cbtComponentPool*>::iterator iter = m_ComponentPools.begin();
                 iter != m_ComponentPools.end(); ++iter)
            {
                delete iter->second;
            }
        }

        template<typename T>
        void FilterEntities(std::vector<cbtECS>& _entities)
        {
            std::vector<cbtECS>::iterator iter = _entities.begin();
            while (iter != _entities.end())
            {
                iter = HasComponent<T>(*iter) ? std::next(iter) : _entities.erase(iter);
            }
        }

        template<typename T, typename U, typename ...Args>
        void FilterEntities(std::vector<cbtECS>& _entities)
        {
            std::vector<cbtECS>::iterator iter = _entities.begin();
            while (iter != _entities.end())
            {
                iter = HasComponent<T>(*iter) ? std::next(iter) : _entities.erase(iter);
            }
            FilterEntities<U, Args...>(_entities);
        }

        template<typename ComponentGroup, typename T>
        void PopulateComponentGroup(const std::vector<cbtECS>& _entities, ComponentGroup& _componentGroup)
        {
            cbtComponentPool* componentPool = m_ComponentPools.find(cbtFamily<cbtManaged>::GetID<T>())->second;
            T** groupArray = _componentGroup.template GetArray<T>();
            for (cbtU32 i = 0; i < _entities.size(); ++i)
            {
                groupArray[i] = componentPool->template Get<T>(_entities[i]);
            }
        }

        template<typename ComponentGroup, typename T, typename U, typename ...Args>
        void PopulateComponentGroup(const std::vector<cbtECS>& _entities, ComponentGroup& _componentGroup)
        {
            cbtComponentPool* componentPool = m_ComponentPools.find(cbtFamily<cbtManaged>::GetID<T>())->second;
            T** groupArray = _componentGroup.template GetArray<T>();
            for (cbtU32 i = 0; i < _entities.size(); ++i)
            {
                groupArray[i] = componentPool->template Get<T>(_entities[i]);
            }
            PopulateComponentGroup<ComponentGroup, U, Args...>(_entities, _componentGroup);
        }

    public:
        // Constructor(s) & Destructor
        cbtScene()
        {
        }

        // Entity
        cbtECS AddEntity()
        {
            return m_EntityPool.Add();
        }

        void RemoveEntity(cbtECS _entity)
        {
            CBT_ASSERT(m_EntityPool.IsValid(_entity));
            for (std::unordered_map<cbtS32, cbtComponentPool*>::iterator iter = m_ComponentPools.begin();
                 iter != m_ComponentPools.end(); ++iter)
            {
                cbtComponentPool* componentPool = iter->second;
                if (componentPool->Has(_entity))
                { componentPool->Remove(_entity); }
            }
            m_EntityPool.Remove(_entity);
        }

        // Component
        template<typename T>
        cbtBool HasComponent(cbtECS _entity) const
        {
            CBT_ASSERT(m_EntityPool.IsValid(_entity));
            std::unordered_map<cbtS32, cbtComponentPool*>::const_iterator iter = m_ComponentPools.find(
                    cbtFamily<cbtManaged>::GetID<T>());
            return (iter == m_ComponentPools.end()) ? false : iter->second->Has(_entity);
        }

        template<typename T>
        const T* GetComponent(cbtECS _entity) const
        {
            CBT_ASSERT(m_EntityPool.IsValid(_entity));
            std::unordered_map<cbtS32, cbtComponentPool*>::const_iterator iter = m_ComponentPools.find(
                    cbtFamily<cbtManaged>::GetID<T>());
            return (iter == m_ComponentPools.end()) ? nullptr : iter->second->Get<T>(_entity);
        }

        template<typename T>
        T* GetComponent(cbtECS _entity)
        {
            CBT_ASSERT(m_EntityPool.IsValid(_entity));
            std::unordered_map<cbtS32, cbtComponentPool*>::iterator iter = m_ComponentPools.find(
                    cbtFamily<cbtManaged>::GetID<T>());
            return (iter == m_ComponentPools.end()) ? nullptr : iter->second->Get<T>(_entity);
        }

        template<typename T>
        const T** GetComponentArray() const
        {
            std::unordered_map<cbtS32, cbtComponentPool*>::const_iterator iter = m_ComponentPools.find(
                    cbtFamily<cbtManaged>::GetID<T>());
            return (iter == m_ComponentPools.end()) ? nullptr : iter->second->GetArray<T>();
        }

        template<typename T>
        T** GetComponentArray()
        {
            std::unordered_map<cbtS32, cbtComponentPool*>::iterator iter = m_ComponentPools.find(
                    cbtFamily<cbtManaged>::GetID<T>());
            return (iter == m_ComponentPools.end()) ? nullptr : iter->second->GetArray<T>();
        }

        template<typename T>
        cbtU32 GetComponentCount() const
        {
            std::unordered_map<cbtS32, cbtComponentPool*>::const_iterator iter = m_ComponentPools.find(
                    cbtFamily<cbtManaged>::GetID<T>());
            return (iter == m_ComponentPools.end()) ? 0 : iter->second->GetCount();
        }

        template<typename T, typename ...Args>
        T* AddComponent(cbtECS _entity, Args&& ... _args)
        {
            CBT_ASSERT(!HasComponent<T>(_entity));
            cbtS32 familyID = cbtFamily<cbtManaged>::GetID<T>();
            std::unordered_map<cbtS32, cbtComponentPool*>::iterator iter = m_ComponentPools.find(familyID);
            if (iter == m_ComponentPools.end())
            {
                cbtComponentPool* componentPool = cbtComponentPool::CreateComponentPool<T>();
                m_ComponentPools.insert(std::pair<cbtS32, cbtComponentPool*>(familyID, componentPool));
                iter = m_ComponentPools.find(familyID);
            }
            return iter->second->Add<T, Args...>(_entity, std::forward<Args>(_args)...);
        }

        template<typename T>
        void RemoveComponent(cbtECS _entity)
        {
            CBT_ASSERT(HasComponent<T>(_entity));
            cbtS32 familyID = cbtFamily<cbtManaged>::GetID<T>();
            m_ComponentPools[familyID]->Remove(_entity);
        }

        // Preferably put the component type with the least number of components as the first template type for best performance.
        template<typename T, typename U, typename ...Args>
        void GetComponentGroup(cbtComponentGroup<T, U, Args...>& _componentGroup)
        {
            T** componentArray = GetComponentArray<T>();
            cbtU32 componentCount = GetComponentCount<T>();
            std::vector<cbtECS> entities;
            for (cbtU32 i = 0; i < componentCount; ++i)
            { entities.push_back(componentArray[i]->GetEntity()); }
            FilterEntities<U, Args...>(entities);
            _componentGroup = cbtComponentGroup<T, U, Args...>((cbtU32)entities.size());
            PopulateComponentGroup<cbtComponentGroup<T, U, Args...>, T, U, Args...>(entities, _componentGroup);
        }
    };

NS_CBT_END