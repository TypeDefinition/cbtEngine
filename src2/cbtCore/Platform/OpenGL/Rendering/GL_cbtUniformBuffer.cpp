// Include CBT
#include "GL_cbtUniformBuffer.h"

NS_CBT_BEGIN

cbtUniformBuffer* cbtUniformBuffer::CreateUniformBuffer() { return cbtNew GL_cbtUniformBuffer(); }

NS_CBT_END