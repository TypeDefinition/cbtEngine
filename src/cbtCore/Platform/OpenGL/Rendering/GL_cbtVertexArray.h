// Include
#include "Rendering/Buffer/cbtVertexArray.h"
#include "GL_cbtVertexBuffer.h"
#include "GL_cbtElementBuffer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <GL/glew.h>

NS_CBT_BEGIN

    class GL_cbtVertexArray : public cbtVertexArray
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

        virtual ~GL_cbtVertexArray();

    public:
        GL_cbtVertexArray();

        virtual void Bind();

        virtual void AddVBO(cbtVertexBuffer* _vbo);

        virtual void SetEBO(cbtElementBuffer* _ebo);
    };

NS_CBT_END

#endif // CBT_OPENGL