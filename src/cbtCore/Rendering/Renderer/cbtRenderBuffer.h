#pragma once

// Include CBT
#include "Rendering/Buffer/cbtFrameBuffer.h"
#include "Rendering/Texture/cbtTexture.h"

NS_CBT_BEGIN

// Geometry Buffer has a DepthStencil Attachment.
    enum class cbtGBuffer : cbtU32 ///< Geometry Buffer
    {
        POSITION_CAMERA_SPACE,
        NORMAL_CAMERA_SPACE,
        AMBIENT_COLOR,
        ALBEDO_COLOR,
        SPECULAR_COLOR,
        GLOSS,

        NUM_COLOR_ATTACHMENTS,
    };

    enum class cbtLBuffer : cbtU32 ///< LightBuffer
    {
        COMPOSITE, // The scene rendered with geometry and lights.
        LIGHT_DIFFUSE, // Light Diffuse Color (To be used as an input by the next pass in order to support unlimited lights.)
        LIGHT_SPECULAR, // Light Specular Color (To be used as an input by the next pass in order to support unlimited lights.)

        NUM_COLOR_ATTACHMENTS,
    };

// Forward Buffer has a DepthStencil Attachment.
    enum class cbtFBuffer : cbtU32 ///< Forward Buffer
    {
        COMPOSITE,
        POSITION_CAMERA_SPACE,
        NORMAL_CAMERA_SPACE,

        NUM_COLOR_ATTACHMENTS,
    };

    enum class cbtPBuffer : cbtU32 ///< Post Process Buffer
    {
        COMPOSITE, // The scene rendered with geometry and lights with post-processing.

        NUM_COLOR_ATTACHMENTS,
    };

    cbtFrameBuffer* CreateGBuffer(cbtS32 _width, cbtS32 _height);

    cbtFrameBuffer* CreateLBuffer(cbtS32 _width, cbtS32 _height);

    cbtFrameBuffer* CreateFBuffer(cbtS32 _width, cbtS32 _height);

    cbtFrameBuffer* CreatePBuffer(cbtS32 _width, cbtS32 _height);

NS_CBT_END