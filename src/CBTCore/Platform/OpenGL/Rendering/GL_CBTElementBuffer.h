#pragma once

// Include CBT
#include "Rendering/Buffer/CBTElementBuffer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

class GL_CBTElementBuffer : public CBTElementBuffer
{
protected:
    /** m_EBOName stores the handle of an Element Buffer Object(EBO).
      * EBOs are used for Indexed Rendering. */
    GLuint m_EBOName;

    virtual ~GL_CBTElementBuffer();

public:
    GL_CBTElementBuffer(void* _data, cbtU32 _byteSize);

    GLuint GetEBOName() const { return m_EBOName; }

    virtual void Bind();
    virtual void SetSubData(void* _data, cbtU32 _byteSize, cbtU32 _byteOffset);
};

NS_CBT_END

#endif // CBT_OPENGL