#pragma once

// Include CBT
#include "CBTMacros.h"

// Include STD
#include <type_traits>
#include <exception>

NS_CBT_BEGIN

/// Represents an Invalid TypeID.
#define CBT_INVALID_TYPE_ID -1

/** 
    \brief
        Assigns an TypeID ID to a type during runtime. Can only generate an ID for classes of type BaseClass and classes inheriting BaseClass.
        Example: CBTFamily<Component> can only generate IDs for Component and classes inheriting Component, such as Camera, Transform, Light etc.
*/
template <typename BaseClass>
class CBTFamily
{
private:
    /// This value is increased each time GetID is called with a new typename DerivedClass. This ensures that each class is assigned a different ID.
    static cbtS32 s_CurrentID;

    /**
        \brief Private Constructor. All functions should be static. No objects of this class should be created.
    */
    CBTFamily() {}
    /**
        \brief Private Destructor. All functions should be static. No objects of this class should be created.
    */
    virtual ~CBTFamily() {}

public:
    /**
        \brief Checks if an ID is valid.

        \param _id The id to check.

        \return Returns true if the ID is valid. Returns false otherwise.
    */
    static cbtBool IsValidID(cbtS32 _id)
    {
        return (_id > CBT_INVALID_TYPE_ID && _id < s_CurrentID);
    }

    /**
        \brief Get the ID of DerivedClass. If DerivedClass does not have an ID yet, a new ID is generated.

        \warning DerivedClass must be a child class of BaseClass.

        \return Returns the ID of DerivedClass.
    */
    template <typename DerivedClass>
    static CBT_ENABLE_IF_DERIVED_1(cbtS32, BaseClass, DerivedClass) GetID()
    {
        // The first time this function of type U is called, result is initialised, increasing m_CurrentID. The subsequent times, result is not initialised again.
        static cbtS32 result = s_CurrentID++;
        return result;
    }
};

template <typename BaseClass>
cbtS32 CBTFamily<BaseClass>::s_CurrentID = 0;

NS_CBT_END