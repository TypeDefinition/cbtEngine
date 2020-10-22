#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Debug/cbtDebug.h"

// Include STD
#include <vector>
#include <mutex>

NS_CBT_BEGIN

/**
    \brief
        A reference counted case class.
        When the reference count of a CBTManaged is 0, the object is deleted.
        The starting value of the reference counter upon creation is 1, but AutoRelease() is called immediately.
        Use Retain() to prevent deletion of the object.
        When using CBTManaged, do not call it's destructor. Use Retain() and Release() to manage the deletion of the object.
        You can also delay the deletion of the object using AutoRelease(). When AutoRelease() is called, the object reference count
        of the object is decreased, but it will only be checked for deletion when ClearReleasePool() is called.
 */
    class cbtManaged
    {
    private:
        /// The maximum size of the auto release pool.
        static constexpr cbtU32 MAX_POOL_SIZE = 65536;
        /// The buffer containing the CBTMananged objects that have called AutoRelease().
        static cbtManaged* s_Buffer[MAX_POOL_SIZE * 2];
        /// The index in s_Buffer where the array of pointers of CBTManaged pointer to be checked for deletion starts.
        static cbtU32 s_ReleaseStart;
        /// The number of CBTManaged objects to be checked for deletion.
        static cbtU32 s_ReleaseCount;

        /// Mutex for checking and deleting CBTManaged objects.
        static std::mutex s_ReleaseMutex;
        /// Mutex for checking and deleting CBTManaged objects.
        static std::mutex s_ClearMutex;

        /// The reference count of this object. The starting value of m_RefCount upon creation is 1.
        cbtS32 m_RefCount = 1;

    protected:
        /**
            \brief Protected Constructor

            \return A CBTManaged.
        */
        cbtManaged()
        {
            AutoRelease();
        }

        /**
            \brief Destructor
        */
        virtual ~cbtManaged()
        {
        }

    public:
        /**
            \brief Increase the reference count by 1.

            \sa Release, AutoRelease
        */
        void Retain()
        {
            ++m_RefCount;
        }

        /**
            \brief Decrease the reference count by 1. If the reference count reaches 0, delete the object immediately.

            \sa Retain, AutoRelease
        */
        void Release()
        {
            CBT_ASSERT(m_RefCount > 0);
            --m_RefCount;
            if (m_RefCount == 0)
            {
                delete this;
            }
        }

        /**
            \brief Decrease the reference count by 1. Add it to the release pool where it will be checked for deletion upon calling ClearReleasePool().

            \sa Retain, Release
        */
        void AutoRelease()
        {
            CBT_ASSERT(m_RefCount > 0);
            std::lock_guard<std::mutex> releaseLock(s_ReleaseMutex);
            s_Buffer[s_ReleaseStart + s_ReleaseCount] = this;
            ++s_ReleaseCount;
        }

        /**
            \brief Checks all the objects that have been added to the release pool. If their reference count is 0, delete them.
        */
        static void ClearReleasePool()
        {
            // There is a chance that the deletion of objects will trigger more objects to be released for deletion.
            // Therefore this will loop till there is nothing left to delete.
            while (true)
            {
                std::lock_guard<std::mutex> clearLock(s_ClearMutex);
                std::unique_lock<std::mutex> releaseLock(s_ReleaseMutex);

                // We do this swap in case at any point during the deletion of Refs, more are added to the release pool.
                cbtU32 clearCount = s_ReleaseCount;
                cbtU32 clearStart = s_ReleaseStart;

                s_ReleaseStart = (s_ReleaseStart + MAX_POOL_SIZE) % (MAX_POOL_SIZE * 2);
                s_ReleaseCount = 0;

                releaseLock.unlock();

                // If there is nothing to clear, stop the loop.
                if (clearCount == 0)
                { break; }
                for (cbtU32 i = 0; i < clearCount; ++i)
                {
                    if (s_Buffer[clearStart + i]->m_RefCount <= 0)
                    {
                        s_Buffer[clearStart + i]->Release();
                        s_Buffer[clearStart + i] = nullptr;
                    }
                }
            }
        }
    };

/**
    \brief
        A wrapper for a pointer to an object of class T which must be a derived class of CBTManaged.
        When pointing to a CBTManaged object, the reference count of the object is increased by 1.
        When no longer pointing to the CBTManaged object, the reference count of the object is decreased by 1.
*/
    template<class T>
    struct cbtRef
    {
    private:
        /// A pointer to the object.
        CBT_ENABLE_IF_DERIVED_1(T*, cbtManaged, T) m_Managed;

    public:
        /**
            \brief Copy Constructor. Point to the same CBTManaged object as _other.

            \param _other The CBTRef to copy. The reference count of the pointed object is increased by 1.

            \return A CBTRef pointing to the same CBTManaged object as _other.
        */
        cbtRef(const cbtRef& _other)
                :m_Managed(_other.m_Managed)
        {
            if (m_Managed)
            { m_Managed->Retain(); }
        }

        /**
            \brief Constructor

            \param _managed The CBTManaged object to point to. The reference count of the object is increased by 1.

            \return A CBTRef pointing to CBTManaged object _managed.
        */
        cbtRef(T& _managed)
                :m_Managed((&_managed))
        {
            m_Managed->Retain();
        }

        /**
            \brief Constructor

            \param _managed The CBTManaged object to point to. The reference count of the object is increased by 1.

            \return A CBTRef pointing to CBTManaged object _managed.
        */
        cbtRef(void* _managed = nullptr)
                :m_Managed(static_cast<T*>(_managed))
        {
            if (m_Managed)
            { m_Managed->Retain(); }
        }

        /**
            \brief Destructor. The pointed object's reference count is decreased by 1.
        */
        ~cbtRef()
        {
            if (m_Managed)
            { m_Managed->AutoRelease(); }
        }

        /**
            \brief Get the raw pointer of the pointed object.

            \return The raw pointer of the pointed object.
        */
        const T* GetRawPointer() const
        {
            return m_Managed;
        }

        /**
            \brief Get the raw pointer of the pointed object.

            \return The raw pointer of the pointed object.
        */
        T* GetRawPointer()
        {
            return m_Managed;
        }

        // Less Than Operator
        /*cbtBool operator<(const CBTRef<T>& _other) const
        {
            return &(*this) < &_other;
        }*/

        // Assignment Operator
        /**
            \brief Point to the same CBTManaged object as _other.
            The new pointed object's reference count is increased by 1.
            The current pointed object's reference count is decreased by 1.

            \return The current CBTRef object.
        */
        cbtRef<T>& operator=(const cbtRef& _other)
        {
            if (_other.m_Managed)
            { _other.m_Managed->Retain(); }
            if (m_Managed)
            { m_Managed->AutoRelease(); }
            m_Managed = _other.m_Managed;
            return { *this };
        }

        /**
            \brief Point to a new CBTManaged object.
            The new pointed object's reference count is increased by 1.
            The current pointed object's reference count is decreased by 1.

            \return The current CBTRef object.
        */
        cbtRef<T>& operator=(T& _managed)
        {
            _managed.Retain();
            if (m_Managed)
            { m_Managed->AutoRelease(); }
            m_Managed = &_managed;
            return { *this };
        }

        /**
            \brief Point to a new CBTManaged object.
            The new pointed object's reference count is increased by 1.
            The current pointed object's reference count is decreased by 1.

            \return The current CBTRef object.
        */
        cbtRef<T>& operator=(void* _managed)
        {
            if (_managed)
            { static_cast<T*>(_managed)->Retain(); }
            if (m_Managed)
            { m_Managed->AutoRelease(); }
            m_Managed = static_cast<T*>(_managed);
            return { *this };
        }

        // Equal Operator
        /**
            \brief Checks if this CBTRef is pointing to the same object as _other.

            \param _other The CBTRef to check against.

            \return Returns true if pointing to the same object. Otherwise, returns false.
        */
        cbtBool operator==(const cbtRef& _other) const
        {
            return m_Managed == _other.m_Managed;
        }

        /**
            \brief Checks if this CBTRef is pointing to _managed.

            \param _managed The CBTManaged object to check against.

            \return Returns true if pointing to _managed. Otherwise, returns false.
        */
        cbtBool operator==(const T& _managed) const
        {
            return m_Managed == &_managed;
        }

        /**
            \brief Checks if this CBTRef is pointing to _managed.

            \param _managed The CBTManaged object to check against.

            \return Returns true if pointing to _managed. Otherwise, returns false.
        */
        cbtBool operator==(const void* _managed) const
        {
            return m_Managed == static_cast<T*>(_managed);
        }

        /**
            \brief Checks if this CBTRef is not pointing to the same object as _other.

            \param _other The CBTRef to check against.

            \return Returns false if pointing to the same object. Otherwise, returns true.
        */
        cbtBool operator!=(const cbtRef& _other) const
        {
            return m_Managed != _other.m_Managed;
        }

        /**
            \brief Checks if this CBTRef is not pointing to _managed.

            \param _managed The CBTManaged object to check against.

            \return Returns false if pointing to _managed. Otherwise, returns true.
        */
        cbtBool operator!=(const T& _managed) const
        {
            return m_Managed != &_managed;
        }

        /**
            \brief Checks if this CBTRef is not pointing to _managed.

            \param _managed The CBTManaged object to check against.

            \return Returns false if pointing to _managed. Otherwise, returns true.
        */
        cbtBool operator!=(const void* _managed) const
        {
            return m_Managed != static_cast<const T*>(_managed);
        }

        // Member Access Operator(s)
        /**
            \brief Get the raw pointer of the pointed object.

            \return The raw pointer of the pointed object.
        */
        const T* operator->() const
        {
            return m_Managed;
        }

        /**
            \brief Get the raw pointer of the pointed object.

            \return The raw pointer of the pointed object.
        */
        T* operator->()
        {
            return m_Managed;
        }

        /**
            \brief Get the reference of the pointed object.

            \return The reference of the pointed object.
        */
        const T& operator*() const
        {
            return *m_Managed;
        }

        /**
            \brief Get the reference of the pointed object.

            \return The reference of the pointed object.
        */
        T& operator*()
        {
            return *m_Managed;
        }
    };

NS_CBT_END