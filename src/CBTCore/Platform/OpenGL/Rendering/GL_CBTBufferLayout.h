#pragma once

// Include CBT
#include "Rendering/Buffer/CBTBufferLayout.h"

#ifdef CBT_OPENGL

// Include GLEW
#include <glew.h>

NS_CBT_BEGIN

GLenum ToGLBufferUsage(CBTBufferUsage _usage);
GLenum ToGLDataType(CBTBufferDataType _dataType);

NS_CBT_END

#endif // CBT_OPENGL