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

void main()
{
    vec4 color = texture(CBT_PBUFFER_COMPOSITE, CBT_V_TEXCOORD);
    color.r = 1.0f - color.r; color.g = 1.0f - color.g; color.b = 1.0f - color.b;
    CBT_O_COMPOSITE = color;
}