#pragma once

// Include CBT
#include "Rendering/Shader/CBTShaderProgram.h"

#ifdef CBT_OPENGL

// Include GL
#include <glew.h>
#include <gl/GL.h>

NS_CBT_BEGIN

/* Engine Built-in shader uniforms. (This means that your shader is expected to name their uniforms as such to receive the information from the engine.)
*************************************************************************Geometry Vertex Shader*************************************************************************
uniform mat4 u_ProjectionMatrix;
uniform vec2 u_TextureOffset;
uniform vec2 u_TextureScale;

*************************************************************************Geometry Fragment Shader*************************************************************************
// Geometry Pass Output
layout (location) out vec3 o_VertexPositionCameraSpace;
layout (location = 1) out vec3 o_VertexNormalCameraSpace;
layout (location = 2) out vec2 o_GlossinessAndSpecularity;
layout (location = 3) out vec4 o_AmbientColor;
layout (location = 4) out vec4 o_DiffuseColor;

// Texture Uniforms
const int CBTShaderProgram::MAX_TEXTURE_ALBEDO = 4; // (Must Match CBTShaderProgram::MAX_LIGHTS_PER_PASS In ShaderProgram.h)
uniform sampler2D u_TextureDiffuse[CBTShaderProgram::MAX_TEXTURE_ALBEDO];
uniform bool u_TextureDiffuseEnabled[CBTShaderProgram::MAX_TEXTURE_ALBEDO];

uniform sampler2D u_TextureNormal;
uniform bool u_TextureNormalEnabled;

uniform sampler2D u_TextureSpecular;
uniform bool u_TextureSpecularEnabled;

uniform sampler2D u_TextureGloss;
uniform bool u_TextureGlossEnabled;

uniform sampler2D u_TextureDisplacement;
uniform bool u_TextureDisplacementEnabled;

// Material Uniforms
uniform vec4 u_AmbientColor;
uniform vec4 u_DiffuseColor;
uniform float u_Glossiness;
uniform float u_Specularity;
uniform float u_DisplacementScale;
uniform int u_MinDisplacementSamples;
uniform int u_MaxDisplacementSamples;

*************************************************************************Light Fragment Shader*************************************************************************
// Light Pass Output
layout (location) out vec4 o_Composite;
layout (location = 1) out vec4 o_LightDiffuseColor;
layout (location = 2) out vec4 o_LightSpecularColor;

// From Geometry Pass To Light Pass
uniform sampler2D u_FBAPositionCameraSpace;
uniform sampler2D u_FBANormalCameraSpace;
uniform sampler2D u_FBAGlossinessAndSpecularity;
uniform sampler2D u_FBAAmbientColor;
uniform sampler2D u_FBADiffuseColor;

// From Light Pass To Light Pass
uniform sampler2D u_FBALightDiffuseColor;
uniform sampler2D u_FBALightSpecularColor;

// Lighting
struct Light
{
    bool m_Enabled;
    int m_Type;
    float m_Power;
    vec4 m_Color;

    vec3 m_PositionCameraSpace;
    vec3 m_DirectionCameraSpace;

    float m_AttenuationConstant;
    float m_AttenuationLinear;
    float m_AttenuationQuadratic;

    float m_SpotlightAngleInnerCosine;
    float m_SpotlightAngleOuterCosine;
};

const int MAX_LIGHTS = 8; // (Must Match CBTShaderProgram::MAX_LIGHTS_PER_PASS(Deferred Rendering) Or CBTShaderProgram::MAX_FORWARD_LIGHTS(Forward Rendering) In ShaderProgram.h / Forward Rendering has a hard limit of MAX_LIGHTS lights.)

const int LIGHT_POINT; // (Must Match Light::POINT In Light.h)
const int LIGHT_SPOT = 1; // (Must Match Light::SPOT In Light.h)
const int LIGHT_DIRECTIONAL = 2; // (Must Match Light::DIRECTIONAL In Light.h)

uniform Light u_Lights[MAX_LIGHTS];
uniform bool u_LightingEnabled;

*************************************************************************Forward Fragment Shader*************************************************************************
// Alpha
uniform float u_AlphaDiscardPixel;
uniform float u_AlphaDiscardPositionNormal;

*************************************************************************Skybox Fragment Shader*************************************************************************
uniform samplerCube u_TextureSkybox;
uniform bool u_TextureSkyboxEnabled;
uniform vec4 u_SkyboxColor;

*************************************************************************Post Process Fragment Shader*************************************************************************
// From Geometry Pass To Post Process Pass
uniform sampler2D u_FBAPositionCameraSpace;
uniform sampler2D u_FBANormalCameraSpace;
uniform sampler2D u_FBADepthStencil;

// From Light Pass To Post Process Pass
uniform sampler2D u_FBACompositeSource;

// From Post Process Pass To Post Process Pass
uniform sampler2D u_FBACompositePost;

uniform uint u_WindowWidth;
uniform uint u_WindowHeight;
uniform float u_NearPlane;
uniform float u_FarPlane;
*/

class GL_CBTShaderProgram : public CBTShaderProgram
{
protected:
    GLuint m_ProgramID;
    GLint m_Uniforms[CBT_NUM_SHADER_UNIFORM];

    virtual ~GL_CBTShaderProgram();

    GLuint CreateGLShader(GLenum _shaderType, const cbtStr& _shaderSource);
    GLint GetUniformLocation(const cbtStr& _uniformName) const;
    GLint GetAttributeLocation(const cbtStr& _attributeName) const;

public:
    GL_CBTShaderProgram(const cbtStr& _name, const std::vector<cbtStr>& _vertexShaderSources, const std::vector<cbtStr> _fragmentShaderSources);

    /// Use Program
    virtual void UseProgram();

    // Texture
    virtual void SetTexture(cbtU32 _textureSlot, CBTTexture* _texture);

    // Float
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0);
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1);
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2);
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2, cbtF32 _value3);

    // Integer
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0);
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1);
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2);
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2, cbtS32 _value3);

    // Unsigned Integer
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0);
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1);
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2);
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2, cbtU32 _value3);

    // Boolean
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2, cbtBool _value3);

    // Matrix (Updated)
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix2F& _value);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix3F& _value); 
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix4F& _value);

    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix<cbtF32, 3, 2>& _value);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix<cbtF32, 2, 3>& _value);

    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix<cbtF32, 2, 4>& _value);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix<cbtF32, 4, 2>& _value);

    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix<cbtF32, 4, 3>& _value);
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const CBTMatrix<cbtF32, 3, 4>& _value);

    // Color
    virtual void SetUniform(const cbtStr& _uniformName, const CBTColor& _value);

    // Vector2
    virtual void SetUniform(const cbtStr& _uniformName, const CBTVector2F& _value);
    virtual void SetUniform(const cbtStr& _uniformName, const CBTVector2U& _value);
    virtual void SetUniform(const cbtStr& _uniformName, const CBTVector2S& _value);

    // Vector3
    virtual void SetUniform(const cbtStr& _uniformName, const CBTVector3F& _value);
    virtual void SetUniform(const cbtStr& _uniformName, const CBTVector3U& _value);
    virtual void SetUniform(const cbtStr& _uniformName, const CBTVector3S& _value);

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
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix2F& _value);
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix3F& _value);
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix4F& _value);

    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix<cbtF32, 3, 2>& _value);
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix<cbtF32, 2, 3>& _value);

    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix<cbtF32, 2, 4>& _value);
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix<cbtF32, 4, 2>& _value);

    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix<cbtF32, 4, 3>& _value);
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const CBTMatrix<cbtF32, 3, 4>& _value);

    // Color
    virtual void SetUniform(cbtU32 _uniformID, const CBTColor& _value);

    // Vector2
    virtual void SetUniform(cbtU32 _uniformID, const CBTVector2F& _value);
    virtual void SetUniform(cbtU32 _uniformID, const CBTVector2U& _value);
    virtual void SetUniform(cbtU32 _uniformID, const CBTVector2S& _value);

    // Vector3
    virtual void SetUniform(cbtU32 _uniformID, const CBTVector3F& _value);
    virtual void SetUniform(cbtU32 _uniformID, const CBTVector3U& _value);
    virtual void SetUniform(cbtU32 _uniformID, const CBTVector3S& _value);
};

NS_CBT_END

#endif // CBT_OPENGL