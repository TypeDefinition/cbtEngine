// Include
#include "GL_CBTVertexBuffer.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

CBTVertexBuffer* CBTVertexBuffer::CreateVBO(const CBTBufferLayout& _layout, CBTBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize, void* _data)
{
    return new GL_CBTVertexBuffer(_layout, _usage, _divisor, _bufferSize, _data);
}

GL_CBTVertexBuffer::GL_CBTVertexBuffer(const CBTBufferLayout& _layout, CBTBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize, void* _data)
    : CBTVertexBuffer(_layout, _usage, _divisor)
{
    glCreateBuffers(1, &m_VBOName);
    // Add the vertex data into the buffer specified by m_VBOName.
    glNamedBufferData(m_VBOName, _bufferSize, _data, ToGLBufferUsage(m_BufferUsage));
}

GL_CBTVertexBuffer::~GL_CBTVertexBuffer() { glDeleteBuffers(1, &this->m_VBOName); }

void GL_CBTVertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOName); }

void GL_CBTVertexBuffer::SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) { glNamedBufferSubData(this->m_VBOName, _offset, _dataSize, _data); }

void GL_CBTVertexBuffer::SetData(cbtU32 _dataSize, void* _data) { glNamedBufferData(this->m_VBOName, _dataSize, _data, ToGLBufferUsage(m_BufferUsage)); }

NS_CBT_END

#endif // CBT_OPENGL