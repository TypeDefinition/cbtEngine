#pragma once

// Include CBT
#include "CBTMacros.h"

NS_CBT_BEGIN

/**
    \brief
        A singleton template to make singletons. The derived class must implement a static function CreateInstance() which returns an instance of itself.\n\n

        How to use:\n
        \code{.cpp}
        class MySingleton : public CBTSingleton<MySingleton>
        {
            friend class CBTSingleton<MySingleton>;

        private:
            MySingleton() {}
            virtual ~MySingleton() {}

            static MySingleton* CreateInstance() { return cbtNew MySingleton(); }

        public:
            void Haa() {}
            void Doo() {}
            void Ken() {}
        };
        \endcode
*/
template <typename T>
class CBTSingleton
{
private:
    /// The singleton instance.
    static T* s_Instance;

protected:
    /**
        \brief Constructor

        \return A CBTSingleton
    */
    CBTSingleton() {}
    /**
        \brief Destructor
    */
    virtual ~CBTSingleton() {}

public:
    /**
        \brief
            Returns the singleton instance. If there isn't an instance, create one and return it.
            The derived class must implement a static function CreateInstance() which returns an instance of itself.

        \return Returns the singleton instance.

        \sa Destroy()
    */
    static T* GetInstance()
    {
        return s_Instance ? s_Instance : (s_Instance = T::CreateInstance());
    }

    /**
        \brief Destroy the singleton instance if there is one.

        \sa GetInstance()
    */
    static void Destroy()
    {
        if (s_Instance != nullptr)
        {
            delete s_Instance;
            s_Instance = nullptr;
        }
    }
};

template <typename T>
T* CBTSingleton<T>::s_Instance = nullptr;

NS_CBT_END