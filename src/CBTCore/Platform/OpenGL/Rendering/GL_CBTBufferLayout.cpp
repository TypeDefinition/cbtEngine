// Include CBT
#include "GL_cbtBufferLayout.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

GLenum ToGLBufferUsage(cbtBufferUsage _usage)
{
    switch (_usage)
    {
    case CBT_STREAM_DRAW:  return GL_STREAM_DRAW;
    case CBT_STREAM_READ:  return GL_STREAM_READ;
    case CBT_STREAM_COPY:  return GL_STREAM_COPY;
    case CBT_STATIC_DRAW:  return GL_STATIC_DRAW;
    case CBT_STATIC_READ:  return GL_STATIC_READ;
    case CBT_STATIC_COPY:  return GL_STATIC_COPY;
    case CBT_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
    case CBT_DYNAMIC_READ: return GL_DYNAMIC_READ;
    case CBT_DYNAMIC_COPY: return GL_DYNAMIC_COPY;
    default:               return GL_INVALID_ENUM;
    }
}

GLenum ToGLDataType(cbtBufferDataType _dataType)
{
    switch (_dataType)
    {
    case CBT_S8:  return GL_BYTE;
    case CBT_U8:  return GL_UNSIGNED_BYTE;
    case CBT_S16: return GL_SHORT;
    case CBT_U16: return GL_UNSIGNED_SHORT;
    case CBT_F16: return GL_HALF_FLOAT;
    case CBT_S32: return GL_INT;
    case CBT_U32: return GL_UNSIGNED_INT;
    case CBT_F32: return GL_FLOAT;
    case CBT_F64: return GL_DOUBLE;
    default:      return GL_INVALID_ENUM;
    }
}

NS_CBT_END

#endif // CBT_OPENGL