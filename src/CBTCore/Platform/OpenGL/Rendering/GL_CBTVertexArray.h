// Include
#include "Rendering/Buffer/CBTVertexArray.h"
#include "GL_CBTVertexBuffer.h"
#include "GL_CBTElementBuffer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

class GL_CBTVertexArray : public CBTVertexArray
{
protected:
    /** m_VAOName stores the handle of a Vertex Array Object(VAO).
      * A VAO contains the various vertex attributes of a 3D model.
      * The actual data of the 3D Model is stored in a VBO.
      * The VAO simply points to the data in the VBO to get the vertex attributes.
      * glVertexAttribPointer is then used to specify how the VAO reads the data from the VBOs. */
    GLuint m_VAOName;
    cbtU32 m_AttributeCounter;
    cbtU32 m_VBOCounter;

    virtual ~GL_CBTVertexArray();

public:
    GL_CBTVertexArray();

    virtual void Bind();

    virtual void AddVBO(CBTVertexBuffer* _vbo);
    virtual void SetEBO(CBTElementBuffer* _ebo);
};

NS_CBT_END

#endif // CBT_OPENGL