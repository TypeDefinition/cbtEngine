// Include CBT
#include "GL_CBTElementBuffer.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

CBTElementBuffer* CBTElementBuffer::CreateEBO(void* _data, cbtU32 _byteSize)
{
    return new GL_CBTElementBuffer(_data, _byteSize);
}

GL_CBTElementBuffer::GL_CBTElementBuffer(void* _data, cbtU32 _byteSize)
    : CBTElementBuffer(_data, _byteSize)
{
    glCreateBuffers(1, &this->m_EBOName);
    glNamedBufferData(this->m_EBOName, _byteSize, _data, GL_STATIC_DRAW);
}

GL_CBTElementBuffer::~GL_CBTElementBuffer()
{
    glDeleteBuffers(1, &this->m_EBOName);
}

void GL_CBTElementBuffer::Bind()
{
    // Must be bound only after VAO has been bound as this function modifies the VAO state. (https://www.khronos.org/opengl/wiki/Vertex_Specification, Vertex Array Object Section)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBOName);
}

void GL_CBTElementBuffer::SetSubData(void* _data, cbtU32 _byteSize, cbtU32 _byteOffset)
{
    glNamedBufferSubData(m_EBOName, _byteOffset, _byteSize, _data);
}

NS_CBT_END

#endif // CBT_OPENGL