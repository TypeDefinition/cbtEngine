#pragma once

// Include CBT
#include "cbtPixelFormat.h"
#include "Debug/cbtDebug.h"
#include "Core/General/cbtRef.h"

// Include STD
#include <array>

NS_CBT_BEGIN

// NOTE: This direction is assuming we are INSIDE the cube.
// These are in this specific order due to OpenGL's enum order for GL_TEXTURE_CUBE_MAP_POSITIVE_X.
#define CBT_TEXTURE_CUBE_MAP_POSITIVE_X 0
#define CBT_TEXTURE_CUBE_MAP_NEGATIVE_X 1
#define CBT_TEXTURE_CUBE_MAP_POSITIVE_Y 2
#define CBT_TEXTURE_CUBE_MAP_NEGATIVE_Y 3
#define CBT_TEXTURE_CUBE_MAP_POSITIVE_Z 4
#define CBT_TEXTURE_CUBE_MAP_NEGATIVE_Z 5

#define CBT_CUBEMAP_LEFT CBT_TEXTURE_CUBE_MAP_POSITIVE_X
#define CBT_CUBEMAP_RIGHT CBT_TEXTURE_CUBE_MAP_NEGATIVE_X
#define CBT_CUBEMAP_TOP CBT_TEXTURE_CUBE_MAP_POSITIVE_Y
#define CBT_CUBEMAP_BOTTOM CBT_TEXTURE_CUBE_MAP_NEGATIVE_Y
#define CBT_CUBEMAP_FRONT CBT_TEXTURE_CUBE_MAP_POSITIVE_Z
#define CBT_CUBEMAP_BACK CBT_TEXTURE_CUBE_MAP_NEGATIVE_Z

#define CBT_CUBEMAP_MAX_SIDES 6

    enum cbtTextureShape
    {
        CBT_TEXTURE_SHAPE_2D,
        CBT_TEXTURE_SHAPE_CUBE,
    };

    enum cbtTextureWrap
    {
        CBT_TEXTURE_WRAP_REPEAT,
        CBT_TEXTURE_WRAP_MIRRORED_REPEAT,
        CBT_TEXTURE_WRAP_CLAMP_TO_EDGE,
    };

// Texture format of texture should be standardised to RGBA.
    class cbtTexture : public cbtManaged
    {
    protected:
        // Variable(s)
        const cbtStr m_Name;
        cbtTextureShape m_Shape;
        cbtS32 m_Width, m_Height;
        cbtPixelFormat m_PixelFormat;

        // Constructor(s) & Destructor
        cbtTexture(const cbtStr& _name, cbtTextureShape _shape, cbtS32 _width, cbtS32 _height,
                cbtPixelFormat _pixelFormat)
                :m_Name(_name), m_Shape(_shape), m_Width(_width), m_Height(_height), m_PixelFormat(_pixelFormat)
        {
        }

        virtual ~cbtTexture()
        {
        }

    public:
        // Interface Function(s)
        inline const cbtStr& GetName() const
        {
            return m_Name;
        }

        inline cbtTextureShape GetShape() const
        {
            return m_Shape;
        }

        inline cbtS32 GetWidth() const
        {
            return m_Width;
        }

        inline cbtS32 GetHeight() const
        {
            return m_Height;
        }

        inline cbtPixelFormat GetPixelFormat() const
        {
            return m_PixelFormat;
        }

        virtual void SetWrapMode(cbtTextureWrap _wrapMode) = 0;

        virtual cbtTextureWrap GetWrapMode() const = 0;

        virtual void Bind(cbtU32 _textureSlot) = 0;

        static cbtTexture*
        Create2DTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat,
                const cbtU8* _data);

        static cbtTexture*
        CreateCubeMap(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat,
                std::array<const cbtU8*, CBT_CUBEMAP_MAX_SIDES> _data);

        static cbtTexture*
        CreateFrameBufferAttachment(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat);
    };

NS_CBT_END