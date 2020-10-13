// Include CBT
#include "Debug/cbtDebug.h"

// Include SDL
#include <SDL2/SDL.h>

NS_CBT_BEGIN

SDL_LogPriority ToSDLLogPriority(cbtLogPriority _priority)
{
    switch (_priority)
    {
    case CBT_LOG_PRIORITY_VERBOSE:
        return SDL_LOG_PRIORITY_VERBOSE;
    case CBT_LOG_PRIORITY_DEBUG:
        return SDL_LOG_PRIORITY_DEBUG;
    case CBT_LOG_PRIORITY_INFO:
        return SDL_LOG_PRIORITY_INFO;
    case CBT_LOG_PRIORITY_WARN:
        return SDL_LOG_PRIORITY_WARN;
    case CBT_LOG_PRIORITY_ERROR:
        return SDL_LOG_PRIORITY_ERROR;
    case CBT_LOG_PRIORITY_CRITICAL:
        return SDL_LOG_PRIORITY_CRITICAL;
    default:
        return SDL_LOG_PRIORITY_ERROR;
    }
}

void cbtDebug::Log(cbtLogCategory _category, cbtLogPriority _priority, const cbtS8* _format, ...)
{
    va_list args;
    va_start(args, _format);
    cbtStr format = "[" + cbtDebug::ToString(_category) + "] " + cbtStr(_format);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, ToSDLLogPriority(_priority), format.c_str(), args);
}

NS_CBT_END