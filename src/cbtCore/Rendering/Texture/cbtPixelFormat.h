#pragma once

// Include CBT
#include "cbtMacros.h"

NS_CBT_BEGIN

    enum cbtPixelFormat : cbtU32
    {
        // Invalid
        CBT_INVALID_PIXEL_FORMAT,

        // Color
        CBT_R8,
        CBT_R8_SNORM,
        CBT_R16,
        CBT_R16_SNORM,
        CBT_RG8,
        CBT_RG8_SNORM,
        CBT_RG16,
        CBT_RG16_SNORM,
        CBT_R3_G3_B2,
        CBT_RGB4,
        CBT_RGB5,
        CBT_RGB8,
        CBT_RGB8_SNORM,
        CBT_RGB10,
        CBT_RGB12,
        CBT_RGB16_SNORM,
        CBT_RGBA2,
        CBT_RGBA4,
        CBT_RGB5_A1,
        CBT_RGBA8,
        CBT_RGBA8_SNORM,
        CBT_RGB10_A2,
        CBT_RGB10_A2UI,
        CBT_RGBA12,
        CBT_RGBA16,
        CBT_SRGB8,
        CBT_SRGB8_ALPHA8,
        CBT_R16F,
        CBT_RG16F,
        CBT_RGB16F,
        CBT_RGBA16F,
        CBT_R32F,
        CBT_RG32F,
        CBT_RGB32F,
        CBT_RGBA32F,
        CBT_R11F_G11F_B10F,
        CBT_RGB9_E5,
        CBT_R8I,
        CBT_R8UI,
        CBT_R16I,
        CBT_R16UI,
        CBT_R32I,
        CBT_R32UI,
        CBT_RG8I,
        CBT_RG8UI,
        CBT_RG16I,
        CBT_RG16UI,
        CBT_RG32I,
        CBT_RG32UI,
        CBT_RGB8I,
        CBT_RGB8UI,
        CBT_RGB16I,
        CBT_RGB16UI,
        CBT_RGB32I,
        CBT_RGB32UI,
        CBT_RGBA8I,
        CBT_RGBA8UI,
        CBT_RGBA16I,
        CBT_RGBA16UI,
        CBT_RGBA32I,
        CBT_RGBA32UI,

        // Depth
        CBT_DEPTH_COMPONENT32F,
        CBT_DEPTH_COMPONENT24,
        CBT_DEPTH_COMPONENT16,

        // Depth-Stencil
        CBT_DEPTH32F_STENCIL8,
        CBT_DEPTH24_STENCIL8,

        // Stencil
        CBT_STENCIL_INDEX8,
    };

    cbtU32 GetChannelCount(cbtPixelFormat _format);

NS_CBT_END