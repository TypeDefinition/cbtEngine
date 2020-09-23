#pragma once

// Include CBT
#include "CBTPixelFormat.h"
#include "Debug/CBTDebug.h"
#include "Core/General/CBTRef.h"

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

enum CBTTextureShape
{
    CBT_TEXTURE_SHAPE_2D,
    CBT_TEXTURE_SHAPE_CUBE,
};

enum CBTTextureWrap
{
    CBT_TEXTURE_WRAP_REPEAT,
    CBT_TEXTURE_WRAP_MIRRORED_REPEAT,
    CBT_TEXTURE_WRAP_CLAMP_TO_EDGE,
};

// Texture format of texture should be standardised to RGBA.
class CBTTexture : public CBTManaged
{
protected:
    // Variable(s)
    const cbtStr m_Name;
    CBTTextureShape m_Shape;
    cbtS32 m_Width, m_Height;
    CBTPixelFormat m_PixelFormat;

    // Constructor(s) & Destructor
    CBTTexture(const cbtStr& _name, CBTTextureShape _shape, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat)
        : m_Name(_name)
        , m_Shape(_shape)
        , m_Width(_width)
        , m_Height(_height)
        , m_PixelFormat(_pixelFormat)
    {}
    virtual ~CBTTexture() {}

public:
    // Interface Function(s)
    inline const cbtStr& GetName() const { return m_Name; }
    inline CBTTextureShape GetShape() const { return m_Shape; }
    inline cbtS32 GetWidth() const { return m_Width; }
    inline cbtS32 GetHeight() const { return m_Height; }
    inline CBTPixelFormat GetPixelFormat() const { return m_PixelFormat; }

    virtual void SetWrapMode(CBTTextureWrap _wrapMode) = 0;
    virtual CBTTextureWrap GetWrapMode() const = 0;
    virtual void Bind(cbtU32 _textureSlot) = 0;

    static CBTTexture* Create2DTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat, const cbtU8* _data);
    static CBTTexture* CreateCubeMap(const cbtStr& _name, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat, std::array<const cbtU8*, CBT_CUBEMAP_MAX_SIDES> _data);
    static CBTTexture* CreateFrameBufferAttachment(const cbtStr& _name, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat);
};

NS_CBT_END