#pragma once

// Include CBT
#include "CBTMacros.h"

// Include STD
#include <cassert>

NS_CBT_BEGIN

/// Assert
#define CBT_ASSERT(__CONDITION__) assert(__CONDITION__)

/// Log Category
enum CBTLogCategory : cbtU32
{
    CBT_LOG_CATEGORY_APPLICATION,
    CBT_LOG_CATEGORY_AUDIO,
    CBT_LOG_CATEGORY_RENDER,
    CBT_LOG_CATEGORY_INPUT,
    CBT_LOG_CATEGORY_PHYSICS,
    CBT_LOG_CATEGORY_TEST,
};

/// Log Priority
enum CBTLogPriority : cbtU32
{
    CBT_LOG_PRIORITY_VERBOSE,
    CBT_LOG_PRIORITY_DEBUG,
    CBT_LOG_PRIORITY_INFO,
    CBT_LOG_PRIORITY_WARN,
    CBT_LOG_PRIORITY_ERROR,
    CBT_LOG_PRIORITY_CRITICAL,
};

/**
    \brief A debug utility class.
*/
class CBTDebug
{
private:
    /**
        \brief Private Constructor. All functions should be static. No objects of this class should be created.
    */
    CBTDebug() {}
    /**
        \brief Private Destructor. All functions should be static. No objects of this class should be created.
    */
    ~CBTDebug() {}

    /**
        \brief Get the string description of a CBTLogCategory.

        \param _category The CBTLogCategory.

        \return The string description of the CBTLogCategory.
    */
    static cbtStr ToString(CBTLogCategory _category)
    {
        switch (_category)
        {
        case CBT_LOG_CATEGORY_APPLICATION: return "APPLICATION";
        case CBT_LOG_CATEGORY_AUDIO: return "AUDIO";
        case CBT_LOG_CATEGORY_RENDER: return "RENDER";
        case CBT_LOG_CATEGORY_INPUT: return "INPUT";
        case CBT_LOG_CATEGORY_PHYSICS: return "PHYSICS";
        case CBT_LOG_CATEGORY_TEST: return "TEST";
        default: return "UNKNOWN CATEGORY";
        }
    }

    /**
        \brief Get the string description of a CBTLogPriority.

        \param _priority The CBTLogPriority.

        \return The string description of the CBTLogPriority.
    */
    static cbtStr ToString(CBTLogPriority _priority)
    {
        switch (_priority)
        {
        case CBT_LOG_PRIORITY_VERBOSE: return "VERBOSE";
        case CBT_LOG_PRIORITY_DEBUG: return "DEBUG";
        case CBT_LOG_PRIORITY_INFO: return "INFO";
        case CBT_LOG_PRIORITY_WARN: return "WARN";
        case CBT_LOG_PRIORITY_ERROR: return "ERROR";
        case CBT_LOG_PRIORITY_CRITICAL: return "CRITICAL";
        default: return "UNKNOWN PRIORITY";
        }
    }

public:
    /**
        \brief Print a message to the console.

        \param _category The message category.
        \param _priority The message priority.
        \param _format The message string in printf() format.
        \param ... Additional arguments.
    */
    static void Log(CBTLogCategory _category, CBTLogPriority _priority, const cbtS8* _format, ...);
};

/// Print a message to the console with priority CBT_LOG_PRIORITY_VERBOSE and a given category.
#define CBT_LOG_VERBOSE(__LOG_CATEGORY__, __FORMAT__, ...) ::NS_CBT::CBTDebug::Log(__LOG_CATEGORY__, CBT_LOG_PRIORITY_VERBOSE, __FORMAT__, __VA_ARGS__)
/// Print a message to the console with priority CBT_LOG_PRIORITY_DEBUG and a given category.
#define CBT_LOG_DEBUG(__LOG_CATEGORY__, __FORMAT__, ...) ::NS_CBT::CBTDebug::Log(__LOG_CATEGORY__, CBT_LOG_PRIORITY_DEBUG, __FORMAT__, __VA_ARGS__)
/// Print a message to the console with priority CBT_LOG_PRIORITY_INFO and a given category.
#define CBT_LOG_INFO(__LOG_CATEGORY__, __FORMAT__, ...) ::NS_CBT::CBTDebug::Log(__LOG_CATEGORY__, CBT_LOG_PRIORITY_INFO, __FORMAT__, __VA_ARGS__)
/// Print a message to the console with priority CBT_LOG_PRIORITY_WARN and a given category.
#define CBT_LOG_WARN(__LOG_CATEGORY__, __FORMAT__, ...) ::NS_CBT::CBTDebug::Log(__LOG_CATEGORY__, CBT_LOG_PRIORITY_WARN, __FORMAT__, __VA_ARGS__)
/// Print a message to the console with priority CBT_LOG_PRIORITY_ERROR and a given category.
#define CBT_LOG_ERROR(__LOG_CATEGORY__, __FORMAT__, ...) ::NS_CBT::CBTDebug::Log(__LOG_CATEGORY__, CBT_LOG_PRIORITY_ERROR, __FORMAT__, __VA_ARGS__)
/// Print a message to the console with priority CBT_LOG_PRIORITY_CRITICAL and a given category.
#define CBT_LOG_CRITICAL(__LOG_CATEGORY__, __FORMAT__, ...) ::NS_CBT::CBTDebug::Log(__LOG_CATEGORY__, CBT_LOG_PRIORITY_CRITICAL, __FORMAT__, __VA_ARGS__)

NS_CBT_END