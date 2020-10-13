// Include CBT
#include "Core/FileUtil/cbtFileUtil.h"
#include "Debug/cbtDebug.h"

#ifdef CBT_SDL

#include <SDL2/SDL.h>

NS_CBT_BEGIN

cbtStr cbtFileUtil::FileToString(const cbtStr& _filePath)
{
    SDL_RWops* file = SDL_RWFromFile(_filePath.c_str(), "r");
    CBT_ASSERT(file);

    cbtS64 fileSize = SDL_RWsize(file);
    cbtS8* stringBuffer = new cbtS8[fileSize + 1]; // Add 1 byte for null terminator.
    stringBuffer[fileSize] = 0; // Add null terminator.
    SDL_RWread(file, stringBuffer, fileSize, 1);
    cbtStr fileString(stringBuffer);

    SDL_RWclose(file);
    delete[] stringBuffer;

    return fileString;
}

void cbtFileUtil::StringToFile(const cbtStr& _filePath, const cbtStr& _string)
{
    SDL_RWops* file = SDL_RWFromFile(_filePath.c_str(), "w");
    CBT_ASSERT(file);

    size_t writeLength = SDL_RWwrite(file, _string.c_str(), 1, SDL_strlen(_string.c_str()));
    CBT_ASSERT(writeLength == SDL_strlen(_string.c_str()));

    SDL_RWclose(file);
}

NS_CBT_END

#endif // CBT_SDL