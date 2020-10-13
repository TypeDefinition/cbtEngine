#version 460 core

// An alternative to the layout qualifier is to use glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name) or
// glBindFragDataLocationIndexed(GLuint program​, GLuint colorNumber​, GLuint index​, const char *name​) in the C++ code.
// By using glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name), it is not necessary to use the layout qualifier and vice-versa.
// However, if both are used and are in conflict, the layout qualifier in the vertex shader has priority.
layout (location = 0) out vec3 CBT_O_POSITION_CAMERA_SPACE;
layout (location = 1) out vec3 CBT_O_NORMAL_CAMERA_SPACE;
layout (location = 2) out vec4 CBT_O_AMBIENT_COLOR;
layout (location = 3) out vec4 CBT_O_ALBEDO_COLOR;
layout (location = 4) out vec4 CBT_O_SPECULAR_COLOR;
layout (location = 5) out float CBT_O_GLOSS;

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

// I tried writing comments to explain this but it cannot beat a single image from [https://learnopengl.com/Advanced-Lighting/Parallax-Mapping].
vec2 SteepParallaxMapping()
{
    /* Steep Parallax Mapping is an extension on top of Parallax Mapping in that it uses the same principles,
    but instead of 1 sample it takes multiple samples to better pinpoint camToFrag to the point we should be looking at.
    This gives much better results, even with steep height changes as the accuracy of the technique is improved by the number of samples.
    The general idea of Steep Parallax Mapping is that it divides the total depth range into multiple layers of the same height/depth.
    For each of these layers we sample the depthmap shifting the texture coordinates along the direction of -camToFrag until we find a sampled depth value that is below the depth value of the current layer. */

    /* The basic idea is that we are going to divide our offset into smaller chunks, and check at each step if we've already overshot the depth. */
    vec2 maxUVDisplacement = ParallaxMapping();

    /* Rather than take a fixed number of samples each time, we are going to make use of the fact that only from the sides do we need a higher number of samples.
    When view perpendicularly, we do not need as many samples as there is no need to displace anything when a fragment is viewed directly perpendicular.
    When the surface is viewed perpendicularly, the dot product betweem the surface normal and vertexToCam vector is 1, and when viewed sideways, the dor product is 0.
    By doing this, we can select how many samples we actually want to calculate. */
    float dotProduct = dot(CBT_V_NORMAL_CAMERA_SPACE, normalize(-CBT_V_POSITION_CAMERA_SPACE));
    int numSamples = int(mix(CBT_U_MAX_DISPLACEMENT_SAMPLE, CBT_U_MIN_DISPLACEMENT_SAMPLE, dotProduct));

    for (int i = 0; i < numSamples; ++i)
    {
        /* We do not have to multiply layerDepth & textureDepth by u_DisplacementScale as they would cancel each other out.
        Futhermore, doing so will mean we will have to declare another variable so that uvDisplacement's multiplication is not affected. */
        float layerDepth = float(i)/float(numSamples);
        vec2 uvDisplacement = layerDepth * maxUVDisplacement;
        float textureDepth = 1.0f - texture(CBT_TEXTURE_DISPLACEMENT, CBT_V_TEXCOORD + uvDisplacement).r;
        if (layerDepth > textureDepth)
        {
            return uvDisplacement;
        }
    }

    return maxUVDisplacement;
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

void main()
{
    vec2 texCoord = GetTexCoord();
    CBT_O_POSITION_CAMERA_SPACE = CBT_V_POSITION_CAMERA_SPACE;
    CBT_O_NORMAL_CAMERA_SPACE = GetNormal(texCoord);
    CBT_O_AMBIENT_COLOR = CBT_U_AMBIENT_COLOR;
    CBT_O_ALBEDO_COLOR = GetAlbedoColor(texCoord);
    CBT_O_SPECULAR_COLOR = GetSpecularColor(texCoord);
    CBT_O_GLOSS = GetGloss(texCoord);
}