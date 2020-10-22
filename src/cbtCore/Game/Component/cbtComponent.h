#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/General/cbtRef.h"
#include "Core/General/cbtPasskey.h"
#include "Core/General/cbtSparseSet.h"
#include "Core/General/cbtHandleSet.h"
#include "Core/General/cbtFlags.h"

// Include STD
#include <utility>

NS_CBT_BEGIN

// Forward Declaration(s)
    class cbtScene;

// Type Definition(s)
    typedef cbtU32 cbtECS;

    typedef cbtHandleSet<cbtECS> cbtEntityPool;

// Component Flag(s)
/// No Flags
#define CBT_COMPONENT_FLAG_NONE          0x00000000
/// All Flags
#define CBT_COMPONENT_FLAG_ALL           0xFFFFFFFF

/// There can only be 1 of this component per scene.
#define CBT_COMPONENT_FLAG_SCENE_UNIQUE  0x00000001
#define CBT_COMPONENT_FLAG_RESERVED30    0x00000002
#define CBT_COMPONENT_FLAG_RESERVED29    0x00000004
#define CBT_COMPONENT_FLAG_RESERVED28    0x00000008

#define CBT_COMPONENT_FLAG_RESERVED27    0x00000010
#define CBT_COMPONENT_FLAG_RESERVED26    0x00000020
#define CBT_COMPONENT_FLAG_RESERVED25    0x00000040
#define CBT_COMPONENT_FLAG_RESERVED24    0x00000080

#define CBT_COMPONENT_FLAG_RESERVED23    0x00000100
#define CBT_COMPONENT_FLAG_RESERVED22    0x00000200
#define CBT_COMPONENT_FLAG_RESERVED21    0x00000400
#define CBT_COMPONENT_FLAG_RESERVED20    0x00000800

#define CBT_COMPONENT_FLAG_RESERVED19    0x00001000
#define CBT_COMPONENT_FLAG_RESERVED18    0x00002000
#define CBT_COMPONENT_FLAG_RESERVED17    0x00004000
#define CBT_COMPONENT_FLAG_RESERVED16    0x00008000

#define CBT_COMPONENT_FLAG_RESERVED15    0x00010000
#define CBT_COMPONENT_FLAG_RESERVED14    0x00020000
#define CBT_COMPONENT_FLAG_RESERVED13    0x00040000
#define CBT_COMPONENT_FLAG_RESERVED12    0x00080000

#define CBT_COMPONENT_FLAG_RESERVED11    0x00100000
#define CBT_COMPONENT_FLAG_RESERVED10    0x00200000
#define CBT_COMPONENT_FLAG_RESERVED9     0x00400000
#define CBT_COMPONENT_FLAG_RESERVED8     0x00800000

#define CBT_COMPONENT_FLAG_RESERVED7     0x01000000
#define CBT_COMPONENT_FLAG_RESERVED6     0x02000000
#define CBT_COMPONENT_FLAG_RESERVED5     0x04000000
#define CBT_COMPONENT_FLAG_RESERVED4     0x08000000

#define CBT_COMPONENT_FLAG_RESERVED3     0x10000000
#define CBT_COMPONENT_FLAG_RESERVED2     0x20000000
#define CBT_COMPONENT_FLAG_RESERVED1     0x40000000
#define CBT_COMPONENT_FLAG_RESERVED0     0x80000000

/**
    \brief
        Base class of components. All components should inherit from cbtComponent.
*/
    class cbtComponent : public cbtManaged
    {
    private:
        /// The entity this component belongs to.
        cbtECS m_Entity;

    protected:
        /**
            \brief Protected Destructor. Use Ref::Release instead.
        */
        virtual ~cbtComponent()
        {
        }

    public:
        /**
            \brief Default Constructor.

            \return A cbtComponent of type T.
        */
        cbtComponent()
        {
        }

        /**
            \brief Initialises the entity.
        */
        void Init(cbtECS _entity)
        {
            m_Entity = _entity;
        }

        /**
            \brief This is called after a component has been initialised. This is where the initialisation of the derived classes should be done.
        */
        virtual void Awake()
        {
        }

        /**
            \brief Get the entity that this component belongs to.

            \return The entity that this component belongs to.
        */
        inline cbtECS GetEntity() const
        {
            return m_Entity;
        }
    };

/**
    \brief
        A container for a pool of components.
        Allows CBTScene to store all the components in a hash map, which would be impossible otherwise
        as the various components do not have a common base class.
*/
    class cbtComponentPool
    {
    private:
        /// The number of pages in the sparse set.
        static constexpr cbtU32 PAGE_COUNT = 512;
        /// The number of paragraphs per page in the sparse set.
        static constexpr cbtU32 PARAGRAPH_COUNT = 512;

        /// The sparse set containing the components.
        void* m_SparseSet = nullptr;
        /// A function to remove a component. As we may not know the component type when removing, we need to store it as a lambda function in advance.
        std::function<void(cbtECS)> m_Remove = nullptr;
        /// A function to check if we have a component. As we may not know the component type when checking, we need to store it as a lambda function in advance.
        std::function<cbtBool(cbtECS)> m_Has = nullptr;
        /// A function to check how many of the components we have. As we may not know the component type when checking, we need to store it as a lambda function in advance.
        std::function<cbtECS(void)> m_GetCount = nullptr;
        ///  A function to delete the components in the destructor. As we may not know the component type when deleting, we need to store it as a lambda function in advance.
        std::function<void(void)> m_Destructor = nullptr;

        /**
            \brief Private Constructor. Create an instance of CBTComponentPool using CreateComponentPool.
        */
        cbtComponentPool()
        {
        }

    public:
        /**
            \brief Destructor
        */
        ~cbtComponentPool()
        {
            m_Destructor();
        }

        /**
            \brief Remove the component belonging to an entity.

            \param _entity The entity whose component to remove.
        */
        void Remove(cbtECS _entity)
        {
            m_Remove(_entity);
        }

        /**
            \brief Check if an entity has a component store in this pool.

            \param _entity The entity whose component to check.

            \return Returns true if the component exists. Otherwise, return false.
        */
        cbtBool Has(cbtECS _entity) const
        {
            return m_Has(_entity);
        }

        /**
            \brief Get the number of components in this pool.

            \return The number of components in this pool.
        */
        cbtU32 GetCount() const
        {
            return m_GetCount();
        }

        /**
            \brief Get the component belonging to an entity.

            \param _entity The entity whose component to retrieve.

            \return The component belonging to the entity.
        */
        template<typename T>
        const T* Get(cbtECS _entity) const
        {
            typedef cbtSparseSet<T*, PAGE_COUNT, PARAGRAPH_COUNT> SparseSet;
            return (*static_cast<SparseSet*>(m_SparseSet))[cbtEntityPool::GetIndex(_entity)];
        }

        /**
            \brief Get the component belonging to an entity.

            \param _entity The entity whose component to retrieve.

            \return The component belonging to the entity.
        */
        template<typename T>
        T* Get(cbtECS _entity)
        {
            typedef cbtSparseSet<T*, PAGE_COUNT, PARAGRAPH_COUNT> SparseSet;
            return (*static_cast<SparseSet*>(m_SparseSet))[cbtEntityPool::GetIndex(_entity)];
        }

        /**
            \brief Get a pointer to the internal array of component pointers.

            \return A pointer to the internal array of component pointers.
        */
        template<typename T>
        const T** GetArray() const
        {
            typedef cbtSparseSet<T*, PAGE_COUNT, PARAGRAPH_COUNT> SparseSet;
            return static_cast<SparseSet*>(m_SparseSet)->GetArray();
        }

        /**
            \brief Get a pointer to the internal array of component pointers.

            \return A pointer to the internal array of component pointers.
        */
        template<typename T>
        T** GetArray()
        {
            typedef cbtSparseSet<T*, PAGE_COUNT, PARAGRAPH_COUNT> SparseSet;
            return static_cast<SparseSet*>(m_SparseSet)->GetArray();
        }

        /**
            \brief Add a component and assign it to an entity.

            \param _entity The entity the components belong to.
            \param _args The arguments necessary for the constructor of the component.

            \return The created component.
        */
        template<typename T, typename ...Args>
        T* Add(cbtECS _entity, Args&& ... _args)
        {
            typedef cbtSparseSet<T*, PAGE_COUNT, PARAGRAPH_COUNT> SparseSet;
            SparseSet* sparseSet = static_cast<SparseSet*>(m_SparseSet);

            if (cbtFlags<T>::HasFlags(CBT_COMPONENT_FLAG_SCENE_UNIQUE))
            {
                CBT_ASSERT(sparseSet->GetCount() == 0);
            }

            T* component = cbtNew T();
            component->Retain();
            component->Init(_entity);
            sparseSet->Insert(cbtEntityPool::GetIndex(_entity), component);
            component->Awake(std::forward<Args>(_args)...);

            return component;
        }

        /**
            \brief
                Create a CBTComponentPool to store components of type T.
                Once a CBTComponentPool is created to store a certain type of component, it cannot store any other type of components.

                \return A CBTComponentPool that can store components of type T.
        */
        template<typename T>
        static cbtComponentPool* CreateComponentPool()
        {
            typedef cbtSparseSet<T*, PAGE_COUNT, PARAGRAPH_COUNT> SparseSet;
            cbtComponentPool* componentPool = cbtNew cbtComponentPool();
            componentPool->m_SparseSet = static_cast<void*>(cbtNew SparseSet());
            componentPool->m_Remove = [componentPool](cbtECS _entity) -> void
            {
              SparseSet* sparseSet = static_cast<SparseSet*>(componentPool->m_SparseSet);
              cbtECS index = cbtEntityPool::GetIndex(_entity);
              (*sparseSet)[index]->AutoRelease();
              sparseSet->Remove(index);
            };
            componentPool->m_Has = [componentPool](cbtECS _entity) -> cbtBool
            {
              return static_cast<SparseSet*>(componentPool->m_SparseSet)->Has(cbtEntityPool::GetIndex(_entity));
            };
            componentPool->m_GetCount = [componentPool](void) -> cbtU32
            {
              return static_cast<SparseSet*>(componentPool->m_SparseSet)->GetCount();
            };
            componentPool->m_Destructor = [componentPool](void) -> void
            {
              SparseSet* sparseSet = static_cast<SparseSet*>(componentPool->m_SparseSet);
              T** componentArray = sparseSet->GetArray();
              for (cbtU32 i = 0; i < sparseSet->GetCount(); ++i)
              { componentArray[i]->AutoRelease(); }
              delete sparseSet;
            };
            return componentPool;
        }
    };

/**
    \brief
        A CBTComponentGroup is used to store arrays of components belonging to entities that have all of the specified components.
        All the components at the same index in the arrays belong to the same entities.
        This means that in a CBTComponentGroup<CBTLightComponent, CBTTransformComponent, CBTCameraComponent>,
        all the CBTLightComponent, CBTTransformComponent and CBTCameraComponent at index 0 belongs to the same entity,
        all the CBTLightComponent, CBTTransformComponent and CBTCameraComponent at index 1 belongs to the same entity,
        all the CBTLightComponent, CBTTransformComponent and CBTCameraComponent at index 2 belongs to the same entity and so on.
*/
    template<typename T, typename U, typename ...Args>
    class cbtComponentGroup
    {
    private:
        /// The array size for each component.
        cbtU32 m_ArraySize;
        /// The arrays of components.
        void* m_ComponentArrays[CBT_TEMPLATE_COUNT<T, U, Args...>]; // An array of void pointers.

        /**
            \brief Create a component array at a specific index of m_ComponentArrays.

            \param _startIndex The index of m_ComponentArrays to create the array.
        */
        template<typename Component>
        void CreateArrays(cbtU32 _startIndex = 0)
        {
            Component** componentArray = cbtNew Component* [m_ArraySize];
            m_ComponentArrays[_startIndex] = static_cast<void*>(componentArray);
            std::memset(componentArray, 0, sizeof(Component*) * m_ArraySize);
        }

        /**
            \brief Create a component array at a specific index of m_ComponentArrays.

            \param _startIndex The index of m_ComponentArrays to create the array.
        */
        template<typename ComponentA, typename ComponentB, typename ...ComponentArgs>
        void CreateArrays(cbtU32 _startIndex = 0)
        {
            ComponentA** componentArray = cbtNew ComponentA* [m_ArraySize];
            m_ComponentArrays[_startIndex] = static_cast<void*>(componentArray);
            std::memset(componentArray, 0, sizeof(ComponentA*) * m_ArraySize);
            CreateArrays < ComponentB, ComponentArgs...>(_startIndex + 1);
        }

        /**
            \brief Copy a component array of another component group at a specific index of m_ComponentArrays.

            \param _other The other component group whose array to copy.
            \param _startIndex The index of m_ComponentArrays to copy the array.
        */
        template<typename Component>
        void CopyArrays(const cbtComponentGroup& _other, cbtU32 _startIndex = 0)
        {
            Component** dstArray = static_cast<Component**>(m_ComponentArrays[_startIndex]);
            Component** srcArray = static_cast<Component**>(_other.m_ComponentArrays[_startIndex]);
            std::memcpy(dstArray, srcArray, sizeof(Component*) * m_ArraySize);
        }

        /**
            \brief Copy a component array of another component group at a specific index of m_ComponentArrays.

            \param _other The other component group whose array to copy.
            \param _startIndex The index of m_ComponentArrays to copy the array.
        */
        template<typename ComponentA, typename ComponentB, typename ...ComponentArgs>
        void CopyArrays(const cbtComponentGroup& _other, cbtU32 _startIndex = 0)
        {
            ComponentA** dstArray = static_cast<ComponentA**>(m_ComponentArrays[_startIndex]);
            ComponentA** srcArray = static_cast<ComponentA**>(_other.m_ComponentArrays[_startIndex]);
            std::memcpy(dstArray, srcArray, sizeof(ComponentA*) * m_ArraySize);
            CopyArrays < ComponentB, ComponentArgs...>(_other, _startIndex + 1);
        }

        /**
            \brief Delete a component array at a specific index of m_ComponentArrays.

            \param _startIndex The index of m_ComponentArrays to delete the array.
        */
        template<typename Component>
        void DeleteArrays(cbtU32 _startIndex = 0)
        {
            Component** componentArray = static_cast<Component**>(m_ComponentArrays[_startIndex]);
            m_ComponentArrays[_startIndex] = nullptr;
            delete[] componentArray;
        }

        /**
            \brief Delete a component array at a specific index of m_ComponentArrays.

            \param _startIndex The index of m_ComponentArrays to delete the array.
        */
        template<typename ComponentA, typename ComponentB, typename ...ComponentArgs>
        void DeleteArrays(cbtU32 _startIndex = 0)
        {
            ComponentA** componentArray = static_cast<ComponentA**>(m_ComponentArrays[_startIndex]);
            m_ComponentArrays[_startIndex] = nullptr;
            delete[] componentArray;
            DeleteArrays < ComponentB, ComponentArgs...>(_startIndex + 1);
        }

    public:
        /**
            \brief Constructor

            \param _arraySize How many components per type this component pool can store.

            \return A CBTComponentGroup.
        */
        cbtComponentGroup(cbtU32 _arraySize = 0)
                :m_ArraySize(_arraySize)
        {
            CreateArrays<T, U, Args...>();
        }

        /**
            \brief Copy Constructor

            \param _other The CBTComponentGroup to copy.

            \return A CBTComponentGroup.
        */
        cbtComponentGroup(const cbtComponentGroup& _other)
                :m_ArraySize(_other.m_ArraySize)
        {
            CreateArrays<T, U, Args...>();
            CopyArrays<T, U, Args...>(_other);
        }

        /**
            \brief Destructor
        */
        ~cbtComponentGroup()
        {
            DeleteArrays<T, U, Args...>();
        }

        /**
            \brief How many components this pool can store.

            \return How many components this pool can store.
        */
        inline cbtU32 GetArraySize() const
        {
            return m_ArraySize;
        }

        /**
            \brief Get the array of components of type Component.

            \return The array of components of type Component.
        */
        template<typename Component>
        const Component** GetArray() const
        {
            cbtU32 index = CBTTemplateIndex<Component, T, U, Args...>();
            Component** componentArray = static_cast<const Component**>(m_ComponentArrays[index]);
            return componentArray;
        }

        /**
            \brief Get the array of components of type Component.

            \return The array of components of type Component.
        */
        template<typename Component>
        Component** GetArray()
        {
            cbtU32 index = CBTTemplateIndex<Component, T, U, Args...>();
            Component** componentArray = static_cast<Component**>(m_ComponentArrays[index]);
            return componentArray;
        }

        /**
            \brief Copy another CBTComponentPool.

            \param _other The component pool to copy.

            \return This component pool after copying _other.
        */
        cbtComponentGroup& operator=(const cbtComponentGroup& _other)
        {
            m_ArraySize = _other.m_ArraySize;
            DeleteArrays<T, U, Args...>();
            CreateArrays<T, U, Args...>();
            CopyArrays<T, U, Args...>(_other);

            return { *this };
        }
    };

NS_CBT_END