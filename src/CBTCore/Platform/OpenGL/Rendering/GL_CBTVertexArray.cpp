// Include CBT
#include "GL_cbtVertexArray.h"
#include "GL_cbtVertexBuffer.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

cbtVertexArray* cbtVertexArray::CreateVAO() { return new GL_cbtVertexArray(); }

GL_cbtVertexArray::GL_cbtVertexArray()
    : m_AttributeCounter(0)
    , m_VBOCounter(0)
{
    glCreateVertexArrays(1, &this->m_VAOName);
}

GL_cbtVertexArray::~GL_cbtVertexArray()
{
    glDeleteVertexArrays(1, &this->m_VAOName); // Delete VAO
    for (cbtU32 i = 0; i < m_VBOs.size(); ++i) { m_VBOs[i]->AutoRelease(); } // Delete VBOs
    if (m_EBO) { m_EBO->AutoRelease(); } // Delete EBO
}

void GL_cbtVertexArray::Bind()
{
    glBindVertexArray(this->m_VAOName);
}

void GL_cbtVertexArray::AddVBO(cbtVertexBuffer* _vbo)
{
    m_VBOs.push_back(_vbo);
    _vbo->Retain();

    // Attach VBO to VAO.
    // glVertexAttribPointer attaches the VBO to the VAO. It also specifies how the VAO should read the various Vertex Attributes from the VBO.
    // Both the VAO and VBO needs to be binded before this function is called.
    // The reason that the offset (last parameter) needs to be a void pointer is due to legacy support. In the past, it used to mean a different thing.
    // For Learning - [https://stackoverflow.com/questions/37972229/glvertexattribpointer-and-glvertexattribformat-whats-the-difference]
    GLuint vboName = static_cast<GL_cbtVertexBuffer*>(_vbo)->GetVBOName();
    const cbtBufferLayout& layout = _vbo->GetLayout();
    const cbtBufferElement* elements = layout.GetElements();
    cbtU32 elementCount = layout.GetElementCount();

    glVertexArrayVertexBuffer(m_VAOName, m_VBOCounter, vboName, 0, layout.GetByteSize());
    glVertexArrayBindingDivisor(m_VAOName, m_VBOCounter, _vbo->GetDivisor());

    for (cbtU32 i = 0; i < elementCount; ++i)
    {
        switch (elements[i].GetDataType())
        {
        case CBT_S32:
        case CBT_U32:
            glVertexArrayAttribIFormat(m_VAOName, m_AttributeCounter, elements[i].GetComponentCount(),
                ToGLDataType(elements[i].GetDataType()), elements[i].GetOffset());
            break;
        case CBT_F32:
            glVertexArrayAttribFormat(m_VAOName, m_AttributeCounter, elements[i].GetComponentCount(),
                ToGLDataType(elements[i].GetDataType()), elements[i].IsNormalized() ? GL_TRUE : GL_FALSE, elements[i].GetOffset());
            break;
        case CBT_F64:
            glVertexArrayAttribLFormat(m_VAOName, m_AttributeCounter, elements[i].GetComponentCount(),
                ToGLDataType(elements[i].GetDataType()), elements[i].GetOffset());
            break;
        default:
            CBT_ASSERT(false);
            break;
        }
    
        glVertexArrayAttribBinding(m_VAOName, m_AttributeCounter, m_VBOCounter);
        glEnableVertexArrayAttrib(m_VAOName, m_AttributeCounter);
        ++m_AttributeCounter;
    }

    ++m_VBOCounter;
}

void GL_cbtVertexArray::SetEBO(cbtElementBuffer* _ebo)
{
    _ebo->Retain();
    if (m_EBO != nullptr) { m_EBO->AutoRelease(); }
    m_EBO = _ebo;
    glVertexArrayElementBuffer(m_VAOName, m_EBO ? static_cast<GL_cbtElementBuffer*>(_ebo)->GetEBOName() : 0);
}

NS_CBT_END

#endif // CBT_OPENGL