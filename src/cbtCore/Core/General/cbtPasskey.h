#pragma once

#include "cbtMacros.h"

NS_CBT_BEGIN

/**
    \brief
        A cbtPasskey can only be create by an object of type T.
        A cbtPasskey is used to ensure that a function can only be called by an object of type T.\n
        Example:\n
        \code{.cpp}
        class Foo; // Forward Declaration
        class Base
        {
            virtual void BoomShakalaka(Foo* _foo)
            {
                _foo->DoSomething(cbtPasskey<Base>()); // Alternatively, can be written as _foo->DoSomething({});
            }
        }
        class DerivedA : public Base
        {
            virtual void BoomShakalaka(Foo* _foo) CBT_OVERRIDE
            {
                _foo->DoSomething(cbtPasskey<Base>()); // Does not compile. DerivedA cannot create a cbtPasskey<Base> even though DerivedA is a child class of Base.
            }
        }
        class DerivedB : public Base
        {
            virtual void BoomShakalaka(Foo* _foo) CBT_OVERRIDE
            {
                _foo->DoNothing(cbtPasskey<DerivedB>()); // Okay
            }
        }
        struct Foo
        {
            DoSomething(cbtPasskey<Base> _passkey) {}
            DoNothing(cbtPasskey<DerivedB> _passkey) {}
        }
        \endcode
 */
    template<typename T>
    class cbtPasskey
    {
        friend T;

    private:
        /**
            \brief Constructor. Can only be created by class T.

            \return A cbtPasskey.
        */
        cbtPasskey()
        {
        }

    public:
        /**
            \brief Destructor
        */
        ~cbtPasskey()
        {
        }
    };

/**
    \brief Same as cbtPasskey, but allows 2 classes to create cbtPasskey2.
*/
    template<typename T, typename U>
    class cbtPasskey2
    {
        friend T;
        friend U;

    private:
        /**
            \brief Constructor. Can only be created by class T and class U.

            \return A cbtPasskey2.
        */
        cbtPasskey2()
        {
        }

    public:
        /**
            \brief Destructor
        */
        ~cbtPasskey2()
        {
        }
    };

/**
    \brief Same as cbtPasskey, but allows 3 classes to create cbtPasskey3.
*/
    template<typename T, typename U, typename V>
    class cbtPasskey3
    {
        friend T;
        friend U;
        friend V;

    private:
        /**
            \brief Constructor. Can only be created by class T and class U and class V.

            \return A cbtPasskey3.
        */
        cbtPasskey3()
        {
        }

    public:
        /**
            \brief Destructor
        */
        ~cbtPasskey3()
        {
        }
    };

NS_CBT_END