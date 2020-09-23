#pragma once

// Include CBT
#include "Rendering/Buffer/CBTFrameBuffer.h"
#include "Rendering/Texture/CBTTexture.h"

NS_CBT_BEGIN

// Geometry Buffer has a DepthStencil Attachment.
enum class CBTGBuffer : cbtU32 ///< Geometry Buffer
{
    POSITION_CAMERA_SPACE,
    NORMAL_CAMERA_SPACE,
    AMBIENT_COLOR,
    ALBEDO_COLOR,
    SPECULAR_COLOR,
    GLOSS,

    NUM_COLOR_ATTACHMENTS,
};

enum class CBTLBuffer : cbtU32 ///< LightBuffer
{
    COMPOSITE, // The scene rendered with geometry and lights.
    LIGHT_DIFFUSE, // Light Diffuse Color (To be used as an input by the next pass in order to support unlimited lights.)
    LIGHT_SPECULAR, // Light Specular Color (To be used as an input by the next pass in order to support unlimited lights.)

    NUM_COLOR_ATTACHMENTS,
};

// Forward Buffer has a DepthStencil Attachment.
enum class CBTFBuffer : cbtU32 ///< Forward Buffer
{
    COMPOSITE,
    POSITION_CAMERA_SPACE,
    NORMAL_CAMERA_SPACE,

    NUM_COLOR_ATTACHMENTS,
};

enum class CBTPBuffer : cbtU32 ///< Post Process Buffer
{
    COMPOSITE, // The scene rendered with geometry and lights with post-processing.

    NUM_COLOR_ATTACHMENTS,
};

CBTFrameBuffer* CreateGBuffer(cbtS32 _width, cbtS32 _height);
CBTFrameBuffer* CreateLBuffer(cbtS32 _width, cbtS32 _height);
CBTFrameBuffer* CreateFBuffer(cbtS32 _width, cbtS32 _height);
CBTFrameBuffer* CreatePBuffer(cbtS32 _width, cbtS32 _height);

NS_CBT_END