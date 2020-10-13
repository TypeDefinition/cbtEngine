// Include
#include "GL_cbtVertexBuffer.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

cbtVertexBuffer* cbtVertexBuffer::CreateVBO(const cbtBufferLayout& _layout, cbtBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize, void* _data)
{
    return new GL_cbtVertexBuffer(_layout, _usage, _divisor, _bufferSize, _data);
}

GL_cbtVertexBuffer::GL_cbtVertexBuffer(const cbtBufferLayout& _layout, cbtBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize, void* _data)
    : cbtVertexBuffer(_layout, _usage, _divisor)
{
    glCreateBuffers(1, &m_VBOName);
    // Add the vertex data into the buffer specified by m_VBOName.
    glNamedBufferData(m_VBOName, _bufferSize, _data, ToGLBufferUsage(m_BufferUsage));
}

GL_cbtVertexBuffer::~GL_cbtVertexBuffer() { glDeleteBuffers(1, &this->m_VBOName); }

void GL_cbtVertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, this->m_VBOName); }

void GL_cbtVertexBuffer::SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) { glNamedBufferSubData(this->m_VBOName, _offset, _dataSize, _data); }

void GL_cbtVertexBuffer::SetData(cbtU32 _dataSize, void* _data) { glNamedBufferData(this->m_VBOName, _dataSize, _data, ToGLBufferUsage(m_BufferUsage)); }

NS_CBT_END

#endif // CBT_OPENGL