// Include CBT
#include "Rendering/Texture/cbtTextureBuilder.h"

#ifdef CBT_SDL

// Include STL
#include "SDL2/SDL_image.h"

NS_CBT_BEGIN

// Image Loading
cbtTexture* cbtTextureBuilder::Create2DTexture(const cbtStr& _name, const cbtStr& _filePath, cbtBool _flipVertical, cbtBool _flipHorizontal)
{
    SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface* rawSurface = IMG_Load(_filePath.c_str());
    SDL_Surface* convertedSurface = SDL_ConvertSurface(rawSurface, pixelFormat, 0);
    CBT_ASSERT(convertedSurface);

    cbtS32 width = convertedSurface->w;
    cbtS32 height = convertedSurface->h;
    cbtU8* pixelData = static_cast<cbtU8*>(convertedSurface->pixels);
    if (_flipHorizontal) { FlipImageHorizontally(pixelData, width, height, pixelFormat->BytesPerPixel); }
    if (_flipVertical) { FlipImageVertically(pixelData, width, height, pixelFormat->BytesPerPixel); }

    cbtTexture* texture = cbtTexture::Create2DTexture(_name, width, height, CBT_RGBA8, pixelData);

    SDL_FreeFormat(pixelFormat);
    SDL_FreeSurface(rawSurface);
    SDL_FreeSurface(convertedSurface);

    return texture;
}

cbtTexture* cbtTextureBuilder::CreateCubeMap(const cbtStr& _name, std::array<cbtStr, CBT_CUBEMAP_MAX_SIDES> _filePath, cbtBool _flipVertical, cbtBool _flipHorizontal)
{
    SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface* rawSurface[CBT_CUBEMAP_MAX_SIDES];
    SDL_Surface* convertedSurface[CBT_CUBEMAP_MAX_SIDES];

    for (cbtU32 i = 0; i < CBT_CUBEMAP_MAX_SIDES; ++i)
    {
        rawSurface[i] = IMG_Load(_filePath[i].c_str());
        convertedSurface[i] = SDL_ConvertSurface(rawSurface[i], pixelFormat, 0);
        CBT_ASSERT(convertedSurface[i]);

        cbtS32 width = convertedSurface[i]->w;
        cbtS32 height = convertedSurface[i]->h;
        cbtU8* pixelData = static_cast<cbtU8*>(convertedSurface[i]->pixels);
        if (_flipHorizontal) { FlipImageHorizontally(pixelData, width, height, pixelFormat->BytesPerPixel); }
        if (_flipVertical) { FlipImageVertically(pixelData, width, height, pixelFormat->BytesPerPixel); }
    }

    cbtTexture* texture = cbtTexture::CreateCubeMap(_name, convertedSurface[0]->w, convertedSurface[0]->h, CBT_RGBA8, {
        static_cast<cbtU8*>(convertedSurface[0]->pixels),
        static_cast<cbtU8*>(convertedSurface[1]->pixels),
        static_cast<cbtU8*>(convertedSurface[2]->pixels),
        static_cast<cbtU8*>(convertedSurface[3]->pixels),
        static_cast<cbtU8*>(convertedSurface[4]->pixels),
        static_cast<cbtU8*>(convertedSurface[5]->pixels)
        });

    SDL_FreeFormat(pixelFormat);
    for (cbtU32 i = 0; i < CBT_CUBEMAP_MAX_SIDES; ++i)
    {
        SDL_FreeSurface(rawSurface[i]);
        SDL_FreeSurface(convertedSurface[i]);
    }

    return texture;
}

NS_CBT_END

#endif // CBT_SDL