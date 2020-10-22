#pragma once

// Include CBT
#include "Core/General/cbtRef.h"
#include "cbtBufferLayout.h"

NS_CBT_BEGIN

    class cbtUniformBuffer : public cbtManaged
    {
    protected:
        virtual ~cbtUniformBuffer()
        {
        }

    public:
        cbtUniformBuffer()
        {
        }

        virtual void Bind(cbtU32 _bufferIndex) = 0;

        virtual void SetData(cbtU32 _dataSize, void* _data) = 0;

        virtual void SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) = 0;

        static cbtUniformBuffer* CreateUniformBuffer();
    };

NS_CBT_END