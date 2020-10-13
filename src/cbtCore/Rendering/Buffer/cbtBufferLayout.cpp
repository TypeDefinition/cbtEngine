// Include CBT
#include "cbtBufferLayout.h"

NS_CBT_BEGIN

cbtU32 GetByteSize(cbtBufferDataType _dataType)
{
    switch (_dataType)
    {
    case cbtBufferDataType::CBT_S8:
    case cbtBufferDataType::CBT_U8:
        return 1;
    case cbtBufferDataType::CBT_S16:
    case cbtBufferDataType::CBT_U16:
    case cbtBufferDataType::CBT_F16:
        return 2;
    case cbtBufferDataType::CBT_S32:
    case cbtBufferDataType::CBT_U32:
    case cbtBufferDataType::CBT_F32:
        return 4;
    case cbtBufferDataType::CBT_F64:
        return 8;
    default:
        return 0;
    }
}

NS_CBT_END