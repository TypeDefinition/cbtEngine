#pragma once

#include "CBTMacros.h"

NS_CBT_BEGIN

/**
    \brief
        A CBTPasskey can only be create by an object of type T.
        A CBTPasskey is used to ensure that a function can only be called by an object of type T.\n
        Example:\n
        \code{.cpp}
        class Foo; // Forward Declaration
        class Base
        {
            virtual void BoomShakalaka(Foo* _foo)
            {
                _foo->DoSomething(CBTPasskey<Base>()); // Alternatively, can be written as _foo->DoSomething({});
            }
        }
        class DerivedA : public Base
        {
            virtual void BoomShakalaka(Foo* _foo) CBT_OVERRIDE
            {
                _foo->DoSomething(CBTPasskey<Base>()); // Does not compile. DerivedA cannot create a CBTPasskey<Base> even though DerivedA is a child class of Base.
            }
        }
        class DerivedB : public Base
        {
            virtual void BoomShakalaka(Foo* _foo) CBT_OVERRIDE
            {
                _foo->DoNothing(CBTPasskey<DerivedB>()); // Okay
            }
        }
        struct Foo
        {
            DoSomething(CBTPasskey<Base> _passkey) {}
            DoNothing(CBTPasskey<DerivedB> _passkey) {}
        }
        \endcode
 */
template <typename T>
class CBTPasskey
{
    friend T;

private:
    /**
        \brief Constructor. Can only be created by class T.

        \return A CBTPasskey.
    */
    CBTPasskey() {}

public:
    /**
        \brief Destructor
    */
    ~CBTPasskey() {}
};

/**
    \brief Same as CBTPasskey, but allows 2 classes to create CBTPasskey2.
*/
template <typename T, typename U>
class CBTPasskey2
{
    friend T;
    friend U;

private:
    /**
        \brief Constructor. Can only be created by class T and class U.

        \return A CBTPasskey2.
    */
    CBTPasskey2() {}

public:
    /**
        \brief Destructor
    */
    ~CBTPasskey2() {}
};

/**
    \brief Same as CBTPasskey, but allows 3 classes to create CBTPasskey3.
*/
template <typename T, typename U, typename V>
class CBTPasskey3
{
    friend T;
    friend U;
    friend V;

private:
    /**
        \brief Constructor. Can only be created by class T and class U and class V.

        \return A CBTPasskey3.
    */
    CBTPasskey3() {}

public:
    /**
        \brief Destructor
    */
    ~CBTPasskey3() {}
};

NS_CBT_END