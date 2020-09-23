#pragma once

// Include CBT
#include "Rendering/Texture/CBTTexture.h"
#include "GL_CBTTexture.h"

#ifdef CBT_OPENGL

// Include GL
#include <glew.h>
#include <gl/GL.h>

NS_CBT_BEGIN

GLenum ToGLBaseFormat(GLenum _sizedFormat);
GLenum ToGLBaseFormat(CBTPixelFormat _sizedFormat);
GLenum ToGLSizedFormat(CBTPixelFormat _sizedFormat);
CBTPixelFormat ToCBTSizedFormat(GLenum _sizedFormat);
cbtS32 GetMipmapLevels(cbtS32 _width, cbtS32 _height);

class GL_CBTTexture : public CBTTexture
{
protected:
    // Variable(s)
    GLuint m_TextureName;
    CBTTextureWrap m_WrapMode;

    virtual ~GL_CBTTexture() { glDeleteTextures(1, &m_TextureName); }

public:
    GL_CBTTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat, const cbtU8* _data);
    GL_CBTTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat, std::array<const cbtU8*, CBT_CUBEMAP_MAX_SIDES> _data);
    GL_CBTTexture(const cbtStr& _name, cbtS32 _width, cbtS32 _height, CBTPixelFormat _pixelFormat);

    virtual void SetWrapMode(CBTTextureWrap _wrapMode);
    virtual CBTTextureWrap GetWrapMode() const { return m_WrapMode; }
    virtual void Bind(cbtU32 _textureSlot) { glBindTextureUnit(_textureSlot, m_TextureName); }

    inline GLuint GetGLTextureName() const { return m_TextureName; }
};

NS_CBT_END

#endif // CBT_OPENGL