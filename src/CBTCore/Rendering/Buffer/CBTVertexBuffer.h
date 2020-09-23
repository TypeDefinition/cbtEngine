#pragma once

// Include CBT
#include "Core/General/CBTRef.h"
#include "CBTBufferLayout.h"

NS_CBT_BEGIN

// Vertex Buffer Object
class CBTVertexBuffer : public CBTManaged
{
protected:
    const CBTBufferLayout m_Layout;
    const CBTBufferUsage m_BufferUsage;
    const cbtU32 m_Divisor;

    virtual ~CBTVertexBuffer() {}

public:
    CBTVertexBuffer(const CBTBufferLayout& _layout, CBTBufferUsage _usage, cbtU32 _divisor)
        : m_Layout(_layout)
        , m_BufferUsage(_usage)
        , m_Divisor(_divisor)
    {}

    inline const CBTBufferLayout& GetLayout() const { return m_Layout; }
    inline CBTBufferUsage GetBufferUsage() const { return m_BufferUsage; }
    inline cbtU32 GetDivisor() const { return m_Divisor; }

    virtual void Bind() = 0;
    virtual void SetSubData(cbtU32 _offset, cbtU32 _dataSize, void* _data) = 0;
    virtual void SetData(cbtU32 _dataSize, void* _data) = 0;

    static CBTVertexBuffer* CreateVBO(const CBTBufferLayout& _layout, CBTBufferUsage _usage, cbtU32 _divisor, cbtU32 _bufferSize, void* _data);
};

NS_CBT_END