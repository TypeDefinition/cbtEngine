#version 460 core

// The invariant qualifier instructs the compiler and linked to ignore expressions and functions that are not directly related to the computation of the output.
// In this section, variance refers to the possibility of getting different values from the same expression in different programs.
// For example, say two vertex shaders, in different programs, each set gl_Position with the same expression in both shaders,
// and the input values into that expression are the same when both shaders run. It is possible, due to independent compilation of the two shaders,
// that the values assigned to gl_Position are not exactly the same when the two shaders run. In this example, this can cause problems with alignment
// of geometry in a multi-pass algorithm. In general, such variance between shaders is allowed. When such variance does not exist for a particular output variable,
// that variable is said to be invariant.
// invariant gl_Position;

// An alternative to the layout qualifier is to use glBindAttribLocation(GLuint program​, GLuint index​, const GLchar *name​) in the C++ code.
// By using glBindAttribLocation(GLuint program​, GLuint index​, const GLchar *name​), it is not necessary to use the layout qualifier and vice-versa.
// However, if both are used and are in conflict, the layout qualifier in the vertex shader has priority.

// Updated Every Vertex
layout(location = 0) in vec3 CBT_A_POSITION;
layout(location = 1) in vec3 CBT_A_NORMAL;
layout(location = 2) in vec2 CBT_A_TEXCOORD;
layout(location = 3) in vec3 CBT_A_TANGENT;

// Updated Every Instance
layout(location = 4) in mat4 CBT_A_MATRIX_MV; // The max size of a vertex attribute is vec4. A mat4 is the size of 4 vec4s. Since this is a mat4, it takes up attribute 4, 5, 6 and 7.
layout(location = 8) in mat3 CBT_A_MATRIX_NORMAL; // The max size of a vertex attribute is vec4. A mat3 is the size of 3 vec3s. Since this is a mat3, it takes up attribute 8, 9, and 10.

out VS_OUT
{
    vec3 CBT_V_POSITION_CAMERA_SPACE;
    vec3 CBT_V_NORMAL_CAMERA_SPACE;
    vec2 CBT_V_TEXCOORD;
    mat3 CBT_V_MATRIX_NORMAL;
    mat3 CBT_V_MATRIX_TBN;
};

// If a uniform is determined to have no effect on the final result, then they are removed.
// This will cause glGetUniformLocation to return -1.
uniform mat4 CBT_U_MATRIX_PROJECTION;
uniform vec2 CBT_U_TEXTURE_OFFSET;
uniform vec2 CBT_U_TEXTURE_SCALE;

void main()
{
    CBT_V_POSITION_CAMERA_SPACE = (CBT_A_MATRIX_MV * vec4(CBT_A_POSITION, 1.0f)).xyz;
    CBT_V_NORMAL_CAMERA_SPACE = normalize(CBT_A_MATRIX_NORMAL *  CBT_A_NORMAL);
    CBT_V_TEXCOORD = (CBT_A_TEXCOORD + CBT_U_TEXTURE_OFFSET) * CBT_U_TEXTURE_SCALE;
    CBT_V_MATRIX_NORMAL = CBT_A_MATRIX_NORMAL;

    // This is the Gramm-Schmidt process. dot(Tangent, Normal) gives us the length of the projection of the tangent along the normal vector.
    // The product of this length by the normal itself is the component of the tangent along the normal.
    // Substract that from the tangent and we get a new vector which is perpendicular to the normal.
    // This is our new tangent (just remember to normalize it as well...).
    vec3 tangent = normalize(CBT_A_TANGENT - dot(CBT_A_TANGENT, CBT_A_NORMAL) * CBT_A_NORMAL);
    // A cross product between the tangent and the normal gives us the bitangent. 
    vec3 bitangent = normalize(cross(CBT_A_NORMAL, tangent));

    /* So, at this point you might be asking, "If we want to convert a vector from one space to another, we need to dot product it with all 3 axis of the new space.
    So if we take CBT_V_MATRIX_TBN and multiply it by a vec3 right now, we aren't actually doing a dot product with all 3 axis. We need to transpose CBT_V_MATRIX_TBN in order to achieve that."
    Ah, but you see, the transpose of CBT_V_MATRIX_TBN converts a point TO tangent space. But what we want is to actually convert FROM tangent space. And for orthoganal matrices, their transpose is also
    their inverse. Which is why CBT_V_MATRIX_TBN is currently the tranpose of what it is now. Because we want it to do the opposite of converting to tangent space. We want to convert FROM tangent space
    to view space. Later on in the fragment shader you will see a point where we transpose CBT_V_MATRIX_TBN when we want to convert TO tangent space. So at the end of the day I guess it kinda is cause
    we named CBT_V_MATRIX_TBN poorly. We should actually name it CBT_V_MATRIX_TBNInverse. But I've already typed out the code and this entire freaking passage. So we'll just keep the name. And if you
    are wondering why I typed this whole message instead of changing the name of CBT_V_MATRIX_TBN, it's cause I only thought of the name change as I am typing this out. */
    // TBN (Technically the inverse of a TBN Matrix. Converts from tangent space to view space.)
    CBT_V_MATRIX_TBN[0] = normalize(CBT_A_MATRIX_NORMAL *  tangent);
    CBT_V_MATRIX_TBN[1] = normalize(CBT_A_MATRIX_NORMAL *  bitangent);
    CBT_V_MATRIX_TBN[2] = CBT_V_NORMAL_CAMERA_SPACE;

    gl_Position = CBT_U_MATRIX_PROJECTION * CBT_A_MATRIX_MV * vec4(CBT_A_POSITION, 1.0f);
}