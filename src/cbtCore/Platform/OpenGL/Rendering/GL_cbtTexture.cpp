// Include CBT
#include "GL_cbtTexture.h"
#include "Core/Math/cbtMathUtil.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

    GLenum ToGLBaseFormat(GLenum _sizedFormat)
    {
        switch (_sizedFormat)
        {
        case GL_R8:
            return GL_RED;
        case GL_R8_SNORM:
            return GL_RED;
        case GL_R16:
            return GL_RED;
        case GL_R16_SNORM:
            return GL_RED;
        case GL_RG8:
            return GL_RG;
        case GL_RG8_SNORM:
            return GL_RG;
        case GL_RG16:
            return GL_RG;
        case GL_RG16_SNORM:
            return GL_RG;
        case GL_R3_G3_B2:
            return GL_RGB;
        case GL_RGB4:
            return GL_RGB;
        case GL_RGB5:
            return GL_RGB;
        case GL_RGB8:
            return GL_RGB;
        case GL_RGB8_SNORM:
            return GL_RGB;
        case GL_RGB10:
            return GL_RGB;
        case GL_RGB12:
            return GL_RGB;
        case GL_RGB16_SNORM:
            return GL_RGB;
        case GL_RGBA2:
            return GL_RGB;
        case GL_RGBA4:
            return GL_RGB;
        case GL_RGB5_A1:
            return GL_RGBA;
        case GL_RGBA8:
            return GL_RGBA;
        case GL_RGBA8_SNORM:
            return GL_RGBA;
        case GL_RGB10_A2:
            return GL_RGBA;
        case GL_RGB10_A2UI:
            return GL_RGBA;
        case GL_RGBA12:
            return GL_RGBA;
        case GL_RGBA16:
            return GL_RGBA;
        case GL_SRGB8:
            return GL_RGB;
        case GL_SRGB8_ALPHA8:
            return GL_RGBA;
        case GL_R16F:
            return GL_RED;
        case GL_RG16F:
            return GL_RG;
        case GL_RGB16F:
            return GL_RGB;
        case GL_RGBA16F:
            return GL_RGBA;
        case GL_R32F:
            return GL_RED;
        case GL_RG32F:
            return GL_RG;
        case GL_RGB32F:
            return GL_RGB;
        case GL_RGBA32F:
            return GL_RGBA;
        case GL_R11F_G11F_B10F:
            return GL_RGB;
        case GL_RGB9_E5:
            return GL_RGB;
        case GL_R8I:
            return GL_RED;
        case GL_R8UI:
            return GL_RED;
        case GL_R16I:
            return GL_RED;
        case GL_R16UI:
            return GL_RED;
        case GL_R32I:
            return GL_RED;
        case GL_R32UI:
            return GL_RED;
        case GL_RG8I:
            return GL_RG;
        case GL_RG8UI:
            return GL_RG;
        case GL_RG16I:
            return GL_RG;
        case GL_RG16UI:
            return GL_RG;
        case GL_RG32I:
            return GL_RG;
        case GL_RG32UI:
            return GL_RG;
        case GL_RGB8I:
            return GL_RGB;
        case GL_RGB8UI:
            return GL_RGB;
        case GL_RGB16I:
            return GL_RGB;
        case GL_RGB16UI:
            return GL_RGB;
        case GL_RGB32I:
            return GL_RGB;
        case GL_RGB32UI:
            return GL_RGB;
        case GL_RGBA8I:
            return GL_RGBA;
        case GL_RGBA8UI:
            return GL_RGBA;
        case GL_RGBA16I:
            return GL_RGBA;
        case GL_RGBA16UI:
            return GL_RGBA;
        case GL_RGBA32I:
            return GL_RGBA;
        case GL_RGBA32UI:
            return GL_RGBA;
        default:
            return GL_INVALID_ENUM;
        }
    }

    GLenum ToGLBaseFormat(cbtPixelFormat _sizedFormat)
    {
        switch (_sizedFormat)
        {
        case CBT_R8:
            return GL_RED;
        case CBT_R8_SNORM:
            return GL_RED;
        case CBT_R16:
            return GL_RED;
        case CBT_R16_SNORM:
            return GL_RED;
        case CBT_RG8:
            return GL_RG;
        case CBT_RG8_SNORM:
            return GL_RG;
        case CBT_RG16:
            return GL_RG;
        case CBT_RG16_SNORM:
            return GL_RG;
        case CBT_R3_G3_B2:
            return GL_RGB;
        case CBT_RGB4:
            return GL_RGB;
        case CBT_RGB5:
            return GL_RGB;
        case CBT_RGB8:
            return GL_RGB;
        case CBT_RGB8_SNORM:
            return GL_RGB;
        case CBT_RGB10:
            return GL_RGB;
        case CBT_RGB12:
            return GL_RGB;
        case CBT_RGB16_SNORM:
            return GL_RGB;
        case CBT_RGBA2:
            return GL_RGB;
        case CBT_RGBA4:
            return GL_RGB;
        case CBT_RGB5_A1:
            return GL_RGBA;
        case CBT_RGBA8:
            return GL_RGBA;
        case CBT_RGBA8_SNORM:
            return GL_RGBA;
        case CBT_RGB10_A2:
            return GL_RGBA;
        case CBT_RGB10_A2UI:
            return GL_RGBA;
        case CBT_RGBA12:
            return GL_RGBA;
        case CBT_RGBA16:
            return GL_RGBA;
        case CBT_SRGB8:
            return GL_RGB;
        case CBT_SRGB8_ALPHA8:
            return GL_RGBA;
        case CBT_R16F:
            return GL_RED;
        case CBT_RG16F:
            return GL_RG;
        case CBT_RGB16F:
            return GL_RGB;
        case CBT_RGBA16F:
            return GL_RGBA;
        case CBT_R32F:
            return GL_RED;
        case CBT_RG32F:
            return GL_RG;
        case CBT_RGB32F:
            return GL_RGB;
        case CBT_RGBA32F:
            return GL_RGBA;
        case CBT_R11F_G11F_B10F:
            return GL_RGB;
        case CBT_RGB9_E5:
            return GL_RGB;
        case CBT_R8I:
            return GL_RED;
        case CBT_R8UI:
            return GL_RED;
        case CBT_R16I:
            return GL_RED;
        case CBT_R16UI:
            return GL_RED;
        case CBT_R32I:
            return GL_RED;
        case CBT_R32UI:
            return GL_RED;
        case CBT_RG8I:
            return GL_RG;
        case CBT_RG8UI:
            return GL_RG;
        case CBT_RG16I:
            return GL_RG;
        case CBT_RG16UI:
            return GL_RG;
        case CBT_RG32I:
            return GL_RG;
        case CBT_RG32UI:
            return GL_RG;
        case CBT_RGB8I:
            return GL_RGB;
        case CBT_RGB8UI:
            return GL_RGB;
        case CBT_RGB16I:
            return GL_RGB;
        case CBT_RGB16UI:
            return GL_RGB;
        case CBT_RGB32I:
            return GL_RGB;
        case CBT_RGB32UI:
            return GL_RGB;
        case CBT_RGBA8I:
            return GL_RGBA;
        case CBT_RGBA8UI:
            return GL_RGBA;
        case CBT_RGBA16I:
            return GL_RGBA;
        case CBT_RGBA16UI:
            return GL_RGBA;
        case CBT_RGBA32I:
            return GL_RGBA;
        case CBT_RGBA32UI:
            return GL_RGBA;
        default:
            return GL_INVALID_ENUM;
        }
    }

    GLenum ToGLSizedFormat(cbtPixelFormat _format)
    {
        switch (_format)
        {
            // Color
        case CBT_R8:
            return GL_R8;
        case CBT_R8_SNORM:
            return GL_R8_SNORM;
        case CBT_R16:
            return GL_R16;
        case CBT_R16_SNORM:
            return GL_R16_SNORM;
        case CBT_RG8:
            return GL_RG8;
        case CBT_RG8_SNORM:
            return GL_RG8_SNORM;
        case CBT_RG16:
            return GL_RG16;
        case CBT_RG16_SNORM:
            return GL_RG16_SNORM;
        case CBT_R3_G3_B2:
            return GL_R3_G3_B2;
        case CBT_RGB4:
            return GL_RGB4;
        case CBT_RGB5:
            return GL_RGB5;
        case CBT_RGB8:
            return GL_RGB8;
        case CBT_RGB8_SNORM:
            return GL_RGB8_SNORM;
        case CBT_RGB10:
            return GL_RGB10;
        case CBT_RGB12:
            return GL_RGB12;
        case CBT_RGB16_SNORM:
            return GL_RGB16_SNORM;
        case CBT_RGBA2:
            return GL_RGBA2;
        case CBT_RGBA4:
            return GL_RGBA4;
        case CBT_RGB5_A1:
            return GL_RGB5_A1;
        case CBT_RGBA8:
            return GL_RGBA8;
        case CBT_RGBA8_SNORM:
            return GL_RGBA8_SNORM;
        case CBT_RGB10_A2:
            return GL_RGB10_A2;
        case CBT_RGB10_A2UI:
            return GL_RGB10_A2UI;
        case CBT_RGBA12:
            return GL_RGBA12;
        case CBT_RGBA16:
            return GL_RGBA16;
        case CBT_SRGB8:
            return GL_SRGB8;
        case CBT_SRGB8_ALPHA8:
            return GL_SRGB8_ALPHA8;
        case CBT_R16F:
            return GL_R16F;
        case CBT_RG16F:
            return GL_RG16F;
        case CBT_RGB16F:
            return GL_RGB16F;
        case CBT_RGBA16F:
            return GL_RGBA16F;
        case CBT_R32F:
            return GL_R32F;
        case CBT_RG32F:
            return GL_RG32F;
        case CBT_RGB32F:
            return GL_RGB32F;
        case CBT_RGBA32F:
            return GL_RGBA32F;
        case CBT_R11F_G11F_B10F:
            return GL_R11F_G11F_B10F;
        case CBT_RGB9_E5:
            return GL_RGB9_E5;
        case CBT_R8I:
            return GL_R8I;
        case CBT_R8UI:
            return GL_R8UI;
        case CBT_R16I:
            return GL_R16I;
        case CBT_R16UI:
            return GL_R16UI;
        case CBT_R32I:
            return GL_R32I;
        case CBT_R32UI:
            return GL_R32UI;
        case CBT_RG8I:
            return GL_RG8I;
        case CBT_RG8UI:
            return GL_RG8UI;
        case CBT_RG16I:
            return GL_RG16I;
        case CBT_RG16UI:
            return GL_RG16UI;
        case CBT_RG32I:
            return GL_RG32I;
        case CBT_RG32UI:
            return GL_RG32UI;
        case CBT_RGB8I:
            return GL_RGB8I;
        case CBT_RGB8UI:
            return GL_RGB8UI;
        case CBT_RGB16I:
            return GL_RGB16I;
        case CBT_RGB16UI:
            return GL_RGB16UI;
        case CBT_RGB32I:
            return GL_RGB32I;
        case CBT_RGB32UI:
            return GL_RGB32UI;
        case CBT_RGBA8I:
            return GL_RGBA8I;
        case CBT_RGBA8UI:
            return GL_RGBA8UI;
        case CBT_RGBA16I:
            return GL_RGBA16I;
        case CBT_RGBA16UI:
            return GL_RGBA16UI;
        case CBT_RGBA32I:
            return GL_RGBA32I;
        case CBT_RGBA32UI:
            return GL_RGBA32UI;

            // Depth
        case CBT_DEPTH_COMPONENT32F:
            return GL_DEPTH_COMPONENT32F;
        case CBT_DEPTH_COMPONENT24:
            return GL_DEPTH_COMPONENT24;
        case CBT_DEPTH_COMPONENT16:
            return GL_DEPTH_COMPONENT16;

            // Depth-Stencil
        case CBT_DEPTH32F_STENCIL8:
            return GL_DEPTH32F_STENCIL8;
        case CBT_DEPTH24_STENCIL8:
            return GL_DEPTH24_STENCIL8;

            // Stencil
        case CBT_STENCIL_INDEX8:
            return GL_STENCIL_INDEX8;

            // Invalid
        default:
            return GL_INVALID_ENUM;
        }
    }

    cbtPixelFormat ToCBTSizedFormat(GLenum _sizedFormat)
    {
        switch (_sizedFormat)
        {
            // Color
        case GL_R8:
            return CBT_R8;
        case GL_R8_SNORM:
            return CBT_R8_SNORM;
        case GL_R16:
            return CBT_R16;
        case GL_R16_SNORM:
            return CBT_R16_SNORM;
        case GL_RG8:
            return CBT_RG8;
        case GL_RG8_SNORM:
            return CBT_RG8_SNORM;
        case GL_RG16:
            return CBT_RG16;
        case GL_RG16_SNORM:
            return CBT_RG16_SNORM;
        case GL_R3_G3_B2:
            return CBT_R3_G3_B2;
        case GL_RGB4:
            return CBT_RGB4;
        case GL_RGB5:
            return CBT_RGB5;
        case GL_RGB8:
            return CBT_RGB8;
        case GL_RGB8_SNORM:
            return CBT_RGB8_SNORM;
        case GL_RGB10:
            return CBT_RGB10;
        case GL_RGB12:
            return CBT_RGB12;
        case GL_RGB16_SNORM:
            return CBT_RGB16_SNORM;
        case GL_RGBA2:
            return CBT_RGBA2;
        case GL_RGBA4:
            return CBT_RGBA4;
        case GL_RGB5_A1:
            return CBT_RGB5_A1;
        case GL_RGBA8:
            return CBT_RGBA8;
        case GL_RGBA8_SNORM:
            return CBT_RGBA8_SNORM;
        case GL_RGB10_A2:
            return CBT_RGB10_A2;
        case GL_RGB10_A2UI:
            return CBT_RGB10_A2UI;
        case GL_RGBA12:
            return CBT_RGBA12;
        case GL_RGBA16:
            return CBT_RGBA16;
        case GL_SRGB8:
            return CBT_SRGB8;
        case GL_SRGB8_ALPHA8:
            return CBT_SRGB8_ALPHA8;
        case GL_R16F:
            return CBT_R16F;
        case GL_RG16F:
            return CBT_RG16F;
        case GL_RGB16F:
            return CBT_RGB16F;
        case GL_RGBA16F:
            return CBT_RGBA16F;
        case GL_R32F:
            return CBT_R32F;
        case GL_RG32F:
            return CBT_RG32F;
        case GL_RGB32F:
            return CBT_RGB32F;
        case GL_RGBA32F:
            return CBT_RGBA32F;
        case GL_R11F_G11F_B10F:
            return CBT_R11F_G11F_B10F;
        case GL_RGB9_E5:
            return CBT_RGB9_E5;
        case GL_R8I:
            return CBT_R8I;
        case GL_R8UI:
            return CBT_R8UI;
        case GL_R16I:
            return CBT_R16I;
        case GL_R16UI:
            return CBT_R16UI;
        case GL_R32I:
            return CBT_R32I;
        case GL_R32UI:
            return CBT_R32UI;
        case GL_RG8I:
            return CBT_RG8I;
        case GL_RG8UI:
            return CBT_RG8UI;
        case GL_RG16I:
            return CBT_RG16I;
        case GL_RG16UI:
            return CBT_RG16UI;
        case GL_RG32I:
            return CBT_RG32I;
        case GL_RG32UI:
            return CBT_RG32UI;
        case GL_RGB8I:
            return CBT_RGB8I;
        case GL_RGB8UI:
            return CBT_RGB8UI;
        case GL_RGB16I:
            return CBT_RGB16I;
        case GL_RGB16UI:
            return CBT_RGB16UI;
        case GL_RGB32I:
            return CBT_RGB32I;
        case GL_RGB32UI:
            return CBT_RGB32UI;
        case GL_RGBA8I:
            return CBT_RGBA8I;
        case GL_RGBA8UI:
            return CBT_RGBA8UI;
        case GL_RGBA16I:
            return CBT_RGBA16I;
        case GL_RGBA16UI:
            return CBT_RGBA16UI;
        case GL_RGBA32I:
            return CBT_RGBA32I;
        case GL_RGBA32UI:
            return CBT_RGBA32UI;

            // Depth
        case GL_DEPTH_COMPONENT32F:
            return CBT_DEPTH_COMPONENT32F;
        case GL_DEPTH_COMPONENT24:
            return CBT_DEPTH_COMPONENT24;
        case GL_DEPTH_COMPONENT16:
            return CBT_DEPTH_COMPONENT16;

            // Depth-Stencil
        case GL_DEPTH32F_STENCIL8:
            return CBT_DEPTH32F_STENCIL8;
        case GL_DEPTH24_STENCIL8:
            return CBT_DEPTH24_STENCIL8;

            // Stencil
        case GL_STENCIL_INDEX8:
            return CBT_STENCIL_INDEX8;

            // Invalid
        default:
            return CBT_INVALID_PIXEL_FORMAT;
        }
    }

    cbtS32 GetMipmapLevels(cbtS32 _width, cbtS32 _height)
    {
        cbtS32 log2Width = (cbtS32)cbtMathUtil::Log2((cbtF32)_width);
        cbtS32 log2Height = (cbtS32)cbtMathUtil::Log2((cbtF32)_height);
        return cbtMathUtil::Clamp<cbtS32>(cbtMathUtil::Min<cbtS32>(log2Width, log2Height), 1, GL_TEXTURE_MAX_LEVEL);
    }

    cbtTexture*
    cbtTexture::Create2DTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat,
            const cbtU8* _data)
    {
        return cbtNew GL_cbtTexture(_name, _width, _height, _pixelFormat, _data);
    }

    cbtTexture*
    cbtTexture::CreateCubeMap(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat,
            std::array<const cbtU8*, CBT_CUBEMAP_MAX_SIDES> _data)
    {
        return cbtNew GL_cbtTexture(_name, _width, _height, _pixelFormat, _data);
    }

    cbtTexture* cbtTexture::CreateFrameBufferAttachment(const cbtStr& _name, cbtS32 _width, cbtS32 _height,
            cbtPixelFormat _pixelFormat)
    {
        return cbtNew GL_cbtTexture(_name, _width, _height, _pixelFormat);
    }

    GL_cbtTexture::GL_cbtTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat,
            const cbtU8* _data)
            :cbtTexture(_name, CBT_TEXTURE_SHAPE_2D, _width, _height, _pixelFormat),
             m_WrapMode(CBT_TEXTURE_WRAP_REPEAT)
    {
        /* IMPORTANT: Unlike glTexImage2D, we have to explicitly state the number of mipmaps to generate.
        We can no longer leave it at 0 and expect OpenGL to figure out how many mipmaps to generate.
        This is because glTextureStorage2D creates a fixed storage space for our texture, not like
        glTexImage2D where it can resize itself to generate mipmaps. The glTextureStorage2D documentation
        states "GL_INVALID_VALUE is generated if width, height or levels are less than 1." */

        // Direct-State-Access Method (OpenGL 4.5)
        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureName);
        CBT_ASSERT(m_TextureName != GL_INVALID_ENUM);

        glTextureStorage2D(m_TextureName, GetMipmapLevels(_width, _height),
                ToGLSizedFormat(m_PixelFormat), ///< Format to store the texture data in OpenGL.
                m_Width, m_Height);
        glTextureSubImage2D(m_TextureName, 0, 0, 0, m_Width, m_Height,
                ToGLBaseFormat(m_PixelFormat), ///< Format of the image data.
                GL_UNSIGNED_BYTE, _data);

        // Texture Parameter(s)
        glTextureParameteri(m_TextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_TextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateTextureMipmap(m_TextureName);
    }

    GL_cbtTexture::GL_cbtTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat,
            std::array<const cbtU8*, CBT_CUBEMAP_MAX_SIDES> _data)
            :cbtTexture(_name, CBT_TEXTURE_SHAPE_CUBE, _width, _height, _pixelFormat),
             m_WrapMode(CBT_TEXTURE_WRAP_CLAMP_TO_EDGE)
    {
        /* IMPORTANT: Unlike glTexImage2D, we have to explicitly state the number of mipmaps to generate.
        We can no longer leave it at 0 and expect OpenGL to figure out how many mipmaps to generate.
        This is because glTextureStorage2D creates a fixed storage space for our texture, not like
        glTexImage2D where it can resize itself to generate mipmaps. The glTextureStorage2D documentation
        states "GL_INVALID_VALUE is generated if width, height or levels are less than 1." */

        // Direct-State-Access Method (OpenGL 4.5)
        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureName);

        // Set the texture data.
        glTextureStorage2D(m_TextureName, GetMipmapLevels(_width, _height),
                ToGLSizedFormat(
                        m_PixelFormat), ///< Format to store the texture data in OpenGL. Standardise to RGBA8
                m_Width, m_Height);

        for (cbtS32 i = 0; i < CBT_CUBEMAP_MAX_SIDES; ++i)
        {
            // Note that for cubemaps, we have to use glTextureSubImage3D instead of glTextureSubImage2D, but we still use glTextureStorage2D.
            glTextureSubImage3D(m_TextureName, 0, 0, 0, i, m_Width, m_Height, 1,
                    ToGLBaseFormat(m_PixelFormat), ///< Format of the image data.
                    GL_UNSIGNED_BYTE, _data[i]);
        }

        // Texture Parameter(s)
        glTextureParameteri(m_TextureName, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureName, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // Generate Mipmap
        glGenerateTextureMipmap(m_TextureName);
    }

    GL_cbtTexture::GL_cbtTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat)
            :cbtTexture(_name, CBT_TEXTURE_SHAPE_2D, _width, _height, _pixelFormat),
             m_WrapMode(CBT_TEXTURE_WRAP_REPEAT)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureName);
        glTextureStorage2D(m_TextureName, 1, ToGLSizedFormat(_pixelFormat), _width, _height);
        glTextureParameteri(m_TextureName, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureName, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void GL_cbtTexture::SetWrapMode(cbtTextureWrap _wrapMode)
    {
        CBT_ASSERT(m_Shape != CBT_TEXTURE_SHAPE_CUBE);
        if (m_Shape == CBT_TEXTURE_SHAPE_CUBE)
        { return; }

        m_WrapMode = _wrapMode;
        switch (m_WrapMode)
        {
        case CBT_TEXTURE_WRAP_REPEAT:
            glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case CBT_TEXTURE_WRAP_MIRRORED_REPEAT:
            glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        case CBT_TEXTURE_WRAP_CLAMP_TO_EDGE:
            glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(m_TextureName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        default:
            break;
        }
    }

NS_CBT_END

#endif // CBT_OPENGL