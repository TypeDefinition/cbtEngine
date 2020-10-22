#pragma once

// Include CBT
#include "Rendering/Buffer/cbtElementBuffer.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <GL/glew.h>

NS_CBT_BEGIN

    class GL_cbtElementBuffer : public cbtElementBuffer
    {
    protected:
        /** m_EBOName stores the handle of an Element Buffer Object(EBO).
          * EBOs are used for Indexed Rendering. */
        GLuint m_EBOName;

        virtual ~GL_cbtElementBuffer();

    public:
        GL_cbtElementBuffer(void* _data, cbtU32 _byteSize);

        GLuint GetEBOName() const
        {
            return m_EBOName;
        }

        virtual void Bind();

        virtual void SetSubData(void* _data, cbtU32 _byteSize, cbtU32 _byteOffset);
    };

NS_CBT_END

#endif // CBT_OPENGL