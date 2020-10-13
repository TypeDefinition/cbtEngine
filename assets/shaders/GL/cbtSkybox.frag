#version 450 core

// Out(s)
layout (location = 0) out vec4 CBT_O_SKYBOX_COLOR;

// In(s)
in VS_OUT
{
    vec3 CBT_V_TEXCOORD; // Skybox has a cubemap texture, so it needs a vec3 texture coordinate.
};

// Uniform(s)
uniform samplerCube CBT_TEXTURE_SKYBOX;
uniform bool CBT_U_TEXTURE_SKYBOX_ENABLED;
uniform vec4 CBT_U_SKYBOX_COLOR;

void main()
{
    CBT_O_SKYBOX_COLOR = CBT_U_SKYBOX_COLOR;
    if (CBT_U_TEXTURE_SKYBOX_ENABLED)
    {
        CBT_O_SKYBOX_COLOR *=  texture(CBT_TEXTURE_SKYBOX, CBT_V_TEXCOORD);
    }
}