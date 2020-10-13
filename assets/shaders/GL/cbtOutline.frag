#version 460 core

// An alternative to the layout qualifier is to use glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name) or
// glBindFragDataLocationIndexed(GLuint program​, GLuint colorNumber​, GLuint index​, const char *name​) in the C++ code.
// By using glBindFragDataLocation(GLuint program, GLuint colorNumber, const char * name), it is not necessary to use the layout qualifier and vice-versa.
// However, if both are used and are in conflict, the layout qualifier in the vertex shader has priority.
layout (location = 0) out vec4 CBT_O_COMPOSITE;

in VS_OUT
{
    vec2 CBT_V_TEXCOORD;
};

uniform sampler2D CBT_FBUFFER_POSITION_CAMERA_SPACE;
uniform sampler2D CBT_FBUFFER_NORMAL_CAMERA_SPACE;
uniform sampler2D CBT_FBUFFER_DEPTH_STENCIL;
uniform sampler2D CBT_PBUFFER_COMPOSITE;

uniform int CBT_U_BUFFER_WIDTH;
uniform int CBT_U_BUFFER_HEIGHT;
uniform int CBT_U_NEAR_PLANE;
uniform int CBT_U_FAR_PLANE;

// Custom Uniform(s)
uniform float u_DepthThreshold = 0.1f;
uniform float u_NormalThreshold = 1.0f;
uniform vec4 u_LineColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

// Local Constant(s)
const float c_KernalVertical[9] = float[](1.0f, 0.0f, -1.0f, 2.0f, 0.0f, -2.0f, 1.0f, 0.0f, -1.0f); // Sobel Edge Detection Kernal
const float c_KernalHorizontal[9] = float[](1.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, -2.0f, -1.0f); // Sobel Edge Detection Kernal

float LinearizedDepth(float _depth)
{
    float ndcDepth = _depth * 2.0f -1.0f; // Convert Depth to NDC space. (From 0 to 1 Range to -1 to 1 Range)
    return (2.0 * CBT_U_NEAR_PLANE) / (CBT_U_FAR_PLANE + CBT_U_NEAR_PLANE - ndcDepth * (CBT_U_FAR_PLANE - CBT_U_NEAR_PLANE)); // Convert the depth to the CBT_U_NEAR_PLANE to CBT_U_FAR_PLANE range.
}

/* We don't need this function now, but this is just a good to know.
Convert From -1 to 1 Range to 0 to 1 Range. Opposite of LinearizedDepth but without the conversion to the CBT_U_NEAR_PLANE to CBT_U_FAR_PLANE Range. */
float NormalizedDepth(float _depth)
{
    return (_depth - CBT_U_NEAR_PLANE) / (CBT_U_FAR_PLANE - CBT_U_NEAR_PLANE);
}

bool DepthCheck()
{
    float deltaVertical = 0.0f;
    float deltaHorizontal = 0.0f;
    float depth = LinearizedDepth(texelFetch(CBT_FBUFFER_DEPTH_STENCIL, ivec2(gl_FragCoord), 0).r); // To get the depth from the Depth24_Stencil8 Buffer, use r or x.

    int loopIteration = 0;
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float neighbourDepth  = LinearizedDepth(texelFetch(CBT_FBUFFER_DEPTH_STENCIL, ivec2(gl_FragCoord) + ivec2(x,y), 0).r);
            deltaVertical += (neighbourDepth - depth) * c_KernalVertical[loopIteration];
            deltaHorizontal += (neighbourDepth - depth) * c_KernalHorizontal[loopIteration];

            ++loopIteration;
        }
    }

    float gradientSquared = (deltaVertical * deltaVertical) + (deltaHorizontal * deltaHorizontal);
    return gradientSquared > (u_DepthThreshold * u_DepthThreshold);
}

bool NormalCheck()
{
    float deltaVertical = 0.0f;
    float deltaHorizontal = 0.0f;
    vec3 normal = texelFetch(CBT_FBUFFER_NORMAL_CAMERA_SPACE, ivec2(gl_FragCoord), 0).rgb;
    
    int loopIteration = 0;
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            vec3 neighbourNormal  = texelFetch(CBT_FBUFFER_NORMAL_CAMERA_SPACE, ivec2(gl_FragCoord) + ivec2(x,y), 0).rgb;

            deltaVertical += dot(normal, neighbourNormal) * c_KernalVertical[loopIteration];
            deltaHorizontal += dot(normal, neighbourNormal) * c_KernalHorizontal[loopIteration];

            ++loopIteration;
        }
    }

    float gradientSquared = (deltaVertical * deltaVertical) + (deltaHorizontal * deltaHorizontal);
    return gradientSquared > (u_NormalThreshold * u_NormalThreshold);
}

void main()
{
    if (NormalCheck() || DepthCheck())
    {
        CBT_O_COMPOSITE = u_LineColor;
    }
    else
    {
        CBT_O_COMPOSITE = texture(CBT_PBUFFER_COMPOSITE, CBT_V_TEXCOORD);
    }
}
