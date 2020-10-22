// Include CBT
#include "GL_cbtShaderProgram.h"
#include "Debug/cbtDebug.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

    cbtShaderProgram*
    cbtShaderProgram::CreateShaderProgram(const cbtStr& _name, const std::vector<cbtStr>& _vertexShaderSources,
            const std::vector<cbtStr>& _fragmentShaderSources)
    {
        return new GL_cbtShaderProgram(_name, _vertexShaderSources, _fragmentShaderSources);
    }

    GL_cbtShaderProgram::GL_cbtShaderProgram(const cbtStr& _name, const std::vector<cbtStr>& _vertexShaderSources,
            const std::vector<cbtStr> _fragmentShaderSources)
            :cbtShaderProgram(_name)
    {
        std::vector<GLuint> vertexShaderIDs, fragmentShaderIDs;

        // Create the shader program.
        m_ProgramID = glCreateProgram();

        // Create the shaders.
        for (cbtS32 i = 0; i < _vertexShaderSources.size(); ++i)
        {
            // Create the fragment shader. OpenGL supports multiple vertex shaders per shader program.
            GLuint vertexShaderID = CreateGLShader(GL_VERTEX_SHADER, _vertexShaderSources[i]);
            vertexShaderIDs.push_back(vertexShaderID);
            // Attach the shader to the program.
            glAttachShader(m_ProgramID, vertexShaderID);
        }

        for (cbtS32 i = 0; i < _fragmentShaderSources.size(); ++i)
        {
            // Create the fragment shader. OpenGL supports multiple fragment shaders per shader program.
            GLuint fragmentShaderID = CreateGLShader(GL_FRAGMENT_SHADER, _fragmentShaderSources[i]);
            fragmentShaderIDs.push_back(fragmentShaderID);
            // Attach the shader to the program.
            glAttachShader(m_ProgramID, fragmentShaderID);
        }

        // Link the shader program. Now that we have attached the shaders, this will use the attached shaders to create an executable that will run on the programmable vertex processor.
        glLinkProgram(m_ProgramID);

        /* Now that we are done creating the shader program, we no longer need the shaders and they can be deleted.
        It is also possible to store the shaders to create other shader programs,
        but there isn't a compelling reason to do so since we can just re-create them again if necessary. */
        for (cbtS32 i = 0; i < vertexShaderIDs.size(); ++i)
        {
            glDetachShader(m_ProgramID, vertexShaderIDs[i]);
            glDeleteShader(vertexShaderIDs[i]);
        }
        for (cbtS32 i = 0; i < fragmentShaderIDs.size(); ++i)
        {
            glDetachShader(m_ProgramID, fragmentShaderIDs[i]);
            glDeleteShader(fragmentShaderIDs[i]);
        }

        // Verify Link Status
        GLint linkStatus = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE)
        {
            // Get Info Log
            GLint infoLogLength = 0;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetProgramInfoLog(
                    m_ProgramID/*Shader*/,
                    infoLogLength /*Max Length*/,
                    &infoLogLength /*This returns the length of the Info Log. (We already know the value, but we need to pass in the parameter anyways.)*/,
                    infoLog/*Info Log*/);

            // Assert
            CBT_LOG_ERROR(CBT_LOG_CATEGORY_RENDER, infoLog);
            CBT_ASSERT(false);

            // Clean-up
            delete[] infoLog;
        }

        // Get Uniform(s)
        m_Uniforms[CBT_U_MATRIX_PROJECTION] = GetUniformLocation("CBT_U_MATRIX_PROJECTION");
        m_Uniforms[CBT_U_TEXTURE_SCALE] = GetUniformLocation("CBT_U_TEXTURE_SCALE");
        m_Uniforms[CBT_U_TEXTURE_OFFSET] = GetUniformLocation("CBT_U_TEXTURE_OFFSET");

        m_Uniforms[CBT_U_TEXTURE_SKYBOX_ENABLED] = GetUniformLocation("CBT_U_TEXTURE_SKYBOX_ENABLED");
        m_Uniforms[CBT_U_SKYBOX_COLOR] = GetUniformLocation("CBT_U_SKYBOX_COLOR");

        m_Uniforms[CBT_U_TEXTURE_ALBEDO_ENABLED] = GetUniformLocation("CBT_U_TEXTURE_ALBEDO_ENABLED");
        m_Uniforms[CBT_U_TEXTURE_NORMAL_ENABLED] = GetUniformLocation("CBT_U_TEXTURE_NORMAL_ENABLED");
        m_Uniforms[CBT_U_TEXTURE_SPECULAR_ENABLED] = GetUniformLocation("CBT_U_TEXTURE_SPECULAR_ENABLED");
        m_Uniforms[CBT_U_TEXTURE_GLOSS_ENABLED] = GetUniformLocation("CBT_U_TEXTURE_GLOSS_ENABLED");
        m_Uniforms[CBT_U_TEXTURE_DISPLACEMENT_ENABLED] = GetUniformLocation("CBT_U_TEXTURE_DISPLACEMENT_ENABLED");

        m_Uniforms[CBT_U_AMBIENT_COLOR] = GetUniformLocation("CBT_U_AMBIENT_COLOR");
        m_Uniforms[CBT_U_ALBEDO_COLOR] = GetUniformLocation("CBT_U_ALBEDO_COLOR");
        m_Uniforms[CBT_U_SPECULAR_COLOR] = GetUniformLocation("CBT_U_SPECULAR_COLOR");
        m_Uniforms[CBT_U_GLOSS] = GetUniformLocation("CBT_U_GLOSS");

        m_Uniforms[CBT_U_DISPLACEMENT_SCALE] = GetUniformLocation("CBT_U_DISPLACEMENT_SCALE");
        m_Uniforms[CBT_U_MIN_DISPLACEMENT_SAMPLE] = GetUniformLocation("CBT_U_MIN_DISPLACEMENT_SAMPLE");
        m_Uniforms[CBT_U_MAX_DISPLACEMENT_SAMPLE] = GetUniformLocation("CBT_U_MAX_DISPLACEMENT_SAMPLE");

        m_Uniforms[CBT_U_LIGHTING_ENABLED] = GetUniformLocation("CBT_U_LIGHTING_ENABLED");
        m_Uniforms[CBT_U_ACTIVE_LIGHTS] = GetUniformLocation("CBT_U_ACTIVE_LIGHTS");

        m_Uniforms[CBT_U_BUFFER_WIDTH] = GetUniformLocation("CBT_U_BUFFER_WIDTH");
        m_Uniforms[CBT_U_BUFFER_HEIGHT] = GetUniformLocation("CBT_U_BUFFER_HEIGHT");

        m_Uniforms[CBT_U_NEAR_PLANE] = GetUniformLocation("CBT_U_NEAR_PLANE");
        m_Uniforms[CBT_U_FAR_PLANE] = GetUniformLocation("CBT_U_FAR_PLANE");

        for (cbtU32 i = 0; i < CBT_MAX_LIGHTS; ++i)
        {
            m_Uniforms[i + CBT_U_LIGHT_MODE0] = GetUniformLocation("CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_Mode");
            m_Uniforms[i + CBT_U_LIGHT_POWER0] = GetUniformLocation("CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_Power");
            m_Uniforms[i + CBT_U_LIGHT_COLOR0] = GetUniformLocation("CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_Color");
            m_Uniforms[i + CBT_U_LIGHT_POSITION_CAMERA_SPACE0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_PositionCameraSpace");
            m_Uniforms[i + CBT_U_LIGHT_DIRECTION_CAMERA_SPACE0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_DirectionCameraSpace");
            m_Uniforms[i + CBT_U_LIGHT_ATTENUATION_CONSTANT0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_AttenuationConstant");
            m_Uniforms[i + CBT_U_LIGHT_ATTENUATION_LINEAR0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_AttenuationLinear");
            m_Uniforms[i + CBT_U_LIGHT_ATTENUATION_QUADRATIC0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_AttenuationQuadratic");
            m_Uniforms[i + CBT_U_LIGHT_SPOTLIGHT_INNER_COSINE0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_SpotlightInnerCosine");
            m_Uniforms[i + CBT_U_LIGHT_SPOTLIGHT_OUTER_COSINE0] = GetUniformLocation(
                    "CBT_U_LIGHT[" + CBT_TO_STRING(i) + "].m_SpotlightOuterCosine");
        }

        // Assign textures to GL_TEXTURE0 to GL_TEXTUREN
        SetUniform("CBT_TEXTURE_SKYBOX", CBT_TEXTURE_SKYBOX);

        SetUniform("CBT_TEXTURE_ALBEDO", CBT_TEXTURE_ALBEDO);
        SetUniform("CBT_TEXTURE_NORMAL", CBT_TEXTURE_NORMAL);
        SetUniform("CBT_TEXTURE_SPECULAR", CBT_TEXTURE_SPECULAR);
        SetUniform("CBT_TEXTURE_GLOSS", CBT_TEXTURE_GLOSS);
        SetUniform("CBT_TEXTURE_DISPLACEMENT", CBT_TEXTURE_DISPLACEMENT);

        SetUniform("CBT_GBUFFER_POSITION_CAMERA_SPACE", CBT_GBUFFER_POSITION_CAMERA_SPACE);
        SetUniform("CBT_GBUFFER_NORMAL_CAMERA_SPACE", CBT_GBUFFER_NORMAL_CAMERA_SPACE);
        SetUniform("CBT_GBUFFER_AMBIENT_COLOR", CBT_GBUFFER_AMBIENT_COLOR);
        SetUniform("CBT_GBUFFER_ALBEDO_COLOR", CBT_GBUFFER_ALBEDO_COLOR);
        SetUniform("CBT_GBUFFER_SPECULAR_COLOR", CBT_GBUFFER_SPECULAR_COLOR);
        SetUniform("CBT_GBUFFER_GLOSS", CBT_GBUFFER_GLOSS);

        SetUniform("CBT_LBUFFER_COMPOSITE", CBT_LBUFFER_COMPOSITE);
        SetUniform("CBT_LBUFFER_LIGHT_DIFFUSE", CBT_LBUFFER_LIGHT_DIFFUSE);
        SetUniform("CBT_LBUFFER_LIGHT_SPECULAR", CBT_LBUFFER_LIGHT_SPECULAR);

        SetUniform("CBT_FBUFFER_POSITION_CAMERA_SPACE", CBT_FBUFFER_POSITION_CAMERA_SPACE);
        SetUniform("CBT_FBUFFER_NORMAL_CAMERA_SPACE", CBT_FBUFFER_NORMAL_CAMERA_SPACE);
        SetUniform("CBT_FBUFFER_DEPTH_STENCIL", CBT_FBUFFER_DEPTH_STENCIL);

        SetUniform("CBT_PBUFFER_COMPOSITE", CBT_PBUFFER_COMPOSITE);

        CBT_LOG_INFO(CBT_LOG_CATEGORY_RENDER, "%s Created", _name.c_str());
    }

    GL_cbtShaderProgram::~GL_cbtShaderProgram()
    {
        glDeleteProgram(m_ProgramID);
    }

    GLuint GL_cbtShaderProgram::CreateGLShader(GLenum _shaderType, const cbtStr& _shaderSource)
    {
        // Get the source code.
        const GLchar* sourceCode = _shaderSource.c_str();
        // Create the shader.
        GLuint shaderID = glCreateShader(_shaderType);
        // Set the source (the shader code) of the shader.
        glShaderSource(shaderID, 1, &(sourceCode), nullptr);
        // Compile the shader.
        glCompileShader(shaderID);

        // Verify Compile Status
        GLint compileStatus = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus == GL_FALSE)
        {
            // Get Info Log
            GLint infoLogLength = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetShaderInfoLog(
                    shaderID /*Shader*/,
                    infoLogLength /*Max Length*/,
                    &infoLogLength /*This returns the length of the Info Log. (We already know the value, but we need to pass in the parameter anyways.)*/,
                    infoLog/*Info Log*/);

            // Assert
            CBT_LOG_ERROR(CBT_LOG_CATEGORY_RENDER, infoLog);
            CBT_ASSERT(compileStatus != GL_FALSE);

            // Clean-up
            delete[] infoLog;
            glDeleteShader(shaderID);

            return 0;
        }
        return shaderID;
    }

    GLint GL_cbtShaderProgram::GetUniformLocation(const cbtStr& _uniformName) const
    {
        GLint uniformID = glGetUniformLocation(m_ProgramID, _uniformName.c_str());
        if (uniformID == -1)
        {
            cbtStr errorMessage = "Cannot find uniform " + _uniformName + " in shader " + m_Name + "!";
            CBT_LOG_WARN(CBT_LOG_CATEGORY_RENDER, errorMessage.c_str());
        }
        return uniformID;
    }

    GLint GL_cbtShaderProgram::GetAttributeLocation(const cbtStr& _attributeName) const
    {
        GLint attributeID = glGetAttribLocation(m_ProgramID, _attributeName.c_str());
        if (attributeID == -1)
        {
            cbtStr errorMessage = "Cannot find attribute " + _attributeName + " in shader " + m_Name + "!";
            CBT_LOG_WARN(CBT_LOG_CATEGORY_RENDER, errorMessage.c_str());
        }
        return attributeID;
    }

// Use Program
    void GL_cbtShaderProgram::UseProgram()
    {
        glUseProgram(m_ProgramID);
    }

// Texture
    void GL_cbtShaderProgram::SetTexture(cbtU32 _textureSlot, cbtTexture* _texture)
    {
        if (_texture)
        {
            _texture->Bind(_textureSlot);
        }
    }

// Float
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtF32 _value0)
    {
        glProgramUniform1f(m_ProgramID, GetUniformLocation(_uniformName), _value0);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1)
    {
        glProgramUniform2f(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2)
    {
        glProgramUniform3f(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1, _value2);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2,
            cbtF32 _value3)
    {
        glProgramUniform4f(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1, _value2, _value3);
    }

// Integer
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtS32 _value0)
    {
        glProgramUniform1i(m_ProgramID, GetUniformLocation(_uniformName), _value0);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1)
    {
        glProgramUniform2i(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2)
    {
        glProgramUniform3i(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1, _value2);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2,
            cbtS32 _value3)
    {
        glProgramUniform4i(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1, _value2, _value3);
    }

// Unsigned Integer
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtU32 _value0)
    {
        glProgramUniform1ui(m_ProgramID, GetUniformLocation(_uniformName), _value0);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1)
    {
        glProgramUniform2ui(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2)
    {
        glProgramUniform3ui(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1, _value2);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2,
            cbtU32 _value3)
    {
        glProgramUniform4ui(m_ProgramID, GetUniformLocation(_uniformName), _value0, _value1, _value2, _value3);
    }

// Boolean
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _value0)
    {
        glProgramUniform1i(m_ProgramID, GetUniformLocation(_uniformName), _value0 ? 1 : 0);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1)
    {
        glProgramUniform2i(m_ProgramID, GetUniformLocation(_uniformName), _value0 ? 1 : 0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1,
            cbtBool _value2)
    {
        glProgramUniform3i(m_ProgramID, GetUniformLocation(_uniformName), _value0 ? 1 : 0, _value1 ? 1 : 0,
                _value2 ? 1 : 0);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2,
            cbtBool _value3)
    {
        glProgramUniform4i(m_ProgramID, GetUniformLocation(_uniformName), _value0 ? 1 : 0, _value1 ? 1 : 0,
                _value2 ? 1 : 0, _value3 ? 1 : 0);
    }

// Matrix
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix2F& _value)
    {
        glProgramUniformMatrix2fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix3F& _value)
    {
        glProgramUniformMatrix3fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix4F& _value)
    {
        glProgramUniformMatrix4fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose,
            const cbtMatrix<cbtF32, 2, 3>& _value)
    {
        glProgramUniformMatrix2x3fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose,
            const cbtMatrix<cbtF32, 3, 2>& _value)
    {
        glProgramUniformMatrix3x2fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose,
            const cbtMatrix<cbtF32, 4, 2>& _value)
    {
        glProgramUniformMatrix4x2fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose,
            const cbtMatrix<cbtF32, 2, 4>& _value)
    {
        glProgramUniformMatrix2x4fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose,
            const cbtMatrix<cbtF32, 3, 4>& _value)
    {
        glProgramUniformMatrix3x4fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, cbtBool _transpose,
            const cbtMatrix<cbtF32, 4, 3>& _value)
    {
        glProgramUniformMatrix4x3fv(m_ProgramID, GetUniformLocation(_uniformName), 1, _transpose, _value[0]);
    }

// Color
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtColor& _color)
    {
        glProgramUniform4f(m_ProgramID, GetUniformLocation(_uniformName), _color.m_R, _color.m_G, _color.m_B,
                _color.m_A);
    }

// Vector2
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtVector2F& _value)
    {
        glProgramUniform2f(m_ProgramID, GetUniformLocation(_uniformName), _value.m_X, _value.m_Y);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtVector2U& _value)
    {
        glProgramUniform2ui(m_ProgramID, GetUniformLocation(_uniformName), _value.m_X, _value.m_Y);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtVector2S& _value)
    {
        glProgramUniform2i(m_ProgramID, GetUniformLocation(_uniformName), _value.m_X, _value.m_Y);
    }

// Vector3
    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtVector3F& _value)
    {
        glProgramUniform3f(m_ProgramID, GetUniformLocation(_uniformName), _value.m_X, _value.m_Y, _value.m_Z);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtVector3U& _value)
    {
        glProgramUniform3ui(m_ProgramID, GetUniformLocation(_uniformName), _value.m_X, _value.m_Y, _value.m_Z);
    }

    void GL_cbtShaderProgram::SetUniform(const cbtStr& _uniformName, const cbtVector3S& _value)
    {
        glProgramUniform3i(m_ProgramID, GetUniformLocation(_uniformName), _value.m_X, _value.m_Y, _value.m_Z);
    }

// Float
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtF32 _value0)
    {
        glProgramUniform1f(m_ProgramID, m_Uniforms[_uniformID], _value0);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1)
    {
        glProgramUniform2f(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2)
    {
        glProgramUniform3f(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1, _value2);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2,
            cbtF32 _value3)
    {
        glProgramUniform4f(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1, _value2, _value3);
    }

// Integer
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtS32 _value0)
    {
        glProgramUniform1i(m_ProgramID, m_Uniforms[_uniformID], _value0);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1)
    {
        glProgramUniform2i(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2)
    {
        glProgramUniform3i(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1, _value2);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2,
            cbtS32 _value3)
    {
        glProgramUniform4i(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1, _value2, _value3);
    }

// Unsigned Integer
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtU32 _value0)
    {
        glProgramUniform1ui(m_ProgramID, m_Uniforms[_uniformID], _value0);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1)
    {
        glProgramUniform2ui(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2)
    {
        glProgramUniform3ui(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1, _value2);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2,
            cbtU32 _value3)
    {
        glProgramUniform4ui(m_ProgramID, m_Uniforms[_uniformID], _value0, _value1, _value2, _value3);
    }

// Boolean
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _value0)
    {
        glProgramUniform1i(m_ProgramID, m_Uniforms[_uniformID], _value0 ? 1 : 0);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1)
    {
        glProgramUniform2i(m_ProgramID, m_Uniforms[_uniformID], _value0 ? 1 : 0, _value1);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1, cbtBool _value2)
    {
        glProgramUniform3i(m_ProgramID, m_Uniforms[_uniformID], _value0 ? 1 : 0, _value1 ? 1 : 0, _value2 ? 1 : 0);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1, cbtBool _value2,
            cbtBool _value3)
    {
        glProgramUniform4i(m_ProgramID, m_Uniforms[_uniformID], _value0 ? 1 : 0, _value1 ? 1 : 0, _value2 ? 1 : 0,
                _value3 ? 1 : 0);
    }

// Matrix
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix2F& _value)
    {
        glProgramUniformMatrix2fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix3F& _value)
    {
        glProgramUniformMatrix3fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix4F& _value)
    {
        glProgramUniformMatrix4fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 3>& _value)
    {
        glProgramUniformMatrix2x3fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 2>& _value)
    {
        glProgramUniformMatrix3x2fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 2>& _value)
    {
        glProgramUniformMatrix4x2fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 4>& _value)
    {
        glProgramUniformMatrix2x4fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 4>& _value)
    {
        glProgramUniformMatrix3x4fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 3>& _value)
    {
        glProgramUniformMatrix4x3fv(m_ProgramID, m_Uniforms[_uniformID], 1, _transpose, _value[0]);
    }

// Color
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtColor& _color)
    {
        glProgramUniform4f(m_ProgramID, m_Uniforms[_uniformID], _color.m_R, _color.m_G, _color.m_B, _color.m_A);
    }

// Vector2
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtVector2F& _value)
    {
        glProgramUniform2f(m_ProgramID, m_Uniforms[_uniformID], _value.m_X, _value.m_Y);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtVector2U& _value)
    {
        glProgramUniform2ui(m_ProgramID, m_Uniforms[_uniformID], _value.m_X, _value.m_Y);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtVector2S& _value)
    {
        glProgramUniform2i(m_ProgramID, m_Uniforms[_uniformID], _value.m_X, _value.m_Y);
    }

// Vector3
    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtVector3F& _value)
    {
        glProgramUniform3f(m_ProgramID, m_Uniforms[_uniformID], _value.m_X, _value.m_Y, _value.m_Z);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtVector3U& _value)
    {
        glProgramUniform3ui(m_ProgramID, m_Uniforms[_uniformID], _value.m_X, _value.m_Y, _value.m_Z);
    }

    void GL_cbtShaderProgram::SetUniform(cbtU32 _uniformID, const cbtVector3S& _value)
    {
        glProgramUniform3i(m_ProgramID, m_Uniforms[_uniformID], _value.m_X, _value.m_Y, _value.m_Z);
    }

NS_CBT_END

#endif // CBT_OPENGL