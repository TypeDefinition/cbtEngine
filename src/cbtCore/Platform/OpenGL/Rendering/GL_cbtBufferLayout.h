#pragma once

// Include CBT
#include "Rendering/Buffer/cbtBufferLayout.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <GL/glew.h>

NS_CBT_BEGIN

GLenum ToGLBufferUsage(cbtBufferUsage _usage);
GLenum ToGLDataType(cbtBufferDataType _dataType);

NS_CBT_END

#endif // CBT_OPENGL