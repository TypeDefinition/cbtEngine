#version 460 core

// An alternative to the layout qualifier is to use glBindAttribLocation(GLuint program​, GLuint index​, const GLchar *name​) in the C++ code.
// By using glBindAttribLocation(GLuint program​, GLuint index​, const GLchar *name​), it is not necessary to use the layout qualifier and vice-versa.
// However, if both are used and are in conflict, the layout qualifier in the vertex shader has priority.

// Updated Every Vertex
layout(location = 0) in vec3 CBT_A_POSITION;
layout(location = 1) in vec3 CBT_A_NORMAL;
layout(location = 2) in vec2 CBT_A_TEXCOORD;
layout(location = 3) in vec3 CBT_A_TANGENT;

out VS_OUT
{
    vec2 CBT_V_TEXCOORD;
};

void main()
{
    CBT_V_TEXCOORD = CBT_A_TEXCOORD;
    gl_Position = vec4(CBT_A_POSITION, 1.0f);
}