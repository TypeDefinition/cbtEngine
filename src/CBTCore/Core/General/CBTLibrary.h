#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTRef.h"

// Include STD
#include <unordered_map>

/**
    \brief
        A template class which stores items of type T using a cbtStr as the key.
        When items are stored, they are given a unique name. They are also retrieved using that name.
*/
template <typename T>
class CBTLibrary
{
protected:
    /// The items in the CBTLibrary.
    std::unordered_map<cbtStr, T*> m_Items;

public:
    /**
        \brief Constructor

        \return A CBTLibrary
    */
    CBTLibrary() {}

    /**
        \brief Destructor
    */
    virtual ~CBTLibrary() { RemoveAllItems(); }

    /**
        \brief Checks if an item of a given name exists.

        \param _name The name of the item.

        \return Returns true if m_Item contains an item of name _name. Otherwise, returns false.
    */
    inline cbtBool HasItem(const cbtStr& _name) const { return m_Items.find(_name) != m_Items.end(); }

    /**
        \brief Get the item of given a name.

        \param _name The name of the item.

        \return The item of name _name.

        \remarks
            When using std::map or std::unordered_map with templated values, using something like this will result in an compile error:\n

            \code{.cpp}
            std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name); // Compile Error C7510

            error C7510: 'iterator': use of dependent type name must be prefixed with 'typename'
            \endcode

        \remarks
            In order to fix it, we need to use:\n
            \code{.cpp}
            typename std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name);
            \endcode
            or\n
            \code{.cpp}
            auto iter = m_Items.find(_name);
            \endcode

        \remarks
            In short, this is a quirk of C++ relating to templates and so-called "dependent names".
            Because T is a template parameter, and because template specialisation exists, C++ can't know for sure that std::map<std::string, T> has
            a member type iterator until a little later in the parsing process.
            As such, your declaration is ill-formed because the compiler can't quite see it as a declaration even if it squints.
            Adding typename says "This is going to be a type, I promise!" and then everything's fine (as long as it does turn out to be a type!).
            You may think that this should be C++'s problem, rather than yours, and you'd probably be right, but that's just the way it is.
            You can search for more information on this or just take it for granted that when the compiler tells you to write typename, you write typename.
            Alternatively, make your code nicer and solve the problem at the same time, by using auto instead.
    */
    const T* GetItem(const cbtStr& _name) const
    {
        typename std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name);
        return iter == m_Items.end() ? nullptr : iter->second;
    }

    /**
        \brief Get the item of given a name.

        \param _name The name of the item.

        \return The item of name _name.

        \remarks
            When using std::map or std::unordered_map with templated values, using something like this will result in an compile error:\n

            \code{.cpp}
            std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name); // Compile Error C7510

            error C7510: 'iterator': use of dependent type name must be prefixed with 'typename'
            \endcode

        \remarks
            In order to fix it, we need to use:\n
            \code{.cpp}
            typename std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name);
            \endcode
            or\n
            \code{.cpp}
            auto iter = m_Items.find(_name);
            \endcode

        \remarks
            In short, this is a quirk of C++ relating to templates and so-called "dependent names".
            Because T is a template parameter, and because template specialisation exists, C++ can't know for sure that std::map<std::string, T> has
            a member type iterator until a little later in the parsing process.
            As such, your declaration is ill-formed because the compiler can't quite see it as a declaration even if it squints.
            Adding typename says "This is going to be a type, I promise!" and then everything's fine (as long as it does turn out to be a type!).
            You may think that this should be C++'s problem, rather than yours, and you'd probably be right, but that's just the way it is.
            You can search for more information on this or just take it for granted that when the compiler tells you to write typename, you write typename.
            Alternatively, make your code nicer and solve the problem at the same time, by using auto instead.
    */
    T* GetItem(const cbtStr& _name)
    {
        auto iter = m_Items.find(_name);
        return iter == m_Items.end() ? nullptr : iter->second;
    }

    /**
        \brief Add an item.

        \param _name The name of the item.
        \param _item The item to add.
    */
    const void AddItem(T* _item) const
    {
        CBT_ASSERT(!HasItem(_item->GetName()));
        _item->Retain();
        m_Items.insert(std::pair<cbtStr, T*>(_item->GetName(), _item));
    }

    /**
        \brief Get the item of given a name.

        \param _name The name of the item.

        \return The item of name _name.

        \remarks
            When using std::map or std::unordered_map with templated values, using something like this will result in an compile error:\n

            \code{.cpp}
            std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name); // Compile Error C7510

            error C7510: 'iterator': use of dependent type name must be prefixed with 'typename'
            \endcode

        \remarks
            In order to fix it, we need to use:\n
            \code{.cpp}
            typename std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name);
            \endcode
            or\n
            \code{.cpp}
            auto iter = m_Items.find(_name);
            \endcode

        \remarks
            In short, this is a quirk of C++ relating to templates and so-called "dependent names".
            Because T is a template parameter, and because template specialisation exists, C++ can't know for sure that std::map<std::string, T> has
            a member type iterator until a little later in the parsing process.
            As such, your declaration is ill-formed because the compiler can't quite see it as a declaration even if it squints.
            Adding typename says "This is going to be a type, I promise!" and then everything's fine (as long as it does turn out to be a type!).
            You may think that this should be C++'s problem, rather than yours, and you'd probably be right, but that's just the way it is.
            You can search for more information on this or just take it for granted that when the compiler tells you to write typename, you write typename.
            Alternatively, make your code nicer and solve the problem at the same time, by using auto instead.
    */
    template <class U>
    U* GetItem(const cbtStr& _name)
    {
        auto iter = m_Items.find(_name);
        return iter == m_Items.end() ? nullptr : static_cast<U*>(iter->second);
    }

    /**
        \brief Remove the item of given a name.

        \param _name The name of the item.

        \remarks
            When using std::map or std::unordered_map with templated values, using something like this will result in an compile error:\n

            \code{.cpp}
            std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name); // Compile Error C7510

            error C7510: 'iterator': use of dependent type name must be prefixed with 'typename'
            \endcode

        \remarks
            In order to fix it, we need to use:\n
            \code{.cpp}
            typename std::unordered_map<cbtStr, T*>::iterator iter = m_Items.find(_name);
            \endcode
            or\n
            \code{.cpp}
            auto iter = m_Items.find(_name);
            \endcode

        \remarks
            In short, this is a quirk of C++ relating to templates and so-called "dependent names".
            Because T is a template parameter, and because template specialisation exists, C++ can't know for sure that std::map<std::string, T> has
            a member type iterator until a little later in the parsing process.
            As such, your declaration is ill-formed because the compiler can't quite see it as a declaration even if it squints.
            Adding typename says "This is going to be a type, I promise!" and then everything's fine (as long as it does turn out to be a type!).
            You may think that this should be C++'s problem, rather than yours, and you'd probably be right, but that's just the way it is.
            You can search for more information on this or just take it for granted that when the compiler tells you to write typename, you write typename.
            Alternatively, make your code nicer and solve the problem at the same time, by using auto instead.
    */
    void RemoveItem(const cbtStr& _name)
    {
        CBT_ASSERT(HasItem(_name));

        auto iter = m_Items.find(_name);
        iter->second->AutoRelease();
        m_Items.erase(iter);
    }

    /**
        \brief Remove all items in the CBTLibrary.
    */
    void RemoveAllItems()
    {
        std::unordered_map<cbtStr, T*> clearPool;
        clearPool.swap(m_Items);
        
        while (!clearPool.empty())
        {
            auto iter = clearPool.begin();
            iter->second->AutoRelease();
            clearPool.erase(iter);
        }
    }
};