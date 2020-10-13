#pragma once

// Include CBT
#include "GL_cbtBufferLayout.h"
#include "Rendering/Buffer/cbtVertexBuffer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

/** m_VBOName stores the handles of Vertex Buffer Objects(VBO).
  * The actual data of a 3D Model is stored in a VBO.
  * A VAO simply points to the data in the VBO to get the vertex attributes.
  * glVertexAttribPointer is then used to specify how the VAO reads the data from the VBOs. */
class GL_cbtVertexBuffer : public cbtVertexBuffer
{
protected:
    GLuint m_VBOName;

    virtual ~GL_cbtVertexBuffer();

public:
    GL_cbtVertexBuffer(const cbtBufferLayout& _layout, cbtBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize, void* _data);

    GLuint GetVBOName() const { return m_VBOName; }

    virtual void Bind();
    virtual void SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data);
    virtual void SetData(cbtU32 _dataSize, void* _data);
};

NS_CBT_END

#endif // CBT_OPENGL