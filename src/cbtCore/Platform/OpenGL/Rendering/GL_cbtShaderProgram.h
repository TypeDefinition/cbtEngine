#pragma once

// Include CBT
#include "Rendering/Shader/cbtShaderProgram.h"

#ifdef CBT_OPENGL

// Include GL
#include <GL/glew.h>
// #include <gl/GL.h>

NS_CBT_BEGIN

    class GL_cbtShaderProgram : public cbtShaderProgram
    {
    protected:
        GLuint m_ProgramID;
        GLint m_Uniforms[CBT_NUM_SHADER_UNIFORM];

        virtual ~GL_cbtShaderProgram();

        GLuint CreateGLShader(GLenum _shaderType, const cbtStr& _shaderSource);

        GLint GetUniformLocation(const cbtStr& _uniformName) const;

        GLint GetAttributeLocation(const cbtStr& _attributeName) const;

    public:
        GL_cbtShaderProgram(const cbtStr& _name, const std::vector<cbtStr>& _vertexShaderSources,
                const std::vector<cbtStr> _fragmentShaderSources);

        /// Use Program
        virtual void UseProgram();

        // Texture
        virtual void SetTexture(cbtU32 _textureSlot, cbtTexture* _texture);

        // Float
        virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0);

        virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1);

        virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2);

        virtual void
        SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2, cbtF32 _value3);

        // Integer
        virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0);

        virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1);

        virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2);

        virtual void
        SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2, cbtS32 _value3);

        // Unsigned Integer
        virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0);

        virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1);

        virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2);

        virtual void
        SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2, cbtU32 _value3);

        // Boolean
        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2);

        virtual void
        SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2, cbtBool _value3);

        // Matrix (Updated)
        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix2F& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix3F& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix4F& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 2>& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 3>& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 4>& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 2>& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 3>& _value);

        virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 4>& _value);

        // Color
        virtual void SetUniform(const cbtStr& _uniformName, const cbtColor& _value);

        // Vector2
        virtual void SetUniform(const cbtStr& _uniformName, const cbtVector2F& _value);

        virtual void SetUniform(const cbtStr& _uniformName, const cbtVector2U& _value);

        virtual void SetUniform(const cbtStr& _uniformName, const cbtVector2S& _value);

        // Vector3
        virtual void SetUniform(const cbtStr& _uniformName, const cbtVector3F& _value);

        virtual void SetUniform(const cbtStr& _uniformName, const cbtVector3U& _value);

        virtual void SetUniform(const cbtStr& _uniformName, const cbtVector3S& _value);

        // Float
        virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0);

        virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1);

        virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2);

        virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2, cbtF32 _value3);

        // Integer
        virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0);

        virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1);

        virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2);

        virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2, cbtS32 _value3);

        // Unsigned Integer
        virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0);

        virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1);

        virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2);

        virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2, cbtU32 _value3);

        // Boolean
        virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1, cbtBool _value2);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1, cbtBool _value2, cbtBool _value3);

        // Matrix
        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix2F& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix3F& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix4F& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 2>& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 3>& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 4>& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 2>& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 3>& _value);

        virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 4>& _value);

        // Color
        virtual void SetUniform(cbtU32 _uniformID, const cbtColor& _value);

        // Vector2
        virtual void SetUniform(cbtU32 _uniformID, const cbtVector2F& _value);

        virtual void SetUniform(cbtU32 _uniformID, const cbtVector2U& _value);

        virtual void SetUniform(cbtU32 _uniformID, const cbtVector2S& _value);

        // Vector3
        virtual void SetUniform(cbtU32 _uniformID, const cbtVector3F& _value);

        virtual void SetUniform(cbtU32 _uniformID, const cbtVector3U& _value);

        virtual void SetUniform(cbtU32 _uniformID, const cbtVector3S& _value);
    };

NS_CBT_END

#endif // CBT_OPENGL