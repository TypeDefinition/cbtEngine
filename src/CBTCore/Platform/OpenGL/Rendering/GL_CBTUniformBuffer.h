#pragma once

// Include CBT
#include "Rendering/Buffer/CBTUniformBuffer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

class GL_CBTUniformBuffer : public CBTUniformBuffer
{
protected:
    GLuint m_UBOName;

    virtual ~GL_CBTUniformBuffer() { glDeleteBuffers(1, &m_UBOName); }

public:
    GL_CBTUniformBuffer() { glCreateBuffers(1, &m_UBOName); glNamedBufferData(m_UBOName, 0, NULL, GL_DYNAMIC_DRAW); }

    GLuint GetUBOName() const { return m_UBOName; }

    virtual void Bind(cbtU32 _bufferIndex) { glBindBufferBase(GL_UNIFORM_BUFFER, _bufferIndex, m_UBOName); }
    virtual void SetData(cbtU32 _dataSize, void* _data) { glNamedBufferData(m_UBOName, _dataSize, _data, GL_DYNAMIC_DRAW); }
    virtual void SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) { glNamedBufferSubData(m_UBOName, _offset, _dataSize, _data); }
};

NS_CBT_END

#endif // CBT_OPENGL