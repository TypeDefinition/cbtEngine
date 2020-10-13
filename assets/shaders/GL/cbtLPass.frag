#version 460 core

// An alternative to the layout qualifier is to use glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name) or
// glBindFragDataLocationIndexed(GLuint program​, GLuint colorNumber​, GLuint index​, const char *name​) in the C++ code.
// By using glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name), it is not necessary to use the layout qualifier and vice-versa.
// However, if both are used and are in conflict, the layout qualifier in the vertex shader has priority.
layout (location = 0) out vec4 CBT_O_COMPOSITE;
layout (location = 1) out vec4 CBT_O_LIGHT_DIFFUSE;
layout (location = 2) out vec4 CBT_O_LIGHT_SPECULAR;

in VS_OUT
{
    vec2 CBT_V_TEXCOORD;
};

// From Geometry Buffer To Light Buffer
uniform sampler2D CBT_GBUFFER_POSITION_CAMERA_SPACE;
uniform sampler2D CBT_GBUFFER_NORMAL_CAMERA_SPACE;
uniform sampler2D CBT_GBUFFER_AMBIENT_COLOR;
uniform sampler2D CBT_GBUFFER_ALBEDO_COLOR;
uniform sampler2D CBT_GBUFFER_SPECULAR_COLOR;
uniform sampler2D CBT_GBUFFER_GLOSS;

// From Light Buffer To Light Buffer
uniform sampler2D CBT_LBUFFER_LIGHT_DIFFUSE;
uniform sampler2D CBT_LBUFFER_LIGHT_SPECULAR;

const int CBT_MAX_LIGHTS = 8;

// Light Mode
const int CBT_LIGHT_POINT = 0;
const int CBT_LIGHT_SPOT = 1;
const int CBT_LIGHT_DIRECTIONAL = 2;

uniform int CBT_U_ACTIVE_LIGHTS;
uniform bool CBT_U_LIGHTING_ENABLED;

struct CBTLight
{
    int m_Mode;
    float m_Power;
    vec4 m_Color;

    vec3 m_PositionCameraSpace;
    vec3 m_DirectionCameraSpace;

    float m_AttenuationConstant;
    float m_AttenuationLinear;
    float m_AttenuationQuadratic;
    
    float m_SpotlightInnerCosine;
    float m_SpotlightOuterCosine;
};

uniform CBTLight CBT_U_LIGHT[CBT_MAX_LIGHTS];

// Diffuse Lighting
vec3 GetVertexToLight(int _lightIndex, vec3 _vertexPositionCameraSpace)
{
    // LIGHT_DIRECTIONAL
    if (CBT_U_LIGHT[_lightIndex].m_Mode == CBT_LIGHT_DIRECTIONAL) { return normalize(-CBT_U_LIGHT[_lightIndex].m_DirectionCameraSpace); }

    // LIGHT_POINT & LIGHT_SPOT
    return normalize(CBT_U_LIGHT[_lightIndex].m_PositionCameraSpace - _vertexPositionCameraSpace);
}

float GetSpotlightEffect(int _lightIndex, vec3 _vertexPositionCameraSpace)
{
    vec3 lightToVertex = normalize(_vertexPositionCameraSpace - CBT_U_LIGHT[_lightIndex].m_PositionCameraSpace);
    float vertexAngleCosine = dot(lightToVertex, CBT_U_LIGHT[_lightIndex].m_DirectionCameraSpace);

    /* As long as the angle between the light direction and lightToVertex is within the inner cosine, the light is at full power.
    The light power will falloff as it approaches the outer cosine. */
    return clamp((vertexAngleCosine - CBT_U_LIGHT[_lightIndex].m_SpotlightOuterCosine) / (CBT_U_LIGHT[_lightIndex].m_SpotlightInnerCosine - CBT_U_LIGHT[_lightIndex].m_SpotlightOuterCosine), 0.0f, 1.0f);
}

float GetLightAttenuation(int _lightIndex, vec3 _vertexPositionCameraSpace)
{
    float distance = length(CBT_U_LIGHT[_lightIndex].m_PositionCameraSpace - _vertexPositionCameraSpace);
    return CBT_U_LIGHT[_lightIndex].m_Power / max(1.0f, CBT_U_LIGHT[_lightIndex].m_AttenuationConstant + (CBT_U_LIGHT[_lightIndex].m_AttenuationLinear * distance) + (CBT_U_LIGHT[_lightIndex].m_AttenuationQuadratic * distance * distance));
}

float GetDiffuseIntensity(int _lightIndex, vec3 _vertexPositionCameraSpace, vec3 _vertexNormalCameraSpace)
{
    return clamp(dot(GetVertexToLight(_lightIndex, _vertexPositionCameraSpace), _vertexNormalCameraSpace), 0.0f, 1.0f);
}

vec4 GetLightDiffuseColor(vec3 _vertexPositionCameraSpace, vec3 _vertexNormalCameraSpace)
{
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (int i = 0; i < CBT_U_ACTIVE_LIGHTS; ++i)
    {
        switch(CBT_U_LIGHT[i].m_Mode)
        {
            case CBT_LIGHT_POINT:
                color +=
                    CBT_U_LIGHT[i].m_Color *
                    GetDiffuseIntensity(i, _vertexPositionCameraSpace, _vertexNormalCameraSpace) *
                    GetLightAttenuation(i, _vertexPositionCameraSpace);
            break;
            case CBT_LIGHT_SPOT:
                color +=
                    CBT_U_LIGHT[i].m_Color *
                    GetDiffuseIntensity(i, _vertexPositionCameraSpace, _vertexNormalCameraSpace) *
                    GetLightAttenuation(i, _vertexPositionCameraSpace) *
                    GetSpotlightEffect(i, _vertexPositionCameraSpace);
            break;
            case CBT_LIGHT_DIRECTIONAL:
                color +=
                    CBT_U_LIGHT[i].m_Color *
                    GetDiffuseIntensity(i, _vertexPositionCameraSpace, _vertexNormalCameraSpace) *
                    CBT_U_LIGHT[i].m_Power;
            break;
            default:
            break;
        }
    }
    
    return color;
}

float GetSpecularIntensity(int _lightIndex, vec3 _vertexPositionCameraSpace, vec3 _vertexNormalCameraSpace, float _gloss)
{
    /*
    To get out specular intensity, we need the dot product of the reflection of the lightToVertex vector and the vertexToCamera vector.

    The reflect function expects the first vector to point from the light source towards the fragment's position,
    but vertexToLight is currently pointing the other way around: from the fragment towards the light source.
    To make sure we get the correct reflect vector we reverse its direction by negating vertexToLight.
    The second argument expects a normal vector so we supply the normalized norm vector.

    But instead of doing that, the other way is to simply leave vertexToLight the way it is, and dot product it
    with the cameraToVertex vector instead. To understand why this works, the reflect(genType I, genType N) function
    works by returning the result of I - 2*dot(N, I) * N. Draw this on a piece of paper with a vector and a normal and see how it reflects.
    */

    vec3 specularDirection = reflect(GetVertexToLight(_lightIndex, _vertexPositionCameraSpace), _vertexNormalCameraSpace);
    vec3 viewDirection = normalize(_vertexPositionCameraSpace);

    return pow(max(dot(specularDirection, viewDirection), 0.0f), _gloss);
}

vec4 GetLightSpecularColor(vec3 _vertexPositionCameraSpace, vec3 _vertexNormalCameraSpace, float _gloss)
{
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < CBT_U_ACTIVE_LIGHTS; ++i)
    {
        switch(CBT_U_LIGHT[i].m_Mode)
        {
            case CBT_LIGHT_POINT:
                color +=
                    GetSpecularIntensity(i, _vertexPositionCameraSpace, _vertexNormalCameraSpace, _gloss) *
                    GetLightAttenuation(i, _vertexPositionCameraSpace) *
                    CBT_U_LIGHT[i].m_Color;
            break;
            case CBT_LIGHT_SPOT:
                color +=
                    GetSpecularIntensity(i, _vertexPositionCameraSpace, _vertexNormalCameraSpace, _gloss) *
                    GetLightAttenuation(i, _vertexPositionCameraSpace) *
                    GetSpotlightEffect(i, _vertexPositionCameraSpace) *
                    CBT_U_LIGHT[i].m_Color;
            break;
            case CBT_LIGHT_DIRECTIONAL:
                color +=
                    GetSpecularIntensity(i, _vertexPositionCameraSpace, _vertexNormalCameraSpace, _gloss) *
                    CBT_U_LIGHT[i].m_Power *
                    CBT_U_LIGHT[i].m_Color;
            break;
            default:
            break;
        }
    }

    return color;
}

void main()
{
    /*Since we can only deal with MAX_LIGHTS in a single pass, we need to output our results into CBT_O_LIGHT_DIFFUSE & CBT_O_LIGHT_SPECULAR,
    and let the next pass continue handling the next 8 lights. If we also add the results from the previous passes. If this is the first pass,
    CBT_LBUFFER_LIGHT_DIFFUSE and CBT_LBUFFER_LIGHT_SPECULAR should be empty (black). */
    vec3 vertexPositionCameraSpace = texture(CBT_GBUFFER_POSITION_CAMERA_SPACE, CBT_V_TEXCOORD).rgb;
    vec3 vertexNormalCameraSpace = texture(CBT_GBUFFER_NORMAL_CAMERA_SPACE, CBT_V_TEXCOORD).rgb;

    vec4 ambientColor = texture(CBT_GBUFFER_AMBIENT_COLOR, CBT_V_TEXCOORD);
    vec4 albedoColor = texture(CBT_GBUFFER_ALBEDO_COLOR, CBT_V_TEXCOORD);
    vec4 specularColor = texture(CBT_GBUFFER_SPECULAR_COLOR, CBT_V_TEXCOORD);
    float gloss = texture(CBT_GBUFFER_GLOSS, CBT_V_TEXCOORD).r;

    vec4 lightDiffuse = texture(CBT_LBUFFER_LIGHT_DIFFUSE, CBT_V_TEXCOORD);
    vec4 lightSpecular = texture(CBT_LBUFFER_LIGHT_SPECULAR, CBT_V_TEXCOORD);

    if (CBT_U_LIGHTING_ENABLED)
    {
        CBT_O_LIGHT_DIFFUSE = lightDiffuse + GetLightDiffuseColor(vertexPositionCameraSpace, vertexNormalCameraSpace);
        CBT_O_LIGHT_SPECULAR = lightSpecular + GetLightSpecularColor(vertexPositionCameraSpace, vertexNormalCameraSpace, gloss);
    }
    else
    {
        CBT_O_LIGHT_DIFFUSE = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        CBT_O_LIGHT_SPECULAR = vec4(0.3f, 0.3f, 0.f, 1.0f);
    }

    CBT_O_COMPOSITE = ambientColor + (albedoColor * CBT_O_LIGHT_DIFFUSE) + (specularColor * CBT_O_LIGHT_SPECULAR);
}