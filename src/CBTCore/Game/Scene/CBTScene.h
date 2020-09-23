#pragma once

// Include CBT
#include "Core/General/CBTRef.h"
#include "Core/General/CBTSparseSet.h"
#include "Core/General/CBTFamily.h"
#include "Core/General/CBTHandleSet.h"
#include "Core//General/CBTArray.h"
#include "Core/Event/CBTEventDispatcher.h"
#include "Game/Component/CBTComponent.h"

// Include STD
#include <unordered_map>
#include <utility>

NS_CBT_BEGIN

class CBTScene : public CBTManaged
{
private:
    CBTEntityPool m_EntityPool;
    std::unordered_map<cbtS32, CBTComponentPool*> m_ComponentPools;

protected:
    virtual ~CBTScene()
    {
        for (std::unordered_map<cbtS32, CBTComponentPool*>::iterator iter = m_ComponentPools.begin(); iter != m_ComponentPools.end(); ++iter)
        {
            delete iter->second;
        }
    }

    template <typename T>
    void FilterEntities(std::vector<cbtECS>& _entities)
    {
        std::vector<cbtECS>::iterator iter = _entities.begin();
        while (iter != _entities.end())
        {
            iter = HasComponent<T>(*iter) ? std::next(iter) : _entities.erase(iter);
        }
    }

    template <typename T, typename U, typename ...Args>
    void FilterEntities(std::vector<cbtECS>& _entities)
    {
        std::vector<cbtECS>::iterator iter = _entities.begin();
        while (iter != _entities.end())
        {
            iter = HasComponent<T>(*iter) ? std::next(iter) : _entities.erase(iter);
        }
        FilterEntities<U, Args...>(_entities);
    }

    template <typename ComponentGroup, typename T>
    void PopulateComponentGroup(const std::vector<cbtECS>& _entities, ComponentGroup& _componentGroup)
    {
        CBTComponentPool* componentPool = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>())->second;
        T** groupArray = _componentGroup.GetArray<T>();
        for (cbtU32 i = 0; i < _entities.size(); ++i)
        {
            groupArray[i] = componentPool->Get<T>(_entities[i]);
        }
    }

    template <typename ComponentGroup, typename T, typename U, typename ...Args>
    void PopulateComponentGroup(const std::vector<cbtECS>& _entities, ComponentGroup& _componentGroup)
    {
        CBTComponentPool* componentPool = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>())->second;
        T** groupArray = _componentGroup.GetArray<T>();
        for (cbtU32 i = 0; i < _entities.size(); ++i)
        {
            groupArray[i] = componentPool->Get<T>(_entities[i]);
        }
        PopulateComponentGroup<ComponentGroup, U, Args...>(_entities, _componentGroup);
    }

public:
    // Constructor(s) & Destructor
    CBTScene() {}

    // Entity
    cbtECS AddEntity()
    {
        return m_EntityPool.Add();
    }

    void RemoveEntity(cbtECS _entity)
    {
        CBT_ASSERT(m_EntityPool.IsValid(_entity));
        for (std::unordered_map<cbtS32, CBTComponentPool*>::iterator iter = m_ComponentPools.begin(); iter != m_ComponentPools.end(); ++iter)
        {
            CBTComponentPool* componentPool = iter->second;
            if (componentPool->Has(_entity)) { componentPool->Remove(_entity); }
        }
        m_EntityPool.Remove(_entity);
    }

    // Component
    template <typename T>
    cbtBool HasComponent(cbtECS _entity) const
    {
        CBT_ASSERT(m_EntityPool.IsValid(_entity));
        std::unordered_map<cbtS32, CBTComponentPool*>::const_iterator iter = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>());
        return (iter == m_ComponentPools.end()) ? false : iter->second->Has(_entity);
    }

    template <typename T>
    const T* GetComponent(cbtECS _entity) const
    {
        CBT_ASSERT(m_EntityPool.IsValid(_entity));
        std::unordered_map<cbtS32, CBTComponentPool*>::const_iterator iter = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>());
        return (iter == m_ComponentPools.end()) ? nullptr : iter->second->Get<T>(_entity);
    }

    template <typename T>
    T* GetComponent(cbtECS _entity)
    {
        CBT_ASSERT(m_EntityPool.IsValid(_entity));
        std::unordered_map<cbtS32, CBTComponentPool*>::iterator iter = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>());
        return (iter == m_ComponentPools.end()) ? nullptr : iter->second->Get<T>(_entity);
    }

    template <typename T>
    const T** GetComponentArray() const
    {
        std::unordered_map<cbtS32, CBTComponentPool*>::const_iterator iter = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>());
        return (iter == m_ComponentPools.end()) ? nullptr : iter->second->GetArray<T>();
    }

    template <typename T>
    T** GetComponentArray()
    {
        std::unordered_map<cbtS32, CBTComponentPool*>::iterator iter = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>());
        return (iter == m_ComponentPools.end()) ? nullptr : iter->second->GetArray<T>();
    }

    template <typename T>
    cbtU32 GetComponentCount() const
    {
        std::unordered_map<cbtS32, CBTComponentPool*>::const_iterator iter = m_ComponentPools.find(CBTFamily<CBTManaged>::GetID<T>());
        return (iter == m_ComponentPools.end()) ? 0 : iter->second->GetCount();
    }

    template <typename T, typename ...Args>
    T* AddComponent(cbtECS _entity, Args&&... _args)
    {
        CBT_ASSERT(!HasComponent<T>(_entity));
        cbtS32 familyID = CBTFamily<CBTManaged>::GetID<T>();
        std::unordered_map<cbtS32, CBTComponentPool*>::iterator iter = m_ComponentPools.find(familyID);
        if (iter == m_ComponentPools.end())
        {
            CBTComponentPool* componentPool = CBTComponentPool::CreateComponentPool<T>();
            m_ComponentPools.insert(std::pair<cbtS32, CBTComponentPool*>(familyID, componentPool));
            iter = m_ComponentPools.find(familyID);
        }
        return iter->second->Add<T, Args...>(_entity, std::forward<Args>(_args)...);
    }

    template <typename T>
    void RemoveComponent(cbtECS _entity)
    {
        CBT_ASSERT(HasComponent<T>(_entity));
        cbtS32 familyID = CBTFamily<CBTManaged>::GetID<T>();
        m_ComponentPools[familyID]->Remove(_entity);
    }

    // Preferably put the component type with the least number of components as the first template type for best performance.
    template <typename T, typename U, typename ...Args>
    void GetComponentGroup(CBTComponentGroup<T, U, Args...>& _componentGroup)
    {
        T** componentArray = GetComponentArray<T>();
        cbtU32 componentCount = GetComponentCount<T>();
        std::vector<cbtECS> entities;
        for (cbtU32 i = 0; i < componentCount; ++i) { entities.push_back(componentArray[i]->GetEntity()); }
        FilterEntities<U, Args...>(entities);
        _componentGroup = CBTComponentGroup<T, U, Args...>((cbtU32)entities.size());
        PopulateComponentGroup<CBTComponentGroup<T, U, Args...>, T, U, Args...>(entities, _componentGroup);
    }
};

NS_CBT_END