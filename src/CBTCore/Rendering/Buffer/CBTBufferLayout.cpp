// Include CBT
#include "CBTBufferLayout.h"

NS_CBT_BEGIN

cbtU32 GetByteSize(CBTBufferDataType _dataType)
{
    switch (_dataType)
    {
    case CBTBufferDataType::CBT_S8:
    case CBTBufferDataType::CBT_U8:
        return 1;
    case CBTBufferDataType::CBT_S16:
    case CBTBufferDataType::CBT_U16:
    case CBTBufferDataType::CBT_F16:
        return 2;
    case CBTBufferDataType::CBT_S32:
    case CBTBufferDataType::CBT_U32:
    case CBTBufferDataType::CBT_F32:
        return 4;
    case CBTBufferDataType::CBT_F64:
        return 8;
    default:
        return 0;
    }
}

NS_CBT_END