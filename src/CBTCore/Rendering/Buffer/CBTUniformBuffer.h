#pragma once

// Include CBT
#include "Core/General/CBTRef.h"
#include "CBTBufferLayout.h"

NS_CBT_BEGIN

class CBTUniformBuffer : public CBTManaged
{
protected:
    virtual ~CBTUniformBuffer() {}

public:
    CBTUniformBuffer() {}

    virtual void Bind(cbtU32 _bufferIndex) = 0;
    virtual void SetData(cbtU32 _dataSize, void* _data) = 0;
    virtual void SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) = 0;

    static CBTUniformBuffer* CreateUniformBuffer();
};

NS_CBT_END