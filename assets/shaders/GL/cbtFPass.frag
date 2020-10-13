#version 460 core

// An alternative to the layout qualifier is to use glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name) or
// glBindFragDataLocationIndexed(GLuint program​, GLuint colorNumber​, GLuint index​, const char *name​) in the C++ code.
// By using glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name), it is not necessary to use the layout qualifier and vice-versa.
// However, if both are used and are in conflict, the layout qualifier in the vertex shader has priority.
layout (location = 0) out vec4 CBT_O_COMPOSITE;
layout (location = 1) out vec3 CBT_O_POSITION_CAMERA_SPACE;
layout (location = 2) out vec3 CBT_O_NORMAL_CAMERA_SPACE;

in VS_OUT
{
    vec3 CBT_V_POSITION_CAMERA_SPACE;
    vec3 CBT_V_NORMAL_CAMERA_SPACE;
    vec2 CBT_V_TEXCOORD;
    mat3 CBT_V_MATRIX_NORMAL;
    mat3 CBT_V_MATRIX_TBN;
};

// If a uniform is determined to have no effect on the final result, then they are removed. This will cause glGetUniformLocation to return -1.
// Texture Uniforms
uniform sampler2D CBT_TEXTURE_ALBEDO;
uniform sampler2D CBT_TEXTURE_NORMAL;
uniform sampler2D CBT_TEXTURE_SPECULAR;
uniform sampler2D CBT_TEXTURE_GLOSS;
uniform sampler2D CBT_TEXTURE_DISPLACEMENT;

uniform bool CBT_U_TEXTURE_ALBEDO_ENABLED;
uniform bool CBT_U_TEXTURE_NORMAL_ENABLED;
uniform bool CBT_U_TEXTURE_SPECULAR_ENABLED;
uniform bool CBT_U_TEXTURE_GLOSS_ENABLED;
uniform bool CBT_U_TEXTURE_DISPLACEMENT_ENABLED;

// Material Uniforms
uniform vec4 CBT_U_AMBIENT_COLOR;
uniform vec4 CBT_U_ALBEDO_COLOR;
uniform vec4 CBT_U_SPECULAR_COLOR;
uniform float CBT_U_GLOSS;

uniform float CBT_U_DISPLACEMENT_SCALE;
uniform int CBT_U_MIN_DISPLACEMENT_SAMPLE;
uniform int CBT_U_MAX_DISPLACEMENT_SAMPLE;

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

const float CBT_EPISILON = 0.001f;

vec2 ParallaxMapping()
{
    /* Get the direction of the camera to the fragment's surface.
    Right now we are in camera space. We need to convert into tangent space.
    Since vso_TBNMatrix converts from tangent space to camera space, the transpose (which is also the inverse) converts from camera space to tangent space. */
    vec3 camToFrag = normalize(transpose(CBT_V_MATRIX_TBN) * CBT_V_POSITION_CAMERA_SPACE); // Convert to tangent space.

    /* We are reading a height map, but we want to do our calculations based on depth instead since the results of a depth map looks better than a heightmap.
    By converting the height map to a depth map, it means that a height of 0.9 is a depth of 0.1, and a height of 0.4 is a depth of 0.6. */
    float depth = 1.0f - texture(CBT_TEXTURE_DISPLACEMENT, CBT_V_TEXCOORD).r;

    /* What is interesting to note here is the division of camToFrag.xy by camToFrag.z.
    As the camToFrag vector is normalized camToFrag.z will be somewhere in the range between 0.0 and 1.0.
    When camToFrag is largely parallel to the surface its z component is close to 0.0 and the division returns a much larger offset.
    compared to when camToFrag is largely perpendicular to the surface.
    So basically we're increasing the size of the offset in such a way that it offsets the texture coordinates at a larger scale when looking at a surface from
    an angle compared to when looking at it from the top which gives more realistic results at angles.
    Some people prefer to leave the division by camToFrag.z out of the equation as normal Parallax Mapping could produce undesirable results at certain angles.
    The technique is then called Parallax Mapping With Offset Limiting. Choosing which technique to pick is usually a matter of personal preference.
    Do take note that if we do divide by camToFrag.z, make sure to negate it. Since we are in tangent space, camToFrag.z is a negative number,
    and any division by it will negate our result. So we need to negate camToFrag.z to turn it into a positive number first */
    // vec2 uvDisplacement = camToFrag.xy * depth * CBT_U_DISPLACEMENT_SCALE; // Parallax Mapping With Offset Limiting
    vec2 uvDisplacement = (camToFrag.xy / -camToFrag.z) * depth * CBT_U_DISPLACEMENT_SCALE; // Parallax Mapping Without Offset Limiting

    return uvDisplacement;
}

vec2 ParallaxOcclusionMapping()
{
    /* Parallax Occlusion Mapping is based on the same principles as Steep Parallax Mapping,
    but instead of taking the texture coordinates of the first depth layer after a collision,
    we're going to linearly interpolate between the depth layer after and before the collision.
    We base the weight of the linear interpolation on how far the surface's height is from the depth layer's value of both layers.
    This is again an approximation, but significantly more accurate than Steep Parallax Mapping. */

    vec2 maxUVDisplacement = ParallaxMapping();

    /* Rather than take a fixed number of samples each time, we are going to make use of the fact that only from the sides do we need a higher number of samples.
    When view perpendicularly, we do not need as many samples as there is no need to displace anything when a fragment is viewed directly perpendicular.
    When the surface is viewed perpendicularly, the dot product betweem the surface normal and vertexToCam vector is 1, and when viewed sideways, the dor product is 0.
    By doing this, we can select how many samples we actually want to calculate. */
    float dotProduct = dot(CBT_V_NORMAL_CAMERA_SPACE, normalize(-CBT_V_POSITION_CAMERA_SPACE));
    int numSamples = int(mix(CBT_U_MAX_DISPLACEMENT_SAMPLE, CBT_U_MIN_DISPLACEMENT_SAMPLE, dotProduct));

    float currentLayerDepth = 0.0f;
    float currentTextureDepth = 0.0f;
    vec2 currentUVDisplacement = vec2(0.0f, 0.0f);
    
    float previousLayerDepth = 0.0f;
    float previousTextureDepth = 0.0f;
    vec2 previousUVDisplacement = vec2(0.0f, 0.0f);

    for (int i = 0; i < numSamples; ++i)
    {
        previousLayerDepth = currentLayerDepth;
        previousTextureDepth = currentTextureDepth;
        previousUVDisplacement = currentUVDisplacement;

        /* We do not have to multiply currentLayerDepth & currentTextureDepth by u_DisplacementScale as they would cancel each other out.
        Futhermore, doing so will mean we will have to declare another variable so that currentUVDisplacement's multiplication is not affected. */
        currentLayerDepth = float(i)/float(numSamples);
        currentUVDisplacement = currentLayerDepth * maxUVDisplacement;
        currentTextureDepth = 1.0f - texture(CBT_TEXTURE_DISPLACEMENT, CBT_V_TEXCOORD + currentUVDisplacement).r;

        // Interpolate between previousUVDisplacement and currentUVDisplacement.
        if (currentLayerDepth > currentTextureDepth)
        {
            // Currently we have overshot by this much.
            float excessDepth = currentLayerDepth - currentTextureDepth;
            // Previously we undershot by this much.
            float lackingDepth = previousTextureDepth - previousLayerDepth;

            // return  previousUVDisplacement + (currentUVDisplacement - previousUVDisplacement) * (lackingDepth / (lackingDepth + excessDepth));
            return mix(previousUVDisplacement, currentUVDisplacement, lackingDepth / (lackingDepth + excessDepth));
        }
    }

    return maxUVDisplacement;
}

vec2 GetTexCoord()
{
    if (!CBT_U_TEXTURE_DISPLACEMENT_ENABLED) { return CBT_V_TEXCOORD; }
    // return CBT_V_TEXCOORD + ParallaxMapping();
    // return CBT_V_TEXCOORD + SteepParallaxMapping();
    return CBT_V_TEXCOORD + ParallaxOcclusionMapping();
}

vec3 GetNormal(vec2 _texCoord)
{
    if (CBT_U_TEXTURE_NORMAL_ENABLED)
    {
        // Get the normal from the texture.
        vec3 normal = texture(CBT_TEXTURE_NORMAL, _texCoord).rgb;

        // Since Normals range from -1 to 1, it had to be halved and have 0.5 added to it to convert it to a 0 to 1 range which can be saved as an image.
        // This is to reverse the image value back into the -1 to 1 range.
        normal *= 2.0f;
        normal -= vec3(1.0f, 1.0f, 1.0f);
        normal = normalize(normal);

        // TBN Version
        // Convert the normal from tangent space to camera space.
        normal = normalize(CBT_V_MATRIX_TBN * normal);

        return normal;
    }

    return CBT_V_NORMAL_CAMERA_SPACE;
}

float GetGloss(vec2 _texCoord)
{
    if (CBT_U_TEXTURE_GLOSS_ENABLED)
    {
        return CBT_U_GLOSS * texture(CBT_TEXTURE_GLOSS, _texCoord).r;
    }
    return CBT_U_GLOSS;
}

vec4 GetSpecularColor(vec2 _texCoord)
{
    if (CBT_U_TEXTURE_SPECULAR_ENABLED)
    {
        return CBT_U_SPECULAR_COLOR * texture(CBT_TEXTURE_SPECULAR, _texCoord);
    }
    return CBT_U_SPECULAR_COLOR;
}

vec4 GetAlbedoColor(vec2 _texCoord)
{
    if (CBT_U_TEXTURE_ALBEDO_ENABLED)
    {
        return CBT_U_ALBEDO_COLOR * texture(CBT_TEXTURE_ALBEDO, _texCoord);
    }
    return CBT_U_ALBEDO_COLOR;
}

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
    vec2 texCoord = GetTexCoord();
    vec3 vertexNormalCameraSpace = GetNormal(texCoord);
    vec4 albedoColor = GetAlbedoColor(texCoord);

	if (albedoColor.a < CBT_EPISILON) { discard; }
	
    vec4 specularColor = GetSpecularColor(texCoord);
    float gloss = GetGloss(texCoord);

    vec4 lightDiffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec4 lightSpecular = vec4(0.3f, 0.3f, 0.f, 1.0f);

    /* Unlike deferred rendering where the geometry pass purely deals with the object color,
    For forward rendering, we need to set the alpha value to diffuseColor.a otherwise the light color and ambient color
    will overwrite the alpha of the diffuse color, causing issues with blending. */
    if (CBT_U_LIGHTING_ENABLED)
    {
        lightDiffuse = GetLightDiffuseColor(CBT_V_POSITION_CAMERA_SPACE, vertexNormalCameraSpace);
        lightSpecular = GetLightSpecularColor(CBT_V_POSITION_CAMERA_SPACE, vertexNormalCameraSpace, gloss);
    }

    CBT_O_POSITION_CAMERA_SPACE  = CBT_V_POSITION_CAMERA_SPACE;
    CBT_O_NORMAL_CAMERA_SPACE = vertexNormalCameraSpace;
    CBT_O_COMPOSITE = CBT_U_AMBIENT_COLOR + (albedoColor * lightDiffuse) + (specularColor * lightSpecular);
    CBT_O_COMPOSITE.a = albedoColor.a;
}