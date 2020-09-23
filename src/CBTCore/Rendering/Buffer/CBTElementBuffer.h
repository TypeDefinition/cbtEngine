#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTRef.h"

NS_CBT_BEGIN

// Element Buffer Object
class CBTElementBuffer : public CBTManaged
{
protected:
    CBTElementBuffer(void* _data, cbtU32 _byteSize) {}
    virtual ~CBTElementBuffer() {}

public:
    virtual void Bind() = 0;
    virtual void SetSubData(void* _data, cbtU32 _byteSize, cbtU32 _byteOffset) = 0;

    static CBTElementBuffer* CreateEBO(void* _data, cbtU32 _byteSize);
};

NS_CBT_END