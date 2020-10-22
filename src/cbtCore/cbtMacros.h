#pragma once

/**
    \file cbtMacros.h
    \brief A file containing generic macros used throughout CBTEngine.
*/

// How to Create and Use a Static Library [https://msdn.microsoft.com/en-us/library/ms235627.aspx#BKMK_CreateLibProject]

// Include STD
#include <string>
#include <functional>
#include <type_traits>

// Type Definition(s)
typedef unsigned char cbtByte;

typedef char cbtS8;
typedef short cbtS16;
typedef int cbtS32;
typedef long long int cbtS64;

typedef unsigned char cbtU8;
typedef unsigned short cbtU16;
typedef unsigned int cbtU32;
typedef unsigned long long int cbtU64;

typedef float cbtF32;
typedef double cbtF64;

typedef bool cbtBool;
typedef std::string cbtStr;

/// \brief Equivalent to writing CBTEngine.
#define NS_CBT CBTEngine
/// \brief Equivalent to writing namespace NS_CBT {
#define NS_CBT_BEGIN namespace NS_CBT {
/// \brief Equivalent to writing }
#define NS_CBT_END }
/// \brief Equivalent to writing using namespace NS_CBT
#define USING_NS_CBT using namespace NS_CBT

/// \brief Equivalent to writing {
#define CBT_REGION(__REGION_NAME__) {
/// \brief Equivalent to writing }
#define CBT_END_REGION(__REGION_NAME__) }

/// \brief Keyword used when instantiating new objects. For now it is the same as typing the new keyword. But it is there just incase it changes in the future.
#define cbtNew new

/**
    \brief Converts a non cbtStr to a cbtStr.

    Example:\n
    \code{.cpp}
    cbtStr myString = CBT_TO_STRING(5); // cbtStr is equal to "5".
    \endcode
*/
#define CBT_TO_STRING std::to_string

/**
    \brief Optional keyword used when overriding virtual function(s).

    Example:\n
    \code{.cpp}
    struct BaseClass
    {
        cbtU32 m_MemberVariable = 0;
        virtual void DoSomething() { m_MemberVariable += 3; }
    };

    struct DerivedClass : public BaseClass
    {
        virtual void DoSomething() CBT_OVERRIDE { m_MemberVariable += 8; }
    };
    \endcode
*/
#define CBT_OVERRIDE override

/// \brief Allows a non-static member function with no parameters to be passed as a parameter.
#define CBT_CALLBACK_0(__SELECTOR__, __TARGET__, ...)   ::std::bind(&__SELECTOR__, __TARGET__, ##__VA_ARGS__)
/// \brief Allows a non-static member function with 1 parameter to be passed as a parameter.
#define CBT_CALLBACK_1(__SELECTOR__, __TARGET__, ...)   ::std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, ##__VA_ARGS__)
/// \brief Allows a non-static member function with 2 parameters to be passed as a parameter.
#define CBT_CALLBACK_2(__SELECTOR__, __TARGET__, ...)   ::std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
/// \brief Allows a non-static member function with 3 parameters to be passed as a parameter.
#define CBT_CALLBACK_3(__SELECTOR__, __TARGET__, ...)   ::std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
/// \brief Allows a non-static member function with 4 parameters to be passed as a parameter.
#define CBT_CALLBACK_4(__SELECTOR__, __TARGET__, ...)   ::std::bind(&__SELECTOR__, __TARGET__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

/// \brief Resolves to true if typename __BASE__ is a base class of typename __DERIVED__. Otherwise, resolves to false.
#define CBT_IS_BASE_OF(__BASE__, __DERIVED__) ::std::is_base_of<__BASE__, __DERIVED__>::value

/**
    \brief Typename __OUT__ is only defined if typename __DERIVED_0__ is derived from typename __BASE__. Otherwise, typename __OUT__ is undefined.
    
    Example:\n
    \code{.cpp}
    template<class Derived>
    ENABLE_IF_DERIVED_1(void, Base, Derived) Foo(Derived* _param)
    {
        // This function does not compile if Derived is not a derived class of Base.
        _param->DoSomething();
    }
    \endcode
*/
#define CBT_ENABLE_IF_DERIVED_1(__OUT__, __BASE__, __DERIVED__) \
    typename ::std::enable_if<CBT_IS_BASE_OF(__BASE__, __DERIVED__), __OUT__>::type

/**
    \brief Typename __OUT__ is only defined if typename __DERIVED_0__ and typename __DERIVED_1__ is derived from typename __BASE__. Otherwise, typename __OUT__ is undefined.

    Example:\n
    \code{.cpp}
    template<class Derived0, class Derived1>
    ENABLE_IF_DERIVED_2(void, Base, Derived0, Derived1) Foo(Derived0* _param0, Derived1* _param1)
    {
        // This function does not compile if Derived0 and Derived1 is not a derived class of Base.
        _param0->DoSomething();
        _param1->DoSomething();
    }
    \endcode
*/
#define CBT_ENABLE_IF_DERIVED_2(__OUT__, __BASE__, __DERIVED_0__, __DERIVED_1__) \
    typename ::std::enable_if<CBT_IS_BASE_OF(__BASE__, __DERIVED_0__) && CBT_IS_BASE_OF(__BASE__, __DERIVED_1__), __OUT__>::type

/**
    \brief Typename __OUT__ is only defined if typename __DERIVED_0__ and typename __DERIVED_1__ and typename __DERIVED_2__ is derived from typename __BASE__. Otherwise, typename __OUT__ is undefined.

    Example:\n
    \code{.cpp}
    template<class Derived0, class Derived1, class Derived2>
    ENABLE_IF_DERIVED_3(void, Base, Derived0, Derived1) Foo(Derived0* _param0, Derived1* _param1, Derived2* _param2)
    {
        // This function does not compile if Derived0 and Derived1 is not a derived class of Base.
        _param0->DoSomething();
        _param1->DoSomething();
        _param2->DoSomething();
    }
    \endcode
*/
#define CBT_ENABLE_IF_DERIVED_3(__OUT__, __BASE__, __DERIVED_0__, __DERIVED_1__, __DERIVED_2__) \
    typename ::std::enable_if<CBT_IS_BASE_OF(__BASE__, __DERIVED_0__) && CBT_IS_BASE_OF(__BASE__, __DERIVED_1__) && CBT_IS_BASE_OF(__BASE__, __DERIVED_2__), __OUT__>::type

// #define CBT_ENABLE_IF_DERIVED_2(__BASE__, __DERIVED__, __OUT__) typename std::enable_if<std::is_base_of<__BASE__, __DERIVED__>::value, __OUT__>::type

/**
    \brief Typename __OUT__ is only defined if typename __IN__ is a floating point type. Otherwise, __OUT__ is undefined.

    Example:\n
    \code{.cpp}
    template<class T>
    ENABLE_IF_FLOAT(T, cbtBool) Foo(T _param)
    {
        return (_param / 0.5f); // If T is not a floating point, it cannot be divided by 0.5f without type casting. So let's not allow this function to be compiled when T is an integral type.
    }
    \endcode
*/
#define CBT_ENABLE_IF_FLOAT(__IN__, __OUT__) typename ::std::enable_if<std::is_floating_point<__IN__>::value, __OUT__>::type

/**
    \brief Typename __OUT__ is only defined if typename __IN__ is a integral type. Otherwise, __OUT__ is undefined.

    Example:\n
    \code{.cpp}
    template<class T>
    ENABLE_IF_INT(T, cbtBool) IsOdd(T _param)
    {
       return (_param & 1) == 1; // This function does not compile if T is not an integral type.
    }
    \endcode
*/
#define CBT_ENABLE_IF_INT(__IN__, __OUT__) typename ::std::enable_if<std::is_integral<__IN__>::value, __OUT__>::type

/**
    \brief Typename __OUT__ is only defined if typename __IN__ is an unsigned integral type. Otherwise, __OUT__ is undefined.

    Example:\n
    \code{.cpp}
    template<class T>
    ENABLE_IF_UINT(T, cbtBool) IsOdd(T _param)
    {
       return (_param & 1) == 1; // This function will not compile since cbtBool is not an unsigned integral.
    }
    \endcode
*/
#define CBT_ENABLE_IF_UINT(__IN__, __OUT__) typename ::std::enable_if<(std::is_integral<__IN__>::value && !std::is_signed<__IN__>::value), __OUT__>::type

/**
    \brief Represents the number of bits in typename __TYPE__.

    Example:\n
    \code{.cpp}
    cbtU32 sizeInBitsA = CBT_BITSIZE(cbtS32); // sizeinBitsA is initialised to 32.
    cbtU32 sizeInBitsB = CBT_BITSIZE(cbtU8); // sizeInBitsB is initialised to 8.
    \endcode
*/
#define CBT_BITSIZE(__TYPE__) (sizeof(__TYPE__) * 8)

/**
    \brief Swaps the value of _a and _b.

    \param _a The first value to be swapped.
    \param _b The second value to be swapped.
*/
template<typename T>
void CBTShallowSwap(T& _a, T& _b)
{
    T temp = _a;
    _a = _b;
    _b = temp;
}

/**
    \brief A template class to get a specific typename in a list of types as specified by INDEX.

    Example:\n
    \code{.cpp}
    TemplateType<2, cbtECS, cbtU32, cbtS8>::Type m_S8 = 'r'; // m_S8 is of type cbtS8.
    \endcode
*/
template<cbtU32 INDEX, typename T, typename... Args>
struct TemplateType
{
    using Type = typename TemplateType<INDEX - 1, Args...>::Type;
};

/**
    \brief A template class to get a specific typename in a list of types as specified by INDEX.

    Example:\n
    \code{.cpp}
    TemplateType<2, cbtECS, cbtU32, cbtS8>::Type m_S8 = 'r'; // m_S8 is of type cbtS8.
    \endcode
*/
template<typename T, typename... Args>
struct TemplateType<0, T, Args...>
{
    using Type = T;
};

/**
    \brief Returns the number of template types.
*/
template<typename ...Args>
constexpr cbtU32 CBT_TEMPLATE_COUNT = sizeof...(Args);

/*
    \brief
        In a list of template types, get the index of CHECK.
        For example, GetTemplateIndex<cbtU32, cbtStr, cbtS32, cbtU32, cbtBool>() will return 2, because first type cbtU32, appears at index 2 in the list cbtStr, cbtS32, cbtU32, cbtBool.
*/
template<typename CHECK>
cbtU32 CBTTemplateIndex()
{
    return 0;
}

/*
    \brief
        In a list of template types, get the index of CHECK.
        For example, GetTemplateIndex<cbtU32, cbtStr, cbtS32, cbtU32, cbtBool>() will return 2, because first type cbtU32, appears at index 2 in the list cbtStr, cbtS32, cbtU32, cbtBool.
*/
template<typename CHECK, typename T, typename ...Args>
cbtU32 CBTTemplateIndex()
{
    return std::is_same<CHECK, T>::value ? 0 : (1 + CBTTemplateIndex<CHECK, Args...>());
}

// External APIs
#define CBT_OPENGL
// #define CBT_VULKAN
#define CBT_SDL
#define CBT_IRRKLANG