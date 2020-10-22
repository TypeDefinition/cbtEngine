#pragma once

// Include CBT
#include "Core/General/cbtRef.h"
#include "cbtBufferLayout.h"

NS_CBT_BEGIN

// Vertex Buffer Object
    class cbtVertexBuffer : public cbtManaged
    {
    protected:
        const cbtBufferLayout m_Layout;
        const cbtBufferUsage m_BufferUsage;
        const cbtU32 m_Divisor;

        virtual ~cbtVertexBuffer()
        {
        }

    public:
        cbtVertexBuffer(const cbtBufferLayout& _layout, cbtBufferUsage _usage, cbtU32 _divisor)
                :m_Layout(_layout), m_BufferUsage(_usage), m_Divisor(_divisor)
        {
        }

        inline const cbtBufferLayout& GetLayout() const
        {
            return m_Layout;
        }

        inline cbtBufferUsage GetBufferUsage() const
        {
            return m_BufferUsage;
        }

        inline cbtU32 GetDivisor() const
        {
            return m_Divisor;
        }

        virtual void Bind() = 0;

        virtual void SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) = 0;

        virtual void SetData(cbtU32 _dataSize, void* _data) = 0;

        static cbtVertexBuffer*
        CreateVBO(const cbtBufferLayout& _layout, cbtBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize,
                void* _data);
    };

NS_CBT_END