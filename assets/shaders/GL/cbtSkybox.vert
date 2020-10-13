#version 450 core

// Updated Every Vertex
layout(location = 0) in vec3 CBT_A_POSITION;

// Updated Every Instance
layout(location = 4) in mat4 CBT_A_MATRIX_MV; // The max size of a vertex attribute is vec4. A mat4 is the size of 4 vec4s. Since this is a mat4, it takes up attribute 4, 5, 6 and 7.

// If a uniform is determined to have no effect on the final result, then they are removed. This will cause glGetUniformLocation to return -1.
uniform mat4 CBT_U_MATRIX_PROJECTION;

// Out(s)
out VS_OUT
{
    vec3 CBT_V_TEXCOORD; // Skybox has a cubemap texture, so it needs a vec3 texture coordinate.
};

void main()
{
    CBT_V_TEXCOORD = CBT_A_POSITION;
    gl_Position = CBT_U_MATRIX_PROJECTION * CBT_A_MATRIX_MV * vec4(CBT_A_POSITION, 1.0);
}