#pragma once

// Include CBT
#include "Rendering/Texture/cbtTexture.h"
#include "GL_cbtTexture.h"

#ifdef CBT_OPENGL

// Include GL
#include <glew.h>
#include <gl/GL.h>

NS_CBT_BEGIN

GLenum ToGLBaseFormat(GLenum _sizedFormat);
GLenum ToGLBaseFormat(cbtPixelFormat _sizedFormat);
GLenum ToGLSizedFormat(cbtPixelFormat _sizedFormat);
cbtPixelFormat ToCBTSizedFormat(GLenum _sizedFormat);
cbtS32 GetMipmapLevels(cbtS32 _width, cbtS32 _height);

class GL_cbtTexture : public cbtTexture
{
protected:
    // Variable(s)
    GLuint m_TextureName;
    cbtTextureWrap m_WrapMode;

    virtual ~GL_cbtTexture() { glDeleteTextures(1, &m_TextureName); }

public:
    GL_cbtTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat, const cbtU8* _data);
    GL_cbtTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat, std::array<const cbtU8*, CBT_CUBEMAP_MAX_SIDES> _data);
    GL_cbtTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, cbtPixelFormat _pixelFormat);

    virtual void SetWrapMode(cbtTextureWrap _wrapMode);
    virtual cbtTextureWrap GetWrapMode() const { return m_WrapMode; }
    virtual void Bind(cbtU32 _textureSlot) { glBindTextureUnit(_textureSlot, m_TextureName); }

    inline GLuint GetGLTextureName() const { return m_TextureName; }
};

NS_CBT_END

#endif // CBT_OPENGL