#pragma once

// Include CBT
#include "Rendering/Mesh/cbtVertex.h"
#include "Rendering/Texture/cbtTexture.h"
#include "Core/Math/cbtMatrix.h"
#include "Core/Math/cbtVector2.h"
#include "Core/Math/cbtVector3.h"
#include "Rendering/Color/cbtColor.h"

NS_CBT_BEGIN

#define CBT_MAX_LIGHTS 8

// Must use cbtS32. Binding a sampler2D uniform to an unsigned int texture index will result in failure.
enum cbtTextureSlot
{
    CBT_TEXTURE_SKYBOX,

    CBT_TEXTURE_ALBEDO,
    CBT_TEXTURE_NORMAL,
    CBT_TEXTURE_SPECULAR,
    CBT_TEXTURE_GLOSS,
    CBT_TEXTURE_DISPLACEMENT,

    CBT_GBUFFER_POSITION_CAMERA_SPACE,
    CBT_GBUFFER_NORMAL_CAMERA_SPACE,
    CBT_GBUFFER_AMBIENT_COLOR,
    CBT_GBUFFER_ALBEDO_COLOR,
    CBT_GBUFFER_SPECULAR_COLOR,
    CBT_GBUFFER_GLOSS,

    CBT_LBUFFER_COMPOSITE, ///< From Light Pass To Post Process Pass
    CBT_LBUFFER_LIGHT_DIFFUSE, ///< From Light Pass To Light Pass
    CBT_LBUFFER_LIGHT_SPECULAR, ///< From Light Pass To Light Pass

    CBT_FBUFFER_POSITION_CAMERA_SPACE,
    CBT_FBUFFER_NORMAL_CAMERA_SPACE,
    CBT_FBUFFER_DEPTH_STENCIL,

    CBT_PBUFFER_COMPOSITE, ///< From Post Process Pass To Post Process Pass

    CBT_NUM_TEXTURE_SLOT,
};

enum cbtUniformID
{
    CBT_U_MATRIX_PROJECTION,
    CBT_U_TEXTURE_SCALE,
    CBT_U_TEXTURE_OFFSET,

    CBT_U_TEXTURE_SKYBOX_ENABLED,
    CBT_U_SKYBOX_COLOR,

    CBT_U_TEXTURE_ALBEDO_ENABLED,
    CBT_U_TEXTURE_NORMAL_ENABLED,
    CBT_U_TEXTURE_SPECULAR_ENABLED,
    CBT_U_TEXTURE_GLOSS_ENABLED,
    CBT_U_TEXTURE_DISPLACEMENT_ENABLED,

    CBT_U_AMBIENT_COLOR,
    CBT_U_ALBEDO_COLOR,
    CBT_U_SPECULAR_COLOR,
    CBT_U_GLOSS,

    CBT_U_DISPLACEMENT_SCALE,
    CBT_U_MIN_DISPLACEMENT_SAMPLE,
    CBT_U_MAX_DISPLACEMENT_SAMPLE,

    CBT_U_LIGHTING_ENABLED,
    CBT_U_ACTIVE_LIGHTS,

    CBT_U_BUFFER_WIDTH,
    CBT_U_BUFFER_HEIGHT,

    CBT_U_NEAR_PLANE,
    CBT_U_FAR_PLANE,

    CBT_U_LIGHT_MODE0,
    CBT_U_LIGHT_POWER0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_MODE0,
    CBT_U_LIGHT_COLOR0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_POWER0,
    CBT_U_LIGHT_POSITION_CAMERA_SPACE0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_COLOR0,
    CBT_U_LIGHT_DIRECTION_CAMERA_SPACE0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_POSITION_CAMERA_SPACE0,
    CBT_U_LIGHT_ATTENUATION_CONSTANT0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_DIRECTION_CAMERA_SPACE0,
    CBT_U_LIGHT_ATTENUATION_LINEAR0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_ATTENUATION_CONSTANT0,
    CBT_U_LIGHT_ATTENUATION_QUADRATIC0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_ATTENUATION_LINEAR0,
    CBT_U_LIGHT_SPOTLIGHT_INNER_COSINE0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_ATTENUATION_QUADRATIC0,
    CBT_U_LIGHT_SPOTLIGHT_OUTER_COSINE0 = CBT_MAX_LIGHTS + CBT_U_LIGHT_SPOTLIGHT_INNER_COSINE0,

    CBT_NUM_SHADER_UNIFORM = CBT_MAX_LIGHTS + CBT_U_LIGHT_SPOTLIGHT_OUTER_COSINE0,
};

class cbtShaderProgram : public cbtManaged
{
protected:
    const cbtStr m_Name;

    virtual ~cbtShaderProgram() {}

public:
    cbtShaderProgram(const cbtStr& _name)
        : m_Name(_name)
    {}

    inline const cbtStr& GetName() const { return m_Name; }

    /// Use Program
    virtual void UseProgram() = 0;

    // Texture
    virtual void SetTexture(cbtU32 _textureSlot, cbtTexture* _texture) = 0;

    // Float
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2, cbtF32 _value3) = 0;

    // Integer
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2, cbtS32 _value3) = 0;

    // Unsigned Integer
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2, cbtU32 _value3) = 0;

    // Boolean
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _value0, cbtBool _value1, cbtBool _value2, cbtBool _value3) = 0;

    // Matrix
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix2F& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix3F& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix4F& _value) = 0;

    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 2>& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 3>& _value) = 0;

    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 4>& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 2>& _value) = 0;

    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 3>& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 4>& _value) = 0;

    // Color
    virtual void SetUniform(const cbtStr& _uniformName, const cbtColor& _value) = 0;

    // Vector2
    virtual void SetUniform(const cbtStr& _uniformName, const cbtVector2F& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, const cbtVector2U& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, const cbtVector2S& _value) = 0;

    // Vector3
    virtual void SetUniform(const cbtStr& _uniformName, const cbtVector3F& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, const cbtVector3U& _value) = 0;
    virtual void SetUniform(const cbtStr& _uniformName, const cbtVector3S& _value) = 0;

    // Float
    virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtF32 _value0, cbtF32 _value1, cbtF32 _value2, cbtF32 _value3) = 0;

    // Integer
    virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtS32 _value0, cbtS32 _value1, cbtS32 _value2, cbtS32 _value3) = 0;

    // Unsigned Integer
    virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtU32 _value0, cbtU32 _value1, cbtU32 _value2, cbtU32 _value3) = 0;

    // Boolean
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1, cbtBool _value2) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _value0, cbtBool _value1, cbtBool _value2, cbtBool _value3) = 0;

    // Matrix
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix2F& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix3F& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix4F& _value) = 0;

    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 2>& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 3>& _value) = 0;

    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 2, 4>& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 2>& _value) = 0;

    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 4, 3>& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, cbtBool _transpose, const cbtMatrix<cbtF32, 3, 4>& _value) = 0;

    // Color
    virtual void SetUniform(cbtU32 _uniformID, const cbtColor& _value) = 0;

    // Vector2
    virtual void SetUniform(cbtU32 _uniformID, const cbtVector2F& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, const cbtVector2U& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, const cbtVector2S& _value) = 0;

    // Vector3
    virtual void SetUniform(cbtU32 _uniformID, const cbtVector3F& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, const cbtVector3U& _value) = 0;
    virtual void SetUniform(cbtU32 _uniformID, const cbtVector3S& _value) = 0;

    static cbtShaderProgram* CreateShaderProgram(const cbtStr& _name, const std::vector<cbtStr>& _vertexShaderSources, const std::vector<cbtStr>& _fragmentShaderSources);
};

NS_CBT_END