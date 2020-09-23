// Include CBT
#include "CBTPixelFormat.h"

NS_CBT_BEGIN

cbtU32 GetChannelCount(CBTPixelFormat _format)
{
    switch (_format)
    {
    case CBT_R8:             return 1;
    case CBT_R8_SNORM:       return 1;
    case CBT_R16:            return 1;
    case CBT_R16_SNORM:      return 1;
    case CBT_RG8:            return 2;
    case CBT_RG8_SNORM:      return 2;
    case CBT_RG16:           return 2;
    case CBT_RG16_SNORM:     return 2;
    case CBT_R3_G3_B2:       return 3;
    case CBT_RGB4:           return 3;
    case CBT_RGB5:           return 3;
    case CBT_RGB8:           return 3;
    case CBT_RGB8_SNORM:     return 3;
    case CBT_RGB10:          return 3;
    case CBT_RGB12:          return 3;
    case CBT_RGB16_SNORM:    return 3;
    case CBT_RGBA2:          return 3;
    case CBT_RGBA4:          return 3;
    case CBT_RGB5_A1:        return 4;
    case CBT_RGBA8:          return 4;
    case CBT_RGBA8_SNORM:    return 4;
    case CBT_RGB10_A2:       return 4;
    case CBT_RGB10_A2UI:     return 4;
    case CBT_RGBA12:         return 4;
    case CBT_RGBA16:         return 4;
    case CBT_SRGB8:          return 3;
    case CBT_SRGB8_ALPHA8:   return 4;
    case CBT_R16F:           return 1;
    case CBT_RG16F:          return 2;
    case CBT_RGB16F:         return 3;
    case CBT_RGBA16F:        return 4;
    case CBT_R32F:           return 1;
    case CBT_RG32F:          return 2;
    case CBT_RGB32F:         return 3;
    case CBT_RGBA32F:        return 4;
    case CBT_R11F_G11F_B10F: return 3;
    case CBT_RGB9_E5:        return 3;
    case CBT_R8I:            return 1;
    case CBT_R8UI:           return 1;
    case CBT_R16I:           return 1;
    case CBT_R16UI:          return 1;
    case CBT_R32I:           return 1;
    case CBT_R32UI:          return 1;
    case CBT_RG8I:           return 2;
    case CBT_RG8UI:          return 2;
    case CBT_RG16I:          return 2;
    case CBT_RG16UI:         return 2;
    case CBT_RG32I:          return 2;
    case CBT_RG32UI:         return 2;
    case CBT_RGB8I:          return 3;
    case CBT_RGB8UI:         return 3;
    case CBT_RGB16I:         return 3;
    case CBT_RGB16UI:        return 3;
    case CBT_RGB32I:         return 3;
    case CBT_RGB32UI:        return 3;
    case CBT_RGBA8I:         return 4;
    case CBT_RGBA8UI:        return 4;
    case CBT_RGBA16I:        return 4;
    case CBT_RGBA16UI:       return 4;
    case CBT_RGBA32I:        return 4;
    case CBT_RGBA32UI:       return 4;
    default:                 return 0;
    }
}

NS_CBT_END