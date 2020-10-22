// Include CBT
#include "GL_cbtElementBuffer.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

    cbtElementBuffer* cbtElementBuffer::CreateEBO(void* _data, cbtU32 _byteSize)
    {
        return new GL_cbtElementBuffer(_data, _byteSize);
    }

    GL_cbtElementBuffer::GL_cbtElementBuffer(void* _data, cbtU32 _byteSize)
            :cbtElementBuffer(_data, _byteSize)
    {
        glCreateBuffers(1, &this->m_EBOName);
        glNamedBufferData(this->m_EBOName, _byteSize, _data, GL_STATIC_DRAW);
    }

    GL_cbtElementBuffer::~GL_cbtElementBuffer()
    {
        glDeleteBuffers(1, &this->m_EBOName);
    }

    void GL_cbtElementBuffer::Bind()
    {
        // Must be bound only after VAO has been bound as this function modifies the VAO state. (https://www.khronos.org/opengl/wiki/Vertex_Specification, Vertex Array Object Section)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBOName);
    }

    void GL_cbtElementBuffer::SetSubData(void* _data, cbtU32 _byteSize, cbtU32 _byteOffset)
    {
        glNamedBufferSubData(m_EBOName, _byteOffset, _byteSize, _data);
    }

NS_CBT_END

#endif // CBT_OPENGL