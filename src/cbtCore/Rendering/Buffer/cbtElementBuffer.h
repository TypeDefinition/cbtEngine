#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/General/cbtRef.h"

NS_CBT_BEGIN

// Element Buffer Object
    class cbtElementBuffer : public cbtManaged
    {
    protected:
        cbtElementBuffer(void* _data, cbtU32 _byteSize)
        {
        }

        virtual ~cbtElementBuffer()
        {
        }

    public:
        virtual void Bind() = 0;

        virtual void SetSubData(void* _data, cbtU32 _byteSize, cbtU32 _byteOffset) = 0;

        static cbtElementBuffer* CreateEBO(void* _data, cbtU32 _byteSize);
    };

NS_CBT_END