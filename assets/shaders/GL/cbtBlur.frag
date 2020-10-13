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
uniform sampler2D CBT_PBUFFER_COMPOSITE;

// Custom Uniform(s)
uniform int u_BlurIntensity = 3;

void main()
{
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    for (int x = -u_BlurIntensity; x <= u_BlurIntensity; ++x)
    {
        for (int y = -u_BlurIntensity; y <= u_BlurIntensity; ++y)
        {
            color += texelFetch(CBT_PBUFFER_COMPOSITE, ivec2(gl_FragCoord) + ivec2(x,y), 0);
        }
    }

    int numPixels = (u_BlurIntensity + u_BlurIntensity + 1) * (u_BlurIntensity + u_BlurIntensity + 1);
    color.rgb /= float(numPixels);
    color.a = 1.0f;

    CBT_O_COMPOSITE = color;
}